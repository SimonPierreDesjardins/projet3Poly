namespace ui
{
    partial class MapPresentator
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapPresentator));
            this.mapButton = new ui.PanelButton();
            this.privacyLabel = new ui.CustomLabel();
            this.customLabel99 = new ui.CustomLabel();
            this.connectionLabel = new ui.CustomLabel();
            this.customLabel5 = new ui.CustomLabel();
            this.numberOfPlayersLabel = new ui.CustomLabel();
            this.NameMapLabel = new ui.CustomLabel();
            this.ModeLabel = new ui.CustomLabel();
            this.customLabel3 = new ui.CustomLabel();
            this.customLabel2 = new ui.CustomLabel();
            this.customLabel1 = new ui.CustomLabel();
            this.settingsPanel = new System.Windows.Forms.Panel();
            this.updateButton = new System.Windows.Forms.Button();
            this.returnButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.privateCheckBox = new System.Windows.Forms.CheckBox();
            this.publicCheckBox = new System.Windows.Forms.CheckBox();
            this.newPasswordLabel = new System.Windows.Forms.Label();
            this.newPasswordBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.privatePanel = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.settingsButton = new ui.PanelButton();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.customLabel4 = new ui.CustomLabel();
            this.passewordLabel = new System.Windows.Forms.Label();
            this.connectButton = new System.Windows.Forms.Button();
            this.passwordBox = new System.Windows.Forms.TextBox();
            this.mapButton.SuspendLayout();
            this.settingsPanel.SuspendLayout();
            this.returnButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.privatePanel.SuspendLayout();
            this.settingsButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // mapButton
            // 
            this.mapButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mapButton.Controls.Add(this.privacyLabel);
            this.mapButton.Controls.Add(this.customLabel99);
            this.mapButton.Controls.Add(this.connectionLabel);
            this.mapButton.Controls.Add(this.customLabel5);
            this.mapButton.Controls.Add(this.numberOfPlayersLabel);
            this.mapButton.Controls.Add(this.NameMapLabel);
            this.mapButton.Controls.Add(this.ModeLabel);
            this.mapButton.Controls.Add(this.customLabel3);
            this.mapButton.Controls.Add(this.customLabel2);
            this.mapButton.Controls.Add(this.customLabel1);
            this.mapButton.Controls.Add(this.privatePanel);
            this.mapButton.Controls.Add(this.settingsPanel);
            this.mapButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mapButton.Location = new System.Drawing.Point(0, 0);
            this.mapButton.Name = "mapButton";
            this.mapButton.Size = new System.Drawing.Size(600, 150);
            this.mapButton.TabIndex = 0;
            this.mapButton.Click += new System.EventHandler(this.mapButton_Click);
            // 
            // privacyLabel
            // 
            this.privacyLabel.AutoSize = true;
            this.privacyLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.privacyLabel.ForeColor = System.Drawing.Color.Silver;
            this.privacyLabel.Location = new System.Drawing.Point(162, 107);
            this.privacyLabel.Name = "privacyLabel";
            this.privacyLabel.Size = new System.Drawing.Size(77, 21);
            this.privacyLabel.TabIndex = 10;
            this.privacyLabel.Text = "Publique";
            // 
            // customLabel99
            // 
            this.customLabel99.AutoSize = true;
            this.customLabel99.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel99.ForeColor = System.Drawing.Color.Silver;
            this.customLabel99.Location = new System.Drawing.Point(22, 107);
            this.customLabel99.Name = "customLabel99";
            this.customLabel99.Size = new System.Drawing.Size(134, 21);
            this.customLabel99.TabIndex = 9;
            this.customLabel99.Text = "Confidentialité :";
            // 
            // connectionLabel
            // 
            this.connectionLabel.AutoSize = true;
            this.connectionLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.connectionLabel.ForeColor = System.Drawing.Color.Silver;
            this.connectionLabel.Location = new System.Drawing.Point(101, 65);
            this.connectionLabel.Name = "connectionLabel";
            this.connectionLabel.Size = new System.Drawing.Size(154, 21);
            this.connectionLabel.TabIndex = 8;
            this.connectionLabel.Text = "HorsLigne / Enligne";
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(20, 65);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(75, 21);
            this.customLabel5.TabIndex = 7;
            this.customLabel5.Text = "Réseau :";
            // 
            // numberOfPlayersLabel
            // 
            this.numberOfPlayersLabel.AutoSize = true;
            this.numberOfPlayersLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.numberOfPlayersLabel.ForeColor = System.Drawing.Color.Silver;
            this.numberOfPlayersLabel.Location = new System.Drawing.Point(192, 86);
            this.numberOfPlayersLabel.Name = "numberOfPlayersLabel";
            this.numberOfPlayersLabel.Size = new System.Drawing.Size(31, 21);
            this.numberOfPlayersLabel.TabIndex = 6;
            this.numberOfPlayersLabel.Text = "#1";
            // 
            // NameMapLabel
            // 
            this.NameMapLabel.AutoSize = true;
            this.NameMapLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NameMapLabel.ForeColor = System.Drawing.Color.Silver;
            this.NameMapLabel.Location = new System.Drawing.Point(101, 17);
            this.NameMapLabel.Name = "NameMapLabel";
            this.NameMapLabel.Size = new System.Drawing.Size(95, 21);
            this.NameMapLabel.TabIndex = 5;
            this.NameMapLabel.Text = "NameMap";
            // 
            // ModeLabel
            // 
            this.ModeLabel.AutoSize = true;
            this.ModeLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ModeLabel.ForeColor = System.Drawing.Color.Silver;
            this.ModeLabel.Location = new System.Drawing.Point(101, 44);
            this.ModeLabel.Name = "ModeLabel";
            this.ModeLabel.Size = new System.Drawing.Size(93, 21);
            this.ModeLabel.TabIndex = 4;
            this.ModeLabel.Text = "TypeMode";
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(22, 86);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(164, 21);
            this.customLabel3.TabIndex = 2;
            this.customLabel3.Text = "Nombre de joueurs :";
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(21, 17);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(55, 21);
            this.customLabel2.TabIndex = 1;
            this.customLabel2.Text = "Nom :";
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(21, 44);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(64, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Mode :";
            // 
            // settingsPanel
            // 
            this.settingsPanel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.settingsPanel.Controls.Add(this.updateButton);
            this.settingsPanel.Controls.Add(this.returnButton);
            this.settingsPanel.Controls.Add(this.privateCheckBox);
            this.settingsPanel.Controls.Add(this.publicCheckBox);
            this.settingsPanel.Controls.Add(this.newPasswordLabel);
            this.settingsPanel.Controls.Add(this.newPasswordBox);
            this.settingsPanel.Controls.Add(this.label1);
            this.settingsPanel.Location = new System.Drawing.Point(299, 0);
            this.settingsPanel.Name = "settingsPanel";
            this.settingsPanel.Size = new System.Drawing.Size(301, 150);
            this.settingsPanel.TabIndex = 19;
            this.settingsPanel.Visible = false;
            // 
            // updateButton
            // 
            this.updateButton.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.updateButton.Location = new System.Drawing.Point(209, 102);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(75, 23);
            this.updateButton.TabIndex = 18;
            this.updateButton.Text = "Mettre a jour";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // returnButton
            // 
            this.returnButton.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.returnButton.Controls.Add(this.pictureBox1);
            this.returnButton.Location = new System.Drawing.Point(12, 17);
            this.returnButton.Name = "returnButton";
            this.returnButton.Size = new System.Drawing.Size(44, 39);
            this.returnButton.TabIndex = 22;
            this.returnButton.Click += new System.EventHandler(this.returnButton_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(10, 7);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 21;
            this.pictureBox1.TabStop = false;
            // 
            // privateCheckBox
            // 
            this.privateCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.privateCheckBox.AutoSize = true;
            this.privateCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.privateCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.privateCheckBox.Location = new System.Drawing.Point(196, 26);
            this.privateCheckBox.Name = "privateCheckBox";
            this.privateCheckBox.Size = new System.Drawing.Size(76, 25);
            this.privateCheckBox.TabIndex = 20;
            this.privateCheckBox.Text = "Privée";
            this.privateCheckBox.UseVisualStyleBackColor = true;
            this.privateCheckBox.Click += new System.EventHandler(this.privateCheckBox_Click);
            // 
            // publicCheckBox
            // 
            this.publicCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.publicCheckBox.AutoSize = true;
            this.publicCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.publicCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.publicCheckBox.Location = new System.Drawing.Point(96, 26);
            this.publicCheckBox.Name = "publicCheckBox";
            this.publicCheckBox.Size = new System.Drawing.Size(96, 25);
            this.publicCheckBox.TabIndex = 19;
            this.publicCheckBox.Text = "Publique";
            this.publicCheckBox.UseVisualStyleBackColor = true;
            this.publicCheckBox.Click += new System.EventHandler(this.publicCheckBox_Click);
            // 
            // newPasswordLabel
            // 
            this.newPasswordLabel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.newPasswordLabel.AutoSize = true;
            this.newPasswordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.newPasswordLabel.ForeColor = System.Drawing.Color.Silver;
            this.newPasswordLabel.Location = new System.Drawing.Point(20, 70);
            this.newPasswordLabel.Name = "newPasswordLabel";
            this.newPasswordLabel.Size = new System.Drawing.Size(192, 21);
            this.newPasswordLabel.TabIndex = 17;
            this.newPasswordLabel.Text = "Nouveau mot de passe";
            // 
            // newPasswordBox
            // 
            this.newPasswordBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.newPasswordBox.Location = new System.Drawing.Point(24, 104);
            this.newPasswordBox.Name = "newPasswordBox";
            this.newPasswordBox.PasswordChar = '*';
            this.newPasswordBox.Size = new System.Drawing.Size(175, 20);
            this.newPasswordBox.TabIndex = 16;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(21, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 16);
            this.label1.TabIndex = 23;
            this.label1.Text = "warning";
            this.label1.Visible = false;
            // 
            // privatePanel
            // 
            this.privatePanel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.privatePanel.Controls.Add(this.label2);
            this.privatePanel.Controls.Add(this.settingsButton);
            this.privatePanel.Controls.Add(this.passewordLabel);
            this.privatePanel.Controls.Add(this.connectButton);
            this.privatePanel.Controls.Add(this.passwordBox);
            this.privatePanel.Location = new System.Drawing.Point(299, 0);
            this.privatePanel.Name = "privatePanel";
            this.privatePanel.Size = new System.Drawing.Size(301, 150);
            this.privatePanel.TabIndex = 16;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Red;
            this.label2.Location = new System.Drawing.Point(21, 127);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 16);
            this.label2.TabIndex = 24;
            this.label2.Text = "warning";
            this.label2.Visible = false;
            // 
            // settingsButton
            // 
            this.settingsButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.settingsButton.Controls.Add(this.pictureBox2);
            this.settingsButton.Controls.Add(this.customLabel4);
            this.settingsButton.Location = new System.Drawing.Point(131, 17);
            this.settingsButton.Name = "settingsButton";
            this.settingsButton.Size = new System.Drawing.Size(153, 39);
            this.settingsButton.TabIndex = 19;
            this.settingsButton.Click += new System.EventHandler(this.settingsButton_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(118, 7);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox2.TabIndex = 1;
            this.pictureBox2.TabStop = false;
            // 
            // customLabel4
            // 
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(13, 10);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(99, 21);
            this.customLabel4.TabIndex = 0;
            this.customLabel4.Text = "Paramètres";
            // 
            // passewordLabel
            // 
            this.passewordLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.passewordLabel.AutoSize = true;
            this.passewordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.passewordLabel.ForeColor = System.Drawing.Color.Silver;
            this.passewordLabel.Location = new System.Drawing.Point(20, 70);
            this.passewordLabel.Name = "passewordLabel";
            this.passewordLabel.Size = new System.Drawing.Size(115, 21);
            this.passewordLabel.TabIndex = 17;
            this.passewordLabel.Text = "Mot de passe";
            // 
            // connectButton
            // 
            this.connectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.connectButton.Location = new System.Drawing.Point(209, 102);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 23);
            this.connectButton.TabIndex = 18;
            this.connectButton.Text = "Connecter";
            this.connectButton.UseVisualStyleBackColor = true;
            // 
            // passwordBox
            // 
            this.passwordBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.passwordBox.Location = new System.Drawing.Point(24, 104);
            this.passwordBox.Name = "passwordBox";
            this.passwordBox.PasswordChar = '*';
            this.passwordBox.Size = new System.Drawing.Size(175, 20);
            this.passwordBox.TabIndex = 16;
            // 
            // MapPresentator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.mapButton);
            this.Name = "MapPresentator";
            this.Size = new System.Drawing.Size(600, 150);
            this.mapButton.ResumeLayout(false);
            this.mapButton.PerformLayout();
            this.settingsPanel.ResumeLayout(false);
            this.settingsPanel.PerformLayout();
            this.returnButton.ResumeLayout(false);
            this.returnButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.privatePanel.ResumeLayout(false);
            this.privatePanel.PerformLayout();
            this.settingsButton.ResumeLayout(false);
            this.settingsButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private PanelButton mapButton;
        private CustomLabel privacyLabel;
        private CustomLabel customLabel99;
        private CustomLabel connectionLabel;
        private CustomLabel customLabel5;
        private CustomLabel numberOfPlayersLabel;
        private CustomLabel NameMapLabel;
        private CustomLabel ModeLabel;
        private CustomLabel customLabel3;
        private CustomLabel customLabel2;
        private CustomLabel customLabel1;
        private System.Windows.Forms.Panel privatePanel;
        private PanelButton settingsButton;
        private System.Windows.Forms.PictureBox pictureBox2;
        private CustomLabel customLabel4;
        private System.Windows.Forms.Label passewordLabel;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.TextBox passwordBox;
        private System.Windows.Forms.Panel settingsPanel;
        private PanelButton returnButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.CheckBox privateCheckBox;
        private System.Windows.Forms.CheckBox publicCheckBox;
        private System.Windows.Forms.Label newPasswordLabel;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.TextBox newPasswordBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}
