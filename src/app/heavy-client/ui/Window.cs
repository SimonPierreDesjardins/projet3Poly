////////////////////////////////////////////////
/// @file   Window.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using ModeEnum;
using System.Drawing;

namespace ui
{
    public partial class Window : Form, IMessageFilter
    {
        public Configure configuration;

        public UserTabChat userChat;

        public MainMenu mainMenu;
        public PersonnalisationSideMenu personnalisationSideMenu;
        public SimulationMenuStrip simulationMenuStrip;
        public TestMenuStrip testMenuStrip;
        public EditionSideMenu editionSideMenu;
        public EditionMenuStrip editionMenuStrip;

        public object timerLock_ = new object();
        public bool lockWasTaken = false;

        private const int WM_KEYDOWN = 0x0100;
        private const int WM_KEYUP = 0x0101;
        private const int WM_SYSKEYDOWN = 0x0104;
        private const int WM_SYSKEYUP = 0x0105;
        private const int WM_LBUTTONDOWN = 0x0201;
        private const int WM_LBUTTONUP = 0x0202;
        private const int WM_RBUTTONDOWN = 0x0204;
        private const int WM_RBUTTONUP = 0x0205;
        private const int WM_MOUSEMOVE = 0x0200;
        private const int WM_MOUSEWHEEL = 0x020A;

        bool arreterToutMessage_;

        public void arreterToutMessage()
        { arreterToutMessage_ = true; }

        public bool estEnPause = false;

