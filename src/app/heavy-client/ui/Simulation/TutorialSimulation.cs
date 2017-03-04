using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class TutorialSimulation : UserControl
    {
        //Définition des states
        const int INTRODUCTION = 0;
        const int MOUVEMENT = 1;
        const int CAMERA_ORTHO = 2;
        const int CAMERA_ORBITE = 3;
        const int CAMERA_FIRSTPERSO = 4;
        const int LIGHTS = 5;
        const int CONCLUSION = 6;

        int state_;
        Window parent_;

        public TutorialSimulation(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            parent_ = parent;
            FonctionsNatives.assignerAutorisationInputClavier(false);
            FonctionsNatives.assignerAutorisationInputSouris(false);

            state_ = 0;
            switchInstruction();
            previousButton.Visible = false;

            instructionBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            instructionBox.MeasureItem += instructionBox_MeasureItem;
            instructionBox.DrawItem += instructionBox_DrawItem;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void instructionBox_MeasureItem(object sender, MeasureItemEventArgs e)
        ///
        /// Sert à calculer la longueur d'une chaine de string dans la liste box
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param MesureItemEventArgs e: evenement pour mesure la grandeur
        ///
        ////////////////////////////////////////////////////////////////////////
        private void instructionBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            e.ItemHeight = (int)e.Graphics.MeasureString(instructionBox.Items[e.Index].ToString(), 
                                                        instructionBox.Font, instructionBox.Width).Height;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void instructionBox_DrawItem(object sender, MeasureItemEventArgs e)
        ///
        /// Sert à dessiner les strings dans la listebox et de faire un "wrap" sur celle-ci
        /// quand elles sont trop longue pour une ligne
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param DrawItemEventArgs e: evenement pour dessiner le control
        ///
        ////////////////////////////////////////////////////////////////////////
        private void instructionBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.DrawFocusRectangle();
            if (e.Index != -1)
                e.Graphics.DrawString(instructionBox.Items[e.Index].ToString(), e.Font, new SolidBrush(e.ForeColor), e.Bounds);
        }

        private void switchInstruction()
        {
            switch(state_)
            {
                case INTRODUCTION:
                    introductionState();
                    break;

                case MOUVEMENT:
                    mouvementState();
                    break;

                case CAMERA_ORTHO:
                    cameraOrthoState();
                    break;

                case CAMERA_ORBITE:
                    cameraOrbiteState();
                    break;

                case CAMERA_FIRSTPERSO:
                    cameraFirstPersoState();
                    break;

                case LIGHTS:
                    lightsState();
                    break;

                case CONCLUSION:
                    conclusionState();
                    break;

                default:
                    break;
            }
        }

        private void introductionState()
        {
            instructionBox.Items.Clear();
            string instruction = "Bienvenu au tutoriel pour le mode simulation! \n" +
                                 "Comme vous avez pu le constater, lorsque vous choississez ce mode," +
                                 "l'application vous demande une carte à charger. Vous pouvez donc sélectionner la carte de votre choix. \n";
            instructionBox.Items.Add(instruction);
        }

        private void mouvementState()
        {
            instructionBox.Items.Clear();
            string instruction = "Pour déplacer votre robot dans la zone de simulation vous devez appuyer sur les touches suivantes : \n" +
                                 "Pour avancer : \n" +
                                 "Pour tourner vers la gauche : \n" +
                                 "Pour tourner vers la droite : \n" +
                                 "Pour reculer : \n" +
                                 "Ces touches dépendent de votre profil qui peut être changé à partir du menu principal dans l'option 'Configuration'";
            instructionBox.Items.Add(instruction);
        }

        private void cameraOrthoState()
        {
            instructionBox.Items.Clear();
            string instruction = "Il y a trois types de caméra disponible dans le mode simulation. \n" +
                                 "La première est la caméra orthographique. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation de haut en bas." +
                                 "Pour déplacer la caméra il suffit de maintenir le boutton droit de la souris enfoncé et se déplacer." +
                                 "On peut également ajuste la distance de la caméra avec la molette de la souris";
            instructionBox.Items.Add(instruction);
        }

        private void cameraOrbiteState()
        {
            instructionBox.Items.Clear();
            string instruction = "Le deuxième type de caméra est la caméra orbite. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation de tous les angles possible. \n" +
                                 "Pour déplacer la caméra il suffit de maintenir le boutton droit de la souris enfoncé et se déplacer." +
                                 "Un mouvement de gauche à droite fera déplacer la caméra horizontalement, tandis qu'un mouvement de haut en bas " +
                                 "fera déplacer la caméra verticalement. \n" + 
                                 "On peut également ajuste la distance de la caméra avec la molette de la souris";
            instructionBox.Items.Add(instruction);
        }

        private void cameraFirstPersoState()
        {
            instructionBox.Items.Clear();
            string instruction = "Le troisème type de caméra est la caméra permière personne. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation sous l'angle d'un conducteur fictif. \n" +
                                 "Cette caméra se déplace automatiquement avec le déplacement du véhicule. Il n'est pas possible de l'ajuster autrement";
            instructionBox.Items.Add(instruction);
        }

        private void lightsState()
        {
            instructionBox.Items.Clear();
            string instruction = "Lumière";
            instructionBox.Items.Add(instruction);
        }

        private void conclusionState()
        {
            instructionBox.Items.Clear();
            string instruction = "Conclusion";
            instructionBox.Items.Add(instruction);
        }

        private void previousButton_Click(object sender, System.EventArgs e)
        {
            state_--;

            if (state_ == 0)
                previousButton.Visible = false;
            else if (state_ == 5)
                nextLabel.Text = "Suivant";

            switchInstruction();
        }

        private void nextButton_Click(object sender, System.EventArgs e)
        {
            state_++;

            if (state_ == 1)
                previousButton.Visible = true;
            else if (state_ == 6)
                nextLabel.Text = "Terminer";
            else if (state_ == 7)
                finishTutorial();

            switchInstruction();
        }

        private void finishTutorial()
        {
            parent_.viewPort.Controls.Remove(this);
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);
        }
    }
}
