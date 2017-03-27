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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MusicSelector));
            this.label1 = new System.Windows.Forms.Label();
            this.panel = new System.Windows.Forms.Panel();
            this.loadingPanel = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.dot1 = new System.Windows.Forms.Label();
            this.dot2 = new System.Windows.Forms.Label();
            this.dot3 = new System.Windows.Forms.Label();
            this.dot4 = new System.Windows.Forms.Label();
            this.LoadingTimer = new System.Windows.Forms.Timer(this.components);
            this.defaultButton = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.customLabel8 = new ui.CustomLabel();
            this.applyButton = new ui.PanelButton();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.customLabel1 = new ui.CustomLabel();
            this.fileDirLabel = new ui.CustomLabel();
            this.importButton = new ui.PanelButton();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.customLabel3 = new ui.CustomLabel();
            this.panel.SuspendLayout();
            this.loadingPanel.SuspendLayout();
            this.defaultButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.applyButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.importButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(16, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(148, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "Choix de musique";
            // 
            // panel
            // 
            this.panel.Controls.Add(this.defaultButton);
            this.panel.Controls.Add(this.applyButton);
            this.panel.Controls.Add(this.fileDirLabel);
            this.panel.Controls.Add(this.importButton);
            this.panel.Controls.Add(this.label1);
            this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel.Location = new System.Drawing.Point(0, 0);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(381, 145);
            this.panel.TabIndex = 0;
            // 
            // loadingPanel
            // 
            this.loadingPanel.Controls.Add(this.label2);
            this.loadingPanel.Controls.Add(this.dot3);
            this.loadingPanel.Controls.Add(this.dot2);
            this.loadingPanel.Controls.Add(this.dot1);
            this.loadingPanel.Controls.Add(this.dot4);
            this.loadingPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.loadingPanel.Location = new System.Drawing.Point(0, 0);
            this.loadingPanel.Name = "loadingPanel";
            this.loadingPanel.Size = new System.Drawing.Size(381, 145);
            this.loadingPanel.TabIndex = 1;
            this.loadingPanel.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Century Gothic", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Silver;
            this.label2.Location = new System.Drawing.Point(109, 31);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(157, 42);
            this.label2.TabIndex = 0;
            this.label2.Text = "Loading";
            // 
            // dot1
            // 
            this.dot1.AutoSize = true;
            this.dot1.Font = new System.Drawing.Font("Poplar Std", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dot1.ForeColor = System.Drawing.Color.Silver;
            this.dot1.Location = new System.Drawing.Point(106, 56);
            this.dot1.Name = "dot1";
            this.dot1.Size = new System.Drawing.Size(34, 57);
            this.dot1.TabIndex = 1;
            this.dot1.Text = ".";
            // 
            // dot2
            // 
            this.dot2.AutoSize = true;
            this.dot2.Font = new System.Drawing.Font("Poplar Std", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dot2.ForeColor = System.Drawing.Color.Silver;
            this.dot2.Location = new System.Drawing.Point(146, 56);
            this.dot2.Name = "dot2";
            this.dot2.Size = new System.Drawing.Size(34, 57);
            this.dot2.TabIndex = 2;
            this.dot2.Text = ".";
            // 
            // dot3
            // 
            this.dot3.AutoSize = true;
            this.dot3.Font = new System.Drawing.Font("Poplar Std", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dot3.ForeColor = System.Drawing.Color.Silver;
            this.dot3.Location = new System.Drawing.Point(186, 56);
            this.dot3.Name = "dot3";
            this.dot3.Size = new System.Drawing.Size(34, 57);
            this.dot3.TabIndex = 3;
            this.dot3.Text = ".";
            // 
            // dot4
            // 
            this.dot4.AutoSize = true;
            this.dot4.Font = new System.Drawing.Font("Poplar Std", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dot4.ForeColor = System.Drawing.Color.Silver;
            this.dot4.Location = new System.Drawing.Point(226, 56);
            this.dot4.Name = "dot4";
            this.dot4.Size = new System.Drawing.Size(34, 57);
            this.dot4.TabIndex = 4;
            this.dot4.Text = ".";
            // 
            // LoadingTimer
            // 
            this.LoadingTimer.Interval = 500;
            this.LoadingTimer.Tick += new System.EventHandler(this.LoadingTimer_Tick);
            // 
            // defaultButton
            // 
            this.defaultButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.defaultButton.Controls.Add(this.pictureBox3);
            this.defaultButton.Controls.Add(this.customLabel8);
            this.defaultButton.Location = new System.Drawing.Point(20, 103);
            this.defaultButton.Name = "defaultButton";
            this.defaultButton.Size = new System.Drawing.Size(164, 33);
            this.defaultButton.TabIndex = 15;
            this.defaultButton.Click += new System.EventHandler(this.defaultButton_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(10, 5);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // customLabel8
            // 
            this.customLabel8.AutoSize = true;
            this.customLabel8.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel8.ForeColor = System.Drawing.Color.Silver;
            this.customLabel8.Location = new System.Drawing.Point(50, 6);
            this.customLabel8.Name = "customLabel8";
            this.customLabel8.Size = new System.Drawing.Size(71, 21);
            this.customLabel8.TabIndex = 0;
            this.customLabel8.Text = "Annuler";
            // 
            // applyButton
            // 
            this.applyButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.applyButton.Controls.Add(this.pictureBox5);
            this.applyButton.Controls.Add(this.customLabel1);
            this.applyButton.Location = new System.Drawing.Point(196, 103);
            this.applyButton.Name = "applyButton";
            this.applyButton.Size = new System.Drawing.Size(164, 33);
            this.applyButton.TabIndex = 14;
            this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
            // 
            // pictureBox5
            // 
            this.pictureBox5.Enabled = false;
            this.pictureBox5.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox5.Image")));
            this.pictureBox5.Location = new System.Drawing.Point(10, 5);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(24, 24);
            this.pictureBox5.TabIndex = 3;
            this.pictureBox5.TabStop = false;
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(50, 6);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(87, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Appliquer";
            // 
            // fileDirLabel
            // 
            this.fileDirLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.fileDirLabel.AutoSize = true;
            this.fileDirLabel.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileDirLabel.ForeColor = System.Drawing.Color.Silver;
            this.fileDirLabel.Location = new System.Drawing.Point(17, 74);
            this.fileDirLabel.Name = "fileDirLabel";
            this.fileDirLabel.Size = new System.Drawing.Size(83, 17);
            this.fileDirLabel.TabIndex = 11;
            this.fileDirLabel.Text = "fileNameDir";
            // 
            // importButton
            // 
            this.importButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.importButton.Controls.Add(this.pictureBox);
            this.importButton.Controls.Add(this.customLabel3);
            this.importButton.Location = new System.Drawing.Point(20, 35);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(224, 36);
            this.importButton.TabIndex = 10;
            this.importButton.Click += new System.EventHandler(this.importButton_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox.Enabled = false;
            this.pictureBox.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox.Image")));
            this.pictureBox.Location = new System.Drawing.Point(10, 7);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(24, 24);
            this.pictureBox.TabIndex = 4;
            this.pictureBox.TabStop = false;
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(40, 7);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(181, 21);
            this.customLabel3.TabIndex = 3;
            this.customLabel3.Text = "Importer une musique";
            // 
            // MusicSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.panel);
            this.Controls.Add(this.loadingPanel);
            this.Name = "MusicSelector";
            this.Size = new System.Drawing.Size(381, 145);
            this.panel.ResumeLayout(false);
            this.panel.PerformLayout();
            this.loadingPanel.ResumeLayout(false);
            this.loadingPanel.PerformLayout();
            this.defaultButton.ResumeLayout(false);
            this.defaultButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.applyButton.ResumeLayout(false);
            this.applyButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.importButton.ResumeLayout(false);
            this.importButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private PanelButton importButton;
        private CustomLabel customLabel3;
        private CustomLabel fileDirLabel;
        private System.Windows.Forms.Panel panel;
        private System.Windows.Forms.Panel loadingPanel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label dot3;
        private System.Windows.Forms.Label dot2;
        private System.Windows.Forms.Label dot1;
        private System.Windows.Forms.Label dot4;
        private System.Windows.Forms.Timer LoadingTimer;
        private PanelButton defaultButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private CustomLabel customLabel8;
        private PanelButton applyButton;
        private System.Windows.Forms.PictureBox pictureBox5;
        private CustomLabel customLabel1;
        private System.Windows.Forms.PictureBox pictureBox;
    }
}
