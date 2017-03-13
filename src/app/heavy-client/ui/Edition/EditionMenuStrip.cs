﻿////////////////////////////////////////////////
/// @file   EditionMenuStrip.cs
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
    public partial class EditionMenuStrip : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EditionMenuStrip(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public EditionMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            crochetPourVue();
            enregistrerToolStripMenuItem.Enabled = false;
        }

        private void fichierToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de nouvelleZone
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            nouvelleZone();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void nouvelleZone()
        ///
        /// Crée une nouvelle zone de céation si l'utilisateur appuie sur oui, 
        /// sinon ne fait rien
        ///
        ////////////////////////////////////////////////////////////////////////
        public void nouvelleZone()
        {
            DialogResult dialogResult = MessageBox.Show("Êtes-vous sure de vouloir créer une nouvelle épreuve", "Creation d'une nouvelle zone", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                FonctionsNatives.nouvelleTable();
                enregistrerToolStripMenuItem.Enabled = false;
                parent_.verificationDuNombreElementChoisi();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de ouvrirZone
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
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
        public void ouvrirZone(bool afficherZoneDefaut)
        {
            ExplorateurOuverture explorateur = new ExplorateurOuverture(parent_);
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);

            DialogResult dialogresult = explorateur.ShowDialog();
            if (dialogresult == DialogResult.OK)
            {
                FonctionsNatives.assignerCheminFichierZone(explorateur.cheminFichier);
                FonctionsNatives.charger();
                enregistrerToolStripMenuItem.Enabled = true;
            }

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
            parent_.verificationDuNombreElementChoisi();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de enregistrer
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            enregistrer();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrer()
        ///
        /// Permet de sauvegarde la zone dans la derniere zone ouverte ou enregistrer sous
        ///
        ////////////////////////////////////////////////////////////////////////
        public void enregistrer()
        {
            FonctionsNatives.sauvegarder();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de enregistrerSous
        ///
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
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
        public void enregistrerSousZone()
        {
            ExplorateurSauvegarde explorateur = new ExplorateurSauvegarde();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            if (explorateur.ShowDialog() == DialogResult.OK)
            {
                FonctionsNatives.assignerCheminFichierZone(explorateur.CheminFichier);
                FonctionsNatives.sauvegarder();
                enregistrerToolStripMenuItem.Enabled = true;
            }
            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode test
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            goTestMode();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goTestMode()
        ///
        /// Cette fonction enlève les composantes du mode édition, ajoute ceux du
        /// du mode test et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goTestMode()
        {
            parent_.testMenuStrip = new TestMenuStrip(parent_);

            parent_.configuration.populerToolStripProfils(parent_.testMenuStrip.profilsToolStripMenuItem);
            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);
            parent_.viewPort.Refresh();

            parent_.viewPort.Controls.Add(parent_.testMenuStrip);
            parent_.testMenuStrip.Dock = DockStyle.Top;
            
            FonctionsNatives.assignerMode(Mode.TEST);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuprincipalToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuprincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            goMenuPrincipal();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goMenuPrincipal()
        ///
        /// Cette fonction enlève les composantes du mode édition, ajoute ceux du
        /// du mode principal et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goMenuPrincipal()
        {
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);
            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void vuesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue orthographique
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            orthoView();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void orthoView()
        ///
        /// Cette fonction assigne la vue orthographique et change les crochets
        /// pour la vue dans le menuStrip
        ///
        ////////////////////////////////////////////////////////////////////////
        public void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            crochetPourVue();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue orbite
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            orbiteView();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void orbiteView()
        ///
        /// Cette fonction assigne la vue orbite et change les crochets
        /// pour la vue dans le menuStrip
        ///
        ////////////////////////////////////////////////////////////////////////
        public void orbiteView()
        {
            FonctionsNatives.assignerVueOrbite();
            crochetPourVue();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void crochetPourVueEdition()
        ///
        /// Gère l'évènement de changement de visibilité de la barre de menu édition.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void crochetPourVue()
        {
            Bitmap bmp;
            switch (FonctionsNatives.obtenirTypeVue())
            {
                case 1:
                    orbiteToolStripMenuItem.Checked = true;
                    orthoToolStripMenuItem.Checked = false;

                    bmp = (Bitmap)parent_.editionSideMenu.zoomPictureBox.Image;
                    bmp = parent_.editionSideMenu.ChangeColor(bmp, Color.Gray);
                    parent_.editionSideMenu.zoomPictureBox.Image = bmp;
                    parent_.editionSideMenu.zoomToolButton.Enabled = false;
                    break;

                case 0:
                default:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = true;

                    bmp = (Bitmap)parent_.editionSideMenu.zoomPictureBox.Image;
                    bmp = parent_.editionSideMenu.ChangeColor(bmp, Color.White);
                    parent_.editionSideMenu.zoomPictureBox.Image = bmp;
                    parent_.editionSideMenu.zoomToolButton.Enabled = true;
                    break;
            }
        }

        private void informationsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Affiche le fenêtre d'aide qui décrit les shortcuts pour chaque outil
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PopOutInterface popup = new PopOutInterface();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            DialogResult dialogresult = popup.ShowDialog();
            if (dialogresult == DialogResult.OK || dialogresult == DialogResult.Cancel)
            {
                popup.Dispose();
                parent_.viewPort.Focus();
            }
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        private void tutorielToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            parent_.editionTutorielMenuStrip = new EditionTutorielMenuStrip(parent_);
            parent_.editionTutorielSideMenu = new EditionTutorielSideMenu(parent_);
            parent_.editionTutorielInstructions = new EditionTutorielInstructions(parent_);
            parent_.editionTutorielModificationPanel = new TutorialEditionModificationPanel(parent_);

            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);

            parent_.viewPort.Controls.Add(parent_.editionTutorielSideMenu);
            parent_.editionTutorielSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionTutorielMenuStrip);
            parent_.editionTutorielMenuStrip.Dock = DockStyle.Top;

            parent_.editionTutorielModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionTutorielModificationPanel.Width,
                                                                  parent_.editionMenuStrip.Height);
            parent_.editionTutorielModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionTutorielModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionTutorielModificationPanel);

            parent_.viewPort.Refresh();

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            FonctionsNatives.assignerMode(Mode.TUTORIAL_EDITION);

            parent_.editionTutorielInstructions = new EditionTutorielInstructions(parent_);
            parent_.editionTutorielInstructions.Location = new Point(parent_.viewPort.Width / 2 - parent_.editionTutorielInstructions.Width / 2,
                                                                    parent_.viewPort.Height / 2 - parent_.editionTutorielInstructions.Height / 2);
            parent_.editionTutorielInstructions.Anchor = AnchorStyles.None;
            parent_.viewPort.Controls.Add(parent_.editionTutorielInstructions);
            parent_.editionTutorielInstructions.BringToFront();
        }
    }
}
