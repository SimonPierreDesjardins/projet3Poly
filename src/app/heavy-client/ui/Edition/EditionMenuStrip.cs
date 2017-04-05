////////////////////////////////////////////////
/// @file   EditionMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using System.Drawing;

namespace ui
{
    public partial class EditionMenuStrip : EditMenuStrip
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
        public EditionMenuStrip(Window parent) : base(parent)
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
        override public void nouvelleZone()
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
        override public void ouvrirZone(bool afficherZoneDefaut)
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

        override public bool canSave()
        {
            return enregistrerToolStripMenuItem.Enabled;
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
        override public bool enregistrerSousZone()
        {
            if (base.enregistrerSousZone())
                enregistrerToolStripMenuItem.Enabled = true;

            return true;
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
        override public void goTestMode()
        {
            parent_.testMenuStrip = new TestMenuStrip(parent_);

            parent_.configuration.populerToolStripProfils(parent_.testMenuStrip.profilsToolStripMenuItem);
            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);
            parent_.viewPort.Refresh();

            parent_.viewPort.Controls.Add(parent_.testMenuStrip);
            parent_.testMenuStrip.Dock = DockStyle.Top;
            
            FonctionsNatives.assignerMode(ModeEnum.Mode.TEST);
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
        override public void goMenuPrincipal()
        {
            base.goMenuPrincipal();
            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void vuesToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Donne le focus au menustrip lorsqu'il est appuyer
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
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
        override public void orthoView()
        {
            base.orthoView();
            crochetPourVue();
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
        override public void orbiteView()
        {
            base.orbiteView();
            crochetPourVue();
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void informationsToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Donne le focus au menustrip lorsqu'il est appuyer
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
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
            helpPopUp();
        }
    }
}
