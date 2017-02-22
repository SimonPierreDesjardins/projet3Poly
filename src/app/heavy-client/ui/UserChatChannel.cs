////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public UserChatChannel(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
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
            e.ItemHeight = (int)e.Graphics.MeasureString(chatListBox.Items[e.Index].ToString(), chatListBox.Font, chatListBox.Width).Height;
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
            if (e.Index != -1)
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void disableControls()
        ///
        /// Désactiver les bouttons sur le control
        ///
        ////////////////////////////////////////////////////////////////////////
        private void disableControls()
        {
            userButton.Enabled = false;
            channelButton.Enabled = false;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enableControls()
        ///
        /// Active les bouttons sur le control
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enableControls()
        {
            userButton.Enabled = true;
            channelButton.Enabled = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void hideChat_Tick(object sender, EventArgs e)
        ///
        /// Cache le chat lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void hideChat_Tick(object sender, EventArgs e)
        ///
        /// Montre le chat lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
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
                chatListBox.Items.Add(chatTextBox.Text);
                chatListBox.TopIndex = chatListBox.Items.Count - 1;

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
    }
}
