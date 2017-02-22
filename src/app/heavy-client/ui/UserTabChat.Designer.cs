namespace ui
{
    partial class UserTabChat
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserTabChat));
            this.minMaxButton = new ui.PanelButton();
            this.minMaxPictureBox = new System.Windows.Forms.PictureBox();
            this.outWindowButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tabControl = new ui.TabControlWithoutHeader();
            this.minMaxButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).BeginInit();
            this.outWindowButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // minMaxButton
            // 
            this.minMaxButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.minMaxButton.BackColor = System.Drawing.Color.Transparent;
            this.minMaxButton.Controls.Add(this.minMaxPictureBox);
            this.minMaxButton.Location = new System.Drawing.Point(205, 3);
            this.minMaxButton.Name = "minMaxButton";
            this.minMaxButton.Size = new System.Drawing.Size(26, 26);
            this.minMaxButton.TabIndex = 2;
            this.minMaxButton.Click += new System.EventHandler(this.minMaxButton_Click);
            // 
            // minMaxPictureBox
            // 
            this.minMaxPictureBox.Enabled = false;
            this.minMaxPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("minMaxPictureBox.Image")));
            this.minMaxPictureBox.Location = new System.Drawing.Point(1, 1);
            this.minMaxPictureBox.Name = "minMaxPictureBox";
            this.minMaxPictureBox.Size = new System.Drawing.Size(24, 24);
            this.minMaxPictureBox.TabIndex = 0;
            this.minMaxPictureBox.TabStop = false;
            // 
            // outWindowButton
            // 
            this.outWindowButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.outWindowButton.BackColor = System.Drawing.Color.Transparent;
            this.outWindowButton.Controls.Add(this.pictureBox1);
            this.outWindowButton.Location = new System.Drawing.Point(236, 3);
            this.outWindowButton.Name = "outWindowButton";
            this.outWindowButton.Size = new System.Drawing.Size(26, 26);
            this.outWindowButton.TabIndex = 1;
            this.outWindowButton.Click += new System.EventHandler(this.outWindowButton_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(1, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl.HotTrack = true;
            this.tabControl.Location = new System.Drawing.Point(0, 31);
            this.tabControl.Margin = new System.Windows.Forms.Padding(0);
            this.tabControl.Name = "tabControl";
            this.tabControl.Padding = new System.Drawing.Point(0, 0);
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(265, 249);
            this.tabControl.TabIndex = 3;
            // 
            // UserTabChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.minMaxButton);
            this.Controls.Add(this.outWindowButton);
            this.Controls.Add(this.tabControl);
            this.Name = "UserTabChat";
            this.Size = new System.Drawing.Size(265, 280);
            this.minMaxButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).EndInit();
            this.outWindowButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private PanelButton outWindowButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private PanelButton minMaxButton;
        private System.Windows.Forms.PictureBox minMaxPictureBox;
        private TabControlWithoutHeader tabControl;
    }
}
