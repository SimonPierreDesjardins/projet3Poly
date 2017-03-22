///////////////////////////////////////////////////////////////////////////////
/// @file NouveauFichier.cs
/// @author Philippe Marcotte
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
    public partial class NouveauFichier : Form
    {
        /// <summary>
        /// Chemin vers le fichier contenant la zone par defaut
        /// </summary>
        private String cheminFichierZoneDefaut;

        /// <summary>
        /// Chemin vers le dossier contenant les fichiers de zones
        /// </summary>
        private String cheminDossierZone;

        /// <summary>
        /// Nom du fichier à créer
        /// </summary>
        private String nomFichier;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public String NomFichier
        ///
        /// Retourne le nom du fichier à sauvegarder.
        ///
        /// @return String
        ///
        ////////////////////////////////////////////////////////////////////////
        public String NomFichier
        {
            get
            {
                return nomFichier;
            }
        }

        /// <summary>
        /// Extension d'un fichier de type zone
        /// </summary>
        private String extensionFichierZone;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public NouveauFichier()
        ///
        /// Constructeur par défaut
        /// Initialise les composantes du formulaires.
        ///
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public NouveauFichier()
        {
            StringBuilder str = new StringBuilder(100);
            FonctionsNatives.obtenirCheminFichierZoneDefaut(str, str.Capacity);
            cheminFichierZoneDefaut = str.ToString();
            cheminDossierZone = cheminFichierZoneDefaut.Substring(0, cheminFichierZoneDefaut.LastIndexOf("/") + 1);
            extensionFichierZone = cheminFichierZoneDefaut.Substring(cheminFichierZoneDefaut.LastIndexOf("."));
            InitializeComponent();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void creerFichierButt_Click(object sender, EventArgs e)
        ///
        /// Fonction appelée lorsque l'évènement du click du bouton "OK" est déclenché.
        /// Celle-ci assigne le nom entré par l'utilisateur à la variable nomFichier et crée le fichier s'il n'existe pas déjà.
        ///
        /// @param[in] senders : Objet ayant déclenché l'évenement
        /// @param[in] e : Paramèetre en lien avec l'évènement
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void creerFichierButt_Click(object sender, EventArgs e)
        {
            nomFichier = nomFichierTextBox.Text;
            if (nomFichier != "")
            {
                if (System.IO.File.Exists(System.IO.Path.GetFullPath(cheminDossierZone + nomFichier + extensionFichierZone)))
                {
                    MessageBox.Show("Vous ne pouvez pas nommer votre fichier ainsi car le fichier existe déjà.", "Nom déjà utilisé", MessageBoxButtons.OK);
                    return;
                }
                DialogResult = DialogResult.OK;
                System.IO.File.Create(cheminDossierZone + nomFichier + extensionFichierZone).Dispose();
            }
            Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void annulerCreerFichierButt_Click(object sender, EventArgs e)
        ///
        /// Fonction appelée lorsque l'évènement du click du bouton "Annuler" est déclenché.
        /// Celle-ci ferme la fenetre.
        ///
        /// @param[in] senders : Objet ayant déclenché l'évenement
        /// @param[in] e : Paramèetre en lien avec l'évènement
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        private void annulerCreerFichierButt_Click(object sender, EventArgs e)
        {
            Close();
        }

        static partial class FonctionsNatives
        {
            [System.Runtime.InteropServices.DllImport(@"model.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
            public static extern void obtenirCheminFichierZoneDefaut(StringBuilder str, int longueur);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////