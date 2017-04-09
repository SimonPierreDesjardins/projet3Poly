////////////////////////////////////////////////
/// @file   UserTabChat.cs
/// @author Frédéric Grégoire
/// @date   2017-02-22
///
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace ui
{
    public partial class UserTabChat : UserControl
    {
        Window parent_;
        Dictionary<string, UserChatChannel> channels_;

        public Boolean inMainWindow = true;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public UserTabChat(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public UserTabChat(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            channels_ = new Dictionary<string, UserChatChannel>();
            createNewChannel("General");

            mInstance = new CallbackForChat(Handler);
            SetCallbackForChat(mInstance);

            //To minimize chat on creation
            minizeOrMaximizeChat();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void onlineChatButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Appel la fonction pour minimiser ou maximiser le chat
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void onlineChatButton_Click(object sender, EventArgs e)
        {
            if (inMainWindow)
                minizeOrMaximizeChat();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void minMaxButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Appel la fonction pour minimiser ou maximiser le chat
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void minMaxButton_Click(object sender, EventArgs e)
        {
            minizeOrMaximizeChat();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void minizeOrMaximizeChat()
        ///
        /// Replace le chat dans la fenetre principal lorsqu'il minimiser ou maximiser
        /// et ajuste ses composantes en fonction
        ///    
        ////////////////////////////////////////////////////////////////////////
        private void minizeOrMaximizeChat()
        {
            //Minimize
            if (tabControl.Height != 0)
            {
                panel.BackColor = Color.FromArgb(26, 32, 40);
                tabControl.Height = 0;
                this.Height = 30;

                this.Location = new Point(parent_.viewPort.Width - this.Width, parent_.viewPort.Height - this.Height);
                minMaxPictureBox.Image = Properties.Resources.Maximize;

            }
            //Maximize
            else
            {
                panel.BackColor = Color.FromArgb(0,102,204);
                this.Height = 280;
                tabControl.Height = 252;

                this.Location = new Point(parent_.viewPort.Width - this.Width, parent_.viewPort.Height - this.Height);
                minMaxPictureBox.Image = Properties.Resources.Minimize;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outWindowButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Sert à changer le chat entre le mode intégré et le mode fenêtré
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void outWindowButton_Click(object sender, EventArgs e)
        {
            //Puts it in seperate window
            if (inMainWindow)
            {
                chatToseperateWindow();
            }
            else
            {
                chatToMainWindow();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chatToseperateWindow()
        ///
        /// Applique les changements au control et cree une nouvelle fenetre pour
        /// le chat pour qu'il soit en mode fenêtré
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatToseperateWindow()
        {
            inMainWindow = false;
            minMaxButton.Visible = false;
            minMaxButton.Enabled = false;
            panel.BackColor = Color.FromArgb(26, 32, 40);

            //Set chat components normal
            this.Height = 280;
            tabControl.Height = 252;
            minMaxPictureBox.Image = Properties.Resources.Minimize;

            if (parent_.viewPort.Controls.Contains(parent_.userChat))
                parent_.viewPort.Controls.Remove(parent_.userChat);
            else if (parent_.viewPort.Controls.Contains(parent_.userChat))
                parent_.viewPort.Controls.Remove(parent_.userChat);

            // Validate form not disposed before using. Initialize as needed. 
            if (parent_.chatWindow_ == null || parent_.chatWindow_.IsDisposed)
            {
                parent_.chatWindow_ = new ChatWindow(parent_);
            }
            parent_.chatWindow_.Controls.Add(parent_.userChat);
            parent_.userChat.Dock = DockStyle.Fill;
            parent_.chatWindow_.Show();
            parent_.chatWindow_.Activate();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chatToMainWindow()
        ///
        /// Applique les changements au control et cree ferme la fenetre de chat et pour
        /// que le chat soit en mode integre
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatToMainWindow()
        {
            inMainWindow = true;
            minMaxButton.Enabled = true;
            minMaxButton.Visible = true;
            panel.BackColor = Color.FromArgb(0, 102, 204);

            parent_.chatWindow_.Controls.Remove(parent_.userChat);
            parent_.chatWindow_.Hide();

            parent_.userChat.Size = new Size(265, 280);
            parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width,
                                                  parent_.viewPort.Height - parent_.userChat.Height);
            parent_.viewPort.Controls.Add(parent_.userChat);
            parent_.userChat.BringToFront();

            parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void createNewChannel(string name)
        ///
        /// Ajoute un tab au chat (channel) avec le nom donné en argument
        /// 
        /// @param string name: nom de la tab à ajouter
        ///
        ////////////////////////////////////////////////////////////////////////
        public void createNewChannel(string name)
        {
            //Add a tab
            TabPage newTabPage = new TabPage(name);
            tabControl.TabPages.Add(newTabPage);

            //Set options for new tab
            newTabPage.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            newTabPage.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            newTabPage.Margin = new System.Windows.Forms.Padding(0);

            //Add the content of the tab
            UserChatChannel newChannel = new UserChatChannel(parent_, name);
            channels_.Add(name, newChannel);

            UserChatChannel gen;
            if (channels_.TryGetValue("General", out gen))
                newChannel.setChannelList(gen.getChannelList());

            newChannel.Dock = DockStyle.Fill;
            newTabPage.Controls.Add(newChannel);

            string tmp = "cj" + name;
            FonctionsNatives.sendMessage(tmp);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool leaveChannel(string name)
        ///
        /// Retire un tab au chat (channel) avec le nom donné en argument
        /// 
        /// @param string name: nom de la tab à ajouter
        ///
        ////////////////////////////////////////////////////////////////////////
        public bool leaveChannel(String tabName)
        {
            bool leftChannel = false;
            for (int i = 1; i < tabControl.TabPages.Count && !leftChannel; ++i)
            {
                if (tabName == tabControl.TabPages[i].Text)
                {
                    tabControl.TabPages.Remove(tabControl.TabPages[i]);
                    channels_.Remove(tabName);
                    leftChannel = true;
                }
            }
            return leftChannel;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool alreadyInChannel(string name)
        ///
        /// Indique si le nom (channel) est déjà présent dans le chat.
        /// Retourne "true" si le channel est unique: pas présent
        /// Retourne "false" si le nom est déjà présent.
        /// 
        /// @param string name: nom de la tab à vérifier
        ///
        ////////////////////////////////////////////////////////////////////////
        public bool alreadyInChannel(String tabName)
        {
            bool unique = true;
            for (int i = 0; i < tabControl.TabPages.Count && unique; ++i)
            {
                if (tabName == tabControl.TabPages[i].Text)
                    unique = false;
            }
            return unique;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void handleChatMessage(string message)
        ///
        /// Redistribu le message recu pour le chat en fonction de la commande au debut
        /// du message
        /// 
        /// @param string message: message recu du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void handleChatMessage(string message)
        {
            byte[] bytes = Encoding.Default.GetBytes(message);
            message = Encoding.UTF8.GetString(bytes);

            switch (message[0])
            {
                case 'm':
                    userSentAMessage(message);
                    break;

                case 'l':
                    channelList(message);
                    break;

                case 'u':
                    userList(message);
                    break;

                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void userSentAMessage(string message)
        ///
        /// Gere le message recu du serveur indiquant qu'un utilisateur a envoyer
        /// un message
        /// 
        /// @param string message: message recu du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void userSentAMessage(string message)
        {
            int begin = 1;
            int lenght = message.IndexOf(';');
            string user = message.Substring(begin, lenght - 1);
            begin += lenght;

            lenght = message.IndexOf(';', begin) - begin;
            string channelName = message.Substring(begin, lenght);
            begin += lenght + 1;

            lenght = message.IndexOf(';', begin) - begin;
            string time = message.Substring(begin, lenght);
            begin += lenght + 1;

            lenght = message.IndexOf(';', begin) - begin;
            string date = message.Substring(begin, lenght);
            begin += lenght + 1;

            string sent = message.Substring(begin);

            UserChatChannel channel;
            bool isValid = channels_.TryGetValue(channelName, out channel);
            if (isValid)
            {
                parent_.Invoke((MethodInvoker)delegate {
                    channel.addMessageToChat(user + " a envoyé a " + time + " " + date + ":\r\n" + sent + "\r\n");
                });
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void channelList(string message)
        ///
        /// Gere le message recu du serveur indiquant tous les channels disponibles
        /// 
        /// @param string message: message recu du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void channelList(string message)
        {
            message = message.Substring(1);
            string[] channels = message.Split(';');

            parent_.Invoke((MethodInvoker)delegate {
                    foreach (KeyValuePair<string, UserChatChannel> entry in channels_)
                    {
                            entry.Value.setChannelList(channels);
                    }
                });
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void userList(string message)
        ///
        /// Gere le message recu du serveur indiquant tous les utilisateurs
        /// present dans un certain channel
        /// 
        /// @param string message: message recu du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void userList(string message)
        {
            string[] users = message.Split(';');
            string channelName = users[0].Substring(1);

            UserChatChannel channel;
            bool isValid = channels_.TryGetValue(channelName, out channel);
            if (isValid)
            {
                parent_.Invoke((MethodInvoker)delegate {
                    channel.addUsersToChannel(users);
                });
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void Test(string message)
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        /// 
        /// @param string message: message recu du serveur
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Test(string message)
        {
            TestCallback(message);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Handler(IntPtr message, int size)
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        /// Il indique qu'un message doit etre gere par le chat
        /// 
        /// @param IntPtr text: pointeur vers le message
        /// @param int size: taille du message
        ///
        ////////////////////////////////////////////////////////////////////////
        private delegate void CallbackForChat(IntPtr text, int size);
        private CallbackForChat mInstance;   
        private void Handler(IntPtr message, int size)
        {
            Byte[] tmp = new Byte[size];
            Marshal.Copy(message, tmp, 0, size);
            var str = System.Text.Encoding.Default.GetString(tmp);

            handleChatMessage(str);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForChat(CallbackForChat fn);

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void TestCallback(string message);
    }
}
