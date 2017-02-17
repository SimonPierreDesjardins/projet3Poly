////////////////////////////////////////////////
/// @file   MainMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using ModeEnum;

namespace ui
{
    public partial class MainMenu : UserControl
    {
        Window parent_;
        private bool PasserEnSimulation = false;

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

            this.Width = 0;
            ShowMenuTimer.Start();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_SimulationButton_Click(object sender, EventArgs e)
        ///
        /// Ouvrir une fenêtre permettant a l'usager de choisir une zone. Si une zone est
        /// choisi, cette fonction enlève les composantes du mode principal, ajoute ceux du
        /// du mode simulation et change de mode. Sinon rien.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_SimulationButton_Click(object sender, EventArgs e)
        {
            ouvrirZone(true);

            if (PasserEnSimulation)
            {
                animationChangingMenu();
                parent_.simulationMenuStrip = new SimulationMenuStrip(parent_);
                parent_.configuration.populerToolStripProfils(parent_.simulationMenuStrip.profilsToolStripMenuItem);
                parent_.viewPort.Controls.Add(parent_.simulationMenuStrip);
                parent_.simulationMenuStrip.Dock = DockStyle.Top;

                FonctionsNatives.assignerVueOrtho();
                FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
                FonctionsNatives.assignerMode(Mode.SIMULATION);

                parent_.viewPort.Visible = true;
                Program.peutAfficher = true;
            }
            parent_.viewPort.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirZone(bool afficherZoneDefaut)
        ///
        /// Ouvre un explorateur de ficher pour charger la zone sauvegarder lorsque 
        /// le bouton ouvrir est appuyer sur le menu
        /// 
        /// @param bool afficherZoneDefaut: bool qui indique si la fenetre affiche
        ///                                 la zone par defaut
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
                PasserEnSimulation = true;
            }
            if (dialogresult == DialogResult.Cancel)
                PasserEnSimulation = false;

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mainMenu_EditionButton_Click(object sender, EventArgs e)
        ///
        /// Cette fonction enlève les composantes du mode principal, ajoute ceux du
        /// du mode edition et change de mode.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mainMenu_EditionButton_Click(object sender, EventArgs e)
        {
            animationChangingMenu();
            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            parent_.viewPort.Visible = true;
            Program.peutAfficher = true;

            FonctionsNatives.assignerMode(Mode.EDITION);
            parent_.verificationDuNombreElementChoisi();
        }

        private void mainMenu_JeuxButton_Click(object sender, EventArgs e)
        {
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
            animationChangingMenu();
            parent_.personnalisationSideMenu = new PersonnalisationSideMenu(parent_);

            parent_.viewPort.Controls.Add(parent_.personnalisationSideMenu);
            parent_.personnalisationSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = true;
            Program.peutAfficher = true;

            FonctionsNatives.assignerMode(Mode.PERSONALIZE);
        }

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
            parent_.mainScreen.Controls.Remove(parent_.mainMenu);
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
                ShowMenuTimer.Stop();
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
    }
}
