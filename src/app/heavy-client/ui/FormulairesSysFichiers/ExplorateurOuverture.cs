﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace ui
{

    public partial class ExplorateurOuverture : Form
    {
        /// <summary>
        /// Chemin vers le fichier que l'utilisateur a sélectionné
        /// </summary>
        public String cheminFichier;

        /// <summary>
        /// Chemin vers le fichier contenant la zone par defaut
        /// </summary>
        private String cheminFichierZoneDefaut;

        /// <summary>
        /// Chemin vers le dossier contenant les fichiers de zones
        /// </summary>
        private String cheminDossierZone;

        /// <summary>
        /// Nom du fichier contenant la zone par defaut
        /// </summary>
        private String nomFichierZoneDefaut;

        /// <summary>
        /// Extension d'un fichier de type zone
        /// </summary>
        private String extensionFichierZone;

        bool afficherZoneDefaut = false;

        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ExplorateurOuverture()
        ///
        /// Constructeur par défaut
        /// Initialise les composantes du formulaires et popule l'arbre de dossiers.
        ///
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public ExplorateurOuverture(Window parent)
        {
            parent_ = parent;

            StringBuilder str = new StringBuilder(100);
            FonctionsNatives.obtenirCheminFichierZoneDefaut(str, str.Capacity);
            cheminFichierZoneDefaut = str.ToString();
            cheminDossierZone = cheminFichierZoneDefaut.Substring(0, cheminFichierZoneDefaut.LastIndexOf("/") + 1);
            nomFichierZoneDefaut = cheminFichierZoneDefaut.Substring(cheminFichierZoneDefaut.LastIndexOf("/") + 1);
            extensionFichierZone = cheminFichierZoneDefaut.Substring(cheminFichierZoneDefaut.LastIndexOf("."));
            InitializeComponent();
            afficherZoneDefaut = true;
            PopulateTreeView();

            parent_.mapMenu.offlineMaps_.Clear();
            populateLocalMapList();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PopulateTreeView()
        ///
        /// Popule l'arbre de dossiers contenu par le dossier Zones.
        ///
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PopulateTreeView()
        {
            TreeNode rootNode;

            DirectoryInfo info = new DirectoryInfo(@cheminDossierZone);
            if (info.Exists)
            {
                rootNode = new TreeNode(info.Name);
                rootNode.Tag = info;
                GetDirectories(info.GetDirectories(), rootNode);
                folderTreeView.Nodes.Add(rootNode);
                ouvreDossier(rootNode);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void GetDirectories(DirectoryInfo[] subDirs, TreeNode nodeToAddTo)
        ///
        /// Ajoute chaque dossier contenu dans le dossier Zones à l'arbre de dossiers.
        ///
        /// @param[in] subDirs : Tableau contenant les sous dossiers du dossier racine.
        /// @param[in] noteToAddTo : Parent du dossier que l'on veut ajouter à la liste
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void GetDirectories(DirectoryInfo[] subDirs, TreeNode nodeToAddTo)
        {
            TreeNode aNode = null;
            DirectoryInfo[] subSubDirs;
            foreach (DirectoryInfo subDir in subDirs)
            {
                aNode = new TreeNode(subDir.Name, 0, 0);
                aNode.Tag = subDir;
                aNode.ImageKey = "folder";
                subSubDirs = subDir.GetDirectories();
                if (subSubDirs.Length != 0)
                {
                    GetDirectories(subSubDirs, aNode);
                }
                nodeToAddTo.Nodes.Add(aNode);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void folderTreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        ///
        /// Fonction appelée lorsque l'évènement de double click sur un noeud de l'arbre est déclenché.
        ///
        /// @param[in] senders : Objet ayant déclenché l'évenement
        /// @param[in] e : Paramèetre en lien avec l'évènement
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        void folderTreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            ouvreDossier(e.Node);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvreDossier(TreeNode newSelected)
        ///
        /// Fonction servant à populer la liste de fichiers et sous-dossiers contenu par un dossier de l'arbre de dossiers.
        ///
        /// @param[in] newSelected : Noeud de l'arbre de dossiers sélectionné
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvreDossier(TreeNode newSelected)
        {
            listView1.Items.Clear();
            DirectoryInfo nodeDirInfo = (DirectoryInfo)newSelected.Tag;
            ListViewItem.ListViewSubItem[] subItems;
            ListViewItem item = null;

            foreach (DirectoryInfo dir in nodeDirInfo.GetDirectories())
            {
                item = new ListViewItem(dir.Name, 0);
                subItems = new ListViewItem.ListViewSubItem[]
                  {new ListViewItem.ListViewSubItem(item, "Directory"), 
                   new ListViewItem.ListViewSubItem(item, 
				dir.LastAccessTime.ToShortDateString())};
                item.SubItems.AddRange(subItems);
                listView1.Items.Add(item);
            }
            foreach (FileInfo file in nodeDirInfo.GetFiles("*" + extensionFichierZone))
            {

                if (file.Length > 0 && (file.Name != nomFichierZoneDefaut || afficherZoneDefaut))
                {
                    item = new ListViewItem(file.Name, 1);
                    subItems = new ListViewItem.ListViewSubItem[] { 
                        new ListViewItem.ListViewSubItem(item, "Fichier zone"), 
                        new ListViewItem.ListViewSubItem(item, 
				        file.LastAccessTime.ToShortDateString())};
                        item.Tag = file;
                        item.SubItems.AddRange(subItems);
                        listView1.Items.Add(item);
                    }
            }

            listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirButt_Click(object sender, EventArgs e)
        ///
        /// Fonction appelée lorsque l'évènement de click du bouton "Ouvrir" est déclenché.
        /// Celle-ci assigne le chemin du fichier sélectionné par l'utilisateur à la variable cheminFichier.
        ///
        /// @param[in] senders : Objet ayant déclenché l'évenement
        /// @param[in] e : Paramèetre en lien avec l'évènement
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirButt_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count > 0)
            {
                DialogResult = DialogResult.OK;
                cheminFichier = ((FileInfo)listView1.SelectedItems[0].Tag).FullName;
            }
            else
                DialogResult = DialogResult.Cancel;

            Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void annulerButt_Click(object sender, EventArgs e)
        ///
        /// Fonction appelée lorsque l'évènement de click du bouton "Annuler" est déclenché.
        /// Celle-ci ferme le formulaire.
        ///
        /// @param[in] senders : Objet ayant déclenché l'évenement
        /// @param[in] e : Paramèetre en lien avec l'évènement
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void annulerButt_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (listView1.SelectedItems.Count > 0)
            {
                DialogResult = DialogResult.OK;
                cheminFichier = ((FileInfo)listView1.SelectedItems[0].Tag).FullName;
                Close();
            }
        }

        private string getPath(string mapName)
        {
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                string text = listView1.Items[i].Text;
                text = text.Replace(extensionFichierZone, "");

                if (mapName == text)
                {
                     return cheminFichier = ((FileInfo)listView1.Items[i].Tag).FullName;
                }
            }
            return "";
        }

        public void populateLocalMapList()
        {
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                string text = listView1.Items[i].Text;
                text = text.Replace(extensionFichierZone, "");

                if (!parent_.mapMenu.offlineMaps_.ContainsKey(text))
                {
                    MapPresentator newMap = new MapPresentator(parent_, text, false, -1, 0, -1, false, false);
                    newMap.setPath(((FileInfo)listView1.Items[i].Tag).FullName);
                    parent_.mapMenu.addOfflineMapEntry(text, newMap);
                }
            }
        }

        static partial class FonctionsNatives
        {
            [System.Runtime.InteropServices.DllImport(@"model.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
            public static extern void obtenirCheminFichierZoneDefaut(StringBuilder str, int longueur);
        }
    }
}
