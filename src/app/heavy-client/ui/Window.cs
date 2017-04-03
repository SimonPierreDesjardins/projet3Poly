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
using System.Text;
using System.Threading;
using System.Drawing;

namespace ui
{
    public partial class Window : Form, IMessageFilter
    {
        public Configure configuration;

        public UserTabChat userChat;
        public string userName = "";

        public DisconnetedPanel disconnectedWarning;

        public MainMenu mainMenu;
        public MapMenu mapMenu;
        public PersonnalisationSideMenu personnalisationSideMenu;
        public SimulationMenuStrip simulationMenuStrip;
        public TestMenuStrip testMenuStrip;

        public EditionSideMenu editionSideMenu;
        public EditionMenuStrip editionMenuStrip;
        public EditionModificationPanel editionModificationPanel;

        public TutorialSimulation simulationTutorial;

        public EditionTutorielMenuStrip editionTutorielMenuStrip;
        public EditionTutorielSideMenu editionTutorielSideMenu;
        public EditionTutorielInstructions editionTutorielInstructions;
        public TutorialEditionModificationPanel editionTutorielModificationPanel;

        public OnlineEditionMenuStrip onlineEditionMenuStrip;
        public OnlineSimulationMenuStrip onlineSimulationMenuStrip;
        public OnlinePiecesMenuStrip onlinePiecesMenuStrip;
        public OnlineRaceMenuStrip onlineRaceMenuStrip;

        public string PathToDefaultZone_;

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

        bool allowCommunication_;

        public bool estEnPause = false;

        public bool PreFilterMessage(ref Message m)
        {
            if (allowCommunication_)
            {
                // On veut seulement traiter les inputs sur le view_port.
                if (m.HWnd == viewPort.Handle ||
                    m.Msg == WM_KEYUP      ||
                    m.Msg == WM_KEYDOWN    ||
                    m.Msg == WM_SYSKEYUP   ||
                    m.Msg == WM_KEYDOWN    ||
                    m.Msg == WM_SYSKEYDOWN ||
                    m.Msg == WM_MOUSEWHEEL)
                {
                    FonctionsNatives.repartirMessage(m.Msg, m.WParam, m.LParam);
                    if (m.Msg == WM_KEYDOWN)
                    {
                        gererMessage(m.WParam);
                    }
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
            allowCommunication_ = true;
            InitializeComponent();

            //Init all menus
            mapMenu = new MapMenu(this);
            mainMenu = new MainMenu(this);
            viewPort.Controls.Add(mainMenu);
            mainMenu.Dock = DockStyle.Left;

            Program.peutAfficher = false;

            InitialiserAnimation();
            configuration = new Configure(this);
            //Load data from last launch
            FonctionsNatives.LoadApplicationSettings();
            System.Text.StringBuilder str = new System.Text.StringBuilder(100);
            FonctionsNatives.obtenirCheminFichierZoneDefaut(str, str.Capacity);
            PathToDefaultZone_ = str.ToString();

            mInstance = new CallbackForNewMap(addNewMap);
            SetCallbackForNewMap(mInstance);
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
        /// @fn public void initializeServerConnection(String hostName, String port)
        ///
        /// Cette fonction lance la connection au serveur 
        ///
        /// @param String hostname: Le hostName ou l'adresse ip du serveur
        /// @param String port: Le port du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        public void initializeServerConnection(String hostName, String port)
        {
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
            //Save data for next launch
            FonctionsNatives.SaveApplicationSettings();

            allowCommunication_ = false;
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;

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
            if (!FonctionsNatives.obtenirAutorisationInputClavier())
                return;

            int mode = FonctionsNatives.obtenirMode();
            switch (mode)
            {
                //Mode Menu_Principal
                case (int)Mode.MENU_PRINCIPAL:
                    break;

                //Mode Simulation
                case (int)Mode.SIMULATION:
                    gererToucheSimulation(keyDown);
                    break;

                //Mode Edition
                case (int)Mode.EDITION:
                    gererToucheEdition(keyDown);
                    break;

                //Mode Configure
                case (int)Mode.CONFIGURE:
                    break;

                //Mode Test
                case (int)Mode.TEST:
                    gererToucheTest(keyDown);
                    break;

                //Mode Personalize
                case (int)Mode.PERSONALIZE:
                    break;

                //Mode Édition Tutoriel
                case (int)Mode.TUTORIAL_EDITION:
                    gererToucheEditionTutoriel(keyDown);
                    break;

                //Mode Édition Tutoriel
                case (int)Mode.PIECES:
                    gererTouchePieces(keyDown);
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
                    else
                        editionSideMenu.teleportorObjet();
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
            if (viewPort.Controls.Contains(simulationMenuStrip.simulationTutorial))
                return;

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
        /// @fn private void gererToucheEditionTutoriel(IntPtr keyDown)
        ///
        /// Gère les touches pour le mode Édition Tutoriel
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererToucheEditionTutoriel(IntPtr keyDown)
        {
            switch ((int)keyDown)
            {
                case Constants.Key_C:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_DUPLICATE_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.duplicateTool();
                    }  
                    break;

                case Constants.Key_D:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_MOVE_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.moveTool();
                    }
                    break;

                case Constants.Key_E:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_SCALE_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.scaleTool();
                    }
                    break;

                case Constants.Key_L:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_LINE_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.lineObject();
                    }
                    break;

                case Constants.Key_M:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_WALL_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.wallObject();
                    }
                    break;

                case Constants.Key_O:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_TELEPORTOR)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.teleportorObjet();
                    }
                    break;    

