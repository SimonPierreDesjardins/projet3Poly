////////////////////////////////////////////////
/// @file   MapPresentator.cs
/// @author Frédéric Grégoire
/// @date   2017-02-27
///
////////////////////////////////////////////////
using System.Windows.Forms;

namespace ui
{
    public partial class MapPresentator : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MapPresentator(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public MapPresentator(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
        }
    }
}
