////////////////////////////////////////////////
/// @file   EditionModificationPanel.cs
/// @author Frédéric Grégoire
/// @date   2017-03-05
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;

namespace ui
{
    public partial class EditionModificationPanel : EditModifPanel
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EditionModificationPanel(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public EditionModificationPanel(Window parent) : base()
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
                base.dimension_keyDown();
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
                base.rotation_keyDown();
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
            base.Xposition_keyDown();
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
            base.Yposition_keyDown();
        }
    }
}


