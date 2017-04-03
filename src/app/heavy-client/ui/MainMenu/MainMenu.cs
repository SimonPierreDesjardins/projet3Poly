////////////////////////////////////////////////
/// @file   MainMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using ModeEnum;
using System.Drawing;

namespace ui
{
    public partial class MainMenu : UserControl
    {
        Window parent_;
        ConnectToServer connectOptions_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MainMenu(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public MainMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            if (FonctionsNatives.isConnected())
            {
                connexionPictureBox.Image = ChangeColor((Bitmap)connexionPictureBox.Image, Color.Green);
            } 
            else
            {
                connexionPictureBox.Image = ChangeColor((Bitmap)connexionPictureBox.Image, Color.Red);
            }

            this.Width = 0;
            ShowMenuTimer.Start();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_mapsButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction permet de voir les cartes disponnible hors ligne et enligne
        /// sur l"application. Enleve les controles du menu principale
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_mapsButton_Click(object sender, EventArgs e)
        {
            animationChangingMenu();
            //Adds offline maps to dictionary
            ExplorateurOuverture explorateur = new ExplorateurOuverture(parent_);

            parent_.mapMenu.Dock = DockStyle.Fill;
            parent_.mapMenu.initMapList();
            parent_.viewPort.Controls.Add(parent_.mapMenu);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_PersoButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction enlève les composantes du mode principal, ajoute ceux du
        /// du mode personnalisation et change de mode.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_PersoButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerCheminFichierZone(parent_.PathToDefaultZone_);
            FonctionsNatives.charger();

            animationChangingMenu();
            parent_.personnalisationSideMenu = new PersonnalisationSideMenu(parent_);

            parent_.viewPort.Controls.Add(parent_.personnalisationSideMenu);
            parent_.personnalisationSideMenu.Dock = DockStyle.Left;

            Program.peutAfficher = true;

            FonctionsNatives.assignerMode(Mode.PERSONALIZE);
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_ConfigurationButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction ouvre une nouvelle fenetre qui permet a l'utilisateur de configurer
        /// son robot et les touches utiliser.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_ConfigurationButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerMode(Mode.CONFIGURE);
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            parent_.configuration.ShowDialog();
            parent_.viewPort.Focus();
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_ConnexionButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction enleve les controles de mode principale et ajoute les controles
        /// pour permettre a l'utilisateur de se connecter au server.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_ConnexionButton_Click(object sender, EventArgs e)
        {
            animationChangingMenu();
            connectOptions_ = new ConnectToServer(parent_);
            parent_.viewPort.Controls.Add(connectOptions_);
            connectOptions_.Location = new Point( (parent_.viewPort.Width + parent_.mainMenu.Width) / 2 - connectOptions_.Width / 2,
                                                   parent_.viewPort.Height / 2 - connectOptions_.Height / 2);
            connectOptions_.Dock = DockStyle.Fill;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_QuitButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction termine l'application
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_QuitButton_Click(object sender, EventArgs e)
        {
            parent_.configuration.Dispose();
            Application.Exit();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void animationChangingMenu()
        ///
        /// Cache le menu principal, attend qu'il soit disparu et l'enlève de la fenete
        /// avant de sortir de la fonction.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void animationChangingMenu()
        {
            ShowMenuTimer.Stop();
            HideMenuTimer.Start();
            while (HideMenuTimer.Enabled)
            {
                Application.DoEvents();
            }
            parent_.viewPort.Controls.Remove(parent_.mainMenu);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ShowMenuTimer_Tick(object sender, EventArgs e)
        ///
        /// Montre le menu principal lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ShowMenuTimer_Tick(object sender, EventArgs e)
        {
            if (this.Width >= 200)
            {
                ShowMenuTimer.Stop();
            }
            else
                this.Width += 5;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void HideMenuTimer_Tick(object sender, EventArgs e)
        ///
        /// Cache le menu principal lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
        private void HideMenuTimer_Tick(object sender, EventArgs e)
        {
            if (this.Width > 0)
                this.Width -= 5;
            else
                HideMenuTimer.Stop();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        ///
        /// Change la couleur d'un image par une nouvelle couleur.
        /// 
        /// @param Bitmap scrBitmap: le bitmap de l'image qui doit être modifié
        /// @param Color newColor: La nouvelle couleur de l'image
        ///
        ////////////////////////////////////////////////////////////////////////
        public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        {
            Color actualColor;
            //make an empty bitmap the same size as scrBitmap
            Bitmap newBitmap = new Bitmap(scrBitmap.Width, scrBitmap.Height);
            for (int i = 0; i < scrBitmap.Width; i++)
            {
                for (int j = 0; j < scrBitmap.Height; j++)
                {
                    //get the pixel from the scrBitmap image
                    actualColor = scrBitmap.GetPixel(i, j);
                    // > 150 because.. Images edges can be of low pixel colr. if we set all pixel color to new then there will be no smoothness left.
                    if (actualColor.A > 175)
                        newBitmap.SetPixel(i, j, newColor);
                    //else
                        //newBitmap.SetPixel(i, j, actualColor);
                }
            }
            return newBitmap;
        }

        private void mainMenu_TutoEditionButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerCheminFichierZone(parent_.PathToDefaultZone_);
            FonctionsNatives.charger();

            animationChangingMenu();

            parent_.goOfflineEditionTutorial();
        }

        private void mainMenu_TutoSimulationButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerCheminFichierZone(parent_.PathToDefaultZone_);
            FonctionsNatives.charger();

            animationChangingMenu();

            parent_.goOfflineSimulationTutorial();
        }
    }
}
