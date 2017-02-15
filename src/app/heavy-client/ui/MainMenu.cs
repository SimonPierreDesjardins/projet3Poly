﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ModeEnum;

namespace ui
{
    public partial class MainMenu : UserControl
    {
        Window parent_;
        private bool PasserEnSimulation = false;

        public MainMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            this.Width = 0;
            ShowMenuTimer.Start();
        }

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
                PasserEnSimulation = true;
            }
            if (dialogresult == DialogResult.Cancel)
                PasserEnSimulation = false;

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

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

        private void ShowMenuTimer_Tick(object sender, EventArgs e)
        {
            if (this.Width >= 200)
                ShowMenuTimer.Stop();
            else
                this.Width += 5;
        }

        private void HideMenuTimer_Tick(object sender, EventArgs e)
        {
            if (this.Width > 0)
                this.Width -= 5;
            else
                HideMenuTimer.Stop();
        }
    }
}