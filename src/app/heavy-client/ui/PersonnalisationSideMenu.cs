////////////////////////////////////////////////
/// @file   PersonnalisationSideMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using ModeEnum;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class PersonnalisationSideMenu : UserControl
    {
        Window parent_;
        public ColorSelector wheelColorSelector;
        public ColorSelector robotColorSelector;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PersonnalisationSideMenu(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public PersonnalisationSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            wheelColorSelector = new ColorSelector(parent_, (int)VehiculePiece.VehiculePiece.Wheels);
            robotColorSelector = new ColorSelector(parent_, (int)VehiculePiece.VehiculePiece.Body);

            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void returnMainMenu_Button_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void returnMainMenu_Button_Click(object sender, System.EventArgs e)
        {
            goMenuPrincipal();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goMenuPrincipal()
        ///
        /// Cette fonction enlève les composantes du mode personnalisation, ajoute ceux du
        /// du mode principal et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goMenuPrincipal()
        {
            setDefaultUnselectedColors();
            parent_.viewPort.Controls.Remove(parent_.personnalisationSideMenu);
            parent_.mainMenu = new MainMenu(parent_);

            parent_.mainScreen.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = false;
            Program.peutAfficher = false;

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        private void wheelColor_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            wheelColorLabel.ForeColor = Color.Silver;
            wheelColor_Button.BackColor = Color.FromArgb(0, 102, 204);

            parent_.viewPort.Controls.Add(wheelColorSelector);
            wheelColorSelector.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            wheelColorSelector.Location = new Point(parent_.viewPort.Width - wheelColorSelector.Width, 0);
        }

        private void carColor_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            robotColorLabel.ForeColor = Color.Silver;
            carColor_Button.BackColor = Color.FromArgb(0, 102, 204);

            parent_.viewPort.Controls.Add(robotColorSelector);
            robotColorSelector.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            robotColorSelector.Location = new Point(parent_.viewPort.Width - robotColorSelector.Width, 0);
        }

        private void carChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            robotChangeLabel.ForeColor = Color.Silver;
            carChange_Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        private void tableChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            changeTableLabel.ForeColor = Color.Silver;
            tableChange_Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        private void musicChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            musicChangeLabel.ForeColor = Color.Silver;
            musicChange_Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        private void setDefaultUnselectedColors()
        {
            returnMainMenu_Button.BackColor = Color.Transparent;
            wheelColor_Button.BackColor = Color.Transparent;
            carColor_Button.BackColor = Color.Transparent;
            carChange_Button.BackColor = Color.Transparent;
            tableChange_Button.BackColor = Color.Transparent;
            musicChange_Button.BackColor = Color.Transparent;

            returnLabel.ForeColor = Color.Silver;
            wheelColorLabel.ForeColor = Color.Silver;
            robotColorLabel.ForeColor = Color.Silver;
            robotChangeLabel.ForeColor = Color.Silver;
            changeTableLabel.ForeColor = Color.Silver;
            musicChangeLabel.ForeColor = Color.Silver;

            if (parent_.viewPort.Controls.Contains(wheelColorSelector))
                parent_.viewPort.Controls.Remove(wheelColorSelector);
            if (parent_.viewPort.Controls.Contains(robotColorSelector))
                parent_.viewPort.Controls.Remove(robotColorSelector);
        }
    }
}
