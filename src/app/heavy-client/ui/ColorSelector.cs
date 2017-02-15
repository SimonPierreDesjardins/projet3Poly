using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System;
using VehiculePiece;

namespace ui
{
    public partial class ColorSelector : UserControl
    {
        Window parent_;
        Color oldColor_;
        Color newColor_;
        int currentPieceChange_;

        public ColorSelector(Window parent, int currentPieceChange)
        {
            InitializeComponent();
            parent_ = parent;

            currentPieceChange_ = currentPieceChange;
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            newColor_ = GetPixelColor(e.X, e.Y);
            FonctionsNatives.changePieceColor(currentPieceChange_, newColor_.A, newColor_.R, newColor_.G, newColor_.B);
        }

        static public System.Drawing.Color GetPixelColor(int x, int y)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            uint pixel = GetPixel(hdc, x, y);
            ReleaseDC(IntPtr.Zero, hdc);
            Color color = Color.FromArgb((int)(pixel & 0x000000FF),
                         (int)(pixel & 0x0000FF00) >> 8,
                         (int)(pixel & 0x00FF0000) >> 16);
            return color;
        }

        [DllImport("user32.dll")]
        static extern IntPtr GetDC(IntPtr hwnd);

        [DllImport("user32.dll")]
        static extern Int32 ReleaseDC(IntPtr hwnd, IntPtr hdc);

        [DllImport("gdi32.dll")]
        static extern uint GetPixel(IntPtr hdc, int nXPos, int nYPos);

        private void applyButton_Click(object sender, EventArgs e)
        {

        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            newColor_ = oldColor_;
        }
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changePieceColor(int piece, int a, int r, int g, int b);


    }
}
