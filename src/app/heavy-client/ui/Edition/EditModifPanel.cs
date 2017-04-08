using System;
using System.Windows.Forms;

namespace ui
{
    public partial class EditModifPanel : UserControl
    {
        TextBox dimension_;
        TextBox rotation_;
        TextBox Xposition_;
        TextBox Yposition_;

        public const double minY = -48;
        public const double maxY = 48;

        public const double minX = -96;
        public const double maxX = 96;

        public EditModifPanel()
        {
            InitializeComponent();
        }

        public virtual void init(TextBox dimension, TextBox rotation, TextBox Xposition, TextBox Yposition)
        {
            dimension_ = dimension;
            rotation_ = rotation;
            Xposition_ = Xposition;
            Yposition_ = Yposition;

            dimension_.GotFocus += OnFocus;
            dimension_.LostFocus += OnDefocus;

            rotation_.GotFocus += OnFocus;
            rotation_.LostFocus += OnDefocus;

            Xposition_.GotFocus += OnFocus;
            Xposition_.LostFocus += OnDefocus;

            Yposition_.GotFocus += OnFocus;
            Yposition_.LostFocus += OnDefocus;
        }

        public virtual void mettreAJourInformation()
        {
            dimension_.Text = FonctionsNatives.obtenirFacteurGrandeur().ToString();
            rotation_.Text = FonctionsNatives.obtenirAngleRotation().ToString();
            Xposition_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();
            Yposition_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();
        }

        public virtual void OnFocus(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(false);
        }

        public virtual void OnDefocus(object sender, EventArgs e)
        {
            FonctionsNatives.assignerAutorisationInputClavier(true);
            mettreAJourInformation();
        }

        public virtual void dimension_keyDown()
        {
            double donnee = 0.0;
            if (!double.TryParse(dimension_.Text, out donnee))
            {
                //handle bad input
                donnee = FonctionsNatives.obtenirFacteurGrandeur();
            }
            FonctionsNatives.assignerFacteurGrandeur(donnee);
            mettreAJourInformation();
            dimension_.Select(dimension_.Text.Length, 0);
        }

        public virtual void rotation_keyDown()
        {
            double donnee = 0.0;
            if (!double.TryParse(rotation_.Text, out donnee))
            {
                //handle bad input
                donnee = FonctionsNatives.obtenirAngleRotation();
            }
            FonctionsNatives.assignerAngleRotation(donnee);
            mettreAJourInformation();
            rotation_.Select(rotation_.Text.Length, 0);
        }

        public virtual void Xposition_keyDown()
        {
            double donnee = 0.0;
            if (!double.TryParse(Xposition_.Text, out donnee))
            {
                //handle bad input
                donnee = FonctionsNatives.obtenirPositionRelativeX();
            }

            if (!(donnee < minX || donnee > maxX))
            {
                FonctionsNatives.assignerPositionRelativeX(donnee);
            }
            else
                Xposition_.Text = FonctionsNatives.obtenirPositionRelativeX().ToString();

            mettreAJourInformation();
            Xposition_.Select(Xposition_.Text.Length, 0);
        }

        public virtual void Yposition_keyDown()
        {
            double donnee = 0.0;
            if (!double.TryParse(Yposition_.Text, out donnee))
            {
                //handle bad input
                donnee = FonctionsNatives.obtenirPositionRelativeY();
            }

            if (!(donnee < minY || donnee > maxY))
            {
                FonctionsNatives.assignerPositionRelativeY(donnee);
            }
            else
                Yposition_.Text = FonctionsNatives.obtenirPositionRelativeY().ToString();

            mettreAJourInformation();
            Yposition_.Select(Yposition_.Text.Length, 0);
        }
    }
}
