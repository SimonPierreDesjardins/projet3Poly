using System;
using System.Windows.Forms;

namespace ui
{
    public partial class MusicSelector : UserControl
    {
        public MusicSelector()
        {
            InitializeComponent();

            defaultCheckBox.Checked = true;
        }

        private void defaultCheckBox_Click(object sender, EventArgs e)
        {
            defaultCheckBox.Checked = true;
            customCheckBox.Checked = false;

            importButton.Visible = false;
            pictureBox.Visible = false;
            fileDirLabel.Visible = false;
        }

        private void customCheckBox_Click(object sender, EventArgs e)
        {
            defaultCheckBox.Checked = false;
            customCheckBox.Checked = true;

            importButton.Visible = true;
            pictureBox.Visible = false;
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
                string path = dialog.FileName;
                string fileName = System.IO.Path.GetFileName(path);

                fileDirLabel.Text = fileName;
                fileDirLabel.Visible = true;

                pictureBox.Visible = true;
                pictureBox.Image = Properties.Resources.confirm;
            }
        }
    }
}
