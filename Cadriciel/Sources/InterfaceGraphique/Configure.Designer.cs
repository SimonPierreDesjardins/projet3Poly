namespace InterfaceGraphique
{
    partial class Configure
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.buttonFinConfig = new System.Windows.Forms.Button();
            this.buttonDefConfig = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxAntiHoraire = new System.Windows.Forms.TextBox();
            this.textBoxModeManuel = new System.Windows.Forms.TextBox();
            this.textBoxAvancer = new System.Windows.Forms.TextBox();
            this.textBoxHoraire = new System.Windows.Forms.TextBox();
            this.textBoxReculer = new System.Windows.Forms.TextBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.buttonDeleteProfil = new System.Windows.Forms.Button();
            this.buttonFiniProfil = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.checkBox11 = new System.Windows.Forms.CheckBox();
            this.checkBox10 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.buttonLoadProfil = new System.Windows.Forms.Button();
            this.buttonSaveProfil = new System.Windows.Forms.Button();
            this.buttonDefProfil = new System.Windows.Forms.Button();
            this.comboBoxProfil = new System.Windows.Forms.ComboBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.label7 = new System.Windows.Forms.Label();
            this.buttonFiniDebug = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(-1, -2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(443, 322);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.buttonFinConfig);
            this.tabPage1.Controls.Add(this.buttonDefConfig);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.textBoxAntiHoraire);
            this.tabPage1.Controls.Add(this.textBoxModeManuel);
            this.tabPage1.Controls.Add(this.textBoxAvancer);
            this.tabPage1.Controls.Add(this.textBoxHoraire);
            this.tabPage1.Controls.Add(this.textBoxReculer);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(435, 296);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Configuration control";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // buttonFinConfig
            // 
            this.buttonFinConfig.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonFinConfig.Location = new System.Drawing.Point(344, 271);
            this.buttonFinConfig.Name = "buttonFinConfig";
            this.buttonFinConfig.Size = new System.Drawing.Size(84, 23);
            this.buttonFinConfig.TabIndex = 12;
            this.buttonFinConfig.Text = "Fini";
            this.buttonFinConfig.UseVisualStyleBackColor = true;
            // 
            // buttonDefConfig
            // 
            this.buttonDefConfig.Location = new System.Drawing.Point(344, 241);
            this.buttonDefConfig.Name = "buttonDefConfig";
            this.buttonDefConfig.Size = new System.Drawing.Size(84, 23);
            this.buttonDefConfig.TabIndex = 11;
            this.buttonDefConfig.Text = "Par défaut";
            this.buttonDefConfig.UseVisualStyleBackColor = true;
            this.buttonDefConfig.Click += new System.EventHandler(this.buttonDefConfig_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(120, 203);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(179, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Activer / Désactiver le mode manuel";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(183, 14);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Avancer";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Rotation en sens horaire";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(186, 103);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Reculer";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(272, 103);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(139, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Rotation en sens antihoraire";
            // 
            // textBoxAntiHoraire
            // 
            this.textBoxAntiHoraire.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxAntiHoraire.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.textBoxAntiHoraire.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxAntiHoraire.HideSelection = false;
            this.textBoxAntiHoraire.Location = new System.Drawing.Point(286, 122);
            this.textBoxAntiHoraire.MaxLength = 10;
            this.textBoxAntiHoraire.Name = "textBoxAntiHoraire";
            this.textBoxAntiHoraire.ReadOnly = true;
            this.textBoxAntiHoraire.Size = new System.Drawing.Size(100, 49);
            this.textBoxAntiHoraire.TabIndex = 5;
            this.textBoxAntiHoraire.Text = "D";
            this.textBoxAntiHoraire.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxAntiHoraire.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxAntiHoraire_KeyPress);
            // 
            // textBoxModeManuel
            // 
            this.textBoxModeManuel.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxModeManuel.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.textBoxModeManuel.Cursor = System.Windows.Forms.Cursors.Hand;
            this.textBoxModeManuel.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxModeManuel.HideSelection = false;
            this.textBoxModeManuel.Location = new System.Drawing.Point(123, 219);
            this.textBoxModeManuel.MaxLength = 10;
            this.textBoxModeManuel.Name = "textBoxModeManuel";
            this.textBoxModeManuel.ReadOnly = true;
            this.textBoxModeManuel.Size = new System.Drawing.Size(167, 49);
            this.textBoxModeManuel.TabIndex = 4;
            this.textBoxModeManuel.Text = "ESPACE";
            this.textBoxModeManuel.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxModeManuel.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxModeManuel_KeyPress);
            // 
            // textBoxAvancer
            // 
            this.textBoxAvancer.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxAvancer.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.textBoxAvancer.Cursor = System.Windows.Forms.Cursors.Hand;
            this.textBoxAvancer.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxAvancer.HideSelection = false;
            this.textBoxAvancer.Location = new System.Drawing.Point(155, 30);
            this.textBoxAvancer.MaxLength = 10;
            this.textBoxAvancer.Name = "textBoxAvancer";
            this.textBoxAvancer.ReadOnly = true;
            this.textBoxAvancer.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.textBoxAvancer.Size = new System.Drawing.Size(100, 49);
            this.textBoxAvancer.TabIndex = 3;
            this.textBoxAvancer.Text = "W";
            this.textBoxAvancer.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxAvancer.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxAvancer_KeyPress);
            // 
            // textBoxHoraire
            // 
            this.textBoxHoraire.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxHoraire.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.textBoxHoraire.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxHoraire.HideSelection = false;
            this.textBoxHoraire.Location = new System.Drawing.Point(22, 122);
            this.textBoxHoraire.MaxLength = 10;
            this.textBoxHoraire.Name = "textBoxHoraire";
            this.textBoxHoraire.ReadOnly = true;
            this.textBoxHoraire.Size = new System.Drawing.Size(100, 49);
            this.textBoxHoraire.TabIndex = 2;
            this.textBoxHoraire.Text = "A";
            this.textBoxHoraire.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxHoraire.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxHoraire_KeyPress);
            // 
            // textBoxReculer
            // 
            this.textBoxReculer.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxReculer.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.textBoxReculer.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxReculer.HideSelection = false;
            this.textBoxReculer.Location = new System.Drawing.Point(155, 122);
            this.textBoxReculer.MaxLength = 10;
            this.textBoxReculer.Name = "textBoxReculer";
            this.textBoxReculer.ReadOnly = true;
            this.textBoxReculer.Size = new System.Drawing.Size(100, 49);
            this.textBoxReculer.TabIndex = 1;
            this.textBoxReculer.Text = "S";
            this.textBoxReculer.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxReculer.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReculer_KeyPress);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.buttonDeleteProfil);
            this.tabPage2.Controls.Add(this.buttonFiniProfil);
            this.tabPage2.Controls.Add(this.label6);
            this.tabPage2.Controls.Add(this.checkBox11);
            this.tabPage2.Controls.Add(this.checkBox10);
            this.tabPage2.Controls.Add(this.checkBox9);
            this.tabPage2.Controls.Add(this.checkBox8);
            this.tabPage2.Controls.Add(this.checkBox7);
            this.tabPage2.Controls.Add(this.checkBox6);
            this.tabPage2.Controls.Add(this.checkBox5);
            this.tabPage2.Controls.Add(this.checkBox4);
            this.tabPage2.Controls.Add(this.checkBox3);
            this.tabPage2.Controls.Add(this.checkBox2);
            this.tabPage2.Controls.Add(this.checkBox1);
            this.tabPage2.Controls.Add(this.buttonLoadProfil);
            this.tabPage2.Controls.Add(this.buttonSaveProfil);
            this.tabPage2.Controls.Add(this.buttonDefProfil);
            this.tabPage2.Controls.Add(this.comboBoxProfil);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(435, 296);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Gestion Profils";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // buttonDeleteProfil
            // 
            this.buttonDeleteProfil.Location = new System.Drawing.Point(347, 191);
            this.buttonDeleteProfil.Name = "buttonDeleteProfil";
            this.buttonDeleteProfil.Size = new System.Drawing.Size(81, 23);
            this.buttonDeleteProfil.TabIndex = 28;
            this.buttonDeleteProfil.Text = "Supprimer";
            this.buttonDeleteProfil.UseVisualStyleBackColor = true;
            this.buttonDeleteProfil.Click += new System.EventHandler(this.buttonDeleteProfil_Click);
            // 
            // buttonFiniProfil
            // 
            this.buttonFiniProfil.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonFiniProfil.Location = new System.Drawing.Point(347, 270);
            this.buttonFiniProfil.Name = "buttonFiniProfil";
            this.buttonFiniProfil.Size = new System.Drawing.Size(82, 23);
            this.buttonFiniProfil.TabIndex = 27;
            this.buttonFiniProfil.Text = "Fini";
            this.buttonFiniProfil.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(195, 9);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(30, 13);
            this.label6.TabIndex = 26;
            this.label6.Text = "Profil";
            // 
            // checkBox11
            // 
            this.checkBox11.AutoSize = true;
            this.checkBox11.Location = new System.Drawing.Point(21, 249);
            this.checkBox11.Name = "checkBox11";
            this.checkBox11.Size = new System.Drawing.Size(137, 17);
            this.checkBox11.TabIndex = 25;
            this.checkBox11.Text = "Activation des capteurs";
            this.checkBox11.UseVisualStyleBackColor = true;
            // 
            // checkBox10
            // 
            this.checkBox10.AutoSize = true;
            this.checkBox10.Location = new System.Drawing.Point(185, 217);
            this.checkBox10.Name = "checkBox10";
            this.checkBox10.Size = new System.Drawing.Size(73, 17);
            this.checkBox10.TabIndex = 24;
            this.checkBox10.Text = "Exception";
            this.checkBox10.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            this.checkBox9.AutoSize = true;
            this.checkBox9.Location = new System.Drawing.Point(21, 217);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(121, 17);
            this.checkBox9.TabIndex = 23;
            this.checkBox9.Text = "Capteur de distance";
            this.checkBox9.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            this.checkBox8.AutoSize = true;
            this.checkBox8.Location = new System.Drawing.Point(21, 185);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(102, 17);
            this.checkBox8.TabIndex = 22;
            this.checkBox8.Text = "Suiveur de ligne";
            this.checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Location = new System.Drawing.Point(185, 185);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(142, 17);
            this.checkBox7.TabIndex = 21;
            this.checkBox7.Text = "Vérification des capteurs";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            this.checkBox6.AutoSize = true;
            this.checkBox6.Location = new System.Drawing.Point(185, 152);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(131, 17);
            this.checkBox6.TabIndex = 20;
            this.checkBox6.Text = "Évitement par la droite";
            this.checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox5
            // 
            this.checkBox5.AutoSize = true;
            this.checkBox5.Location = new System.Drawing.Point(21, 152);
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.Size = new System.Drawing.Size(141, 17);
            this.checkBox5.TabIndex = 19;
            this.checkBox5.Text = "Évitement par la gauche";
            this.checkBox5.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            this.checkBox4.AutoSize = true;
            this.checkBox4.Location = new System.Drawing.Point(185, 119);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(134, 17);
            this.checkBox4.TabIndex = 18;
            this.checkBox4.Text = "Déviation vers la droite";
            this.checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Location = new System.Drawing.Point(21, 119);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(144, 17);
            this.checkBox3.TabIndex = 17;
            this.checkBox3.Text = "Déviation vers la gauche";
            this.checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(21, 85);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(143, 17);
            this.checkBox2.TabIndex = 16;
            this.checkBox2.Text = "Balayage sur 180 degrés";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(21, 58);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(89, 17);
            this.checkBox1.TabIndex = 15;
            this.checkBox1.Text = "Suivi de ligne";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // buttonLoadProfil
            // 
            this.buttonLoadProfil.Location = new System.Drawing.Point(348, 162);
            this.buttonLoadProfil.Name = "buttonLoadProfil";
            this.buttonLoadProfil.Size = new System.Drawing.Size(81, 23);
            this.buttonLoadProfil.TabIndex = 14;
            this.buttonLoadProfil.Text = "Charger";
            this.buttonLoadProfil.UseVisualStyleBackColor = true;
            // 
            // buttonSaveProfil
            // 
            this.buttonSaveProfil.Location = new System.Drawing.Point(348, 133);
            this.buttonSaveProfil.Name = "buttonSaveProfil";
            this.buttonSaveProfil.Size = new System.Drawing.Size(81, 23);
            this.buttonSaveProfil.TabIndex = 13;
            this.buttonSaveProfil.Text = "Sauvegarder";
            this.buttonSaveProfil.UseVisualStyleBackColor = true;
            this.buttonSaveProfil.Click += new System.EventHandler(this.buttonSaveProfil_Click);
            // 
            // buttonDefProfil
            // 
            this.buttonDefProfil.Location = new System.Drawing.Point(347, 241);
            this.buttonDefProfil.Name = "buttonDefProfil";
            this.buttonDefProfil.Size = new System.Drawing.Size(81, 23);
            this.buttonDefProfil.TabIndex = 12;
            this.buttonDefProfil.Text = "Défaut";
            this.buttonDefProfil.UseVisualStyleBackColor = true;
            this.buttonDefProfil.Click += new System.EventHandler(this.buttonDefProfil_Click);
            // 
            // comboBoxProfil
            // 
            this.comboBoxProfil.FormattingEnabled = true;
            this.comboBoxProfil.Items.AddRange(new object[] {
            "Défaut"});
            this.comboBoxProfil.Location = new System.Drawing.Point(124, 25);
            this.comboBoxProfil.Name = "comboBoxProfil";
            this.comboBoxProfil.Size = new System.Drawing.Size(166, 21);
            this.comboBoxProfil.TabIndex = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.label7);
            this.tabPage3.Controls.Add(this.buttonFiniDebug);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(435, 296);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Option Débogage";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(22, 112);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(391, 48);
            this.label7.TabIndex = 1;
            this.label7.Text = "DONT LOOK HERE YET! \r\nCONTACT THE TECHNICIEN IT\'S BROKEN!\r\n";
            // 
            // buttonFiniDebug
            // 
            this.buttonFiniDebug.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonFiniDebug.Location = new System.Drawing.Point(344, 267);
            this.buttonFiniDebug.Name = "buttonFiniDebug";
            this.buttonFiniDebug.Size = new System.Drawing.Size(84, 23);
            this.buttonFiniDebug.TabIndex = 0;
            this.buttonFiniDebug.Text = "Fini";
            this.buttonFiniDebug.UseVisualStyleBackColor = true;
            // 
            // Configure
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(443, 321);
            this.Controls.Add(this.tabControl1);
            this.Name = "Configure";
            this.Text = "Configure";
            this.Load += new System.EventHandler(this.Configure_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxAntiHoraire;
        private System.Windows.Forms.TextBox textBoxModeManuel;
        private System.Windows.Forms.TextBox textBoxAvancer;
        private System.Windows.Forms.TextBox textBoxHoraire;
        private System.Windows.Forms.TextBox textBoxReculer;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonFinConfig;
        private System.Windows.Forms.Button buttonDefConfig;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.CheckBox checkBox6;
        private System.Windows.Forms.CheckBox checkBox5;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Button buttonLoadProfil;
        private System.Windows.Forms.Button buttonSaveProfil;
        private System.Windows.Forms.Button buttonDefProfil;
        private System.Windows.Forms.ComboBox comboBoxProfil;
        private System.Windows.Forms.Button buttonFiniProfil;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox checkBox11;
        private System.Windows.Forms.CheckBox checkBox10;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.Button buttonFiniDebug;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonDeleteProfil;
    }
}