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

            //Set callbacks for connection state
            connectSuccess = new CallbackConnectionSuccess(ConnectionSuccessHandler);
            SetCallbackForConnectionSuccess(connectSuccess);

            connectFail = new CallbackConnectionFail(ConnectionFailHandler);
            SetCallbackForConnectionFail(connectFail);

            //Set callbacks for user authentification
            authenticationInstance = new CallbackAuthentification(AuthentificationHandler);
            SetCallbackForAuthentification(authenticationInstance);
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
                //Parse Ip to remove extra 0. This is a shit fix
                String[] ip = IPTextBox.Text.Split('.');
                string tmp = "";
                for (int i = 0; i < ip.Length; i++)
                {
                    tmp += removeExtraNumbers(ip[i]) + ".";
                }
                tmp = tmp.Substring(0, tmp.Length - 1);

                parent_.userChat = new UserTabChat(parent_);
                if (FonctionsNatives.connectToServer(tmp, "5000"))
                {
                    ConnectionSuccessHandler();
                }
                else
                {
                    ConnectionFailHandler();
                }
            }
        }

        private string removeExtraNumbers(string ip)
        {
            string tmp = ip;
            for (int i = 0; i < ip.Length -1 ; i++)
            {
                if (ip[i].Equals('0'))
                    tmp = ip.Substring(i + 1);
                else
                    return tmp;
            }
            return tmp;
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
            existingAccountWarningLabel.Visible = false;
            newAccountWarningLabel.Visible = false;

            FonctionsNatives.createProfile(newAccountTextBox.Text);
            parent_.userName = newAccountTextBox.Text;
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
            existingAccountWarningLabel.Visible = false;
            newAccountWarningLabel.Visible = false;

            FonctionsNatives.authenticate(ExistingAccountTextBox.Text);
            parent_.userName = ExistingAccountTextBox.Text;
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
            parent_.mapMenu.onlineMapsName_.Clear();
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

            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;
        }

        private void userConnectionSuccess()
        {
            parent_.Invoke((MethodInvoker)delegate {
                goBackToMainMenu();

                parent_.viewPort.Controls.Add(parent_.userChat);
                parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width, parent_.viewPort.Height - parent_.userChat.Height);
                parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
                parent_.userChat.BringToFront();
            });
        }

        private void userAlreadyExists()
        {
            parent_.Invoke((MethodInvoker)delegate {
                newAccountWarningLabel.Text = "Un utilisateur avec ce nom exist déjà";
                newAccountWarningLabel.Visible = true;
                parent_.userName = null;
            });
        }

        private void userAuthFail()
        {
            parent_.Invoke((MethodInvoker)delegate {
                existingAccountWarningLabel.Text = "Cet utilisateur n'existe pas";
                existingAccountWarningLabel.Visible = true;
                parent_.userName = null;
            });
        }

        private void userAlreadyConnected()
        {
            parent_.Invoke((MethodInvoker)delegate {
                existingAccountWarningLabel.Text = "Un utilisateur avec ce nom est déjà connecté";
                existingAccountWarningLabel.Visible = true;
                parent_.userName = null;
            });
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void removeChat()
        ///
        /// Enleve le chat de l'application.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void removeChat()
        {
            parent_.userName = "";
            if (parent_.userChat.inMainWindow)
                parent_.viewPort.Controls.Remove(parent_.userChat);
            else
                parent_.chatWindow_.Hide();
        }

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

        [DllImport("model.dll")]
        private static extern void connectionWasFail();

        //New user authentication
        public void Test3(int action)
        {
            authentification(action);
        }

        private delegate void CallbackAuthentification(int action);
        // Ensure it doesn't get garbage collected
        private CallbackAuthentification authenticationInstance;
        private void AuthentificationHandler(int action)
        {
            switch(action)
            {
                case (int)AuthenticationAction.Authentication.CREATION_SUCCESS:
                    FonctionsNatives.authenticate(newAccountTextBox.Text);
                    break;

                case (int)AuthenticationAction.Authentication.NEW_ALREADY_EXIST:
                    userAlreadyExists();
                    break;

                case (int)AuthenticationAction.Authentication.AUTEHNTIFICATION_SUCCESS:
                    userConnectionSuccess();
                    break;

                case (int)AuthenticationAction.Authentication.EXISTING_ALREADY_CONNECTED:
                    userAlreadyConnected();
                    break;

                case (int)AuthenticationAction.Authentication.EXISTING_FAIL:
                    userAuthFail();
                    break;

                default:
                    break;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForAuthentification(CallbackAuthentification fn);

        [DllImport("model.dll")]
        private static extern void authentification(int action);
    }
}
