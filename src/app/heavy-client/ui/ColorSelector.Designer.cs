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
            this.applyButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.cancelButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            ((System.ComponentModel.ISupportInitialize)(this.colorPicture)).BeginInit();
            this.applyButton.SuspendLayout();
            this.cancelButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // colorPicture
            // 
            this.colorPicture.Image = ((System.Drawing.Image)(resources.GetObject("colorPicture.Image")));
            this.colorPicture.Location = new System.Drawing.Point(0, 0);
            this.colorPicture.Name = "colorPicture";
            this.colorPicture.Size = new System.Drawing.Size(256, 156);
            this.colorPicture.TabIndex = 0;
            this.colorPicture.TabStop = false;
            this.colorPicture.Click += new System.EventHandler(this.colorPicture_Click);
            this.colorPicture.MouseMove += new System.Windows.Forms.MouseEventHandler(this.colorPicture_MouseMove);
            // 
            // applyButton
            // 
            this.applyButton.BackColor = System.Drawing.Color.Transparent;
            this.applyButton.Controls.Add(this.customLabel2);
            this.applyButton.Location = new System.Drawing.Point(129, 156);
            this.applyButton.Name = "applyButton";
            this.applyButton.Size = new System.Drawing.Size(129, 26);
            this.applyButton.TabIndex = 2;
            this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
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
            // cancelButton
            // 
            this.cancelButton.BackColor = System.Drawing.Color.Transparent;
            this.cancelButton.Controls.Add(this.customLabel1);
            this.cancelButton.Location = new System.Drawing.Point(0, 156);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(129, 26);
            this.cancelButton.TabIndex = 1;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
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
            // ColorSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.applyButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.colorPicture);
            this.MinimumSize = new System.Drawing.Size(258, 100);
            this.Name = "ColorSelector";
            this.Size = new System.Drawing.Size(258, 182);
            ((System.ComponentModel.ISupportInitialize)(this.colorPicture)).EndInit();
            this.applyButton.ResumeLayout(false);
            this.applyButton.PerformLayout();
            this.cancelButton.ResumeLayout(false);
            this.cancelButton.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox colorPicture;
        private PanelButton cancelButton;
        private CustomLabel customLabel1;
        private PanelButton applyButton;
        private CustomLabel customLabel2;
    }
}
