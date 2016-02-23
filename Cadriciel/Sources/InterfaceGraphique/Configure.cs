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

namespace InterfaceGraphique
{
    public partial class Configure : Form
    {
        public Configure()
        {
            InitializeComponent();
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
            FonctionsNatives.chargerProfilParDefaut();
        }

        private bool caractereInvalide(object sender, KeyPressEventArgs e)
        { return e.Handled = !(char.IsLetter(e.KeyChar) || e.KeyChar == (char)Keys.Back); }

        private void textBoxAvancer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                textBoxAvancer.Text = e.KeyChar.ToString();
                FonctionsNatives.modifierToucheCommande(e.KeyChar, TypeCommande.AVANCER);
            }
                

            textBoxAvancer.Select(textBoxAvancer.Text.Length, 0);
        }

        private void textBoxReculer_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                textBoxReculer.Text = e.KeyChar.ToString().ToUpper();
                FonctionsNatives.modifierToucheCommande(Char.ToUpper(e.KeyChar), TypeCommande.RECULER);
            }
                

            textBoxReculer.Select(textBoxReculer.Text.Length, 0);
        }

        private void textBoxAntiHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                textBoxAntiHoraire.Text = e.KeyChar.ToString();
                FonctionsNatives.modifierToucheCommande(e.KeyChar, TypeCommande.ROTATION_DROITE);
            }
                

            textBoxAntiHoraire.Select(textBoxAntiHoraire.Text.Length, 0);
        }

        private void textBoxHoraire_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                textBoxHoraire.Text = e.KeyChar.ToString();
                FonctionsNatives.modifierToucheCommande(e.KeyChar, TypeCommande.ROTATION_GAUCHE);
            }
                

            textBoxHoraire.Select(textBoxHoraire.Text.Length, 0);
        }

        private void textBoxModeManuel_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!caractereInvalide(sender, e))
            {
                textBoxModeManuel.Text = e.KeyChar.ToString();
                FonctionsNatives.modifierToucheCommande(e.KeyChar, TypeCommande.INVERSER_MODE_CONTROLE);
            }
                
            textBoxModeManuel.Select(textBoxModeManuel.Text.Length, 0);
        }

        private void buttonDefProfil_Click(object sender, EventArgs e)
        {
            
            checkBox1.Checked = false;
            checkBox2.Checked = false;
            checkBox3.Checked = false;
            checkBox4.Checked = false;
            checkBox5.Checked = false;
            checkBox6.Checked = false;
            checkBox7.Checked = false;
            checkBox8.Checked = false;
            checkBox9.Checked = false;
            checkBox10.Checked = false;
            checkBox11.Checked = false;
        }

        private void buttonSaveProfil_Click(object sender, EventArgs e)
        {
            bool[] options = new bool[11];
            options[0] = checkBox1.Checked;
            options[1] = checkBox2.Checked;
            options[2] = checkBox3.Checked;
            options[3] = checkBox4.Checked;
            options[4] = checkBox5.Checked;
            options[5] = checkBox6.Checked;
            options[6] = checkBox7.Checked;
            options[7] = checkBox8.Checked;
            options[8] = checkBox9.Checked;
            options[9] = checkBox10.Checked;
            options[10] = checkBox11.Checked;
            FonctionsNatives.assignerOptionsProfil(options);
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
    }

    enum TypeCommande
    {
	    INVERSER_MODE_CONTROLE,
	    AVANCER,
	    RECULER,
	    ROTATION_GAUCHE,
	    ROTATION_DROITE
    };

    static partial class FonctionsNatives{
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerOptionsProfil([MarshalAs(UnmanagedType.LPArray, SizeConst = 11)] bool[] options);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modifierToucheCommande(char touche, TypeCommande commande);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerProfilParDefaut();
    }
}


