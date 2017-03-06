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
            this.label1 = new System.Windows.Forms.Label();
            this.instructionBox = new System.Windows.Forms.ListBox();
            this.nextButton = new ui.PanelButton();
            this.nextPictureBox = new System.Windows.Forms.PictureBox();
            this.nextLabel = new ui.CustomLabel();
            this.previousButton = new ui.PanelButton();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.customLabel2 = new ui.CustomLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tutorialPanel.SuspendLayout();
            this.nextButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).BeginInit();
            this.previousButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.panel1.SuspendLayout();
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
            this.tutorialPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.tutorialPanel_MouseDown);
            this.tutorialPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.tutorialPanel_MouseMove);
            this.tutorialPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.tutorialPanel_MouseUp);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(5, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(161, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tutoriel Pour Édition";
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
            // previousButton
            // 
            this.previousButton.Controls.Add(this.customLabel2);
            this.previousButton.Controls.Add(this.pictureBox2);
            this.previousButton.Location = new System.Drawing.Point(9, 262);
            this.previousButton.Name = "previousButton";
            this.previousButton.Size = new System.Drawing.Size(137, 35);
            this.previousButton.TabIndex = 3;
            this.previousButton.Click += new System.EventHandler(this.previousButton_Click);
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
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(35, 5);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(93, 21);
            this.customLabel2.TabIndex = 1;
            this.customLabel2.Text = "Précédant";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel1.Controls.Add(this.previousButton);
            this.panel1.Controls.Add(this.nextButton);
            this.panel1.Controls.Add(this.instructionBox);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(411, 300);
            this.panel1.TabIndex = 0;
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
            this.nextButton.ResumeLayout(false);
            this.nextButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).EndInit();
            this.previousButton.ResumeLayout(false);
            this.previousButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel tutorialPanel;
        private System.Windows.Forms.Panel panel1;
        private PanelButton previousButton;
        private CustomLabel customLabel2;
        private System.Windows.Forms.PictureBox pictureBox2;
        private PanelButton nextButton;
        private CustomLabel nextLabel;
        private System.Windows.Forms.PictureBox nextPictureBox;
        private System.Windows.Forms.ListBox instructionBox;
        private System.Windows.Forms.Label label1;
    }
}
