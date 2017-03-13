﻿////////////////////////////////////////////////
/// @file   UserChatChannel.cs
/// @author Frédéric Grégoire
/// @date   2017-02-22
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class UserChatChannel : UserControl
    {
        Window parent_;
        String name_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public UserChatChannel(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public UserChatChannel(Window parent, string name)
        {
            InitializeComponent();
            parent_ = parent;
            name_ = name;


            panelUser.Visible = false;
            userListBox.Items.Add("USERS MOFO");
            
            panelChannel.Visible = false;
            ChannelListBox.Items.Add("CHANNELS MOFO");

            chatListBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            chatListBox.MeasureItem += chatBox_MeasureItem;
            chatListBox.DrawItem += chatBox_DrawItem;
        }

        public ListBox.ObjectCollection getChannelListBoxInfo()
        {
            return ChannelListBox.Items;
        }

        public void addNewChannel(String newChannelName)
        {
            ChannelListBox.Items.Add(newChannelName);
        }

        public void setChannelList(string[] listOfChannels)
        {
            ChannelListBox.Items.Clear();
            foreach (var channel in listOfChannels)
            {
                ChannelListBox.Items.Add(channel);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chatBox_MeasureItem(object sender, MeasureItemEventArgs e)
        ///
        /// Sert à calculer la longueur d'une chaine de string dans la liste box
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param MesureItemEventArgs e: evenement pour mesure la grandeur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            if (chatListBox.Items.Count > 0)
            {
                e.ItemHeight = (int)e.Graphics.MeasureString(chatListBox.Items[e.Index].ToString(), chatListBox.Font, chatListBox.Width).Height;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chatBox_MeasureItem(object sender, MeasureItemEventArgs e)
        ///
        /// Sert à dessiner les strings dans la listebox et de faire un "wrap" sur celle-ci
        /// quand elles sont trop longue pour une ligne
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param DrawItemEventArgs e: evenement pour dessiner le control
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.DrawFocusRectangle();
            if (e.Index > -1)
                e.Graphics.DrawString(chatListBox.Items[e.Index].ToString(), e.Font, new SolidBrush(e.ForeColor), e.Bounds);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void UserChatChannel_Resize(object sender, EventArgs e)
        ///
        /// Redimensionne les boutons a la droite du controle lorsqu'il est redimensionner
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void UserChatChannel_Resize(object sender, EventArgs e)
        {
            userButton.Height = this.Height / 2;
            userButton.Location = new Point(0, 0);

            channelButton.Height = this.Height / 2;
            channelButton.Location = new Point(0, this.Height / 2);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void userButton_Click(object sender, EventArgs e)
        ///
        /// Actions lorsque le boutton des usagers est appuyé.
        /// Il fait les actions suivantes selon son état:
        /// 1. Cache le chat et affiche les users
        /// 2. Cache les users et affiche le chat
        /// 3. Cache les channels et montre les users
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void userButton_Click(object sender, EventArgs e)
        {
            //If Chat is active
            if (panelChat.Visible)
            {
                userPictureBox.Image = Properties.Resources.Chat;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChat.Visible = false;
                panelUser.Visible = true;
            }
            //If ChannelList is displayed
            else if(panelChannel.Visible)
            {
                userPictureBox.Image = Properties.Resources.Chat;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChannel.Visible = false;
                panelUser.Visible = true;
            }
            else
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelUser.Visible = false;
                panelChat.Visible = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void userButton_Click(object sender, EventArgs e)
        ///
        /// Actions lorsque le boutton des channels est appuyé.
        /// Il fait les actions suivantes selon son état:
        /// 1. Cache le chat et affiche les channels
        /// 2. Cache les users et affiche les channels
        /// 3. Cache les channels et affiche le chat
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void channelButton_Click(object sender, EventArgs e)
        {
            //If Chat is active
            if (panelChat.Visible)
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Chat;

                panelChannel.Visible = true;
                panelChat.Visible = false;
            }
            //If UserList is displayed
            else if(panelUser.Visible)
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Chat;

                panelUser.Visible = false;
                panelChannel.Visible = true;
            }
            else
            {
                userPictureBox.Image = Properties.Resources.User;
                channelPictureBox.Image = Properties.Resources.Channels;

                panelChannel.Visible = false;
                panelChat.Visible = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void userButton_Click(object sender, EventArgs e)
        ///
        /// Arrete d'envoyer des actions au modele. Si la touche est "enter"
        /// le message est envoyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param PreviewKeyDownEventArgs e: evenement d'une keydown
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatTextBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);

            if (e.KeyCode == Keys.Enter)
                sendText();

            FonctionsNatives.assignerAutorisationInputClavier(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sendButton_Click_1(object sender, EventArgs e)
        ///
        /// Envoie le message lorsque le boutton est appuyer
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void sendButton_Click_1(object sender, EventArgs e)
        {
            sendText();
            chatTextBox.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sendText()
        ///
        /// Vérifie si le message est vide et l'ajoute au chat (chatListBox)
        /// et vide la textbox
        ///
        ////////////////////////////////////////////////////////////////////////
        private void sendText()
        {
            if (!System.Text.RegularExpressions.Regex.Replace(chatTextBox.Text, "\n|\t| |\r", "").Equals(""))
            {
                string tmp = "cm" + parent_.userName + ";" + name_ + ";" + DateTime.Now.ToString("HH:mm:ss;yyyy-MM-dd;") + chatTextBox.Text;
                FonctionsNatives.sendMessage(tmp, tmp.Length);
                chatTextBox.Clear();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void createButton_Click(object sender, EventArgs e)
        ///
        /// Crée un nouveau tab (channel) avec le nom dans la textbox si possible
        /// Sinon un message d'erreur est retourné dans le label
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void joinButton_Click(object sender, EventArgs e)
        ///
        /// Crée un nouveau tab (channel) avec le nom sélectionné parmi les channels.
        /// Si le channel est deja présent un message d'erreur est retourné dans le label
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void joinButton_Click(object sender, EventArgs e)
        {
            warningLabel.Visible = false;

            if (ChannelListBox.SelectedIndex != -1)
            {
                bool unique = parent_.userChat.alreadyInChannel(ChannelListBox.SelectedItem.ToString());
                
                if (unique)
                {
                    parent_.userChat.createNewChannel(ChannelListBox.SelectedItem.ToString());
                }   
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void leaveButton_Click(object sender, EventArgs e)
        ///
        /// Enlève un tab (channel) avec le nom sélectionné parmi les channels.
        /// Si le channel n'est pas présent un message d'erreur est retourné dans le label
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void leaveButton_Click(object sender, EventArgs e)
        {
            warningLabel.Visible = false;

            if (ChannelListBox.SelectedIndex != -1)
            {
                string channel = ChannelListBox.SelectedItem.ToString();
                bool leftChannel = parent_.userChat.leaveChannel(channel);

                if (!leftChannel)
                {
                    warningLabel.Visible = true;
                    warningLabel.Text = "Ne peut quitter ce canal";
                }
                else
                {
                    string tmp = "cq" + channel;
                    FonctionsNatives.sendMessage(tmp, tmp.Length);
                }
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Aucun canal sélectionné";
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panelChannel_VisibleChanged(object sender, EventArgs e)
        ///
        /// Change la visibilité du warning label lorsque la visibilité est changé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panelChannel_VisibleChanged(object sender, EventArgs e)
        {
            warningLabel.Visible = false;
            warningLabel.Text = "";
        }

        public void addMessageToChat(string message)
        {
            chatListBox.Items.Add(message);
            chatListBox.TopIndex = chatListBox.Items.Count - 1;
        }

        public void addUsersToChannel(string[] users)
        {
            userListBox.Items.Clear();
            for (int i = 1; i < users.Length; i++)
                userListBox.Items.Add(users[i]);
        }
    }
}
