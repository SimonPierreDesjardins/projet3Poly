////////////////////////////////////////////////
/// @file   UserTabChat.cs
/// @author Frédéric Grégoire
/// @date   2017-02-22
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class UserTabChat : UserControl
    {
        Window parent_;
        ChatWindow chatWindow_;
        Boolean inMainWindow = true;

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

            createNewChannel("General");


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
                tabControl.Height = 0;
                this.Height = 30;

                this.Location = new Point(parent_.viewPort.Width - this.Width, parent_.viewPort.Height - this.Height);
                minMaxPictureBox.Image = Properties.Resources.Maximize;

            }
            //Maximize
            else
            {
                this.Height = 280;
                tabControl.Height = 249;

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
            if (inMainWindow)
            {
                inMainWindow = false;
                minMaxButton.Visible = false;
                minMaxButton.Enabled = false;

                //Set chat components normal
                this.Height = 280;
                tabControl.Height = 249;
                minMaxPictureBox.Image = Properties.Resources.Minimize;

                if (parent_.viewPort.Controls.Contains(parent_.userChat))
                    parent_.viewPort.Controls.Remove(parent_.userChat);
                else if (parent_.viewPort.Controls.Contains(parent_.userChat))
                    parent_.viewPort.Controls.Remove(parent_.userChat);

                chatWindow_ = new ChatWindow(parent_);
                chatWindow_.Controls.Add(parent_.userChat);
                parent_.userChat.Dock = DockStyle.Fill;
                chatWindow_.Show();

            } else
            {
                inMainWindow = true;
                minMaxButton.Enabled = true;
                minMaxButton.Visible = true;
               
                chatWindow_.Controls.Remove(parent_.userChat);
                chatWindow_.Dispose();

                parent_.userChat.Size = new Size(265, 280);
                parent_.userChat.Location = new Point(parent_.viewPort.Width - parent_.userChat.Width,
                                                      parent_.viewPort.Height - parent_.userChat.Height);
                parent_.viewPort.Controls.Add(parent_.userChat);
                
                parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            }
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
            UserChatChannel newChannel = new UserChatChannel(parent_);
            newTabPage.Controls.Add(newChannel);
            newChannel.Dock = DockStyle.Fill;
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
    }
}
