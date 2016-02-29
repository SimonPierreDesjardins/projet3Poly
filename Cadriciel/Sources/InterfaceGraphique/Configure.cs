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

        public Configure()
        {
            InitializeComponent();
            List<TypeComportement> comportementsList = Enum.GetValues(typeof(TypeComportement)).Cast<TypeComportement>().ToList();

            suiviLigneCB.DataSource = comportementsList;

            balayageCB.BindingContext = new BindingContext();
            balayageCB.DataSource = comportementsList;

            deviationGCB.BindingContext = new BindingContext();
            deviationGCB.DataSource = comportementsList;

            deviationDCB.BindingContext = new BindingContext();
            deviationDCB.DataSource = comportementsList;

            evitementGCB.BindingContext = new BindingContext();
            evitementGCB.DataSource = comportementsList;

            evitementDCB.BindingContext = new BindingContext();
            evitementDCB.DataSource = comportementsList;

            capteurDistanceDangerCB.BindingContext = new BindingContext();
            capteurDistanceDangerCB.DataSource = comportementsList;

            capteurDistanceSecuritaireCB.BindingContext = new BindingContext();
            capteurDistanceSecuritaireCB.DataSource = comportementsList;
        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {

        }

        private void buttonDefConfig_Click(object sender, EventArgs e)
        {
            textBoxAvancer.Text = "W";
            textBoxReculer.Text = "S";
            textBoxHoraire.Text = "A";
            textBoxAntiHoraire.Text = "D";
            textBoxModeManuel.Text = "Espace";
        }

        private bool caractereInvalide(object sender, KeyPressEventArgs e)
        { return e.Handled = !(char.IsLetter(e.KeyChar) || e.KeyChar == (char)Keys.Back); }

        private void textBoxAvancer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e)) 
                textBoxAvancer.Text = e.KeyChar.ToString();
                
            

            textBoxAvancer.Select(textBoxAvancer.Text.Length, 0);    
        }

        private void textBoxReculer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
                textBoxReculer.Text = e.KeyChar.ToString();
            

            textBoxReculer.Select(textBoxReculer.Text.Length, 0);
        }

        private void textBoxAntiHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
                textBoxAntiHoraire.Text = e.KeyChar.ToString();
            

            textBoxAntiHoraire.Select(textBoxAntiHoraire.Text.Length, 0);
        }

        private void textBoxHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
                textBoxHoraire.Text = e.KeyChar.ToString();
            

            textBoxHoraire.Select(textBoxHoraire.Text.Length, 0);
        }

        private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
                textBoxModeManuel.Text = e.KeyChar.ToString();
            

            textBoxModeManuel.Select(textBoxModeManuel.Text.Length, 0);
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

        private void buttonDeleteProfil_Click(object sender, EventArgs e)
        {
            if (comboBoxProfil.SelectedIndex == -1)
            {}
            else if (comboBoxProfil.SelectedIndex != 0)
            {
                comboBoxProfil.Items.RemoveAt(comboBoxProfil.SelectedIndex);
            }
        }

        private void Configure_Load(object sender, EventArgs e)
        {
            //comboBoxProfil.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxProfil.SelectedIndex = 0;
        }

        private void textBoxAvancer_KeyDown(object sender, KeyEventArgs e)
        {

        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox4_CheckedChanged_1(object sender, EventArgs e)
        {

        }

        private void checkBox6_CheckedChanged_1(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void buttonFinConfig_Click(object sender, EventArgs e)
        {

        }

        private void tabPage2_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label15_Click(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label20_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click_1(object sender, EventArgs e)
        {

        }

        private void parametresLbl_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click_1(object sender, EventArgs e)
        {

        }

        private void capteurDistanceProchComportementSecuritaireLbl_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click_2(object sender, EventArgs e)
        {

        }

        private void capteurDistanceOptionsPnl_Paint(object sender, PaintEventArgs e)
        {

        }

        private void groupBox1_Enter_1(object sender, EventArgs e)
        {

        }

        private void capteurDistanceChkBox_CheckedChanged(object sender, EventArgs e)
        {
            capteurDistanceOptionsPnl.Enabled = capteurDistanceChkBox.Checked;
        }

        private void buttonSaveProfil_Click_1(object sender, EventArgs e)
        {
            FonctionsNatives.assignerComportementSuivreLigne((TypeComportement)suiviLigneCB.SelectedValue);
            FonctionsNatives.assignerComportementBalayage((TypeComportement)balayageCB.SelectedValue);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationGCB.SelectedValue, Convert.ToDouble(angleDeviationGNumBox.Value), TypeComportement.DEVIATIONVERSLAGAUCHE);
            FonctionsNatives.assignerComportementDeviation((TypeComportement)deviationDCB.SelectedValue, Convert.ToDouble(angleDeviationDNumBox.Value), TypeComportement.DEVIATIONVERSLADROITE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementGCB.SelectedValue, Convert.ToDouble(angleEvitementGNumBox.Value), Convert.ToDouble(dureeEvitementGNumBox.Value), TypeComportement.EVITEMENTPARLAGAUCHE);
            FonctionsNatives.assignerComportementEvitement((TypeComportement)evitementDCB.SelectedValue, Convert.ToDouble(angleEvitementDNumBox.Value), Convert.ToDouble(dureeEvitementDNumBox.Value), TypeComportement.EVITEMENTPARLADROITE);
            
            FonctionsNatives.modifierToucheCommande(textBoxAvancer.Text[0], TypeCommande.AVANCER);
            FonctionsNatives.modifierToucheCommande(textBoxReculer.Text[0], TypeCommande.RECULER);
            FonctionsNatives.modifierToucheCommande(textBoxAntiHoraire.Text[0], TypeCommande.ROTATION_DROITE);
            FonctionsNatives.modifierToucheCommande(textBoxHoraire.Text[0], TypeCommande.ROTATION_GAUCHE);
            FonctionsNatives.modifierToucheCommande(textBoxModeManuel.Text[0], TypeCommande.INVERSER_MODE_CONTROLE);
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

    }
}


