////////////////////////////////////////////////
/// @file   MusicSelector.cs
/// @author Frédéric Grégoire
/// @date   2017-03-20
///
////////////////////////////////////////////////
using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace ui
{
    public partial class MusicSelector : UserControl
    {
        Window parent_;
        string defaultMusicPath_;
        string customMusicPath_;

        int ticks_ = 0;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MusicSelector(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public MusicSelector(Window parent)
        {
            InitializeComponent();

            parent_ = parent;

            defaultMusicPath_ = FonctionsNatives.getDefaultMusic();
            customMusicPath_ = FonctionsNatives.getMusic();

            if (defaultMusicPath_.Equals(customMusicPath_))
            {
                fileDirLabel.Text = System.IO.Path.GetFileName(defaultMusicPath_);
                defaultButton.Visible = false;
                applyButton.Visible = false;
            }
            else
            {
                fileDirLabel.Text = System.IO.Path.GetFileName(customMusicPath_);
                defaultButton.Visible = true;
                applyButton.Visible = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void importButton_Click(object sender, EventArgs e)
        ///
        /// Ouvre un explorateur de fichier qui permet de chercher pour une musique
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void importButton_Click(object sender, EventArgs e)
        {
            string homePath = (Environment.OSVersion.Platform == PlatformID.Unix || Environment.OSVersion.Platform == PlatformID.MacOSX)
                                ? Environment.GetEnvironmentVariable("HOME") : Environment.ExpandEnvironmentVariables("%HOMEDRIVE%%HOMEPATH%");
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Fichier MP3 (.mp3)|*mp3|Fichier WAV (.wav)|*wav";
            dialog.InitialDirectory = homePath;
            dialog.Title = "Please select your mp3 file";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                customMusicPath_ = dialog.FileName;
                fileDirLabel.Text = System.IO.Path.GetFileName(customMusicPath_);
                defaultButton.Visible = true;
                applyButton.Visible = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void defaultButton_Click(object sender, EventArgs e)
        ///
        /// Remet la musique par defaut pour la simulation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void defaultButton_Click(object sender, EventArgs e)
        {
            string a = System.IO.Path.GetFileName(defaultMusicPath_);
            fileDirLabel.Text = System.IO.Path.GetFileName(defaultMusicPath_);
            defaultButton.Visible = false;
            applyButton.Visible = false;

            if (defaultMusicPath_.Equals(FonctionsNatives.getMusic()))
                return;

            loadSong(defaultMusicPath_);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyButton_Click(object sender, EventArgs e)
        ///
        /// Met la musique de l'user en mémoire
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void applyButton_Click(object sender, EventArgs e)
        {
            applyButton.Visible = false;
            defaultButton.Visible = true;

            if (customMusicPath_.Equals(FonctionsNatives.getMusic()))
                return;

            loadSong(customMusicPath_);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void loadSong(string path)
        ///
        /// Crée un thread pour charger le musique de l'user dans l'engin de son
        /// 
        /// @param string path: chemin vers la musique
        ////////////////////////////////////////////////////////////////////////
        private void loadSong(string path)
        {
            parent_.personnalisationSideMenu.controlsEnabled(false);
            controlsEnabled(false);
            loadingPanel.Visible = true;
            LoadingTimer.Start();

            panel.Visible = false;

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

            fileDirLabel.Text = System.IO.Path.GetFileName(path);

            pictureBox.Visible = true;
            pictureBox.Image = Properties.Resources.confirm;

            panel.Visible = true;
            loadingPanel.Visible = false;
            LoadingTimer.Stop();
            resetLoading();
            controlsEnabled(true);
            parent_.personnalisationSideMenu.controlsEnabled(true);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void controlsEnabled(bool permission)
        ///
        /// Active ou desactive les controle pour changer la musique
        /// 
        /// @param bool permission: true pour activer, false pour desactiver
        ///
        ////////////////////////////////////////////////////////////////////////
        private void controlsEnabled(bool permission)
        {
            defaultButton.Enabled = permission;
            applyButton.Enabled = permission;
            importButton.Enabled = permission;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void resetLoading()
        ///
        /// Remet le widget pour charger a son état initial
        ///
        ////////////////////////////////////////////////////////////////////////
        private void resetLoading()
        {
            dot1.ForeColor = System.Drawing.Color.Silver;
            dot2.ForeColor = System.Drawing.Color.Silver;
            dot3.ForeColor = System.Drawing.Color.Silver;
            dot4.ForeColor = System.Drawing.Color.Silver;
            ticks_ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void LoadingTimer_Tick(object sender, EventArgs e)
        ///
        /// Change la couleur d'une lettre à chaque fois que le timer "tick"
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du tick
        ///
        ////////////////////////////////////////////////////////////////////////
        private void LoadingTimer_Tick(object sender, EventArgs e)
        {
            switch(++ticks_)
            {
                case 1:
                    dot1.ForeColor = System.Drawing.Color.FromArgb(0, 102, 204);
                    break;

                case 2:
                    dot2.ForeColor = System.Drawing.Color.FromArgb(0, 102, 204);
                    break;

                case 3:
                    dot3.ForeColor = System.Drawing.Color.FromArgb(0, 102, 204);
                    break;

                case 4:
                    dot4.ForeColor = System.Drawing.Color.FromArgb(0, 102, 204);
                    break;

                default:
                    resetLoading();
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// public class Worker
        ///
        /// Cette classe a pour but de changer la musique dans l'engin de son
        /// 
        ////////////////////////////////////////////////////////////////////////
        public class Worker
        {
            string path_;

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public Worker(string path)
            ///
            /// Cette fonction initialize assigne les attributs.
            ///
            /// @param string path: Chemin vers la musique 
            /// 
            ////////////////////////////////////////////////////////////////////////
            public Worker(string path)
            {
                path_ = path;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public DoWork()
            ///
            /// Change la musique dans l'engin de son
            /// 
            ////////////////////////////////////////////////////////////////////////
            public void DoWork()
            {
                FonctionsNatives.setMusic(path_);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn FonctionsNatives
    ///
    /// Communication avec le modèle C++
    ///
    ////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setMusic(String path);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void getMusic(StringBuilder str, int size);
        public static string getMusic()
        {
            StringBuilder str = new StringBuilder(100);
            getMusic(str, str.Capacity);
            return str.ToString();
        }

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void getDefaultMusic(StringBuilder str, int size);
        public static string getDefaultMusic()
        {
            StringBuilder str = new StringBuilder(100);
            getDefaultMusic(str, str.Capacity);
            return str.ToString();
        }
    }
}
