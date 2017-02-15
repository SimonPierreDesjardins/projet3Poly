namespace ui
{
    partial class PersonnalisationSideMenu
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PersonnalisationSideMenu));
            this.ShowMenuTimer = new System.Windows.Forms.Timer(this.components);
            this.returnMainMenu_Button = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.customLabel6 = new ui.CustomLabel();
            this.musicChange_Button = new ui.PanelButton();
            this.pictureBox6 = new System.Windows.Forms.PictureBox();
            this.customLabel5 = new ui.CustomLabel();
            this.tableChange_Button = new ui.PanelButton();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.customLabel4 = new ui.CustomLabel();
            this.carChange_Button = new ui.PanelButton();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.customLabel3 = new ui.CustomLabel();
            this.carColor_Button = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.customLabel2 = new ui.CustomLabel();
            this.wheelColor_Button = new ui.PanelButton();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.customLabel1 = new ui.CustomLabel();
            this.returnMainMenu_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.musicChange_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).BeginInit();
            this.tableChange_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.carChange_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.carColor_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.wheelColor_Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // ShowMenuTimer
            // 
            this.ShowMenuTimer.Interval = 1;
            this.ShowMenuTimer.Tick += new System.EventHandler(this.ShowMenuTimer_Tick);
            // 
            // returnMainMenu_Button
            // 
            this.returnMainMenu_Button.Controls.Add(this.pictureBox1);
            this.returnMainMenu_Button.Controls.Add(this.customLabel6);
            this.returnMainMenu_Button.Location = new System.Drawing.Point(0, 12);
            this.returnMainMenu_Button.Name = "returnMainMenu_Button";
            this.returnMainMenu_Button.Size = new System.Drawing.Size(200, 50);
            this.returnMainMenu_Button.TabIndex = 1;
            this.returnMainMenu_Button.Click += new System.EventHandler(this.returnMainMenu_Button_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(10, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(25, 25);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // customLabel6
            // 
            this.customLabel6.AutoSize = true;
            this.customLabel6.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel6.ForeColor = System.Drawing.Color.Silver;
            this.customLabel6.Location = new System.Drawing.Point(45, 15);
            this.customLabel6.Name = "customLabel6";
            this.customLabel6.Size = new System.Drawing.Size(136, 21);
            this.customLabel6.TabIndex = 0;
            this.customLabel6.Text = "Retour au menu";
            // 
            // musicChange_Button
            // 
            this.musicChange_Button.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.musicChange_Button.Controls.Add(this.pictureBox6);
            this.musicChange_Button.Controls.Add(this.customLabel5);
            this.musicChange_Button.Location = new System.Drawing.Point(0, 350);
            this.musicChange_Button.Name = "musicChange_Button";
            this.musicChange_Button.Size = new System.Drawing.Size(200, 50);
            this.musicChange_Button.TabIndex = 1;
            this.musicChange_Button.Click += new System.EventHandler(this.musicChange_Button_Click);
            // 
            // pictureBox6
            // 
            this.pictureBox6.Enabled = false;
            this.pictureBox6.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox6.Image")));
            this.pictureBox6.Location = new System.Drawing.Point(10, 12);
            this.pictureBox6.Name = "pictureBox6";
            this.pictureBox6.Size = new System.Drawing.Size(25, 25);
            this.pictureBox6.TabIndex = 6;
            this.pictureBox6.TabStop = false;
            // 
            // customLabel5
            // 
            this.customLabel5.AutoSize = true;
            this.customLabel5.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel5.ForeColor = System.Drawing.Color.Silver;
            this.customLabel5.Location = new System.Drawing.Point(45, 15);
            this.customLabel5.Name = "customLabel5";
            this.customLabel5.Size = new System.Drawing.Size(148, 21);
            this.customLabel5.TabIndex = 0;
            this.customLabel5.Text = "Choix de musique";
            // 
            // tableChange_Button
            // 
            this.tableChange_Button.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.tableChange_Button.Controls.Add(this.pictureBox5);
            this.tableChange_Button.Controls.Add(this.customLabel4);
            this.tableChange_Button.Location = new System.Drawing.Point(0, 290);
            this.tableChange_Button.Name = "tableChange_Button";
            this.tableChange_Button.Size = new System.Drawing.Size(200, 50);
            this.tableChange_Button.TabIndex = 1;
            this.tableChange_Button.Click += new System.EventHandler(this.tableChange_Button_Click);
            // 
            // pictureBox5
            // 
            this.pictureBox5.Enabled = false;
            this.pictureBox5.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox5.Image")));
            this.pictureBox5.Location = new System.Drawing.Point(10, 12);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(25, 25);
            this.pictureBox5.TabIndex = 5;
            this.pictureBox5.TabStop = false;
            // 
            // customLabel4
            // 
            this.customLabel4.AutoSize = true;
            this.customLabel4.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel4.ForeColor = System.Drawing.Color.Silver;
            this.customLabel4.Location = new System.Drawing.Point(45, 15);
            this.customLabel4.Name = "customLabel4";
            this.customLabel4.Size = new System.Drawing.Size(125, 21);
            this.customLabel4.TabIndex = 0;
            this.customLabel4.Text = "Choix de table";
            // 
            // carChange_Button
            // 
            this.carChange_Button.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.carChange_Button.Controls.Add(this.pictureBox4);
            this.carChange_Button.Controls.Add(this.customLabel3);
            this.carChange_Button.Location = new System.Drawing.Point(0, 230);
            this.carChange_Button.Name = "carChange_Button";
            this.carChange_Button.Size = new System.Drawing.Size(200, 50);
            this.carChange_Button.TabIndex = 1;
            this.carChange_Button.Click += new System.EventHandler(this.carChange_Button_Click);
            // 
            // pictureBox4
            // 
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(10, 12);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(25, 25);
            this.pictureBox4.TabIndex = 4;
            this.pictureBox4.TabStop = false;
            // 
            // customLabel3
            // 
            this.customLabel3.AutoSize = true;
            this.customLabel3.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel3.ForeColor = System.Drawing.Color.Silver;
            this.customLabel3.Location = new System.Drawing.Point(45, 15);
            this.customLabel3.Name = "customLabel3";
            this.customLabel3.Size = new System.Drawing.Size(142, 21);
            this.customLabel3.TabIndex = 0;
            this.customLabel3.Text = "Choix du modèle";
            // 
            // carColor_Button
            // 
            this.carColor_Button.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.carColor_Button.Controls.Add(this.pictureBox3);
            this.carColor_Button.Controls.Add(this.customLabel2);
            this.carColor_Button.Location = new System.Drawing.Point(0, 170);
            this.carColor_Button.Name = "carColor_Button";
            this.carColor_Button.Size = new System.Drawing.Size(200, 50);
            this.carColor_Button.TabIndex = 1;
            this.carColor_Button.Click += new System.EventHandler(this.carColor_Button_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(10, 12);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(25, 25);
            this.pictureBox3.TabIndex = 3;
            this.pictureBox3.TabStop = false;
            // 
            // customLabel2
            // 
            this.customLabel2.AutoSize = true;
            this.customLabel2.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel2.ForeColor = System.Drawing.Color.Silver;
            this.customLabel2.Location = new System.Drawing.Point(45, 15);
            this.customLabel2.Name = "customLabel2";
            this.customLabel2.Size = new System.Drawing.Size(152, 21);
            this.customLabel2.TabIndex = 0;
            this.customLabel2.Text = "Couleur du châssis";
            // 
            // wheelColor_Button
            // 
            this.wheelColor_Button.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.wheelColor_Button.Controls.Add(this.pictureBox2);
            this.wheelColor_Button.Controls.Add(this.customLabel1);
            this.wheelColor_Button.Location = new System.Drawing.Point(0, 110);
            this.wheelColor_Button.Name = "wheelColor_Button";
            this.wheelColor_Button.Size = new System.Drawing.Size(200, 50);
            this.wheelColor_Button.TabIndex = 0;
            this.wheelColor_Button.Click += new System.EventHandler(this.wheelColor_Button_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(10, 12);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(25, 25);
            this.pictureBox2.TabIndex = 2;
            this.pictureBox2.TabStop = false;
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(45, 15);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(147, 21);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Couleur des roues";
            // 
            // PersonnalisationSideMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.returnMainMenu_Button);
            this.Controls.Add(this.musicChange_Button);
            this.Controls.Add(this.tableChange_Button);
            this.Controls.Add(this.carChange_Button);
            this.Controls.Add(this.carColor_Button);
            this.Controls.Add(this.wheelColor_Button);
            this.Name = "PersonnalisationSideMenu";
            this.Size = new System.Drawing.Size(200, 471);
            this.returnMainMenu_Button.ResumeLayout(false);
            this.returnMainMenu_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.musicChange_Button.ResumeLayout(false);
            this.musicChange_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).EndInit();
            this.tableChange_Button.ResumeLayout(false);
            this.tableChange_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.carChange_Button.ResumeLayout(false);
            this.carChange_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.carColor_Button.ResumeLayout(false);
            this.carColor_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.wheelColor_Button.ResumeLayout(false);
            this.wheelColor_Button.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private PanelButton wheelColor_Button;
        private CustomLabel customLabel1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private PanelButton carColor_Button;
        private CustomLabel customLabel2;
        private PanelButton carChange_Button;
        private CustomLabel customLabel3;
        private PanelButton tableChange_Button;
        private CustomLabel customLabel4;
        private PanelButton musicChange_Button;
        private CustomLabel customLabel5;
        private PanelButton returnMainMenu_Button;
        private System.Windows.Forms.PictureBox pictureBox1;
        private CustomLabel customLabel6;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.PictureBox pictureBox6;
        private System.Windows.Forms.Timer ShowMenuTimer;
    }
}
