using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ui
{
    public partial class TutorialEditionModificationPanel : UserControl
    {
        Window parent_;

        public TutorialEditionModificationPanel(Window parent)
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

        private void OnFocus(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

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
            string tmp = textboxDimension_.Text;
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
                if (tmp.Equals(textboxDimension_.Text))
                    parent_.editionTutorielInstructions.nextState();
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
            string tmp = textBoxRotation_.Text;
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
                if (tmp.Equals(textBoxRotation_.Text))
                    parent_.editionTutorielInstructions.nextState();
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
            string tmp = textBoxPositionX_.Text;
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionX_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeX();
                }

                if (!(donnee < -47 || donnee > 47))
                {
                    FonctionsNatives.assignerPositionRelativeX(donnee);
                }   
                else
                    textBoxPositionX_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();

                mettreAJourInformation();
                if (tmp.Equals(textBoxPositionX_.Text))
                    parent_.editionTutorielInstructions.nextState();
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
            string tmp = textBoxPositionY_.Text;
            if (e.KeyCode == Keys.Enter)
            {
                double donnee = 0.0;
                if (!double.TryParse(textBoxPositionY_.Text, out donnee))
                {
                    //handle bad input
                    donnee = FonctionsNatives.obtenirPositionRelativeY();
                }

                if (!(donnee < -23 || donnee > 23))
                {
                    FonctionsNatives.assignerPositionRelativeY(donnee);
                }  
                else
                    textBoxPositionY_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();

                mettreAJourInformation();
                if (tmp.Equals(textBoxPositionY_.Text))
                    parent_.editionTutorielInstructions.nextState();
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


