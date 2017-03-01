using System;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace ui
{
    public partial class ConnectToServer : UserControl
    {
        Window parent_;

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

        private void IPTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar.ToString() == "\r")
                connectToServer();
        }

        private void connectionButton_Click(object sender, EventArgs e)
        {
            connectToServer();
        }

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

        private void connectToServer()
        {
            IPWarningLabel.Visible = false;
            bool continuConnexion = isIPAdressePossible();

            //TODO: Connection to server
            if (continuConnexion)
            {
                FonctionsNatives.connectToServer(IPTextBox.Text, "5000");
                connectPanel.Visible = false;

                this.Location = new Point((parent_.viewPort.Width + parent_.mainMenu.Width) / 2 - Width / 2,
                                           parent_.viewPort.Height / 2 - Height / 2);

                authenticatePanel.Visible = true;
                newAccountWarningLabel.Visible = false;
                existingAccountWarningLabel.Visible = false;
            }
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            goBackToMainMenu();
        }

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

        private void crateAndAuthenticateButton_Click(object sender, EventArgs e)
        {
            createAndConnectNewUser();
        }

        private void createAndConnectNewUser()
        {
            goBackToMainMenu();

            parent_.viewPort.Controls.Add(parent_.userChat);
            parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width, parent_.viewPort.Height - parent_.userChat.Height);
            parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            parent_.userChat.BringToFront();
        }

        private void cancelNewUserButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            goBackToMainMenu();
        }

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

        private void cancelExistingUserButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            goBackToMainMenu();
        }

        private void authenticateButton_Click(object sender, EventArgs e)
        {
            connectExistingUser();
        }

        private void connectExistingUser()
        {
            goBackToMainMenu();

            parent_.viewPort.Controls.Add(parent_.userChat);
            parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width, parent_.viewPort.Height - parent_.userChat.Height);
            parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            parent_.userChat.BringToFront();
        }

        private void DeconnectButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.disconnectFromServer();
            goBackToMainMenu();
        }

        private void CancelDeconnectButton_Click(object sender, EventArgs e)
        {
            goBackToMainMenu();
        }

        private void goBackToMainMenu()
        {
            parent_.viewPort.Controls.Remove(this);
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Remove(parent_.editionMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionSideMenu);
            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;
        }
    }
}
