namespace ui
{
    partial class MapMenu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapMenu));
            this.mapPanel = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.addPanel = new System.Windows.Forms.Panel();
            this.onlineCheckBox = new System.Windows.Forms.CheckBox();
            this.modeComboBox = new System.Windows.Forms.ComboBox();
            this.offlineCheckBox = new System.Windows.Forms.CheckBox();
            this.privateCheckBox = new System.Windows.Forms.CheckBox();
            this.publicCheckBox = new System.Windows.Forms.CheckBox();
            this.warningLabel = new System.Windows.Forms.Label();
            this.textBox = new System.Windows.Forms.TextBox();
            this.offlineModePanel = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.passwordLabel = new System.Windows.Forms.Label();
            this.passwordBox = new System.Windows.Forms.TextBox();
            this.passwordWarningLabel = new System.Windows.Forms.Label();
            this.createButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.returnButton = new ui.PanelButton();
            this.returnPictureBox = new System.Windows.Forms.PictureBox();
            this.modeSelectionLabel = new ui.CustomLabel();
            this.customLabel6 = new ui.CustomLabel();
            this.confirmeButton = new ui.PanelButton();
            this.customLabel5 = new ui.CustomLabel();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.rightsModificationLabel = new ui.CustomLabel();
            this.nameLabel = new ui.CustomLabel();
            this.fileDirLabel = new ui.CustomLabel();
            this.importButton = new ui.PanelButton();
            this.customLabel3 = new ui.CustomLabel();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.cancelButton = new ui.PanelButton();
            this.customLabel2 = new ui.CustomLabel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.cancelJoiningButton = new ui.PanelButton();
            this.customLabel8 = new ui.CustomLabel();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.offlineEditionModeButton = new ui.PanelButton();
            this.customLabel4 = new ui.CustomLabel();
            this.offlineSimulationModeButton = new ui.PanelButton();
            this.customLabel7 = new ui.CustomLabel();
            this.panel1.SuspendLayout();
            this.addPanel.SuspendLayout();
            this.offlineModePanel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel5.SuspendLayout();
            this.createButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.returnButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.returnPictureBox)).BeginInit();
            this.confirmeButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.importButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.cancelButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.cancelJoiningButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.offlineEditionModeButton.SuspendLayout();
            this.offlineSimulationModeButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // mapPanel
            // 
            this.mapPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mapPanel.AutoScroll = true;
            this.mapPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.mapPanel.Location = new System.Drawing.Point(5, 5);
            this.mapPanel.Margin = new System.Windows.Forms.Padding(5);
            this.mapPanel.Name = "mapPanel";
            this.mapPanel.Size = new System.Drawing.Size(600, 394);
            this.mapPanel.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(296, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 21);
            this.label1.TabIndex = 3;
            this.label1.Text = "Cartes";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel1.Controls.Add(this.addPanel);
            this.panel1.Controls.Add(this.mapPanel);
            this.panel1.Controls.Add(this.offlineModePanel);
            this.panel1.Location = new System.Drawing.Point(30, 41);
            this.panel1.Margin = new System.Windows.Forms.Padding(30);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(610, 404);
            this.panel1.TabIndex = 4;
            // 
            // addPanel
            // 
            this.addPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.addPanel.Controls.Add(this.passwordWarningLabel);
            this.addPanel.Controls.Add(this.passwordLabel);
            this.addPanel.Controls.Add(this.passwordBox);
            this.addPanel.Controls.Add(this.onlineCheckBox);
            this.addPanel.Controls.Add(this.modeSelectionLabel);
            this.addPanel.Controls.Add(this.modeComboBox);
            this.addPanel.Controls.Add(this.offlineCheckBox);
            this.addPanel.Controls.Add(this.customLabel6);
            this.addPanel.Controls.Add(this.confirmeButton);
            this.addPanel.Controls.Add(this.privateCheckBox);
            this.addPanel.Controls.Add(this.publicCheckBox);
            this.addPanel.Controls.Add(this.rightsModificationLabel);
            this.addPanel.Controls.Add(this.warningLabel);
            this.addPanel.Controls.Add(this.textBox);
            this.addPanel.Controls.Add(this.nameLabel);
            this.addPanel.Controls.Add(this.fileDirLabel);
            this.addPanel.Controls.Add(this.importButton);
            this.addPanel.Controls.Add(this.cancelButton);
            this.addPanel.Location = new System.Drawing.Point(3, 4);
            this.addPanel.Margin = new System.Windows.Forms.Padding(5);
            this.addPanel.Name = "addPanel";
            this.addPanel.Size = new System.Drawing.Size(600, 394);
            this.addPanel.TabIndex = 0;
            this.addPanel.Visible = false;
            this.addPanel.VisibleChanged += new System.EventHandler(this.addPanel_VisibleChanged);
            // 
            // onlineCheckBox
            // 
            this.onlineCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.onlineCheckBox.AutoSize = true;
            this.onlineCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.onlineCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.onlineCheckBox.Location = new System.Drawing.Point(91, 226);
            this.onlineCheckBox.Name = "onlineCheckBox";
            this.onlineCheckBox.Size = new System.Drawing.Size(85, 25);
            this.onlineCheckBox.TabIndex = 18;
            this.onlineCheckBox.Text = "Enligne";
            this.onlineCheckBox.UseVisualStyleBackColor = true;
            this.onlineCheckBox.Click += new System.EventHandler(this.onlineCheckBox_Click);
            // 
            // modeComboBox
            // 
            this.modeComboBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.modeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.modeComboBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.modeComboBox.FormattingEnabled = true;
            this.modeComboBox.Items.AddRange(new object[] {
            "Édition",
            "Simulation",
            "Pièce",
            "Course"});
            this.modeComboBox.Location = new System.Drawing.Point(329, 102);
            this.modeComboBox.Name = "modeComboBox";
            this.modeComboBox.Size = new System.Drawing.Size(189, 29);
            this.modeComboBox.TabIndex = 19;
            // 
            // offlineCheckBox
            // 
            this.offlineCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.offlineCheckBox.AutoSize = true;
            this.offlineCheckBox.Checked = true;
            this.offlineCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.offlineCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.offlineCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.offlineCheckBox.Location = new System.Drawing.Point(91, 195);
            this.offlineCheckBox.Name = "offlineCheckBox";
            this.offlineCheckBox.Size = new System.Drawing.Size(106, 25);
            this.offlineCheckBox.TabIndex = 17;
            this.offlineCheckBox.Text = "Hors Ligne";
            this.offlineCheckBox.UseVisualStyleBackColor = true;
            this.offlineCheckBox.Click += new System.EventHandler(this.offlineCheckBox_Click);
            // 
            // privateCheckBox
            // 
            this.privateCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.privateCheckBox.AutoSize = true;
            this.privateCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.privateCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.privateCheckBox.Location = new System.Drawing.Point(329, 226);
            this.privateCheckBox.Name = "privateCheckBox";
            this.privateCheckBox.Size = new System.Drawing.Size(76, 25);
            this.privateCheckBox.TabIndex = 15;
            this.privateCheckBox.Text = "Privée";
            this.privateCheckBox.UseVisualStyleBackColor = true;
            this.privateCheckBox.Click += new System.EventHandler(this.privateCheckBox_Click);
            // 
            // publicCheckBox
            // 
            this.publicCheckBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.publicCheckBox.AutoSize = true;
            this.publicCheckBox.Checked = true;
            this.publicCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.publicCheckBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.publicCheckBox.ForeColor = System.Drawing.Color.Silver;
            this.publicCheckBox.Location = new System.Drawing.Point(329, 195);
            this.publicCheckBox.Name = "publicCheckBox";
            this.publicCheckBox.Size = new System.Drawing.Size(96, 25);
            this.publicCheckBox.TabIndex = 14;
            this.publicCheckBox.Text = "Publique";
            this.publicCheckBox.UseVisualStyleBackColor = true;
            this.publicCheckBox.Click += new System.EventHandler(this.publicCheckBox_Click);
            // 
            // warningLabel
            // 
            this.warningLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.warningLabel.AutoSize = true;
            this.warningLabel.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.warningLabel.ForeColor = System.Drawing.Color.Brown;
            this.warningLabel.Location = new System.Drawing.Point(87, 132);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(91, 17);
            this.warningLabel.TabIndex = 12;
            this.warningLabel.Text = "Warning label";
            this.warningLabel.Visible = false;
            // 
            // textBox
            // 
            this.textBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.textBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox.Location = new System.Drawing.Point(87, 102);
            this.textBox.MaxLength = 10;
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(189, 27);
            this.textBox.TabIndex = 11;
            this.textBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // offlineModePanel
            // 
            this.offlineModePanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.offlineModePanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.offlineModePanel.Controls.Add(this.cancelJoiningButton);
            this.offlineModePanel.Controls.Add(this.panel2);
            this.offlineModePanel.Controls.Add(this.panel3);
            this.offlineModePanel.Location = new System.Drawing.Point(5, 3);
            this.offlineModePanel.Name = "offlineModePanel";
            this.offlineModePanel.Size = new System.Drawing.Size(600, 394);
            this.offlineModePanel.TabIndex = 19;
            this.offlineModePanel.Visible = false;
            // 
            // panel2
            // 
            this.panel2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel2.Controls.Add(this.panel4);
            this.panel2.Location = new System.Drawing.Point(123, 103);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(338, 53);
            this.panel2.TabIndex = 4;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel4.Controls.Add(this.offlineEditionModeButton);
            this.panel4.Location = new System.Drawing.Point(3, 3);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(332, 47);
            this.panel4.TabIndex = 9;
            // 
            // panel3
            // 
            this.panel3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.panel3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel3.Controls.Add(this.panel5);
            this.panel3.Location = new System.Drawing.Point(126, 242);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(338, 53);
            this.panel3.TabIndex = 3;
            // 
            // panel5
            // 
            this.panel5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel5.Controls.Add(this.offlineSimulationModeButton);
            this.panel5.Location = new System.Drawing.Point(3, 3);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(332, 47);
            this.panel5.TabIndex = 9;
            // 
            // passwordLabel
            // 
            this.passwordLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.passwordLabel.AutoSize = true;
            this.passwordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.passwordLabel.ForeColor = System.Drawing.Color.Silver;
            this.passwordLabel.Location = new System.Drawing.Point(325, 288);
            this.passwordLabel.Name = "passwordLabel";
            this.passwordLabel.Size = new System.Drawing.Size(115, 21);
            this.passwordLabel.TabIndex = 22;
            this.passwordLabel.Text = "Mot de passe";
            // 
            // passwordBox
            // 
            this.passwordBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.passwordBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.passwordBox.Location = new System.Drawing.Point(329, 315);
            this.passwordBox.Name = "passwordBox";
            this.passwordBox.PasswordChar = '*';
            this.passwordBox.Size = new System.Drawing.Size(188, 27);
            this.passwordBox.TabIndex = 21;
            // 
            // passwordWarningLabel
            // 
            this.passwordWarningLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.passwordWarningLabel.AutoSize = true;
            this.passwordWarningLabel.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.passwordWarningLabel.ForeColor = System.Drawing.Color.Brown;
            this.passwordWarningLabel.Location = new System.Drawing.Point(326, 345);
            this.passwordWarningLabel.Name = "passwordWarningLabel";
            this.passwordWarningLabel.Size = new System.Drawing.Size(91, 17);
            this.passwordWarningLabel.TabIndex = 23;
            this.passwordWarningLabel.Text = "Warning label";
            this.passwordWarningLabel.Visible = false;
            // 
            // createButton
            // 
            this.createButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.createButton.Controls.Add(this.customLabel1);
            this.createButton.Controls.Add(this.pictureBox1);
            this.createButton.Location = new System.Drawing.Point(483, 1);
            this.createButton.Name = "createButton";
            this.createButton.Size = new System.Drawing.Size(147, 36);
            this.createButton.TabIndex = 6;
            this.createButton.Click += new System.EventHandler(this.createButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(10, 7);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(100, 21);
            this.customLabel1.TabIndex = 3;
            this.customLabel1.Text = "Créer carte";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(116, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // returnButton
            // 
            this.returnButton.Controls.Add(this.returnPictureBox);
            this.returnButton.Location = new System.Drawing.Point(38, 2);
            this.returnButton.Name = "returnButton";
            this.returnButton.Size = new System.Drawing.Size(36, 36);
            this.returnButton.TabIndex = 5;
            this.returnButton.Click += new System.EventHandler(this.returnButton_Click);
            // 
            // returnPictureBox
            // 
            this.returnPictureBox.Enabled = false;
            this.returnPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("returnPictureBox.Image")));
            this.returnPictureBox.Location = new System.Drawing.Point(6, 6);
            this.returnPictureBox.Name = "returnPictureBox";
            this.returnPictureBox.Size = new System.Drawing.Size(24, 24);
            this.returnPictureBox.TabIndex = 2;
            this.returnPictureBox.TabStop = false;
            // 
            // modeSelectionLabel
            // 
            this.modeSelectionLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.modeSelectionLabel.AutoSize = true;
            this.modeSelectionLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.modeSelectionLabel.ForeColor = System.Drawing.Color.Silver;
            this.modeSelectionLabel.Location = new System.Drawing.Point(325, 78);
            this.modeSelectionLabel.Name = "modeSelectionLabel";
            this.modeSelectionLabel.Size = new System.Drawing.Size(150, 21);
            this.modeSelectionLabel.TabIndex = 20;
            this.modeSelectionLabel.Text = "Mode de la carte:";
            // 
            // customLabel6
            // 
            this.customLabel6.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.customLabel6.AutoSize = true;
            this.customLabel6.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel6.ForeColor = System.Drawing.Color.Silver;
            this.customLabel6.Location = new System.Drawing.Point(87, 171);
            this.customLabel6.Name = "customLabel6";
            this.customLabel6.Size = new System.Drawing.Size(157, 21);
            this.customLabel6.TabIndex = 16;
            this.customLabel6.Text = "Paramètre réseau :";
            // 
            // confirmeButton
            // 
            this.confirmeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.confirmeButton.Controls.Add(this.customLabel5);
            this.confirmeButton.Controls.Add(this.pictureBox4);
            this.confirmeButton.Location = new System.Drawing.Point(369, 4);
            this.confirmeButton.Name = "confirmeButton";
            this.confirmeButton.Size = new System.Drawing.Size(228, 36);
            this.confirmeButton.TabIndex = 8;
            this.confirmeButton.Click += new System.EventHandler(this.confirmeButton_Click);
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(10, 7);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(174, 21);
            this.customLabel5.TabIndex = 3;
            this.customLabel5.Text = "Confirmer la création";
            // 
            // pictureBox4
            // 
            this.pictureBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(197, 6);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(24, 24);
            this.pictureBox4.TabIndex = 2;
            this.pictureBox4.TabStop = false;
            // 
            // rightsModificationLabel
            // 
            this.rightsModificationLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.rightsModificationLabel.AutoSize = true;
            this.rightsModificationLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rightsModificationLabel.ForeColor = System.Drawing.Color.Silver;
            this.rightsModificationLabel.Location = new System.Drawing.Point(325, 171);
            this.rightsModificationLabel.Name = "rightsModificationLabel";
            this.rightsModificationLabel.Size = new System.Drawing.Size(182, 21);
            this.rightsModificationLabel.TabIndex = 13;
            this.rightsModificationLabel.Text = "Droit de modification :";
            // 
            // nameLabel
            // 
            this.nameLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nameLabel.AutoSize = true;
            this.nameLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nameLabel.ForeColor = System.Drawing.Color.Silver;
            this.nameLabel.Location = new System.Drawing.Point(87, 78);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(145, 21);
            this.nameLabel.TabIndex = 10;
            this.nameLabel.Text = "Nom de la carte :";
            // 
            // fileDirLabel
            // 
            this.fileDirLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.fileDirLabel.AutoSize = true;
            this.fileDirLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileDirLabel.ForeColor = System.Drawing.Color.Silver;
            this.fileDirLabel.Location = new System.Drawing.Point(101, 320);
            this.fileDirLabel.Name = "fileDirLabel";
            this.fileDirLabel.Size = new System.Drawing.Size(99, 21);
            this.fileDirLabel.TabIndex = 9;
            this.fileDirLabel.Text = "fileNameDir";
            this.fileDirLabel.Click += new System.EventHandler(this.importButton_Click);
            // 
            // importButton
            // 
            this.importButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.importButton.Controls.Add(this.customLabel3);
            this.importButton.Controls.Add(this.pictureBox3);
            this.importButton.Location = new System.Drawing.Point(91, 281);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(210, 36);
            this.importButton.TabIndex = 8;
            this.importButton.Click += new System.EventHandler(this.importButton_Click);
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(10, 7);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(159, 21);
            this.customLabel3.TabIndex = 3;
            this.customLabel3.Text = "Importer une carte";
            // 
            // pictureBox3
            // 
            this.pictureBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Location = new System.Drawing.Point(179, 6);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // cancelButton
            // 
            this.cancelButton.Controls.Add(this.customLabel2);
            this.cancelButton.Controls.Add(this.pictureBox2);
            this.cancelButton.Location = new System.Drawing.Point(5, 4);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(210, 36);
            this.cancelButton.TabIndex = 7;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(10, 7);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(159, 21);
            this.customLabel2.TabIndex = 3;
            this.customLabel2.Text = "Annuler la création";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(179, 6);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.TabIndex = 2;
            this.pictureBox2.TabStop = false;
            // 
            // cancelJoiningButton
            // 
            this.cancelJoiningButton.Controls.Add(this.customLabel8);
            this.cancelJoiningButton.Controls.Add(this.pictureBox5);
            this.cancelJoiningButton.Location = new System.Drawing.Point(20, 12);
            this.cancelJoiningButton.Name = "cancelJoiningButton";
            this.cancelJoiningButton.Size = new System.Drawing.Size(164, 36);
            this.cancelJoiningButton.TabIndex = 8;
            this.cancelJoiningButton.Click += new System.EventHandler(this.cancelJoiningButton_Click);
            // 
            // customLabel8
            // 
            this.customLabel8.AutoSize = true;
            this.customLabel8.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel8.ForeColor = System.Drawing.Color.Silver;
            this.customLabel8.Location = new System.Drawing.Point(10, 7);
            this.customLabel8.Name = "customLabel8";
            this.customLabel8.Size = new System.Drawing.Size(120, 21);
            this.customLabel8.TabIndex = 3;
            this.customLabel8.Text = "Ne pas joindre";
            // 
            // pictureBox5
            // 
            this.pictureBox5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox5.Enabled = false;
            this.pictureBox5.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox5.Image")));
            this.pictureBox5.Location = new System.Drawing.Point(133, 6);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(24, 24);
            this.pictureBox5.TabIndex = 2;
            this.pictureBox5.TabStop = false;
            // 
            // offlineEditionModeButton
            // 
            this.offlineEditionModeButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.offlineEditionModeButton.Controls.Add(this.customLabel4);
            this.offlineEditionModeButton.Location = new System.Drawing.Point(0, 0);
            this.offlineEditionModeButton.Name = "offlineEditionModeButton";
            this.offlineEditionModeButton.Size = new System.Drawing.Size(332, 47);
            this.offlineEditionModeButton.TabIndex = 0;
            this.offlineEditionModeButton.Click += new System.EventHandler(this.offlineEditionModeButton_Click);
            // 
            // customLabel4
            // 
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(40, 10);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(250, 24);
            this.customLabel4.TabIndex = 0;
            this.customLabel4.Text = "Mode Édition Hors Ligne";
            // 
            // offlineSimulationModeButton
            // 
            this.offlineSimulationModeButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.offlineSimulationModeButton.Controls.Add(this.customLabel7);
            this.offlineSimulationModeButton.Location = new System.Drawing.Point(0, 0);
            this.offlineSimulationModeButton.Name = "offlineSimulationModeButton";
            this.offlineSimulationModeButton.Size = new System.Drawing.Size(332, 47);
            this.offlineSimulationModeButton.TabIndex = 0;
            this.offlineSimulationModeButton.Click += new System.EventHandler(this.offlineSimulationModeButton_Click);
            // 
            // customLabel7
            // 
            this.customLabel7.AutoSize = true;
            this.customLabel7.Font = new System.Drawing.Font("Century Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel7.ForeColor = System.Drawing.Color.Silver;
            this.customLabel7.Location = new System.Drawing.Point(25, 10);
            this.customLabel7.Name = "customLabel7";
            this.customLabel7.Size = new System.Drawing.Size(288, 24);
            this.customLabel7.TabIndex = 0;
            this.customLabel7.Text = "Mode Simulation Hors Ligne";
            // 
            // MapMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.createButton);
            this.Controls.Add(this.returnButton);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label1);
            this.Name = "MapMenu";
            this.Size = new System.Drawing.Size(670, 475);
            this.panel1.ResumeLayout(false);
            this.addPanel.ResumeLayout(false);
            this.addPanel.PerformLayout();
            this.offlineModePanel.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.createButton.ResumeLayout(false);
            this.createButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.returnButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.returnPictureBox)).EndInit();
            this.confirmeButton.ResumeLayout(false);
            this.confirmeButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.importButton.ResumeLayout(false);
            this.importButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.cancelButton.ResumeLayout(false);
            this.cancelButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.cancelJoiningButton.ResumeLayout(false);
            this.cancelJoiningButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.offlineEditionModeButton.ResumeLayout(false);
            this.offlineEditionModeButton.PerformLayout();
            this.offlineSimulationModeButton.ResumeLayout(false);
            this.offlineSimulationModeButton.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel mapPanel;
        private System.Windows.Forms.PictureBox returnPictureBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel addPanel;
        private PanelButton returnButton;
        private PanelButton createButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private CustomLabel customLabel1;
        private PanelButton importButton;
        private CustomLabel customLabel3;
        private System.Windows.Forms.PictureBox pictureBox3;
        private PanelButton cancelButton;
        private CustomLabel customLabel2;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.CheckBox privateCheckBox;
        private System.Windows.Forms.CheckBox publicCheckBox;
        private CustomLabel rightsModificationLabel;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.TextBox textBox;
        private CustomLabel nameLabel;
        private CustomLabel fileDirLabel;
        private PanelButton confirmeButton;
        private CustomLabel customLabel5;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.CheckBox onlineCheckBox;
        private System.Windows.Forms.CheckBox offlineCheckBox;
        private CustomLabel customLabel6;
        private System.Windows.Forms.Panel offlineModePanel;
        private System.Windows.Forms.Panel panel2;
        private PanelButton offlineEditionModeButton;
        private CustomLabel customLabel4;
        private System.Windows.Forms.Panel panel3;
        private PanelButton offlineSimulationModeButton;
        private CustomLabel customLabel7;
        private CustomLabel modeSelectionLabel;
        private System.Windows.Forms.ComboBox modeComboBox;
        private PanelButton cancelJoiningButton;
        private CustomLabel customLabel8;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Label passwordWarningLabel;
        private System.Windows.Forms.Label passwordLabel;
        private System.Windows.Forms.TextBox passwordBox;
    }
}
