using System.Windows.Forms;

namespace ui
{
    public partial class DisconnetedPanel : UserControl
    {
        Window parent_;

        public DisconnetedPanel(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
        }

        private void reconnectButton_Click(object sender, System.EventArgs e)
        {
            //Add reconnect call
        }

        private void continuButton_Click(object sender, System.EventArgs e)
        {
            parent_.viewPort.Controls.Remove(this);
        }
    }
}
