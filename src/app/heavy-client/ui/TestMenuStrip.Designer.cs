namespace ui
{
    partial class TestMenuStrip
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.profilsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEditionToolStripMenuItem,
            this.menuPrincipalToolStripMenuItem});
            this.fichierToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fichierToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(71, 25);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // vuesToolStripMenuItem
            // 
            this.vuesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem});
            this.vuesToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.vuesToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.vuesToolStripMenuItem.Name = "vuesToolStripMenuItem";
            this.vuesToolStripMenuItem.Size = new System.Drawing.Size(59, 25);
            this.vuesToolStripMenuItem.Text = "Vues";
            // 
            // profilsToolStripMenuItem
            // 
            this.profilsToolStripMenuItem.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.profilsToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(178)))), ((int)(((byte)(216)))), ((int)(((byte)(255)))));
            this.profilsToolStripMenuItem.Name = "profilsToolStripMenuItem";
            this.profilsToolStripMenuItem.Size = new System.Drawing.Size(63, 25);
            this.profilsToolStripMenuItem.Text = "Profils";
            // 
            // menuEditionToolStripMenuItem
            // 
            this.menuEditionToolStripMenuItem.Name = "menuEditionToolStripMenuItem";
            this.menuEditionToolStripMenuItem.Size = new System.Drawing.Size(196, 26);
            this.menuEditionToolStripMenuItem.Text = "Mode edition";
            this.menuEditionToolStripMenuItem.Click += new System.EventHandler(this.menuEditionToolStripMenuItem_Click);
            // 
            // menuPrincipalToolStripMenuItem
            // 
            this.menuPrincipalToolStripMenuItem.Name = "menuPrincipalToolStripMenuItem";
            this.menuPrincipalToolStripMenuItem.Size = new System.Drawing.Size(196, 26);
            this.menuPrincipalToolStripMenuItem.Text = "Menu principal";
            this.menuPrincipalToolStripMenuItem.Click += new System.EventHandler(this.menuPrincipalToolStripMenuItem_Click);
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            this.orthographiqueToolStripMenuItem.Size = new System.Drawing.Size(208, 26);
            this.orthographiqueToolStripMenuItem.Text = "Orthographique";
            this.orthographiqueToolStripMenuItem.Click += new System.EventHandler(this.orthographiqueToolStripMenuItem_Click);
            // 
            // orbiteToolStripMenuItem
            // 
            this.orbiteToolStripMenuItem.Name = "orbiteToolStripMenuItem";
            this.orbiteToolStripMenuItem.Size = new System.Drawing.Size(208, 26);
            this.orbiteToolStripMenuItem.Text = "Orbite";
            this.orbiteToolStripMenuItem.Click += new System.EventHandler(this.orbiteToolStripMenuItem_Click);
            // 
            // TestMenuStrip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.menuStrip1);
            this.Name = "TestMenuStrip";
            this.Size = new System.Drawing.Size(793, 29);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vuesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem profilsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuEditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem;
    }
}
