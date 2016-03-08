namespace InterfaceGraphique
{
    partial class NouveauProfil
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
            this.nomFichierTextBox = new System.Windows.Forms.TextBox();
            this.creerFichierButt = new System.Windows.Forms.Button();
            this.annulerCreerFichierButt = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // nomFichierTextBox
            // 
            this.nomFichierTextBox.Location = new System.Drawing.Point(12, 12);
            this.nomFichierTextBox.Name = "nomFichierTextBox";
            this.nomFichierTextBox.Size = new System.Drawing.Size(260, 20);
            this.nomFichierTextBox.TabIndex = 0;
            // 
            // creerFichierButt
            // 
            this.creerFichierButt.Location = new System.Drawing.Point(12, 38);
            this.creerFichierButt.Name = "creerFichierButt";
            this.creerFichierButt.Size = new System.Drawing.Size(75, 23);
            this.creerFichierButt.TabIndex = 1;
            this.creerFichierButt.Text = "Ok";
            this.creerFichierButt.UseVisualStyleBackColor = true;
            this.creerFichierButt.Click += new System.EventHandler(this.creerFichierButt_Click);
            // 
            // annulerCreerFichierButt
            // 
            this.annulerCreerFichierButt.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.annulerCreerFichierButt.Location = new System.Drawing.Point(197, 38);
            this.annulerCreerFichierButt.Name = "annulerCreerFichierButt";
            this.annulerCreerFichierButt.Size = new System.Drawing.Size(75, 23);
            this.annulerCreerFichierButt.TabIndex = 2;
            this.annulerCreerFichierButt.Text = "Annuler";
            this.annulerCreerFichierButt.UseVisualStyleBackColor = true;
            this.annulerCreerFichierButt.Click += new System.EventHandler(this.annulerCreerFichierButt_Click);
            // 
            // NouveauFichier
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 66);
            this.Controls.Add(this.annulerCreerFichierButt);
            this.Controls.Add(this.creerFichierButt);
            this.Controls.Add(this.nomFichierTextBox);
            this.Name = "NouveauFichier";
            this.Text = "Nouvelle zone";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox nomFichierTextBox;
        private System.Windows.Forms.Button creerFichierButt;
        private System.Windows.Forms.Button annulerCreerFichierButt;
    }
}