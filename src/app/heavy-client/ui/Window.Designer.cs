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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Window));
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
            this.viewPort = new System.Windows.Forms.Panel();
            this.picturePause = new System.Windows.Forms.PictureBox();
            this.mainScreen = new System.Windows.Forms.Panel();
            this.menuEdition_.SuspendLayout();
            this.panneauOperation_.SuspendLayout();
            this.menuSimTest.SuspendLayout();
            this.viewPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).BeginInit();
            this.mainScreen.SuspendLayout();
            this.SuspendLayout();
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
            this.menuEdition_.Size = new System.Drawing.Size(749, 24);
            this.menuEdition_.TabIndex = 5;
            this.menuEdition_.Text = "menuStrip1";
            this.menuEdition_.Visible = false;
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
            // 
            // ouvrirMenuEdition_
            // 
            this.ouvrirMenuEdition_.Name = "ouvrirMenuEdition_";
            this.ouvrirMenuEdition_.ShortcutKeyDisplayString = "CTRL-O";
            this.ouvrirMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.ouvrirMenuEdition_.Text = "Ouvrir";
            // 
            // enregistrerMenuEdition_
            // 
            this.enregistrerMenuEdition_.Enabled = false;
            this.enregistrerMenuEdition_.Name = "enregistrerMenuEdition_";
            this.enregistrerMenuEdition_.ShortcutKeyDisplayString = "CTRL-S";
            this.enregistrerMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.enregistrerMenuEdition_.Text = "Enregistrer";
            // 
            // enregistrerSousMenuEdition_
            // 
            this.enregistrerSousMenuEdition_.Name = "enregistrerSousMenuEdition_";
            this.enregistrerSousMenuEdition_.Size = new System.Drawing.Size(203, 22);
            this.enregistrerSousMenuEdition_.Text = "Enregistrer Sous";
            // 
            // modeTestModeEdition_
            // 
            this.modeTestModeEdition_.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.modeTestModeEdition_.Name = "modeTestModeEdition_";
            this.modeTestModeEdition_.ShortcutKeyDisplayString = "T";
            this.modeTestModeEdition_.Size = new System.Drawing.Size(203, 22);
            this.modeTestModeEdition_.Text = "Mode test";
            // 
            // menuPrincipalMenuEdition
            // 
            this.menuPrincipalMenuEdition.Name = "menuPrincipalMenuEdition";
            this.menuPrincipalMenuEdition.ShortcutKeyDisplayString = "CTRL-Q";
            this.menuPrincipalMenuEdition.Size = new System.Drawing.Size(203, 22);
            this.menuPrincipalMenuEdition.Text = "Menu Principal";
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
            // 
            // deplacementMenuEdition_
            // 
            this.deplacementMenuEdition_.Name = "deplacementMenuEdition_";
            this.deplacementMenuEdition_.ShortcutKeyDisplayString = "D";
            this.deplacementMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.deplacementMenuEdition_.Text = "Déplacement";
            // 
            // rotationMenuEdition_
            // 
            this.rotationMenuEdition_.Name = "rotationMenuEdition_";
            this.rotationMenuEdition_.ShortcutKeyDisplayString = "R";
            this.rotationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.rotationMenuEdition_.Text = "Rotation";
            // 
            // miseAEchelleMenuEdition_
            // 
            this.miseAEchelleMenuEdition_.Name = "miseAEchelleMenuEdition_";
            this.miseAEchelleMenuEdition_.ShortcutKeyDisplayString = "E";
            this.miseAEchelleMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.miseAEchelleMenuEdition_.Text = "Mise à échelle";
            // 
            // duplicationMenuEdition_
            // 
            this.duplicationMenuEdition_.Name = "duplicationMenuEdition_";
            this.duplicationMenuEdition_.ShortcutKeyDisplayString = "C";
            this.duplicationMenuEdition_.Size = new System.Drawing.Size(164, 22);
            this.duplicationMenuEdition_.Text = "Duplication";
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
            // 
            // murMenuEdition_
            // 
            this.murMenuEdition_.Name = "murMenuEdition_";
            this.murMenuEdition_.ShortcutKeyDisplayString = "M";
            this.murMenuEdition_.Size = new System.Drawing.Size(146, 22);
            this.murMenuEdition_.Text = "Mur";
            // 
            // ligneNoireMenuEdition_
            // 
            this.ligneNoireMenuEdition_.Name = "ligneNoireMenuEdition_";
            this.ligneNoireMenuEdition_.ShortcutKeyDisplayString = "L";
            this.ligneNoireMenuEdition_.Size = new System.Drawing.Size(146, 22);
            this.ligneNoireMenuEdition_.Text = "Ligne noire";
            // 
            // zoomToolStripMenuItem
            // 
            this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
            this.zoomToolStripMenuItem.ShortcutKeyDisplayString = "Z";
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.zoomToolStripMenuItem.Text = "Zoom";
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
            // 
            // orbiteMenuEdition_
            // 
            this.orbiteMenuEdition_.Name = "orbiteMenuEdition_";
            this.orbiteMenuEdition_.ShortcutKeyDisplayString = "2";
            this.orbiteMenuEdition_.Size = new System.Drawing.Size(172, 22);
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
            this.panneauOperation_.Location = new System.Drawing.Point(621, 27);
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
            this.menuSimTest.Size = new System.Drawing.Size(749, 24);
            this.menuSimTest.TabIndex = 9;
            this.menuSimTest.Text = "menuStrip1";
            this.menuSimTest.Visible = false;
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
            // 
            // modeEditionMenuSimTest
            // 
            this.modeEditionMenuSimTest.Name = "modeEditionMenuSimTest";
            this.modeEditionMenuSimTest.ShortcutKeyDisplayString = "CTRL-E";
            this.modeEditionMenuSimTest.Size = new System.Drawing.Size(206, 22);
            this.modeEditionMenuSimTest.Text = "Mode Édition ";
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
            // 
            // orbiteMenuSimTest
            // 
            this.orbiteMenuSimTest.Name = "orbiteMenuSimTest";
            this.orbiteMenuSimTest.ShortcutKeyDisplayString = "2";
            this.orbiteMenuSimTest.Size = new System.Drawing.Size(186, 22);
            this.orbiteMenuSimTest.Text = "Orbite";
            // 
            // premierePersonneMenuSimTest
            // 
            this.premierePersonneMenuSimTest.Name = "premierePersonneMenuSimTest";
            this.premierePersonneMenuSimTest.ShortcutKeyDisplayString = "3";
            this.premierePersonneMenuSimTest.Size = new System.Drawing.Size(186, 22);
            this.premierePersonneMenuSimTest.Text = "Première personne";
            // 
            // profilsMenuSimTest
            // 
            this.profilsMenuSimTest.Name = "profilsMenuSimTest";
            this.profilsMenuSimTest.Size = new System.Drawing.Size(52, 20);
            this.profilsMenuSimTest.Text = "Profils";
            // 
            // viewPort
            // 
            this.viewPort.AutoSize = true;
            this.viewPort.Controls.Add(this.picturePause);
            this.viewPort.Dock = System.Windows.Forms.DockStyle.Fill;
            this.viewPort.Location = new System.Drawing.Point(0, 0);
            this.viewPort.MinimumSize = new System.Drawing.Size(100, 100);
            this.viewPort.Name = "viewPort";
            this.viewPort.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.viewPort.Size = new System.Drawing.Size(749, 536);
            this.viewPort.TabIndex = 0;
            this.viewPort.Visible = false;
            this.viewPort.MouseMove += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseMove);
            this.viewPort.MouseUp += new System.Windows.Forms.MouseEventHandler(this.viewPort__MouseUp);
            this.viewPort.Resize += new System.EventHandler(this.viewPort_Resize);
            // 
            // picturePause
            // 
            this.picturePause.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picturePause.Image = ((System.Drawing.Image)(resources.GetObject("picturePause.Image")));
            this.picturePause.Location = new System.Drawing.Point(330, 208);
            this.picturePause.Name = "picturePause";
            this.picturePause.Size = new System.Drawing.Size(96, 96);
            this.picturePause.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.picturePause.TabIndex = 0;
            this.picturePause.TabStop = false;
            this.picturePause.Visible = false;
            // 
            // mainScreen
            // 
            this.mainScreen.Controls.Add(this.viewPort);
            this.mainScreen.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainScreen.Location = new System.Drawing.Point(0, 0);
            this.mainScreen.Name = "mainScreen";
            this.mainScreen.Size = new System.Drawing.Size(749, 536);
            this.mainScreen.TabIndex = 10;
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(749, 536);
            this.Controls.Add(this.panneauOperation_);
            this.Controls.Add(this.menuSimTest);
            this.Controls.Add(this.menuEdition_);
            this.Controls.Add(this.mainScreen);
            this.MainMenuStrip = this.menuSimTest;
            this.MinimumSize = new System.Drawing.Size(765, 575);
            this.Name = "Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulateur de robot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Window_FormClosing);
            this.menuEdition_.ResumeLayout(false);
            this.menuEdition_.PerformLayout();
            this.panneauOperation_.ResumeLayout(false);
            this.panneauOperation_.PerformLayout();
            this.menuSimTest.ResumeLayout(false);
            this.menuSimTest.PerformLayout();
            this.viewPort.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picturePause)).EndInit();
            this.mainScreen.ResumeLayout(false);
            this.mainScreen.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
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
        public System.Windows.Forms.Panel viewPort;
        public System.Windows.Forms.PictureBox picturePause;
        public System.Windows.Forms.Panel mainScreen;
    }
}

