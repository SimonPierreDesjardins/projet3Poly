////////////////////////////////////////////////
/// @file   OnlineEditionMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-03-29
///
////////////////////////////////////////////////
using System;
using System.Drawing;

namespace ui
{
    public partial class OnlineEditionMenuStrip : EditMenuStrip
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public OnlineEditionMenuStrip(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public OnlineEditionMenuStrip(Window parent) : base(parent)
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

        private void modePiècesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            parent_.viewPort.Controls.Remove(this);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);

            parent_.goOnlineCoin();

        }

        private void modeSimulationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Focus();
            parent_.viewPort.Controls.Remove(this);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionModificationPanel);

            parent_.goOnlineSimulation();
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
            parent_.viewPort.Controls.Remove(this);
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
