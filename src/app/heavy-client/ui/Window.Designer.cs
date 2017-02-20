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
            this.panneauOperation_ = new System.Windows.Forms.Panel();
            this.textBoxPositionY_ = new System.Windows.Forms.TextBox();
            this.textBoxPositionX_ = new System.Windows.Forms.TextBox();
            this.textBoxRotation_ = new System.Windows.Forms.TextBox();
            this.textboxDimension_ = new System.Windows.Forms.TextBox();
            this.panneauPositionY_ = new System.Windows.Forms.Label();
            this.panneauPositionX_ = new System.Windows.Forms.Label();
            this.panneauDimension_ = new System.Windows.Forms.Label();
            this.panneauRotation_ = new System.Windows.Forms.Label();
            this.viewPort = new System.Windows.Forms.Panel();
            this.picturePause = new System.Windows.Forms.PictureBox();
            this.mainScreen = new System.Windows.Forms.Panel();
            this.panneauOperation_.SuspendLayout();
            this.viewPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).BeginInit();
            this.mainScreen.SuspendLayout();
            this.SuspendLayout();
            // 
            // panneauOperation_
            // 
            this.panneauOperation_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panneauOperation_.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.panneauOperation_.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panneauOperation_.Controls.Add(this.textBoxPositionY_);
            this.panneauOperation_.Controls.Add(this.textBoxPositionX_);
            this.panneauOperation_.Controls.Add(this.textBoxRotation_);
            this.panneauOperation_.Controls.Add(this.textboxDimension_);
            this.panneauOperation_.Controls.Add(this.panneauPositionY_);
            this.panneauOperation_.Controls.Add(this.panneauPositionX_);
            this.panneauOperation_.Controls.Add(this.panneauDimension_);
            this.panneauOperation_.Controls.Add(this.panneauRotation_);
            this.panneauOperation_.Location = new System.Drawing.Point(621, 27);
            this.panneauOperation_.Name = "panneauOperation_";
            this.panneauOperation_.Size = new System.Drawing.Size(128, 223);
            this.panneauOperation_.TabIndex = 8;
            this.panneauOperation_.Visible = false;
            // 
            // textBoxPositionY_
            // 
            this.textBoxPositionY_.Location = new System.Drawing.Point(18, 190);
            this.textBoxPositionY_.Name = "textBoxPositionY_";
            this.textBoxPositionY_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionY_.TabIndex = 7;
            this.textBoxPositionY_.TabStop = false;
            this.textBoxPositionY_.Enter += new System.EventHandler(this.textBoxPositionY__Enter);
            this.textBoxPositionY_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionY__KeyDown);
            this.textBoxPositionY_.Leave += new System.EventHandler(this.textBoxPositionY__Leave);
            // 
            // textBoxPositionX_
            // 
            this.textBoxPositionX_.Location = new System.Drawing.Point(18, 132);
            this.textBoxPositionX_.Name = "textBoxPositionX_";
            this.textBoxPositionX_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionX_.TabIndex = 6;
            this.textBoxPositionX_.TabStop = false;
            this.textBoxPositionX_.Enter += new System.EventHandler(this.textBoxPositionX__Enter);
            this.textBoxPositionX_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionX__KeyDown);
            this.textBoxPositionX_.Leave += new System.EventHandler(this.textBoxPositionX__Leave);
            // 
            // textBoxRotation_
            // 
            this.textBoxRotation_.Location = new System.Drawing.Point(18, 81);
            this.textBoxRotation_.Name = "textBoxRotation_";
            this.textBoxRotation_.Size = new System.Drawing.Size(84, 20);
            this.textBoxRotation_.TabIndex = 5;
            this.textBoxRotation_.TabStop = false;
            this.textBoxRotation_.Enter += new System.EventHandler(this.textBoxRotation__Enter);
            this.textBoxRotation_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxRotation__KeyDown);
            this.textBoxRotation_.Leave += new System.EventHandler(this.textBoxRotation__Leave);
            // 
            // textboxDimension_
            // 
            this.textboxDimension_.Location = new System.Drawing.Point(18, 30);
            this.textboxDimension_.Name = "textboxDimension_";
            this.textboxDimension_.Size = new System.Drawing.Size(84, 20);
            this.textboxDimension_.TabIndex = 4;
            this.textboxDimension_.TabStop = false;
            this.textboxDimension_.Enter += new System.EventHandler(this.textboxDimension__Enter);
            this.textboxDimension_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textboxDimension__KeyDown);
            this.textboxDimension_.Leave += new System.EventHandler(this.textboxDimension__Leave);
            // 
            // panneauPositionY_
            // 
            this.panneauPositionY_.AutoSize = true;
            this.panneauPositionY_.Location = new System.Drawing.Point(15, 174);
            this.panneauPositionY_.Name = "panneauPositionY_";
            this.panneauPositionY_.Size = new System.Drawing.Size(69, 13);
            this.panneauPositionY_.TabIndex = 3;
            this.panneauPositionY_.Text = "Position en Y";
            // 
            // panneauPositionX_
            // 
            this.panneauPositionX_.AutoSize = true;
            this.panneauPositionX_.Location = new System.Drawing.Point(15, 116);
            this.panneauPositionX_.Name = "panneauPositionX_";
            this.panneauPositionX_.Size = new System.Drawing.Size(69, 13);
            this.panneauPositionX_.TabIndex = 2;
            this.panneauPositionX_.Text = "Position en X";
            // 
            // panneauDimension_
            // 
            this.panneauDimension_.AutoSize = true;
            this.panneauDimension_.Location = new System.Drawing.Point(15, 14);
            this.panneauDimension_.Name = "panneauDimension_";
            this.panneauDimension_.Size = new System.Drawing.Size(108, 13);
            this.panneauDimension_.TabIndex = 1;
            this.panneauDimension_.Text = "Facteur de dimension";
            // 
            // panneauRotation_
            // 
            this.panneauRotation_.AutoSize = true;
            this.panneauRotation_.Location = new System.Drawing.Point(15, 65);
            this.panneauRotation_.Name = "panneauRotation_";
            this.panneauRotation_.Size = new System.Drawing.Size(87, 13);
            this.panneauRotation_.TabIndex = 0;
            this.panneauRotation_.Text = "Angle de rotation";
            // 
            // viewPort
            // 
            this.viewPort.AutoSize = true;
            this.viewPort.Controls.Add(this.picturePause);
            this.viewPort.Dock = System.Windows.Forms.DockStyle.Fill;
            this.viewPort.Location = new System.Drawing.Point(0, 0);
            this.viewPort.MinimumSize = new System.Drawing.Size(100, 100);
            this.viewPort.Name = "viewPort";
            this.viewPort.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort.Size = new System.Drawing.Size(749, 536);
            this.viewPort.TabIndex = 0;
            this.viewPort.Visible = false;
            this.viewPort.MouseMove += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseMove);
            this.viewPort.MouseUp += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseUp);
            this.viewPort.Resize += new System.EventHandler(this.viewPort_Resize);
            // 
            // picturePause
            // 
            this.picturePause.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picturePause.Image = ((System.Drawing.Image)(resources.GetObject("picturePause.Image")));
            this.picturePause.Location = new System.Drawing.Point(330, 208);
            this.picturePause.Name = "picturePause";
            this.picturePause.Size = new System.Drawing.Size(96, 96);
            this.picturePause.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.picturePause.TabIndex = 0;
            this.picturePause.TabStop = false;
            this.picturePause.Visible = false;
            // 
            // mainScreen
            // 
            this.mainScreen.Controls.Add(this.viewPort);
            this.mainScreen.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainScreen.Location = new System.Drawing.Point(0, 0);
            this.mainScreen.Name = "mainScreen";
            this.mainScreen.Size = new System.Drawing.Size(749, 536);
            this.mainScreen.TabIndex = 10;
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(749, 536);
            this.Controls.Add(this.panneauOperation_);
            this.Controls.Add(this.mainScreen);
            this.MinimumSize = new System.Drawing.Size(765, 575);
            this.Name = "Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.panneauOperation_.ResumeLayout(false);
            this.panneauOperation_.PerformLayout();
            this.viewPort.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).EndInit();
            this.mainScreen.ResumeLayout(false);
            this.mainScreen.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panneauOperation_;
        private System.Windows.Forms.Label panneauRotation_;
        private System.Windows.Forms.Label panneauPositionY_;
        private System.Windows.Forms.Label panneauPositionX_;
        private System.Windows.Forms.Label panneauDimension_;
        private System.Windows.Forms.TextBox textBoxPositionY_;
        private System.Windows.Forms.TextBox textBoxPositionX_;
        private System.Windows.Forms.TextBox textBoxRotation_;
        private System.Windows.Forms.TextBox textboxDimension_;
        public System.Windows.Forms.Panel viewPort;
        public System.Windows.Forms.PictureBox picturePause;
        public System.Windows.Forms.Panel mainScreen;
    }
}

