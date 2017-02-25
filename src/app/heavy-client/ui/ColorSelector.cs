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
        Bitmap bmp;
        bool wantedChange = false;
        bool usingDefault = false;

        public ColorSelector(Window parent, int currentPieceChange)
        {
            InitializeComponent();
            parent_ = parent;
            bmp = (Bitmap)colorPicture.Image;

            currentPieceChange_ = currentPieceChange;

            if (!FonctionsNatives.getUsingDefaultMaterialForPiece(currentPieceChange_))
            {
                int[] color = FonctionsNatives.getPieceColor(4, currentPieceChange_);
                oldColor_ = Color.FromArgb(color[0], color[1], color[2], color[3]);
            }
            else
                usingDefault = true;

        }

        private void applyButton_Click(object sender, EventArgs e)
        {
            wantedChange = true;
            oldColor_ = newColor_;
            FonctionsNatives.setUsingDefaultMaterialForPiece(currentPieceChange_, false);
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            newColor_ = oldColor_;
            FonctionsNatives.changePieceColor(currentPieceChange_, oldColor_.A, oldColor_.R, oldColor_.G, oldColor_.B);
        }

        private bool inColorCanvas(int X, int Y)
        {
            if (X > 0 && X < colorPicture.Width && Y > 0 && Y < colorPicture.Height)
                return true;

            return false;
        }

        private void colorPicture_MouseMove(object sender, MouseEventArgs e)
        {
            int X = e.X;
            int Y = e.Y;

            if (e.Button == MouseButtons.Left && inColorCanvas(X, Y))
            {
                newColor_ = bmp.GetPixel(X, Y);
                FonctionsNatives.changePieceColor(currentPieceChange_, newColor_.A, newColor_.R, newColor_.G, newColor_.B);
            }
        }

        public void applyChanges()
        {
            //Didn't click on apply
            if (wantedChange && usingDefault)
            {
                FonctionsNatives.changePieceColor(currentPieceChange_, oldColor_.A, oldColor_.R, oldColor_.G, oldColor_.B);
            }
            else
            {
                FonctionsNatives.setUsingDefaultMaterialForPiece(currentPieceChange_, true);
            }
        }
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getUsingDefaultMaterialForPiece(int piece);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setUsingDefaultMaterialForPiece(int piece, bool value);
        

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changePieceColor(int piece, int a, int r, int g, int b);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getPieceColor(int piece);
        public static int[] getPieceColor(int taille, int piece)
        {
            int[] limitesParametres = new int[taille];
            Marshal.Copy(getPieceColor(piece), limitesParametres, 0, taille);
            return limitesParametres;
        }
    }
}
