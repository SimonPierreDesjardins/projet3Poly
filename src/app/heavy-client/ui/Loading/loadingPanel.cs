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
    public partial class loadingPanel : UserControl
    {
        int ticks_ = 0;
        Window parent_;

        public loadingPanel(Window parent)
        {
            parent_ = parent;
            InitializeComponent();
            load.Start();
        }

        private void load_Tick(object sender, EventArgs e)
        {
            parent_.Invoke((MethodInvoker)delegate {
                switch (++ticks_)
                {
                    case 1:
                        c.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 2:
                        h.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 3:
                        a.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 4:
                        r.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 5:
                        g.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 6:
                        E1.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 7:
                        m.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 8:
                        E2.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 9:
                        N.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    case 10:
                        t.ForeColor = Color.FromArgb(0, 102, 204);
                        break;

                    default:
                        c.ForeColor = Color.Silver;
                        h.ForeColor = Color.Silver;
                        a.ForeColor = Color.Silver;
                        r.ForeColor = Color.Silver;
                        g.ForeColor = Color.Silver;
                        E1.ForeColor = Color.Silver;
                        m.ForeColor = Color.Silver;
                        E2.ForeColor = Color.Silver;
                        N.ForeColor = Color.Silver;
                        t.ForeColor = Color.Silver;
                        ticks_ = 0;
                        break;
                }
            });
        }
    }
}
