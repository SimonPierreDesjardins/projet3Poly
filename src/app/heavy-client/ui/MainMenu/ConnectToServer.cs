﻿////////////////////////////////////////////////
/// @file   ConnectToServer.cs
/// @author Frédéric Grégoire
/// @date   2017-03-01
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace ui
{
    public partial class ConnectToServer : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ConnectToServer(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ConnectToServer(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            if (FonctionsNatives.isConnected())
            {
                DeconnectPanel.Visible = true;
                connectPanel.Visible = false;
            }              
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void IPTextBox_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Action lorsqu'une touche est appuyée dans la text box pour l'adresse IP
        /// Si la touche est enter, on appel la méthode connectToServer.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement du keydown
        ///
        ////////////////////////////////////////////////////////////////////////
        private void IPTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar.ToString() == "\r")
                connectToServer();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void connectionButton_Click(object sender, EventArgs e)
        ///
        /// Appel la méthode connectToServer
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void connectionButton_Click(object sender, EventArgs e)
        {
            connectToServer();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool isIPAdressePossible()
        ///
        /// Utilise du regex pour savoir si l'adresse ipv4 est valide ou non.
        /// Affiche un message d'erreur si l'adresse n'est pas valide.
        /// 
        /// @return bool: True si valide, else false
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool isIPAdressePossible()
        {
            Regex ipAdresse = new Regex("^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$");
            bool validIpAdresse = ipAdresse.IsMatch(IPTextBox.Text);
            if (!validIpAdresse)
            {
                IPWarningLabel.Visible = true;
                IPWarningLabel.Text = "Adresse IP invalide.";
            }
            return validIpAdresse;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void connectToServer()
        ///
        /// Tente de se connecter au server. Message d'erreur si la connection n'est pas
        /// possible.
        /// Si la connection est établi, on passe à l'authentification du user.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void connectToServer()
        {
            IPWarningLabel.Visible = false;
            bool continuConnexion = isIPAdressePossible();

            if (continuConnexion)
            {
                if (FonctionsNatives.connectToServer(IPTextBox.Text, "5000"))
                {
                    connectPanel.Visible = false;

                    this.Location = new Point((parent_.viewPort.Width + parent_.mainMenu.Width) / 2 - Width / 2,
                                               parent_.viewPort.Height / 2 - Height / 2);

                    authenticatePanel.Visible = true;
                    newAccountWarningLabel.Visible = false;
                    existingAccountWarningLabel.Visible = false;
                }else
                {
                    IPWarningLabel.Visible = true;
                    IPWarningLabel.Text = "Serveur non disponible à cette adresse.";
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cancelButton_Click(object sender, EventArgs e)
        ///
        /// Annule la tentative de connexion et retourne au menu-principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelButton_Click(object sender, EventArgs e)
        {
            goBackToMainMenu();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void newAccountTextBox_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Action lorsqu'une touche est appuyée dans la text box pour un nouvel utilisateur
        /// Utilise du regex pour permettre les caractere alphanumérique et accent.
        /// Si la touche est enter, on appel la méthode createAndConnectNewUser.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement du keydown
        ///
        ////////////////////////////////////////////////////////////////////////
        private void newAccountTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar.ToString() == "\r")
                createAndConnectNewUser();
            else if (e.KeyChar.ToString() != "\b")
            {
                Regex regex = new Regex("[A-zÀ-ÿ0-9._]+");
                e.Handled = !regex.IsMatch(e.KeyChar.ToString());
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void crateAndAuthenticateButton_Click(object sender, EventArgs e)
        ///
        /// Appel la méthode createAndConnectNewUser();
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void crateAndAuthenticateButton_Click(object sender, EventArgs e)
        {
            createAndConnectNewUser();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void createAndConnectNewUser
        ///
        /// Authentifie l'utilisateur. Si l'action réussi, on retourne au menu-principal.
        /// Sinon un message d'erreur est affiché.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void createAndConnectNewUser()
        {
            goBackToMainMenu();

            parent_.viewPort.Controls.Add(parent_.userChat);
            parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width, parent_.viewPort.Height - parent_.userChat.Height);
            parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            parent_.userChat.BringToFront();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cancelNewUserButton_Click(object sender, EventArgs e)
        ///
        /// Disconnect du serveur et retourne au menu-principale.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelNewUserButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            removeChat();
            goBackToMainMenu();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ExistingAccountTextBox_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Action lorsqu'une touche est appuyée dans la text box pour un utilisateur existant
        /// Utilise du regex pour permettre les caractere alphanumérique et accent.
        /// Si la touche est enter, on appel la méthode createAndConnectNewUser.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement du keydown
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ExistingAccountTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar.ToString() == "\r")
                connectExistingUser();
            else if (e.KeyChar.ToString() != "\b")
            {
                Regex regex = new Regex("[A-zÀ-ÿ0-9._]+");
                e.Handled = !regex.IsMatch(e.KeyChar.ToString());
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cancelExistingUserButton_Click(object sender, EventArgs e)
        ///
        /// Disconnect du serveur et retourne au menu-principale.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelExistingUserButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            removeChat();
            goBackToMainMenu();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void authenticateButton_Click(object sender, EventArgs e)
        ///
        /// Appel la méthode connectExistingUser();
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void authenticateButton_Click(object sender, EventArgs e)
        {
            connectExistingUser();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void connectExistingUser()
        ///
        /// Authentifie l'utilisateur. Si l'action réussi, on retourne au menu-principal.
        /// Sinon un message d'erreur est affiché.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void connectExistingUser()
        {
            goBackToMainMenu();

            parent_.viewPort.Controls.Add(parent_.userChat);
            parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width, parent_.viewPort.Height - parent_.userChat.Height);
            parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            parent_.userChat.BringToFront();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void DeconnectButton_Click(object sender, EventArgs e)
        ///
        /// Deconnect du server et retourne au menu-principale.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void DeconnectButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            removeChat();
            goBackToMainMenu();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CancelDeconnectButton_Click(object sender, EventArgs e)
        ///
        /// Arrête le processus de déconnexion et retourne au menu-principale.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CancelDeconnectButton_Click(object sender, EventArgs e)
        {
            goBackToMainMenu();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void goBackToMainMenu()
        ///
        /// Enlève les composantes de ce controle et ajoute les composantes pour le
        /// menu-principale.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void goBackToMainMenu()
        {
            parent_.viewPort.Controls.Remove(this);
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;
        }

        private void removeChat()
        {
            if (parent_.userChat.inMainWindow)
                parent_.viewPort.Controls.Remove(parent_.userChat);
            else
                parent_.userChat.chatWindow_.Dispose();
        }
    }
}