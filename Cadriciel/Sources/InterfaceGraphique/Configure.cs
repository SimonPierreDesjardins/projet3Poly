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
using ConfigureControlEnum;

namespace InterfaceGraphique
{
    public partial class Configure : Form
    {

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        static extern bool HideCaret(IntPtr hWnd);
        private List<TypeComportement> comportementsList;

        private string cheminProfils;
        private string extensionProfils;
        private string nomProfilDefaut;
        private int indexProfilDefaut;

        bool afficherDebugComportement = false;
        bool afficherDebugEclairage = false;
        bool afficherDebugCapteurs = false;

        public Configure()
        {
            InitializeComponent();
        }

        private void assignerProfilsCB(StringBuilder str){
            
            FonctionsNatives.obtenirCheminProfils(str, str.Capacity);
            cheminProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirExtensionProfils(str, str.Capacity);
            extensionProfils = str.ToString();

            str.Clear();

            FonctionsNatives.obtenirNomProfilDefaut(str, str.Capacity);

            nomProfilDefaut = str.ToString();

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

        void setUpAllControls(Control control)
        {
            foreach (Control item in control.Controls)
            {
                if (item.Tag != null)
                {
                    if (item.GetType().Equals(typeof(ComboBox)) && Int32.Parse((String)item.Tag) <= 20)
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

        private void buttonDefConfig_Click(object sender, EventArgs e)
        {
            FonctionsNatives.chargerProfilParDefaut();
        }

        private bool caractereInvalide(object sender, KeyPressEventArgs e)
        { return e.Handled = !(/*char.IsLetterOrDigit(e.KeyChar)*/true); }

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

        private void Configure_Load(object sender, EventArgs e)
        {
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

        private bool empecherTextChangedEvent = false;

        private void modeManuelValidation(TextBox textBox, char key)
        {
            if (empecherTextChangedEvent)
                return;
            empecherTextChangedEvent = true;
            textBox.Text = afficherCaractere(key);
            empecherTextChangedEvent = false;
        }
        
        private bool degreeValidation(string aTester)
        {
            double nombre;
            bool reussi;
            reussi = Double.TryParse(aTester.Replace('.', ','), out nombre);
            if (reussi)
                if (nombre < 0.00 || nombre > 360.00 || BitConverter.GetBytes(decimal.GetBits(Convert.ToDecimal(nombre))[3])[2] > 2)
                    reussi = false;

            return reussi;
        }

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

        private string oldText;

        private void angleDGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        private void angleDGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void angleDDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        private void angleDDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void angleEGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        private void angleEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void dureeEGTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
        }

        private void dureeEGTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void angleEDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, true);
        }

        private void angleEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void dureeEDTxtBox_TextChanged(object sender, EventArgs e)
        {
            angleEtDureeValidation(sender as TextBox, false);
        }

        private void dureeEDTxtBox_KeyDown(object sender, KeyEventArgs e)
        {
            oldText = (sender as TextBox).Text;
        }

        private void retourMenuButt_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            Close();
        }

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

        private void OptionAffichage_CheckedChanged(object sender, EventArgs e)
        {
            enableOptionAffichage();
            setBooleanAffichageComportement();
            setBooleanAffichageEclairage();
            setBooleanAffichageCapteurs();
        }

        private void enableOptionAffichage()
        {
            if (OptionAffichage.Checked)
            {
                comboBox_capteur.Enabled = true;
                comboBox_comportement.Enabled = true;
                comboBox_eclairage.Enabled = true;
            }
            else
            {
                comboBox_capteur.Enabled = false;
                comboBox_comportement.Enabled = false;
                comboBox_eclairage.Enabled = false;
            }
        }

        private void comboBox_comportement_SelectedIndexChanged(object sender, EventArgs e)
        {
            setBooleanAffichageComportement();
        }

        private void setBooleanAffichageComportement()
        {
            if (comboBox_comportement.Enabled)
            {
                if (comboBox_comportement.SelectedIndex == 0)
                    afficherDebugComportement = true;
            }
            else
                afficherDebugComportement = false;
        }

        private void comboBox_eclairage_SelectedIndexChanged(object sender, EventArgs e)
        {
            setBooleanAffichageEclairage();
        }

        private void setBooleanAffichageEclairage()
        {
            if (comboBox_eclairage.Enabled)
            {
                if (comboBox_eclairage.SelectedIndex == 0)
                    afficherDebugEclairage = true;
            }
            else
                afficherDebugEclairage = false;
        }

        private void comboBox_capteur_SelectedIndexChanged(object sender, EventArgs e)
        {
            setBooleanAffichageCapteurs();
        }

        private void setBooleanAffichageCapteurs()
        {
            if (comboBox_capteur.Enabled)
            {
                if (comboBox_capteur.SelectedIndex == 0)
                    afficherDebugCapteurs = true;
            }
            else
                afficherDebugCapteurs = false;
        }

        private void textBoxModeManuel_TextChanged(object sender, EventArgs e)
        {
            Console.Write("allo");
        }

        private enum creationProfil
        {
            ATTENTE_CREATION,
            ATTENTE_CONFIRMATION
        }

        private creationProfil etatCreationProfil = creationProfil.ATTENTE_CREATION;

        private void buttonCréerProfil_Click(object sender, EventArgs e)
        {
            if (etatCreationProfil == creationProfil.ATTENTE_CREATION)
            {
                comboBoxProfil.DropDownStyle = ComboBoxStyle.DropDown;
                comboBoxProfil.Focus();
                buttonCréerProfil.Text = "Confirmer création";
                etatCreationProfil = creationProfil.ATTENTE_CONFIRMATION;
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
                etatCreationProfil = creationProfil.ATTENTE_CREATION;
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

        private enum modificationProfil
        {
            ATTENTE_MODIFICATION,
            ATTENTE_CONFIRMATION
        }

        private modificationProfil etatModificationProfil = modificationProfil.ATTENTE_MODIFICATION;

        private void modifierProfilButt_Click(object sender, EventArgs e)
        {
            if (comboBoxProfil.SelectedIndex == indexProfilDefaut)
                return;

            bool tabEnabled;
            

            if (etatModificationProfil == modificationProfil.ATTENTE_MODIFICATION)
            {
                tabEnabled = true;
                modifierProfilButt.Text = "Enregistrer";
                etatModificationProfil = modificationProfil.ATTENTE_CONFIRMATION;
            }
            else
            {
                FonctionsNatives.assignerComportementSuivreLigne((TypeComportement)suiviLigneCB.SelectedValue);
                FonctionsNatives.assignerComportementBalayage((TypeComportement)balayageCB.SelectedValue);
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, Convert.ToDouble(angleDGTxtBox.Text.Replace('.', ',')), TypeComportement.DEVIATIONVERSLAGAUCHE);
                FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, Convert.ToDouble(angleDDTxtBox.Text.Replace('.', ',')), TypeComportement.DEVIATIONVERSLADROITE);
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, Convert.ToDouble(angleEGTxtBox.Text.Replace('.', ',')), Convert.ToDouble(dureeEGTxtBox.Text.Replace('.', ',')), TypeComportement.EVITEMENTPARLAGAUCHE);
                FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, Convert.ToDouble(angleEDTxtBox.Text.Replace('.', ',')), Convert.ToDouble(dureeEDTxtBox.Text.Replace('.', ',')), TypeComportement.EVITEMENTPARLADROITE);
                FonctionsNatives.sauvegarderProfil(comboBoxProfil.Text + extensionProfils);
                tabEnabled = false;
                modifierProfilButt.Text = "Modifier";
                etatModificationProfil = modificationProfil.ATTENTE_MODIFICATION;
            }

            foreach (Control tab in configureTabs.TabPages)
            {
                tab.Enabled = tabEnabled;
            }
        }

    }

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

        //[DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void assignerCapteurDistance(int indexCapteur, bool estActif, );

        //[DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void assignerComportementEvitement(TypeComportement comportementSuivant, double angle, double duree, TypeComportement typeEvitement);

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


