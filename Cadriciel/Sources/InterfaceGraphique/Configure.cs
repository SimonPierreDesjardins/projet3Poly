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

        System.Globalization.CultureInfo culture = new System.Globalization.CultureInfo("en");
        
        private List<TypeComportement> comportementsList;

        private string cheminProfils;
        private string extensionProfils;
        private string nomProfilDefaut;
        private int indexProfilDefaut;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Configure()
        ///
        /// Cette fonction initialize la fenetre et initialise la visibilité de
        /// ses composantes
        ///
        ////////////////////////////////////////////////////////////////////////
        public Configure()
        {
            InitializeComponent();

            comportementsList = Enum.GetValues(typeof(TypeComportement)).Cast<TypeComportement>().ToList();

            FonctionsNatives.setHandle((IntPtr)comboBoxProfil.Handle, Int32.Parse((String)comboBoxProfil.Tag));

            setUpAllControls(configureTabs);

            StringBuilder str = new StringBuilder(100);

            assignerProfilsCB(str);

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
        private void assignerProfilsCB(StringBuilder str){
            
            FonctionsNatives.obtenirCheminProfils(str, str.Capacity);
            cheminProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirExtensionProfils(str, str.Capacity);
            extensionProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirNomProfilDefaut(str, str.Capacity);

            nomProfilDefaut = str.ToString();

            comboBoxProfil.Items.Clear();

            string[] fichiersProfile = System.IO.Directory.GetFiles(cheminProfils, "*" + extensionProfils);
            if (fichiersProfile.Length == 0)
            {
                FonctionsNatives.chargerProfilParDefaut();
                fichiersProfile = System.IO.Directory.GetFiles(cheminProfils, "*" + extensionProfils);
                string nomFichier;
                for (int i = 0; i < fichiersProfile.Length; i++)
                {
                    nomFichier = System.IO.Path.GetFileName(fichiersProfile[i]);
                    fichiersProfile[i] = nomFichier.Substring(0, nomFichier.IndexOf('.'));
                }
                comboBoxProfil.Items.AddRange(fichiersProfile);
                comboBoxProfil.SelectedIndex = comboBoxProfil.FindString(nomProfilDefaut);
            }
            else
            {
                string nomFichier;
                for (int i = 0; i < fichiersProfile.Length; i++)
                {
                    nomFichier = System.IO.Path.GetFileName(fichiersProfile[i]);
                    fichiersProfile[i] = nomFichier.Substring(0, nomFichier.IndexOf('.'));
                }

                comboBoxProfil.Items.AddRange(fichiersProfile);
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
                    if (item.GetType().Equals(typeof(ComboBox)) && Int32.Parse((String)item.Tag) <= 23)
                    {
                        ComboBox combo = item as ComboBox;
                        combo.BindingContext = new BindingContext();
                        combo.DataSource = comportementsList;
                    }
                    FonctionsNatives.setHandle((IntPtr)item.Handle, Int32.Parse((String)item.Tag));
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
        /// @fn private bool degreeValidation(string aTester)
        ///
        /// Cette fonction permet de valider un degree ou il n'y a que deux chiffres apres
        /// la virgule et que le nombre est entre 0 et 360
        ///
        /// @param[in] string aTester: la string représentant un degree
        ///
        /// @return bool: true si valide sinon false
        /// 
        ////////////////////////////////////////////////////////////////////////
        private bool degreeValidation(string aTester)
        {
            double nombre;
            bool reussi;
            reussi = Double.TryParse(aTester.Replace(',', '.'), System.Globalization.NumberStyles.Float, culture, out nombre);
            if (reussi)
                if (nombre < 0.00 || nombre > 360.00 || BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(nombre))[3])[2] > 2)
                    reussi = false;

            return reussi;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool tempsValidation(string aTester)
        ///
        /// Cette fonction permet de valider un temps ou il n'y a que deux chiffres apres
        /// la virgule
        ///
        /// @param[in] string aTester: la string représentant un temps
        ///
        /// @return bool: true si valide sinon false
        /// 
        ////////////////////////////////////////////////////////////////////////
        private bool tempsValidation(string aTester)
        {
            double nombre;
            bool reussi;
            reussi = Double.TryParse(aTester.Replace('.', ','), out nombre);
            if (reussi)
                if (BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(nombre))[3])[2] > 2)
                    reussi = false;

            return reussi;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEtDureeValidation(TextBox box, bool estDegree)
        ///
        /// Cette fonction permet de valider un temps et un angle. S'il n'est pas valide,
        /// l'ancien text est affiché
        ///
        /// @param[in] TextBox box: la textbox a vérifier
        /// @param[in] bool estDegree: la validité d'un angle
        ///
        /// @return: Aucun
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleEtDureeValidation(TextBox box, bool estDegree)
        {
            if (empecherTextChangedEvent)
                return;

            empecherTextChangedEvent = true;

            if (box.Text == "")
                box.Text = "0";
            else if(!decimalCheck(box))
                if (estDegree ? !degreeValidation(box.Text) : !tempsValidation(box.Text))
                    box.Text = oldText;

            empecherTextChangedEvent = false;
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
        private void angleDGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
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
        private void angleDGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
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
        private void angleDDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleDDTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleDDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEGTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleEGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dureeEGTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void dureeEGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dureeEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void dureeEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEDTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleEDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void angleEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void angleEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dureeEDTxtBox_TextChanged(object sender, EventArgs e)
        ///
        /// Cette fonction vérifie si l'entrer est valide. Change le text si valide sinon
        /// remet l'ancient text
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void dureeEDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dureeEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Cette fonction prend la valeur du text avant un key down et l'assigne au oldText
        ///
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventArgs e: evenement d'un touche du clavier
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void dureeEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void longueurZoneDangerCapteurDistanceTB_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
            // TODO: VERIFIER PERTINENCE DU CODE CI-DESSOUS
            /*FonctionsNatives.assignerComportementSuivreLigne((TypeComportement)suiviLigneCB.SelectedValue);
            FonctionsNatives.assignerComportementBalayage((TypeComportement)balayageCB.SelectedValue);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, Convert.ToDouble(angleDGTxtBox.Text.Replace('.',',')), TypeComportement.DEVIATIONVERSLAGAUCHE);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, Convert.ToDouble(angleDDTxtBox.Text.Replace('.', ',')), TypeComportement.DEVIATIONVERSLADROITE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, Convert.ToDouble(angleEGTxtBox.Text.Replace('.', ',')), Convert.ToDouble(dureeEGTxtBox.Text.Replace('.', ',')), TypeComportement.EVITEMENTPARLAGAUCHE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, Convert.ToDouble(angleEDTxtBox.Text.Replace('.', ',')), Convert.ToDouble(dureeEDTxtBox.Text.Replace('.', ',')), TypeComportement.EVITEMENTPARLADROITE);
            */
            // TODO: VALIDE?
            this.DialogResult = DialogResult.OK;
            Close();
        }

        private void longueurZoneDangerCapteurDistanceTB_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void longueurZoneSecuritaireCapteurDistanceTB_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
        }

        private void longueurZoneSecuritaireCapteurDistanceTB_KeyDown(object sender, KeyEventArgs e)
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
            FonctionsNatives.changerProfil(nomProfil + extensionProfils);
            textBoxModeManuel.Text = afficherCaractere(textBoxModeManuel.Text[0]);
            textBoxAvancer.Text = afficherCaractere(textBoxAvancer.Text[0]);
            textBoxReculer.Text = afficherCaractere(textBoxReculer.Text[0]);
            textBoxHoraire.Text = afficherCaractere(textBoxHoraire.Text[0]);
            textBoxAntiHoraire.Text = afficherCaractere(textBoxAntiHoraire.Text[0]);
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
                
                
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, Double.Parse(angleDGTxtBox.Text.Replace(',', '.'), culture), TypeComportement.DEVIATIONVERSLAGAUCHE);
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, Double.Parse(angleDDTxtBox.Text.Replace(',', '.'), culture), TypeComportement.DEVIATIONVERSLADROITE);
                
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, Double.Parse(angleEGTxtBox.Text.Replace(',', '.'), culture), Double.Parse(dureeEGTxtBox.Text.Replace(',', '.'), culture), TypeComportement.EVITEMENTPARLAGAUCHE);
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, Double.Parse(angleEDTxtBox.Text.Replace(',', '.'), culture), Double.Parse(dureeEDTxtBox.Text.Replace(',', '.'), culture), TypeComportement.EVITEMENTPARLADROITE);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistDroitCB.SelectedIndex == 0, (TypeComportement)zoneDangerDroitCB.SelectedValue, Double.Parse(longueurDangerDroitTxtBox.Text.Replace(',', '.'), culture), (TypeComportement)zoneSecuritaireDroitCB.SelectedValue, Double.Parse(longueurSecuritaireDroitTxtBox.Text.Replace(',', '.'), culture), 0);
                FonctionsNatives.assignerCapteurDistance(capteurDistCentreCB.SelectedIndex == 0, (TypeComportement)zoneDangerCentreCB.SelectedValue, Double.Parse(longueurDangerCentreTxtBox.Text.Replace(',', '.'), culture), (TypeComportement)zoneSecuritaireCentreCB.SelectedValue, Double.Parse(longueurSecuritaireCentreTxtBox.Text.Replace(',', '.'), culture), 1);
                
                FonctionsNatives.assignerCapteurDistance(capteurDistGaucheCB.SelectedIndex == 0, (TypeComportement)zoneDangerGaucheCB.SelectedValue, Double.Parse(longueurDangerGaucheTxtBox.Text.Replace(',', '.'), culture), (TypeComportement)zoneSecuritaireGaucheCB.SelectedValue, Double.Parse(longueurSecuritaireGaucheTxtBox.Text.Replace(',', '.'), culture), 2);
                
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
        public static extern void obtenirNomProfilDefaut(StringBuilder str, int longueur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerProfilParDefaut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern char obtenirToucheCommande(TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setHandle(IntPtr handle, int ctrl);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerProfil(string nomProfil);

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAffichageComportement(bool afficherDebugComportement);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAffichageEclairage(bool afficherDebugEclairage);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAffichageCapteurs(bool afficherDebugCapteurs);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirExtensionProfils(StringBuilder str, int longueur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirCheminProfils(StringBuilder str, int longueur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerProfil(string nomProfil);

    }
}


