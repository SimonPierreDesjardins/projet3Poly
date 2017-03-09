namespace ui
{
    partial class ModeleSelector
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ModeleSelector));
            this.controlDescription = new System.Windows.Forms.Label();
            this.robotButton = new ui.PanelButton();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.truckButton = new ui.PanelButton();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.f1Button = new ui.PanelButton();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.audiButton = new ui.PanelButton();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.robotButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.truckButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.f1Button.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.audiButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.SuspendLayout();
            // 
            // controlDescription
            // 
            this.controlDescription.AutoSize = true;
            this.controlDescription.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.controlDescription.ForeColor = System.Drawing.Color.Silver;
            this.controlDescription.Location = new System.Drawing.Point(3, 0);
            this.controlDescription.Name = "controlDescription";
            this.controlDescription.Size = new System.Drawing.Size(175, 21);
            this.controlDescription.TabIndex = 0;
            this.controlDescription.Text = "Choix du chasis utilisé";
            // 
            // robotButton
            // 
            this.robotButton.Controls.Add(this.pictureBox1);
            this.robotButton.Location = new System.Drawing.Point(36, 56);
            this.robotButton.Name = "robotButton";
            this.robotButton.Size = new System.Drawing.Size(54, 54);
            this.robotButton.TabIndex = 1;
            this.robotButton.Click += new System.EventHandler(this.robotButton_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Enabled = false;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(9, 9);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(36, 36);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Silver;
            this.label1.Location = new System.Drawing.Point(33, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "Robot";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Silver;
            this.label2.Location = new System.Drawing.Point(153, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Audi";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Silver;
            this.label3.Location = new System.Drawing.Point(153, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "F1";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Century Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.Silver;
            this.label4.Location = new System.Drawing.Point(33, 116);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(61, 17);
            this.label4.TabIndex = 8;
            this.label4.Text = "Camion";
            // 
            // truckButton
            // 
            this.truckButton.Controls.Add(this.pictureBox3);
            this.truckButton.Location = new System.Drawing.Point(36, 136);
            this.truckButton.Name = "truckButton";
            this.truckButton.Size = new System.Drawing.Size(54, 54);
            this.truckButton.TabIndex = 3;
            this.truckButton.Click += new System.EventHandler(this.truckButton_Click);
            // 
            // pictureBox4
            // 
            this.pictureBox4.Enabled = false;
            this.pictureBox4.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox4.Image")));
            this.pictureBox4.Location = new System.Drawing.Point(9, 9);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(36, 36);
            this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox4.TabIndex = 0;
            this.pictureBox4.TabStop = false;
            // 
            // f1Button
            // 
            this.f1Button.Controls.Add(this.pictureBox4);
            this.f1Button.Location = new System.Drawing.Point(156, 136);
            this.f1Button.Name = "f1Button";
            this.f1Button.Size = new System.Drawing.Size(54, 54);
            this.f1Button.TabIndex = 4;
            this.f1Button.Click += new System.EventHandler(this.f1Button_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Enabled = false;
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(9, 9);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(36, 36);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // audiButton
            // 
            this.audiButton.Controls.Add(this.pictureBox2);
            this.audiButton.Location = new System.Drawing.Point(156, 56);
            this.audiButton.Name = "audiButton";
            this.audiButton.Size = new System.Drawing.Size(54, 54);
            this.audiButton.TabIndex = 2;
            this.audiButton.Click += new System.EventHandler(this.audiButton_Click);
            // 
            // pictureBox3
            // 
            this.pictureBox3.Enabled = false;
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(9, 9);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(36, 36);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox3.TabIndex = 0;
            this.pictureBox3.TabStop = false;
            // 
            // ModeleSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(32)))), ((int)(((byte)(40)))));
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.f1Button);
            this.Controls.Add(this.truckButton);
            this.Controls.Add(this.audiButton);
            this.Controls.Add(this.robotButton);
            this.Controls.Add(this.controlDescription);
            this.Name = "ModeleSelector";
            this.Size = new System.Drawing.Size(258, 207);
            this.robotButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.truckButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.f1Button.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.audiButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label controlDescription;
        private PanelButton robotButton;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private PanelButton truckButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private PanelButton f1Button;
        private System.Windows.Forms.PictureBox pictureBox2;
        private PanelButton audiButton;
    }
}
