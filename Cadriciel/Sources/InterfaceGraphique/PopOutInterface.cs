using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    public partial class PopOutInterface : Form
    {
        public PopOutInterface()
        {
            InitializeComponent();
            int mode = FonctionsNatives.obtenirMode();
            switch(mode)
            {
                case 1:
                    infoText_.Text = mode.ToString();
                    break;

                case 2:
                    //Rapport délicitation Annexe A
                    infoText_.Text = mode.ToString();
                    break;

                case 3:
                    infoText_.Text = mode.ToString();
                    break;

                case 4:
                    infoText_.Text = mode.ToString();
                    break;

                case 5:
                    infoText_.Text = mode.ToString();
                    break;

                default:
                    infoText_.Text = mode.ToString();
                    break;
            }
            
        }
    }
}
