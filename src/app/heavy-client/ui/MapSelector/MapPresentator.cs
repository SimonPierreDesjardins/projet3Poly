////////////////////////////////////////////////
/// @file   MapPresentator.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class MapPresentator : UserControl
    {
        Window parent_;
        private string mapName_;
        private bool connectionState_;
        private int modeType_;
        private int numberOfPlayers_;
        private int mapId_;

        public string pathToFile_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MapPresentator(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public MapPresentator(Window parent, String mapName, bool connectionState, int modeType, int numberOfPlayers, int id)
        {
            InitializeComponent();
            parent_ = parent;

            mapName_ = mapName;
            modeType_ = modeType;
            connectionState_ = connectionState;
            numberOfPlayers_ = numberOfPlayers;
            mapId_ = id;

            switch(modeType_)
            {
                case (int)ModeEnum.Mode.SIMULATION:
                    ModeLabel.Text = "Simulation";
                    break;

                case (int)ModeEnum.Mode.EDITION:
                    ModeLabel.Text = "Edition";
                    break;

                default:
                    ModeLabel.Text = "Edition / Simulation";
                    break;
            }

            if (connectionState_)
                connectionLabel.Text = "Enligne";
            else
                connectionLabel.Text = "Hors Ligne";

            NameMapLabel.Text = mapName_;
            numberOfPlayersLabel.Text = numberOfPlayers_.ToString();
        }

        private void mapButton_Click(object sender, EventArgs e)
        {
            switch (modeType_)
            {
                case (int)ModeEnum.Mode.SIMULATION:
                    loadOnlineSimulationMode();
                    break;

                case (int)ModeEnum.Mode.EDITION:
                    loadOnlineEditionMode();
                    break;

                default:
                    parent_.mapMenu.choseOfflineMode(this);
                    break;
            }
        }

        internal void setPath(string path)
        {
            pathToFile_ = path;
        }

        public void loadOnlineSimulationMode()
        {
            parent_.simulationMenuStrip = new SimulationMenuStrip(parent_);
            parent_.configuration.populerToolStripProfils(parent_.simulationMenuStrip.profilsToolStripMenuItem);

            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            parent_.mapMenu.defaultView();

            parent_.simulationMenuStrip.Dock = DockStyle.Top;
            parent_.viewPort.Controls.Add(parent_.simulationMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            Program.peutAfficher = true;

            if (connectionState_)
            {
                FonctionsNatives.joinMap(mapId_);
            }
        }

        public void loadOnlineEditionMode()
        {
            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionModificationPanel = new EditionModificationPanel(parent_);

            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            parent_.mapMenu.defaultView();

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            parent_.editionModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionModificationPanel.Width,
                                                                  parent_.editionMenuStrip.Height);
            parent_.editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionModificationPanel);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            Program.peutAfficher = true;
            parent_.verificationDuNombreElementChoisi();

            if (connectionState_)
            {
                FonctionsNatives.joinMap(mapId_);
            }
        }
    }
}
