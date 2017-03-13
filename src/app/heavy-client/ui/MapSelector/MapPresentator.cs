////////////////////////////////////////////////
/// @file   MapPresentator.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////

using System;
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
            //Check for offline or online
            //Add function to send id_ somewhere

            FonctionsNatives.assignerCheminFichierZone(pathToFile_);
            FonctionsNatives.charger();

            parent_.simulationMenuStrip = new SimulationMenuStrip(parent_);
            parent_.configuration.populerToolStripProfils(parent_.simulationMenuStrip.profilsToolStripMenuItem);

            parent_.viewPort.Controls.Remove(parent_.mapMenu);

            parent_.simulationMenuStrip.Dock = DockStyle.Top;
            parent_.viewPort.Controls.Add(parent_.simulationMenuStrip);
            
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            FonctionsNatives.assignerMode(ModeEnum.Mode.SIMULATION);

            Program.peutAfficher = true;
        }

        internal void setPath(string path)
        {
            pathToFile_ = path;
        }
    }
}
