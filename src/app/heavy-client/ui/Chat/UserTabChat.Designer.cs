namespace ui
{
    partial class UserTabChat
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserTabChat));
            this.panel = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.tabControl = new ui.TabControlWithoutHeader();
            this.outWindowButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.minMaxButton = new ui.PanelButton();
            this.minMaxPictureBox = new System.Windows.Forms.PictureBox();
            this.onlineChatButton = new ui.PanelButton();
            this.customLabel1 = new ui.CustomLabel();
            this.panel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.outWindowButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.minMaxButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).BeginInit();
            this.onlineChatButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel
            // 
            this.panel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(204)))));
            this.panel.Controls.Add(this.panel2);
            this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel.Location = new System.Drawing.Point(0, 0);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(265, 280);
            this.panel.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.panel2.Controls.Add(this.tabControl);
            this.panel2.Controls.Add(this.outWindowButton);
            this.panel2.Controls.Add(this.minMaxButton);
            this.panel2.Controls.Add(this.onlineChatButton);
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(259, 277);
            this.panel2.TabIndex = 0;
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Font = new System.Drawing.Font("Century Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl.HotTrack = true;
            this.tabControl.Location = new System.Drawing.Point(1, 24);
            this.tabControl.Margin = new System.Windows.Forms.Padding(5);
            this.tabControl.Name = "tabControl";
            this.tabControl.Padding = new System.Drawing.Point(0, 0);
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(258, 253);
            this.tabControl.TabIndex = 11;
            // 
            // outWindowButton
            // 
            this.outWindowButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.outWindowButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.outWindowButton.Controls.Add(this.pictureBox1);
            this.outWindowButton.Location = new System.Drawing.Point(233, 0);
            this.outWindowButton.Name = "outWindowButton";
            this.outWindowButton.Size = new System.Drawing.Size(26, 26);
            this.outWindowButton.TabIndex = 9;
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
            // minMaxButton
            // 
            this.minMaxButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.minMaxButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.minMaxButton.Controls.Add(this.minMaxPictureBox);
            this.minMaxButton.Location = new System.Drawing.Point(202, 0);
            this.minMaxButton.Name = "minMaxButton";
            this.minMaxButton.Size = new System.Drawing.Size(26, 26);
            this.minMaxButton.TabIndex = 10;
            this.minMaxButton.Click += new System.EventHandler(this.minMaxButton_Click);
            // 
            // minMaxPictureBox
            // 
            this.minMaxPictureBox.Enabled = false;
            this.minMaxPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("minMaxPictureBox.Image")));
            this.minMaxPictureBox.Location = new System.Drawing.Point(1, 1);
            this.minMaxPictureBox.Name = "minMaxPictureBox";
            this.minMaxPictureBox.Size = new System.Drawing.Size(24, 24);
            this.minMaxPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.minMaxPictureBox.TabIndex = 0;
            this.minMaxPictureBox.TabStop = false;
            // 
            // onlineChatButton
            // 
            this.onlineChatButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.onlineChatButton.Controls.Add(this.customLabel1);
            this.onlineChatButton.Location = new System.Drawing.Point(1, 0);
            this.onlineChatButton.Name = "onlineChatButton";
            this.onlineChatButton.Size = new System.Drawing.Size(186, 22);
            this.onlineChatButton.TabIndex = 12;
            this.onlineChatButton.Click += new System.EventHandler(this.onlineChatButton_Click);
            // 
            // customLabel1
            // 
            this.customLabel1.AutoSize = true;
            this.customLabel1.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.customLabel1.ForeColor = System.Drawing.Color.Silver;
            this.customLabel1.Location = new System.Drawing.Point(3, 2);
            this.customLabel1.Name = "customLabel1";
            this.customLabel1.Size = new System.Drawing.Size(142, 17);
            this.customLabel1.TabIndex = 0;
            this.customLabel1.Text = "Clavardage en ligne";
            // 
            // UserTabChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.panel);
            this.Name = "UserTabChat";
            this.Size = new System.Drawing.Size(265, 280);
            this.panel.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.outWindowButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.minMaxButton.ResumeLayout(false);
            this.minMaxButton.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.minMaxPictureBox)).EndInit();
            this.onlineChatButton.ResumeLayout(false);
            this.onlineChatButton.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel;
        private System.Windows.Forms.Panel panel2;
        private PanelButton onlineChatButton;
        private CustomLabel customLabel1;
        private PanelButton minMaxButton;
        private System.Windows.Forms.PictureBox minMaxPictureBox;
        private PanelButton outWindowButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private TabControlWithoutHeader tabControl;
    }
}
