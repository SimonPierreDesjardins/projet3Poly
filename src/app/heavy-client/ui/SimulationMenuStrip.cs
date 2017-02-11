using System;
using System.Windows.Forms;
using ModeEnum;

namespace ui
{
    public partial class SimulationMenuStrip : UserControl
    {
        Window parent_;

        public SimulationMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            menuStrip1.Visible = false;
            crochetPourVue();
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

            parent_.configuration.deallocateCurrentProfilToolStrip();
            parent_.viewPort.Controls.Remove(parent_.simulationMenuStrip);

            parent_.mainScreen.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = false;
            Program.peutAfficher = false;

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //if (tempItemEdition != null)
            //    tempItemEdition.Checked = false;

            //orthographiqueMenuEdition_.Checked = true;
            //tempItemEdition = orthographiqueMenuEdition_;

            orthoView();

            //outilsZoom_.Enabled = true;
            //zoomToolStripMenuItem.Enabled = true;
        }

        public void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /*if (tempItemEdition != null)
                tempItemEdition.Checked = false;
            else
                orthographiqueMenuEdition_.Checked = false;

            orbiteMenuEdition_.Checked = true;
            tempItemEdition = orbiteMenuEdition_;*/

            orbiteView();

            //outilsZoom_.Enabled = false;
            //zoomToolStripMenuItem.Enabled = false;
        }

        public void orbiteView()
        {
            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        private void premierePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /*if (tempItemSimTest != null)
                tempItemSimTest.Checked = false;
            else
                orthographiqueMenuSimTest.Checked = false;*/


            //orbiteMenuSimTest.Checked = true;
            //tempItemSimTest = orbiteMenuSimTest;

            firstPersonView();

            //outilsZoom_.Enabled = false;
            //zoomToolStripMenuItem.Enabled = false;
        }

        public void firstPersonView()
        {
            FonctionsNatives.assignerVuePremierePersonne();
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
                case 2:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = false;
                    premierePersonneToolStripMenuItem.Checked = true;
                    break;
                case 1:
                    orbiteToolStripMenuItem.Checked = true;
                    orthoToolStripMenuItem.Checked = false;
                    premierePersonneToolStripMenuItem.Checked = false;
                    break;

                case 0:
                default:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = true;
                    premierePersonneToolStripMenuItem.Checked = false;
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
