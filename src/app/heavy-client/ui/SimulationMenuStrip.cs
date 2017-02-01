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
    public partial class SimulationMenuStrip : UserControl
    {
        Window parent_;

        public SimulationMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            parent_.mainMenu = new MainMenu(parent_);
            parent_.viewPort.Controls.Remove(parent_.simulationMenuStrip);
            parent_.viewPort.Controls.Add(parent_.mainMenu);

            Program.peutAfficher = false;
            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //if (tempItemEdition != null)
            //    tempItemEdition.Checked = false;

            //orthographiqueMenuEdition_.Checked = true;
            //tempItemEdition = orthographiqueMenuEdition_;

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            //outilsZoom_.Enabled = true;
            //zoomToolStripMenuItem.Enabled = true;
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /*if (tempItemEdition != null)
                tempItemEdition.Checked = false;
            else
                orthographiqueMenuEdition_.Checked = false;

            orbiteMenuEdition_.Checked = true;
            tempItemEdition = orbiteMenuEdition_;*/

            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            //outilsZoom_.Enabled = false;
            //zoomToolStripMenuItem.Enabled = false;
        }

        private void premierePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /*if (tempItemSimTest != null)
                tempItemSimTest.Checked = false;
            else
                orthographiqueMenuSimTest.Checked = false;*/


            //orbiteMenuSimTest.Checked = true;
            //tempItemSimTest = orbiteMenuSimTest;

            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            //outilsZoom_.Enabled = false;
            //zoomToolStripMenuItem.Enabled = false;
        }
    }
}
