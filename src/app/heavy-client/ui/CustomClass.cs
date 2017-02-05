using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
    static class Constants
    {
        //Numbers
        public const int Key_1 = 49;
        public const int Key_2 = 50;
        public const int Key_3 = 51;

        //Alphabet
        public const int Key_A = 65;
        public const int Key_B = 66;
        public const int Key_C = 67;
        public const int Key_D = 68;
        public const int Key_E = 69;
        public const int Key_F = 70;
        public const int Key_G = 71;
        public const int Key_H = 72;
        public const int Key_I = 73;
        public const int Key_J = 74;
        public const int Key_K = 75;
        public const int Key_L = 76;
        public const int Key_M = 77;
        public const int Key_N = 78;
        public const int Key_O = 79;
        public const int Key_P = 80;
        public const int Key_Q = 81;
        public const int Key_R = 82;
        public const int Key_S = 83;
        public const int Key_T = 84;
        public const int Key_U = 85;
        public const int Key_V = 86;
        public const int Key_W = 87;
        public const int Key_X = 88;
        public const int Key_Y = 89;
        public const int Key_Z = 90;

        //Others
        public const int Key_Ctrl = 17;
        public const int Key_Del = 46;
        public const int Key_Esc = 27;
    }
    

    class CustomMenuStrip : MenuStrip
    {
        protected override void WndProc(ref Message m)
        {
            const int WM_KEYDOWN = 0x0100;
            const int WM_SYSKEYDOWN = 0x0104;
            const int HTTRANSPARENT = (-1);

            if (m.Msg == WM_KEYDOWN || m.Msg == WM_SYSKEYDOWN)
            {
                m.Result = (IntPtr)HTTRANSPARENT;
            }
            else
            {
                base.WndProc(ref m);
            }
        }
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
