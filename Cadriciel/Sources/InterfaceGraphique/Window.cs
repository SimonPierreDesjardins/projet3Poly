using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace InterfaceGraphique
{
    public partial class Window : Form
    {

        public Window()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            InitializeComponent();
            InitialiserAnimation();
        }

        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(viewPort_.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                });
            }
            catch (Exception)
            {
            }
            
        }

        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {

            //Voir https://msdn.microsoft.com/fr-fr/library/system.windows.forms.keys%28v=vs.110%29.aspx

            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée.");
            }
        }
       

        private void Window_Load(object sender, EventArgs e)
        {

        }

        private void Window_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock(Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }


        private void quitterToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buttonSimulation_Click(object sender, EventArgs e)
        {

        }

        private void buttonEditeur_Click(object sender, EventArgs e)
        {

        }

        private void buttonConfiguration_Click(object sender, EventArgs e)
        {

        }

        private void buttonQuitter_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("Êtes-vous sûr de vouloir quitter l'application?",
            "Simulation de robot",
            MessageBoxButtons.YesNo,
            MessageBoxIcon.Question,
            MessageBoxDefaultButton.Button1);

            if (result == DialogResult.Yes)
            {
                Application.Exit();
            }
        }

        private void viewPort__Paint(object sender, PaintEventArgs e)
        {

        }


    }

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);
    }
}
