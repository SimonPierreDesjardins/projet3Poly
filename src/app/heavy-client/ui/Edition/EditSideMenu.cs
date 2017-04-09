using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class EditSideMenu : UserControl
    {
        PictureBox picBox_;
        PanelButton toolButton_;

        public EditSideMenu()
        {
            InitializeComponent();
        }

        public virtual void init(PictureBox picBox, PanelButton toolButton)
        {
            picBox_ = picBox;
            toolButton_ = toolButton;
        }

        public virtual void disableDuplication()
        {
            toolButton_.Enabled = false;
            picBox_.Image = ChangeColor((Bitmap)picBox_.Image, Color.Gray);
        }

        public virtual void enableDuplication()
        {
            toolButton_.Enabled = true;
            picBox_.Image = ChangeColor((Bitmap)picBox_.Image, Color.White);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        ///
        /// Change la couleur d'un image par une nouvelle couleur.
        /// 
        /// @param Bitmap scrBitmap: le bitmap de l'image qui doit être modifié
        /// @param Color newColor: La nouvelle couleur de l'image
        ///
        ////////////////////////////////////////////////////////////////////////
        public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        {
            Color actualColor;
            //make an empty bitmap the same size as scrBitmap
            Bitmap newBitmap = new Bitmap(scrBitmap.Width, scrBitmap.Height);
            for (int i = 0; i < scrBitmap.Width; i++)
            {
                for (int j = 0; j < scrBitmap.Height; j++)
                {
                    //get the pixel from the scrBitmap image
                    actualColor = scrBitmap.GetPixel(i, j);
                    // > 150 because.. Images edges can be of low pixel colr. if we set all pixel color to new then there will be no smoothness left.
                    if (actualColor.A > 175)
                        newBitmap.SetPixel(i, j, newColor);
                    //else
                    //newBitmap.SetPixel(i, j, actualColor);
                }
            }
            return newBitmap;
        }

    }
}
