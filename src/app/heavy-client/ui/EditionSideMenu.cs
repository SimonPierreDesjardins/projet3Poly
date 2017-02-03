using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
    public partial class EditionSideMenu : UserControl
    {
        Window parent_;

        public EditionSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            editionObjectMenu.Width = 0;
            editionToolsMenu.Width = 0;

            ShowFullTools.Start();
        }

        private void ShowObjetMenu_Tick(object sender, EventArgs e)
        {
            if (editionObjectMenu.Width >= 200)
                ShowObjetMenu.Stop();
            else
                editionObjectMenu.Width += 5;                
        }

        private void ShowFullToolsTimer_Tick(object sender, EventArgs e)
        {
            if (editionToolsMenu.Width >= 200)
                ShowFullTools.Stop();
            else
                editionToolsMenu.Width += 5;
        }

        private void HideFullMenu_Tick(object sender, EventArgs e)
        {
            if (editionObjectMenu.Width != 0)
            {
                if (editionObjectMenu.Width > 0)
                    editionObjectMenu.Width -= 5;
                else
                    HideFullMenu.Stop();
            }
            else
            {
                if (editionToolsMenu.Width > 0)
                    editionToolsMenu.Width -= 5;
                else
                    HideFullMenu.Stop();
            }
        }

        private void ShowSideToolMenu_Tick(object sender, EventArgs e)
        {
            if (editionToolsMenu.Width > 35)
                editionToolsMenu.Width -= 5;
            else
                ShowSideToolMenu.Stop();
        }

        private void returnObjetButton_Click(object sender, EventArgs e)
        {
            animationHidingMenu();
            ShowFullTools.Start();
        }

        private void menuToolObjet_Click(object sender, EventArgs e)
        {
            if (editionToolsMenu.Width >= 200)
                ShowSideToolMenu.Start();
            else
                ShowFullTools.Start();
        }

        public void animationHidingMenu()
        {
            HideFullMenu.Start();
            while (HideFullMenu.Enabled)
            {
                Application.DoEvents();
            }
        }

        private void createToolButton_Click(object sender, EventArgs e)
        {
            animationHidingMenu();
            ShowObjetMenu.Start();
        }
    }
}
