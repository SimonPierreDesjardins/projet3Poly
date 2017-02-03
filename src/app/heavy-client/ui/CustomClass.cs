using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
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
            if (this.BackColor != Color.FromArgb(0, 102, 204))
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
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            if (this.BackColor != Color.FromArgb(0, 102, 204))
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

    class myRenderer : ToolStripProfessionalRenderer
    {
        protected override void OnRenderMenuItemBackground(ToolStripItemRenderEventArgs myMenu)
        {
            if (!myMenu.Item.Selected)
                base.OnRenderMenuItemBackground(myMenu);
            else
            {
                Rectangle menuRectangle = new Rectangle(Point.Empty, myMenu.Item.Size);
                //Fill Color
                myMenu.Graphics.FillRectangle(Brushes.LightBlue, menuRectangle);
                myMenu.Item.ForeColor = Color.FromArgb(26, 32, 40);
                // Border Color
                //myMenu.Graphics.DrawRectangle(Pens.Lime, 1, 0, menuRectangle.Width - 2, menuRectangle.Height - 1);
            }
        }

        protected override void OnRenderItemText(ToolStripItemTextRenderEventArgs e)
        {
            base.OnRenderItemText(e);
            if (e.Item.Pressed)
                e.Item.ForeColor = Color.FromArgb(26, 32, 40);
            else if (e.Item.OwnerItem != null && e.Item.OwnerItem.Pressed)
                e.Item.ForeColor = Color.FromArgb(26, 32, 40);
            else
                e.Item.ForeColor = Color.FromArgb(178, 216, 255);
        }
    }
}
