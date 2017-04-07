////////////////////////////////////////////////
/// @file   SimMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-04-04
///
////////////////////////////////////////////////
using System.Windows.Forms;

namespace ui
{
    public partial class SimMenuStrip : UserControl
    {
        Window parent_;

        public SimMenuStrip()
        {
            InitializeComponent();
        }

        public SimMenuStrip(Window parent) : this()
        {
            parent_ = parent;
        }

        public virtual void goMenuPrincipal()
        {
            parent_.goMainMenu();
        }

        public virtual void goModeEdition()
        {
            parent_.configuration.deallocateCurrentProfilToolStrip();
            parent_.goOfflineEdition();
        }

        public virtual void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        public virtual void orbiteView()
        {
            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        public virtual void firstPersonView()
        {
            FonctionsNatives.assignerVuePremierePersonne();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        public virtual void goIntoPause()
        {
            parent_.estEnPause = !parent_.estEnPause;
        }
    }
}
