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
        private const int WM_KEYUP =        0x101;
        private const int WM_KEYDOWN =      0x100;
        private const int WM_LBUTTONDOWN =  0x0201;
        private const int WM_LBUTTONUP =    0x0202;
        private const int WM_RBUTTONDOWN =  0x0204;
        private const int WM_RBUTTONUP =    0x0205;
        private const int WM_MOUSEMOVE =    0x0200;
        private const int WM_MOUSEWHEEL =   0x020A;

        public bool PreFilterMessage(ref Message m)
        {
            // On veut seulement traiter les inputs sur le view_port.
            if (m.HWnd == viewPort_.Handle || m.Msg == WM_KEYDOWN || m.Msg == WM_KEYUP || m.Msg == WM_MOUSEWHEEL)
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
            barreOutils_.Visible = false;
            panneauOperation_.Visible = false;
            supprimerToolStripMenuItem.Enabled = false;
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
            {}
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
            panneauOperation_.Visible = false;
            FonctionsNatives.assignerMode(Mode.EDITION);
            viewPort_.Focus();
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
            barreOutils_.Visible = !afficherMenu;
            panneauOperation_.Visible = !afficherMenu;
        }

        private void miseAÉchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.MISE_A_ECHELLE);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.CadetBlue;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(true);
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void sToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.SELECTION);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.CadetBlue;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DEPLACEMENT);
            outilsDéplacement_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ROTATION);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.CadetBlue;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DUPLICATION);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.CadetBlue;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_POTEAU);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.CadetBlue;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void murToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_MUR);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.CadetBlue;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_LIGNE_NOIRE);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        private void Window_Resize(object sender, EventArgs e)
        {
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
            FonctionsNatives.dessinerOpenGL();
        }

        private void Window_Load(object sender, EventArgs e)
        {
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
        }

        private void outilsSelection__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.SELECTION);
            outilsSelection_.BackColor = Color.CadetBlue;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsDéplacement__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DEPLACEMENT);
            outilsDéplacement_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsRotation__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ROTATION);
            outilsRotation_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsMiseAEchelle__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.MISE_A_ECHELLE);
            outilsMiseAEchelle_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsDuplication__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.DUPLICATION);
            outilsDuplication_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsZoom__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ZOOM);
            outilsZoom_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsCreationPoteau__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_POTEAU);
            outilsCreationPoteau_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsCreationMurs__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_MUR);
            outilsCreationMurs_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        private void outilsCreationLigne__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.CREATION_LIGNE_NOIRE);
            outilsCreationLigne_.BackColor = Color.CadetBlue;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
        }

        private void modeTestModeEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.TEST);
        }

        private void bouttonSimulation__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.SIMULATION);
        }

        private void bouttonConfiguration__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.CONFIGURE);
        }

        private void aideMenuEdition__Click(object sender, EventArgs e)
        {
            PopOutInterface popup = new PopOutInterface();
            DialogResult dialogresult = popup.ShowDialog();
            if (dialogresult == DialogResult.OK || dialogresult == DialogResult.Cancel)
            {
                popup.Dispose();
                viewPort_.Focus();
            }
        }

        private void textboxDimension__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerFacteurGrandeur(Convert.ToDouble(textboxDimension_.Text));
        }

        private void textBoxRotation__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAngleRotation(Convert.ToDouble(textBoxRotation_.Text));
        }

        private void textBoxPositionX__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerPositionRelativeX(Convert.ToDouble(textBoxPositionX_.Text));
        }

        private void textBoxPositionY__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionY_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeY();
                }

                if (!(donnee < -24 || donnee > 24))
                    FonctionsNatives.assignerPositionRelativeY(donnee);
                else
                    textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
            }
        }

        private void textBoxPositionX__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionX_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeX();
                }

                if (!(donnee < -48 || donnee > 48))
                    FonctionsNatives.assignerPositionRelativeX(donnee);
                else
                    textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
            }
        }

        private void textBoxRotation__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textBoxRotation_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirAngleRotation();
                }
                FonctionsNatives.assignerAngleRotation(donnee);
            }
        }

        private void textboxDimension__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textboxDimension_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirFacteurGrandeur();
                }
                FonctionsNatives.assignerFacteurGrandeur(donnee);
            }
        }

        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.suppression();
            supprimerToolStripMenuItem.Enabled = false;
            panneauOperation_.Visible = false;
            viewPort_.Focus();
        }

        private void viewPort__MouseClick(object sender, MouseEventArgs e)
        {
            FonctionsNatives.assignerAutorisationInput(true);
            if (FonctionsNatives.obtenirEtat() == 0)
            {
                int nbEnfant = FonctionsNatives.obtenirNombreSelection();
                if (nbEnfant == 1)
                {
                    textboxDimension_.Text = FonctionsNatives.obtenirFacteurGrandeur().ToString();
                    textBoxRotation_.Text = FonctionsNatives.obtenirAngleRotation().ToString();
                    textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
                    textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
                    viewPort_.Focus();
                    panneauOperation_.Visible = true;
                    supprimerToolStripMenuItem.Enabled = true;
                }
                else if (nbEnfant > 1)
                {
                    supprimerToolStripMenuItem.Enabled = true;
                    panneauOperation_.Visible = false;
                }
                else
                {
                    panneauOperation_.Visible = false;
                    supprimerToolStripMenuItem.Enabled = false;
                }
                    
            }
        }

        private void nouveauMenuEdition__Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Êtes-vous sure de vouloir créer une nouvelle épreuve", "Creation d'une nouvelle zone", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                FonctionsNatives.nouvelleTable();
            }
        }

        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerEtat(Etat.ZOOM);
            outilsDéplacement_.BackColor = Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.CadetBlue;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            viewPort_.Focus();
        }

        private void enregistrerSousMenuEdition__Click(object sender, EventArgs e)
        {
            Process.Start(@"explorer.exe");
        }

        private void ouvrirMenuEdition__Click(object sender, EventArgs e)
        {
            Process.Start(@"explorer.exe");
        }

        private void textboxDimension__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInput(false);
        }

        private void textBoxRotation__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInput(false);
        }

        private void textBoxPositionX__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInput(false);
        }

        private void textBoxPositionY__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInput(false);
        }

        private void viewPort__PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                if (FonctionsNatives.obtenirEtat() == 0)
                {
                    int nbEnfant = FonctionsNatives.obtenirNombreSelection();
                    if (nbEnfant == 1)
                    {
                        textboxDimension_.Text = FonctionsNatives.obtenirFacteurGrandeur().ToString();
                        textBoxRotation_.Text = FonctionsNatives.obtenirAngleRotation().ToString();
                        textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
                        textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
                        viewPort_.Focus();
                        panneauOperation_.Visible = true;
                        supprimerToolStripMenuItem.Enabled = true;
                    }
                    else if (nbEnfant > 1)
                    {
                        supprimerToolStripMenuItem.Enabled = true;
                        panneauOperation_.Visible = false;
                    }
                    else
                    {
                        panneauOperation_.Visible = false;
                        supprimerToolStripMenuItem.Enabled = false;
                    }

                }
            }
            else if (e.KeyCode == Keys.D)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.Gray;
                outilsDéplacement_.BackColor = Color.CadetBlue;
                outilsRotation_.BackColor = System.Drawing.Color.Gray;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
                outilsDuplication_.BackColor = System.Drawing.Color.Gray;
                outilsZoom_.BackColor = System.Drawing.Color.Gray;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            }
            else if (e.KeyCode == Keys.S)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.CadetBlue;
                outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
                outilsRotation_.BackColor = System.Drawing.Color.Gray;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
                outilsDuplication_.BackColor = System.Drawing.Color.Gray;
                outilsZoom_.BackColor = System.Drawing.Color.Gray;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            }
            else if (e.KeyCode == Keys.R)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.Gray;
                outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
                outilsRotation_.BackColor = System.Drawing.Color.CadetBlue;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
                outilsDuplication_.BackColor = System.Drawing.Color.Gray;
                outilsZoom_.BackColor = System.Drawing.Color.Gray;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            }
            else if (e.KeyCode == Keys.E)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.Gray;
                outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
                outilsRotation_.BackColor = System.Drawing.Color.Gray;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.CadetBlue;
                outilsDuplication_.BackColor = System.Drawing.Color.Gray;
                outilsZoom_.BackColor = System.Drawing.Color.Gray;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            }
            else if (e.KeyCode == Keys.C)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.Gray;
                outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
                outilsRotation_.BackColor = System.Drawing.Color.Gray;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
                outilsDuplication_.BackColor = System.Drawing.Color.CadetBlue;
                outilsZoom_.BackColor = System.Drawing.Color.Gray;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
            }
            else if (e.KeyCode == Keys.Z)
            {
                outilsCreationMurs_.BackColor = Color.Gray;
                outilsSelection_.BackColor = System.Drawing.Color.Gray;
                outilsDéplacement_.BackColor = System.Drawing.Color.Gray;
                outilsRotation_.BackColor = System.Drawing.Color.Gray;
                outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
                outilsDuplication_.BackColor = System.Drawing.Color.Gray;
                outilsZoom_.BackColor = System.Drawing.Color.CadetBlue;
                outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
                outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
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
        ZOOM
    };

    enum Mode
    {
        MENU_PRINCIPAL,
        SIMULATION,
        EDITION,
        CONFIGURE,
        TEST
    };

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
        public static extern int obtenirEtat();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerMode(Mode mode);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirMode();

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

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirAngleRotation();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirFacteurGrandeur();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAngleRotation(double angle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerFacteurGrandeur(double facteurGrandeur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeX(double positionRelativeX);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeY(double positionRelativeY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void suppression();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreSelection();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nouvelleTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAutorisationInput(bool autorisation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool obtenirAutorisationInput();

    }
}
