////////////////////////////////////////////////
/// @file   ChatWindow.cs
/// @author Frédéric Grégoire
/// @date   2017-02-22
///
////////////////////////////////////////////////
using System.Windows.Forms;

namespace ui
{
    public partial class ChatWindow : Form
    {
        Window mainWindow_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ChatWindow(Window mainWindow)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window mainWindow: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ChatWindow(Window mainWindow)
        {
            InitializeComponent();
            mainWindow_ = mainWindow;
        }
    }
}
