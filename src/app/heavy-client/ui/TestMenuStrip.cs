using System;
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
    public partial class TestMenuStrip : UserControl
    {
        Window parent_;

        public TestMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
        }

        private void menuEditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionSideMenu = new EditionSideMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.testMenuStrip);
            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;
            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            //outilsZoom_.Enabled = true;
            //zoomToolStripMenuItem.Enabled = true;

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            //afficherMenuPrincipal(false);
            //afficherMenuEdition(true);
            //panneauOperation_.Visible = false;

            FonctionsNatives.assignerMode(Mode.EDITION);
            parent_.verificationDuNombreElementChoisi();
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
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
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }
    }
}
