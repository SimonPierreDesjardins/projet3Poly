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

        public SimMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
        }

        public virtual void goMenuPrincipal()
        {
            parent_.estEnPause = false;
            parent_.picturePause.Visible = false;

            parent_.mainMenu = new MainMenu(parent_);

            parent_.configuration.deallocateCurrentProfilToolStrip();

            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            FonctionsNatives.assignerMode(ModeEnum.Mode.MENU_PRINCIPAL);
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
