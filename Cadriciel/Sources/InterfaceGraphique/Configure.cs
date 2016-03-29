////////////////////////////////////////////////
/// @file   Configure.cs
/// @author Philippe Marcotte et Frédéric Grégoire
/// @date   2016-02-22
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Runtime.InteropServices;
using TypeCommandeEnum;
using TypeComportementEnum;

namespace InterfaceGraphique
{
    public partial class Configure : Form
    {
        /// <summary>
        /// Culture pour convertir les string, ayant un point pour délimiter les décimales, en double
        /// </summary>
        System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.InvariantCulture;
        
        /// <summary>
        /// Liste contenant tous les types de comportements d'un robot
        /// </summary>
        private List<TypeComportement> comportementsList;

        /// <summary>
        /// Liste contenant tous les noms de profils que l'on peut charger
        /// </summary>
        private List<string> fichiersProfil;

        /// <summary>
        /// Chemin vers le dossier Donnees
        /// </summary>
        private string cheminProfils;

        /// <summary>
        /// Extension d'un fichier de type profil
        /// </summary>
        private string extensionProfils;

        /// <summary>
        /// Nom du profil par défaut
        /// </summary>
        private string nomProfilDefaut;

        /// <summary>
        /// Nom du dernier profil chargé
        /// </summary>
        private string nomDernierProfil;

        /// <summary>
        /// Index du profil par défaut dans la combobox permettant de choisir les profils
        /// </summary>
        private int indexProfilDefaut;

        /// <summary>
        /// Fonction déléguée représentant la fonction servant à ajouter un profil dans le ToolStripMenuItem contenant les profils lors d'une simulation ou test
        /// </summary>
        public delegate void ajouterProfilSimulationDelegue(string nomProfil);

        /// <summary>
        /// Référence vers la fonction servant à ajouter un profil dans le ToolStripMenuItem contenant les profils lors d'une simulation ou test
        /// </summary>
        private ajouterProfilSimulationDelegue ajouterProfilSimulation;

        /// <summary>
        /// Référence vers le ToolStripMenuItem contenant les profils lors d'une simulation ou test
        /// </summary>
        private ToolStripMenuItem profilsSimulationItem;

        /// <summary>
        /// Enum représentant les types de paramètres associés aux comportements
        /// </summary>
        private enum typeParametre
        {
            ANGLE,
            DUREE,
            LARGEUR_ZONE
        }

        /// <summary>
        /// Structure contenant les limites pour chacun des types de paramètres associés aux comportements
        /// </summary>
        private struct Parametre
        {
            public int limiteMin;
            public int limiteMax;
        }

        /// <summary>
        /// Tableau contenant les 3 struct Parametre
        /// </summary>
        private Parametre[] limitesParametres;

        /// <summary>
        /// Tableau contenant les TextBox servant à modifier la largeur des zones sécuritaires et de dangers
        /// </summary>
        private TextBox[] largeurZoneTextBox;

        /// <summary>
        /// Tableau contenant les TextBox servant à modifier les touches contrôlant le robot
        /// </summary>
        private TextBox[] touchesCommande;

