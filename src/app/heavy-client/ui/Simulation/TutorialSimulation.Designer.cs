﻿namespace ui
{
    partial class TutorialSimulation
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TutorialSimulation));
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.previousButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.nextButton = new ui.PanelButton();
            this.nextLabel = new ui.CustomLabel();
            this.nextPictureBox = new System.Windows.Forms.PictureBox();
            this.instructionBox = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.previousButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.nextButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).BeginInit();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel1.Controls.Add(this.pictureBox);
            this.panel1.Controls.Add(this.previousButton);
            this.panel1.Controls.Add(this.nextButton);
            this.panel1.Controls.Add(this.instructionBox);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(596, 300);
            this.panel1.TabIndex = 0;
            // 
            // pictureBox
            // 
            this.pictureBox.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox.Image")));
            this.pictureBox.Location = new System.Drawing.Point(405, 35);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(188, 208);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox.TabIndex = 4;
            this.pictureBox.TabStop = false;
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
            this.nextButton.Location = new System.Drawing.Point(465, 262);
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
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(5, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(188, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tutoriel Pour Simulation";
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel2.Controls.Add(this.panel1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(602, 306);
            this.panel2.TabIndex = 1;
            // 
            // TutorialSimulation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.panel2);
            this.Name = "TutorialSimulation";
            this.Size = new System.Drawing.Size(602, 306);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.previousButton.ResumeLayout(false);
            this.previousButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.nextButton.ResumeLayout(false);
            this.nextButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nextPictureBox)).EndInit();
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ListBox instructionBox;
        private System.Windows.Forms.Label label1;
        private PanelButton previousButton;
        private CustomLabel customLabel2;
        private System.Windows.Forms.PictureBox pictureBox2;
        private PanelButton nextButton;
        private CustomLabel nextLabel;
        private System.Windows.Forms.PictureBox nextPictureBox;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PictureBox pictureBox;
    }
}
