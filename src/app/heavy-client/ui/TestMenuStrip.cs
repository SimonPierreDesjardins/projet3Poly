using System;
using System.Windows.Forms;
using ModeEnum;

namespace ui
{
    public partial class TestMenuStrip : UserControl
    {
        Window parent_;

        public TestMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            menuStrip1.Visible = false;
            crochetPourVue();
        }

        private void menuEditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goModeEdition();            
        }

        public void goModeEdition()
        {
            parent_.estEnPause = false;
            parent_.picturePause.Visible = false;

            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionSideMenu = new EditionSideMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.testMenuStrip);
            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            FonctionsNatives.assignerMode(Mode.EDITION);
            parent_.verificationDuNombreElementChoisi();
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goMenuPrincipal();
        }

        public void goMenuPrincipal()
        {
            parent_.estEnPause = false;
            parent_.picturePause.Visible = false;

            parent_.mainMenu = new MainMenu(parent_);
            parent_.viewPort.Controls.Remove(parent_.testMenuStrip);
            parent_.mainScreen.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = false;
            Program.peutAfficher = false;

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orthoView();
        }

        public void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orbiteView();
        }

        public void orbiteView()
        {
            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
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

        public void goIntoPause()
        {
            parent_.estEnPause = !parent_.estEnPause;
            parent_.picturePause.Visible = parent_.estEnPause;
            menuStrip1.Visible = parent_.estEnPause;
        }
    }
}
