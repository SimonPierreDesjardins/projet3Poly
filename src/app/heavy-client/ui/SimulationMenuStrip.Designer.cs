namespace ui
{
    partial class SimulationMenuStrip
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.premierePersonneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.profilsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.vuesToolStripMenuItem,
            this.profilsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(793, 29);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "simulationMenuStrip";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPrincipalToolStripMenuItem});
            this.fichierToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fichierToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(71, 25);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // menuPrincipalToolStripMenuItem
            // 
            this.menuPrincipalToolStripMenuItem.Name = "menuPrincipalToolStripMenuItem";
            this.menuPrincipalToolStripMenuItem.Size = new System.Drawing.Size(194, 26);
            this.menuPrincipalToolStripMenuItem.Text = "Menu Principal";
            this.menuPrincipalToolStripMenuItem.Click += new System.EventHandler(this.menuPrincipalToolStripMenuItem_Click);
            // 
            // vuesToolStripMenuItem
            // 
            this.vuesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthoToolStripMenuItem,
            this.orbiteToolStripMenuItem,
            this.premierePersonneToolStripMenuItem});
            this.vuesToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.vuesToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.vuesToolStripMenuItem.Name = "vuesToolStripMenuItem";
            this.vuesToolStripMenuItem.Size = new System.Drawing.Size(59, 25);
            this.vuesToolStripMenuItem.Text = "Vues";
            // 
            // orthoToolStripMenuItem
            // 
            this.orthoToolStripMenuItem.Name = "orthoToolStripMenuItem";
            this.orthoToolStripMenuItem.Size = new System.Drawing.Size(221, 26);
            this.orthoToolStripMenuItem.Text = "Orthographique";
            this.orthoToolStripMenuItem.Click += new System.EventHandler(this.orthoToolStripMenuItem_Click);
            // 
            // orbiteToolStripMenuItem
            // 
            this.orbiteToolStripMenuItem.Name = "orbiteToolStripMenuItem";
            this.orbiteToolStripMenuItem.Size = new System.Drawing.Size(221, 26);
            this.orbiteToolStripMenuItem.Text = "Orbite";
            this.orbiteToolStripMenuItem.Click += new System.EventHandler(this.orbiteToolStripMenuItem_Click);
            // 
            // premierePersonneToolStripMenuItem
            // 
            this.premierePersonneToolStripMenuItem.Name = "premierePersonneToolStripMenuItem";
            this.premierePersonneToolStripMenuItem.Size = new System.Drawing.Size(221, 26);
            this.premierePersonneToolStripMenuItem.Text = "Premiere Personne";
            this.premierePersonneToolStripMenuItem.Click += new System.EventHandler(this.premierePersonneToolStripMenuItem_Click);
            // 
            // profilsToolStripMenuItem
            // 
            this.profilsToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.profilsToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.profilsToolStripMenuItem.Name = "profilsToolStripMenuItem";
            this.profilsToolStripMenuItem.Size = new System.Drawing.Size(63, 25);
            this.profilsToolStripMenuItem.Text = "Profils";
            // 
            // SimulationMenuStrip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.menuStrip1);
            this.Name = "SimulationMenuStrip";
            this.Size = new System.Drawing.Size(793, 29);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vuesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orthoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem premierePersonneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem profilsToolStripMenuItem;
    }
}
