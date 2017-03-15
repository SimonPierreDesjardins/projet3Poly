﻿////////////////////////////////////////////////
/// @file   MapMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace ui
{
    public partial class MapMenu : UserControl
    {
        Window parent_;
        MapPresentator selectedMap_;
        int numberOfMaps_ = 0;

        public Dictionary<string, MapPresentator> offlineMaps_ = new Dictionary<string, MapPresentator>();
        public Dictionary<int, MapPresentator> onlineMaps_ = new Dictionary<int, MapPresentator>();

        private string cheminFichierZoneDefaut;
        private string cheminDossierZone;
        private string nomFichierZoneDefaut;
        private string extensionFichierZone;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MapMenu(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public MapMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            StringBuilder str = new StringBuilder(100);
            FonctionsNatives.obtenirCheminFichierZoneDefaut(str, str.Capacity);
            cheminFichierZoneDefaut = str.ToString();
            cheminDossierZone = cheminFichierZoneDefaut.Substring(0, cheminFichierZoneDefaut.LastIndexOf("/") + 1);
            nomFichierZoneDefaut = cheminFichierZoneDefaut.Substring(cheminFichierZoneDefaut.LastIndexOf("/") + 1);
            extensionFichierZone = cheminFichierZoneDefaut.Substring(cheminFichierZoneDefaut.LastIndexOf("."));

            fileDirLabel.Text = "";
        }

        public void addOnlineMapEntry(int mapId, MapPresentator newMap)
        { 
            if (!onlineMaps_.ContainsKey(mapId))
            {
                newMap.Size = new Size(this.mapPanel.Width, newMap.Height);
                newMap.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
                newMap.Location = new Point(0, numberOfMaps_++ * 150);
                onlineMaps_.Add(mapId, newMap);
                //this.mapPanel.Controls.Add(newMap);

                parent_.Invoke((MethodInvoker)delegate {
                    this.mapPanel.Controls.Add(newMap);
                });
            }
        }
        
        public void addOfflineMapEntry(string name, MapPresentator newMap)
        {
            if (!offlineMaps_.ContainsKey(name))
            {
                newMap.Size = new Size(this.mapPanel.Width, newMap.Height);
                newMap.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
                newMap.Location = new Point(0, numberOfMaps_++ * 150);
                offlineMaps_.Add(name, newMap);
                this.mapPanel.Controls.Add(newMap);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void returnButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Retourne au menu principal et enleve le usercontrol de la window
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void returnButton_Click(object sender, EventArgs e)
        {
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Remove(this);
            defaultView();
            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void createButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Affiche le panel pour la creation d'une nouvelle carte
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void createButton_Click(object sender, EventArgs e)
        {
            mapPanel.Visible = false;
            addPanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void importButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Affiche un explorateur de fichier qui permet de sélectionner une zone
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void importButton_Click(object sender, EventArgs e)
        {
            ouvrirZone(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirZone(bool afficherZoneDefaut)
        ///
        /// Ouvre un explorateur de ficher pour sélectionner une zone sauvegarder.
        /// Si une zone est sélectionner et met a jour le label avec le chemin.
        /// 
        /// @param bool afficherZoneDefaut: bool qui indique si la fenetre affiche
        ///                                 la zone par defaut
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirZone(bool afficherZoneDefaut)
        {
            ExplorateurOuverture explorateur = new ExplorateurOuverture(parent_);
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            DialogResult dialogresult = explorateur.ShowDialog();
            if (dialogresult == DialogResult.OK)
            {
                fileDirLabel.Text = explorateur.cheminFichier;
            }
            if (dialogresult == DialogResult.Cancel)
                fileDirLabel.Text = "";

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void offlineCheckBox_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Sélectionne l'option hors ligne et met le l'option enligne à false;
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void offlineCheckBox_Click(object sender, EventArgs e)
        {
            offlineCheckBox.Checked = true;
            onlineCheckBox.Checked = false;
            showOnlineFeatures(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void onlineCheckBox_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Sélectionne l'option enligne et met le l'option hors ligne à false;
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void onlineCheckBox_Click(object sender, EventArgs e)
        {
            onlineCheckBox.Checked = true;
            showOnlineFeatures(true);
            offlineCheckBox.Checked = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void publicCheckBox_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Sélectionne l'option public et met le l'option privée à false;
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void publicCheckBox_Click(object sender, EventArgs e)
        {
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void privateCheckBox_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Sélectionne l'option privée et met le l'option publique à false;
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void privateCheckBox_Click(object sender, EventArgs e)
        {
            publicCheckBox.Checked = false;
            privateCheckBox.Checked = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void onlineChatButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Appel la fonction pour minimiser ou maximiser le chat
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelButton_Click(object sender, EventArgs e)
        {
            addPanel.Visible = false;
            mapPanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void confirmeButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Ajoute une nouvelle carte en retourne au panel qui permet de choisir une carte.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void confirmeButton_Click(object sender, EventArgs e)
        {
            String mapName = textBox.Text;
            if (mapName.Equals(""))
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte ne peut avoir ce nom.";
                textBox.Clear();
                return;
            }

            //Offline map
            if (offlineCheckBox.Checked)
            {
                bool a = System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone));

                if (!System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone)) && !parent_.mapMenu.offlineMaps_.ContainsKey(mapName))
                {
                    //Create the map and Copy the default map
                    File.Copy(cheminDossierZone + "defaut" + extensionFichierZone, cheminDossierZone + mapName + extensionFichierZone);
                    MapPresentator newMap = new MapPresentator(parent_, mapName, false, -1, 0, -1);
                    newMap.setPath(cheminDossierZone + mapName + extensionFichierZone);
                    parent_.mapMenu.addOfflineMapEntry(mapName, newMap);
                }
                else
                {
                    warningLabel.Visible = true;
                    warningLabel.Text = "Une carte avec ce nom existe déjà.";
                    textBox.Clear();
                    return;
                }
            }
            //Online map
            else
            {
                switch(modeComboBox.SelectedIndex)
                {
                    //Edition
                    case 0:
                        FonctionsNatives.createMap(mapName, mapName.Length, (char)(ModeEnum.Mode.EDITION));
                        break;

                    //Simulation
                    case 1:
                        FonctionsNatives.createMap(mapName, mapName.Length, (char)(ModeEnum.Mode.SIMULATION));
                        break;
                }
            }

            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        private void showOnlineFeatures(bool visibility)
        {
            modeSelectionLabel.Visible = visibility;
            modeComboBox.Visible = visibility;

            rightsModificationLabel.Visible = visibility;
            publicCheckBox.Visible = visibility;
            privateCheckBox.Visible = visibility;

            importButton.Visible = visibility;
            fileDirLabel.Visible = visibility;
        }

        public void defaultView()
        {
            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        public void choseOfflineMode(MapPresentator selectedMap)
        {
            selectedMap_ = selectedMap;

            mapPanel.Visible = false;
            addPanel.Visible = false;
            offlineModePanel.Visible = true;
        }

        private void offlineEditionModeButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerCheminFichierZone(selectedMap_.pathToFile_);
            FonctionsNatives.charger();

            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionModificationPanel = new EditionModificationPanel(parent_);

            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            defaultView();

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            parent_.editionModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionModificationPanel.Width,
                                                                  parent_.editionMenuStrip.Height);
            parent_.editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionModificationPanel);

            Program.peutAfficher = true;
            parent_.verificationDuNombreElementChoisi();

            FonctionsNatives.assignerMode(ModeEnum.Mode.EDITION);
        }

        private void offlineSimulationModeButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerCheminFichierZone(selectedMap_.pathToFile_);
            FonctionsNatives.charger();

            parent_.simulationMenuStrip = new SimulationMenuStrip(parent_);
            parent_.configuration.populerToolStripProfils(parent_.simulationMenuStrip.profilsToolStripMenuItem);

            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            defaultView();

            parent_.simulationMenuStrip.Dock = DockStyle.Top;
            parent_.viewPort.Controls.Add(parent_.simulationMenuStrip);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            Program.peutAfficher = true;

            FonctionsNatives.assignerMode(ModeEnum.Mode.SIMULATION);
        }

        private void addPanel_VisibleChanged(object sender, EventArgs e)
        {
            if (addPanel.Visible)
            {
                createButton.Visible = false;
            }
            else
            {
                createButton.Visible = true;
            }

            warningLabel.Visible = false;

            textBox.Clear();

            offlineCheckBox.Checked = true;
            onlineCheckBox.Checked = false;
            showOnlineFeatures(false);

            modeComboBox.SelectedIndex = 0;

            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
            fileDirLabel.Text = "";
        }

        private void cancelJoiningButton_Click(object sender, EventArgs e)
        {
            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }
    }
}
