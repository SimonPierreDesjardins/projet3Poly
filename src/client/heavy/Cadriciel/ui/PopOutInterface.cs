////////////////////////////////////////////////
/// @file   PopOutInterface.cs
/// @author Frédéric Grégoire
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
            
            infoText_.Text = ("Ce text se met à jour pour vous aider selon le mode dans lequel vous êtes.\n\n"+ 
            "Flèche droite          Déplacement de la fenêtre virtuelle vers la droite.\n"+ 
            "Flèche gauche       Déplacement de la fenêtre virtuelle vers la gauche.\n"+
            "Flèche bas             Déplacement de la fenêtre virtuelle vers le bas.\n"+
            "Flèche haut            Déplacement de la fenêtre virtuelle vers le haut.\n\n "+
            "+/-                         Zoom avant / arrière.\n"+
            "Supprimer              Supprime les objets sélectionnés.\n"+
            "D                            Choisit l'outil de déplacement.\n"+
            "S                            Choisit l'outil de sélection.\n"+
            "R                            Choisit l'outil de rotation.\n"+
            "E                            Choisit l'outil de rotation.\n"+
            "C                            Choisit l'outil de duplication.\n"+
            "Z                            Choisit l'outil de zoom.\n"+
            "T                            Baslcule en mode test.\n\n"+
            "CTRL - S                Savegarde la scène dans le fichier.\n"+
            "CTRL - N                Réinitialise l'environnement d'édition avec une nouvelle scène.\n"+
            "CTRL - O                Choisi une scène sauvegardé et l'affiche.\n"+
            "1                             Choisit la caméra orthographique.\n"+
            "2                             Choisit la caméra orbite.");
        }
    }
}
