////////////////////////////////////////////////
/// @file   ColorSelector.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System;

namespace ui
{
    public partial class ColorSelector : UserControl
    {
        Color oldColor_;
        Color newColor_;
        int currentPieceChange_;
        Bitmap bmp;
        bool wantedChange = false;
        bool usingDefault = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ColorSelector(Window parent, int currentPieceChange)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// @parem int currentPieceChange: int indiquant le numero de la piece qui est modifier
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ColorSelector(int currentPieceChange)
        {
            InitializeComponent();
            bmp = (Bitmap)colorPicture.Image;

            currentPieceChange_ = currentPieceChange;

            if (currentPieceChange == (int)VehiculePiece.VehiculePiece.BODY)
                controlDescription.Text = "Choix de couleur pour le chasis";

            if (!FonctionsNatives.getUsingDefaultMaterialForPiece(currentPieceChange_))
            {
                int[] color = FonctionsNatives.getPieceColor(4, currentPieceChange_);
                oldColor_ = Color.FromArgb(color[0], color[1], color[2], color[3]);
            }
            else
                usingDefault = true;

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyButton_Click(object sender, EventArgs e)
        ///
        /// Applique la couleur choisi et la conserve en mémoire.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void applyButton_Click(object sender, EventArgs e)
        {
            wantedChange = true;
            oldColor_ = newColor_;
            FonctionsNatives.setUsingDefaultMaterialForPiece(currentPieceChange_, false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cancelButton_Click(object sender, EventArgs e)
        ///
        /// Annule la couleur choisi et la remet l'ancienne couleur qui était en
        /// mémoire
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cancelButton_Click(object sender, EventArgs e)
        {
            if (newColor_ != oldColor_)
            {
                newColor_ = oldColor_;
                if (oldColor_.A == 0) 
                {
                    FonctionsNatives.setUsingDefaultMaterialForPiece(currentPieceChange_, true);
                }
                else
                {
                    FonctionsNatives.changePieceColor(currentPieceChange_, oldColor_.A, oldColor_.R, oldColor_.G, oldColor_.B);
                }
            }     
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool inColorCanvas(int X, int Y)
        ///
        /// Indique sa la position X et Y est à l'intérieur du colorCanvas.
        /// 
        /// @param int X: position en X du curseur
        /// @param int Y: position en Y du curseur
        /// 
        /// @return bool: vrai si à l'intérieur, faux sinon
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool inColorCanvas(int X, int Y)
        {
            if (X > 0 && X < colorPicture.Width && Y > 0 && Y < colorPicture.Height)
                return true;

            return false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void colorPicture_MouseMove(object sender, EventArgs e)
        ///
        /// Change la couleur lorsqu'il y a un déplacement de la souris sur le color
        /// canvas et que le click gauche est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du mouvement de souris
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void colorPicture_Click(object sender, EventArgs e)
        ///
        /// Change la couleur lorsqu'il y a un click de la souris sur le color
        /// canvas et que le click gauche est appuyé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void colorPicture_Click(object sender, EventArgs e)
        {

            MouseEventArgs me = (MouseEventArgs)e;
            Point coordinates = me.Location;

            newColor_ = bmp.GetPixel(coordinates.X, coordinates.Y);
            FonctionsNatives.changePieceColor(currentPieceChange_, newColor_.A, newColor_.R, newColor_.G, newColor_.B);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void applyChanges(object sender, EventArgs e)
        ///
        /// Applique les changements si lu bouton apply à été appuyer. Sinon l'ancienne
        /// couleur en mémoire est appliquée.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        public void applyChanges()
        {
            //Didn't click on apply
            if (!wantedChange && usingDefault)
            {
                FonctionsNatives.setUsingDefaultMaterialForPiece(currentPieceChange_, true);
            }
            else
            {
                FonctionsNatives.changePieceColor(currentPieceChange_, oldColor_.A, oldColor_.R, oldColor_.G, oldColor_.B);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn FonctionsNatives
    ///
    /// Communication avec le modèle C++
    ///
    ////////////////////////////////////////////////////////////////////////
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
