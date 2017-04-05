////////////////////////////////////////////////
/// @file   EditionMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Drawing;

namespace ui
{
    public partial class EditionTutorielMenuStrip : EditMenuStrip
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
        public EditionTutorielMenuStrip(Window parent) : base(parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            crochetPourVue();
            enregistrerToolStripMenuItem.Enabled = false;

            disableAllControls();
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
            base.orbiteView();
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

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.CHANGE_VIEW)
                parent_.editionTutorielInstructions.nextState();
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

                    bmp = (Bitmap)parent_.editionTutorielSideMenu.zoomPictureBox.Image;
                    bmp = parent_.editionTutorielSideMenu.ChangeColor(bmp, Color.Gray);
                    parent_.editionTutorielSideMenu.zoomPictureBox.Image = bmp;
                    parent_.editionTutorielSideMenu.zoomToolButton.Enabled = false;
                    break;

                case 0:
                default:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = true;

                    bmp = (Bitmap)parent_.editionTutorielSideMenu.zoomPictureBox.Image;
                    bmp = parent_.editionTutorielSideMenu.ChangeColor(bmp, Color.White);
                    parent_.editionTutorielSideMenu.zoomPictureBox.Image = bmp;
                    parent_.editionTutorielSideMenu.zoomToolButton.Enabled = true;
                    break;
            }
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
            base.helpPopUp();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void disableAllControls()
        ///
        /// Désactive toutes les controls sur le userControl
        ///
        ////////////////////////////////////////////////////////////////////////
        public void disableAllControls()
        {
            fichierToolStripMenuItem.Enabled = false;
            vuesToolStripMenuItem.Enabled = false;
            informationsToolStripMenuItem.Enabled = false;
        }
    }
}
