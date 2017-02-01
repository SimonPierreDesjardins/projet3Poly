using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
    class CustomClass
    {
    }

    class CustomLabel : Label
    {
        protected override void WndProc(ref Message m)
        {
            const int WM_NCHITTEST = 0x0084;
            const int WM_MOUSEHOVER = 0x02A1;
            const int HTTRANSPARENT = (-1);

            if (m.Msg == WM_NCHITTEST || m.Msg == WM_MOUSEHOVER)
            {
                m.Result = (IntPtr)HTTRANSPARENT;
            }
            else
            {
                base.WndProc(ref m);
            }
        }
    }

    class PanelButton : Panel
    {
        protected override void OnMouseEnter(EventArgs e)
        {
            BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(36)))), ((int)(((byte)(42)))), ((int)(((byte)(49)))));
            foreach (Control c in this.Controls)
            {
                if (c.GetType() == typeof(CustomLabel))
                {
                    c.ForeColor = Color.FromArgb(0, 102, 204);
                }
            }
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            BackColor = Color.Transparent;
            foreach (Control c in this.Controls)
            {
                if (c.GetType() == typeof(CustomLabel))
                {
                    c.ForeColor = Color.Silver;
                }
            }
        }
    }
}
