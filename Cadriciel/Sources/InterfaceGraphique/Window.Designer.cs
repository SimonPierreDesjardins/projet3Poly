namespace InterfaceGraphique
{
    partial class Window
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

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.viewPort_ = new System.Windows.Forms.Panel();
            this.menuEdition_ = new System.Windows.Forms.MenuStrip();
            this.fichierMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.nouveauMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.ouvrirMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerMenuEdition = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.modeTestMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.editionMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.supprimerMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.outilsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.selectionMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.deplacementMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.rotationMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.miseAEchelleMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.duplicationMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.creationDobjetsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.poteauMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.murMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.ligneNoireMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.informationsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.aideMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.bouttonSimulation_ = new System.Windows.Forms.Button();
            this.bouttonEditeur_ = new System.Windows.Forms.Button();
            this.bouttonConfiguration_ = new System.Windows.Forms.Button();
            this.bouttonQuitter_ = new System.Windows.Forms.Button();
            this.viewPort_.SuspendLayout();
            this.menuEdition_.SuspendLayout();
            this.SuspendLayout();
            // 
            // viewPort_
            // 
            this.viewPort_.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.viewPort_.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.viewPort_.Controls.Add(this.menuEdition_);
            this.viewPort_.Location = new System.Drawing.Point(-4, -2);
            this.viewPort_.Name = "viewPort_";
            this.viewPort_.Size = new System.Drawing.Size(627, 430);
            this.viewPort_.TabIndex = 0;
            this.viewPort_.Visible = false;
            this.viewPort_.VisibleChanged += new System.EventHandler(this.viewPort__VisibleChanged);
            this.viewPort_.Paint += new System.Windows.Forms.PaintEventHandler(this.viewPort_Paint);
            // 
            // menuEdition_
            // 
            this.menuEdition_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierMenuEdition_,
            this.editionMenuEdition_,
            this.outilsMenuEdition_,
            this.vuesMenuEdition_,
            this.informationsMenuEdition_});
            this.menuEdition_.Location = new System.Drawing.Point(0, 0);
            this.menuEdition_.Name = "menuEdition_";
            this.menuEdition_.Size = new System.Drawing.Size(627, 24);
            this.menuEdition_.TabIndex = 0;
            this.menuEdition_.Text = "menuStrip1";
            // 
            // fichierMenuEdition_
            // 
            this.fichierMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nouveauMenuEdition_,
            this.ouvrirMenuEdition_,
            this.enregistrerMenuEdition,
            this.enregistrerMenuEdition_,
            this.modeTestMenuEdition_,
            this.menuPrincipalMenuEdition_});
            this.fichierMenuEdition_.Name = "fichierMenuEdition_";
            this.fichierMenuEdition_.Size = new System.Drawing.Size(54, 20);
            this.fichierMenuEdition_.Text = "Fichier";
            // 
            // nouveauMenuEdition_
            // 
            this.nouveauMenuEdition_.Name = "nouveauMenuEdition_";
            this.nouveauMenuEdition_.Size = new System.Drawing.Size(157, 22);
            this.nouveauMenuEdition_.Text = "Nouveau";
            // 
            // ouvrirMenuEdition_
            // 
            this.ouvrirMenuEdition_.Name = "ouvrirMenuEdition_";
            this.ouvrirMenuEdition_.Size = new System.Drawing.Size(157, 22);
            this.ouvrirMenuEdition_.Text = "Ouvrir";
            // 
            // enregistrerMenuEdition
            // 
            this.enregistrerMenuEdition.Name = "enregistrerMenuEdition";
            this.enregistrerMenuEdition.Size = new System.Drawing.Size(157, 22);
            this.enregistrerMenuEdition.Text = "Enregistrer";
            // 
            // enregistrerMenuEdition_
            // 
            this.enregistrerMenuEdition_.Name = "enregistrerMenuEdition_";
            this.enregistrerMenuEdition_.Size = new System.Drawing.Size(157, 22);
            this.enregistrerMenuEdition_.Text = "Enregistrer sous";
            // 
            // modeTestMenuEdition_
            // 
            this.modeTestMenuEdition_.Name = "modeTestMenuEdition_";
            this.modeTestMenuEdition_.Size = new System.Drawing.Size(157, 22);
            this.modeTestMenuEdition_.Text = "Mode test";
            // 
            // menuPrincipalMenuEdition_
            // 
            this.menuPrincipalMenuEdition_.Name = "menuPrincipalMenuEdition_";
            this.menuPrincipalMenuEdition_.Size = new System.Drawing.Size(157, 22);
            this.menuPrincipalMenuEdition_.Text = "Menu principal";
            this.menuPrincipalMenuEdition_.Click += new System.EventHandler(this.menuPrincipalMenuEdition__Click);
            // 
            // editionMenuEdition_
            // 
            this.editionMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.supprimerMenuEdition_});
            this.editionMenuEdition_.Name = "editionMenuEdition_";
            this.editionMenuEdition_.Size = new System.Drawing.Size(56, 20);
            this.editionMenuEdition_.Text = "Édition";
            // 
            // supprimerMenuEdition_
            // 
            this.supprimerMenuEdition_.Name = "supprimerMenuEdition_";
            this.supprimerMenuEdition_.Size = new System.Drawing.Size(129, 22);
            this.supprimerMenuEdition_.Text = "Supprimer";
            // 
            // outilsMenuEdition_
            // 
            this.outilsMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectionMenuEdition_,
            this.deplacementMenuEdition_,
            this.rotationMenuEdition_,
            this.miseAEchelleMenuEdition_,
            this.duplicationMenuEdition_,
            this.creationDobjetsMenuEdition_});
            this.outilsMenuEdition_.Name = "outilsMenuEdition_";
            this.outilsMenuEdition_.Size = new System.Drawing.Size(50, 20);
            this.outilsMenuEdition_.Text = "Outils";
            // 
            // selectionMenuEdition_
            // 
            this.selectionMenuEdition_.Name = "selectionMenuEdition_";
            this.selectionMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.selectionMenuEdition_.Text = "Sélection";
            // 
            // deplacementMenuEdition_
            // 
            this.deplacementMenuEdition_.Name = "deplacementMenuEdition_";
            this.deplacementMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.deplacementMenuEdition_.Text = "Déplacement";
            // 
            // rotationMenuEdition_
            // 
            this.rotationMenuEdition_.Name = "rotationMenuEdition_";
            this.rotationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.rotationMenuEdition_.Text = "Rotation";
            // 
            // miseAEchelleMenuEdition_
            // 
            this.miseAEchelleMenuEdition_.Name = "miseAEchelleMenuEdition_";
            this.miseAEchelleMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.miseAEchelleMenuEdition_.Text = "Mise à échelle";
            // 
            // duplicationMenuEdition_
            // 
            this.duplicationMenuEdition_.Name = "duplicationMenuEdition_";
            this.duplicationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.duplicationMenuEdition_.Text = "Duplication";
            // 
            // creationDobjetsMenuEdition_
            // 
            this.creationDobjetsMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.poteauMenuEdition_,
            this.murMenuEdition_,
            this.ligneNoireMenuEdition_});
            this.creationDobjetsMenuEdition_.Name = "creationDobjetsMenuEdition_";
            this.creationDobjetsMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.creationDobjetsMenuEdition_.Text = "Création d\'objets";
            // 
            // poteauMenuEdition_
            // 
            this.poteauMenuEdition_.Name = "poteauMenuEdition_";
            this.poteauMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.poteauMenuEdition_.Text = "Poteau";
            // 
            // murMenuEdition_
            // 
            this.murMenuEdition_.Name = "murMenuEdition_";
            this.murMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.murMenuEdition_.Text = "Mur";
            // 
            // ligneNoireMenuEdition_
            // 
            this.ligneNoireMenuEdition_.Name = "ligneNoireMenuEdition_";
            this.ligneNoireMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.ligneNoireMenuEdition_.Text = "Ligne noire";
            // 
            // vuesMenuEdition_
            // 
            this.vuesMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueMenuEdition_,
            this.orbiteMenuEdition_});
            this.vuesMenuEdition_.Name = "vuesMenuEdition_";
            this.vuesMenuEdition_.Size = new System.Drawing.Size(44, 20);
            this.vuesMenuEdition_.Text = "Vues";
            // 
            // orthographiqueMenuEdition_
            // 
            this.orthographiqueMenuEdition_.Name = "orthographiqueMenuEdition_";
            this.orthographiqueMenuEdition_.Size = new System.Drawing.Size(159, 22);
            this.orthographiqueMenuEdition_.Text = "Orthographique";
            // 
            // orbiteMenuEdition_
            // 
            this.orbiteMenuEdition_.Name = "orbiteMenuEdition_";
            this.orbiteMenuEdition_.Size = new System.Drawing.Size(159, 22);
            this.orbiteMenuEdition_.Text = "Orbite";
            // 
            // informationsMenuEdition_
            // 
            this.informationsMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aideMenuEdition_});
            this.informationsMenuEdition_.Name = "informationsMenuEdition_";
            this.informationsMenuEdition_.Size = new System.Drawing.Size(87, 20);
            this.informationsMenuEdition_.Text = "Informations";
            // 
            // aideMenuEdition_
            // 
            this.aideMenuEdition_.Name = "aideMenuEdition_";
            this.aideMenuEdition_.Size = new System.Drawing.Size(98, 22);
            this.aideMenuEdition_.Text = "Aide";
            // 
            // bouttonSimulation_
            // 
            this.bouttonSimulation_.Enabled = false;
            this.bouttonSimulation_.Location = new System.Drawing.Point(225, 109);
            this.bouttonSimulation_.Name = "bouttonSimulation_";
            this.bouttonSimulation_.Size = new System.Drawing.Size(175, 23);
            this.bouttonSimulation_.TabIndex = 1;
            this.bouttonSimulation_.TabStop = false;
            this.bouttonSimulation_.Text = "Simulation";
            this.bouttonSimulation_.UseVisualStyleBackColor = true;
            this.bouttonSimulation_.Click += new System.EventHandler(this.buttonSimulation_Click);
            // 
            // bouttonEditeur_
            // 
            this.bouttonEditeur_.Location = new System.Drawing.Point(225, 153);
            this.bouttonEditeur_.Name = "bouttonEditeur_";
            this.bouttonEditeur_.Size = new System.Drawing.Size(175, 23);
            this.bouttonEditeur_.TabIndex = 2;
            this.bouttonEditeur_.TabStop = false;
            this.bouttonEditeur_.Text = "Éditeur";
            this.bouttonEditeur_.UseVisualStyleBackColor = true;
            this.bouttonEditeur_.Click += new System.EventHandler(this.buttonEditeur_Click);
            // 
            // bouttonConfiguration_
            // 
            this.bouttonConfiguration_.Enabled = false;
            this.bouttonConfiguration_.Location = new System.Drawing.Point(225, 201);
            this.bouttonConfiguration_.Name = "bouttonConfiguration_";
            this.bouttonConfiguration_.Size = new System.Drawing.Size(175, 23);
            this.bouttonConfiguration_.TabIndex = 3;
            this.bouttonConfiguration_.TabStop = false;
            this.bouttonConfiguration_.Text = "Configuration";
            this.bouttonConfiguration_.UseVisualStyleBackColor = true;
            this.bouttonConfiguration_.Click += new System.EventHandler(this.buttonConfiguration_Click);
            // 
            // bouttonQuitter_
            // 
            this.bouttonQuitter_.Location = new System.Drawing.Point(225, 247);
            this.bouttonQuitter_.Name = "bouttonQuitter_";
            this.bouttonQuitter_.Size = new System.Drawing.Size(175, 23);
            this.bouttonQuitter_.TabIndex = 4;
            this.bouttonQuitter_.TabStop = false;
            this.bouttonQuitter_.Text = "Quitter";
            this.bouttonQuitter_.UseVisualStyleBackColor = true;
            this.bouttonQuitter_.Click += new System.EventHandler(this.buttonQuitter_Click);
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 428);
            this.Controls.Add(this.bouttonSimulation_);
            this.Controls.Add(this.bouttonQuitter_);
            this.Controls.Add(this.bouttonEditeur_);
            this.Controls.Add(this.bouttonConfiguration_);
            this.Controls.Add(this.viewPort_);
            this.MainMenuStrip = this.menuEdition_;
            this.Name = "Window";
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.Load += new System.EventHandler(this.Window_Load);
            this.viewPort_.ResumeLayout(false);
            this.viewPort_.PerformLayout();
            this.menuEdition_.ResumeLayout(false);
            this.menuEdition_.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion


        private System.Windows.Forms.Panel viewPort_;
        private System.Windows.Forms.MenuStrip menuEdition_;
        private System.Windows.Forms.ToolStripMenuItem fichierMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem nouveauMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem ouvrirMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem enregistrerMenuEdition;
        private System.Windows.Forms.ToolStripMenuItem enregistrerMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem modeTestMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem editionMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem supprimerMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem outilsMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem selectionMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem deplacementMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem rotationMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem miseAEchelleMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem duplicationMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem creationDobjetsMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem poteauMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem murMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem ligneNoireMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem vuesMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem orbiteMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem informationsMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem aideMenuEdition_;
        private System.Windows.Forms.Button bouttonSimulation_;
        private System.Windows.Forms.Button bouttonEditeur_;
        private System.Windows.Forms.Button bouttonConfiguration_;
        private System.Windows.Forms.Button bouttonQuitter_;
    }
}

