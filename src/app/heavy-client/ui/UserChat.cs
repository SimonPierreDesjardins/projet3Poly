using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace ui
{
    public partial class UserChat : UserControl
    {
        Window parent_;
        ChatWindow chatWindow_;
        Boolean inMainWindow = true;

        public UserChat(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            chatBox1.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            chatBox1.MeasureItem += chatBox_MeasureItem;
            chatBox1.DrawItem += chatBox_DrawItem;
        }

        private void chatBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            e.ItemHeight = (int)e.Graphics.MeasureString(chatBox1.Items[e.Index].ToString(), chatBox1.Font, chatBox1.Width).Height;
        }

        private void chatBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.DrawFocusRectangle();
            if (e.Index != -1)
                e.Graphics.DrawString(chatBox1.Items[e.Index].ToString(), e.Font, new SolidBrush(e.ForeColor), e.Bounds);
        }

        public void sendText()
        {
            if (!Regex.Replace(chatTextBox1.Text, "\n|\t| |\r", "").Equals(""))
            {
                chatBox1.Items.Add(chatTextBox1.Text);
                chatBox1.TopIndex = chatBox1.Items.Count - 1;

                chatTextBox1.Clear();
            }
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            sendText();
        }

        private void chatTextBox1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);

            if (e.KeyCode == Keys.Enter)
                sendText();

            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        private void minMaxButton_Click(object sender, EventArgs e)
        {

        }

        private void outWindowButton_Click(object sender, EventArgs e)
        {
            if (inMainWindow)
            {
                inMainWindow = false;

                if (parent_.mainScreen.Controls.Contains(parent_.userChat))
                    parent_.mainScreen.Controls.Remove(parent_.userChat);
                else if (parent_.viewPort.Controls.Contains(parent_.userChat))
                    parent_.viewPort.Controls.Remove(parent_.userChat);

                chatWindow_ = new ChatWindow(parent_);
                chatWindow_.Controls.Add(parent_.userChat);
                parent_.userChat.Dock = DockStyle.Fill;
                chatWindow_.Show();
            } else
            {
                inMainWindow = true;
                chatWindow_.Controls.Remove(parent_.userChat);
                chatWindow_.Dispose();

                parent_.userChat.Size = new Size(265, 280);
                parent_.userChat.Location = new Point(parent_.mainScreen.Width - parent_.userChat.Width,
                                                      parent_.mainScreen.Height - parent_.userChat.Height);
                parent_.mainScreen.Controls.Add(parent_.userChat);
                
                parent_.userChat.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            }
        }
    }



}