        /// <summary>
        /// Représente si le programme initialise les TextBox des paramètres associés aux comportements
        /// </summary>
        private bool initialisationParametres;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Configure(ToolStripMenuItem menuItem, ajouterProfilSimulationDelegue fonction)
        ///
        /// Constructeur par paramètre
        /// 
        /// @param[in] menuItem : Référence vers le ToolStripMenuItem contenant les profils lors d'une simulation ou test
        /// @param[in] fonction : Référence servant à ajouter un profil dans le ToolStripMenuItem contenant les profils lors d'une simulation ou test
        ///
        ////////////////////////////////////////////////////////////////////////
        public Configure(ToolStripMenuItem menuItem, ajouterProfilSimulationDelegue fonction)
        {
            InitializeComponent();

            profilsSimulationItem = menuItem;

            ajouterProfilSimulation = fonction;

            comportementsList = Enum.GetValues(typeof(TypeComportement)).Cast<TypeComportement>().ToList();

            int[] minEtMaxParametres = FonctionsNatives.obtenirLimitesParametres(Enum.GetNames(typeof(typeParametre)).Length * 2);

            limitesParametres = new Parametre[Enum.GetNames(typeof(typeParametre)).Length];

            for (int i = 0; i < minEtMaxParametres.Length; i+= 2)
            {
                limitesParametres[i / 2].limiteMin = minEtMaxParametres[i];
                limitesParametres[i / 2].limiteMax = minEtMaxParametres[i + 1];
            }

            largeurZoneTextBox = new TextBox[] { longueurDangerGaucheTxtBox, longueurSecuritaireGaucheTxtBox, longueurDangerCentreTxtBox, longueurSecuritaireCentreTxtBox, longueurDangerDroitTxtBox, longueurSecuritaireDroitTxtBox };

            touchesCommande = new TextBox[] { textBoxModeManuel, textBoxAvancer, textBoxReculer, textBoxAntiHoraire, textBoxHoraire };

            cheminProfils = FonctionsNatives.obtenirCheminProfils();

            extensionProfils = FonctionsNatives.obtenirExtensionProfils();

            FonctionsNatives.assignerConfigureHandles((IntPtr)comboBoxProfil.Handle, Int32.Parse((String)comboBoxProfil.Tag));

            assignerHandles();

            initialisationParametres = true;

            assignerProfilsCB();

            initialisationParametres = false;
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public List<string> FichiersProfil
        ///
        /// Fonction retournant la liste des noms de profils
        ///
        /// @return List<string>
        ///
        ////////////////////////////////////////////////////////////////////////
        public List<string> FichiersProfil
        {
            get
            {
                return fichiersProfil;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public string NomDernierProfil
        ///
        /// Fonction retournant le nom du dernier profil chargé
        ///
        /// @return string
        ///
        ////////////////////////////////////////////////////////////////////////
        public string NomDernierProfil
        {
            get
            {
                return FonctionsNatives.obtenirNomDernierProfil();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void assignerProfilsCB()
        ///
        /// Cette fonction permet de populer la ComboBox contenant les profils que l'on peut charger
        ///
        ////////////////////////////////////////////////////////////////////////
        private void assignerProfilsCB(){
            comboBoxProfil.Items.Clear();
            FonctionsNatives.chargerDernierProfil();

            nomDernierProfil = FonctionsNatives.obtenirNomDernierProfil();

            nomProfilDefaut = FonctionsNatives.obtenirNomProfilDefaut();

            fichiersProfil = new List<string>(System.IO.Directory.GetFiles(cheminProfils, "*" + extensionProfils));
            string nomFichier;
            for (int i = 0; i < fichiersProfil.Count; i++)
            {
                nomFichier = System.IO.Path.GetFileName(fichiersProfil[i]);
                fichiersProfil[i] = nomFichier.Substring(0, nomFichier.IndexOf('.'));
            }
            indexProfilDefaut = fichiersProfil.FindIndex(nom => nom == nomProfilDefaut);
            string tmp = fichiersProfil[0];
            fichiersProfil[0] = fichiersProfil[indexProfilDefaut];
            fichiersProfil[indexProfilDefaut] = tmp;
            indexProfilDefaut = 0;
            comboBoxProfil.Items.AddRange(fichiersProfil.ToArray());

            comboBoxProfil.SelectedIndexChanged -= comboBoxProfil_SelectedIndexChanged;
            comboBoxProfil.SelectedIndex = comboBoxProfil.FindString(nomDernierProfil);
            comboBoxProfil.SelectedIndexChanged += comboBoxProfil_SelectedIndexChanged;

            

            int indexCommande = 0;
            foreach (TextBox box in touchesCommande)
            {
                box.Text = afficherCaractere(FonctionsNatives.obtenirToucheCommande((TypeCommande)indexCommande++));
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void assignerHandles()
        ///
        /// Fonction appelant la fonction récursive du même nom à partir de la composante représetant les onglets principaux.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void assignerHandles()
        {
            button_Default.Enabled = false;
            assignerHandles(configureTabs);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void assignerHandles(Control control)
        ///
        /// Fonction récursive permettant d'envoyer le handle de chaque composant au modele et de desactiver les composantes servant à modifier les paramètres des comportements
        /// 
        /// @param[in] control : Composante à partir de laquelle on veut assigner les handles
        ///
        ////////////////////////////////////////////////////////////////////////
        private void assignerHandles(Control control)
        {
            foreach (Control item in control.Controls)
            {
                if (item.Tag != null)
                {
                    item.Enabled = false;
                    int indexControl = Int32.Parse(item.Tag.ToString().Split(';')[0]);
                    if (item.GetType().Equals(typeof(ComboBox)) && indexControl <= 23)
                    {
                        ComboBox combo = item as ComboBox;
                        combo.BindingContext = new BindingContext();
                        combo.DataSource = comportementsList;
                    }
                    FonctionsNatives.assignerConfigureHandles((IntPtr)item.Handle, indexControl);
                }

                assignerHandles(item);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void changerEtatComposantesParametres(bool etat)
        ///
        /// Fonction appelant la fonction récursive du même nom à partir de la composante représetant les onglets principaux.
        /// 
        /// @param[in] etat : Représentante si la composante doiêtre active ou non
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void changerEtatComposantesParametres(bool etat)
        {
            button_Default.Enabled = etat;
            changerEtatComposantesParametres(configureTabs, etat);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void changerEtatComposantesParametres(Control control, bool etat)
        ///
        /// Fonction appelant la fonction récursive du même nom à partir de la composante représetant les onglets principaux.
        /// 
        /// @param[in] control : Composante à partir de laquelle on cherche les composantes à modifier
        /// @param[in] etat : Représentante si la composante doiêtre active ou non
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void changerEtatComposantesParametres(Control control, bool etat)
        {
            foreach (Control item in control.Controls)
            {
                if (item.Tag != null)
                    item.Enabled = etat;

                changerEtatComposantesParametres(item, etat);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool caractereInvalide(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private bool caractereInvalide(object sender, KeyPressEventArgs e)
        { return e.Handled = !(/*char.IsLetterOrDigit(e.KeyChar)*/true); }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxAvancer_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigne le comportement avancer
        /// a la touche en changement l'affichage dans configure
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void textBoxAvancer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.AVANCER);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.AVANCER);
            textBoxAvancer.Text = afficherCaractere(caractere);
            textBoxAvancer.Select(textBoxAvancer.Text.Length, 0);    
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxReculer_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigne le comportement reculer
        /// a la touche en changement l'affichage dans configure
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void textBoxReculer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.RECULER);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.RECULER);
            textBoxReculer.Text = afficherCaractere(caractere);
            textBoxReculer.Select(textBoxReculer.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxAntiHoraire_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigne le comportement tourner gauche
        /// a la touche en changement l'affichage dans configure
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void textBoxAntiHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.ROTATION_GAUCHE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.ROTATION_GAUCHE);
            textBoxAntiHoraire.Text = afficherCaractere(caractere);
            textBoxAntiHoraire.Select(textBoxAntiHoraire.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxHoraire_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigne le comportement tourner droit
        /// a la touche en changement l'affichage dans configure
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void textBoxHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.ROTATION_DROITE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.ROTATION_DROITE);
            textBoxHoraire.Text = afficherCaractere(caractere);
            textBoxHoraire.Select(textBoxHoraire.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigne le comportement tourner droit
        /// a la touche en changement l'affichage dans configure
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.INVERSER_MODE_CONTROLE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.INVERSER_MODE_CONTROLE);
            textBoxModeManuel.Text = afficherCaractere(caractere);
            textBoxModeManuel.Select(textBoxReculer.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn string afficherCaractere(char caractere)
        ///
        /// Cette fonction prend un char et retourne une string avec le nom complet de la touche
        ///
        /// @param[in] char caractere: char représentant la touche
        ///
        /// @return string: le nom complet représentant le char
        /// 
        ////////////////////////////////////////////////////////////////////////
        string afficherCaractere(char caractere)
        {
            string mot = caractere.ToString();
            if (caractere == ' ')
            {
                mot = "ESPACE";
            }
            else if (caractere == '\r')
            {
                mot = "Enter";
            }
            else if (caractere == '\b')
            {
                mot = "Backspace";
            }
            return mot;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEtDureeValidation(TextBox box, typeParametre parametre)
        ///
        /// Cette fonction permet de vérifier l'intégrité d'un angle ou d'une duree entré par un utilisateur
        ///
        /// @param[in] box: la text box modifiée par l'utilisateur
        /// @param[in] parametre: représente si c'est un angle ou une durée
        ///
        ////////////////////////////////////////////////////////////////////////
        private void angleEtDureeValidation(TextBox box, typeParametre parametre)
        {
            double nombre;
            string nouvelleValeur = null;
            int indexParametre = (int)parametre;
            if (Double.TryParse(box.Text.Replace(',', '.'), System.Globalization.NumberStyles.Float, culture, out nombre) && BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(nombre))[3])[2] <= 2)
            {
                if (nombre > limitesParametres[indexParametre].limiteMax)
                    nouvelleValeur = limitesParametres[indexParametre].limiteMax.ToString();
                else if (nombre < limitesParametres[indexParametre].limiteMin)
                    nouvelleValeur = limitesParametres[indexParametre].limiteMin.ToString();
            }
            else
                nouvelleValeur = oldText;

            if(nouvelleValeur != null)
                box.Text = nouvelleValeur;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void largeurZoneValidation(TextBox box)
        ///
        /// Cette fonction permet de vérifier l'intégrité d'une largeur de zone de capteur de distance entrée par un utilisateur
        ///
        /// @param[in] box: la text box modifiée par l'utilisateur
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void largeurZoneValidation(TextBox box)
        {
            int indexTextBox = int.Parse(box.Tag.ToString().Split(';')[1]);
            int indexTextBoxComplementaire = indexTextBox % 2 == 0 ? indexTextBox + 1 : indexTextBox - 1;
            largeurZoneTextBox[indexTextBoxComplementaire].TextChanged -= largeurZoneTxtBox_TextChanged;
            TextBox boxComplementaire = largeurZoneTextBox[indexTextBoxComplementaire];
            double largeur1;
            double largeur2 = stringToDouble(boxComplementaire.Text);
            int indexParametre = (int)typeParametre.LARGEUR_ZONE;
            if (Double.TryParse(box.Text.Replace(',', '.'), System.Globalization.NumberStyles.Float, culture, out largeur1) && BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(largeur1))[3])[2] <= 2)
            {
                if (largeur1 > limitesParametres[indexParametre].limiteMax)
                {
                    box.Text = limitesParametres[indexParametre].limiteMax.ToString();
                    boxComplementaire.Text = limitesParametres[indexParametre].limiteMin.ToString();
                }
                else if (largeur1 + largeur2 > limitesParametres[indexParametre].limiteMax)
                    boxComplementaire.Text = (limitesParametres[indexParametre].limiteMax - largeur1).ToString();
                else if (largeur1 < limitesParametres[indexParametre].limiteMin)
                    box.Text = limitesParametres[indexParametre].limiteMin.ToString();
            }
            else
                box.Text = oldText;

            boxComplementaire.TextChanged += largeurZoneTxtBox_TextChanged;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void parametresValidation(TextBox box, typeParametre parametre)
        ///
        /// Cette fonction permet de vérifier si la valeur entré par un utilisateur n'est pas nulle.
        /// Dans le cas échéant, on vérifie l'intégrité de la valeur.
        ///
        /// @param[in] box: la text box modifiée par l'utilisateur
        /// @param[in] parametre: représente si c'est un angle, une durée ou une largeur de zone
        ///
        ////////////////////////////////////////////////////////////////////////
        private void parametresValidation(TextBox box, typeParametre parametre)
        {
            if (box.Text == "")
                box.Text = "0";
            else if (oldText == "0" && box.Text[1] != '0' && box.Text[1] != '.' && box.Text[1] != ',')
                box.Text = box.Text.Replace("0", "");
            
            if (!decimalCheck(box))
            {
                switch (parametre)
                {
                    case typeParametre.ANGLE:
                    case typeParametre.DUREE:
                        angleEtDureeValidation(box, parametre);
                        break;
                    case typeParametre.LARGEUR_ZONE:
                        largeurZoneValidation(box);
                        break;
                }
            }

            box.SelectionStart = oldCaretIndex + 1;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  private bool decimalCheck(TextBox box)
        ///
        /// Cette fonction permet de valider d'un nombre ou il ne peut qu'y avoir deux chiffre apres
        /// une virgule
        ///
        /// @param[in] TextBox box: la textbox a vérifier
        ///
        /// @return: Aucun
        /// 
        ////////////////////////////////////////////////////////////////////////
        private bool decimalCheck(TextBox box)
        {
            if (box.Text.Count(f => f == '.' | f == ',') == 1 && (box.Text.IndexOf('.') > box.TextLength - 3 || box.Text.IndexOf(',') > box.TextLength - 3))
            {
                string[] tags = box.Tag.ToString().Split(';');
                if (tags[tags.Length - 1] != "true")
                {
                    box.Tag = box.Tag + ";true";
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// String représentant l'ancienne valeur du textbox
        /// </summary>
        private string oldText;
        
        /// <summary>
        /// Integer représentant l'ancienne position du caret
        /// </summary>
        private int oldCaretIndex;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleTxtBox_TextChanged(object sender, EventArgs e)
        {
            TextBox box = sender as TextBox;
            box.TextChanged -= angleTxtBox_TextChanged;
            parametresValidation(box, typeParametre.ANGLE);
            box.TextChanged += angleTxtBox_TextChanged;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dureeTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void dureeTxtBox_TextChanged(object sender, EventArgs e)
        {
            TextBox box = sender as TextBox;
            box.TextChanged -= dureeTxtBox_TextChanged;
            parametresValidation(box, typeParametre.DUREE);
            box.TextChanged += dureeTxtBox_TextChanged;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void largeurZoneTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void largeurZoneTxtBox_TextChanged(object sender, EventArgs e)
        {
            if (initialisationParametres)
                return;

            TextBox box = sender as TextBox;
            box.TextChanged -= largeurZoneTxtBox_TextChanged;
            parametresValidation(box, typeParametre.LARGEUR_ZONE);
            box.TextChanged += largeurZoneTxtBox_TextChanged;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void parametreTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText ainsi que la position du caret.
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void parametreTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            TextBox box = sender as TextBox;
            oldText = box.Text;
            oldCaretIndex = box.SelectionStart;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void retourMenuButt_Click(object sender, EventArgs e)
        ///
        /// Cette fonction ferme la fenetre si le resultat du dialog vaut OK
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void retourMenuButt_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void comboBoxProfil_SelectedIndexChanged(object sender, EventArgs e)
        ///
        /// Cette fonction charge le profil lors d'un changement d'indexe de la ComboBox contenat les profils pouvant être chargés
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void comboBoxProfil_SelectedIndexChanged(object sender, EventArgs e)
        {
            string nomProfil = (string)(sender as ComboBox).SelectedItem;
            if (!comboBoxProfil.Items.Cast<string>().Any(cbi => cbi.Equals(nomProfil)))
                return;

            (profilsSimulationItem.DropDownItems.Find(FonctionsNatives.obtenirNomDernierProfil(), false)[0] as ToolStripMenuItem).Checked = false;
            (profilsSimulationItem.DropDownItems.Find(nomProfil, false)[0] as ToolStripMenuItem).Checked = true;

            changerProfil(nomProfil);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void changerProfil(string nomProfil)
        ///
        /// Cette fonction charge le profil sélectionner dans la ComboBox contenat les profils pouvant être chargés
        ///
        /// @param nomProfil : le nom du profil à charger
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void changerProfil(string nomProfil)
        {
            FonctionsNatives.changerProfil(nomProfil + extensionProfils);
            int i = 0;
            foreach (TextBox box in touchesCommande)
            {
                box.Text = afficherCaractere(FonctionsNatives.obtenirToucheCommande((TypeCommande)i++));
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void changerProfilSelectionne(string nomProfil)
        ///
        /// Cette fonction change le profil sélectionné par la ComboBox contenat les profils pouvant être chargés
        ///
        /// @param nomProfil : le nom du profil à sélectionner
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void changerProfilSelectionne(string nomProfil){
            comboBoxProfil.SelectedIndex = comboBoxProfil.FindString(nomProfil);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// private enum creationProfil
        ///
        /// Etat dans la creation d'un profil
        /// 
        ////////////////////////////////////////////////////////////////////////
        private enum actionProfil
        {
            ATTENTE_ACTION,
            ATTENTE_CONFIRMATION
        }

        /// <summary>
        /// Représente l'état du bouton pour créer un profil
        /// </summary>
        private actionProfil etatCreationProfil = actionProfil.ATTENTE_ACTION;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonCréerProfil_Click(object sender, EventArgs e)
        ///
        /// Cette fonction permet de gérer la création d'un profil
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un click de souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void buttonCréerProfil_Click(object sender, EventArgs e)
        {
            if (etatCreationProfil == actionProfil.ATTENTE_ACTION)
            {
                comboBoxProfil.DropDownStyle = ComboBoxStyle.Simple;
                comboBoxProfil.Focus();
                buttonCréerProfil.Text = "Confirmer création";
                etatCreationProfil = actionProfil.ATTENTE_CONFIRMATION;
                modifierProfilButt.Enabled = false;
                buttonDeleteProfil.Enabled = false;
                retourMenuButt.Enabled = false;
            }
            else
            {
                buttonCréerProfil.Text = "Nouveau profil";
                string nouvelItem = comboBoxProfil.Text;

                string nomSiDoublon = nouvelItem;
                int nombre = 1;
                while (comboBoxProfil.Items.Cast<string>().Any(cbi => cbi.Equals(nomSiDoublon)))
                    nomSiDoublon = nouvelItem + nombre++;

                comboBoxProfil.Items.Add(nomSiDoublon);
                ajouterProfilSimulation(nomSiDoublon);
                (profilsSimulationItem.DropDownItems.Find(nomSiDoublon, false)[0] as ToolStripMenuItem).Checked = true;
                comboBoxProfil.SelectedIndex = comboBoxProfil.Items.Count - 1;
                comboBoxProfil.DropDownStyle = ComboBoxStyle.DropDownList;
                etatCreationProfil = actionProfil.ATTENTE_ACTION;
                modifierProfilButt.Enabled = true;
                buttonDeleteProfil.Enabled = true;
                retourMenuButt.Enabled = true;
            }
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonDeleteProfil_Click(object sender, EventArgs e)
        ///
        /// Cette fonction permet de gérer la suppression d'un profil
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un click de souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void buttonDeleteProfil_Click(object sender, EventArgs e)
        {
            string profilASupprimer = comboBoxProfil.Text;
            if (profilASupprimer == nomProfilDefaut)
                return;
            FonctionsNatives.supprimerProfil(profilASupprimer + extensionProfils);
            comboBoxProfil.Items.Remove(profilASupprimer);
            profilsSimulationItem.DropDownItems.Remove(profilsSimulationItem.DropDownItems.Find(profilASupprimer, false)[0]);
            (profilsSimulationItem.DropDownItems.Find(nomProfilDefaut, false)[0] as ToolStripMenuItem).Checked = true;
            comboBoxProfil.SelectedIndexChanged -= comboBoxProfil_SelectedIndexChanged;
            comboBoxProfil.SelectedIndex = indexProfilDefaut;
            comboBoxProfil.SelectedIndexChanged += comboBoxProfil_SelectedIndexChanged;
        }

        /// <summary>
        /// Représente l'état du bouton pour modifier un profil
        /// </summary>
        private actionProfil etatModificationProfil = actionProfil.ATTENTE_ACTION;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modifierProfilButt_Click(object sender, EventArgs e)
        ///
        /// Cette fonction permet de gérer la modification d'un profil
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un click de souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void modifierProfilButt_Click(object sender, EventArgs e)
        {
            if (comboBoxProfil.SelectedIndex == indexProfilDefaut)
                return;

            bool composanteEnabled;


            if (etatModificationProfil == actionProfil.ATTENTE_ACTION)
            {
                composanteEnabled = true;
                modifierProfilButt.Text = "Enregistrer";
                etatModificationProfil = actionProfil.ATTENTE_CONFIRMATION;
                buttonCréerProfil.Enabled = false;
                buttonDeleteProfil.Enabled = false;
                retourMenuButt.Enabled = false;
                comboBoxProfil.Enabled = false;
            }
            else
            {
                FonctionsNatives.assignerComportementSuivreLigne((TypeComportement)suiviLigneCB.SelectedValue);
                
                FonctionsNatives.assignerComportementBalayage((TypeComportement)balayageCB.SelectedValue);      
                
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, stringToDouble(angleDGTxtBox.Text), TypeComportement.DEVIATIONVERSLAGAUCHE);
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, stringToDouble(angleDDTxtBox.Text), TypeComportement.DEVIATIONVERSLADROITE);
                
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, stringToDouble(angleEGTxtBox.Text), stringToDouble(dureeEGTxtBox.Text)/1000, TypeComportement.EVITEMENTPARLAGAUCHE);
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, stringToDouble(angleEDTxtBox.Text), stringToDouble(dureeEDTxtBox.Text)/1000, TypeComportement.EVITEMENTPARLADROITE);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistDroitCB.SelectedIndex == 0, (TypeComportement)zoneDangerDroitCB.SelectedValue, stringToDouble(longueurDangerDroitTxtBox.Text), (TypeComportement)zoneSecuritaireDroitCB.SelectedValue, stringToDouble(longueurSecuritaireDroitTxtBox.Text), 0);
                FonctionsNatives.assignerCapteurDistance(capteurDistCentreCB.SelectedIndex == 0, (TypeComportement)zoneDangerCentreCB.SelectedValue, stringToDouble(longueurDangerCentreTxtBox.Text), (TypeComportement)zoneSecuritaireCentreCB.SelectedValue, stringToDouble(longueurSecuritaireCentreTxtBox.Text), 1);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistGaucheCB.SelectedIndex == 0, (TypeComportement)zoneDangerGaucheCB.SelectedValue, stringToDouble(longueurDangerGaucheTxtBox.Text), (TypeComportement)zoneSecuritaireGaucheCB.SelectedValue, stringToDouble(longueurSecuritaireGaucheTxtBox.Text), 2);
                
                FonctionsNatives.assignerSuiveurLigne(suiveurLigneCB.SelectedIndex == 0);
                
                FonctionsNatives.assignerOptionsDebogages(optionsDebogagesCB.SelectedIndex == 0, comboBox_comportement.SelectedIndex == 0, comboBox_eclairage.SelectedIndex == 0, comboBox_capteur.SelectedIndex == 0);
                
                FonctionsNatives.sauvegarderProfil(comboBoxProfil.Text + extensionProfils);
                
                composanteEnabled = false;
                modifierProfilButt.Text = "Modifier";
                etatModificationProfil = actionProfil.ATTENTE_ACTION;
                buttonCréerProfil.Enabled = true;
                buttonDeleteProfil.Enabled = true;
                retourMenuButt.Enabled = true;
                comboBoxProfil.Enabled = true;
            }

            changerEtatComposantesParametres(composanteEnabled);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modifierProfilButt_Click(object sender, EventArgs e)
        ///
        /// Cette fonction permet de gérer la modification d'un profil
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un click de souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void optionsDebogagesCB_SelectionChangeCommitted(object sender, EventArgs e)
        {
            bool estActif = optionsDebogagesCB.SelectedIndex == 0;
            comboBox_comportement.Enabled = estActif;
            comboBox_eclairage.Enabled = estActif;
            comboBox_capteur.Enabled = estActif;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void button_Default_Click(object sender, EventArgs e)
        ///
        /// Cette fonction remet les touches contrôlant le robot aux valeurs par défaut
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un click de souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void button_Default_Click(object sender, EventArgs e)
        {
            FonctionsNatives.modifierToucheCommande('W', TypeCommande.AVANCER);
            textBoxAvancer.Text = "W";
            FonctionsNatives.modifierToucheCommande('S', TypeCommande.RECULER);
            textBoxReculer.Text = "S";
            FonctionsNatives.modifierToucheCommande('A', TypeCommande.ROTATION_GAUCHE);
            textBoxAntiHoraire.Text = "A";
            FonctionsNatives.modifierToucheCommande('D', TypeCommande.ROTATION_DROITE);
            textBoxHoraire.Text = "D";
            FonctionsNatives.modifierToucheCommande(' ', TypeCommande.INVERSER_MODE_CONTROLE);
            textBoxModeManuel.Text = "ESPACE";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private double stringToDouble(string aConvertir)
        ///
        /// Cette fonction convertit une string à un double. Si la string est vide, celle-ci renvoie 0.
        ///
        /// @param aConvertir : la string à convertir
        /// 
        /// @return double La valeur de la string en double
        /// 
        ////////////////////////////////////////////////////////////////////////
        private double stringToDouble(string aConvertir)
        {
            if (aConvertir == "")
                return 0.0;

            return Double.Parse(aConvertir.Replace(',','.'), culture);
        }
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn  static partial class FonctionsNatives
    ///
    /// Permet de faire le lien avec les méthodes implémentées dans le C++
    ///
    ////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives{
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerComportementSuivreLigne(TypeComportement comportementSuivant);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerComportementBalayage(TypeComportement comportementSuivant);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerComportementDeviation(TypeComportement comportementSuivant, double angle, TypeComportement typeDeviation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerComportementEvitement(TypeComportement comportementSuivant, double angle, double duree, TypeComportement typeEvitement);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderProfil(string nomProfil);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerCapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire, int indexCapteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerSuiveurLigne(bool estActif);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerOptionsDebogages(bool debogageActif, bool debogageComportements, bool debogageEclairage, bool debogageCapteurs);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modifierToucheCommande(char touche, TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void obtenirNomProfilDefaut(StringBuilder str, int longueur);
        public static string obtenirNomProfilDefaut()
        {
            StringBuilder str = new StringBuilder(100);
            obtenirNomProfilDefaut(str, str.Capacity);
            return str.ToString();
        }

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void obtenirNomDernierProfil(StringBuilder str, int longueur);
        public static string obtenirNomDernierProfil()
        {
            StringBuilder str = new StringBuilder(100);
            obtenirNomDernierProfil(str, str.Capacity);
            return str.ToString();
        }

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerDernierProfil();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern char obtenirToucheCommande(TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerConfigureHandles(IntPtr handle, int ctrl);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void obtenirExtensionProfils(StringBuilder str, int longueur);
        public static string obtenirExtensionProfils()
        {
            StringBuilder str = new StringBuilder(100);
            obtenirExtensionProfils(str, str.Capacity);
            return str.ToString();
        }

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void obtenirCheminProfils(StringBuilder str, int longueur);
        public static string obtenirCheminProfils()
        {
            StringBuilder str = new StringBuilder(100);
            obtenirCheminProfils(str, str.Capacity);
            return str.ToString();
        }

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerProfil(string nomProfil);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerProfil(string nomProfil);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr obtenirLimitesParametres();
        public static int[] obtenirLimitesParametres(int taille)
        {
            int[] limitesParametres = new int[taille];
            Marshal.Copy(obtenirLimitesParametres(), limitesParametres, 0, taille);
            return limitesParametres;
        }
    }
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////