namespace InterfaceGraphique
{
    partial class ExplorateurSauvegarde
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ExplorateurSauvegarde));
            this.folderImageList = new System.Windows.Forms.ImageList(this.components);
            this.folderTreeView = new System.Windows.Forms.TreeView();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.listView1 = new System.Windows.Forms.ListView();
            this.nomCol = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.typeCol = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.dateCol = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.nouveauButt = new System.Windows.Forms.Button();
            this.annulerButt = new System.Windows.Forms.Button();
            this.enregistrerButt = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // folderImageList
            // 
            this.folderImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("folderImageList.ImageStream")));
            this.folderImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.folderImageList.Images.SetKeyName(0, "ic_folder_black_24dp_2x.png");
            this.folderImageList.Images.SetKeyName(1, "ic_description_black_24dp_2x.png");
            this.folderImageList.Images.SetKeyName(2, "ic_folder_open_black_24dp_2x.png");
            this.folderImageList.Images.SetKeyName(3, "ic_create_new_folder_black_24dp_2x.png");
            this.folderImageList.Images.SetKeyName(4, "ic_save_black_24dp_2x.png");
            // 
            // folderTreeView
            // 
            this.folderTreeView.CausesValidation = false;
            this.folderTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.folderTreeView.ImageIndex = 0;
            this.folderTreeView.ImageList = this.folderImageList;
            this.folderTreeView.Location = new System.Drawing.Point(0, 0);
            this.folderTreeView.Name = "folderTreeView";
            this.folderTreeView.SelectedImageIndex = 2;
            this.folderTreeView.ShowRootLines = false;
            this.folderTreeView.Size = new System.Drawing.Size(196, 451);
            this.folderTreeView.TabIndex = 0;
            this.folderTreeView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.folderTreeView_NodeMouseClick);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.folderTreeView);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(593, 451);
            this.splitContainer1.SplitterDistance = 196;
            this.splitContainer1.TabIndex = 1;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.listView1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.nouveauButt);
            this.splitContainer2.Panel2.Controls.Add(this.annulerButt);
            this.splitContainer2.Panel2.Controls.Add(this.enregistrerButt);
            this.splitContainer2.Size = new System.Drawing.Size(393, 451);
            this.splitContainer2.SplitterDistance = 394;
            this.splitContainer2.TabIndex = 0;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.nomCol,
            this.typeCol,
            this.dateCol});
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(393, 394);
            this.listView1.SmallImageList = this.folderImageList;
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseDoubleClick);
            // 
            // nomCol
            // 
            this.nomCol.Text = "Nom";
            this.nomCol.Width = 138;
            // 
            // typeCol
            // 
            this.typeCol.Text = "Type";
            this.typeCol.Width = 128;
            // 
            // dateCol
            // 
            this.dateCol.Text = "Dernière modification";
            this.dateCol.Width = 269;
            // 
            // nouveauButt
            // 
            this.nouveauButt.Location = new System.Drawing.Point(164, 18);
            this.nouveauButt.Name = "nouveauButt";
            this.nouveauButt.Size = new System.Drawing.Size(75, 23);
            this.nouveauButt.TabIndex = 2;
            this.nouveauButt.Text = "Nouveau";
            this.nouveauButt.UseVisualStyleBackColor = true;
            this.nouveauButt.Click += new System.EventHandler(this.nouveauButt_Click);
            // 
            // annulerButt
            // 
            this.annulerButt.Location = new System.Drawing.Point(284, 18);
            this.annulerButt.Name = "annulerButt";
            this.annulerButt.Size = new System.Drawing.Size(75, 23);
            this.annulerButt.TabIndex = 1;
            this.annulerButt.Text = "Annuler";
            this.annulerButt.UseVisualStyleBackColor = true;
            this.annulerButt.Click += new System.EventHandler(this.annulerButt_Click);
            // 
            // enregistrerButt
            // 
            this.enregistrerButt.Location = new System.Drawing.Point(44, 18);
            this.enregistrerButt.Name = "enregistrerButt";
            this.enregistrerButt.Size = new System.Drawing.Size(75, 23);
            this.enregistrerButt.TabIndex = 0;
            this.enregistrerButt.Text = "Enregistrer";
            this.enregistrerButt.UseVisualStyleBackColor = true;
            this.enregistrerButt.Click += new System.EventHandler(this.enregistrerButt_Click);
            // 
            // ExplorateurSauvegarde
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(593, 451);
            this.Controls.Add(this.splitContainer1);
            this.Name = "ExplorateurSauvegarde";
            this.Text = "Sauvegarder une zone";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ImageList folderImageList;
        private System.Windows.Forms.TreeView folderTreeView;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Button annulerButt;
        private System.Windows.Forms.Button enregistrerButt;
        private System.Windows.Forms.ColumnHeader nomCol;
        private System.Windows.Forms.ColumnHeader typeCol;
        private System.Windows.Forms.ColumnHeader dateCol;
        private System.Windows.Forms.Button nouveauButt;
    }
}