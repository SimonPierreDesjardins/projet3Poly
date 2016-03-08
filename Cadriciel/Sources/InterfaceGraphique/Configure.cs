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
        System.Text.RegularExpressions.Regex regex;

        public Configure()
        {
            InitializeComponent();

            comportementsList = Enum.GetValues(typeof(TypeComportement)).Cast<TypeComportement>().ToList();

            FonctionsNatives.setHandle((IntPtr)comboBoxProfil.Handle, Int32.Parse((String)comboBoxProfil.Tag));

            FonctionsNatives.assignerProfils();

            setUpAllControls(configureTabs);

            FonctionsNatives.chargerProfilParDefaut();

        }

        void setUpAllControls(Control control)
        {
            foreach (Control item in control.Controls)
            {
                if (item.Tag != null)
                {
                    if (item.GetType().Equals(typeof(ComboBox)))
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
            textBoxAvancer.Text = "W";
            textBoxReculer.Text = "S";
            textBoxHoraire.Text = "A";
            textBoxAntiHoraire.Text = "D";
            textBoxModeManuel.Text = "Espace";
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

        private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        {
            
            if (!caractereInvalide(sender, e))
            {
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.INVERSER_MODE_CONTROLE);
            }
            char caractere = FonctionsNatives.obtenirToucheCommande(TypeCommande.INVERSER_MODE_CONTROLE);
            textBoxModeManuel.Text = afficherCaractere(caractere);    
            textBoxModeManuel.Select(textBoxModeManuel.Text.Length, 0);
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

        private void buttonDefProfil_Click(object sender, EventArgs e)
        {
            capteurDistanceChkBox.Checked = false;
            capteurLigneChkBox.Checked = false;
        }

        private void buttonSaveProfil_Click(object sender, EventArgs e)
        {
            comboBoxProfil.Items.Insert(comboBoxProfil.Items.Count, comboBoxProfil.Text);
        }

        private void Configure_Load(object sender, EventArgs e)
        {
            comboBoxProfil.SelectedIndex = 0;
        }

        private void capteurDistanceChkBox_CheckedChanged(object sender, EventArgs e)
        {
            capteurDistanceOptionsPnl.Enabled = capteurDistanceChkBox.Checked;
        }

        private void buttonSaveProfil_Click_1(object sender, EventArgs e)
        {
            FonctionsNatives.assignerComportementSuivreLigne((TypeComportement)suiviLigneCB.SelectedValue);
            FonctionsNatives.assignerComportementBalayage((TypeComportement)balayageCB.SelectedValue);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, Convert.ToDouble(angleDGTxtBox.Text), TypeComportement.DEVIATIONVERSLAGAUCHE);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, Convert.ToDouble(angleDDTxtBox.Text), TypeComportement.DEVIATIONVERSLADROITE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, Convert.ToDouble(angleEGTxtBox.Text), Convert.ToDouble(dureeEGTxtBox.Text), TypeComportement.EVITEMENTPARLAGAUCHE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, Convert.ToDouble(angleEDTxtBox.Text), Convert.ToDouble(dureeEDTxtBox.Text), TypeComportement.EVITEMENTPARLADROITE);
        }

        private bool empecherTextChangedEvent = false;

        private void textBoxModeManuel_TextChanged(object sender, EventArgs e)
        {
            if (empecherTextChangedEvent)
                return;
            empecherTextChangedEvent = true;
            TextBox textBox = sender as TextBox;
            textBox.Text = afficherCaractere(textBox.Text[0]);
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
        public static extern void modifierToucheCommande(char touche, TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerProfilParDefaut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern char obtenirToucheCommande(TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setHandle(IntPtr handle, int ctrl);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerProfils();

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);
    }
}


