namespace ui
{
    partial class MapMenu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapMenu));
            this.mapPanel = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.returnPictureBox = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.addPanel = new System.Windows.Forms.Panel();
            this.confirmeButton = new ui.PanelButton();
            this.customLabel5 = new ui.CustomLabel();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.privateCheckBox = new System.Windows.Forms.CheckBox();
            this.publicCheckBox = new System.Windows.Forms.CheckBox();
            this.customLabel4 = new ui.CustomLabel();
            this.warningLabel = new System.Windows.Forms.Label();
            this.textBox = new System.Windows.Forms.TextBox();
            this.nameLabel = new ui.CustomLabel();
            this.fileDirLabel = new ui.CustomLabel();
            this.importButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.cancelButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.returnButton = new ui.PanelButton();
            this.createButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.returnPictureBox)).BeginInit();
            this.panel1.SuspendLayout();
            this.addPanel.SuspendLayout();
            this.confirmeButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.importButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.cancelButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.returnButton.SuspendLayout();
            this.createButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // mapPanel
            // 
            this.mapPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mapPanel.AutoScroll = true;
            this.mapPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mapPanel.Location = new System.Drawing.Point(5, 5);
            this.mapPanel.Margin = new System.Windows.Forms.Padding(5);
            this.mapPanel.Name = "mapPanel";
            this.mapPanel.Size = new System.Drawing.Size(600, 394);
            this.mapPanel.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(124, 9);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(64, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Test";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // returnPictureBox
            // 
            this.returnPictureBox.Enabled = false;
            this.returnPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("returnPictureBox.Image")));
            this.returnPictureBox.Location = new System.Drawing.Point(6, 6);
            this.returnPictureBox.Name = "returnPictureBox";
            this.returnPictureBox.Size = new System.Drawing.Size(24, 24);
            this.returnPictureBox.TabIndex = 2;
            this.returnPictureBox.TabStop = false;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(272, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 21);
            this.label1.TabIndex = 3;
            this.label1.Text = "Cartes en ligne";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel1.Controls.Add(this.addPanel);
            this.panel1.Controls.Add(this.mapPanel);
            this.panel1.Location = new System.Drawing.Point(30, 41);
            this.panel1.Margin = new System.Windows.Forms.Padding(30);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(610, 404);
            this.panel1.TabIndex = 4;
            // 
            // addPanel
            // 
            this.addPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.addPanel.Controls.Add(this.confirmeButton);
            this.addPanel.Controls.Add(this.privateCheckBox);
            this.addPanel.Controls.Add(this.publicCheckBox);
            this.addPanel.Controls.Add(this.customLabel4);
            this.addPanel.Controls.Add(this.warningLabel);
            this.addPanel.Controls.Add(this.textBox);
            this.addPanel.Controls.Add(this.nameLabel);
            this.addPanel.Controls.Add(this.fileDirLabel);
            this.addPanel.Controls.Add(this.importButton);
            this.addPanel.Controls.Add(this.cancelButton);
            this.addPanel.Location = new System.Drawing.Point(3, 4);
            this.addPanel.Margin = new System.Windows.Forms.Padding(5);
            this.addPanel.Name = "addPanel";
            this.addPanel.Size = new System.Drawing.Size(600, 394);
            this.addPanel.TabIndex = 0;
            this.addPanel.Visible = false;
            // 
            // confirmeButton
            // 
            this.confirmeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.confirmeButton.Controls.Add(this.customLabel5);
            this.confirmeButton.Controls.Add(this.pictureBox4);
            this.confirmeButton.Location = new System.Drawing.Point(369, 4);
            this.confirmeButton.Name = "confirmeButton";
            this.confirmeButton.Size = new System.Drawing.Size(228, 36);
            this.confirmeButton.TabIndex = 8;
            this.confirmeButton.Click += new System.EventHandler(this.confirmeButton_Click);
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(10, 7);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(174, 21);
            this.customLabel5.TabIndex = 3;
            this.customLabel5.Text = "Confirmer la création";
            // 
            // pictureBox4
            // 
            this.pictureBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(197, 6);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(24, 24);
            this.pictureBox4.TabIndex = 2;
            this.pictureBox4.TabStop = false;
            // 
            // privateCheckBox
            // 
            this.privateCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.privateCheckBox.AutoSize = true;
            this.privateCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.privateCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.privateCheckBox.Location = new System.Drawing.Point(204, 235);
            this.privateCheckBox.Name = "privateCheckBox";
            this.privateCheckBox.Size = new System.Drawing.Size(76, 25);
            this.privateCheckBox.TabIndex = 15;
            this.privateCheckBox.Text = "Privée";
            this.privateCheckBox.UseVisualStyleBackColor = true;
            this.privateCheckBox.Click += new System.EventHandler(this.privateCheckBox_Click);
            // 
            // publicCheckBox
            // 
            this.publicCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.publicCheckBox.AutoSize = true;
            this.publicCheckBox.Checked = true;
            this.publicCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.publicCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.publicCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.publicCheckBox.Location = new System.Drawing.Point(204, 204);
            this.publicCheckBox.Name = "publicCheckBox";
            this.publicCheckBox.Size = new System.Drawing.Size(96, 25);
            this.publicCheckBox.TabIndex = 14;
            this.publicCheckBox.Text = "Publique";
            this.publicCheckBox.UseVisualStyleBackColor = true;
            this.publicCheckBox.Click += new System.EventHandler(this.publicCheckBox_Click);
            // 
            // customLabel4
            // 
            this.customLabel4.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(200, 180);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(182, 21);
            this.customLabel4.TabIndex = 13;
            this.customLabel4.Text = "Droit de modification :";
            // 
            // warningLabel
            // 
            this.warningLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.warningLabel.AutoSize = true;
            this.warningLabel.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.warningLabel.ForeColor = System.Drawing.Color.Brown;
            this.warningLabel.Location = new System.Drawing.Point(200, 125);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(91, 17);
            this.warningLabel.TabIndex = 12;
            this.warningLabel.Text = "Warning label";
            this.warningLabel.Visible = false;
            // 
            // textBox
            // 
            this.textBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.textBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox.Location = new System.Drawing.Point(200, 95);
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(189, 27);
            this.textBox.TabIndex = 11;
            // 
            // nameLabel
            // 
            this.nameLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nameLabel.AutoSize = true;
            this.nameLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nameLabel.ForeColor = System.Drawing.Color.Silver;
            this.nameLabel.Location = new System.Drawing.Point(200, 71);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(145, 21);
            this.nameLabel.TabIndex = 10;
            this.nameLabel.Text = "Nom de la carte :";
            // 
            // fileDirLabel
            // 
            this.fileDirLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.fileDirLabel.AutoSize = true;
            this.fileDirLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileDirLabel.ForeColor = System.Drawing.Color.Silver;
            this.fileDirLabel.Location = new System.Drawing.Point(200, 329);
            this.fileDirLabel.Name = "fileDirLabel";
            this.fileDirLabel.Size = new System.Drawing.Size(99, 21);
            this.fileDirLabel.TabIndex = 9;
            this.fileDirLabel.Text = "fileNameDir";
            // 
            // importButton
            // 
            this.importButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.importButton.Controls.Add(this.customLabel3);
            this.importButton.Controls.Add(this.pictureBox3);
            this.importButton.Location = new System.Drawing.Point(190, 290);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(210, 36);
            this.importButton.TabIndex = 8;
            this.importButton.Click += new System.EventHandler(this.importButton_Click);
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(10, 7);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(159, 21);
            this.customLabel3.TabIndex = 3;
            this.customLabel3.Text = "Importer une carte";
            // 
            // pictureBox3
            // 
            this.pictureBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Location = new System.Drawing.Point(179, 6);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // cancelButton
            // 
            this.cancelButton.Controls.Add(this.customLabel2);
            this.cancelButton.Controls.Add(this.pictureBox2);
            this.cancelButton.Location = new System.Drawing.Point(5, 4);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(210, 36);
            this.cancelButton.TabIndex = 7;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(10, 7);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(159, 21);
            this.customLabel2.TabIndex = 3;
            this.customLabel2.Text = "Annuler la création";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(179, 6);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.TabIndex = 2;
            this.pictureBox2.TabStop = false;
            // 
            // returnButton
            // 
            this.returnButton.Controls.Add(this.returnPictureBox);
            this.returnButton.Location = new System.Drawing.Point(38, 2);
            this.returnButton.Name = "returnButton";
            this.returnButton.Size = new System.Drawing.Size(36, 36);
            this.returnButton.TabIndex = 5;
            this.returnButton.Click += new System.EventHandler(this.returnButton_Click);
            // 
            // createButton
            // 
            this.createButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.createButton.Controls.Add(this.customLabel1);
            this.createButton.Controls.Add(this.pictureBox1);
            this.createButton.Location = new System.Drawing.Point(483, 1);
            this.createButton.Name = "createButton";
            this.createButton.Size = new System.Drawing.Size(147, 36);
            this.createButton.TabIndex = 6;
            this.createButton.Click += new System.EventHandler(this.createButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(10, 7);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(100, 21);
            this.customLabel1.TabIndex = 3;
            this.customLabel1.Text = "Créer carte";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(116, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // MapMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.createButton);
            this.Controls.Add(this.returnButton);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Name = "MapMenu";
            this.Size = new System.Drawing.Size(670, 475);
            ((System.ComponentModel.ISupportInitialize)(this.returnPictureBox)).EndInit();
            this.panel1.ResumeLayout(false);
            this.addPanel.ResumeLayout(false);
            this.addPanel.PerformLayout();
            this.confirmeButton.ResumeLayout(false);
            this.confirmeButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.importButton.ResumeLayout(false);
            this.importButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.cancelButton.ResumeLayout(false);
            this.cancelButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.returnButton.ResumeLayout(false);
            this.createButton.ResumeLayout(false);
            this.createButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel mapPanel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.PictureBox returnPictureBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel addPanel;
        private PanelButton returnButton;
        private PanelButton createButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private CustomLabel customLabel1;
        private PanelButton importButton;
        private CustomLabel customLabel3;
        private System.Windows.Forms.PictureBox pictureBox3;
        private PanelButton cancelButton;
        private CustomLabel customLabel2;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.CheckBox privateCheckBox;
        private System.Windows.Forms.CheckBox publicCheckBox;
        private CustomLabel customLabel4;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.TextBox textBox;
        private CustomLabel nameLabel;
        private CustomLabel fileDirLabel;
        private PanelButton confirmeButton;
        private CustomLabel customLabel5;
        private System.Windows.Forms.PictureBox pictureBox4;
    }
}
