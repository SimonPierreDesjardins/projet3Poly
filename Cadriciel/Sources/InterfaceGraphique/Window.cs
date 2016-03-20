////////////////////////////////////////////////
/// @file   Window.cs
/// @author INF2990
/// @date   2016-02-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
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
using ModeEnum;

namespace InterfaceGraphique
{    
    public partial class Window : Form, IMessageFilter
    {
        private const int WM_KEYDOWN =      0x0100;
        private const int WM_KEYUP =        0x0101;
        private const int WM_SYSKEYDOWN =   0x0104;
        private const int WM_SYSKEYUP =     0x0105;
        private const int WM_LBUTTONDOWN =  0x0201;
        private const int WM_LBUTTONUP =    0x0202;
        private const int WM_RBUTTONDOWN =  0x0204;
        private const int WM_RBUTTONUP =    0x0205;
        private const int WM_MOUSEMOVE =    0x0200;
        private const int WM_MOUSEWHEEL =   0x020A;

        private Configure configuration;

        bool arreterToutMessage_;


        public void arreterToutMessage()
        { arreterToutMessage_ = true; }

        private bool estEnPause = false;
        private bool PasserEnSimulation = false;

        public bool PreFilterMessage(ref Message m)
        {
            if(!arreterToutMessage_)
            {
                // On veut seulement traiter les inputs sur le view_port.
                if (m.HWnd == viewPort_.Handle ||
                    m.Msg == WM_KEYUP          || 
                    m.Msg == WM_KEYDOWN        || 
                    m.Msg == WM_SYSKEYUP       || 
                    m.Msg == WM_SYSKEYDOWN     ||
                    m.Msg == WM_MOUSEWHEEL)   
                {
                    FonctionsNatives.repartirMessage(m.Msg, m.WParam, m.LParam);
                }
                return false;
            }
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Window()
        ///
        /// Cette fonction initialize la fenetre et initialise la visibilité de
        /// ses composantes
        ///
        ////////////////////////////////////////////////////////////////////////
        public Window()
        {
            arreterToutMessage_ = false;
            InitializeComponent();
            InitialiserAnimation();
            menuEdition_.Visible = false;
            barreOutils_.Visible = false;
            panneauOperation_.Visible = false;
            supprimerToolStripMenuItem.Enabled = false;
            configuration = new Configure(profilsMenuSimTest, ajouterProfilSimulation);
            populerProfils();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void InitialiserAnimation()
        ///
        /// Cette fonction initialize les animations sur le viewPort_ panel
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(viewPort_.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        ///
        /// Cette fonction met a jour l'animation de viewPort_ panel
        /// 
        /// @param double tempsInterAffichage: Temps entre chaque affichage
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Window_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// Cette fonction arrete openGL
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param FormClosingEventArgs e: evenement de fermeture
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Window_FormClosing(object sender, FormClosingEventArgs e)
        {
            arreterToutMessage();

            lock(Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
                
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonEditeur_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change la visibilité des composant pour être en mode édition
        /// et assigne le mode à édition et etat à sélection
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonEditeur_Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(false);
            afficherMenuEdition(true);
            panneauOperation_.Visible = false;
            FonctionsNatives.assignerMode(Mode.EDITION);
            verificationDuNombreElementChoisi();
            changeIconColor();
            outilsSelection_.BackColor = Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void quitterToolStripMenuItem1_Click(object sender, EventArgs e)
        ///
        /// Cette fonction ferme l'application lorsque l'utilisation appuie sur Quitter
        /// du menu principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonQuitter_Click(object sender, EventArgs e)
        {
                configuration.Dispose();
                Application.Exit();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void afficherMenuPrincipal(bool afficherMenu)
        ///
        /// Cette fonction ajuste la visibilité des composants de la fenêtre
        /// pour le menu principal
        /// 
        /// @param bool afficherMenu: true si on veut afficher Menu sinon false
        ///
        ////////////////////////////////////////////////////////////////////////
        private void afficherMenuPrincipal(bool afficherMenu)
        {
            bouttonConfiguration_.Visible = afficherMenu;
            bouttonEditeur_.Visible = afficherMenu;
            bouttonQuitter_.Visible = afficherMenu;
            bouttonSimulation_.Visible = afficherMenu;
            viewPort_.Visible = !afficherMenu;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void afficherMenuEdition(bool afficherMenu)
        ///
        /// Cette fonction ajuste la visibilité des composants de la fenêtre
        /// pour le menu édition
        /// 
        /// @param bool afficherMenu: true si on veut afficher Menu sinon false
        ///
        ////////////////////////////////////////////////////////////////////////
        private void afficherMenuEdition(bool afficherMenu)
        {
            viewPort_.Visible = afficherMenu;
            menuEdition_.Visible = afficherMenu;
            barreOutils_.Visible = afficherMenu;
            panneauOperation_.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void afficherMenuSimulation(bool afficherMenu)
        ///
        /// Cette fonction ajuste la visibilité des composants de la fenêtre
        /// pour le menu de simulation
        /// 
        /// @param bool afficherMenu: true si on veut afficher Menu sinon false
        ///
        ////////////////////////////////////////////////////////////////////////
        private void afficherMenuSimulation(bool afficherMenu)
        {
            menuSimTest.Visible = false;
            modeEditionMenuSimTest.Visible = !afficherMenu;
            premierePersonneMenuSimTest.Visible = afficherMenu;
            viewPort_.Visible = afficherMenu;
        }

        private void populerProfils()
        {
            foreach (string nomProfil in configuration.FichiersProfil)
            {
                ajouterProfilSimulation(nomProfil);
            }
            (profilsMenuSimTest.DropDownItems.Find(configuration.NomDernierProfil, false)[0] as ToolStripMenuItem).Checked = true;
        }

        public void ajouterProfilSimulation(string nomProfil)
        {
            ToolStripMenuItem item = new ToolStripMenuItem(nomProfil);
            item.Name = nomProfil;
            item.Click += new EventHandler(profilItem_Click);
            profilsMenuSimTest.DropDownItems.Add(item);
        }

        private void profilItem_Click(object sender, EventArgs e){
            ToolStripMenuItem item = sender as ToolStripMenuItem;
            configuration.changerProfilSelectionne(item.Text);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void afficherMenuTest(bool afficherMenu)
        ///
        /// Cette fonction ajuste la visibilité des composants de la fenêtre
        /// pour le menu de test
        /// 
        /// @param bool afficherMenu: true si on veut afficher Menu sinon false
        ///
        ////////////////////////////////////////////////////////////////////////
        private void afficherMenuTest(bool afficherMenu)
        {
            menuSimTest.Visible = afficherMenu;
            modeEditionMenuSimTest.Visible = afficherMenu;
            premierePersonneMenuSimTest.Visible = !afficherMenu;
            viewPort_.Visible = afficherMenu;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void changeIconColor()
        ///
        /// Cette fonction met la couleur des icons a gris
        ///
        ////////////////////////////////////////////////////////////////////////
        private void changeIconColor()
        {
            outilsDeplacement_.BackColor = System.Drawing.Color.Gray;
            outilsSelection_.BackColor = System.Drawing.Color.Gray;
            outilsRotation_.BackColor = System.Drawing.Color.Gray;
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.Gray;
            outilsDuplication_.BackColor = System.Drawing.Color.Gray;
            outilsZoom_.BackColor = System.Drawing.Color.Gray;
            outilsCreationPoteau_.BackColor = System.Drawing.Color.Gray;
            outilsCreationMurs_.BackColor = System.Drawing.Color.Gray;
            outilsCreationLigne_.BackColor = System.Drawing.Color.Gray;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction affiche le menu principal et change le mode à menu principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            afficherMenuPrincipal(true);
            afficherMenuEdition(false);
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void miseAÉchelleToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, mise à échelle
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void miseAEchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton E : Mise a échelle
            FonctionsNatives.repartirMessage((int)256, (IntPtr)69, (IntPtr)1179649);
            changeIconColor();
            outilsMiseAEchelle_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, sélection
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void sToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton S : sélection
            FonctionsNatives.repartirMessage((int)256, (IntPtr)83, (IntPtr)2031617);
            changeIconColor();
            outilsSelection_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, déplacement
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton D : Déplacement
            FonctionsNatives.repartirMessage((int)256, (IntPtr)68, (IntPtr)2097153);
            changeIconColor();
            outilsDeplacement_.BackColor = Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, rotation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton R : Rotation
            FonctionsNatives.repartirMessage((int)256, (IntPtr)82, (IntPtr)1245185);
            changeIconColor();
            outilsRotation_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, duplication
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton C : Duplication
            FonctionsNatives.repartirMessage((int)256, (IntPtr)67, (IntPtr)3014657);
            changeIconColor();
            outilsDuplication_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation poteau
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton P : Creation poteau
            FonctionsNatives.repartirMessage((int)256, (IntPtr)80, (IntPtr)1638401);
            changeIconColor();
            outilsCreationPoteau_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void murToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation mur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void murToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton M : Creation mur
            FonctionsNatives.repartirMessage((int)256, (IntPtr)77, (IntPtr)3276801);
            changeIconColor();
            outilsCreationMurs_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne noire
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton L : Creation ligne
            FonctionsNatives.repartirMessage((int)256, (IntPtr)76, (IntPtr)2490368);
            changeIconColor();
            outilsCreationLigne_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, zoom
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Bouton Z : Zoom
            FonctionsNatives.repartirMessage((int)256, (IntPtr)90, (IntPtr)2883585);
            changeIconColor();
            outilsZoom_.BackColor = System.Drawing.Color.CadetBlue;
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Fonction appelant les fonctions servant à redimenssionner la fenetre virtuelle selon la cloture pour garder le rapport d'aspect.
        /// Celle-ci est appelée lorsqu'on redimenssionne la fenetre.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Window_Resize(object sender, EventArgs e)
        {
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Fonction appelant les fonctions servant à redimenssionner la fenetre virtuelle selon la cloture pour garder le rapport d'aspect.
        /// Celle-ci est appelée lors du chargement de la fenetre.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Window_Load(object sender, EventArgs e)
        {
            // On gère cette redimension dans openGL
            FonctionsNatives.redimensionnerFenetre(viewPort_.Width, viewPort_.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsSelection__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, sélection
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsSelection__Click(object sender, EventArgs e)
        {
            //Bouton S : sélection
            FonctionsNatives.repartirMessage((int)256, (IntPtr)83, (IntPtr)2031617);
            changeIconColor();
            outilsSelection_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsDéplacement__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, déplacement
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsDéplacement__Click(object sender, EventArgs e)
        {
            //Bouton D : Déplacement
            FonctionsNatives.repartirMessage((int)256, (IntPtr)68, (IntPtr)2097153);
            changeIconColor();
            outilsDeplacement_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsRotation__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, rotation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsRotation__Click(object sender, EventArgs e)
        {
            //Bouton R : Rotation
            FonctionsNatives.repartirMessage((int)256, (IntPtr)82, (IntPtr)1245185);
            changeIconColor();
            outilsRotation_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsMiseAEchelle__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, mise à échelle
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsMiseAEchelle__Click(object sender, EventArgs e)
        {
            //Bouton E : Mise a échelle
            FonctionsNatives.repartirMessage((int)256, (IntPtr)69, (IntPtr)1179649);
            changeIconColor();
            outilsMiseAEchelle_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsDuplication__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, duplication
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsDuplication__Click(object sender, EventArgs e)
        {
            //Bouton C : Duplication
            FonctionsNatives.repartirMessage((int)256, (IntPtr)67, (IntPtr)3014657);
            changeIconColor();
            outilsDuplication_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsZoom__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, zoom
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsZoom__Click(object sender, EventArgs e)
        {
            //Bouton Z : Zoom
            FonctionsNatives.repartirMessage((int)256, (IntPtr)90, (IntPtr)2883585);
            changeIconColor();
            outilsZoom_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationPoteau__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation poteau
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsCreationPoteau__Click(object sender, EventArgs e)
        {
            //Bouton P : Creation poteau
            FonctionsNatives.repartirMessage((int)256, (IntPtr)80, (IntPtr)1638401);
            changeIconColor();
            outilsCreationPoteau_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationMurs__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation mur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsCreationMurs__Click(object sender, EventArgs e)
        {
            //Bouton M : Creation mur
            FonctionsNatives.repartirMessage((int)256, (IntPtr)77, (IntPtr)3276801);
            changeIconColor();
            outilsCreationMurs_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationLigne__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne noire
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outilsCreationLigne__Click(object sender, EventArgs e)
        {
            //Bouton L : Creation ligne
            FonctionsNatives.repartirMessage((int)256, (IntPtr)76, (IntPtr)2490368);
            changeIconColor();
            outilsCreationLigne_.BackColor = Color.CadetBlue;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modeTestModeEdition__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change le mode pour test lorsque le mode test est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void modeTestModeEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.TEST);
            afficherMenuPrincipal(false);
            afficherMenuEdition(false);
            afficherMenuTest(true);
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouttonSimulation__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change le mode pour simulation lorsque le mode simulation est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouttonSimulation__Click(object sender, EventArgs e)
        {
            ouvrirZone(true);

            if (PasserEnSimulation)
            {
                afficherMenuPrincipal(false);
                afficherMenuEdition(false);
                afficherMenuSimulation(true);
                FonctionsNatives.assignerMode(Mode.SIMULATION);
            }
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouttonConfiguration__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change le mode pour configuration lorsque le mode configuration est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouttonConfiguration__Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.CONFIGURE);
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            configuration.ShowDialog();
            viewPort_.Focus();
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void aideMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Affiche une nouvelle fenêtre indiquant des informations d'aide
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void aideMenuEdition__Click(object sender, EventArgs e)
        {
            PopOutInterface popup = new PopOutInterface();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            DialogResult dialogresult = popup.ShowDialog();
            if (dialogresult == DialogResult.OK || dialogresult == DialogResult.Cancel)
            {
                popup.Dispose();
                viewPort_.Focus();
            }
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionY__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
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

                mettreAJourInformation();
                textBoxPositionY_.Select(textBoxPositionY_.Text.Length, 0);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionX__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
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

                mettreAJourInformation();
                textBoxPositionX_.Select(textBoxPositionX_.Text.Length, 0);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotation__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
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
                mettreAJourInformation();
                textBoxRotation_.Select(textBoxRotation_.Text.Length, 0);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textboxDimension__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
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
                mettreAJourInformation();
                textboxDimension_.Select(textboxDimension_.Text.Length, 0);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Supprime tous les objets sélectionnés
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            supprimerToolStripMenuItem.Enabled = false;
            verificationDuNombreElementChoisi();
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nouveauMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Crée une nouvelle zone de céation lorsque nouveau est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nouveauMenuEdition__Click(object sender, EventArgs e)
        {
            nouvelleZone();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nouveauMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Crée une nouvelle zone de céation si l'utilisateur appuie sur oui, 
        /// sinon ne fait rien
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nouvelleZone()
        {
            DialogResult dialogResult = MessageBox.Show("Êtes-vous sure de vouloir créer une nouvelle épreuve", "Creation d'une nouvelle zone", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                FonctionsNatives.nouvelleTable();
                panneauOperation_.Visible = false;
                enregistrerMenuEdition_.Enabled = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerSousMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Sauvegarde la zone lorsque enregistrer sous est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerSousMenuEdition__Click(object sender, EventArgs e)
        {
            enregistrerSousZone();            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerSousZone()
        ///
        /// Ouvre un explorateur de fichier qui permet de sauvegarde la zone, permet uniquement à 
        /// l'utilisateur de sauvegarder dans zones
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerSousZone()
        {
            ExplorateurSauvegarde explorateur = new ExplorateurSauvegarde();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            if (explorateur.ShowDialog() == DialogResult.OK)
            {
                FonctionsNatives.assignerCheminFichierZone(explorateur.cheminFichier);
                FonctionsNatives.sauvegarder();
                enregistrerMenuEdition_.Enabled = true;
            }
            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Charge une zone sauvegardée
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirMenuEdition__Click(object sender, EventArgs e)
        {
            ouvrirZone(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirZone()
        ///
        /// Ouvre un explorateur de ficher pour charger la zone sauvegarder lorsque 
        /// le bouton ouvrir est appuyer sur le menu
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirZone(bool afficherZoneDefaut)
        {
            ExplorateurOuverture explorateur = new ExplorateurOuverture(afficherZoneDefaut);
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            DialogResult dialogresult = explorateur.ShowDialog();
            if (dialogresult == DialogResult.OK)
            {
                FonctionsNatives.assignerCheminFichierZone(explorateur.cheminFichier);
                FonctionsNatives.charger();
                enregistrerMenuEdition_.Enabled = true;
                PasserEnSimulation = true;
            }
            if (dialogresult == DialogResult.Cancel)
                PasserEnSimulation = false;

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
            panneauOperation_.Visible = false;
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void viewPort__PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Gère les touches lorsque le viewPort_ panel à le focus selon le mode
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param PreviewKeyDownEventArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void viewPort__PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            int mode = FonctionsNatives.obtenirMode();

            switch(mode)
            {
                //Mode Menu_Principal
                case 0:
                    break;

                //Mode Simulation
                case 1:
                    gererToucheSimulation(sender, e);
                    break;
                
                //Mode Edition
                case 2:
                    gererToucheEdition(sender, e);
                    break;

                //Mode Configure
                case 3:
                    break;

                //Mode Test
                case 4:
                    gererToucheTest(sender, e);
                    break;

                default:
                    break;
            }

            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheEdition(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Gère les touches pour le mode édition
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param PreviewKeyDownEventArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheEdition(object sender, PreviewKeyDownEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Delete:
                    verificationDuNombreElementChoisi();
                    break;

                case Keys.S:
                    if (e.Control)
                    {
                        if (enregistrerMenuEdition_.Enabled)
                            FonctionsNatives.sauvegarder();
                        else
                            enregistrerSousZone();
                    }
                    else
                    {
                        changeIconColor();
                        outilsSelection_.BackColor = System.Drawing.Color.CadetBlue;
                    }
                    break;

                case Keys.Q:
                    if (e.Control)
                    {
                        FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
                        afficherMenuEdition(false);
                        afficherMenuPrincipal(true);
                    }
                    break;

                case Keys.O:
                    if (e.Control)
                        ouvrirZone(false);
                    break;

                case Keys.N:
                    if (e.Control)
                        nouvelleZone();
                    break;

                case Keys.D:
                    changeIconColor();
                    outilsDeplacement_.BackColor = Color.CadetBlue;
                    break;

                case Keys.R:
                    changeIconColor();
                    outilsRotation_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.E:
                    changeIconColor();
                    outilsMiseAEchelle_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.C:
                    changeIconColor();
                    outilsDuplication_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.Z:
                    changeIconColor();
                    outilsZoom_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.P:
                    changeIconColor();
                    outilsCreationPoteau_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.M:
                    changeIconColor();
                    outilsCreationMurs_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.L:
                    changeIconColor();
                    outilsCreationLigne_.BackColor = System.Drawing.Color.CadetBlue;
                    break;

                case Keys.T:
                    afficherMenuEdition(false);
                    afficherMenuTest(true);
                    FonctionsNatives.assignerMode(Mode.TEST);
                    break;

                default:
                    break;
            }     
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheSimulation(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Gère les touches pour le mode Simulation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param PreviewKeyDownEventArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheSimulation(object sender, PreviewKeyDownEventArgs e)
        {
            

            switch (e.KeyCode)
            {
                case Keys.Q:
                    if (e.Control)
                    {
                        afficherMenuSimulation(false);
                        afficherMenuTest(false);
                        afficherMenuEdition(false);
                        afficherMenuPrincipal(true);
                        FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
                        estEnPause = false;
                        //FonctionsNatives.mettreEnPause(estEnPause);
                        picturePause.Visible = estEnPause;
                    }
                    break;

                case Keys.Escape:
                    estEnPause = !estEnPause;
                    //FonctionsNatives.mettreEnPause(estEnPause);
                    picturePause.Visible = estEnPause;
                    menuSimTest.Visible = estEnPause;
                    break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheTest(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Gère les touches pour le mode Test
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param PreviewKeyDownEventArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheTest(object sender, PreviewKeyDownEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Q:
                    if (e.Control)
                    {
                        estEnPause = false;
                        picturePause.Visible = estEnPause;

                        FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
                        afficherMenuTest(false);
                        afficherMenuPrincipal(true);
                    }
                    break;

                case Keys.Escape:
                    estEnPause = !estEnPause;
                    //FonctionsNatives.mettreEnPause(estEnPause);
                    picturePause.Visible = estEnPause;
                    menuSimTest.Visible = estEnPause;
                    break;

                case Keys.E:
                    if (e.Control)
                    {
                        estEnPause = false;
                        picturePause.Visible = estEnPause;

                        afficherMenuSimulation(false);
                        afficherMenuTest(false);
                        afficherMenuPrincipal(false);
                        afficherMenuEdition(true);
                        changeIconColor();
                        outilsSelection_.BackColor = Color.CadetBlue;
                        FonctionsNatives.assignerMode(Mode.EDITION);
                        viewPort_.Focus();
                    }
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textboxDimension__Enter(object sender, EventArgs e)
        ///
        /// Empêche les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textboxDimension__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionX__Enter(object sender, EventArgs e)
        ///
        /// Empêche les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionX__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotation__Enter(object sender, EventArgs e)
        ///
        /// Empêche les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxRotation__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionY__Enter(object sender, EventArgs e)
        ///
        /// Empêche les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionY__Enter(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerMenuEdition__Click(object sender, EventArgs e)
        ///
        /// Permet de sauvegarder un ficher lorsque le bouton sauvegarder est cliqué
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerMenuEdition__Click(object sender, EventArgs e)
        {
            FonctionsNatives.sauvegarder();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void verificationDuNombreElementChoisi ()
        ///
        /// Permet de savoir le nombre d'objet sélectionné et affiche le panneau
        /// des opérations si un objet est sélectionné
        ///
        ////////////////////////////////////////////////////////////////////////
        private void verificationDuNombreElementChoisi ()
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);

            int nbEnfant = FonctionsNatives.obtenirNombreSelection();
            if (nbEnfant == 1)
            {
                mettreAJourInformation();
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void viewPort__MouseUp(object sender, MouseEventArgs e)
        ///
        /// Vérifie le nombre d'objet sélectionné lorsqu'un clique de la souris est relâché
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement de la souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void viewPort__MouseUp(object sender, MouseEventArgs e)
        {
            verificationDuNombreElementChoisi();
            viewPort_.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mettreAJourInformation()
        ///
        /// Met à jour les informations dans le panneau d'opération
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mettreAJourInformation()
        {
            textboxDimension_.Text = FonctionsNatives.obtenirFacteurGrandeur().ToString();
            textBoxRotation_.Text = FonctionsNatives.obtenirAngleRotation().ToString();
            textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
            textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void viewPort__MouseMove(object sender, MouseEventArgs e)
        ///
        /// Vérifie le nombre d'objet sélectionné, s'il en a seulement un et que le clique
        /// gauche est appuyé il met a jour les info dans le panneau d'opération
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement de la souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void viewPort__MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                verificationDuNombreElementChoisi();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalMenuSimTest_Click(object sender, MouseEventArgs e)
        ///
        /// Affiche le menu principal lorsque le bouton Menu Principal est appuyé à partir
        /// du menu de Simulation ou du menu de Test
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement de la souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalMenuSimTest_Click(object sender, EventArgs e)
        {
            afficherMenuSimulation(false);
            afficherMenuTest(false);
            afficherMenuEdition(false);
            afficherMenuPrincipal(true);
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
            estEnPause = false;
            picturePause.Visible = estEnPause;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modeEditionMenuSimTest_Click(object sender, MouseEventArgs e)
        ///
        /// Affiche le menu Edition lorsque le bouton Mode Edition est appuyé à partir
        /// du menu de Test
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement de la souris
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void modeEditionMenuSimTest_Click(object sender, EventArgs e)
        {
            estEnPause = false;
            picturePause.Visible = estEnPause;

            afficherMenuSimulation(false);
            afficherMenuTest(false);
            afficherMenuPrincipal(false);
            afficherMenuEdition(true);
            changeIconColor();
            outilsSelection_.BackColor = Color.CadetBlue;
            FonctionsNatives.assignerMode(Mode.EDITION);
            viewPort_.Focus();
        }

    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn  static partial class FonctionsNatives
    ///
    /// Permet de faire le lien avec les méthodes implémentées dans le C++
    ///
    ////////////////////////////////////////////////////////////////////////
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
        public static extern void assignerMode(Mode mode);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirMode();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

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
        public static extern void assignerFacteurGrandeur(double facteurMiseAEchelle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeX(double positionRelativeX);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeY(double positionRelativeY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarder();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void charger();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreSelection();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nouvelleTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerCheminFichierZone(string chemin);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAutorisationInputClavier(bool autorisation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool obtenirAutorisationInputClavier();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAutorisationInputSouris(bool autorisation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool obtenirAutorisationInputSouris();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string obtenirCheminFichierZoneDefaut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mettreEnPause(bool estEnPause);
    }
}
