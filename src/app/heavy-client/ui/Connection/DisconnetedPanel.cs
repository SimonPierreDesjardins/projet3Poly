////////////////////////////////////////////////
/// @file   DisconnectedPanel.cs
/// @author Frédéric Grégoire
/// @date   2017-03-16
///
////////////////////////////////////////////////
using System.Windows.Forms;

namespace ui
{
    public partial class DisconnetedPanel : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public DisconnetedPanel(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public DisconnetedPanel(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void reconnectButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Tente de reconnecter le client au serveur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void reconnectButton_Click(object sender, System.EventArgs e)
        {
            //Add reconnect call
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void continuButton_Click(object sender, MeasureItemEventArgs e)
        ///
        /// Enleve le control du viewport
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void continuButton_Click(object sender, System.EventArgs e)
        {
            parent_.viewPort.Controls.Remove(this);
        }
    }
}
