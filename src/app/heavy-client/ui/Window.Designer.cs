namespace ui
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
            this.viewPort = new System.Windows.Forms.Panel();
            this.picturePause = new System.Windows.Forms.PictureBox();
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
            this.zoomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.informationsMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.aideMenuEdition_ = new System.Windows.Forms.ToolStripMenuItem();
            this.barreOutils_ = new System.Windows.Forms.ToolStrip();
            this.outilsSelection_ = new System.Windows.Forms.ToolStripButton();
            this.outilsDeplacement_ = new System.Windows.Forms.ToolStripButton();
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
            this.menuSimTest = new System.Windows.Forms.MenuStrip();
            this.fichierMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.modeEditionMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.premierePersonneMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.profilsMenuSimTest = new System.Windows.Forms.ToolStripMenuItem();
            this.viewPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).BeginInit();
            this.menuEdition_.SuspendLayout();
            this.barreOutils_.SuspendLayout();
            this.panneauOperation_.SuspendLayout();
            this.menuSimTest.SuspendLayout();
            this.SuspendLayout();
            // 
            // viewPort
            // 
            this.viewPort.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.viewPort.AutoSize = true;
            this.viewPort.Controls.Add(this.picturePause);
            this.viewPort.Location = new System.Drawing.Point(0, 0);
            this.viewPort.MinimumSize = new System.Drawing.Size(100, 100);
            this.viewPort.Name = "viewPort";
            this.viewPort.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort.Size = new System.Drawing.Size(623, 462);
            this.viewPort.TabIndex = 0;
            this.viewPort.MouseMove += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseMove);
            this.viewPort.MouseUp += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseUp);
            this.viewPort.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.viewPort__PreviewKeyDown);
            // 
            // picturePause
            // 
            this.picturePause.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picturePause.Image = global::ui.Properties.Resources.pauseNoire;
            this.picturePause.Location = new System.Drawing.Point(267, 171);
            this.picturePause.Name = "picturePause";
            this.picturePause.Size = new System.Drawing.Size(96, 96);
            this.picturePause.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.picturePause.TabIndex = 0;
            this.picturePause.TabStop = false;
            this.picturePause.Visible = false;
            // 
            // bouttonSimulation_
            // 
            this.bouttonSimulation_.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.bouttonSimulation_.Location = new System.Drawing.Point(225, 125);
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
            this.bouttonEditeur_.Location = new System.Drawing.Point(225, 169);
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
            this.bouttonConfiguration_.Location = new System.Drawing.Point(225, 217);
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
            this.bouttonQuitter_.Location = new System.Drawing.Point(225, 263);
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
            this.menuEdition_.Visible = false;
            this.menuEdition_.VisibleChanged += new System.EventHandler(this.menuEdition__VisibleChanged);
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
            this.nouveauMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.nouveauMenuEdition_.Text = "Nouveau";
            this.nouveauMenuEdition_.Click += new System.EventHandler(this.nouveauMenuEdition__Click);
            // 
            // ouvrirMenuEdition_
            // 
            this.ouvrirMenuEdition_.Name = "ouvrirMenuEdition_";
            this.ouvrirMenuEdition_.ShortcutKeyDisplayString = "CTRL-O";
            this.ouvrirMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.ouvrirMenuEdition_.Text = "Ouvrir";
            this.ouvrirMenuEdition_.Click += new System.EventHandler(this.ouvrirMenuEdition__Click);
            // 
            // enregistrerMenuEdition_
            // 
            this.enregistrerMenuEdition_.Enabled = false;
            this.enregistrerMenuEdition_.Name = "enregistrerMenuEdition_";
            this.enregistrerMenuEdition_.ShortcutKeyDisplayString = "CTRL-S";
            this.enregistrerMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.enregistrerMenuEdition_.Text = "Enregistrer";
            this.enregistrerMenuEdition_.Click += new System.EventHandler(this.enregistrerMenuEdition__Click);
            // 
            // enregistrerSousMenuEdition_
            // 
            this.enregistrerSousMenuEdition_.Name = "enregistrerSousMenuEdition_";
            this.enregistrerSousMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.enregistrerSousMenuEdition_.Text = "Enregistrer Sous";
            this.enregistrerSousMenuEdition_.Click += new System.EventHandler(this.enregistrerSousMenuEdition__Click);
            // 
            // modeTestModeEdition_
            // 
            this.modeTestModeEdition_.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.modeTestModeEdition_.Name = "modeTestModeEdition_";
            this.modeTestModeEdition_.ShortcutKeyDisplayString = "T";
            this.modeTestModeEdition_.Size = new System.Drawing.Size(203, 22);
            this.modeTestModeEdition_.Text = "Mode test";
            this.modeTestModeEdition_.Click += new System.EventHandler(this.modeTestModeEdition__Click);
            // 
            // menuPrincipalMenuEdition
            // 
            this.menuPrincipalMenuEdition.Name = "menuPrincipalMenuEdition";
            this.menuPrincipalMenuEdition.ShortcutKeyDisplayString = "CTRL-Q";
            this.menuPrincipalMenuEdition.Size = new System.Drawing.Size(203, 22);
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
            this.supprimerToolStripMenuItem.Size = new System.Drawing.Size(129, 22);
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
            this.selectionMenuEdition_.ShortcutKeyDisplayString = "S";
            this.selectionMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.selectionMenuEdition_.Text = "Sélection";
            this.selectionMenuEdition_.Click += new System.EventHandler(this.sToolStripMenuItem_Click);
            // 
            // deplacementMenuEdition_
            // 
            this.deplacementMenuEdition_.Name = "deplacementMenuEdition_";
            this.deplacementMenuEdition_.ShortcutKeyDisplayString = "D";
            this.deplacementMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.deplacementMenuEdition_.Text = "Déplacement";
            this.deplacementMenuEdition_.Click += new System.EventHandler(this.déplacementToolStripMenuItem_Click);
            // 
            // rotationMenuEdition_
            // 
            this.rotationMenuEdition_.Name = "rotationMenuEdition_";
            this.rotationMenuEdition_.ShortcutKeyDisplayString = "R";
            this.rotationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.rotationMenuEdition_.Text = "Rotation";
            this.rotationMenuEdition_.Click += new System.EventHandler(this.rotationToolStripMenuItem_Click);
            // 
            // miseAEchelleMenuEdition_
            // 
            this.miseAEchelleMenuEdition_.Name = "miseAEchelleMenuEdition_";
            this.miseAEchelleMenuEdition_.ShortcutKeyDisplayString = "E";
            this.miseAEchelleMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.miseAEchelleMenuEdition_.Text = "Mise à échelle";
            this.miseAEchelleMenuEdition_.Click += new System.EventHandler(this.miseAEchelleToolStripMenuItem_Click);
            // 
            // duplicationMenuEdition_
            // 
            this.duplicationMenuEdition_.Name = "duplicationMenuEdition_";
            this.duplicationMenuEdition_.ShortcutKeyDisplayString = "C";
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
            this.poteauMenuEdition_.ShortcutKeyDisplayString = "P";
            this.poteauMenuEdition_.Size = new System.Drawing.Size(146, 22);
            this.poteauMenuEdition_.Text = "Poteau";
            this.poteauMenuEdition_.Click += new System.EventHandler(this.poteauToolStripMenuItem_Click);
            // 
            // murMenuEdition_
            // 
            this.murMenuEdition_.Name = "murMenuEdition_";
            this.murMenuEdition_.ShortcutKeyDisplayString = "M";
            this.murMenuEdition_.Size = new System.Drawing.Size(146, 22);
            this.murMenuEdition_.Text = "Mur";
            this.murMenuEdition_.Click += new System.EventHandler(this.murToolStripMenuItem_Click);
            // 
            // ligneNoireMenuEdition_
            // 
            this.ligneNoireMenuEdition_.Name = "ligneNoireMenuEdition_";
            this.ligneNoireMenuEdition_.ShortcutKeyDisplayString = "L";
            this.ligneNoireMenuEdition_.Size = new System.Drawing.Size(146, 22);
            this.ligneNoireMenuEdition_.Text = "Ligne noire";
            this.ligneNoireMenuEdition_.Click += new System.EventHandler(this.ligneNoireToolStripMenuItem_Click);
            // 
            // zoomToolStripMenuItem
            // 
            this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
            this.zoomToolStripMenuItem.ShortcutKeyDisplayString = "Z";
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.zoomToolStripMenuItem.Text = "Zoom";
            this.zoomToolStripMenuItem.Click += new System.EventHandler(this.zoomToolStripMenuItem_Click);
            // 
            // vuesMenuEdition_
            // 
            this.vuesMenuEdition_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueMenuEdition_,
            this.orbiteMenuEdition_});
            this.vuesMenuEdition_.Name = "vuesMenuEdition_";
            this.vuesMenuEdition_.ShortcutKeyDisplayString = "1";
            this.vuesMenuEdition_.Size = new System.Drawing.Size(44, 20);
            this.vuesMenuEdition_.Text = "Vues";
            // 
            // orthographiqueMenuEdition_
            // 
            this.orthographiqueMenuEdition_.Checked = true;
            this.orthographiqueMenuEdition_.CheckState = System.Windows.Forms.CheckState.Checked;
            this.orthographiqueMenuEdition_.Name = "orthographiqueMenuEdition_";
            this.orthographiqueMenuEdition_.ShortcutKeyDisplayString = "1";
            this.orthographiqueMenuEdition_.Size = new System.Drawing.Size(172, 22);
            this.orthographiqueMenuEdition_.Text = "Orthographique";
            this.orthographiqueMenuEdition_.Click += new System.EventHandler(this.orthographiqueMenuEdition__Click);
            // 
            // orbiteMenuEdition_
            // 
            this.orbiteMenuEdition_.Name = "orbiteMenuEdition_";
            this.orbiteMenuEdition_.ShortcutKeyDisplayString = "2";
            this.orbiteMenuEdition_.Size = new System.Drawing.Size(172, 22);
            this.orbiteMenuEdition_.Text = "Orbite";
            this.orbiteMenuEdition_.Click += new System.EventHandler(this.orbiteMenuEdition__Click);
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
            this.barreOutils_.AllowDrop = true;
            this.barreOutils_.AllowMerge = false;
            this.barreOutils_.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.barreOutils_.AutoSize = false;
            this.barreOutils_.BackColor = System.Drawing.Color.Gray;
            this.barreOutils_.Dock = System.Windows.Forms.DockStyle.None;
            this.barreOutils_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.outilsSelection_,
            this.outilsDeplacement_,
            this.outilsRotation_,
            this.outilsMiseAEchelle_,
            this.outilsDuplication_,
            this.outilsZoom_,
            this.outilsCreationPoteau_,
            this.outilsCreationMurs_,
            this.outilsCreationLigne_});
            this.barreOutils_.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Flow;
            this.barreOutils_.Location = new System.Drawing.Point(201, 427);
            this.barreOutils_.Name = "barreOutils_";
            this.barreOutils_.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.barreOutils_.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.barreOutils_.Size = new System.Drawing.Size(219, 25);
            this.barreOutils_.Stretch = true;
            this.barreOutils_.TabIndex = 7;
            this.barreOutils_.Text = "toolStrip1";
            this.barreOutils_.Visible = false;
            // 
            // outilsSelection_
            // 
            this.outilsSelection_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsSelection_.Image = global::ui.Properties.Resources.ic_near_me_white_48dp_2x;
            this.outilsSelection_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsSelection_.Name = "outilsSelection_";
            this.outilsSelection_.Size = new System.Drawing.Size(23, 20);
            this.outilsSelection_.Text = "Sélection";
            this.outilsSelection_.Click += new System.EventHandler(this.outilsSelection__Click);
            // 
            // outilsDeplacement_
            // 
            this.outilsDeplacement_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsDeplacement_.Image = global::ui.Properties.Resources.ic_open_with;
            this.outilsDeplacement_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsDeplacement_.Name = "outilsDeplacement_";
            this.outilsDeplacement_.Size = new System.Drawing.Size(23, 20);
            this.outilsDeplacement_.Text = "Déplacement";
            this.outilsDeplacement_.Click += new System.EventHandler(this.outilsDéplacement__Click);
            // 
            // outilsRotation_
            // 
            this.outilsRotation_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsRotation_.Image = global::ui.Properties.Resources.ic_loop_white_48dp_2x;
            this.outilsRotation_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsRotation_.Name = "outilsRotation_";
            this.outilsRotation_.Size = new System.Drawing.Size(23, 20);
            this.outilsRotation_.Text = "Rotation";
            this.outilsRotation_.Click += new System.EventHandler(this.outilsRotation__Click);
            // 
            // outilsMiseAEchelle_
            // 
            this.outilsMiseAEchelle_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsMiseAEchelle_.Image = global::ui.Properties.Resources.ic_settings_overscan_white_48dp_2x;
            this.outilsMiseAEchelle_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsMiseAEchelle_.Name = "outilsMiseAEchelle_";
            this.outilsMiseAEchelle_.Size = new System.Drawing.Size(23, 20);
            this.outilsMiseAEchelle_.Text = "Mise à échelle";
            this.outilsMiseAEchelle_.Click += new System.EventHandler(this.outilsMiseAEchelle__Click);
            // 
            // outilsDuplication_
            // 
            this.outilsDuplication_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsDuplication_.Image = global::ui.Properties.Resources.editcopy;
            this.outilsDuplication_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsDuplication_.Name = "outilsDuplication_";
            this.outilsDuplication_.Size = new System.Drawing.Size(23, 20);
            this.outilsDuplication_.Text = "Duplication";
            this.outilsDuplication_.Click += new System.EventHandler(this.outilsDuplication__Click);
            // 
            // outilsZoom_
            // 
            this.outilsZoom_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsZoom_.Image = global::ui.Properties.Resources.ic_search_white_48dp_2x;
            this.outilsZoom_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsZoom_.Name = "outilsZoom_";
            this.outilsZoom_.Size = new System.Drawing.Size(23, 20);
            this.outilsZoom_.Text = "Zoom";
            this.outilsZoom_.Click += new System.EventHandler(this.outilsZoom__Click);
            // 
            // outilsCreationPoteau_
            // 
            this.outilsCreationPoteau_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationPoteau_.Image = global::ui.Properties.Resources.law2;
            this.outilsCreationPoteau_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationPoteau_.Name = "outilsCreationPoteau_";
            this.outilsCreationPoteau_.Size = new System.Drawing.Size(23, 20);
            this.outilsCreationPoteau_.Text = "Création de poteaux";
            this.outilsCreationPoteau_.Click += new System.EventHandler(this.outilsCreationPoteau__Click);
            // 
            // outilsCreationMurs_
            // 
            this.outilsCreationMurs_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationMurs_.Image = global::ui.Properties.Resources.walls1;
            this.outilsCreationMurs_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationMurs_.Name = "outilsCreationMurs_";
            this.outilsCreationMurs_.Size = new System.Drawing.Size(23, 20);
            this.outilsCreationMurs_.Text = "Céreation de murs";
            this.outilsCreationMurs_.Click += new System.EventHandler(this.outilsCreationMurs__Click);
            // 
            // outilsCreationLigne_
            // 
            this.outilsCreationLigne_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.outilsCreationLigne_.Image = global::ui.Properties.Resources.line2;
            this.outilsCreationLigne_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.outilsCreationLigne_.Name = "outilsCreationLigne_";
            this.outilsCreationLigne_.Size = new System.Drawing.Size(23, 20);
            this.outilsCreationLigne_.Text = "Création de lignes";
            this.outilsCreationLigne_.Click += new System.EventHandler(this.outilsCreationLigne__Click);
            // 
            // panneauOperation_
            // 
            this.panneauOperation_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panneauOperation_.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.panneauOperation_.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
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
            this.panneauOperation_.Visible = false;
            // 
            // textBoxPositionY_
            // 
            this.textBoxPositionY_.Location = new System.Drawing.Point(18, 190);
            this.textBoxPositionY_.Name = "textBoxPositionY_";
            this.textBoxPositionY_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionY_.TabIndex = 7;
            this.textBoxPositionY_.TabStop = false;
            this.textBoxPositionY_.Enter += new System.EventHandler(this.textBoxPositionY__Enter);
            this.textBoxPositionY_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionY__KeyDown);
            this.textBoxPositionY_.Leave += new System.EventHandler(this.textBoxPositionY__Leave);
            // 
            // textBoxPositionX_
            // 
            this.textBoxPositionX_.Location = new System.Drawing.Point(18, 132);
            this.textBoxPositionX_.Name = "textBoxPositionX_";
            this.textBoxPositionX_.Size = new System.Drawing.Size(84, 20);
            this.textBoxPositionX_.TabIndex = 6;
            this.textBoxPositionX_.TabStop = false;
            this.textBoxPositionX_.Enter += new System.EventHandler(this.textBoxPositionX__Enter);
            this.textBoxPositionX_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPositionX__KeyDown);
            this.textBoxPositionX_.Leave += new System.EventHandler(this.textBoxPositionX__Leave);
            // 
            // textBoxRotation_
            // 
            this.textBoxRotation_.Location = new System.Drawing.Point(18, 81);
            this.textBoxRotation_.Name = "textBoxRotation_";
            this.textBoxRotation_.Size = new System.Drawing.Size(84, 20);
            this.textBoxRotation_.TabIndex = 5;
            this.textBoxRotation_.TabStop = false;
            this.textBoxRotation_.Enter += new System.EventHandler(this.textBoxRotation__Enter);
            this.textBoxRotation_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxRotation__KeyDown);
            this.textBoxRotation_.Leave += new System.EventHandler(this.textBoxRotation__Leave);
            // 
            // textboxDimension_
            // 
            this.textboxDimension_.Location = new System.Drawing.Point(18, 30);
            this.textboxDimension_.Name = "textboxDimension_";
            this.textboxDimension_.Size = new System.Drawing.Size(84, 20);
            this.textboxDimension_.TabIndex = 4;
            this.textboxDimension_.TabStop = false;
            this.textboxDimension_.Enter += new System.EventHandler(this.textboxDimension__Enter);
            this.textboxDimension_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textboxDimension__KeyDown);
            this.textboxDimension_.Leave += new System.EventHandler(this.textboxDimension__Leave);
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
            // menuSimTest
            // 
            this.menuSimTest.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierMenuSimTest,
            this.vuesMenuSimTest,
            this.profilsMenuSimTest});
            this.menuSimTest.Location = new System.Drawing.Point(0, 0);
            this.menuSimTest.Name = "menuSimTest";
            this.menuSimTest.Size = new System.Drawing.Size(623, 24);
            this.menuSimTest.TabIndex = 9;
            this.menuSimTest.Text = "menuStrip1";
            this.menuSimTest.Visible = false;
            this.menuSimTest.VisibleChanged += new System.EventHandler(this.menuSimTest_VisibleChanged);
            // 
            // fichierMenuSimTest
            // 
            this.fichierMenuSimTest.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPrincipalMenuSimTest,
            this.modeEditionMenuSimTest});
            this.fichierMenuSimTest.Name = "fichierMenuSimTest";
            this.fichierMenuSimTest.ShortcutKeyDisplayString = "CTRL-Q";
            this.fichierMenuSimTest.Size = new System.Drawing.Size(54, 20);
            this.fichierMenuSimTest.Text = "Fichier";
            // 
            // menuPrincipalMenuSimTest
            // 
            this.menuPrincipalMenuSimTest.Name = "menuPrincipalMenuSimTest";
            this.menuPrincipalMenuSimTest.ShortcutKeyDisplayString = "CTRL-Q";
            this.menuPrincipalMenuSimTest.Size = new System.Drawing.Size(206, 22);
            this.menuPrincipalMenuSimTest.Text = "Menu principal ";
            this.menuPrincipalMenuSimTest.Click += new System.EventHandler(this.menuPrincipalMenuSimTest_Click);
            // 
            // modeEditionMenuSimTest
            // 
            this.modeEditionMenuSimTest.Name = "modeEditionMenuSimTest";
            this.modeEditionMenuSimTest.ShortcutKeyDisplayString = "CTRL-E";
            this.modeEditionMenuSimTest.Size = new System.Drawing.Size(206, 22);
            this.modeEditionMenuSimTest.Text = "Mode Édition ";
            this.modeEditionMenuSimTest.Click += new System.EventHandler(this.modeEditionMenuSimTest_Click);
            // 
            // vuesMenuSimTest
            // 
            this.vuesMenuSimTest.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueMenuSimTest,
            this.orbiteMenuSimTest,
            this.premierePersonneMenuSimTest});
            this.vuesMenuSimTest.Name = "vuesMenuSimTest";
            this.vuesMenuSimTest.ShortcutKeyDisplayString = "1";
            this.vuesMenuSimTest.Size = new System.Drawing.Size(44, 20);
            this.vuesMenuSimTest.Text = "Vues";
            // 
            // orthographiqueMenuSimTest
            // 
            this.orthographiqueMenuSimTest.Checked = true;
            this.orthographiqueMenuSimTest.CheckState = System.Windows.Forms.CheckState.Checked;
            this.orthographiqueMenuSimTest.Name = "orthographiqueMenuSimTest";
            this.orthographiqueMenuSimTest.ShortcutKeyDisplayString = "1";
            this.orthographiqueMenuSimTest.Size = new System.Drawing.Size(186, 22);
            this.orthographiqueMenuSimTest.Text = "Orthographique";
            this.orthographiqueMenuSimTest.Click += new System.EventHandler(this.orthographiqueMenuSimTest_Click);
            // 
            // orbiteMenuSimTest
            // 
            this.orbiteMenuSimTest.Name = "orbiteMenuSimTest";
            this.orbiteMenuSimTest.ShortcutKeyDisplayString = "2";
            this.orbiteMenuSimTest.Size = new System.Drawing.Size(186, 22);
            this.orbiteMenuSimTest.Text = "Orbite";
            this.orbiteMenuSimTest.Click += new System.EventHandler(this.orbiteMenuSimTest_Click);
            // 
            // premierePersonneMenuSimTest
            // 
            this.premierePersonneMenuSimTest.Name = "premierePersonneMenuSimTest";
            this.premierePersonneMenuSimTest.ShortcutKeyDisplayString = "3";
            this.premierePersonneMenuSimTest.Size = new System.Drawing.Size(186, 22);
            this.premierePersonneMenuSimTest.Text = "Première personne";
            this.premierePersonneMenuSimTest.Click += new System.EventHandler(this.premierePersonneMenuSimTest_Click);
            // 
            // profilsMenuSimTest
            // 
            this.profilsMenuSimTest.Name = "profilsMenuSimTest";
            this.profilsMenuSimTest.Size = new System.Drawing.Size(52, 20);
            this.profilsMenuSimTest.Text = "Profils";
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 462);
            this.Controls.Add(this.panneauOperation_);
            this.Controls.Add(this.barreOutils_);
            this.Controls.Add(this.menuEdition_);
            this.Controls.Add(this.menuSimTest);
            this.Controls.Add(this.bouttonSimulation_);
            this.Controls.Add(this.bouttonQuitter_);
            this.Controls.Add(this.bouttonEditeur_);
            this.Controls.Add(this.bouttonConfiguration_);
            this.Controls.Add(this.viewPort);
            this.MainMenuStrip = this.menuSimTest;
            this.MinimumSize = new System.Drawing.Size(500, 500);
            this.Name = "Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.Load += new System.EventHandler(this.Window_Load);
            this.Resize += new System.EventHandler(this.Window_Resize);
            this.viewPort.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).EndInit();
            this.menuEdition_.ResumeLayout(false);
            this.menuEdition_.PerformLayout();
            this.barreOutils_.ResumeLayout(false);
            this.barreOutils_.PerformLayout();
            this.panneauOperation_.ResumeLayout(false);
            this.panneauOperation_.PerformLayout();
            this.menuSimTest.ResumeLayout(false);
            this.menuSimTest.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion


        public System.Windows.Forms.Panel viewPort;
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
        private System.Windows.Forms.ToolStripButton outilsDeplacement_;
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
        private System.Windows.Forms.MenuStrip menuSimTest;
        private System.Windows.Forms.ToolStripMenuItem fichierMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem modeEditionMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem vuesMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem orbiteMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem premierePersonneMenuSimTest;
        private System.Windows.Forms.ToolStripMenuItem profilsMenuSimTest;
        private System.Windows.Forms.PictureBox picturePause;
    }
}

