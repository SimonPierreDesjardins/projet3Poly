﻿using System;
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
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            switch (keyData)
            {
                case Keys.Space:
                    System.Console.WriteLine("Barre d'espacement appuyée.");
                    break;

                case Keys.Up:
                    System.Console.WriteLine("La fleche du haut est appuyée.");
                    break;

                case Keys.Down:
                    System.Console.WriteLine("La fleche du bas est appuyée.");
                    break;

                case Keys.Left:
                    System.Console.WriteLine("La fleche de gauche est appuyée.");
                    break;

                case Keys.Right:
                    System.Console.WriteLine("la fleche de droite est appuyée.");
                    break;

                case Keys.Tab:
                    System.Console.WriteLine("Le boutton tab est appuyé.");
                    break;

                case Keys.Back:
                    System.Console.WriteLine("La touche de retour appuyée.");
                    break;

                case Keys.ControlKey:
                    System.Console.WriteLine("La touche CTRL est appuyée.");
                    break;

                case Keys.XButton1:
                    System.Console.WriteLine("Click gauche de la souris est appuyé.");
                    break;

                case Keys.XButton2:
                    System.Console.WriteLine("Click droit de la souris est appuyé.");
                    break;

                default:
                    break;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        public Window()
        {
            //this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
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

        /*private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            //Voir https://msdn.microsoft.com/fr-fr/library/system.windows.forms.keys%28v=vs.110%29.aspx

            switch(e.KeyChar)
            {
                case (char)Keys.Space:
                    System.Console.WriteLine("Barre d'espacement appuyée.");
                    break;
            }

        }*/
       

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
            afficherMenuPrincipal(false);
            menuEdition_.Visible = true;
            
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

        private void afficherMenuPrincipal(bool afficherMenu)
        {
            bouttonConfiguration_.Visible = afficherMenu;
            bouttonEditeur_.Visible = afficherMenu;
            bouttonQuitter_.Visible = afficherMenu;
            bouttonSimulation_.Visible = afficherMenu;
            viewPort_.Visible = !afficherMenu;
        }

        private void viewPort_Paint(object sender, PaintEventArgs e)
        {

        }

        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void menuPrincipalMenuEdition__Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(true);
            menuEdition_.Visible = false;
        }

        private void viewPort__VisibleChanged(object sender, EventArgs e)
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
