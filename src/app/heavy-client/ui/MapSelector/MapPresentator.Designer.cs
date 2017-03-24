﻿namespace ui
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
            this.passwordPanel = new System.Windows.Forms.Panel();
            this.publicCheckBox = new System.Windows.Forms.CheckBox();
            this.privateCheckBox = new System.Windows.Forms.CheckBox();
            this.passwordBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.mapButton = new ui.PanelButton();
            this.privacyLabel = new ui.CustomLabel();
            this.customLabel99 = new ui.CustomLabel();
            this.connectionLabel = new ui.CustomLabel();
            this.customLabel5 = new ui.CustomLabel();
            this.numberOfPlayersLabel = new ui.CustomLabel();
            this.NameMapLabel = new ui.CustomLabel();
            this.ModeLabel = new ui.CustomLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.customLabel3 = new ui.CustomLabel();
            this.customLabel2 = new ui.CustomLabel();
            this.customLabel1 = new ui.CustomLabel();
            this.passwordPanel.SuspendLayout();
            this.mapButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // passwordPanel
            // 
            this.passwordPanel.Controls.Add(this.button1);
            this.passwordPanel.Controls.Add(this.label1);
            this.passwordPanel.Controls.Add(this.passwordBox);
            this.passwordPanel.Controls.Add(this.privateCheckBox);
            this.passwordPanel.Controls.Add(this.publicCheckBox);
            this.passwordPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.passwordPanel.Location = new System.Drawing.Point(0, 0);
            this.passwordPanel.Name = "passwordPanel";
            this.passwordPanel.Size = new System.Drawing.Size(600, 150);
            this.passwordPanel.TabIndex = 1;
            this.passwordPanel.Visible = false;
            // 
            // publicCheckBox
            // 
            this.publicCheckBox.AutoSize = true;
            this.publicCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.publicCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.publicCheckBox.Location = new System.Drawing.Point(419, 33);
            this.publicCheckBox.Name = "publicCheckBox";
            this.publicCheckBox.Size = new System.Drawing.Size(96, 25);
            this.publicCheckBox.TabIndex = 0;
            this.publicCheckBox.Text = "Publique";
            this.publicCheckBox.UseVisualStyleBackColor = true;
            this.publicCheckBox.CheckedChanged += new System.EventHandler(this.publicCheckBox_CheckedChanged);
            // 
            // privateCheckBox
            // 
            this.privateCheckBox.AutoSize = true;
            this.privateCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.privateCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.privateCheckBox.Location = new System.Drawing.Point(419, 74);
            this.privateCheckBox.Name = "privateCheckBox";
            this.privateCheckBox.Size = new System.Drawing.Size(76, 25);
            this.privateCheckBox.TabIndex = 1;
            this.privateCheckBox.Text = "Privée";
            this.privateCheckBox.UseVisualStyleBackColor = true;
            this.privateCheckBox.CheckedChanged += new System.EventHandler(this.privateCheckBox_CheckedChanged);
            // 
            // passwordBox
            // 
            this.passwordBox.Location = new System.Drawing.Point(24, 68);
            this.passwordBox.Name = "passwordBox";
            this.passwordBox.PasswordChar = '*';
            this.passwordBox.Size = new System.Drawing.Size(188, 20);
            this.passwordBox.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(24, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 21);
            this.label1.TabIndex = 3;
            this.label1.Text = "Mot de passe";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(137, 94);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "Connecter";
            this.button1.UseVisualStyleBackColor = true;
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
            this.mapButton.Controls.Add(this.panel1);
            this.mapButton.Controls.Add(this.customLabel3);
            this.mapButton.Controls.Add(this.customLabel2);
            this.mapButton.Controls.Add(this.customLabel1);
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
            this.privacyLabel.Location = new System.Drawing.Point(161, 107);
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
            this.customLabel99.Location = new System.Drawing.Point(21, 107);
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
            this.connectionLabel.Location = new System.Drawing.Point(101, 63);
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
            this.customLabel5.Location = new System.Drawing.Point(20, 63);
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
            this.numberOfPlayersLabel.Location = new System.Drawing.Point(191, 86);
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
            this.NameMapLabel.Location = new System.Drawing.Point(101, 38);
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
            this.ModeLabel.Location = new System.Drawing.Point(101, 17);
            this.ModeLabel.Name = "ModeLabel";
            this.ModeLabel.Size = new System.Drawing.Size(93, 21);
            this.ModeLabel.TabIndex = 4;
            this.ModeLabel.Text = "TypeMode";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.LightGray;
            this.panel1.Enabled = false;
            this.panel1.Location = new System.Drawing.Point(362, 10);
            this.panel1.Margin = new System.Windows.Forms.Padding(10);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 130);
            this.panel1.TabIndex = 3;
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(21, 86);
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
            this.customLabel2.Location = new System.Drawing.Point(21, 38);
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
            this.customLabel1.Location = new System.Drawing.Point(21, 17);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(64, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Mode :";
            // 
            // MapPresentator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.passwordPanel);
            this.Controls.Add(this.mapButton);
            this.Name = "MapPresentator";
            this.Size = new System.Drawing.Size(600, 150);
            this.passwordPanel.ResumeLayout(false);
            this.passwordPanel.PerformLayout();
            this.mapButton.ResumeLayout(false);
            this.mapButton.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private PanelButton mapButton;
        private CustomLabel numberOfPlayersLabel;
        private CustomLabel NameMapLabel;
        private CustomLabel ModeLabel;
        private System.Windows.Forms.Panel panel1;
        private CustomLabel customLabel3;
        private CustomLabel customLabel2;
        private CustomLabel customLabel1;
        private CustomLabel connectionLabel;
        private CustomLabel customLabel5;
        private CustomLabel privacyLabel;
        private CustomLabel customLabel99;
        private System.Windows.Forms.Panel passwordPanel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox passwordBox;
        private System.Windows.Forms.CheckBox privateCheckBox;
        private System.Windows.Forms.CheckBox publicCheckBox;
    }
}
