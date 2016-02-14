////////////////////////////////////////////////
/// @file   PopOutInterface.cs
/// @author INF2990
/// @date   2016-02-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
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
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PopOutInterface()
        ///
        /// Cette fonction initialize le popout et lui assigne un text sur son label
        ///
        ////////////////////////////////////////////////////////////////////////
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
                    infoText_.Text = ("Ce text se met à jour pour vous aider selon le mode dans lequel vous êtes.\n\n"+ 
                    "Flèche droite      Déplacement de la fenêtre virtuelle vers la droite.\n"+ 
                    "Flèche gauche      Déplacement de la fenêtre virtuelle vers la gauche.\n"+
                    "Flèche bas         Déplacement de la fenêtre virtuelle vers le bas.\n"+
                    "Flèche haut        Déplacement de la fenêtre virtuelle vers le haut.\n\n "+
                    "+/-            Zoom avant / arrière\n"+
                    "Supprimer      Supprime les objets sélectionnés.\n"+
                    "d              Choisit l'outil de déplacement\n"+
                    "s              Choisit l'outil de sélection.\n"+
                    "r              Choisit l'outil de rotation.\n"+
                    "e              Choisit l'outil de rotation.\n"+
                    "c              Choisit l'outil de duplication.\n"+
                    "z              Choisit l'outil de zoom.\n"+
                    "t              Baslcule en mode test.\n\n"+
                    "CTRL-s         Savegarde la scène dans le fichier.\n"+
                    "CTRL-n         Réinitialise l'environnement d'édition avec une nouvelle scène.\n"+
                    "CTRL-o         Choisi une scène sauvegardé et l'affiche\n"+
                    "1              Choisit la caméra orthographique\n"+
                    "2              Choisit la caméra orbite");
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
