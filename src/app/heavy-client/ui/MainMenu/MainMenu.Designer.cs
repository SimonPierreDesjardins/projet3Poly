namespace ui
{
    partial class MainMenu
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainMenu));
            this.HideMenuTimer = new System.Windows.Forms.Timer(this.components);
            this.ShowMenuTimer = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.achievementButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.mainMenu_ConnexionButton = new ui.PanelButton();
            this.connexionPictureBox = new System.Windows.Forms.PictureBox();
            this.customLabel6 = new ui.CustomLabel();
            this.mainMenu_QuitButton = new ui.PanelButton();
            this.customLabel5 = new ui.CustomLabel();
            this.mainMenu_ConfigurationButton = new ui.PanelButton();
            this.customLabel4 = new ui.CustomLabel();
            this.mainMenu_PersoButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.mainMenu_mapsButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.panel1.SuspendLayout();
            this.achievementButton.SuspendLayout();
            this.mainMenu_ConnexionButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.connexionPictureBox)).BeginInit();
            this.mainMenu_QuitButton.SuspendLayout();
            this.mainMenu_ConfigurationButton.SuspendLayout();
            this.mainMenu_PersoButton.SuspendLayout();
            this.mainMenu_mapsButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // HideMenuTimer
            // 
            this.HideMenuTimer.Interval = 1;
            this.HideMenuTimer.Tick += new System.EventHandler(this.HideMenuTimer_Tick);
            // 
            // ShowMenuTimer
            // 
            this.ShowMenuTimer.Interval = 1;
            this.ShowMenuTimer.Tick += new System.EventHandler(this.ShowMenuTimer_Tick);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel1.Controls.Add(this.achievementButton);
            this.panel1.Controls.Add(this.mainMenu_ConnexionButton);
            this.panel1.Controls.Add(this.mainMenu_QuitButton);
            this.panel1.Controls.Add(this.mainMenu_ConfigurationButton);
            this.panel1.Controls.Add(this.mainMenu_PersoButton);
            this.panel1.Controls.Add(this.mainMenu_mapsButton);
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 471);
            this.panel1.TabIndex = 0;
            // 
            // achievementButton
            // 
            this.achievementButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.achievementButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.achievementButton.Controls.Add(this.customLabel1);
            this.achievementButton.Location = new System.Drawing.Point(0, 275);
            this.achievementButton.Name = "achievementButton";
            this.achievementButton.Size = new System.Drawing.Size(200, 50);
            this.achievementButton.TabIndex = 6;
            this.achievementButton.Click += new System.EventHandler(this.achievementButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(55, 15);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(72, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Réussite";
            // 
            // mainMenu_ConnexionButton
            // 
            this.mainMenu_ConnexionButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_ConnexionButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_ConnexionButton.Controls.Add(this.connexionPictureBox);
            this.mainMenu_ConnexionButton.Controls.Add(this.customLabel6);
            this.mainMenu_ConnexionButton.Location = new System.Drawing.Point(0, 331);
            this.mainMenu_ConnexionButton.Name = "mainMenu_ConnexionButton";
            this.mainMenu_ConnexionButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_ConnexionButton.TabIndex = 5;
            this.mainMenu_ConnexionButton.Click += new System.EventHandler(this.mainMenu_ConnexionButton_Click);
            // 
            // connexionPictureBox
            // 
            this.connexionPictureBox.Enabled = false;
            this.connexionPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("connexionPictureBox.Image")));
            this.connexionPictureBox.Location = new System.Drawing.Point(18, 15);
            this.connexionPictureBox.Name = "connexionPictureBox";
            this.connexionPictureBox.Size = new System.Drawing.Size(24, 24);
            this.connexionPictureBox.TabIndex = 1;
            this.connexionPictureBox.TabStop = false;
            // 
            // customLabel6
            // 
            this.customLabel6.AutoSize = true;
            this.customLabel6.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel6.ForeColor = System.Drawing.Color.Silver;
            this.customLabel6.Location = new System.Drawing.Point(55, 15);
            this.customLabel6.Name = "customLabel6";
            this.customLabel6.Size = new System.Drawing.Size(94, 21);
            this.customLabel6.TabIndex = 0;
            this.customLabel6.Text = "Connexion";
            // 
            // mainMenu_QuitButton
            // 
            this.mainMenu_QuitButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.mainMenu_QuitButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_QuitButton.Controls.Add(this.customLabel5);
            this.mainMenu_QuitButton.Location = new System.Drawing.Point(0, 408);
            this.mainMenu_QuitButton.Name = "mainMenu_QuitButton";
            this.mainMenu_QuitButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_QuitButton.TabIndex = 3;
            this.mainMenu_QuitButton.Click += new System.EventHandler(this.mainMenu_QuitButton_Click);
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(55, 15);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(66, 21);
            this.customLabel5.TabIndex = 0;
            this.customLabel5.Text = "Quitter";
            // 
            // mainMenu_ConfigurationButton
            // 
            this.mainMenu_ConfigurationButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_ConfigurationButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_ConfigurationButton.Controls.Add(this.customLabel4);
            this.mainMenu_ConfigurationButton.Location = new System.Drawing.Point(0, 194);
            this.mainMenu_ConfigurationButton.Name = "mainMenu_ConfigurationButton";
            this.mainMenu_ConfigurationButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_ConfigurationButton.TabIndex = 4;
            this.mainMenu_ConfigurationButton.Click += new System.EventHandler(this.mainMenu_ConfigurationButton_Click);
            // 
            // customLabel4
            // 
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(55, 15);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(118, 21);
            this.customLabel4.TabIndex = 0;
            this.customLabel4.Text = "Configuration";
            // 
            // mainMenu_PersoButton
            // 
            this.mainMenu_PersoButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_PersoButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_PersoButton.Controls.Add(this.customLabel3);
            this.mainMenu_PersoButton.Location = new System.Drawing.Point(0, 138);
            this.mainMenu_PersoButton.Name = "mainMenu_PersoButton";
            this.mainMenu_PersoButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_PersoButton.TabIndex = 5;
            this.mainMenu_PersoButton.Click += new System.EventHandler(this.mainMenu_PersoButton_Click);
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(55, 15);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(134, 21);
            this.customLabel3.TabIndex = 0;
            this.customLabel3.Text = "Personnalisation";
            // 
            // mainMenu_mapsButton
            // 
            this.mainMenu_mapsButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_mapsButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_mapsButton.Controls.Add(this.customLabel2);
            this.mainMenu_mapsButton.Location = new System.Drawing.Point(0, 82);
            this.mainMenu_mapsButton.Name = "mainMenu_mapsButton";
            this.mainMenu_mapsButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_mapsButton.TabIndex = 6;
            this.mainMenu_mapsButton.Click += new System.EventHandler(this.mainMenu_mapsButton_Click);
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(55, 15);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(62, 21);
            this.customLabel2.TabIndex = 0;
            this.customLabel2.Text = "Cartes";
            // 
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel1);
            this.Name = "MainMenu";
            this.Size = new System.Drawing.Size(200, 471);
            this.panel1.ResumeLayout(false);
            this.achievementButton.ResumeLayout(false);
            this.achievementButton.PerformLayout();
            this.mainMenu_ConnexionButton.ResumeLayout(false);
            this.mainMenu_ConnexionButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.connexionPictureBox)).EndInit();
            this.mainMenu_QuitButton.ResumeLayout(false);
            this.mainMenu_QuitButton.PerformLayout();
            this.mainMenu_ConfigurationButton.ResumeLayout(false);
            this.mainMenu_ConfigurationButton.PerformLayout();
            this.mainMenu_PersoButton.ResumeLayout(false);
            this.mainMenu_PersoButton.PerformLayout();
            this.mainMenu_mapsButton.ResumeLayout(false);
            this.mainMenu_mapsButton.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer HideMenuTimer;
        private System.Windows.Forms.Timer ShowMenuTimer;
        private PanelButton mainMenu_mapsButton;
        private CustomLabel customLabel2;
        private PanelButton mainMenu_PersoButton;
        private CustomLabel customLabel3;
        private PanelButton mainMenu_ConfigurationButton;
        private CustomLabel customLabel4;
        private PanelButton mainMenu_QuitButton;
        private CustomLabel customLabel5;
        private System.Windows.Forms.Panel panel1;
        private PanelButton mainMenu_ConnexionButton;
        private CustomLabel customLabel6;
        private CustomLabel customLabel1;
        public System.Windows.Forms.PictureBox connexionPictureBox;
        public PanelButton achievementButton;
    }
}
