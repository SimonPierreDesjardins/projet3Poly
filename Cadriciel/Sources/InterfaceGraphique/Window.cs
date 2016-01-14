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
            
            switch(e.KeyChar)
            {
                case (char)Keys.Space:
                    System.Console.WriteLine("Barre d'espacement appuyée.");
                    break;

                case (char)Keys.Up:
                    System.Console.WriteLine("La fleche du haut est appuyée.");
                    break;

                case (char)Keys.Down:
                    System.Console.WriteLine("La fleche du bas est appuyée.");
                    break;

                case (char)Keys.Left:
                    System.Console.WriteLine("La fleche de gauche est appuyée.");
                    break;

                case (char)Keys.Right:
                    System.Console.WriteLine("la fleche de droite est appuyée.");
                    break;

                case (char)Keys.Tab:
                    System.Console.WriteLine("Le boutton tab est appuyé.");
                    break;

                case (char)Keys.Back:
                    System.Console.WriteLine("La touche de retour appuyée.");
                    break;

                case (char)Keys.ControlKey:
                    System.Console.WriteLine("La touche CTRL est appuyée.");
                    break;

                case (char)Keys.XButton1:
                    System.Console.WriteLine("Click gauche de la souris est appuyé.");
                    break;

                case (char)Keys.XButton2:
                    System.Console.WriteLine("Click droit de la souris est appuyé.");
                    break;

                default:
                    break;
            }
                
            /*
            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée.");
            }
             */
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
            //TODO: Libérer le viewport au menu prinnci
            /*
            if (afficherMenu)
            {
                FonctionsNatives.libererOpenGL();
            }
            else
            {
                InitialiserAnimation();
            }
             * */
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

        private void selectionMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.SELECTION);
        }

        private void deplacementMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DEPLACEMENT);
        }

        private void rotationMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ROTATION);
        }

        private void miseAEchelleMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.MISE_A_ECHELLE);
        }

        private void duplicationMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DUPLICATION);
        }

        private void poteauMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_POTEAU);
        }

        private void murMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_MUR);
        }

        private void ligneNoireMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_LIGNE_NOIRE);
        }
    }

    enum Etat
    {
        SELECTION,
        DEPLACEMENT,
        ROTATION,
        MISE_A_ECHELLE,
        DUPLICATION,
        CREATION_POTEAU,
        CREATION_MUR,
        CREATION_LIGNE_NOIRE
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

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerEtat(Etat etat);
    }
}
