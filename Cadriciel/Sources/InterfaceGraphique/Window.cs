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
    public partial class Window : Form, IMessageFilter
    {        
        
        private const int WM_KEYDOWN =      0x100;
        private const int WM_LBUTTONDOWN =  0x0201;
        private const int WM_LBUTTONUP =    0x0202;
        private const int WM_RBUTTONDOWN =  0x0204;
        private const int WM_RBUTTONUP =    0x0205;
        private const int WM_MOUSEMOVE =    0x0200;


        public bool PreFilterMessage(ref Message m)
        {
            // On veut seulement traiter les inputs sur le view_port.
            if (m.HWnd != viewPort_.Handle) return false;

            if (m.Msg == WM_LBUTTONDOWN ||
                m.Msg == WM_LBUTTONUP   ||
                m.Msg == WM_RBUTTONDOWN ||
                m.Msg == WM_RBUTTONUP   || 
                m.Msg == WM_MOUSEMOVE   ||
                m.Msg == WM_KEYDOWN)
            {
                FonctionsNatives.repartirMessage(m.Msg, m.WParam, m.LParam);
            }
            // Permet le traitement du message par l'interface.
            return false;
        }
        
        /*
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            //Voir https://msdn.microsoft.com/fr-fr/library/system.windows.forms.keys%28v=vs.110%29.aspx

            switch (keyData)
            {
                case Keys.Space:
                    System.Console.WriteLine("Barre d'espacement appuyée.");
                    return true;

                case Keys.Up:
                    System.Console.WriteLine("La fleche du haut est appuyée.");
                    return true;

                case Keys.Down:
                    System.Console.WriteLine("La fleche du bas est appuyée.");
                    return true;

                case Keys.Left:
                    System.Console.WriteLine("La fleche de gauche est appuyée.");
                    return true;

                case Keys.Right:
                    System.Console.WriteLine("la fleche de droite est appuyée.");
                    return true;

                case Keys.Tab:
                    System.Console.WriteLine("La touche tab est appuyée.");
                    return true;

                case Keys.Back:
                    System.Console.WriteLine("La touche de retour appuyée.");
                    return true;

                case Keys.Escape:
                    System.Console.WriteLine("La touche esc est appuyée.");
                    return true;

                case Keys.Control | Keys.F4:
                    System.Console.WriteLine("La touche CTRL+F4 est appuyée.");
                    Application.Exit();
                    return true;

                case Keys.CapsLock:
                    System.Console.WriteLine("La touche CapsLock est appuyée.");
                    return true;

                case Keys.LButton:
                    System.Console.WriteLine("Click gauche de la souris est appuyé.");
                    return true;

                case Keys.RButton:
                    System.Console.WriteLine("Click droit de la souris est appuyé.");
                    return true;

                default:
                    break;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        */
        public Window()
        {
            InitializeComponent();
            InitialiserAnimation();
            menuEdition_.Visible = false;
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

        private void buttonEditeur_Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(false);
            menuEdition_.Visible = true;
            FonctionsNatives.assignerEtat(Etat.SELECTION);
        }

        private void buttonQuitter_Click(object sender, EventArgs e)
        {
                Application.Exit();
        }

        private void afficherMenuPrincipal(bool afficherMenu)
        {
            //TODO: Libérer le viewport au menu principal
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
            menuEdition_.Visible = !afficherMenu;
        }

        private void miseAÉchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.MISE_A_ECHELLE);
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(true);
            menuEdition_.Visible = false;
        }

        private void sToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.SELECTION);
        }

        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DEPLACEMENT);
        }

        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ROTATION);
        }

        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DUPLICATION);
        }

        private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_POTEAU);
        }

        private void murToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_MUR);
        }

        private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_LIGNE_NOIRE);
        }

        private void Window_Resize(object sender, EventArgs e)
        {
            //FonctionsNatives.redimensionnerFenetre(this.Height, this.Width);
            FonctionsNatives.dessinerOpenGL();
        }

        private void viewPort__Click(object sender, EventArgs e)
        {

        }
        
        private void viewPort__MouseDown(object sender, MouseEventArgs e)
        {
            Point p = viewPort_.PointToClient(Cursor.Position);
            if (e.Button == MouseButtons.Right)
            {
                FonctionsNatives.gererClicDroitEnfonce(p.X, p.Y);
            }
            else if (e.Button == MouseButtons.Left)
            {
                FonctionsNatives.gererClicGaucheEnfonce(p.X, p.Y);
            }
        }

        private void viewPort__MouseUp(object sender, MouseEventArgs e)
        {
            Point p = viewPort_.PointToClient(Cursor.Position);
            if (e.Button == MouseButtons.Right)
            {
                FonctionsNatives.gererClicDroitRelache(p.X, p.Y);
            }
            else if (e.Button == MouseButtons.Left)
            {
                FonctionsNatives.gererClicGaucheRelache(p.X, p.Y);
            }
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
        CREATION_LIGNE_NOIRE,
        MENU_PRINCIPALE,
        SIMULATION,
        TEST
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

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirAffichagesParSeconde();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void gererMessage(Message m);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
	    public static extern void gererClicGaucheEnfonce(int x, int y);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void gererClicDroitEnfonce(int x, int y);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void gererClicGaucheRelache(int x, int y);
	   
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void gererClicDroitRelache(int x, int y);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void repartirMessage(int msg, IntPtr wParam, IntPtr lParam);

    }
}
