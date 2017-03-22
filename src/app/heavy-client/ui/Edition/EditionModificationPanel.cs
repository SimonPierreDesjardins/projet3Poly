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
    public partial class EditionModificationPanel : UserControl
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
        public EditionModificationPanel(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            textboxDimension_.GotFocus += OnFocus;
            textboxDimension_.LostFocus += OnDefocus;

            textBoxRotation_.GotFocus += OnFocus;
            textBoxRotation_.LostFocus += OnDefocus;

            textBoxPositionX_.GotFocus += OnFocus;
            textBoxPositionX_.LostFocus += OnDefocus;

            textBoxPositionY_.GotFocus += OnFocus;
            textBoxPositionY_.LostFocus += OnDefocus;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OnFocus(object sender, MeasureItemEventArgs e)
        ///
        /// Evenement quand le control est utiliser
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OnFocus(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OnDefocus(object sender, MeasureItemEventArgs e)
        ///
        /// Evenement quand le control n'est plus utiliser
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OnDefocus(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
            mettreAJourInformation();
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
                double donnee = 0.0;
                if (!double.TryParse(textboxDimension_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirFacteurGrandeur();
                }
                FonctionsNatives.assignerFacteurGrandeur(donnee);
                mettreAJourInformation();
                textboxDimension_.Select(textboxDimension_.Text.Length, 0);
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
                double donnee = 0.0;
                if (!double.TryParse(textBoxRotation_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirAngleRotation();
                }
                FonctionsNatives.assignerAngleRotation(donnee);
                mettreAJourInformation();
                textBoxRotation_.Select(textBoxRotation_.Text.Length, 0);
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
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionX_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeX();
                }

                if (!(donnee < -47 || donnee > 47))
                    FonctionsNatives.assignerPositionRelativeX(donnee);
                else
                    textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();

                mettreAJourInformation();
                textBoxPositionX_.Select(textBoxPositionX_.Text.Length, 0);
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
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionY_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeY();
                }

                if (!(donnee < -23 || donnee > 23))
                    FonctionsNatives.assignerPositionRelativeY(donnee);
                else
                    textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();

                mettreAJourInformation();
                textBoxPositionY_.Select(textBoxPositionY_.Text.Length, 0);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void mettreAJourInformation()
        ///
        /// Met à jour les informations dans le panneau d'opération
        ///
        ////////////////////////////////////////////////////////////////////////
        public void mettreAJourInformation()
        {
            textboxDimension_.Text = FonctionsNatives.obtenirFacteurGrandeur().ToString();
            textBoxRotation_.Text = FonctionsNatives.obtenirAngleRotation().ToString();
            textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
            textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
        }
    }
}