        public bool PreFilterMessage(ref Message m)
        {
            if (!arreterToutMessage_)
            {
                // On veut seulement traiter les inputs sur le view_port.
                if (m.HWnd == viewPort.Handle ||
                    m.Msg == WM_KEYUP ||
                    m.Msg == WM_KEYDOWN ||
                    m.Msg == WM_SYSKEYUP ||
                    m.Msg == WM_SYSKEYDOWN ||
                    m.Msg == WM_MOUSEWHEEL)
                {
                    FonctionsNatives.repartirMessage(m.Msg, m.WParam, m.LParam);
                    if (m.Msg == WM_KEYDOWN)
                        gererMessage(m.WParam);
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

            //Init all menus
            mainMenu = new MainMenu(this);
            mainScreen.Controls.Add(mainMenu);
            mainMenu.Dock = DockStyle.Left;

            userChat = new UserTabChat(this);
            mainScreen.Controls.Add(userChat);
            userChat.Location = new Point(mainScreen.Width - userChat.Width, mainScreen.Height - userChat.Height);
            userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);

            Program.peutAfficher = false;

            InitialiserAnimation();
            panneauOperation_.Visible = false;
            configuration = new Configure(this);
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
            FonctionsNatives.initialiserOpenGL(viewPort.Handle);
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
            { }
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

            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;

            }
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

                if (!(donnee < -23 || donnee > 23))
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

                if (!(donnee < -47 || donnee > 47))
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
        /// @fn private void gererMessage(IntPtr keyDown)
        ///
        /// Gère les touches lorsque le viewPort_ panel à le focus selon le mode
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererMessage(IntPtr keyDown)
        {
            int mode = FonctionsNatives.obtenirMode();

            switch (mode)
            {
                //Mode Menu_Principal
                case 0:
                    break;

                //Mode Simulation
                case 1:
                    gererToucheSimulation(keyDown);
                    break;

                //Mode Edition
                case 2:
                    gererToucheEdition(keyDown);
                    break;

                //Mode Configure
                case 3:
                    break;

                //Mode Test
                case 4:
                    gererToucheTest(keyDown);
                    break;

                //Mode Personalize
                case 5:
                    break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheEdition(IntPtr keyDown)
        ///
        /// Gère les touches pour le mode édition
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheEdition(IntPtr keyDown)
        {
            switch ((int)keyDown)
            {
                case Constants.Key_1:
                    editionMenuStrip.orthoView();
                    break;

                case Constants.Key_2:
                    editionMenuStrip.orbiteView();
                    break;

                case Constants.Key_Del:
                    editionSideMenu.deleteTool();
                    break;

                case Constants.Key_S:
                    if (ModifierKeys.HasFlag(Keys.Control))
                    {
                        if (editionMenuStrip.enregistrerToolStripMenuItem.Enabled)
                            editionMenuStrip.enregistrer();
                        else
                            editionMenuStrip.enregistrerSousZone();
                    }
                    else
                        editionSideMenu.selectTool();
                    break;

                case Constants.Key_Q:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        editionMenuStrip.goMenuPrincipal();
                    break;

                case Constants.Key_O:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        editionMenuStrip.ouvrirZone(false);
                    break;

                case Constants.Key_N:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        editionMenuStrip.nouvelleZone();
                    break;

                case Constants.Key_D:
                    editionSideMenu.moveTool();
                    break;

                case Constants.Key_R:
                    editionSideMenu.rotateTool();
                    break;

                case Constants.Key_E:
                    editionSideMenu.scaleTool();
                    break;

                case Constants.Key_C:
                    editionSideMenu.duplicateTool();
                    break;

                case Constants.Key_Z:
                    editionSideMenu.zoomTool();
                    break;

                case Constants.Key_P:
                    editionSideMenu.postObject();
                    break;

                case Constants.Key_M:
                    editionSideMenu.wallObject();
                    break;

                case Constants.Key_L:
                    editionSideMenu.lineObject();
                    break;

                case Constants.Key_T:
                    editionMenuStrip.goTestMode();
                    break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheSimulation(IntPtr keyDown)
        ///
        /// Gère les touches pour le mode Simulation
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheSimulation(IntPtr keyDown)
        {
            switch ((int)keyDown)
            {
                case Constants.Key_1:
                    simulationMenuStrip.orthoView();
                    break;

                case Constants.Key_2:
                    simulationMenuStrip.orbiteView();
                    break;

                case Constants.Key_3:
                    simulationMenuStrip.firstPersonView();
                    break;

                case Constants.Key_Q:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        simulationMenuStrip.goMenuPrincipal();
                    break;

                 case Constants.Key_Esc:
                    simulationMenuStrip.goIntoPause();
                     break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererToucheTest(IntPtr keyDown)
        ///
        /// Gère les touches pour le mode Test
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheTest(IntPtr keyDown)
        {
            switch ((int)keyDown)
            {
                case Constants.Key_1:
                    testMenuStrip.orthoView();
                    break;

                case Constants.Key_2:
                    testMenuStrip.orbiteView();
                    break;

                case Constants.Key_Q:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        testMenuStrip.goMenuPrincipal();
                    break;

                case Constants.Key_Esc:
                    testMenuStrip.goIntoPause();
                    break;

                case Constants.Key_E:
                    if (ModifierKeys.HasFlag(Keys.Control))
                        testMenuStrip.goModeEdition();
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
        /// @fn private void verificationDuNombreElementChoisi ()
        ///
        /// Permet de savoir le nombre d'objet sélectionné et affiche le panneau
        /// des opérations si un objet est sélectionné
        ///
        ////////////////////////////////////////////////////////////////////////
        public void verificationDuNombreElementChoisi()
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);

            int nbEnfant = FonctionsNatives.obtenirNombreSelection();
            if (nbEnfant == 1)
            {
                mettreAJourInformation();
                viewPort.Focus();
                panneauOperation_.Visible = true;
            }
            else if (nbEnfant > 1)
                panneauOperation_.Visible = false;
            else
                panneauOperation_.Visible = false;
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
            viewPort.Focus();
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
        /// @fn private void textboxDimension__Leave(object sender, EventArgs e)
        ///
        /// Permet les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textboxDimension__Leave(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotation__Leave(object sender, EventArgs e)
        ///
        /// Permet les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxRotation__Leave(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionX__Leave(object sender, EventArgs e)
        ///
        /// Permet les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionX__Leave(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionY__Leave(object sender, EventArgs e)
        ///
        /// Permet les inputs dans le code du c++
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionY__Leave(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void viewPort_Resize(object sender, EventArgs e)
        ///
        /// Ajuste OpenGL lors du redimensionnement du control viewport
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du focus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void viewPort_Resize(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);
            FonctionsNatives.dessinerOpenGL();
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
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerMode(Mode mode);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirMode();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirAffichagesParSeconde();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void repartirMessage(int msg, IntPtr wParam, IntPtr lParam);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirAngleRotation();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirFacteurGrandeur();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeX();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeY();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAngleRotation(double angle);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerFacteurGrandeur(double facteurMiseAEchelle);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeX(double positionRelativeX);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPositionRelativeY(double positionRelativeY);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarder();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void charger();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreSelection();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void nouvelleTable();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerCheminFichierZone(string chemin);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAutorisationInputClavier(bool autorisation);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool obtenirAutorisationInputClavier();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerAutorisationInputSouris(bool autorisation);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool obtenirAutorisationInputSouris();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string obtenirCheminFichierZoneDefaut();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mettreEnPause(bool estEnPause);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerVueOrtho();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerVueOrbite();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerVuePremierePersonne();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTypeVue();
    }
}
