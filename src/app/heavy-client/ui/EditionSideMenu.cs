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
        }
    }
}
