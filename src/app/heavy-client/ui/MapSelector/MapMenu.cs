////////////////////////////////////////////////
/// @file   MapMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class MapMenu : UserControl
    {
        Window parent_;
        int numberOfMaps_ = 0;

        public Dictionary<string, MapPresentator> offlineMaps_ = new Dictionary<string, MapPresentator>();
        public Dictionary<int, MapPresentator> onlineMaps_ = new Dictionary<int, MapPresentator>();

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

        //Delete this button. only for testing
        private void button1_Click(object sender, EventArgs e)
        {
            parent_.viewPort.Controls.Remove(this);
            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);
            parent_.editionModificationPanel = new EditionModificationPanel(parent_);

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;
            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            parent_.editionModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionModificationPanel.Width,
                                                      parent_.editionMenuStrip.Height);
            parent_.editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionModificationPanel);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            String name = "coucou";
            FonctionsNatives.createMap(name, name.Length, (char)(2));

            Program.peutAfficher = true;
            parent_.verificationDuNombreElementChoisi();

            /*
            MapPresentator newMap = new MapPresentator(parent_);
            this.mapPanel.Controls.Add(newMap);
            newMap.Size = new Size(this.mapPanel.Width, newMap.Height);
            newMap.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
            newMap.Location = new Point(0, numberOfMaps_++ * 150);
            */
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
                //FonctionsNatives.assignerCheminFichierZone(explorateur.cheminFichier);
                //FonctionsNatives.charger();
                //PasserEnSimulation = true;
            }
            if (dialogresult == DialogResult.Cancel)
                fileDirLabel.Text = "";
                //PasserEnSimulation = false;

            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
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

            warningLabel.Visible = false;
            textBox.Clear();
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
            fileDirLabel.Text = "";
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
            FonctionsNatives.createMap(mapName, mapName.Length, (char)(ModeEnum.Mode.EDITION));

            addPanel.Visible = false;
            warningLabel.Visible = false;
            textBox.Clear();
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
            fileDirLabel.Text = "";
        }
    }
}
