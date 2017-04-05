////////////////////////////////////////////////
/// @file   MapMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

namespace ui
{
    public partial class MapMenu : UserControl
    {
        Window parent_;
        MapPresentator selectedMap_;

        int numberOfMaps_ = 0;
        public Dictionary<string, MapPresentator> offlineMaps_ = new Dictionary<string, MapPresentator>();
        public Dictionary<string, MapPresentator> onlineMapsName_ = new Dictionary<string, MapPresentator>();
        public Dictionary<int, MapPresentator> onlineMaps_ = new Dictionary<int, MapPresentator>();

        private string cheminFichierZoneDefaut = "";
        private string cheminDossierZone = "";
        private string nomFichierZoneDefaut = "";
        private string extensionFichierZone = "";

        private string importPath = "";

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

            fileDirLabel.Text = null;

            //Lovely circles as char in password
            passwordBox.PasswordChar = '\u25CF';

            //Set callbacks for map permission change
            mapPermissionInstance = new CallbackMapPermission(MapPermissionHandler);
            SetCallbackForMapPermission(mapPermissionInstance);

            //Set callbacks for map connection
            mapConnectionInstance = new CallbackMapConnection(MapConnectionHandler);
            SetCallbackForMapConnection(mapConnectionInstance);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void initMapList()
        ///
        /// Ajoute les maps presentes dans les dictionnaires au mapPanel
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void initMapList()
        {
            if (FonctionsNatives.isConnected())
                onlineCheckBox.Visible = true;
            else
                onlineCheckBox.Visible = false;

            mapPanel.Controls.Clear();
            numberOfMaps_ = 0;
            foreach (KeyValuePair<int, MapPresentator> pair in onlineMaps_)
            {
                pair.Value.Size = new Size(this.mapPanel.Width, pair.Value.Height);
                pair.Value.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
                pair.Value.Location = new Point(0, numberOfMaps_++ * 150);
                mapPanel.Controls.Add(pair.Value);
            }
            foreach (KeyValuePair<string, MapPresentator> pair in offlineMaps_)
            {
                pair.Value.Size = new Size(this.mapPanel.Width, pair.Value.Height);
                pair.Value.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
                pair.Value.Location = new Point(0, numberOfMaps_++ * 150);
                mapPanel.Controls.Add(pair.Value);
            }
            verifyMapsAttributes();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void addOnlineMapEntry(int mapId, MapPresentator newMap)
        ///
        /// Cette fonction ajoute une map enligne au dictionnaire
        ///
        /// @param int mapId: numero unique representant une map
        /// @param MapPresentator newMap: la map a ajouter
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void addOnlineMapEntry(int mapId, MapPresentator newMap)
        { 
            if (!onlineMaps_.ContainsKey(mapId))
            {
                newMap.Size = new Size(this.mapPanel.Width, newMap.Height);
                newMap.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
                newMap.Location = new Point(0, numberOfMaps_++ * 150);
                onlineMaps_.Add(mapId, newMap);

                parent_.Invoke((MethodInvoker)delegate {
                    mapPanel.VerticalScroll.Value = 0;
                    this.mapPanel.Controls.Add(newMap);
                });
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void addOfflineMapEntry(int mapId, MapPresentator newMap)
        ///
        /// Cette fonction ajoute une map hors ligne au dictionnaire
        ///
        /// @param int mapId: numero unique representant une map
        /// @param MapPresentator newMap: la map a ajouter
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void addOfflineMapEntry(string name, MapPresentator newMap)
        {
            if (!offlineMaps_.ContainsKey(name))
            {
                mapPanel.VerticalScroll.Value = 0;
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
            offlineModePanel.Visible = false;
            mapPanel.Visible = false;
            addPanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Gere les touches accepter par cette textBox
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyPressEventArgs e: evenement d'un keydown
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar.ToString() != "\b")
            {
                Regex regex = new Regex("[A-zÀ-ÿ0-9._]+");
                e.Handled = !regex.IsMatch(e.KeyChar.ToString());
            }
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
            numberOfMaps_ = 0;
            mapPanel.Controls.Clear();
            ouvrirZone(true);
            initMapList();
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
                importPath = explorateur.cheminFichier;
                fileDirLabel.Text = Path.GetFileName(importPath);
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

            //No password
            passwordLabel.Visible = false;
            passwordBox.Visible = false;
            passwordBox.Clear();
            passwordWarningLabel.Visible = false;
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

            //Show password
            passwordLabel.Visible = true;
            passwordBox.Visible = true;
            passwordWarningLabel.Visible = false;
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
            createMap();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void createMap()
        ///
        /// Cree une map selon les choix de l'utilisateur. Fait egalement de la gestion
        /// d'erreur si ses choix ne peuvent pas etre executer.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void createMap()
        {
            String mapName = textBox.Text;
            if (mapName.Equals("") || offlineMaps_.ContainsKey(mapName) || onlineMapsName_.ContainsKey(mapName))
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte ne peut avoir ce nom.";
                textBox.Clear();
                return;
            }

            //Offline map
            if (offlineCheckBox.Checked)
            {
                creatingOffLineMap(mapName);
            }
            //Online map
            else
            {
                //Check password
                String password = "";
                if (privateCheckBox.Checked)
                {
                    if (passwordBox.TextLength == 0)
                    {
                        passwordWarningLabel.Visible = true;
                        passwordWarningLabel.Text = "Doit avoir un mot de passe";
                        passwordBox.Clear();
                        return;
                    }
                    password = passwordBox.Text;
                }

                creatingOnlineMap(mapName, password);
            }

            importPath = null;
            fileDirLabel.Text = null;

            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        private void creatingOffLineMap(string mapName)
        {
            if (!System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone)))
            {
                //Create the map and Copy the default map
                File.Copy(cheminDossierZone + "defaut" + extensionFichierZone, cheminDossierZone + mapName + extensionFichierZone);
                MapPresentator newMap = new MapPresentator(parent_, mapName, false, -1, 0, -1, false, false);
                newMap.setPath(cheminDossierZone + mapName + extensionFichierZone);
                parent_.mapMenu.addOfflineMapEntry(mapName, newMap);
                verifyMapsAttributes();
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte avec ce nom existe déjà.";
                textBox.Clear();
                return;
            }
        }

        private void creatingOnlineMap(string mapName, string password)
        {
            //Import map
            if (!string.IsNullOrEmpty(fileDirLabel.Text))
            {
                uploadMap(importPath);
            }
            
            //Create map
            char mapType = '\0';
            switch (modeComboBox.SelectedIndex)
            {
                //Edition
                case 0:
                    mapType = (char)(ModeEnum.Mode.ONLINE_EDITION);
                    FonctionsNatives.createMap(mapName, mapName.Length, password, password.Length, mapType, privateCheckBox.Checked ? (char)1 : (char)0);
                    break;

                //Simulation
                case 1:
                    mapType = (char)(ModeEnum.Mode.ONLINE_SIMULATION);
                    FonctionsNatives.createMap(mapName, mapName.Length, password, password.Length, mapType, privateCheckBox.Checked ? (char)1 : (char)0);
                    break;

                //Piece
                case 2:
                    createMapPieceMode();
                    //FonctionsNatives.createMap(mapName, mapName.Length, (char)(ModeEnum.Mode.SIMULATION));
                    break;

                case 3:
                    createMapRaceMode();
                    //FonctionsNatives.createMap(mapName, mapName.Length, (char)(ModeEnum.Mode.SIMULATION));
                    break;
            }
        }

        private void uploadMap(string path)
        {
            loadingPanel load = new loadingPanel(parent_);
            load.Dock = DockStyle.Fill;
            parent_.Controls.Add(load);
            load.BringToFront();

            //Create thread
            Worker workerObject = new Worker(path);
            Thread workerThread = new Thread(workerObject.DoWork);

            // Start the worker thread.
            workerThread.Start();

            // Loop until worker thread activates.
            while (!workerThread.IsAlive) ;

            // Loop until worker thread activates.
            while (workerThread.IsAlive)
            {
                Application.DoEvents();
            };

            load.stop();
            parent_.Controls.Remove(load);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void showOnlineFeatures(bool visibility)
        ///
        /// Change la visibilite des options de creation pour une map enligne
        /// 
        /// @param bool visibility: Bool indiquant si les composantes sont visible ou non
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void showOnlineFeatures(bool visibility)
        {
            modeComboBox.SelectedIndex = 0;
            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
            fileDirLabel.Text = null;

            passwordLabel.Visible = false;
            passwordBox.Visible = false;
            passwordBox.Clear();
            passwordWarningLabel.Visible = false;

            modeSelectionLabel.Visible = visibility;
            modeComboBox.Visible = visibility;

            rightsModificationLabel.Visible = visibility;
            publicCheckBox.Visible = visibility;
            privateCheckBox.Visible = visibility;

            importButton.Visible = visibility;
            fileDirLabel.Visible = visibility;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void defaultView()
        ///
        /// Remet la vue par defaut pour le controle
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void defaultView()
        {
            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
            fileDirLabel.Text = null;

            numberOfMaps_ = 0;
            mapPanel.Controls.Clear();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void choseOfflineMode(MapPresentator selectedMap)
        ///
        /// Montre le panel pour choisir entre edition / simulation lorsqu'une 
        /// map est appuyer
        /// 
        /// @param MapPresentator selectedMap: map selectionne par l'utilisateur
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void choseOfflineMode(MapPresentator selectedMap)
        {
            selectedMap_ = selectedMap;

            mapPanel.Visible = false;
            addPanel.Visible = false;
            offlineModePanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void offlineEditionModeButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Fonction qui change le ui pour aller en mode edition et charge la carte selectionner
        /// par l'utilisateur.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void offlineEditionModeButton_Click(object sender, EventArgs e)
        {
            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            defaultView();

            if (FonctionsNatives.getEditionTutorialState())
            {
                parent_.goOfflineEdition(selectedMap_.pathToFile_);
            }
            else
            {
                parent_.goOfflineEditionTutorial();
            }
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void offlineSimulationModeButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Fonction qui change le ui pour aller en mode simulation et charge la carte selectionner
        /// par l'utilisateur.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void offlineSimulationModeButton_Click(object sender, EventArgs e)
        {
            parent_.viewPort.Controls.Remove(parent_.mapMenu);
            defaultView();

            if (FonctionsNatives.getSimulationTutorialState())
            {
                parent_.goOfflineSimulation(selectedMap_.pathToFile_);
            }
            else
            {
                parent_.goOfflineSimulationTutorial();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void addPanel_VisibleChanged(object sender, EventArgs e)
        ///
        /// Fonction qui remet par defaut les options de creation d'une map lorsque
        /// sa visibiliter change
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du changement de visibiliter
        ///
        ////////////////////////////////////////////////////////////////////////
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
            passwordBox.Clear();

            offlineCheckBox.Checked = true;
            onlineCheckBox.Checked = false;
            showOnlineFeatures(false);

            modeComboBox.SelectedIndex = 0;

            publicCheckBox.Checked = true;
            privateCheckBox.Checked = false;
            fileDirLabel.Text = null;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cancelJoiningButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Fonction qui remontre le choix des maps lorsque l'utilisateur choisi de ne pas
        /// joindre une map
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelJoiningButton_Click(object sender, EventArgs e)
        {
            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void verifyMapsAttributes()
        ///
        /// Fonction qui ajuste toutes les maps presenter a l'utilisateur
        /// en fonction des dimensions du mapPanel
        ///
        ////////////////////////////////////////////////////////////////////////
        private void verifyMapsAttributes()
        {
            foreach (MapPresentator map in mapPanel.Controls)
            {
                map.Width = mapPanel.Width;
            }
        }

        //Cette fonction est temporaire - attend que le mode soit en ligne
        private void createMapPieceMode()
        {
            String mapName = textBox.Text;
            if (mapName.Equals(""))
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte ne peut avoir ce nom.";
                textBox.Clear();
                return;
            }

            bool a = System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone));

            if (!System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone)) && !parent_.mapMenu.offlineMaps_.ContainsKey(mapName))
            {
                //Create the map and Copy the default map
                File.Copy(cheminDossierZone + "defaut" + extensionFichierZone, cheminDossierZone + mapName + extensionFichierZone);
                MapPresentator newMap = new MapPresentator(parent_, mapName, false, (int)ModeEnum.Mode.PIECES, 0, -1, false, false);
                newMap.setPath(cheminDossierZone + mapName + extensionFichierZone);
                parent_.mapMenu.addOnlineMapEntry(-1, newMap);
                verifyMapsAttributes();
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte avec ce nom existe déjà.";
                textBox.Clear();
                return;
            }

            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        //Cette fonction est temporaire - attend que le mode soit en ligne
        //Également changer dans SingleMapPresentation
        public void createMapRaceMode()
        {
            String mapName = textBox.Text;
            if (mapName.Equals(""))
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte ne peut avoir ce nom.";
                textBox.Clear();
                return;
            }

            bool a = System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone));

            if (!System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + mapName + extensionFichierZone)) && !parent_.mapMenu.offlineMaps_.ContainsKey(mapName))
            {
                //Create the map and Copy the default map
                File.Copy(cheminDossierZone + "defaut" + extensionFichierZone, cheminDossierZone + mapName + extensionFichierZone);
                //Todo change mode
                MapPresentator newMap = new MapPresentator(parent_, mapName, false, (int)ModeEnum.Mode.PIECES, 0, -1, false, false);
                newMap.setPath(cheminDossierZone + mapName + extensionFichierZone);
                parent_.mapMenu.addOnlineMapEntry(-1, newMap);
                verifyMapsAttributes();
            }
            else
            {
                warningLabel.Visible = true;
                warningLabel.Text = "Une carte avec ce nom existe déjà.";
                textBox.Clear();
                return;
            }

            mapPanel.Visible = true;
            addPanel.Visible = false;
            offlineModePanel.Visible = false;
        }

        public class Worker
        {
            string path_;

            public Worker(string path)
            {
                path_ = path;
            }
            // This method will be called when the thread is started.
            public void DoWork()
            {
                FonctionsNatives.uploadMap(path_);
            }
        }

        public void Test1(int mapId, int action)
        {
            mapPermission(mapId, action);
        }

        private delegate void CallbackMapPermission(int mapId, int action);
        // Ensure it doesn't get garbage collected
        private CallbackMapPermission mapPermissionInstance;
        private void MapPermissionHandler(int mapId, int action)
        {
            MapPresentator tmp;
            bool success = onlineMaps_.TryGetValue(mapId, out tmp);
            if (!success)
                System.Console.WriteLine("Couldn't find map with id: " + mapId + " in online dictionary.");

            switch (action)
            {
                case (int)MapPermission.Permission.CHANGED_PUBLIC:
                    tmp.changeToPublic();
                    break;

                case (int)MapPermission.Permission.CHANGED_PRIVATE:
                    tmp.changeToPrivate();
                    break;

                case (int)MapPermission.Permission.CHANGED_DENIED:
                    System.Console.WriteLine("Permission denied to change permission on mapId: " + mapId + ".");
                    break;

                default:
                    System.Console.WriteLine("Unexpected command on map permission change. MapId: " + mapId + ".");
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForMapPermission(CallbackMapPermission fn);

        [DllImport("model.dll")]
        private static extern void mapPermission(int mapId, int action);


        public void Test(int mapId, int action)
        {
            mapConnect(mapId, action);
        }

        private delegate void CallbackMapConnection(int mapId, int action);
        // Ensure it doesn't get garbage collected
        private CallbackMapConnection mapConnectionInstance;
        private void MapConnectionHandler(int mapId, int action)
        {
            MapPresentator tmp;
            bool success = onlineMaps_.TryGetValue(mapId, out tmp);
            if (!success)
                System.Console.WriteLine("Couldn't find map with id: " + mapId + " in online dictionary.");

            switch (action)
            {
                case (int)MapJoin.Response.MAP_JOINED:
                    tmp.joinMap();
                    break;

                case (int)MapJoin.Response.MAP_FULL:
                    tmp.sessionFull();
                    break;

                case (int)MapJoin.Response.MAP_WRONG_PASSWORD:
                    tmp.wrongPassword();
                    break;

                default:
                    System.Console.WriteLine("Unexpected command on map connection. MapId: " + mapId + ".");
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction permettant le callback entre le c++ et le c#
        ///
        ////////////////////////////////////////////////////////////////////////
        [DllImport("model.dll")]
        private static extern void SetCallbackForMapConnection(CallbackMapConnection fn);

        [DllImport("model.dll")]
        private static extern void mapConnect(int mapId, int action);
    }

    static partial class FonctionsNatives
    {
		[DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void uploadMap(string chemin);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getEditionTutorialState();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getSimulationTutorialState();
    }
}