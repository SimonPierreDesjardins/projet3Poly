namespace ui
{
    partial class ConnectToServer
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConnectToServer));
            this.connectPanel = new System.Windows.Forms.Panel();
            this.label4 = new System.Windows.Forms.Label();
            this.connectionButton = new ui.PanelButton();
            this.pictureBox8 = new System.Windows.Forms.PictureBox();
            this.customLabel2 = new ui.CustomLabel();
            this.IPWarningLabel = new System.Windows.Forms.Label();
            this.IPTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cancelButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.customLabel1 = new ui.CustomLabel();
            this.authenticatePanel = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.cancelExistingUserButton = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.customLabel8 = new ui.CustomLabel();
            this.cancelNewUserButton = new ui.PanelButton();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.customLabel7 = new ui.CustomLabel();
            this.crateAndAuthenticateButton = new ui.PanelButton();
            this.pictureBox6 = new System.Windows.Forms.PictureBox();
            this.customLabel4 = new ui.CustomLabel();
            this.newAccountWarningLabel = new System.Windows.Forms.Label();
            this.existingAccountWarningLabel = new System.Windows.Forms.Label();
            this.newAccountTextBox = new System.Windows.Forms.TextBox();
            this.ExistingAccountTextBox = new System.Windows.Forms.TextBox();
            this.authenticateButton = new ui.PanelButton();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.customLabel3 = new ui.CustomLabel();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.DeconnectPanel = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.DeconnectButton = new ui.PanelButton();
            this.pictureBox7 = new System.Windows.Forms.PictureBox();
            this.customLabel6 = new ui.CustomLabel();
            this.CancelDeconnectButton = new ui.PanelButton();
            this.customLabel5 = new ui.CustomLabel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.connectPanel.SuspendLayout();
            this.connectionButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox8)).BeginInit();
            this.cancelButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.authenticatePanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.cancelExistingUserButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.cancelNewUserButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.crateAndAuthenticateButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).BeginInit();
            this.authenticateButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.DeconnectPanel.SuspendLayout();
            this.DeconnectButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox7)).BeginInit();
            this.CancelDeconnectButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // connectPanel
            // 
            this.connectPanel.Controls.Add(this.label4);
            this.connectPanel.Controls.Add(this.connectionButton);
            this.connectPanel.Controls.Add(this.IPWarningLabel);
            this.connectPanel.Controls.Add(this.IPTextBox);
            this.connectPanel.Controls.Add(this.label2);
            this.connectPanel.Controls.Add(this.cancelButton);
            this.connectPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.connectPanel.Location = new System.Drawing.Point(0, 0);
            this.connectPanel.Name = "connectPanel";
            this.connectPanel.Size = new System.Drawing.Size(512, 285);
            this.connectPanel.TabIndex = 0;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.Silver;
            this.label4.Location = new System.Drawing.Point(17, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(183, 21);
            this.label4.TabIndex = 9;
            this.label4.Text = "Connexion à un server";
            // 
            // connectionButton
            // 
            this.connectionButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.connectionButton.Controls.Add(this.pictureBox8);
            this.connectionButton.Controls.Add(this.customLabel2);
            this.connectionButton.Location = new System.Drawing.Point(153, 228);
            this.connectionButton.Name = "connectionButton";
            this.connectionButton.Size = new System.Drawing.Size(146, 44);
            this.connectionButton.TabIndex = 7;
            this.connectionButton.Click += new System.EventHandler(this.connectionButton_Click);
            // 
            // pictureBox8
            // 
            this.pictureBox8.Enabled = false;
            this.pictureBox8.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox8.Image")));
            this.pictureBox8.Location = new System.Drawing.Point(10, 10);
            this.pictureBox8.Name = "pictureBox8";
            this.pictureBox8.Size = new System.Drawing.Size(24, 24);
            this.pictureBox8.TabIndex = 2;
            this.pictureBox8.TabStop = false;
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(50, 10);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(94, 21);
            this.customLabel2.TabIndex = 0;
            this.customLabel2.Text = "Connexion";
            // 
            // IPWarningLabel
            // 
            this.IPWarningLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.IPWarningLabel.AutoSize = true;
            this.IPWarningLabel.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.IPWarningLabel.ForeColor = System.Drawing.Color.Red;
            this.IPWarningLabel.Location = new System.Drawing.Point(18, 131);
            this.IPWarningLabel.Name = "IPWarningLabel";
            this.IPWarningLabel.Size = new System.Drawing.Size(96, 17);
            this.IPWarningLabel.TabIndex = 5;
            this.IPWarningLabel.Text = "warningLabel";
            this.IPWarningLabel.Visible = false;
            // 
            // IPTextBox
            // 
            this.IPTextBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.IPTextBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.IPTextBox.Location = new System.Drawing.Point(21, 101);
            this.IPTextBox.Name = "IPTextBox";
            this.IPTextBox.Size = new System.Drawing.Size(223, 27);
            this.IPTextBox.TabIndex = 4;
            this.IPTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IPTextBox_KeyPress);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Silver;
            this.label2.Location = new System.Drawing.Point(17, 77);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(172, 21);
            this.label2.TabIndex = 1;
            this.label2.Text = "Adresse IP du server :";
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cancelButton.Controls.Add(this.pictureBox1);
            this.cancelButton.Controls.Add(this.customLabel1);
            this.cancelButton.Location = new System.Drawing.Point(15, 228);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(124, 44);
            this.cancelButton.TabIndex = 8;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(13, 10);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(50, 10);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(71, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Annuler";
            // 
            // authenticatePanel
            // 
            this.authenticatePanel.Controls.Add(this.panel3);
            this.authenticatePanel.Controls.Add(this.panel1);
            this.authenticatePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.authenticatePanel.Location = new System.Drawing.Point(0, 0);
            this.authenticatePanel.Name = "authenticatePanel";
            this.authenticatePanel.Size = new System.Drawing.Size(512, 285);
            this.authenticatePanel.TabIndex = 1;
            this.authenticatePanel.Visible = false;
            // 
            // panel3
            // 
            this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.panel3.BackColor = System.Drawing.Color.Silver;
            this.panel3.Location = new System.Drawing.Point(250, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(10, 285);
            this.panel3.TabIndex = 9;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.cancelExistingUserButton);
            this.panel1.Controls.Add(this.cancelNewUserButton);
            this.panel1.Controls.Add(this.crateAndAuthenticateButton);
            this.panel1.Controls.Add(this.newAccountWarningLabel);
            this.panel1.Controls.Add(this.existingAccountWarningLabel);
            this.panel1.Controls.Add(this.newAccountTextBox);
            this.panel1.Controls.Add(this.ExistingAccountTextBox);
            this.panel1.Controls.Add(this.authenticateButton);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(15, 16);
            this.panel1.Margin = new System.Windows.Forms.Padding(5);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(480, 256);
            this.panel1.TabIndex = 8;
            // 
            // cancelExistingUserButton
            // 
            this.cancelExistingUserButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.cancelExistingUserButton.Controls.Add(this.pictureBox3);
            this.cancelExistingUserButton.Controls.Add(this.customLabel8);
            this.cancelExistingUserButton.Location = new System.Drawing.Point(282, 209);
            this.cancelExistingUserButton.Name = "cancelExistingUserButton";
            this.cancelExistingUserButton.Size = new System.Drawing.Size(164, 44);
            this.cancelExistingUserButton.TabIndex = 13;
            this.cancelExistingUserButton.Click += new System.EventHandler(this.cancelExistingUserButton_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(10, 10);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // customLabel8
            // 
            this.customLabel8.AutoSize = true;
            this.customLabel8.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel8.ForeColor = System.Drawing.Color.Silver;
            this.customLabel8.Location = new System.Drawing.Point(50, 10);
            this.customLabel8.Name = "customLabel8";
            this.customLabel8.Size = new System.Drawing.Size(71, 21);
            this.customLabel8.TabIndex = 0;
            this.customLabel8.Text = "Annuler";
            // 
            // cancelNewUserButton
            // 
            this.cancelNewUserButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cancelNewUserButton.Controls.Add(this.pictureBox4);
            this.cancelNewUserButton.Controls.Add(this.customLabel7);
            this.cancelNewUserButton.Location = new System.Drawing.Point(21, 206);
            this.cancelNewUserButton.Name = "cancelNewUserButton";
            this.cancelNewUserButton.Size = new System.Drawing.Size(164, 44);
            this.cancelNewUserButton.TabIndex = 12;
            this.cancelNewUserButton.Click += new System.EventHandler(this.cancelNewUserButton_Click);
            // 
            // pictureBox4
            // 
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(10, 10);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(24, 24);
            this.pictureBox4.TabIndex = 3;
            this.pictureBox4.TabStop = false;
            // 
            // customLabel7
            // 
            this.customLabel7.AutoSize = true;
            this.customLabel7.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel7.ForeColor = System.Drawing.Color.Silver;
            this.customLabel7.Location = new System.Drawing.Point(50, 10);
            this.customLabel7.Name = "customLabel7";
            this.customLabel7.Size = new System.Drawing.Size(71, 21);
            this.customLabel7.TabIndex = 0;
            this.customLabel7.Text = "Annuler";
            // 
            // crateAndAuthenticateButton
            // 
            this.crateAndAuthenticateButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.crateAndAuthenticateButton.Controls.Add(this.pictureBox6);
            this.crateAndAuthenticateButton.Controls.Add(this.customLabel4);
            this.crateAndAuthenticateButton.Location = new System.Drawing.Point(21, 159);
            this.crateAndAuthenticateButton.Name = "crateAndAuthenticateButton";
            this.crateAndAuthenticateButton.Size = new System.Drawing.Size(164, 44);
            this.crateAndAuthenticateButton.TabIndex = 12;
            this.crateAndAuthenticateButton.Click += new System.EventHandler(this.crateAndAuthenticateButton_Click);
            // 
            // pictureBox6
            // 
            this.pictureBox6.Enabled = false;
            this.pictureBox6.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox6.Image")));
            this.pictureBox6.Location = new System.Drawing.Point(10, 10);
            this.pictureBox6.Name = "pictureBox6";
            this.pictureBox6.Size = new System.Drawing.Size(24, 24);
            this.pictureBox6.TabIndex = 3;
            this.pictureBox6.TabStop = false;
            // 
            // customLabel4
            // 
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(50, 10);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(53, 21);
            this.customLabel4.TabIndex = 0;
            this.customLabel4.Text = "Créer";
            // 
            // newAccountWarningLabel
            // 
            this.newAccountWarningLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.newAccountWarningLabel.AutoSize = true;
            this.newAccountWarningLabel.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.newAccountWarningLabel.ForeColor = System.Drawing.Color.Red;
            this.newAccountWarningLabel.Location = new System.Drawing.Point(25, 121);
            this.newAccountWarningLabel.Name = "newAccountWarningLabel";
            this.newAccountWarningLabel.Size = new System.Drawing.Size(96, 17);
            this.newAccountWarningLabel.TabIndex = 16;
            this.newAccountWarningLabel.Text = "warningLabel";
            this.newAccountWarningLabel.Visible = false;
            // 
            // existingAccountWarningLabel
            // 
            this.existingAccountWarningLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.existingAccountWarningLabel.AutoSize = true;
            this.existingAccountWarningLabel.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.existingAccountWarningLabel.ForeColor = System.Drawing.Color.Red;
            this.existingAccountWarningLabel.Location = new System.Drawing.Point(288, 124);
            this.existingAccountWarningLabel.Name = "existingAccountWarningLabel";
            this.existingAccountWarningLabel.Size = new System.Drawing.Size(96, 17);
            this.existingAccountWarningLabel.TabIndex = 15;
            this.existingAccountWarningLabel.Text = "warningLabel";
            this.existingAccountWarningLabel.Visible = false;
            // 
            // newAccountTextBox
            // 
            this.newAccountTextBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.newAccountTextBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.newAccountTextBox.Location = new System.Drawing.Point(28, 87);
            this.newAccountTextBox.MaxLength = 10;
            this.newAccountTextBox.Name = "newAccountTextBox";
            this.newAccountTextBox.Size = new System.Drawing.Size(146, 27);
            this.newAccountTextBox.TabIndex = 14;
            this.newAccountTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.newAccountTextBox_KeyPress);
            // 
            // ExistingAccountTextBox
            // 
            this.ExistingAccountTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ExistingAccountTextBox.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ExistingAccountTextBox.Location = new System.Drawing.Point(291, 90);
            this.ExistingAccountTextBox.MaxLength = 10;
            this.ExistingAccountTextBox.Name = "ExistingAccountTextBox";
            this.ExistingAccountTextBox.Size = new System.Drawing.Size(146, 27);
            this.ExistingAccountTextBox.TabIndex = 13;
            this.ExistingAccountTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ExistingAccountTextBox_KeyPress);
            // 
            // authenticateButton
            // 
            this.authenticateButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.authenticateButton.Controls.Add(this.pictureBox5);
            this.authenticateButton.Controls.Add(this.customLabel3);
            this.authenticateButton.Location = new System.Drawing.Point(282, 159);
            this.authenticateButton.Name = "authenticateButton";
            this.authenticateButton.Size = new System.Drawing.Size(164, 44);
            this.authenticateButton.TabIndex = 11;
            this.authenticateButton.Click += new System.EventHandler(this.authenticateButton_Click);
            // 
            // pictureBox5
            // 
            this.pictureBox5.Enabled = false;
            this.pictureBox5.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox5.Image")));
            this.pictureBox5.Location = new System.Drawing.Point(10, 10);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(24, 24);
            this.pictureBox5.TabIndex = 3;
            this.pictureBox5.TabStop = false;
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(50, 10);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(103, 21);
            this.customLabel3.TabIndex = 0;
            this.customLabel3.Text = "Authentifier";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Silver;
            this.label3.Location = new System.Drawing.Point(287, 46);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(150, 21);
            this.label3.TabIndex = 10;
            this.label3.Text = "Compte existant :";
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(24, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(158, 21);
            this.label1.TabIndex = 9;
            this.label1.Text = "Nouveau compte :";
            // 
            // DeconnectPanel
            // 
            this.DeconnectPanel.Controls.Add(this.label5);
            this.DeconnectPanel.Controls.Add(this.DeconnectButton);
            this.DeconnectPanel.Controls.Add(this.CancelDeconnectButton);
            this.DeconnectPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DeconnectPanel.Location = new System.Drawing.Point(0, 0);
            this.DeconnectPanel.Name = "DeconnectPanel";
            this.DeconnectPanel.Size = new System.Drawing.Size(512, 285);
            this.DeconnectPanel.TabIndex = 2;
            this.DeconnectPanel.Visible = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.Silver;
            this.label5.Location = new System.Drawing.Point(11, 10);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(202, 21);
            this.label5.TabIndex = 15;
            this.label5.Text = "Déconnexion à un server";
            // 
            // DeconnectButton
            // 
            this.DeconnectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.DeconnectButton.Controls.Add(this.pictureBox7);
            this.DeconnectButton.Controls.Add(this.customLabel6);
            this.DeconnectButton.Location = new System.Drawing.Point(10, 172);
            this.DeconnectButton.Name = "DeconnectButton";
            this.DeconnectButton.Size = new System.Drawing.Size(203, 44);
            this.DeconnectButton.TabIndex = 13;
            this.DeconnectButton.Click += new System.EventHandler(this.DeconnectButton_Click);
            // 
            // pictureBox7
            // 
            this.pictureBox7.Enabled = false;
            this.pictureBox7.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox7.Image")));
            this.pictureBox7.Location = new System.Drawing.Point(12, 10);
            this.pictureBox7.Name = "pictureBox7";
            this.pictureBox7.Size = new System.Drawing.Size(24, 24);
            this.pictureBox7.TabIndex = 2;
            this.pictureBox7.TabStop = false;
            // 
            // customLabel6
            // 
            this.customLabel6.AutoSize = true;
            this.customLabel6.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel6.ForeColor = System.Drawing.Color.Silver;
            this.customLabel6.Location = new System.Drawing.Point(50, 12);
            this.customLabel6.Name = "customLabel6";
            this.customLabel6.Size = new System.Drawing.Size(113, 21);
            this.customLabel6.TabIndex = 0;
            this.customLabel6.Text = "Déconnexion";
            // 
            // CancelDeconnectButton
            // 
            this.CancelDeconnectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CancelDeconnectButton.Controls.Add(this.customLabel5);
            this.CancelDeconnectButton.Controls.Add(this.pictureBox2);
            this.CancelDeconnectButton.Location = new System.Drawing.Point(9, 222);
            this.CancelDeconnectButton.Name = "CancelDeconnectButton";
            this.CancelDeconnectButton.Size = new System.Drawing.Size(204, 44);
            this.CancelDeconnectButton.TabIndex = 14;
            this.CancelDeconnectButton.Click += new System.EventHandler(this.CancelDeconnectButton_Click);
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(50, 10);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(71, 21);
            this.customLabel5.TabIndex = 0;
            this.customLabel5.Text = "Annuler";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(13, 10);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.TabIndex = 1;
            this.pictureBox2.TabStop = false;
            // 
            // ConnectToServer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.authenticatePanel);
            this.Controls.Add(this.DeconnectPanel);
            this.Controls.Add(this.connectPanel);
            this.Name = "ConnectToServer";
            this.Size = new System.Drawing.Size(512, 285);
            this.connectPanel.ResumeLayout(false);
            this.connectPanel.PerformLayout();
            this.connectionButton.ResumeLayout(false);
            this.connectionButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox8)).EndInit();
            this.cancelButton.ResumeLayout(false);
            this.cancelButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.authenticatePanel.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.cancelExistingUserButton.ResumeLayout(false);
            this.cancelExistingUserButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.cancelNewUserButton.ResumeLayout(false);
            this.cancelNewUserButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.crateAndAuthenticateButton.ResumeLayout(false);
            this.crateAndAuthenticateButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).EndInit();
            this.authenticateButton.ResumeLayout(false);
            this.authenticateButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.DeconnectPanel.ResumeLayout(false);
            this.DeconnectPanel.PerformLayout();
            this.DeconnectButton.ResumeLayout(false);
            this.DeconnectButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox7)).EndInit();
            this.CancelDeconnectButton.ResumeLayout(false);
            this.CancelDeconnectButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel connectPanel;
        private System.Windows.Forms.Label IPWarningLabel;
        private System.Windows.Forms.TextBox IPTextBox;
        private System.Windows.Forms.Label label2;
        private PanelButton connectionButton;
        private CustomLabel customLabel2;
        private System.Windows.Forms.Panel authenticatePanel;
        private System.Windows.Forms.Label label4;
        private PanelButton cancelButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private CustomLabel customLabel1;
        private System.Windows.Forms.Panel DeconnectPanel;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel1;
        private PanelButton crateAndAuthenticateButton;
        private CustomLabel customLabel4;
        private System.Windows.Forms.Label newAccountWarningLabel;
        private System.Windows.Forms.TextBox newAccountTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private PanelButton DeconnectButton;
        private CustomLabel customLabel6;
        private PanelButton CancelDeconnectButton;
        private System.Windows.Forms.PictureBox pictureBox2;
        private CustomLabel customLabel5;
        private PanelButton cancelNewUserButton;
        private System.Windows.Forms.PictureBox pictureBox4;
        private CustomLabel customLabel7;
        private System.Windows.Forms.PictureBox pictureBox6;
        private System.Windows.Forms.PictureBox pictureBox8;
        private System.Windows.Forms.PictureBox pictureBox7;
        private PanelButton cancelExistingUserButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private CustomLabel customLabel8;
        private System.Windows.Forms.Label existingAccountWarningLabel;
        private System.Windows.Forms.TextBox ExistingAccountTextBox;
        private PanelButton authenticateButton;
        private System.Windows.Forms.PictureBox pictureBox5;
        private CustomLabel customLabel3;
        private System.Windows.Forms.Label label3;
    }
}
