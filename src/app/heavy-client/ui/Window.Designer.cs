namespace ui
{
    partial class Window
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

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Window));
            this.viewPort = new System.Windows.Forms.Panel();
            this.picturePause = new System.Windows.Forms.PictureBox();
            this.viewPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).BeginInit();
            this.SuspendLayout();
            // 
            // viewPort
            // 
            this.viewPort.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.viewPort.BackColor = System.Drawing.SystemColors.Control;
            this.viewPort.Controls.Add(this.picturePause);
            this.viewPort.Location = new System.Drawing.Point(0, 0);
            this.viewPort.MinimumSize = new System.Drawing.Size(100, 100);
            this.viewPort.Name = "viewPort";
            this.viewPort.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort.Size = new System.Drawing.Size(799, 536);
            this.viewPort.TabIndex = 0;
            this.viewPort.MouseMove += new System.Windows.Forms.MouseEventHandler(this.viewPort_MouseMove);
            this.viewPort.MouseUp += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseUp);
            this.viewPort.Resize += new System.EventHandler(this.viewPort_Resize);
            // 
            // picturePause
            // 
            this.picturePause.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picturePause.Image = ((System.Drawing.Image)(resources.GetObject("picturePause.Image")));
            this.picturePause.Location = new System.Drawing.Point(355, 208);
            this.picturePause.Name = "picturePause";
            this.picturePause.Size = new System.Drawing.Size(96, 96);
            this.picturePause.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.picturePause.TabIndex = 0;
            this.picturePause.TabStop = false;
            this.picturePause.Visible = false;
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(799, 536);
            this.Controls.Add(this.viewPort);
            this.MinimumSize = new System.Drawing.Size(815, 575);
            this.Name = "Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.viewPort.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        public System.Windows.Forms.Panel viewPort;
        public System.Windows.Forms.PictureBox picturePause;
    }
}

