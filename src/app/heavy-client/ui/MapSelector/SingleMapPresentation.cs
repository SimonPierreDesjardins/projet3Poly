////////////////////////////////////////////////
/// @file   MapPresentator.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class MapPresentator : UserControl
    {
        Window parent_;
        private string mapName_;
        private bool connectionState_;
        private bool confidentiality_;
        private int modeType_;
        private int numberOfPlayers_;
        private int mapId_;

        public string pathToFile_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MapPresentator(Window parent, String mapName, bool connectionState, int modeType, int numberOfPlayers, int id)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// @param String mapName: nom de la map
        /// @param bool connectionState: true si enligne, sinon false
        /// @param int modeType: Le mode dans lequel la map est
        /// @param int numberOfPlayers: le nombre de joueur dans la map
        /// @param int id: numero unique pour les maps enligne
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

                case (int)ModeEnum.Mode.PIECES:
                    ModeLabel.Text = "Collection Pièces";
                    break;

                default:
                    ModeLabel.Text = "Edition / Simulation";
                    break;
            }

            if (connectionState_)
                connectionLabel.Text = "Enligne";
            else
                connectionLabel.Text = "Hors Ligne";

            confidentiality_ = false;
            if (confidentiality_)
                privacyLabel.Text = "Publique";
            else
                privacyLabel.Text = "Privée";

            NameMapLabel.Text = mapName_;
            numberOfPlayersLabel.Text = numberOfPlayers_.ToString();

            //Lovely circles as char in password
            passwordBox.PasswordChar = '\u25CF';
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mapButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Assigne le mode, si la carte est en ligne, selon le mode de la carte.
        /// Si la carte est hors ligne, l'utilisateur a le choix entre le mode
        /// edition ou simulation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
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

                case (int)ModeEnum.Mode.PIECES:
                    loadOnlinePieceMode();
                    break;

                default:
                    parent_.mapMenu.choseOfflineMode(this);
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn internal void setPath(string path)
        ///
        /// Assigne le chemin vers le fichier contenant les informations de sauvegarde
        /// de la map
        /// 
        /// @param string path: Chemin vers le fichier
        ///
        ////////////////////////////////////////////////////////////////////////
        internal void setPath(string path)
        {
            pathToFile_ = path;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void loadOnlineSimulationMode()
        ///
        /// Assigne le mode de simulation pour une carte enligne et change le ui
        /// pour aller en simulation
        ///
        ////////////////////////////////////////////////////////////////////////
        private void loadOnlineSimulationMode()
        {
            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            parent_.mapMenu.defaultView();

            parent_.goOnlineSimulation();

            if (connectionState_)
            {
                FonctionsNatives.joinMap(mapId_);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void loadOnlineEditionMode()
        ///
        /// Assigne le mode de edition pour une carte enligne et change le ui
        /// pour aller en edition
        ///
        ////////////////////////////////////////////////////////////////////////
        private void loadOnlineEditionMode()
        {
            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            parent_.mapMenu.defaultView();

            parent_.goOnlineEdition();

            if (connectionState_)
            {
                FonctionsNatives.joinMap(mapId_);
            }
        }


        private void loadOnlinePieceMode()
        {
            FonctionsNatives.assignerCheminFichierZone(pathToFile_);
            FonctionsNatives.charger();

            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            parent_.mapMenu.defaultView();

            parent_.goOnlineCoin();
        }

        private void publicCheckBox_Click(object sender, EventArgs e)
        {
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
        }

        private void privateCheckBox_Click(object sender, EventArgs e)
        {
            publicCheckBox.Checked = false;
            privateCheckBox.Checked = true;
        }
    }
}
