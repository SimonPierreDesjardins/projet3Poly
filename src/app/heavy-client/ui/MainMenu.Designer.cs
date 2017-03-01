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
            this.mainMenu_QuitButton = new ui.PanelButton();
            this.customLabel5 = new ui.CustomLabel();
            this.mainMenu_ConfigurationButton = new ui.PanelButton();
            this.customLabel4 = new ui.CustomLabel();
            this.mainMenu_PersoButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.mainMenu_cardsOnlineButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.mainMenu_EditionButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.mainMenu_SimulationButton = new ui.PanelButton();
            this.label1 = new ui.CustomLabel();
            this.mainMenu_ConnexionButton = new ui.PanelButton();
            this.customLabel6 = new ui.CustomLabel();
            this.connexionPictureBox = new System.Windows.Forms.PictureBox();
            this.panel1.SuspendLayout();
            this.mainMenu_QuitButton.SuspendLayout();
            this.mainMenu_ConfigurationButton.SuspendLayout();
            this.mainMenu_PersoButton.SuspendLayout();
            this.mainMenu_cardsOnlineButton.SuspendLayout();
            this.mainMenu_EditionButton.SuspendLayout();
            this.mainMenu_SimulationButton.SuspendLayout();
            this.mainMenu_ConnexionButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.connexionPictureBox)).BeginInit();
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
            this.panel1.Controls.Add(this.mainMenu_ConnexionButton);
            this.panel1.Controls.Add(this.mainMenu_QuitButton);
            this.panel1.Controls.Add(this.mainMenu_ConfigurationButton);
            this.panel1.Controls.Add(this.mainMenu_PersoButton);
            this.panel1.Controls.Add(this.mainMenu_cardsOnlineButton);
            this.panel1.Controls.Add(this.mainMenu_EditionButton);
            this.panel1.Controls.Add(this.mainMenu_SimulationButton);
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 471);
            this.panel1.TabIndex = 0;
            // 
            // mainMenu_QuitButton
            // 
            this.mainMenu_QuitButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
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
            this.mainMenu_ConfigurationButton.Location = new System.Drawing.Point(0, 294);
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
            this.mainMenu_PersoButton.Location = new System.Drawing.Point(0, 238);
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
            // mainMenu_cardsOnlineButton
            // 
            this.mainMenu_cardsOnlineButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_cardsOnlineButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_cardsOnlineButton.Controls.Add(this.customLabel2);
            this.mainMenu_cardsOnlineButton.Location = new System.Drawing.Point(0, 182);
            this.mainMenu_cardsOnlineButton.Name = "mainMenu_cardsOnlineButton";
            this.mainMenu_cardsOnlineButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_cardsOnlineButton.TabIndex = 6;
            this.mainMenu_cardsOnlineButton.Click += new System.EventHandler(this.mainMenu_cardsOnlineButton_Click);
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(55, 15);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(121, 21);
            this.customLabel2.TabIndex = 0;
            this.customLabel2.Text = "Carte en ligne";
            // 
            // mainMenu_EditionButton
            // 
            this.mainMenu_EditionButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_EditionButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_EditionButton.Controls.Add(this.customLabel1);
            this.mainMenu_EditionButton.Location = new System.Drawing.Point(0, 126);
            this.mainMenu_EditionButton.Name = "mainMenu_EditionButton";
            this.mainMenu_EditionButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_EditionButton.TabIndex = 7;
            this.mainMenu_EditionButton.Click += new System.EventHandler(this.mainMenu_EditionButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(55, 15);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(63, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Edition";
            // 
            // mainMenu_SimulationButton
            // 
            this.mainMenu_SimulationButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_SimulationButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_SimulationButton.Controls.Add(this.label1);
            this.mainMenu_SimulationButton.Location = new System.Drawing.Point(0, 70);
            this.mainMenu_SimulationButton.Name = "mainMenu_SimulationButton";
            this.mainMenu_SimulationButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_SimulationButton.TabIndex = 2;
            this.mainMenu_SimulationButton.Click += new System.EventHandler(this.mainMenu_SimulationButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(55, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "Simulation";
            // 
            // mainMenu_ConnexionButton
            // 
            this.mainMenu_ConnexionButton.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.mainMenu_ConnexionButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mainMenu_ConnexionButton.Controls.Add(this.connexionPictureBox);
            this.mainMenu_ConnexionButton.Controls.Add(this.customLabel6);
            this.mainMenu_ConnexionButton.Location = new System.Drawing.Point(0, 350);
            this.mainMenu_ConnexionButton.Name = "mainMenu_ConnexionButton";
            this.mainMenu_ConnexionButton.Size = new System.Drawing.Size(200, 50);
            this.mainMenu_ConnexionButton.TabIndex = 5;
            this.mainMenu_ConnexionButton.Click += new System.EventHandler(this.mainMenu_ConnexionButton_Click);
            // 
            // customLabel6
            // 
            this.customLabel6.AutoSize = true;
            this.customLabel6.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel6.ForeColor = System.Drawing.Color.Silver;
            this.customLabel6.Location = new System.Drawing.Point(55, 15);
            this.customLabel6.Name = "customLabel6";
            this.customLabel6.Size = new System.Drawing.Size(103, 21);
            this.customLabel6.TabIndex = 0;
            this.customLabel6.Text = "Connection";
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
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel1);
            this.Name = "MainMenu";
            this.Size = new System.Drawing.Size(200, 471);
            this.panel1.ResumeLayout(false);
            this.mainMenu_QuitButton.ResumeLayout(false);
            this.mainMenu_QuitButton.PerformLayout();
            this.mainMenu_ConfigurationButton.ResumeLayout(false);
            this.mainMenu_ConfigurationButton.PerformLayout();
            this.mainMenu_PersoButton.ResumeLayout(false);
            this.mainMenu_PersoButton.PerformLayout();
            this.mainMenu_cardsOnlineButton.ResumeLayout(false);
            this.mainMenu_cardsOnlineButton.PerformLayout();
            this.mainMenu_EditionButton.ResumeLayout(false);
            this.mainMenu_EditionButton.PerformLayout();
            this.mainMenu_SimulationButton.ResumeLayout(false);
            this.mainMenu_SimulationButton.PerformLayout();
            this.mainMenu_ConnexionButton.ResumeLayout(false);
            this.mainMenu_ConnexionButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.connexionPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer HideMenuTimer;
        private System.Windows.Forms.Timer ShowMenuTimer;
        private PanelButton mainMenu_SimulationButton;
        private CustomLabel label1;
        private PanelButton mainMenu_EditionButton;
        private CustomLabel customLabel1;
        private PanelButton mainMenu_cardsOnlineButton;
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
        public System.Windows.Forms.PictureBox connexionPictureBox;
    }
}
