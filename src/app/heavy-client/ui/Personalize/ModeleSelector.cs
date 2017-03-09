////////////////////////////////////////////////
/// @file   ModeleSelector.cs
/// @author Frédéric Grégoire
/// @date   2017-03-02
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ui
{
    public partial class ModeleSelector : UserControl
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ModeleSelector()
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ModeleSelector()
        {
            InitializeComponent();

            switch (FonctionsNatives.getModele())
            {
                case "robot":
                    robotButton.BackColor = Color.FromArgb(0, 102, 204);
                    break;
                case "audi":
                    audiButton.BackColor = Color.FromArgb(0, 102, 204);
                    break;
                case "truck":
                    truckButton.BackColor = Color.FromArgb(0, 102, 204);
                    break;
                case "f1":
                    f1Button.BackColor = Color.FromArgb(0, 102, 204);
                    break;
                default:
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void robotButton_Click(object sender, EventArgs e)
        ///
        /// Applique la couleur choisi au boutton et change le modele pour le robot
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void robotButton_Click(object sender, EventArgs e)
        {
            setDefaultColor();
            FonctionsNatives.setModele("robot");
            robotButton.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void audiButton_Click(object sender, EventArgs e)
        ///
        /// Applique la couleur choisi au boutton et change le modele pour la audi
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void audiButton_Click(object sender, EventArgs e)
        {
            setDefaultColor();
            FonctionsNatives.setModele("audi");
            audiButton.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void truckButton_Click(object sender, EventArgs e)
        ///
        /// Applique la couleur choisi au boutton et change le modele pour le camion
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void truckButton_Click(object sender, EventArgs e)
        {
            setDefaultColor();
            FonctionsNatives.setModele("truck");
            truckButton.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void f1Button_Click(object sender, EventArgs e)
        ///
        /// Applique la couleur choisi au boutton et change le modele pour la f1
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void f1Button_Click(object sender, EventArgs e)
        {
            setDefaultColor();
            FonctionsNatives.setModele("f1");
            f1Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setDefaultColor()
        ///
        /// Remet la couleur par défaut pour tous les bouttons
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setDefaultColor()
        {
            robotButton.BackColor = Color.Transparent;
            audiButton.BackColor = Color.Transparent;
            truckButton.BackColor = Color.Transparent;
            f1Button.BackColor = Color.Transparent;
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
        public static extern void setModele(String modele);

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void getModele(StringBuilder str, int longueur);
        public static string getModele()
        {
            StringBuilder str = new StringBuilder(100);
            getModele(str, str.Capacity);
            return str.ToString();
        }
    }
}
