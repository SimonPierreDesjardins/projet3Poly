namespace ui
{
    partial class MusicSelector
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
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.customCheckBox = new System.Windows.Forms.CheckBox();
            this.defaultCheckBox = new System.Windows.Forms.CheckBox();
            this.fileDirLabel = new ui.CustomLabel();
            this.importButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.panel1.SuspendLayout();
            this.importButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(16, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(148, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "Choix de musique";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.customCheckBox);
            this.panel1.Controls.Add(this.defaultCheckBox);
            this.panel1.Controls.Add(this.fileDirLabel);
            this.panel1.Controls.Add(this.importButton);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(258, 207);
            this.panel1.TabIndex = 0;
            // 
            // customCheckBox
            // 
            this.customCheckBox.AutoSize = true;
            this.customCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.customCheckBox.Location = new System.Drawing.Point(20, 81);
            this.customCheckBox.Name = "customCheckBox";
            this.customCheckBox.Size = new System.Drawing.Size(127, 25);
            this.customCheckBox.TabIndex = 13;
            this.customCheckBox.Text = "Personnaliser";
            this.customCheckBox.UseVisualStyleBackColor = true;
            this.customCheckBox.Click += new System.EventHandler(this.customCheckBox_Click);
            // 
            // defaultCheckBox
            // 
            this.defaultCheckBox.AutoSize = true;
            this.defaultCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.defaultCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.defaultCheckBox.Location = new System.Drawing.Point(20, 50);
            this.defaultCheckBox.Name = "defaultCheckBox";
            this.defaultCheckBox.Size = new System.Drawing.Size(84, 25);
            this.defaultCheckBox.TabIndex = 12;
            this.defaultCheckBox.Text = "Défaut";
            this.defaultCheckBox.UseVisualStyleBackColor = true;
            this.defaultCheckBox.Click += new System.EventHandler(this.defaultCheckBox_Click);
            // 
            // fileDirLabel
            // 
            this.fileDirLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.fileDirLabel.AutoSize = true;
            this.fileDirLabel.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileDirLabel.ForeColor = System.Drawing.Color.Silver;
            this.fileDirLabel.Location = new System.Drawing.Point(31, 165);
            this.fileDirLabel.Name = "fileDirLabel";
            this.fileDirLabel.Size = new System.Drawing.Size(83, 17);
            this.fileDirLabel.TabIndex = 11;
            this.fileDirLabel.Text = "fileNameDir";
            this.fileDirLabel.Visible = false;
            // 
            // importButton
            // 
            this.importButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.importButton.Controls.Add(this.customLabel3);
            this.importButton.Controls.Add(this.pictureBox);
            this.importButton.Location = new System.Drawing.Point(20, 126);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(210, 36);
            this.importButton.TabIndex = 10;
            this.importButton.Visible = false;
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
            // pictureBox
            // 
            this.pictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox.Enabled = false;
            this.pictureBox.Location = new System.Drawing.Point(179, 6);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(24, 24);
            this.pictureBox.TabIndex = 2;
            this.pictureBox.TabStop = false;
            // 
            // MusicSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.panel1);
            this.Name = "MusicSelector";
            this.Size = new System.Drawing.Size(258, 207);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.importButton.ResumeLayout(false);
            this.importButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private PanelButton importButton;
        private CustomLabel customLabel3;
        private System.Windows.Forms.PictureBox pictureBox;
        private CustomLabel fileDirLabel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.CheckBox customCheckBox;
        private System.Windows.Forms.CheckBox defaultCheckBox;
    }
}
