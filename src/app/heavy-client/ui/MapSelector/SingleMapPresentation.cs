﻿////////////////////////////////////////////////
/// @file   MapPresentator.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Runtime.InteropServices;
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
        private bool isAdmin_;

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
        public MapPresentator(Window parent, String mapName, bool connectionState, int modeType, 
                                int numberOfPlayers, int id, bool isAdmin, bool isPrivate)
        {
            InitializeComponent();
            parent_ = parent;

            mapName_ = mapName;
            connectionState_ = connectionState;
            modeType_ = modeType;
            numberOfPlayers_ = numberOfPlayers;
            mapId_ = id;
            isAdmin_ = isAdmin;
            confidentiality_ = isPrivate;

            switch (modeType_)
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

            if (confidentiality_)
            {
                privacyLabel.Text = "Privée";
                privateSettings();
            }
            else
            {
                privacyLabel.Text = "Publique";
                publicSettings();
            }

            if (isAdmin_)
            {
                settingsButton.Visible = true;
            }
            else
            {
                settingsButton.Visible = false;
            }
                
            NameMapLabel.Text = mapName_;
            numberOfPlayersLabel.Text = numberOfPlayers_.ToString();

            //Lovely circles as char in password
            passwordBox.PasswordChar = '\u25CF';
            newPasswordBox.PasswordChar = '\u25CF';

            //Set callbacks for map connection
            mapConnectionInstance = new CallbackMapConnection(MapConnectionHandler);
            SetCallbackForMapConnection(mapConnectionInstance);

            //Set callbacks for map permission change
            mapPermissionInstance = new CallbackMapPermission(MapPermissionHandler);
            SetCallbackForMapPermission(mapPermissionInstance);
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
            if (confidentiality_)
            {
                privatePanel.Visible = true;
                settingsPanel.Visible = false;

                if (passwordBox.TextLength == 0)
                {
                    label2.Visible = true;
                    label2.Text = "Doit entrer un mot de passe pour joindre.";
                    return;
                }
            }

            label2.Visible = false;

            //This will be in callback
            if (connectionState_)
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

                    /*case (int)ModeEnum.Mode.COURSE:
                        loadOnlineRaceMode();
                        break;*/

                    default:
                        break;
                }
            }
            else
            {
                parent_.mapMenu.choseOfflineMode(this);
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

        private void settingsButton_Click(object sender, EventArgs e)
        {
            settingsPanel.Visible = true;
            privatePanel.Visible = false;

            label2.Visible = false;
        }

        private void returnButton_Click(object sender, EventArgs e)
        {
            //Stayed private
            if (confidentiality_ && privateCheckBox.Checked)
            {
                //Maybe some code here??
            }
            //Changed to public
            else if (confidentiality_ && publicCheckBox.Checked)
            {
                publicSettings();
                //Mettre a jour info
                confidentiality_ = false;
                privacyLabel.Text = "Publique";
                FonctionsNatives.changeMapPermission(mapId_, (char)0, null, 0);
            }
            //Change to private
            else if (!confidentiality_ && privateCheckBox.Checked)
            {
                if (newPasswordBox.TextLength == 0)
                {
                    label1.Visible = true;
                    label1.Text = "Doit entrer un mot de passe";
                    return;
                }
            }
            //Stayed public
            else
            {
                //Maybe some code here??
            }

            label1.Visible = false;
            settingsPanel.Visible = false;
            privatePanel.Visible = true;
        }

        private void publicCheckBox_Click(object sender, EventArgs e)
        {
            publicSettings();
        }

        private void publicSettings()
        {
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;

            newPasswordLabel.Visible = false;
            newPasswordBox.Clear();
            newPasswordBox.Visible = false;
            updateButton.Visible = false;

            passewordLabel.Visible = false;
            passwordBox.Clear();
            passwordBox.Visible = false;
            connectButton.Visible = false;

            label1.Visible = false;
            label2.Visible = false;
        }

        private void privateCheckBox_Click(object sender, EventArgs e)
        {
            privateSettings();
        }

        private void privateSettings()
        {
            privateCheckBox.Checked = true;
            publicCheckBox.Checked = false;

            newPasswordLabel.Visible = true;
            newPasswordBox.Visible = true;
            updateButton.Visible = true;

            passewordLabel.Visible = true;
            passwordBox.Visible = true;
            connectButton.Visible = true;

            label1.Visible = false;
            label2.Visible = false;
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            if (newPasswordBox.TextLength == 0)
            {
                label1.Visible = true;
                label1.Text = "Doit entrer un mot de passe";
                return;
            }

            FonctionsNatives.changeMapPermission(mapId_, (char)1, newPasswordBox.Text, newPasswordBox.TextLength);
            newPasswordBox.Clear();

            privateSettings();
            settingsPanel.Visible = false;
            privatePanel.Visible = true;

            label1.Visible = false;

            //Mettre a jour info
            confidentiality_ = true;
            privacyLabel.Text = "Privée";
        }

        public void Test(int action)
        {
            mapConnect(action);
        }

        private delegate void CallbackMapConnection(int action);
        // Ensure it doesn't get garbage collected
        private CallbackMapConnection mapConnectionInstance;
        private void MapConnectionHandler(int action)
        {
            // Do something...
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForMapConnection(CallbackMapConnection fn);

        [DllImport("model.dll")]
        private static extern void mapConnect(int action);

        public void Test1(int action)
        {
            mapPermission(action);
        }

        private delegate void CallbackMapPermission(int action);
        // Ensure it doesn't get garbage collected
        private CallbackMapPermission mapPermissionInstance;
        private void MapPermissionHandler(int action)
        {
            // Do something...
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForMapPermission(CallbackMapPermission fn);

        [DllImport("model.dll")]
        private static extern void mapPermission(int action);
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeMapPermission(int mapId, char permission, string password, int passwordSize);
    }
}
