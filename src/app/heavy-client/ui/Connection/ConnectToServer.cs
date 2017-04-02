////////////////////////////////////////////////
/// @file   ConnectToServer.cs
/// @author Frédéric Grégoire
/// @date   2017-03-01
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Runtime.InteropServices;
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

            mInstance = new CallbackDisconnect(DisconnectHandler);
            SetCallbackForDisconnect(mInstance);

            connectSuccess = new CallbackConnectionSuccess(ConnectionSuccessHandler);
            SetCallbackForConnectionSuccess(connectSuccess);

            connectFail = new CallbackConnectionFail(ConnectionFailHandler);
            SetCallbackForConnectionFail(connectFail);
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
                parent_.userChat = new UserTabChat(parent_);
                if (FonctionsNatives.connectToServer(IPTextBox.Text, "5000"))
                {
                    ConnectionSuccessHandler();
                }
                else
                {
                    ConnectionFailHandler();
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void onConnectionSucces()
        ///
        /// Fonction qui passe à l'authentification du user si la connection reussi
        ///
        ////////////////////////////////////////////////////////////////////////
        private void onConnectionSucces()
        {
            connectPanel.Visible = false;

            authenticatePanel.Visible = true;
            newAccountWarningLabel.Visible = false;
            existingAccountWarningLabel.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void onConnectionFailure()
        ///
        /// Fonction qui indique un message d'erreur la connection echoue
        ///
        ////////////////////////////////////////////////////////////////////////
        private void onConnectionFailure()
        {
            IPWarningLabel.Visible = true;
            IPWarningLabel.Text = "Serveur non disponible à cette adresse.";
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
            FonctionsNatives.createProfile(newAccountTextBox.Text);
            FonctionsNatives.authenticate(newAccountTextBox.Text);

            parent_.userName = newAccountTextBox.Text;
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
            deconnectFromServer();
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
            deconnectFromServer();
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
            FonctionsNatives.authenticate(ExistingAccountTextBox.Text);

            parent_.userName = newAccountTextBox.Text;
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
            deconnectFromServer();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void deconnectFromServer()
        ///
        /// Deconnect du server et retourne au menu-principale.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void deconnectFromServer()
        {
            FonctionsNatives.disconnectFromServer();
            parent_.mapMenu.onlineMaps_.Clear();
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void removeChat()
        ///
        /// Enleve le chat de l'application.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void removeChat()
        {
            parent_.userName = "";
            if (parent_.userChat.inMainWindow)
                parent_.viewPort.Controls.Remove(parent_.userChat);
            else
                parent_.userChat.chatWindow_.Dispose();
        }

        public void Test()
        {
            GotDisconnected();
        }

        private delegate void CallbackDisconnect();
        // Ensure it doesn't get garbage collected
        private CallbackDisconnect mInstance;
        private void DisconnectHandler()
        {
            // Do something...
            if (parent_.viewPort.Controls.Contains(parent_.mainMenu))
            {
                parent_.mainMenu.connexionPictureBox.Image = parent_.mainMenu.ChangeColor((Bitmap)parent_.mainMenu.connexionPictureBox.Image, Color.Red);
            }

            parent_.mapMenu.onlineMaps_.Clear();

            parent_.disconnectedWarning = new DisconnetedPanel(parent_);
            parent_.disconnectedWarning.Location = new Point(parent_.viewPort.Width / 2 - parent_.disconnectedWarning.Width / 2,
                                                             parent_.viewPort.Height / 2 - parent_.disconnectedWarning.Height / 2);
            parent_.viewPort.Controls.Add(parent_.disconnectedWarning);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForDisconnect(CallbackDisconnect fn);

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void GotDisconnected();

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Test1()
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Test1()
        {
            connectionWasSuccess();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ConnectionSuccessHandler()
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        /// Il indique que la connection au serveur a reussi
        ///
        ////////////////////////////////////////////////////////////////////////
        private delegate void CallbackConnectionSuccess();
        private CallbackConnectionSuccess connectSuccess;
        private void ConnectionSuccessHandler()
        {
            parent_.Invoke((MethodInvoker)delegate {
                onConnectionSucces();
            });
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForConnectionSuccess(CallbackConnectionSuccess fn);

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void connectionWasSuccess();

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Test2()
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Test2()
        {
            connectionWasFail();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ConnectionFailHandler()
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        /// Il indique que la connection au serveur a echoue
        ///
        ////////////////////////////////////////////////////////////////////////
        private delegate void CallbackConnectionFail();
        private CallbackConnectionFail connectFail;
        private void ConnectionFailHandler()
        {
            parent_.Invoke((MethodInvoker)delegate {
                onConnectionFailure();
            });
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForConnectionFail(CallbackConnectionFail fn);

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void connectionWasFail();
    }
}
