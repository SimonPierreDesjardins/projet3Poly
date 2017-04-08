////////////////////////////////////////////////
/// @file   TutorialEditionModificationPanel.cs
/// @author Frédéric Grégoire
/// @date   2017-03-05
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ui
{
    public partial class TutorialEditionModificationPanel : EditModifPanel
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public TutorialEditionModificationPanel(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public TutorialEditionModificationPanel(Window parent) : base()
        {
            InitializeComponent();
            init(textboxDimension_, textBoxRotation_, textBoxPositionX_, textBoxPositionY_);
            parent_ = parent;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textboxDimension__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textboxDimension__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string tmp = textboxDimension_.Text;
                base.dimension_keyDown();
                if (tmp.Equals(textboxDimension_.Text))
                    parent_.editionTutorielInstructions.nextState();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotation__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxRotation__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string tmp = textBoxRotation_.Text;
                base.rotation_keyDown();
                if (tmp.Equals(textBoxRotation_.Text))
                    parent_.editionTutorielInstructions.nextState();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionX__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionX__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string tmp = textBoxPositionX_.Text;
                base.Xposition_keyDown();
                if (tmp.Equals(textBoxPositionX_.Text))
                    parent_.editionTutorielInstructions.nextState();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxPositionY__KeyDown(object sender, EventArgs e)
        ///
        /// Lorsque la touche Enter du clavier est appuyé et que cette fenêtre à le focus
        /// les données sont envoyées au modèle et vérifie que l'objet est toujours sur la 
        /// table
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param KeyEventsArgs e: evenement du clavier
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxPositionY__KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string tmp = textBoxPositionY_.Text;
                base.Yposition_keyDown();
                if (tmp.Equals(textBoxPositionY_.Text))
                    parent_.editionTutorielInstructions.nextState();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void ajusteToMode()
        ///
        /// Rend les controls enable ou disable selon le stade du tutoriel edition
        ///
        ////////////////////////////////////////////////////////////////////////
        public void ajusteToMode()
        {
            int state = parent_.editionTutorielInstructions.GetState();
            switch (state)
            {
                case (int)EditionTutorial.State.APPLYING_SCALE:
                    textboxDimension_.Enabled = true;
                    break;

                case (int)EditionTutorial.State.APPLYING_ROTATION:
                    textBoxRotation_.Enabled = true;
                    break;

                case (int)EditionTutorial.State.APPLYING_MOVE:
                    textBoxPositionX_.Enabled = true;
                    textBoxPositionY_.Enabled = true;
                    break;

                default:
                    DisableAllControls();
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void DisableAllControls()
        ///
        /// Desactive tous les controles pour la modification d'un objet
        ///
        ////////////////////////////////////////////////////////////////////////
        private void DisableAllControls()
        {
            textboxDimension_.Enabled = false;
            textBoxRotation_.Enabled = false;
            textBoxPositionX_.Enabled = false;
            textBoxPositionY_.Enabled = false;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    ///
    /// @fn  static partial class FonctionsNatives
    ///
    /// Permet de faire le lien avec les méthodes implémentées dans le C++
    ///
    ////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirAngleRotation();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirFacteurGrandeur();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeX();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionRelativeY();
    }
}


