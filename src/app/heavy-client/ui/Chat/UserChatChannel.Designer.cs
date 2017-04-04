namespace ui
{
    partial class UserChatChannel
    {
        /// <summary> 
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur de composants

        /// <summary> 
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas 
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserChatChannel));
            this.panelForButtons = new System.Windows.Forms.Panel();
            this.panelChat = new System.Windows.Forms.Panel();
            this.chatTextBox = new System.Windows.Forms.TextBox();
            this.chatListBox = new System.Windows.Forms.ListBox();
            this.userListBox = new System.Windows.Forms.ListBox();
            this.ChannelListBox = new System.Windows.Forms.ListBox();
            this.panelChannel = new System.Windows.Forms.Panel();
            this.warningLabel = new System.Windows.Forms.Label();
            this.addChannelTextBox = new System.Windows.Forms.TextBox();
            this.panelUser = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.panel = new System.Windows.Forms.Panel();
            this.channelButton = new ui.PanelButton();
            this.channelPictureBox = new System.Windows.Forms.PictureBox();
            this.userButton = new ui.PanelButton();
            this.userPictureBox = new System.Windows.Forms.PictureBox();
            this.sendButton = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.createButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.joinButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.leaveButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.panelForButtons.SuspendLayout();
            this.panelChat.SuspendLayout();
            this.panelChannel.SuspendLayout();
            this.panelUser.SuspendLayout();
            this.panel.SuspendLayout();
            this.channelButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.channelPictureBox)).BeginInit();
            this.userButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.userPictureBox)).BeginInit();
            this.sendButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.createButton.SuspendLayout();
            this.joinButton.SuspendLayout();
            this.leaveButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelForButtons
            // 
            this.panelForButtons.Controls.Add(this.channelButton);
            this.panelForButtons.Controls.Add(this.userButton);
            this.panelForButtons.Dock = System.Windows.Forms.DockStyle.Right;
            this.panelForButtons.Location = new System.Drawing.Point(237, 0);
            this.panelForButtons.Name = "panelForButtons";
            this.panelForButtons.Size = new System.Drawing.Size(20, 239);
            this.panelForButtons.TabIndex = 13;
            // 
            // panelChat
            // 
            this.panelChat.Controls.Add(this.chatTextBox);
            this.panelChat.Controls.Add(this.sendButton);
            this.panelChat.Controls.Add(this.chatListBox);
            this.panelChat.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelChat.Location = new System.Drawing.Point(0, 0);
            this.panelChat.Name = "panelChat";
            this.panelChat.Size = new System.Drawing.Size(257, 239);
            this.panelChat.TabIndex = 14;
            // 
            // chatTextBox
            // 
            this.chatTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chatTextBox.Location = new System.Drawing.Point(14, 207);
            this.chatTextBox.Name = "chatTextBox";
            this.chatTextBox.Size = new System.Drawing.Size(175, 20);
            this.chatTextBox.TabIndex = 15;
            this.chatTextBox.Enter += new System.EventHandler(this.chatTextBox_Enter);
            this.chatTextBox.Leave += new System.EventHandler(this.chatTextBox_Leave);
            // 
            // chatListBox
            // 
            this.chatListBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chatListBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.chatListBox.CausesValidation = false;
            this.chatListBox.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chatListBox.IntegralHeight = false;
            this.chatListBox.ItemHeight = 17;
            this.chatListBox.Location = new System.Drawing.Point(12, 5);
            this.chatListBox.Name = "chatListBox";
            this.chatListBox.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.chatListBox.Size = new System.Drawing.Size(210, 186);
            this.chatListBox.TabIndex = 13;
            this.chatListBox.TabStop = false;
            this.chatListBox.UseTabStops = false;
            // 
            // userListBox
            // 
            this.userListBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.userListBox.FormattingEnabled = true;
            this.userListBox.Location = new System.Drawing.Point(6, 31);
            this.userListBox.Name = "userListBox";
            this.userListBox.Size = new System.Drawing.Size(216, 199);
            this.userListBox.TabIndex = 17;
            // 
            // ChannelListBox
            // 
            this.ChannelListBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ChannelListBox.FormattingEnabled = true;
            this.ChannelListBox.Location = new System.Drawing.Point(6, 5);
            this.ChannelListBox.Name = "ChannelListBox";
            this.ChannelListBox.Size = new System.Drawing.Size(216, 147);
            this.ChannelListBox.TabIndex = 18;
            // 
            // panelChannel
            // 
            this.panelChannel.Controls.Add(this.createButton);
            this.panelChannel.Controls.Add(this.warningLabel);
            this.panelChannel.Controls.Add(this.addChannelTextBox);
            this.panelChannel.Controls.Add(this.joinButton);
            this.panelChannel.Controls.Add(this.leaveButton);
            this.panelChannel.Controls.Add(this.ChannelListBox);
            this.panelChannel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelChannel.Location = new System.Drawing.Point(0, 0);
            this.panelChannel.Name = "panelChannel";
            this.panelChannel.Size = new System.Drawing.Size(257, 239);
            this.panelChannel.TabIndex = 19;
            this.panelChannel.VisibleChanged += new System.EventHandler(this.panelChannel_VisibleChanged);
            // 
            // warningLabel
            // 
            this.warningLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.warningLabel.AutoSize = true;
            this.warningLabel.ForeColor = System.Drawing.Color.Red;
            this.warningLabel.Location = new System.Drawing.Point(10, 220);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(35, 13);
            this.warningLabel.TabIndex = 22;
            this.warningLabel.Text = "label1";
            this.warningLabel.Visible = false;
            // 
            // addChannelTextBox
            // 
            this.addChannelTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addChannelTextBox.Location = new System.Drawing.Point(8, 197);
            this.addChannelTextBox.Name = "addChannelTextBox";
            this.addChannelTextBox.Size = new System.Drawing.Size(150, 20);
            this.addChannelTextBox.TabIndex = 21;
            this.addChannelTextBox.Enter += new System.EventHandler(this.addChannelTextBox_Enter);
            this.addChannelTextBox.Leave += new System.EventHandler(this.addChannelTextBox_Leave);
            this.addChannelTextBox.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.addChannelTextBox_PreviewKeyDown);
            // 
            // panelUser
            // 
            this.panelUser.Controls.Add(this.label1);
            this.panelUser.Controls.Add(this.userListBox);
            this.panelUser.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelUser.Location = new System.Drawing.Point(0, 0);
            this.panelUser.Name = "panelUser";
            this.panelUser.Size = new System.Drawing.Size(257, 239);
            this.panelUser.TabIndex = 20;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(4, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(154, 21);
            this.label1.TabIndex = 18;
            this.label1.Text = "Liste d\'utilisateur(s)";
            // 
            // panel
            // 
            this.panel.Controls.Add(this.panelChannel);
            this.panel.Controls.Add(this.panelChat);
            this.panel.Controls.Add(this.panelUser);
            this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel.Location = new System.Drawing.Point(0, 0);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(257, 239);
            this.panel.TabIndex = 21;
            // 
            // channelButton
            // 
            this.channelButton.BackColor = System.Drawing.Color.Transparent;
            this.channelButton.Controls.Add(this.channelPictureBox);
            this.channelButton.Location = new System.Drawing.Point(0, 120);
            this.channelButton.Name = "channelButton";
            this.channelButton.Size = new System.Drawing.Size(20, 119);
            this.channelButton.TabIndex = 1;
            this.channelButton.Click += new System.EventHandler(this.channelButton_Click);
            // 
            // channelPictureBox
            // 
            this.channelPictureBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.channelPictureBox.Enabled = false;
            this.channelPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("channelPictureBox.Image")));
            this.channelPictureBox.Location = new System.Drawing.Point(2, 55);
            this.channelPictureBox.Name = "channelPictureBox";
            this.channelPictureBox.Size = new System.Drawing.Size(16, 16);
            this.channelPictureBox.TabIndex = 0;
            this.channelPictureBox.TabStop = false;
            // 
            // userButton
            // 
            this.userButton.BackColor = System.Drawing.Color.Transparent;
            this.userButton.Controls.Add(this.userPictureBox);
            this.userButton.Location = new System.Drawing.Point(0, 0);
            this.userButton.Name = "userButton";
            this.userButton.Size = new System.Drawing.Size(20, 119);
            this.userButton.TabIndex = 0;
            this.userButton.Click += new System.EventHandler(this.userButton_Click);
            // 
            // userPictureBox
            // 
            this.userPictureBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.userPictureBox.Enabled = false;
            this.userPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("userPictureBox.Image")));
            this.userPictureBox.Location = new System.Drawing.Point(2, 55);
            this.userPictureBox.Name = "userPictureBox";
            this.userPictureBox.Size = new System.Drawing.Size(16, 16);
            this.userPictureBox.TabIndex = 0;
            this.userPictureBox.TabStop = false;
            // 
            // sendButton
            // 
            this.sendButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sendButton.BackColor = System.Drawing.Color.Transparent;
            this.sendButton.Controls.Add(this.pictureBox3);
            this.sendButton.Location = new System.Drawing.Point(196, 201);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(26, 26);
            this.sendButton.TabIndex = 14;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click_1);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(1, 1);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 0;
            this.pictureBox3.TabStop = false;
            // 
            // createButton
            // 
            this.createButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.createButton.Controls.Add(this.customLabel3);
            this.createButton.Location = new System.Drawing.Point(164, 197);
            this.createButton.Name = "createButton";
            this.createButton.Size = new System.Drawing.Size(58, 20);
            this.createButton.TabIndex = 23;
            this.createButton.Click += new System.EventHandler(this.createButton_Click);
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(15, 2);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(37, 15);
            this.customLabel3.TabIndex = 0;
            this.customLabel3.Text = "Créer";
            // 
            // joinButton
            // 
            this.joinButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.joinButton.Controls.Add(this.customLabel2);
            this.joinButton.Location = new System.Drawing.Point(112, 158);
            this.joinButton.Name = "joinButton";
            this.joinButton.Size = new System.Drawing.Size(100, 33);
            this.joinButton.TabIndex = 20;
            this.joinButton.Click += new System.EventHandler(this.joinButton_Click);
            // 
            // customLabel2
            // 
            this.customLabel2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(3, 7);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(82, 16);
            this.customLabel2.TabIndex = 0;
            this.customLabel2.Text = "Joindre canal";
            // 
            // leaveButton
            // 
            this.leaveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.leaveButton.Controls.Add(this.customLabel1);
            this.leaveButton.Location = new System.Drawing.Point(6, 158);
            this.leaveButton.Name = "leaveButton";
            this.leaveButton.Size = new System.Drawing.Size(100, 33);
            this.leaveButton.TabIndex = 19;
            this.leaveButton.Click += new System.EventHandler(this.leaveButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(3, 7);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(97, 16);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Quitter ce canal";
            // 
            // UserChatChannel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panelForButtons);
            this.Controls.Add(this.panel);
            this.Name = "UserChatChannel";
            this.Size = new System.Drawing.Size(257, 239);
            this.Resize += new System.EventHandler(this.UserChatChannel_Resize);
            this.panelForButtons.ResumeLayout(false);
            this.panelChat.ResumeLayout(false);
            this.panelChat.PerformLayout();
            this.panelChannel.ResumeLayout(false);
            this.panelChannel.PerformLayout();
            this.panelUser.ResumeLayout(false);
            this.panelUser.PerformLayout();
            this.panel.ResumeLayout(false);
            this.channelButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.channelPictureBox)).EndInit();
            this.userButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.userPictureBox)).EndInit();
            this.sendButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.createButton.ResumeLayout(false);
            this.createButton.PerformLayout();
            this.joinButton.ResumeLayout(false);
            this.joinButton.PerformLayout();
            this.leaveButton.ResumeLayout(false);
            this.leaveButton.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panelForButtons;
        private PanelButton channelButton;
        private PanelButton userButton;
        private System.Windows.Forms.PictureBox channelPictureBox;
        private System.Windows.Forms.PictureBox userPictureBox;
        private System.Windows.Forms.Panel panelChat;
        private System.Windows.Forms.TextBox chatTextBox;
        private PanelButton sendButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.ListBox chatListBox;
        private System.Windows.Forms.ListBox userListBox;
        private System.Windows.Forms.ListBox ChannelListBox;
        private System.Windows.Forms.Panel panelChannel;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.TextBox addChannelTextBox;
        private PanelButton joinButton;
        private CustomLabel customLabel2;
        private PanelButton leaveButton;
        private CustomLabel customLabel1;
        private System.Windows.Forms.Panel panelUser;
        private System.Windows.Forms.Panel panel;
        private CustomLabel customLabel3;
        private PanelButton createButton;
        private System.Windows.Forms.Label label1;
    }
}
