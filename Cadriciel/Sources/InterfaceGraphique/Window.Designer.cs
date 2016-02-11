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
            this.supprimerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.barreOutils_ = new System.Windows.Forms.ToolStrip();
            this.outilsSelection_ = new System.Windows.Forms.ToolStripButton();
            this.outilsDéplacement_ = new System.Windows.Forms.ToolStripButton();
            this.outilsRotation_ = new System.Windows.Forms.ToolStripButton();
            this.outilsMiseAEchelle_ = new System.Windows.Forms.ToolStripButton();
            this.outilsDuplication_ = new System.Windows.Forms.ToolStripButton();
            this.outilsZoom_ = new System.Windows.Forms.ToolStripButton();
            this.outilsCreationPoteau_ = new System.Windows.Forms.ToolStripButton();
            this.outilsCreationMurs_ = new System.Windows.Forms.ToolStripButton();
            this.outilsCreationLigne_ = new System.Windows.Forms.ToolStripButton();
            this.panneauOperation_ = new System.Windows.Forms.Panel();
            this.textBoxPositionY_ = new System.Windows.Forms.TextBox();
            this.textBoxPositionX_ = new System.Windows.Forms.TextBox();
            this.textBoxRotation_ = new System.Windows.Forms.TextBox();
            this.textboxDimension_ = new System.Windows.Forms.TextBox();
            this.panneauPositionY_ = new System.Windows.Forms.Label();
            this.panneauPositionX_ = new System.Windows.Forms.Label();
            this.panneauDimension_ = new System.Windows.Forms.Label();
            this.panneauRotation_ = new System.Windows.Forms.Label();
            this.zoomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();

            this.menuEdition_.SuspendLayout();
            this.barreOutils_.SuspendLayout();
            this.panneauOperation_.SuspendLayout();
            this.SuspendLayout();
            // 
            // viewPort_
            // 
            this.viewPort_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.viewPort_.AutoSize = true;
            this.viewPort_.Location = new System.Drawing.Point(0, 27);
            this.viewPort_.Name = "viewPort_";
            this.viewPort_.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort_.Size = new System.Drawing.Size(623, 402);
            this.viewPort_.TabIndex = 0;
            this.viewPort_.Visible = false;
            this.viewPort_.MouseClick += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseClick);
            this.viewPort_.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.viewPort__PreviewKeyDown);
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
            this.bouttonSimulation_.Click += new System.EventHandler(this.bouttonSimulation__Click);
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
            this.bouttonConfiguration_.Click += new System.EventHandler(this.bouttonConfiguration__Click);
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
            this.nouveauMenuEdition_.Click += new System.EventHandler(this.nouveauMenuEdition__Click);
            // 
            // ouvrirMenuEdition_
            // 
            this.ouvrirMenuEdition_.Name = "ouvrirMenuEdition_";
            this.ouvrirMenuEdition_.Size = new System.Drawing.Size(158, 22);
            this.ouvrirMenuEdition_.Text = "Ouvrir";
            this.ouvrirMenuEdition_.Click += new System.EventHandler(this.ouvrirMenuEdition__Click);
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
            this.enregistrerSousMenuEdition_.Click += new System.EventHandler(this.enregistrerSousMenuEdition__Click);
            // 
            // modeTestModeEdition_
            // 
            this.modeTestModeEdition_.Enabled = false;
            this.modeTestModeEdition_.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.modeTestModeEdition_.Name = "modeTestModeEdition_";
            this.modeTestModeEdition_.Size = new System.Drawing.Size(158, 22);
            this.modeTestModeEdition_.Text = "Mode test";
            this.modeTestModeEdition_.Click += new System.EventHandler(this.modeTestModeEdition__Click);
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
            this.editionMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.supprimerToolStripMenuItem});
            this.editionMenuEdition_.Name = "editionMenuEdition_";
            this.editionMenuEdition_.Size = new System.Drawing.Size(56, 20);
            this.editionMenuEdition_.Text = "Édition";
            // 
            // supprimerToolStripMenuItem
            // 
            this.supprimerToolStripMenuItem.Enabled = false;
            this.supprimerToolStripMenuItem.Name = "supprimerToolStripMenuItem";
            this.supprimerToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.supprimerToolStripMenuItem.Text = "Supprimer";
            this.supprimerToolStripMenuItem.Click += new System.EventHandler(this.supprimerToolStripMenuItem_Click);
            // 
            // outilsMenuEdition_
            // 
            this.outilsMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectionMenuEdition_,
            this.deplacementMenuEdition_,
            this.rotationMenuEdition_,
            this.miseAEchelleMenuEdition_,
            this.duplicationMenuEdition_,
            this.creationMenuEdition_,
            this.zoomToolStripMenuItem});
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
            this.aideMenuEdition_.Click += new System.EventHandler(this.aideMenuEdition__Click);
            // 
            // barreOutils_
            // 
            this.barreOutils_.AllowMerge = false;
            this.barreOutils_.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.barreOutils_.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.barreOutils_.Dock = System.Windows.Forms.DockStyle.None;
            this.barreOutils_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.outilsSelection_,
            this.outilsDéplacement_,
            this.outilsRotation_,
            this.outilsMiseAEchelle_,
            this.outilsDuplication_,
            this.outilsZoom_,
            this.outilsCreationPoteau_,
            this.outilsCreationMurs_,
            this.outilsCreationLigne_});
            this.barreOutils_.Location = new System.Drawing.Point(201, 394);
            this.barreOutils_.Name = "barreOutils_";
            this.barreOutils_.Size = new System.Drawing.Size(219, 25);
            this.barreOutils_.Stretch = true;
            this.barreOutils_.TabIndex = 7;
            this.barreOutils_.Text = "toolStrip1";
            // 
            // outilsSelection_
            // 
            this.outilsSelection_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsSelection_.Image = global::InterfaceGraphique.Properties.Resources.ic_near_me_white_48dp_2x;
            this.outilsSelection_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsSelection_.Name = "outilsSelection_";
            this.outilsSelection_.Size = new System.Drawing.Size(23, 22);
            this.outilsSelection_.Text = "Sélection";
            this.outilsSelection_.Click += new System.EventHandler(this.outilsSelection__Click);
            // 
            // outilsDéplacement_
            // 
            this.outilsDéplacement_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsDéplacement_.Image = global::InterfaceGraphique.Properties.Resources.ic_open_with;
            this.outilsDéplacement_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsDéplacement_.Name = "outilsDéplacement_";
            this.outilsDéplacement_.Size = new System.Drawing.Size(23, 22);
            this.outilsDéplacement_.Text = "Déplacement";
            this.outilsDéplacement_.Click += new System.EventHandler(this.outilsDéplacement__Click);
            // 
            // outilsRotation_
            // 
            this.outilsRotation_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsRotation_.Image = global::InterfaceGraphique.Properties.Resources.ic_loop_white_48dp_2x;
            this.outilsRotation_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsRotation_.Name = "outilsRotation_";
            this.outilsRotation_.Size = new System.Drawing.Size(23, 22);
            this.outilsRotation_.Text = "Rotation";
            this.outilsRotation_.Click += new System.EventHandler(this.outilsRotation__Click);
            // 
            // outilsMiseAEchelle_
            // 
            this.outilsMiseAEchelle_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsMiseAEchelle_.Image = global::InterfaceGraphique.Properties.Resources.ic_settings_overscan_white_48dp_2x;
            this.outilsMiseAEchelle_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsMiseAEchelle_.Name = "outilsMiseAEchelle_";
            this.outilsMiseAEchelle_.Size = new System.Drawing.Size(23, 22);
            this.outilsMiseAEchelle_.Text = "Mise à échelle";
            this.outilsMiseAEchelle_.Click += new System.EventHandler(this.outilsMiseAEchelle__Click);
            // 
            // outilsDuplication_
            // 
            this.outilsDuplication_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsDuplication_.Image = global::InterfaceGraphique.Properties.Resources.editcopy;
            this.outilsDuplication_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsDuplication_.Name = "outilsDuplication_";
            this.outilsDuplication_.Size = new System.Drawing.Size(23, 22);
            this.outilsDuplication_.Text = "Duplication";
            this.outilsDuplication_.Click += new System.EventHandler(this.outilsDuplication__Click);
            // 
            // outilsZoom_
            // 
            this.outilsZoom_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsZoom_.Image = global::InterfaceGraphique.Properties.Resources.ic_search_white_48dp_2x;
            this.outilsZoom_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsZoom_.Name = "outilsZoom_";
            this.outilsZoom_.Size = new System.Drawing.Size(23, 22);
            this.outilsZoom_.Text = "Zoom";
            this.outilsZoom_.Click += new System.EventHandler(this.outilsZoom__Click);
            // 
            // outilsCreationPoteau_
            // 
            this.outilsCreationPoteau_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationPoteau_.Image = global::InterfaceGraphique.Properties.Resources.ionic;
            this.outilsCreationPoteau_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationPoteau_.Name = "outilsCreationPoteau_";
            this.outilsCreationPoteau_.Size = new System.Drawing.Size(23, 22);
            this.outilsCreationPoteau_.Text = "Création de poteaux";
            this.outilsCreationPoteau_.Click += new System.EventHandler(this.outilsCreationPoteau__Click);
            // 
            // outilsCreationMurs_
            // 
            this.outilsCreationMurs_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationMurs_.Image = global::InterfaceGraphique.Properties.Resources.walls1;
            this.outilsCreationMurs_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationMurs_.Name = "outilsCreationMurs_";
            this.outilsCreationMurs_.Size = new System.Drawing.Size(23, 22);
            this.outilsCreationMurs_.Text = "Céreation de murs";
            this.outilsCreationMurs_.Click += new System.EventHandler(this.outilsCreationMurs__Click);
            // 
            // outilsCreationLigne_
            // 
            this.outilsCreationLigne_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationLigne_.Image = global::InterfaceGraphique.Properties.Resources.line2;
            this.outilsCreationLigne_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationLigne_.Name = "outilsCreationLigne_";
            this.outilsCreationLigne_.Size = new System.Drawing.Size(23, 22);
            this.outilsCreationLigne_.Text = "Création de lignes";
            this.outilsCreationLigne_.Click += new System.EventHandler(this.outilsCreationLigne__Click);
            // 
            // panneauOperation_
            // 
            this.panneauOperation_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panneauOperation_.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.panneauOperation_.Controls.Add(this.textBoxPositionY_);
            this.panneauOperation_.Controls.Add(this.textBoxPositionX_);
            this.panneauOperation_.Controls.Add(this.textBoxRotation_);
            this.panneauOperation_.Controls.Add(this.textboxDimension_);
            this.panneauOperation_.Controls.Add(this.panneauPositionY_);
            this.panneauOperation_.Controls.Add(this.panneauPositionX_);
            this.panneauOperation_.Controls.Add(this.panneauDimension_);
            this.panneauOperation_.Controls.Add(this.panneauRotation_);
            this.panneauOperation_.Location = new System.Drawing.Point(495, 27);
            this.panneauOperation_.Name = "panneauOperation_";
            this.panneauOperation_.Size = new System.Drawing.Size(128, 223);
            this.panneauOperation_.TabIndex = 8;
            // 
            // textBoxPositionY_
            // 
            this.textBoxPositionY_.Location = new System.Drawing.Point(18, 190);
            this.textBoxPositionY_.Name = "textBoxPositionY_";
            this.textBoxPositionY_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionY_.TabIndex = 7;
            this.textBoxPositionY_.TabStop = false;
            this.textBoxPositionY_.Click += new System.EventHandler(this.textBoxPositionY__Click);
            this.textBoxPositionY_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionY__KeyDown);
            // 
            // textBoxPositionX_
            // 
            this.textBoxPositionX_.Location = new System.Drawing.Point(18, 132);
            this.textBoxPositionX_.Name = "textBoxPositionX_";
            this.textBoxPositionX_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionX_.TabIndex = 6;
            this.textBoxPositionX_.TabStop = false;
            this.textBoxPositionX_.Click += new System.EventHandler(this.textBoxPositionX__Click);
            this.textBoxPositionX_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionX__KeyDown);
            // 
            // textBoxRotation_
            // 
            this.textBoxRotation_.Location = new System.Drawing.Point(18, 81);
            this.textBoxRotation_.Name = "textBoxRotation_";
            this.textBoxRotation_.Size = new System.Drawing.Size(84, 20);
            this.textBoxRotation_.TabIndex = 5;
            this.textBoxRotation_.TabStop = false;
            this.textBoxRotation_.Click += new System.EventHandler(this.textBoxRotation__Click);
            this.textBoxRotation_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxRotation__KeyDown);
            // 
            // textboxDimension_
            // 
            this.textboxDimension_.Location = new System.Drawing.Point(18, 30);
            this.textboxDimension_.Name = "textboxDimension_";
            this.textboxDimension_.Size = new System.Drawing.Size(84, 20);
            this.textboxDimension_.TabIndex = 4;
            this.textboxDimension_.TabStop = false;
            this.textboxDimension_.Click += new System.EventHandler(this.textboxDimension__Click);
            this.textboxDimension_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textboxDimension__KeyDown);
            // 
            // panneauPositionY_
            // 
            this.panneauPositionY_.AutoSize = true;
            this.panneauPositionY_.Location = new System.Drawing.Point(15, 174);
            this.panneauPositionY_.Name = "panneauPositionY_";
            this.panneauPositionY_.Size = new System.Drawing.Size(69, 13);
            this.panneauPositionY_.TabIndex = 3;
            this.panneauPositionY_.Text = "Position en Y";
            // 
            // panneauPositionX_
            // 
            this.panneauPositionX_.AutoSize = true;
            this.panneauPositionX_.Location = new System.Drawing.Point(15, 116);
            this.panneauPositionX_.Name = "panneauPositionX_";
            this.panneauPositionX_.Size = new System.Drawing.Size(69, 13);
            this.panneauPositionX_.TabIndex = 2;
            this.panneauPositionX_.Text = "Position en X";
            // 
            // panneauDimension_
            // 
            this.panneauDimension_.AutoSize = true;
            this.panneauDimension_.Location = new System.Drawing.Point(15, 14);
            this.panneauDimension_.Name = "panneauDimension_";
            this.panneauDimension_.Size = new System.Drawing.Size(108, 13);
            this.panneauDimension_.TabIndex = 1;
            this.panneauDimension_.Text = "Facteur de dimension";
            // 
            // panneauRotation_
            // 
            this.panneauRotation_.AutoSize = true;
            this.panneauRotation_.Location = new System.Drawing.Point(15, 65);
            this.panneauRotation_.Name = "panneauRotation_";
            this.panneauRotation_.Size = new System.Drawing.Size(87, 13);
            this.panneauRotation_.TabIndex = 0;
            this.panneauRotation_.Text = "Angle de rotation";
            // 
            // zoomToolStripMenuItem
            // 
            this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.zoomToolStripMenuItem.Text = "Zoom";
            this.zoomToolStripMenuItem.Click += new System.EventHandler(this.zoomToolStripMenuItem_Click);
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 428);
            this.Controls.Add(this.panneauOperation_);
            this.Controls.Add(this.barreOutils_);
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
            this.menuEdition_.ResumeLayout(false);
            this.menuEdition_.PerformLayout();
            this.barreOutils_.ResumeLayout(false);
            this.barreOutils_.PerformLayout();
            this.panneauOperation_.ResumeLayout(false);
            this.panneauOperation_.PerformLayout();
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
        private System.Windows.Forms.ToolStripButton outilsDéplacement_;
        private System.Windows.Forms.ToolStripButton outilsRotation_;
        private System.Windows.Forms.ToolStripButton outilsMiseAEchelle_;
        private System.Windows.Forms.ToolStripButton outilsDuplication_;
        private System.Windows.Forms.ToolStripButton outilsZoom_;
        private System.Windows.Forms.ToolStripButton outilsCreationPoteau_;
        private System.Windows.Forms.ToolStripButton outilsCreationMurs_;
        private System.Windows.Forms.ToolStripButton outilsCreationLigne_;
        private System.Windows.Forms.Panel panneauOperation_;
        private System.Windows.Forms.Label panneauRotation_;
        private System.Windows.Forms.Label panneauPositionY_;
        private System.Windows.Forms.Label panneauPositionX_;
        private System.Windows.Forms.Label panneauDimension_;
        private System.Windows.Forms.TextBox textBoxPositionY_;
        private System.Windows.Forms.TextBox textBoxPositionX_;
        private System.Windows.Forms.TextBox textBoxRotation_;
        private System.Windows.Forms.TextBox textboxDimension_;
        private System.Windows.Forms.ToolStripMenuItem zoomToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem supprimerToolStripMenuItem;
    }
}

