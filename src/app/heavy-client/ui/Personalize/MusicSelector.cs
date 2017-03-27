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

        private void applyButton_Click(object sender, EventArgs e)
        {
            applyButton.Visible = false;
            defaultButton.Visible = true;

            if (customMusicPath_.Equals(FonctionsNatives.getMusic()))
                return;

            loadSong(customMusicPath_);
        }

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

        private void controlsEnabled(bool permission)
        {
            defaultButton.Enabled = permission;
            applyButton.Enabled = permission;
            importButton.Enabled = permission;
        }

        private void resetLoading()
        {
            dot1.ForeColor = System.Drawing.Color.Silver;
            dot2.ForeColor = System.Drawing.Color.Silver;
            dot3.ForeColor = System.Drawing.Color.Silver;
            dot4.ForeColor = System.Drawing.Color.Silver;
            ticks_ = 0;
        }

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
