////////////////////////////////////////////////
/// @file   CustomClass.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ui
{
    public partial class TabControlWithoutHeader : TabControl
    {
        public TabControlWithoutHeader()
        {
            
        }

       // private const int TCM_ADJUSTRECT = 0x1328;

        /*protected override void WndProc(ref Message m)
        {
            //Hide the tab headers at run-time
            if (m.Msg == TCM_ADJUSTRECT)
            {

                RECT rect = (RECT)(m.GetLParam(typeof(RECT)));
                rect.Left = this.Left - this.Margin.Left;
                rect.Right = this.Right + this.Margin.Right - 2;

                rect.Top = this.Top - this.Margin.Top + 2;
                rect.Bottom = this.Bottom + this.Margin.Bottom - 1;
                Marshal.StructureToPtr(rect, m.LParam, true);
                //m.Result = (IntPtr)1;
                //return;
            }
            //else
            // call the base class implementation
            base.WndProc(ref m);
        }*/

       /* private struct RECT
        {
            public int Left, Top, Right, Bottom;
        }*/
    }


    public class CustomLabel : Label
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

    public class PanelButton : Panel
    {
        public ToolTip toolTip;

        public PanelButton()
        {
            toolTip = new ToolTip();
        }

        protected override void OnClick(EventArgs e)
        {
            base.OnClick(e);
            this.Focus();
        }

        protected override void OnMouseEnter(EventArgs e)
        {
            //When not selected
            if (this.BackColor != Color.FromArgb(0,102,204))
            {
                BackColor = System.Drawing.Color.FromArgb(36, 42, 49);
                foreach (Control c in this.Controls)
                {
                    if (c.GetType() == typeof(CustomLabel))
                    {
                        c.ForeColor = Color.FromArgb(0, 102, 204);
                    }
                }
            }

            foreach (Control c in this.Controls)
            {
                if (c.GetType() == typeof(PictureBox))
                {
                    var tipstring = toolTip.GetToolTip(c);
                    toolTip.Show(tipstring, c, this.Width, c.Height / 2);
                    toolTip.Tag = c;
                }
            }
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            Control ctrl = toolTip.Tag as Control;
            if (ctrl != null)
            {
                toolTip.Hide(ctrl);
                toolTip.Tag = null;
            }

            if (this.BackColor != Color.FromArgb(0,102,204))
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
}
