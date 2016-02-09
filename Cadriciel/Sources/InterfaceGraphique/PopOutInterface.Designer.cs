namespace InterfaceGraphique
{
    partial class PopOutInterface
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
            this.informationDone_ = new System.Windows.Forms.Button();
            this.infoText_ = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // informationDone_
            // 
            this.informationDone_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.informationDone_.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.informationDone_.Location = new System.Drawing.Point(105, 226);
            this.informationDone_.Name = "informationDone_";
            this.informationDone_.Size = new System.Drawing.Size(75, 23);
            this.informationDone_.TabIndex = 0;
            this.informationDone_.Text = "Done";
            this.informationDone_.UseVisualStyleBackColor = true;
            // 
            // infoText_
            // 
            this.infoText_.Location = new System.Drawing.Point(13, 13);
            this.infoText_.Name = "infoText_";
            this.infoText_.Size = new System.Drawing.Size(259, 210);
            this.infoText_.TabIndex = 1;
            this.infoText_.Text = "Entrez\r\ntout\r\nle\r\ntext\r\nnecessaire\r\nque\r\nle\r\nprogramme\r\ndoit\r\nfaire\r\net\r\nles\r\nkey" +
    "bind";
            // 
            // PopOutInterface
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.infoText_);
            this.Controls.Add(this.informationDone_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "PopOutInterface";
            this.Text = "Information";
            this.ResumeLayout(false);

            
        }

        #endregion

        private System.Windows.Forms.Button informationDone_;
        private System.Windows.Forms.Label infoText_;
    }

}