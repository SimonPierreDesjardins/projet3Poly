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

        System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.InvariantCulture;
        private List<TypeComportement> comportementsList;

        private List<string> fichiersProfil;

        public List<string> FichiersProfil
        {
            get
            {
                return fichiersProfil;
            }
        }

        private string cheminProfils;

        private string extensionProfils;
        public string ExtensionProfils
        {
            get
            {
                return extensionProfils;
            }
        }

        private string nomProfilDefaut;
        public string NomProfilInitiale
        {
            get
            {
                return nomProfilDefaut;
            }
        }
        private int indexProfilDefaut;

        public delegate void ajouterProfilAMenuDelegue(string nomProfil);

        private ajouterProfilAMenuDelegue ajouterProfilAMenu;

        private enum typeParametre
        {
            ANGLE,
            DUREE,
            LARGEUR_ZONE
        }

        private struct Parametre
        {
            public int limiteMin;
            public int limiteMax;
        }

        private Parametre[] limitesParametres;

        private TextBox[] largeurZoneTextBoxes;

        private bool initialisation;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Configure()
        ///
        /// Cette fonction initialize la fenetre et initialise la visibilité de
        /// ses composantes
        ///
        ////////////////////////////////////////////////////////////////////////
        public Configure(ajouterProfilAMenuDelegue fonction)
        {
            InitializeComponent();

            ajouterProfilAMenu = fonction;

            comportementsList = Enum.GetValues(typeof(TypeComportement)).Cast<TypeComportement>().ToList();

            int[] minEtMaxParametres = FonctionsNatives.obtenirLimitesParametres(Enum.GetNames(typeof(typeParametre)).Length * 2);

            limitesParametres = new Parametre[Enum.GetNames(typeof(typeParametre)).Length];

            for (int i = 0; i < minEtMaxParametres.Length; i+= 2)
            {
                limitesParametres[i / 2].limiteMin = minEtMaxParametres[i];
                limitesParametres[i / 2].limiteMax = minEtMaxParametres[i + 1];
            }

            largeurZoneTextBoxes = new TextBox[] { longueurDangerGaucheTxtBox, longueurSecuritaireGaucheTxtBox, longueurDangerCentreTxtBox, longueurSecuritaireCentreTxtBox, longueurDangerDroitTxtBox, longueurSecuritaireDroitTxtBox };

            FonctionsNatives.setHandle((IntPtr)comboBoxProfil.Handle, Int32.Parse((String)comboBoxProfil.Tag));

            setUpAllControls(configureTabs);

            initialisation = true;

            assignerProfilsCB();

            initialisation = false;

            indexProfilDefaut = comboBoxProfil.FindString(nomProfilDefaut);

            foreach (Control tab in configureTabs.TabPages)
            {
                tab.Enabled = false;
            }
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void assignerProfilsCB(StringBuilder str)
        ///
        /// Cette fonction permet d'assigner un profil à la fenetre configure
        ///
        ////////////////////////////////////////////////////////////////////////
        private void assignerProfilsCB(){
            StringBuilder str = new StringBuilder(100);
            
            FonctionsNatives.obtenirCheminProfils(str, str.Capacity);
            cheminProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirExtensionProfils(str, str.Capacity);
            extensionProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirNomProfilDefaut(str, str.Capacity);

            nomProfilDefaut = str.ToString();

            comboBoxProfil.Items.Clear();
            fichiersProfil = new List<string>(System.IO.Directory.GetFiles(cheminProfils, "*" + extensionProfils));
            if (fichiersProfil.Count == 0)
            {
                FonctionsNatives.chargerProfilParDefaut();
                fichiersProfil.AddRange(System.IO.Directory.GetFiles(cheminProfils, "*" + extensionProfils));
                string nomFichier;
                for (int i = 0; i < fichiersProfil.Count; i++)
                {
                    nomFichier = System.IO.Path.GetFileName(fichiersProfil[i]);
                    fichiersProfil[i] = nomFichier.Substring(0, nomFichier.IndexOf('.'));
                }
                comboBoxProfil.Items.AddRange(fichiersProfil.ToArray());
                comboBoxProfil.SelectedIndex = comboBoxProfil.FindString(nomProfilDefaut);
            }
            else
            {
                string nomFichier;
                for (int i = 0; i < fichiersProfil.Count; i++)
                {
                    nomFichier = System.IO.Path.GetFileName(fichiersProfil[i]);
                    fichiersProfil[i] = nomFichier.Substring(0, nomFichier.IndexOf('.'));
                }

                comboBoxProfil.Items.AddRange(fichiersProfil.ToArray());
                FonctionsNatives.chargerProfilParDefaut();
                textBoxModeManuel.Text = afficherCaractere(textBoxModeManuel.Text[0]);
                textBoxAvancer.Text = afficherCaractere(textBoxAvancer.Text[0]);
                textBoxReculer.Text = afficherCaractere(textBoxReculer.Text[0]);
                textBoxHoraire.Text = afficherCaractere(textBoxHoraire.Text[0]);
                textBoxAntiHoraire.Text = afficherCaractere(textBoxAntiHoraire.Text[0]);
            }

            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void setUpAllControls(Control control)
        ///
        /// Cette fonction permet d'envoyer le handle de chaque composant au modele
        ///
        ////////////////////////////////////////////////////////////////////////
        void setUpAllControls(Control control)
        {
            foreach (Control item in control.Controls)
            {
                if (item.Tag != null)
                {
                    int indexControl = Int32.Parse(item.Tag.ToString().Split(';')[0]);
                    if (item.GetType().Equals(typeof(ComboBox)) && indexControl <= 23)
                    {
                        ComboBox combo = item as ComboBox;
                        combo.BindingContext = new BindingContext();
                        combo.DataSource = comportementsList;
                    }
                    FonctionsNatives.setHandle((IntPtr)item.Handle, indexControl);
                }

                setUpAllControls(item);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonDefConfig_Click(object sender, EventArgs e)
        ///
        /// Cette fonction charge le profil par défault
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du click
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void buttonDefConfig_Click(object sender, EventArgs e)
        {
            FonctionsNatives.chargerProfilParDefaut();
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
        /// Cette fonction vérifie si la touche est valide et assigner le comportement avancer
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
        /// Cette fonction vérifie si la touche est valide et assigner le comportement reculer
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
        /// Cette fonction vérifie si la touche est valide et assigner le comportement tourner gauche
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
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.ROTATION_DROITE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.ROTATION_DROITE);
            textBoxAntiHoraire.Text = afficherCaractere(caractere);
            textBoxAntiHoraire.Select(textBoxAntiHoraire.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxHoraire_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigner le comportement tourner droit
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
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.ROTATION_GAUCHE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.ROTATION_GAUCHE);
            textBoxHoraire.Text = afficherCaractere(caractere);
            textBoxHoraire.Select(textBoxHoraire.Text.Length, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Cette fonction vérifie si la touche est valide et assigner le comportement tourner droit
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

        private bool empecherTextChangedEvent = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEtDureeValidation(TextBox box, typeParametre parametre)
        ///
        /// Cette fonction permet de vérifier l'intégrité d'un angle ou d'une duree entré par un utilisateur
        ///
        /// @param[in] box: la text box modifiée par l'utilisateur
        /// @param[in] parametre: représente si c'est un angle ou une durée
        ///
        ///  
        ////////////////////////////////////////////////////////////////////////
        private void angleEtDureeValidation(TextBox box, typeParametre parametre)
        {
            double nombre;
            string nouvelleValeur = null;
            int indexParametre = (int)parametre;
            if (Double.TryParse(box.Text.Replace(',', '.'), System.Globalization.NumberStyles.Float, culture, out nombre) && BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(nombre))[3])[2] < 2)
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
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void largeurZoneValidation(TextBox box)
        {
            int indexTextBox = int.Parse(box.Tag.ToString().Split(';')[1]);
            int indexTextBoxComplementaire = indexTextBox % 2 == 0 ? indexTextBox + 1 : indexTextBox - 1;
            largeurZoneTextBoxes[indexTextBoxComplementaire].TextChanged -= largeurZoneTxtBox_TextChanged;
            TextBox boxComplementaire = largeurZoneTextBoxes[indexTextBoxComplementaire];
            double largeur1;
            double largeur2 = stringToDouble(boxComplementaire.Text);
            int indexParametre = (int)typeParametre.LARGEUR_ZONE;
            if (Double.TryParse(box.Text.Replace(',', '.'), System.Globalization.NumberStyles.Float, culture, out largeur1) && BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(largeur1))[3])[2] < 2)
            {
                if (largeur1 > limitesParametres[indexParametre].limiteMax)
                    box.Text = limitesParametres[indexParametre].limiteMax.ToString();
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
        /// @return: Aucun
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void parametresValidation(TextBox box, typeParametre parametre)
        {

            if (box.Text == "")
                box.Text = "0";
            else if(oldText == "0" && box.Text[1] != '0')
                box.Text = box.Text.Replace("0", "");
            else if (!decimalCheck(box))
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

            box.SelectionStart = oldCaretIndex + 2;
                
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
                if (box.Tag as Object[] == null)
                {
                    box.Tag = new Object[2] { box.Tag, 1 };
                    return true;
                }
            return false;
        }

        //String représentant l'ancienne valeur du textbox
        private string oldText;
        //Integer représentant l'ancienne position du caret
        private int oldCaretIndex;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleDGTxtBox_TextChanged(object sender, EventArgs e)
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
        /// @fn private void angleDDTxtBox_TextChanged(object sender, EventArgs e)
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
        /// @fn private void angleDDTxtBox_TextChanged(object sender, EventArgs e)
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
            if (initialisation)
                return;

            TextBox box = sender as TextBox;
            box.TextChanged -= largeurZoneTxtBox_TextChanged;
            parametresValidation(box, typeParametre.LARGEUR_ZONE);
            box.TextChanged += largeurZoneTxtBox_TextChanged;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleDGTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void parametreTxtBox_KeyDown(object sender, KeyEventArgs e)
        {

            oldText = (sender as TextBox).Text;
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
        /// Cette fonction selectionne l'index 1 des textbox de la fenetre
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
            changerProfil(nomProfil);
            textBoxModeManuel.Text = afficherCaractere(textBoxModeManuel.Text[0]);
            textBoxAvancer.Text = afficherCaractere(textBoxAvancer.Text[0]);
            textBoxReculer.Text = afficherCaractere(textBoxReculer.Text[0]);
            textBoxHoraire.Text = afficherCaractere(textBoxHoraire.Text[0]);
            textBoxAntiHoraire.Text = afficherCaractere(textBoxAntiHoraire.Text[0]);
        }

        public void changerProfil(string nomProfil){
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

        private actionProfil etatCreationProfil = actionProfil.ATTENTE_ACTION;

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
                ajouterProfilAMenu(nomSiDoublon);
                comboBoxProfil.SelectedIndex = comboBoxProfil.Items.Count - 1;
                comboBoxProfil.DropDownStyle = ComboBoxStyle.DropDownList;
                etatCreationProfil = actionProfil.ATTENTE_ACTION;
                modifierProfilButt.Enabled = true;
                buttonDeleteProfil.Enabled = true;
                retourMenuButt.Enabled = true;
            }
            
        }

        private void buttonDeleteProfil_Click(object sender, EventArgs e)
        {
            string profilASupprimer = comboBoxProfil.Text;
            if (profilASupprimer == nomProfilDefaut)
                return;
            FonctionsNatives.supprimerProfil(profilASupprimer + extensionProfils);
            comboBoxProfil.Items.Remove(profilASupprimer);
            comboBoxProfil.SelectedIndex = indexProfilDefaut;
        }

        private actionProfil etatModificationProfil = actionProfil.ATTENTE_ACTION;

        private void modifierProfilButt_Click(object sender, EventArgs e)
        {
            if (comboBoxProfil.SelectedIndex == indexProfilDefaut)
                return;

            bool tabEnabled;


            if (etatModificationProfil == actionProfil.ATTENTE_ACTION)
            {
                tabEnabled = true;
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
                
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, stringToDouble(angleEGTxtBox.Text), stringToDouble(dureeEGTxtBox.Text), TypeComportement.EVITEMENTPARLAGAUCHE);
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, stringToDouble(angleEDTxtBox.Text), stringToDouble(dureeEDTxtBox.Text), TypeComportement.EVITEMENTPARLADROITE);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistDroitCB.SelectedIndex == 0, (TypeComportement)zoneDangerDroitCB.SelectedValue, stringToDouble(longueurDangerDroitTxtBox.Text), (TypeComportement)zoneSecuritaireDroitCB.SelectedValue, stringToDouble(longueurSecuritaireDroitTxtBox.Text), 0);
                FonctionsNatives.assignerCapteurDistance(capteurDistCentreCB.SelectedIndex == 0, (TypeComportement)zoneDangerCentreCB.SelectedValue, stringToDouble(longueurDangerCentreTxtBox.Text), (TypeComportement)zoneSecuritaireCentreCB.SelectedValue, stringToDouble(longueurSecuritaireCentreTxtBox.Text), 1);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistGaucheCB.SelectedIndex == 0, (TypeComportement)zoneDangerGaucheCB.SelectedValue, stringToDouble(longueurDangerGaucheTxtBox.Text), (TypeComportement)zoneSecuritaireGaucheCB.SelectedValue, stringToDouble(longueurSecuritaireGaucheTxtBox.Text), 2);
                
                FonctionsNatives.assignerSuiveurLigne(suiveurLigneCB.SelectedIndex == 0);
                
                FonctionsNatives.assignerOptionsDebogages(optionsDebogagesCB.SelectedIndex == 0, comboBox_comportement.SelectedIndex == 0, comboBox_eclairage.SelectedIndex == 0, comboBox_capteur.SelectedIndex == 0);
                
                FonctionsNatives.sauvegarderProfil(comboBoxProfil.Text + extensionProfils);
                
                tabEnabled = false;
                modifierProfilButt.Text = "Modifier";
                etatModificationProfil = actionProfil.ATTENTE_ACTION;
                buttonCréerProfil.Enabled = true;
                buttonDeleteProfil.Enabled = true;
                retourMenuButt.Enabled = true;
                comboBoxProfil.Enabled = true;
            }

            foreach (Control tab in configureTabs.TabPages)
            {
                tab.Enabled = tabEnabled;

            }

            foreach (Control tab in capteursDistTabs.TabPages)
            {
                tab.Enabled = tabEnabled;
            }
        }

        private void optionsDebogagesCB_SelectionChangeCommitted(object sender, EventArgs e)
        {
            bool estActif = optionsDebogagesCB.SelectedIndex == 0;
            comboBox_comportement.Enabled = estActif;
            comboBox_eclairage.Enabled = estActif;
            comboBox_capteur.Enabled = estActif;
        }

        private void button_Default_Click(object sender, EventArgs e)
        {
            FonctionsNatives.modifierToucheCommande('W', TypeCommande.AVANCER);
            textBoxAvancer.Text = "W";
            FonctionsNatives.modifierToucheCommande('S', TypeCommande.RECULER);
            textBoxReculer.Text = "S";
            FonctionsNatives.modifierToucheCommande('A', TypeCommande.ROTATION_GAUCHE);
            textBoxAntiHoraire.Text = "D";
            FonctionsNatives.modifierToucheCommande('D', TypeCommande.ROTATION_DROITE);
            textBoxHoraire.Text = "A";
            FonctionsNatives.modifierToucheCommande(' ', TypeCommande.INVERSER_MODE_CONTROLE);
            textBoxModeManuel.Text = "ESPACE";
        }


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

        //[DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void [MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VT_I4)]

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
        public static extern void obtenirNomProfilDefaut(StringBuilder str, int longueur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerProfilParDefaut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern char obtenirToucheCommande(TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setHandle(IntPtr handle, int ctrl);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirExtensionProfils(StringBuilder str, int longueur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirCheminProfils(StringBuilder str, int longueur);

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


