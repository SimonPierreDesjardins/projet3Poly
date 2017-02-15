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

            //Doit aller get les couleurs courrantes des pieces

            currentPieceChange_ = currentPieceChange;
        }

        private void applyButton_Click(object sender, EventArgs e)
        {
            oldColor_ = newColor_;
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            newColor_ = oldColor_;
        }

        private void colorPicture_MouseClick(object sender, MouseEventArgs e)
        {
            Bitmap bmp = (Bitmap)colorPicture.Image;
            newColor_ = bmp.GetPixel(e.X, e.Y);
            FonctionsNatives.changePieceColor(currentPieceChange_, newColor_.A, newColor_.R, newColor_.G, newColor_.B);
        }
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changePieceColor(int piece, int a, int r, int g, int b);
    }
}