                case Constants.Key_P:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_POST_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.postObject();
                    }
                    break;

                case Constants.Key_R:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_ROTATION_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.rotateTool();
                    }
                    break;

                case Constants.Key_S:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.selectTool();
                    }
                    break;

                case Constants.Key_Del:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.DELETE_TOOL)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielSideMenu.deleteTool();
                    }
                    break;

                case Constants.Key_2:
                    if (editionTutorielInstructions.GetState() == (int)EditionTutorial.State.CHANGE_VIEW)
                    {
                        editionTutorielInstructions.nextState();
                        editionTutorielMenuStrip.orbiteView();
                    }
                    break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void gererTouchePieces(IntPtr keyDown)
        ///
        /// Gère les touches pour le mode Simulation
        /// 
        /// @param IntPtr keyDown: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void gererTouchePieces(IntPtr keyDown)
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
        /// @fn private void verificationDuNombreElementChoisi ()
        ///
        /// Permet de savoir le nombre d'objet sélectionné et affiche le panneau
        /// des opérations si un objet est sélectionné
        ///
        ////////////////////////////////////////////////////////////////////////
        public void verificationDuNombreElementChoisi()
        {
            int mode = FonctionsNatives.obtenirMode();
            if (!(mode == (int)Mode.EDITION || mode == (int)Mode.TUTORIAL_EDITION))
                return;

            FonctionsNatives.assignerAutorisationInputClavier(true);
            if (mode == (int)Mode.EDITION)
            {
                int nbEnfant = FonctionsNatives.obtenirNombreSelection();
                if (nbEnfant == 1)
                {
                    editionModificationPanel.mettreAJourInformation();
                    editionModificationPanel.Visible = true;
                }
                else
                    editionModificationPanel.Visible = false;
            }
            else
            {
                int nbEnfant = FonctionsNatives.obtenirNombreSelection();
                if (nbEnfant == 1)
                {
                    editionTutorielModificationPanel.mettreAJourInformation();
                    editionTutorielModificationPanel.Visible = true;
                }
                else
                    editionTutorielModificationPanel.Visible = false;
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
            viewPort.Focus();
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
            if (Program.peutAfficher)
            {
                FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);
                FonctionsNatives.dessinerOpenGL();

                int w = viewPort.Width;
                int h = viewPort.Height;
            }
        }

        public void goOfflineEdition()
        {
            estEnPause = false;
            picturePause.Visible = false;

            editionSideMenu = new EditionSideMenu(this);
            editionMenuStrip = new EditionMenuStrip(this);
            editionModificationPanel = new EditionModificationPanel(this);

            editionSideMenu.Dock = DockStyle.Left;
            viewPort.Controls.Add(editionSideMenu);
            

            viewPort.Controls.Add(editionMenuStrip);
            editionMenuStrip.Dock = DockStyle.Top;

            editionModificationPanel.Location = new Point(viewPort.Width - editionModificationPanel.Width, editionMenuStrip.Height);
            editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            editionModificationPanel.Visible = false;
            viewPort.Controls.Add(editionModificationPanel);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();
            verificationDuNombreElementChoisi();

            FonctionsNatives.assignerMode(Mode.EDITION);
            verificationDuNombreElementChoisi();
        }

        public void goOfflineEditionTutorial()
        {
            editionTutorielSideMenu = new EditionTutorielSideMenu(this);
            editionTutorielMenuStrip = new EditionTutorielMenuStrip(this);
            editionTutorielInstructions = new EditionTutorielInstructions(this);
            editionTutorielModificationPanel = new TutorialEditionModificationPanel(this);

            editionTutorielSideMenu.Dock = DockStyle.Left;
            viewPort.Controls.Add(editionTutorielSideMenu);

            editionTutorielMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(editionTutorielMenuStrip);

            editionTutorielModificationPanel.Location = new Point(viewPort.Width - editionTutorielModificationPanel.Width, editionTutorielMenuStrip.Height);
            editionTutorielModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            editionTutorielModificationPanel.Visible = false;
            viewPort.Controls.Add(editionTutorielModificationPanel);

            viewPort.Refresh();

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);
            Program.peutAfficher = true;
            FonctionsNatives.assignerMode(Mode.TUTORIAL_EDITION);


            editionTutorielInstructions = new EditionTutorielInstructions(this);
            editionTutorielInstructions.Location = new Point(viewPort.Width / 2 - editionTutorielInstructions.Width / 2,
                                                             viewPort.Height / 2 - editionTutorielInstructions.Height / 2);
            editionTutorielInstructions.Anchor = AnchorStyles.None;
            viewPort.Controls.Add(editionTutorielInstructions);
            editionTutorielInstructions.BringToFront();
        }

        public void goOnlineEdition()
        {
            estEnPause = false;
            picturePause.Visible = false;

            editionSideMenu = new EditionSideMenu(this);
            onlineEditionMenuStrip = new OnlineEditionMenuStrip(this);
            editionModificationPanel = new EditionModificationPanel(this);

            editionSideMenu.Dock = DockStyle.Left;
            viewPort.Controls.Add(editionSideMenu);

            onlineEditionMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(onlineEditionMenuStrip);
            
            editionModificationPanel.Location = new Point(viewPort.Width - editionModificationPanel.Width, onlineEditionMenuStrip.Height);
            editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            editionModificationPanel.Visible = false;
            viewPort.Controls.Add(editionModificationPanel);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();
            verificationDuNombreElementChoisi();

            FonctionsNatives.assignerMode(Mode.EDITION);
            verificationDuNombreElementChoisi();
        }

        public void goOfflineSimulation()
        {
            simulationMenuStrip = new SimulationMenuStrip(this);
            configuration.populerToolStripProfils(simulationMenuStrip.profilsToolStripMenuItem);

            simulationMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(simulationMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();

            FonctionsNatives.assignerMode(ModeEnum.Mode.SIMULATION);
        }

        public void goOfflineSimulationTutorial()
        {
            simulationMenuStrip = new SimulationMenuStrip(this);
            simulationMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(simulationMenuStrip);

            simulationTutorial = new TutorialSimulation(this);
            simulationTutorial.Location = new Point(viewPort.Width / 2 - simulationTutorial.Width / 2,
                                                    viewPort.Height / 2 - simulationTutorial.Height / 2);

            simulationTutorial.Anchor = AnchorStyles.None;

            viewPort.Controls.Add(simulationTutorial);

            simulationTutorial.BringToFront();

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);
            FonctionsNatives.assignerMode(Mode.SIMULATION);
            Program.peutAfficher = true;
        }

        public void goOnlineSimulation()
        {
            onlineSimulationMenuStrip = new OnlineSimulationMenuStrip(this);
            configuration.populerToolStripProfils(onlineSimulationMenuStrip.profilsToolStripMenuItem);

            onlineSimulationMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(onlineSimulationMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();

            FonctionsNatives.assignerMode(ModeEnum.Mode.SIMULATION);
        }

        public void goOnlineCoin()
        {
            onlinePiecesMenuStrip = new OnlinePiecesMenuStrip(this);
            configuration.populerToolStripProfils(onlinePiecesMenuStrip.profilsToolStripMenuItem);

            onlinePiecesMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(onlinePiecesMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();

            FonctionsNatives.assignerMode(ModeEnum.Mode.PIECES);
        }

        public void goOnlineRace()
        {
            onlineRaceMenuStrip = new OnlineRaceMenuStrip(this);
            configuration.populerToolStripProfils(onlineRaceMenuStrip.profilsToolStripMenuItem);

            onlineRaceMenuStrip.Dock = DockStyle.Top;
            viewPort.Controls.Add(onlineRaceMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(viewPort.Width, viewPort.Height);

            Program.peutAfficher = true;
            viewPort.Refresh();

            //Todo change for race
            FonctionsNatives.assignerMode(ModeEnum.Mode.PIECES);
        }



        public void Test(string mapName, bool connectionState, int mode, int nbPlayers, bool isAdmin, int id)
        {
            AddMap(mapName, connectionState, mode, nbPlayers, isAdmin, id);
        }

        private delegate void CallbackForNewMap(IntPtr mapName, int mapNameSize, bool connectionState, int mode, int nbPlayers, bool isAdmin, int id);
        // Ensure it doesn't get garbage collected
        private CallbackForNewMap mInstance;
        private void addNewMap(IntPtr mapName, int mapNameSize, bool connectionState, int mode, int nbPlayers, bool isAdmin, int id)
        {
            Byte[] tmp = new Byte[mapNameSize];
            Marshal.Copy(mapName, tmp, 0, mapNameSize);
            var str = System.Text.Encoding.Default.GetString(tmp);

            MapPresentator newMap = new MapPresentator(this, str, connectionState, mode, nbPlayers, id);
            mapMenu.addOnlineMapEntry(id, newMap);
        }

        [DllImport("model.dll")]
        private static extern void SetCallbackForNewMap(CallbackForNewMap fn);

        [DllImport("model.dll")]
        private static extern void AddMap(string mapName, bool connectionState, int mode, int nbPlayers, bool isAdmin, int id);
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

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sendMessage(String message, int size);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool connectToServer(String hostName, String port);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void createProfile(String profileName);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void authenticate(String profileName);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void disconnectFromServer();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool isConnected();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool createMap(String mapName, int mapNamesize, String password, int passwordSize, char mapType, char isPrivate);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool joinMap(int mapId);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool leaveMap();

        [DllImport(@"model.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void obtenirCheminFichierZoneDefaut(StringBuilder str, int longueur);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LoadApplicationSettings();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SaveApplicationSettings();
    }
}
