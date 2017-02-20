namespace ui
{
    partial class UserChat
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserChat));
            this.minMaxButton = new ui.PanelButton();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.outWindowButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tabControlWithoutHeader1 = new ui.TabControlWithoutHeader();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.chatTextBox1 = new System.Windows.Forms.TextBox();
            this.sendButton = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.panelButton1 = new ui.PanelButton();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.chatBox1 = new System.Windows.Forms.ListBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.minMaxButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.outWindowButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tabControlWithoutHeader1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.sendButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.panelButton1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.SuspendLayout();
            // 
            // minMaxButton
            // 
            this.minMaxButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.minMaxButton.BackColor = System.Drawing.Color.Transparent;
            this.minMaxButton.Controls.Add(this.pictureBox2);
            this.minMaxButton.Location = new System.Drawing.Point(205, 3);
            this.minMaxButton.Name = "minMaxButton";
            this.minMaxButton.Size = new System.Drawing.Size(26, 26);
            this.minMaxButton.TabIndex = 2;
            this.minMaxButton.Click += new System.EventHandler(this.minMaxButton_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(1, 1);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(24, 24);
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // outWindowButton
            // 
            this.outWindowButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.outWindowButton.BackColor = System.Drawing.Color.Transparent;
            this.outWindowButton.Controls.Add(this.pictureBox1);
            this.outWindowButton.Location = new System.Drawing.Point(236, 3);
            this.outWindowButton.Name = "outWindowButton";
            this.outWindowButton.Size = new System.Drawing.Size(26, 26);
            this.outWindowButton.TabIndex = 1;
            this.outWindowButton.Click += new System.EventHandler(this.outWindowButton_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(1, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 24);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // tabControlWithoutHeader1
            // 
            this.tabControlWithoutHeader1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControlWithoutHeader1.Controls.Add(this.tabPage1);
            this.tabControlWithoutHeader1.Controls.Add(this.tabPage2);
            this.tabControlWithoutHeader1.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControlWithoutHeader1.HotTrack = true;
            this.tabControlWithoutHeader1.Location = new System.Drawing.Point(0, 12);
            this.tabControlWithoutHeader1.Margin = new System.Windows.Forms.Padding(0);
            this.tabControlWithoutHeader1.Name = "tabControlWithoutHeader1";
            this.tabControlWithoutHeader1.Padding = new System.Drawing.Point(0, 0);
            this.tabControlWithoutHeader1.SelectedIndex = 0;
            this.tabControlWithoutHeader1.Size = new System.Drawing.Size(265, 268);
            this.tabControlWithoutHeader1.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.tabPage1.Controls.Add(this.chatTextBox1);
            this.tabPage1.Controls.Add(this.sendButton);
            this.tabPage1.Controls.Add(this.panelButton1);
            this.tabPage1.Controls.Add(this.chatBox1);
            this.tabPage1.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(0);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(257, 239);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Général";
            // 
            // chatTextBox1
            // 
            this.chatTextBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chatTextBox1.Location = new System.Drawing.Point(7, 210);
            this.chatTextBox1.Name = "chatTextBox1";
            this.chatTextBox1.Size = new System.Drawing.Size(193, 21);
            this.chatTextBox1.TabIndex = 8;
            this.chatTextBox1.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.chatTextBox1_PreviewKeyDown);
            // 
            // sendButton
            // 
            this.sendButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sendButton.BackColor = System.Drawing.Color.Transparent;
            this.sendButton.Controls.Add(this.pictureBox3);
            this.sendButton.Location = new System.Drawing.Point(205, 208);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(26, 26);
            this.sendButton.TabIndex = 6;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(1, 1);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(24, 24);
            this.pictureBox3.TabIndex = 0;
            this.pictureBox3.TabStop = false;
            // 
            // panelButton1
            // 
            this.panelButton1.Controls.Add(this.pictureBox4);
            this.panelButton1.Dock = System.Windows.Forms.DockStyle.Right;
            this.panelButton1.Location = new System.Drawing.Point(241, 0);
            this.panelButton1.Name = "panelButton1";
            this.panelButton1.Size = new System.Drawing.Size(16, 239);
            this.panelButton1.TabIndex = 7;
            // 
            // pictureBox4
            // 
            this.pictureBox4.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(0, 100);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(16, 16);
            this.pictureBox4.TabIndex = 0;
            this.pictureBox4.TabStop = false;
            // 
            // chatBox1
            // 
            this.chatBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chatBox1.FormattingEnabled = true;
            this.chatBox1.ItemHeight = 16;
            this.chatBox1.Location = new System.Drawing.Point(6, 6);
            this.chatBox1.Name = "chatBox1";
            this.chatBox1.Size = new System.Drawing.Size(225, 196);
            this.chatBox1.TabIndex = 4;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(257, 239);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // UserChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.minMaxButton);
            this.Controls.Add(this.outWindowButton);
            this.Controls.Add(this.tabControlWithoutHeader1);
            this.Name = "UserChat";
            this.Size = new System.Drawing.Size(265, 280);
            this.minMaxButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.outWindowButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tabControlWithoutHeader1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.sendButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.panelButton1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private PanelButton outWindowButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private PanelButton minMaxButton;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.TabPage tabPage1;
        private PanelButton sendButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private PanelButton panelButton1;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.ListBox chatBox1;
        private TabControlWithoutHeader tabControlWithoutHeader1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox chatTextBox1;
    }
}
