using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class UserChatChannel : UserControl
    {
        Window parent_;

        public UserChatChannel(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
            
            panelUser.Visible = false;
            userListBox.Items.Add("USERS MOFO");
            
            panelChannel.Visible = false;
            ChannelListBox.Items.Add("CHANNELS MOFO");

            chatListBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            chatListBox.MeasureItem += chatBox_MeasureItem;
            chatListBox.DrawItem += chatBox_DrawItem;
        }

        private void chatBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            e.ItemHeight = (int)e.Graphics.MeasureString(chatListBox.Items[e.Index].ToString(), chatListBox.Font, chatListBox.Width).Height;
        }

        private void chatBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.DrawFocusRectangle();
            if (e.Index != -1)
                e.Graphics.DrawString(chatListBox.Items[e.Index].ToString(), e.Font, new SolidBrush(e.ForeColor), e.Bounds);
        }

        private void UserChatChannel_Resize(object sender, EventArgs e)
        {
            userButton.Height = this.Height / 2;
            userButton.Location = new Point(0, 0);

            channelButton.Height = this.Height / 2;
            channelButton.Location = new Point(0, this.Height / 2);
        }

        private void userButton_Click(object sender, EventArgs e)
        {
            disableControls();

            //If Chat is active
            if (panelChat.Visible)
            {
                userPictureBox.Image = Properties.Resources.Chat;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelUser.Visible = true;
                hideChat.Start();
            }
            //If ChannelList is displayed
            else if(panelChannel.Visible)
            {
                userPictureBox.Image = Properties.Resources.Chat;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChannel.Visible = false;
                panelUser.Visible = true;
                enableControls();
            }
            else
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChat.Width = 0;
                panelChat.Visible = true;
                showChat.Start();
            }
        }

        private void channelButton_Click(object sender, EventArgs e)
        {
            disableControls();

            //If Chat is active
            if (panelChat.Visible)
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Chat;

                panelChannel.Visible = true;
                hideChat.Start();
            }
            //If UserList is displayed
            else if(panelUser.Visible)
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Chat;

                panelUser.Visible = false;
                panelChannel.Visible = true;
                enableControls();
            }
            else
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChat.Width = 0;
                panelChat.Visible = true;
                showChat.Start();
            }
        }

        private void disableControls()
        {
            userButton.Enabled = false;
            channelButton.Enabled = false;
        }

        private void enableControls()
        {
            userButton.Enabled = true;
            channelButton.Enabled = true;
        }

        private void hideChat_Tick(object sender, EventArgs e)
        {
            if (panelChat.Width > 0)
            {
                panelChat.Width -= 5;
            }
            else
            {
                hideChat.Stop();
                panelChat.Visible = false;
                enableControls();
            }
        }

        private void showChat_Tick(object sender, EventArgs e)
        {

            if (panelChat.Width < (this.Width - panelForButtons.Width - 5))
            {
                panelChat.Width += 5;
                chatListBox.Refresh();
            }
            else
            {
                showChat.Stop();
                panelUser.Visible = false;
                panelChannel.Visible = false;
                chatListBox.Refresh();
                enableControls();
            }
        }

        private void chatTextBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);

            if (e.KeyCode == Keys.Enter)
                sendText();

            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        private void sendButton_Click_1(object sender, EventArgs e)
        {
            sendText();
            chatTextBox.Focus();
        }

        private void sendText()
        {
            if (!System.Text.RegularExpressions.Regex.Replace(chatTextBox.Text, "\n|\t| |\r", "").Equals(""))
            {
                chatListBox.Items.Add(chatTextBox.Text);
                chatListBox.TopIndex = chatListBox.Items.Count - 1;

                chatTextBox.Clear();
            }
        }

        private void createButton_Click(object sender, EventArgs e)
        {
            warningLabel.Visible = false;

            if (ChannelListBox.Items.Contains(addChannelTextBox.Text))
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Ce canal existe déjà";
            }
            else if (!System.Text.RegularExpressions.Regex.Replace(addChannelTextBox.Text, "\n|\t| |\r", "").Equals(""))
            {
                parent_.userChat.createNewChannel(addChannelTextBox.Text);
                ChannelListBox.Items.Add(addChannelTextBox.Text);
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Ne peut créer ce canal";
            }

            addChannelTextBox.Clear();
        }

        private void addChannelTextBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {

        }

        private void joinButton_Click(object sender, EventArgs e)
        {
            warningLabel.Visible = false;

            if (ChannelListBox.SelectedIndex != -1)
            {
                bool unique = parent_.userChat.alreadyInChannel(ChannelListBox.SelectedItem.ToString());
                
                if (unique)
                    parent_.userChat.createNewChannel(ChannelListBox.SelectedItem.ToString());
                else
                {
                    warningLabel.Visible = true;
                    warningLabel.Text = "Vous êtes déjà dans ce canal";
                }
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Aucun canal sélectionné";
            }
                
        }

        private void leaveButton_Click(object sender, EventArgs e)
        {
            warningLabel.Visible = false;

            if (ChannelListBox.SelectedIndex != -1)
            {
                bool leftChannel = parent_.userChat.leaveChannel(ChannelListBox.SelectedItem.ToString());

                if (!leftChannel)
                {
                    warningLabel.Visible = true;
                    warningLabel.Text = "Ne peut quitter ce canal";
                }
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Aucun canal sélectionné";
            }
        }

        private void panelChannel_VisibleChanged(object sender, EventArgs e)
        {
            warningLabel.Visible = false;
            warningLabel.Text = "";
        }
    }
}
