////////////////////////////////////////////////
/// @file   TestMenuStrip.cs
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
    public partial class TestMenuStrip : SimMenuStrip
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public TestMenuStrip(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public TestMenuStrip(Window parent) : base(parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            menuStrip1.Visible = false;
            crochetPourVue();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuEditionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode édition
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuEditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goModeEdition();            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goModeEdition()
        ///
        /// Cette fonction enlève les composantes du mode test, ajoute ceux du
        /// du mode édition et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        override public void goModeEdition()
        {
            parent_.configuration.deallocateCurrentProfilToolStrip();
            parent_.estEnPause = false;
            parent_.picturePause.Visible = false;

            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionModificationPanel = new EditionModificationPanel(parent_);

            parent_.editionSideMenu.Dock = DockStyle.Left;
            parent_.viewPort.Controls.Add(parent_.editionSideMenu);


            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            parent_.editionModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionModificationPanel.Width, 
                                                                    parent_.editionMenuStrip.Height);
            parent_.editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionModificationPanel);

            parent_.viewPort.Refresh();
            parent_.verificationDuNombreElementChoisi();
            parent_.viewPort.Controls.Remove(parent_.testMenuStrip);

            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            FonctionsNatives.assignerMode(ModeEnum.Mode.EDITION);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goMenuPrincipal();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goMenuPrincipal()
        ///
        /// Cette fonction enlève les composantes du mode test, ajoute ceux du
        /// du mode principal et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        override public void goMenuPrincipal()
        {
            base.goMenuPrincipal();
            parent_.viewPort.Controls.Remove(parent_.testMenuStrip);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue orthographique
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
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
        /// Assigne un crochet dans le menuStrip selon la vue utilisée
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void crochetPourVue()
        {
            switch (FonctionsNatives.obtenirTypeVue())
            {
                case 1:
                    orbiteToolStripMenuItem.Checked = true;
                    orthoToolStripMenuItem.Checked = false;
                    break;

                case 0:
                default:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = true;
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goIntoPause()
        ///
        /// Cette fonction change l'état de la valeure estEnPause et change la
        /// visibilité de l'image pause et du menuStrip en conséquence
        ///
        ////////////////////////////////////////////////////////////////////////
        override public void goIntoPause()
        {
            base.goIntoPause();
            parent_.picturePause.Visible = parent_.estEnPause;
            menuStrip1.Visible = parent_.estEnPause;
        }
    }
}
