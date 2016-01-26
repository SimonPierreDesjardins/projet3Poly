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
        private const int WM_MOUSEWHEEL =    0x020A;

        public bool PreFilterMessage(ref Message m)
        {
            // On veut seulement traiter les inputs sur le view_port.
            if (m.HWnd == viewPort_.Handle || m.Msg == WM_KEYDOWN || m.Msg == WM_MOUSEWHEEL)
            {
                FonctionsNatives.repartirMessage(m.Msg, m.WParam, m.LParam);
            }
            return false;
        }
       
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
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
            FonctionsNatives.dessinerOpenGL();
        }

        private void viewPort__Paint(object sender, PaintEventArgs e)
        {

        }

        private void Window_Load(object sender, EventArgs e)
        {
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
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
        public static extern void repartirMessage(int msg, IntPtr wParam, IntPtr lParam);

    }
}
