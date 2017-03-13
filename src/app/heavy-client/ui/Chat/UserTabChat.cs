////////////////////////////////////////////////
/// @file   UserTabChat.cs
/// @author Frédéric Grégoire
/// @date   2017-02-22
///
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ui
{
    public partial class UserTabChat : UserControl
    {
        Window parent_;
        public ChatWindow chatWindow_;
        UserChatChannel generalChannel_ = null;
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
            generalChannel_ = createNewChannel("General");

            mInstance = new CallbackForChat(Handler);
            SetCallbackForChat(mInstance);
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

            chatWindow_ = new ChatWindow(parent_);
            chatWindow_.Controls.Add(parent_.userChat);
            parent_.userChat.Dock = DockStyle.Fill;
            chatWindow_.Show();
        }

        private void chatToMainWindow()
        {
            inMainWindow = true;
            minMaxButton.Enabled = true;
            minMaxButton.Visible = true;
            panel.BackColor = Color.FromArgb(0, 102, 204);

            chatWindow_.Controls.Remove(parent_.userChat);
            chatWindow_.Dispose();

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
        public UserChatChannel createNewChannel(string name)
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

            if (generalChannel_ != null)
            {
                generalChannel_.addNewChannel(name);
                updateChannelList();
            } 
            newTabPage.Controls.Add(newChannel);
            newChannel.Dock = DockStyle.Fill;

            return newChannel;
        }

        private void updateChannelList()
        {
            foreach (KeyValuePair<string, UserChatChannel> entry in channels_)
            {
                if (!entry.Key.Equals("General"))
                    entry.Value.setChannelList(generalChannel_);
            }
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

        private void handleChatMessage(string message)
        {
            switch(message[0])
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
                this.Invoke((MethodInvoker)delegate {
                    channel.addMessageToChat(user + " a envoyé a " + time + " " + date + ":\r\n" + sent + "\r\n");
                });
            }
        }

        private void channelList(string message)
        {
            string[] channels = message.Split(';');
        }

        private void userList(string message)
        {
            string[] users = message.Split(';');
            string channelName = users[0].Substring(1);

            UserChatChannel channel;
            bool isValid = channels_.TryGetValue(channelName, out channel);
            if (isValid)
            {
                this.Invoke((MethodInvoker)delegate {
                    channel.addUsersToChannel(users);
                });
            }
        }

        public void Test(string message)
        {
            TestCallback(message);
        }

        private delegate void CallbackForChat(IntPtr text, int size);
        // Ensure it doesn't get garbage collected
        private CallbackForChat mInstance;   
        private void Handler(IntPtr message, int size)
        {
            // Do something...
            Byte[] tmp = new Byte[size];
            Marshal.Copy(message, tmp, 0, size);
            var str = System.Text.Encoding.Default.GetString(tmp);

            handleChatMessage(str);

            //For debugging
            Console.WriteLine(str);
            Console.WriteLine("\n Callback \n");
        }

        [DllImport("model.dll")]
        private static extern void SetCallbackForChat(CallbackForChat fn);

        [DllImport("model.dll")]
        private static extern void TestCallback(string message);
    }
}
