﻿namespace InterfaceGraphique
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Window));
            this.viewPort_ = new System.Windows.Forms.Panel();
            this.barreOutils_ = new System.Windows.Forms.ToolStrip();
            this.bouttonSimulation_ = new System.Windows.Forms.Button();
            this.bouttonEditeur_ = new System.Windows.Forms.Button();
            this.bouttonConfiguration_ = new System.Windows.Forms.Button();
            this.bouttonQuitter_ = new System.Windows.Forms.Button();
            this.menuEdition_ = new System.Windows.Forms.MenuStrip();
            this.fichierMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.nouveauMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.ouvrirMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerSousMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.modeTestModeEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalMenuEdition = new System.Windows.Forms.ToolStripMenuItem();
            this.editionMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.outilsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.selectionMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.deplacementMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.rotationMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.miseAEchelleMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.duplicationMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.creationMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.poteauMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.murMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.ligneNoireMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.informationsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.aideMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.outilsSelection_ = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.outilsRotation_ = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.outilsZoom_ = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton7 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton8 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton9 = new System.Windows.Forms.ToolStripButton();
            this.viewPort_.SuspendLayout();
            this.barreOutils_.SuspendLayout();
            this.menuEdition_.SuspendLayout();
            this.SuspendLayout();
            // 
            // viewPort_
            // 
            this.viewPort_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.viewPort_.AutoSize = true;
            this.viewPort_.Controls.Add(this.barreOutils_);
            this.viewPort_.Location = new System.Drawing.Point(0, 27);
            this.viewPort_.Name = "viewPort_";
            this.viewPort_.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort_.Size = new System.Drawing.Size(623, 400);
            this.viewPort_.TabIndex = 0;
            this.viewPort_.Visible = false;
            // 
            // barreOutils_
            // 
            this.barreOutils_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.barreOutils_.BackColor = System.Drawing.Color.Transparent;
            this.barreOutils_.Dock = System.Windows.Forms.DockStyle.None;
            this.barreOutils_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.outilsSelection_,
            this.toolStripButton2,
            this.outilsRotation_,
            this.toolStripButton4,
            this.toolStripButton5,
            this.outilsZoom_,
            this.toolStripButton7,
            this.toolStripButton8,
            this.toolStripButton9});
            this.barreOutils_.Location = new System.Drawing.Point(200, 317);
            this.barreOutils_.Name = "barreOutils_";
            this.barreOutils_.Size = new System.Drawing.Size(219, 25);
            this.barreOutils_.TabIndex = 0;
            this.barreOutils_.Text = "toolStrip1";
            // 
            // bouttonSimulation_
            // 
            this.bouttonSimulation_.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.bouttonSimulation_.Enabled = false;
            this.bouttonSimulation_.Location = new System.Drawing.Point(225, 109);
            this.bouttonSimulation_.Name = "bouttonSimulation_";
            this.bouttonSimulation_.Size = new System.Drawing.Size(175, 23);
            this.bouttonSimulation_.TabIndex = 1;
            this.bouttonSimulation_.TabStop = false;
            this.bouttonSimulation_.Text = "Simulation";
            this.bouttonSimulation_.UseVisualStyleBackColor = true;
            // 
            // bouttonEditeur_
            // 
            this.bouttonEditeur_.Anchor = System.Windows.Forms.AnchorStyles.None;
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
            this.bouttonConfiguration_.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.bouttonConfiguration_.Enabled = false;
            this.bouttonConfiguration_.Location = new System.Drawing.Point(225, 201);
            this.bouttonConfiguration_.Name = "bouttonConfiguration_";
            this.bouttonConfiguration_.Size = new System.Drawing.Size(175, 23);
            this.bouttonConfiguration_.TabIndex = 3;
            this.bouttonConfiguration_.TabStop = false;
            this.bouttonConfiguration_.Text = "Configuration";
            this.bouttonConfiguration_.UseVisualStyleBackColor = true;
            // 
            // bouttonQuitter_
            // 
            this.bouttonQuitter_.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.bouttonQuitter_.Location = new System.Drawing.Point(225, 247);
            this.bouttonQuitter_.Name = "bouttonQuitter_";
            this.bouttonQuitter_.Size = new System.Drawing.Size(175, 23);
            this.bouttonQuitter_.TabIndex = 4;
            this.bouttonQuitter_.TabStop = false;
            this.bouttonQuitter_.Text = "Quitter";
            this.bouttonQuitter_.UseVisualStyleBackColor = true;
            this.bouttonQuitter_.Click += new System.EventHandler(this.buttonQuitter_Click);
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
            this.menuEdition_.Size = new System.Drawing.Size(623, 24);
            this.menuEdition_.TabIndex = 5;
            this.menuEdition_.Text = "menuStrip1";
            // 
            // fichierMenuEdition_
            // 
            this.fichierMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nouveauMenuEdition_,
            this.ouvrirMenuEdition_,
            this.enregistrerMenuEdition_,
            this.enregistrerSousMenuEdition_,
            this.modeTestModeEdition_,
            this.menuPrincipalMenuEdition});
            this.fichierMenuEdition_.Name = "fichierMenuEdition_";
            this.fichierMenuEdition_.Size = new System.Drawing.Size(54, 20);
            this.fichierMenuEdition_.Text = "Fichier";
            // 
            // nouveauMenuEdition_
            // 
            this.nouveauMenuEdition_.Name = "nouveauMenuEdition_";
            this.nouveauMenuEdition_.Size = new System.Drawing.Size(158, 22);
            this.nouveauMenuEdition_.Text = "Nouveau";
            // 
            // ouvrirMenuEdition_
            // 
            this.ouvrirMenuEdition_.Name = "ouvrirMenuEdition_";
            this.ouvrirMenuEdition_.Size = new System.Drawing.Size(158, 22);
            this.ouvrirMenuEdition_.Text = "Ouvrir";
            // 
            // enregistrerMenuEdition_
            // 
            this.enregistrerMenuEdition_.Name = "enregistrerMenuEdition_";
            this.enregistrerMenuEdition_.Size = new System.Drawing.Size(158, 22);
            this.enregistrerMenuEdition_.Text = "Enregistrer";
            // 
            // enregistrerSousMenuEdition_
            // 
            this.enregistrerSousMenuEdition_.Name = "enregistrerSousMenuEdition_";
            this.enregistrerSousMenuEdition_.Size = new System.Drawing.Size(158, 22);
            this.enregistrerSousMenuEdition_.Text = "Enregistrer Sous";
            // 
            // modeTestModeEdition_
            // 
            this.modeTestModeEdition_.Name = "modeTestModeEdition_";
            this.modeTestModeEdition_.Size = new System.Drawing.Size(158, 22);
            this.modeTestModeEdition_.Text = "Mode test";
            // 
            // menuPrincipalMenuEdition
            // 
            this.menuPrincipalMenuEdition.Name = "menuPrincipalMenuEdition";
            this.menuPrincipalMenuEdition.Size = new System.Drawing.Size(158, 22);
            this.menuPrincipalMenuEdition.Text = "Menu Principal";
            this.menuPrincipalMenuEdition.Click += new System.EventHandler(this.menuPrincipalToolStripMenuItem_Click);
            // 
            // editionMenuEdition_
            // 
            this.editionMenuEdition_.Name = "editionMenuEdition_";
            this.editionMenuEdition_.Size = new System.Drawing.Size(56, 20);
            this.editionMenuEdition_.Text = "Édition";
            // 
            // outilsMenuEdition_
            // 
            this.outilsMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectionMenuEdition_,
            this.deplacementMenuEdition_,
            this.rotationMenuEdition_,
            this.miseAEchelleMenuEdition_,
            this.duplicationMenuEdition_,
            this.creationMenuEdition_});
            this.outilsMenuEdition_.Name = "outilsMenuEdition_";
            this.outilsMenuEdition_.Size = new System.Drawing.Size(50, 20);
            this.outilsMenuEdition_.Text = "Outils";
            // 
            // selectionMenuEdition_
            // 
            this.selectionMenuEdition_.Name = "selectionMenuEdition_";
            this.selectionMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.selectionMenuEdition_.Text = "Sélection";
            this.selectionMenuEdition_.Click += new System.EventHandler(this.sToolStripMenuItem_Click);
            // 
            // deplacementMenuEdition_
            // 
            this.deplacementMenuEdition_.Name = "deplacementMenuEdition_";
            this.deplacementMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.deplacementMenuEdition_.Text = "Déplacement";
            this.deplacementMenuEdition_.Click += new System.EventHandler(this.déplacementToolStripMenuItem_Click);
            // 
            // rotationMenuEdition_
            // 
            this.rotationMenuEdition_.Name = "rotationMenuEdition_";
            this.rotationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.rotationMenuEdition_.Text = "Rotation";
            this.rotationMenuEdition_.Click += new System.EventHandler(this.rotationToolStripMenuItem_Click);
            // 
            // miseAEchelleMenuEdition_
            // 
            this.miseAEchelleMenuEdition_.Name = "miseAEchelleMenuEdition_";
            this.miseAEchelleMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.miseAEchelleMenuEdition_.Text = "Mise à échelle";
            this.miseAEchelleMenuEdition_.Click += new System.EventHandler(this.miseAÉchelleToolStripMenuItem_Click);
            // 
            // duplicationMenuEdition_
            // 
            this.duplicationMenuEdition_.Name = "duplicationMenuEdition_";
            this.duplicationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.duplicationMenuEdition_.Text = "Duplication";
            this.duplicationMenuEdition_.Click += new System.EventHandler(this.duplicationToolStripMenuItem_Click);
            // 
            // creationMenuEdition_
            // 
            this.creationMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.poteauMenuEdition_,
            this.murMenuEdition_,
            this.ligneNoireMenuEdition_});
            this.creationMenuEdition_.Name = "creationMenuEdition_";
            this.creationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.creationMenuEdition_.Text = "Création d\'objets";
            // 
            // poteauMenuEdition_
            // 
            this.poteauMenuEdition_.Name = "poteauMenuEdition_";
            this.poteauMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.poteauMenuEdition_.Text = "Poteau";
            this.poteauMenuEdition_.Click += new System.EventHandler(this.poteauToolStripMenuItem_Click);
            // 
            // murMenuEdition_
            // 
            this.murMenuEdition_.Name = "murMenuEdition_";
            this.murMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.murMenuEdition_.Text = "Mur";
            this.murMenuEdition_.Click += new System.EventHandler(this.murToolStripMenuItem_Click);
            // 
            // ligneNoireMenuEdition_
            // 
            this.ligneNoireMenuEdition_.Name = "ligneNoireMenuEdition_";
            this.ligneNoireMenuEdition_.Size = new System.Drawing.Size(133, 22);
            this.ligneNoireMenuEdition_.Text = "Ligne noire";
            this.ligneNoireMenuEdition_.Click += new System.EventHandler(this.ligneNoireToolStripMenuItem_Click);
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
            // outilsSelection_
            // 
            this.outilsSelection_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsSelection_.Image = global::InterfaceGraphique.Properties.Resources.ic_near_me_white_48dp_2x;
            this.outilsSelection_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsSelection_.Name = "outilsSelection_";
            this.outilsSelection_.Size = new System.Drawing.Size(23, 22);
            this.outilsSelection_.Text = "outilsSelection_";
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Text = "toolStripButton2";
            // 
            // outilsRotation_
            // 
            this.outilsRotation_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsRotation_.Image = global::InterfaceGraphique.Properties.Resources.ic_loop_white_48dp_2x;
            this.outilsRotation_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsRotation_.Name = "outilsRotation_";
            this.outilsRotation_.Size = new System.Drawing.Size(23, 22);
            this.outilsRotation_.Text = "outilsRotation_";
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton4.Image = global::InterfaceGraphique.Properties.Resources.ic_settings_overscan_white_48dp_2x;
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton4.Text = "toolStripButton4";
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton5.Image = global::InterfaceGraphique.Properties.Resources.editcopy;
            this.toolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton5.Text = "toolStripButton5";
            // 
            // outilsZoom_
            // 
            this.outilsZoom_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsZoom_.Image = global::InterfaceGraphique.Properties.Resources.ic_search_white_48dp_2x;
            this.outilsZoom_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsZoom_.Name = "outilsZoom_";
            this.outilsZoom_.Size = new System.Drawing.Size(23, 22);
            this.outilsZoom_.Text = "outilsZoom_";
            // 
            // toolStripButton7
            // 
            this.toolStripButton7.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton7.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton7.Image")));
            this.toolStripButton7.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton7.Name = "toolStripButton7";
            this.toolStripButton7.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton7.Text = "toolStripButton7";
            // 
            // toolStripButton8
            // 
            this.toolStripButton8.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton8.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton8.Image")));
            this.toolStripButton8.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton8.Name = "toolStripButton8";
            this.toolStripButton8.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton8.Text = "toolStripButton8";
            // 
            // toolStripButton9
            // 
            this.toolStripButton9.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton9.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton9.Image")));
            this.toolStripButton9.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton9.Name = "toolStripButton9";
            this.toolStripButton9.Size = new System.Drawing.Size(23, 20);
            this.toolStripButton9.Text = "toolStripButton9";
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 428);
            this.Controls.Add(this.menuEdition_);
            this.Controls.Add(this.bouttonSimulation_);
            this.Controls.Add(this.bouttonQuitter_);
            this.Controls.Add(this.bouttonEditeur_);
            this.Controls.Add(this.bouttonConfiguration_);
            this.Controls.Add(this.viewPort_);
            this.MinimumSize = new System.Drawing.Size(100, 100);
            this.Name = "Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.Load += new System.EventHandler(this.Window_Load);
            this.Resize += new System.EventHandler(this.Window_Resize);
            this.viewPort_.ResumeLayout(false);
            this.viewPort_.PerformLayout();
            this.barreOutils_.ResumeLayout(false);
            this.barreOutils_.PerformLayout();
            this.menuEdition_.ResumeLayout(false);
            this.menuEdition_.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion


        private System.Windows.Forms.Panel viewPort_;
        private System.Windows.Forms.Button bouttonSimulation_;
        private System.Windows.Forms.Button bouttonEditeur_;
        private System.Windows.Forms.Button bouttonConfiguration_;
        private System.Windows.Forms.Button bouttonQuitter_;
        private System.Windows.Forms.MenuStrip menuEdition_;
        private System.Windows.Forms.ToolStripMenuItem fichierMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem nouveauMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem ouvrirMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem enregistrerMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem enregistrerSousMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem modeTestModeEdition_;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalMenuEdition;
        private System.Windows.Forms.ToolStripMenuItem editionMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem outilsMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem selectionMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem deplacementMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem rotationMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem miseAEchelleMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem duplicationMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem creationMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem vuesMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem orbiteMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem informationsMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem aideMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem poteauMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem murMenuEdition_;
        private System.Windows.Forms.ToolStripMenuItem ligneNoireMenuEdition_;
        private System.Windows.Forms.ToolStrip barreOutils_;
        private System.Windows.Forms.ToolStripButton outilsSelection_;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripButton outilsRotation_;
        private System.Windows.Forms.ToolStripButton toolStripButton4;
        private System.Windows.Forms.ToolStripButton toolStripButton5;
        private System.Windows.Forms.ToolStripButton outilsZoom_;
        private System.Windows.Forms.ToolStripButton toolStripButton7;
        private System.Windows.Forms.ToolStripButton toolStripButton8;
        private System.Windows.Forms.ToolStripButton toolStripButton9;
    }
}

