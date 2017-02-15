namespace ui
{
    partial class ColorSelector
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ColorSelector));
            this.colorPicture = new System.Windows.Forms.PictureBox();
            this.panelButton1 = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.panelButton2 = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            ((System.ComponentModel.ISupportInitialize)(this.colorPicture)).BeginInit();
            this.panelButton1.SuspendLayout();
            this.panelButton2.SuspendLayout();
            this.SuspendLayout();
            // 
            // colorPicture
            // 
            this.colorPicture.Image = ((System.Drawing.Image)(resources.GetObject("colorPicture.Image")));
            this.colorPicture.Location = new System.Drawing.Point(0, 0);
            this.colorPicture.Name = "colorPicture";
            this.colorPicture.Size = new System.Drawing.Size(258, 156);
            this.colorPicture.TabIndex = 0;
            this.colorPicture.TabStop = false;
            this.colorPicture.MouseClick += new System.Windows.Forms.MouseEventHandler(this.colorPicture_MouseClick);
            // 
            // panelButton1
            // 
            this.panelButton1.BackColor = System.Drawing.Color.Transparent;
            this.panelButton1.Controls.Add(this.customLabel1);
            this.panelButton1.Location = new System.Drawing.Point(0, 156);
            this.panelButton1.Name = "panelButton1";
            this.panelButton1.Size = new System.Drawing.Size(129, 26);
            this.panelButton1.TabIndex = 1;
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(30, 3);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(71, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Annuler";
            // 
            // panelButton2
            // 
            this.panelButton2.BackColor = System.Drawing.Color.Transparent;
            this.panelButton2.Controls.Add(this.customLabel2);
            this.panelButton2.Location = new System.Drawing.Point(129, 156);
            this.panelButton2.Name = "panelButton2";
            this.panelButton2.Size = new System.Drawing.Size(129, 26);
            this.panelButton2.TabIndex = 2;
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(22, 3);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(87, 21);
            this.customLabel2.TabIndex = 1;
            this.customLabel2.Text = "Appliquer";
            // 
            // ColorSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.panelButton2);
            this.Controls.Add(this.panelButton1);
            this.Controls.Add(this.colorPicture);
            this.MinimumSize = new System.Drawing.Size(258, 100);
            this.Name = "ColorSelector";
            this.Size = new System.Drawing.Size(258, 182);
            ((System.ComponentModel.ISupportInitialize)(this.colorPicture)).EndInit();
            this.panelButton1.ResumeLayout(false);
            this.panelButton1.PerformLayout();
            this.panelButton2.ResumeLayout(false);
            this.panelButton2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox colorPicture;
        private PanelButton panelButton1;
        private CustomLabel customLabel1;
        private PanelButton panelButton2;
        private CustomLabel customLabel2;
    }
}
