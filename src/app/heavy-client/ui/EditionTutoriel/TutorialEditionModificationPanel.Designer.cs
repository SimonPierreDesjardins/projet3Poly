namespace ui
{
    partial class TutorialEditionModificationPanel
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
            this.EditionOperationPanel = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.textBoxPositionY_ = new System.Windows.Forms.TextBox();
            this.textBoxPositionX_ = new System.Windows.Forms.TextBox();
            this.textBoxRotation_ = new System.Windows.Forms.TextBox();
            this.textboxDimension_ = new System.Windows.Forms.TextBox();
            this.panneauPositionY_ = new System.Windows.Forms.Label();
            this.panneauPositionX_ = new System.Windows.Forms.Label();
            this.panneauDimension_ = new System.Windows.Forms.Label();
            this.panneauRotation_ = new System.Windows.Forms.Label();
            this.EditionOperationPanel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // EditionOperationPanel
            // 
            this.EditionOperationPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.EditionOperationPanel.Controls.Add(this.panel2);
            this.EditionOperationPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.EditionOperationPanel.Location = new System.Drawing.Point(0, 0);
            this.EditionOperationPanel.Name = "EditionOperationPanel";
            this.EditionOperationPanel.Size = new System.Drawing.Size(128, 223);
            this.EditionOperationPanel.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel2.Controls.Add(this.textBoxPositionY_);
            this.panel2.Controls.Add(this.textBoxPositionX_);
            this.panel2.Controls.Add(this.textBoxRotation_);
            this.panel2.Controls.Add(this.textboxDimension_);
            this.panel2.Controls.Add(this.panneauPositionY_);
            this.panel2.Controls.Add(this.panneauPositionX_);
            this.panel2.Controls.Add(this.panneauDimension_);
            this.panel2.Controls.Add(this.panneauRotation_);
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(122, 217);
            this.panel2.TabIndex = 0;
            // 
            // textBoxPositionY_
            // 
            this.textBoxPositionY_.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.textBoxPositionY_.ForeColor = System.Drawing.Color.Silver;
            this.textBoxPositionY_.Location = new System.Drawing.Point(10, 186);
            this.textBoxPositionY_.Name = "textBoxPositionY_";
            this.textBoxPositionY_.Size = new System.Drawing.Size(102, 20);
            this.textBoxPositionY_.TabIndex = 23;
            this.textBoxPositionY_.TabStop = false;
            this.textBoxPositionY_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionY__KeyDown);
            // 
            // textBoxPositionX_
            // 
            this.textBoxPositionX_.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.textBoxPositionX_.ForeColor = System.Drawing.Color.Silver;
            this.textBoxPositionX_.Location = new System.Drawing.Point(10, 128);
            this.textBoxPositionX_.Name = "textBoxPositionX_";
            this.textBoxPositionX_.Size = new System.Drawing.Size(102, 20);
            this.textBoxPositionX_.TabIndex = 22;
            this.textBoxPositionX_.TabStop = false;
            this.textBoxPositionX_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionX__KeyDown);
            // 
            // textBoxRotation_
            // 
            this.textBoxRotation_.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.textBoxRotation_.ForeColor = System.Drawing.Color.Silver;
            this.textBoxRotation_.Location = new System.Drawing.Point(10, 77);
            this.textBoxRotation_.Name = "textBoxRotation_";
            this.textBoxRotation_.Size = new System.Drawing.Size(102, 20);
            this.textBoxRotation_.TabIndex = 21;
            this.textBoxRotation_.TabStop = false;
            this.textBoxRotation_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxRotation__KeyDown);
            // 
            // textboxDimension_
            // 
            this.textboxDimension_.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.textboxDimension_.ForeColor = System.Drawing.Color.Silver;
            this.textboxDimension_.Location = new System.Drawing.Point(10, 26);
            this.textboxDimension_.Name = "textboxDimension_";
            this.textboxDimension_.Size = new System.Drawing.Size(102, 20);
            this.textboxDimension_.TabIndex = 20;
            this.textboxDimension_.TabStop = false;
            this.textboxDimension_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textboxDimension__KeyDown);
            // 
            // panneauPositionY_
            // 
            this.panneauPositionY_.AutoSize = true;
            this.panneauPositionY_.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panneauPositionY_.ForeColor = System.Drawing.Color.Silver;
            this.panneauPositionY_.Location = new System.Drawing.Point(0, 170);
            this.panneauPositionY_.Name = "panneauPositionY_";
            this.panneauPositionY_.Size = new System.Drawing.Size(75, 16);
            this.panneauPositionY_.TabIndex = 19;
            this.panneauPositionY_.Text = "Position en Y";
            // 
            // panneauPositionX_
            // 
            this.panneauPositionX_.AutoSize = true;
            this.panneauPositionX_.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panneauPositionX_.ForeColor = System.Drawing.Color.Silver;
            this.panneauPositionX_.Location = new System.Drawing.Point(0, 112);
            this.panneauPositionX_.Name = "panneauPositionX_";
            this.panneauPositionX_.Size = new System.Drawing.Size(75, 16);
            this.panneauPositionX_.TabIndex = 18;
            this.panneauPositionX_.Text = "Position en X";
            // 
            // panneauDimension_
            // 
            this.panneauDimension_.AutoSize = true;
            this.panneauDimension_.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panneauDimension_.ForeColor = System.Drawing.Color.Silver;
            this.panneauDimension_.Location = new System.Drawing.Point(0, 7);
            this.panneauDimension_.Name = "panneauDimension_";
            this.panneauDimension_.Size = new System.Drawing.Size(124, 16);
            this.panneauDimension_.TabIndex = 17;
            this.panneauDimension_.Text = "Facteur de dimension";
            // 
            // panneauRotation_
            // 
            this.panneauRotation_.AutoSize = true;
            this.panneauRotation_.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panneauRotation_.ForeColor = System.Drawing.Color.Silver;
            this.panneauRotation_.Location = new System.Drawing.Point(0, 61);
            this.panneauRotation_.Name = "panneauRotation_";
            this.panneauRotation_.Size = new System.Drawing.Size(101, 16);
            this.panneauRotation_.TabIndex = 16;
            this.panneauRotation_.Text = "Angle de rotation";
            // 
            // TutorialEditionModificationPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.EditionOperationPanel);
            this.Name = "TutorialEditionModificationPanel";
            this.Size = new System.Drawing.Size(128, 223);
            this.EditionOperationPanel.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel EditionOperationPanel;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox textBoxPositionY_;
        private System.Windows.Forms.TextBox textBoxPositionX_;
        private System.Windows.Forms.TextBox textBoxRotation_;
        private System.Windows.Forms.TextBox textboxDimension_;
        private System.Windows.Forms.Label panneauPositionY_;
        private System.Windows.Forms.Label panneauPositionX_;
        private System.Windows.Forms.Label panneauDimension_;
        private System.Windows.Forms.Label panneauRotation_;
    }
}
