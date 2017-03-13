namespace ui
{
    partial class EditionTutorielInstructions
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditionTutorielInstructions));
            this.tutorialPanel = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.instructionBox = new System.Windows.Forms.ListBox();
            this.TitleButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.minMaxButton = new ui.PanelButton();
            this.minMaxPictureBox = new System.Windows.Forms.PictureBox();
            this.previousButton = new ui.PanelButton();
            this.previousLabel = new ui.CustomLabel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.nextButton = new ui.PanelButton();
            this.nextLabel = new ui.CustomLabel();
            this.nextPictureBox = new System.Windows.Forms.PictureBox();
            this.tutorialPanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.TitleButton.SuspendLayout();
            this.minMaxButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).BeginInit();
            this.previousButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.nextButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // tutorialPanel
            // 
            this.tutorialPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.tutorialPanel.Controls.Add(this.panel1);
            this.tutorialPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tutorialPanel.Location = new System.Drawing.Point(0, 0);
            this.tutorialPanel.Name = "tutorialPanel";
            this.tutorialPanel.Size = new System.Drawing.Size(417, 306);
            this.tutorialPanel.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel1.Controls.Add(this.TitleButton);
            this.panel1.Controls.Add(this.minMaxButton);
            this.panel1.Controls.Add(this.previousButton);
            this.panel1.Controls.Add(this.nextButton);
            this.panel1.Controls.Add(this.instructionBox);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(411, 300);
            this.panel1.TabIndex = 0;
            // 
            // instructionBox
            // 
            this.instructionBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.instructionBox.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.instructionBox.ForeColor = System.Drawing.Color.Silver;
            this.instructionBox.FormattingEnabled = true;
            this.instructionBox.ItemHeight = 17;
            this.instructionBox.Location = new System.Drawing.Point(9, 35);
            this.instructionBox.Name = "instructionBox";
            this.instructionBox.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.instructionBox.Size = new System.Drawing.Size(389, 208);
            this.instructionBox.TabIndex = 1;
            // 
            // TitleButton
            // 
            this.TitleButton.Controls.Add(this.customLabel1);
            this.TitleButton.Location = new System.Drawing.Point(9, 0);
            this.TitleButton.Name = "TitleButton";
            this.TitleButton.Size = new System.Drawing.Size(180, 25);
            this.TitleButton.TabIndex = 12;
            this.TitleButton.Click += new System.EventHandler(this.TitleButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(0, 0);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(177, 25);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Tutoriel pour Édition";
            // 
            // minMaxButton
            // 
            this.minMaxButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.minMaxButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.minMaxButton.Controls.Add(this.minMaxPictureBox);
            this.minMaxButton.Location = new System.Drawing.Point(372, 0);
            this.minMaxButton.Name = "minMaxButton";
            this.minMaxButton.Size = new System.Drawing.Size(26, 26);
            this.minMaxButton.TabIndex = 11;
            this.minMaxButton.Click += new System.EventHandler(this.minMaxButton_Click);
            // 
            // minMaxPictureBox
            // 
            this.minMaxPictureBox.Enabled = false;
            this.minMaxPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("minMaxPictureBox.Image")));
            this.minMaxPictureBox.Location = new System.Drawing.Point(1, 1);
            this.minMaxPictureBox.Name = "minMaxPictureBox";
            this.minMaxPictureBox.Size = new System.Drawing.Size(24, 24);
            this.minMaxPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.minMaxPictureBox.TabIndex = 0;
            this.minMaxPictureBox.TabStop = false;
            // 
            // previousButton
            // 
            this.previousButton.Controls.Add(this.previousLabel);
            this.previousButton.Controls.Add(this.pictureBox2);
            this.previousButton.Location = new System.Drawing.Point(9, 262);
            this.previousButton.Name = "previousButton";
            this.previousButton.Size = new System.Drawing.Size(137, 35);
            this.previousButton.TabIndex = 3;
            this.previousButton.Click += new System.EventHandler(this.previousButton_Click);
            // 
            // previousLabel
            // 
            this.previousLabel.AutoSize = true;
            this.previousLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.previousLabel.ForeColor = System.Drawing.Color.Silver;
            this.previousLabel.Location = new System.Drawing.Point(35, 5);
            this.previousLabel.Name = "previousLabel";
            this.previousLabel.Size = new System.Drawing.Size(92, 21);
            this.previousLabel.TabIndex = 1;
            this.previousLabel.Text = "Précédent";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(10, 5);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // nextButton
            // 
            this.nextButton.Controls.Add(this.nextLabel);
            this.nextButton.Controls.Add(this.nextPictureBox);
            this.nextButton.Location = new System.Drawing.Point(285, 262);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(119, 35);
            this.nextButton.TabIndex = 2;
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // nextLabel
            // 
            this.nextLabel.AutoSize = true;
            this.nextLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nextLabel.ForeColor = System.Drawing.Color.Silver;
            this.nextLabel.Location = new System.Drawing.Point(10, 5);
            this.nextLabel.Name = "nextLabel";
            this.nextLabel.Size = new System.Drawing.Size(69, 21);
            this.nextLabel.TabIndex = 1;
            this.nextLabel.Text = "Suivant";
            // 
            // nextPictureBox
            // 
            this.nextPictureBox.Enabled = false;
            this.nextPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("nextPictureBox.Image")));
            this.nextPictureBox.Location = new System.Drawing.Point(85, 5);
            this.nextPictureBox.Name = "nextPictureBox";
            this.nextPictureBox.Size = new System.Drawing.Size(24, 24);
            this.nextPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.nextPictureBox.TabIndex = 0;
            this.nextPictureBox.TabStop = false;
            // 
            // EditionTutorielInstructions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.tutorialPanel);
            this.Name = "EditionTutorielInstructions";
            this.Size = new System.Drawing.Size(417, 306);
            this.tutorialPanel.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.TitleButton.ResumeLayout(false);
            this.minMaxButton.ResumeLayout(false);
            this.minMaxButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).EndInit();
            this.previousButton.ResumeLayout(false);
            this.previousButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.nextButton.ResumeLayout(false);
            this.nextButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel tutorialPanel;
        private System.Windows.Forms.Panel panel1;
        private PanelButton previousButton;
        private CustomLabel previousLabel;
        private System.Windows.Forms.PictureBox pictureBox2;
        private PanelButton nextButton;
        private CustomLabel nextLabel;
        private System.Windows.Forms.PictureBox nextPictureBox;
        private System.Windows.Forms.ListBox instructionBox;
        private PanelButton TitleButton;
        private PanelButton minMaxButton;
        private System.Windows.Forms.PictureBox minMaxPictureBox;
        private CustomLabel customLabel1;
    }
}
