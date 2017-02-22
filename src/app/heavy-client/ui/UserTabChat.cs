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

        public UserTabChat(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            createNewChannel("General");


        }

        private void onlineChatButton_Click(object sender, EventArgs e)
        {
            minizeOrMaximizeChat();
        }

        private void minMaxButton_Click(object sender, EventArgs e)
        {
            minizeOrMaximizeChat();
        }

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
