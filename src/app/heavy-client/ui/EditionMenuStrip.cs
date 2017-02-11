using System;
using System.Windows.Forms;
using ModeEnum;
using System.Drawing;

namespace ui
{
    public partial class EditionMenuStrip : UserControl
    {
        Window parent_;

        public EditionMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            crochetPourVue();
            enregistrerToolStripMenuItem.Enabled = false;
        }

        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
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

        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
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
        public void ouvrirZone(bool afficherZoneDefaut)
        {
            ExplorateurOuverture explorateur = new ExplorateurOuverture(afficherZoneDefaut);
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

        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            enregistrer();
        }

        public void enregistrer()
        {
            FonctionsNatives.sauvegarder();
        }

        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
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

        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goTestMode();
        }

        public void goTestMode()
        {
            parent_.testMenuStrip = new TestMenuStrip(parent_);

            parent_.configuration.populerToolStripProfils(parent_.testMenuStrip.profilsToolStripMenuItem);
            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Refresh();

            parent_.viewPort.Controls.Add(parent_.testMenuStrip);
            parent_.testMenuStrip.Dock = DockStyle.Top;
            
            FonctionsNatives.assignerMode(Mode.TEST);
        }

        private void menuprincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goMenuPrincipal();
        }

        public void goMenuPrincipal()
        {
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.mainScreen.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = false;
            Program.peutAfficher = false;

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orthoView();
        }

        public void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            crochetPourVue();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orbiteView();
        }

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
    }
}
