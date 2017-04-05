////////////////////////////////////////////////
/// @file   EditMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-04-04
///
////////////////////////////////////////////////
using System.Windows.Forms;

namespace ui
{
    public partial class EditMenuStrip : UserControl
    {
        Window parent_;

        public EditMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;
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

        public virtual bool canSave()
        {
            return false;
        }

        public virtual void enregistrer()
        {
            FonctionsNatives.sauvegarder();
        }

        public virtual bool enregistrerSousZone()
        {
            bool saved = false;
            ExplorateurSauvegarde explorateur = new ExplorateurSauvegarde();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            if (explorateur.ShowDialog() == DialogResult.OK)
            {
                FonctionsNatives.assignerCheminFichierZone(explorateur.CheminFichier);
                FonctionsNatives.sauvegarder();
                saved = true;
            }
            explorateur.Dispose();
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
            return saved;
        }

        public virtual void goMenuPrincipal()
        {
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            FonctionsNatives.assignerMode(ModeEnum.Mode.MENU_PRINCIPAL);
        }

        public virtual void ouvrirZone(bool showDefault)
        {

        }

        public virtual void nouvelleZone()
        {

        }

        public virtual void goTestMode()
        {

        }

        public virtual void helpPopUp()
        {
            PopOutInterface popup = new PopOutInterface();
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);
            DialogResult dialogresult = popup.ShowDialog();
            if (dialogresult == DialogResult.OK || dialogresult == DialogResult.Cancel)
            {
                popup.Dispose();
                parent_.viewPort.Focus();
            }
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }
    }
}
