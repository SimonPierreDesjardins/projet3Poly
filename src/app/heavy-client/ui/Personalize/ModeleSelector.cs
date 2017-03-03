using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ui
{
    public partial class ModeleSelector : UserControl
    {
        String modele_;

        public ModeleSelector()
        {
            InitializeComponent();

            //modele_ = FonctionsNatives.getModele();
        }

        private void robotButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.setModele("robot");
        }

        private void audiButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.setModele("audi");
        }

        private void truckButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.setModele("truck");
        }

        private void f1Button_Click(object sender, EventArgs e)
        {
            FonctionsNatives.setModele("f1");
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
        public static extern String getModele();
    }
}
