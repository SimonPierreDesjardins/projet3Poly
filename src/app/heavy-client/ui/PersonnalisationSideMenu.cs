using ModeEnum;
using System.Windows.Forms;

namespace ui
{
    public partial class PersonnalisationSideMenu : UserControl
    {
        Window parent_;

        public PersonnalisationSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            this.Width = 0;
            ShowMenuTimer.Start();
        }

        private void ShowMenuTimer_Tick(object sender, System.EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (this.Width >= 200)
                ShowMenuTimer.Stop();
            else
                this.Width += 5;
        }

        private void returnMainMenu_Button_Click(object sender, System.EventArgs e)
        {
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
            ColorSelector colorSelector = new ColorSelector(parent_);
            parent_.viewPort.Controls.Add(colorSelector);
            colorSelector.Dock = DockStyle.Right;


        }

        private void carColor_Button_Click(object sender, System.EventArgs e)
        {

        }

        private void carChange_Button_Click(object sender, System.EventArgs e)
        {

        }

        private void tableChange_Button_Click(object sender, System.EventArgs e)
        {

        }

        private void musicChange_Button_Click(object sender, System.EventArgs e)
        {

        }
    }
}
