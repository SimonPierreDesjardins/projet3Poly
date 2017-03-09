////////////////////////////////////////////////
/// @file   TutorialSimulation.cs
/// @author Frédéric Grégoire
/// @date   2017-03-04
///
////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public TutorialSimulation(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public TutorialSimulation(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            parent_ = parent;
            parent_.simulationMenuStrip.Enabled = false;
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public switchInstruction()
        ///
        /// Cette fonction appel la fonction pour ajuster le text selon l'état du tutoriel
        /// 
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public introductionState()
        ///
        /// Cette fonction présente une introduction pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void introductionState()
        {
            instructionBox.Items.Clear();
            string instruction = "Bienvenu au tutoriel pour le mode simulation! \n\n" +
                                 "Comme vous avez pu le constater, lorsque vous choississez ce mode, " +
                                 "l'application vous demande une carte à charger. Vous pouvez donc sélectionner la carte de votre choix. \n" +
                                 "La carte conservera tous les changements que vous y avez effectué durant le mode 'Édition'.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public mouvementState()
        ///
        /// Cette fonction présente les mouvements du robot pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void mouvementState()
        {
            instructionBox.Items.Clear();
            string instruction = "Pour déplacer votre robot dans la zone de simulation, vous devez appuyer sur les touches suivantes : \n" +
                                 "Pour avancer: '" + FonctionsNatives.obtenirToucheCommande(TypeCommandeEnum.TypeCommande.AVANCER) + "'\n" +
                                 "Pour tourner vers la gauche: '" + FonctionsNatives.obtenirToucheCommande(TypeCommandeEnum.TypeCommande.ROTATION_GAUCHE) + "'\n" +
                                 "Pour tourner vers la droite: '" + FonctionsNatives.obtenirToucheCommande(TypeCommandeEnum.TypeCommande.ROTATION_DROITE) + "'\n" +
                                 "Pour reculer: '" + FonctionsNatives.obtenirToucheCommande(TypeCommandeEnum.TypeCommande.RECULER) + "'\n" +
                                 "Vous pouvez également passez en mode automatique où le véhicule se dirigera de façon autonome avec la touche: '" +
                                 FonctionsNatives.obtenirToucheCommande(TypeCommandeEnum.TypeCommande.INVERSER_MODE_CONTROLE) + "'. \n" +
                                 "Ces touches dépendent de votre profil qui peut être changé à partir du menu principal dans l'option 'Configuration'. \n";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public cameraOrthoState()
        ///
        /// Cette fonction présente la camera ortho pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void cameraOrthoState()
        {
            instructionBox.Items.Clear();
            string instruction = "Il y a trois types de caméra disponible dans le mode simulation. \n" +
                                 "La première est la caméra orthographique. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation de haut en bas. " +
                                 "Pour déplacer la caméra il suffit de maintenir le boutton droit de la souris enfoncé et la déplacer. " +
                                 "On peut également ajuster la distance de la caméra avec la molette de la souris. \n" +
                                 "La touche rapide pour accéder à cette caméra est '1'.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public cameraOrbiteState()
        ///
        /// Cette fonction présente la camera orbite pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void cameraOrbiteState()
        {
            instructionBox.Items.Clear();
            string instruction = "Le deuxième type de caméra est la caméra orbite. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation de tous les angles possible. \n" +
                                 "Pour déplacer la caméra il suffit de maintenir le boutton droit de la souris enfoncé et se déplacer." +
                                 "Un mouvement de gauche à droite fera déplacer la caméra horizontalement, tandis qu'un mouvement de haut en bas " +
                                 "fera déplacer la caméra verticalement. \n" + 
                                 "On peut également ajuster la distance de la caméra avec la molette de la souris. \n" +
                                 "La touche rapide pour accéder à cette caméra est '2'.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public cameraFirstPersoState()
        ///
        /// Cette fonction présente la camera premiere personne pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void cameraFirstPersoState()
        {
            instructionBox.Items.Clear();
            string instruction = "Le troisème type de caméra est la caméra permière personne. \n" +
                                 "Avec cette caméra, il est possible de voir la zone de simulation sous l'angle d'un conducteur fictif. \n" +
                                 "Cette caméra se déplace automatiquement avec le déplacement du véhicule. Il n'est pas possible de l'ajuster autrement. \n" +
                                 "La touche rapide pour accéder à cette caméra est '3'.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public lightsState()
        ///
        /// Cette fonction présente les options de lumiere pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void lightsState()
        {
            instructionBox.Items.Clear();
            string instruction = "Il y a trois types de lumière possible que vous pouvez changer lors de la simulation. \n\n" +
                                 "La première est la lumière ambiante. \n" +
                                 "La touche rapide pour changer sa valeur est 'J'. \n\n" +
                                 "La deuxième est la lumière directionnelle. \n" +
                                 "La touche rapide pour changer sa valeur est 'K'. \n\n" +
                                 "La troisième est un projecteur braqué sur le véhicule. \n" +
                                 "La touche rapide pour changer sa valeur est 'L'.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public conclusionState()
        ///
        /// Cette fonction présente une conclusion pour le tutoriel de simulation
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void conclusionState()
        {
            instructionBox.Items.Clear();
            string instruction = "Vous avez maintenant complété le tutoriel de simulation! \n\n" +
                                 "Vous pouvez toujours refaire le tutoriel de simulation en sélectionnant l'option 'Tutoriel' dans le menu au haut de l'écran, " +
                                 "lorsque la simulation est en pause.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void previousButton_Click(object sender, EventArgs e)
        ///
        /// Décrémente l'état du tutoriel et appel switchInstruction pour changer le
        /// text présenté à l'utilisateur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void previousButton_Click(object sender, System.EventArgs e)
        {
            state_--;

            if (state_ == 0)
                previousButton.Visible = false;
            else if (state_ == 5)
            {
                nextLabel.Text = "Suivant";
                nextPictureBox.Image = ui.Properties.Resources.RightArrow;
            }
                

            switchInstruction();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nextButton_Click(object sender, EventArgs e)
        ///
        /// Incrémente l'état du tutoriel et appel switchInstruction pour changer le
        /// text présenté à l'utilisateur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nextButton_Click(object sender, System.EventArgs e)
        {
            state_++;

            if (state_ == 1)
                previousButton.Visible = true;
            else if (state_ == 6)
            {
                nextLabel.Text = "Terminer";
                nextPictureBox.Image = ui.Properties.Resources.confirm;
            }    
            else if (state_ == 7)
                finishTutorial();

            switchInstruction();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void finishTutorial()
        ///
        /// Complete le tutoriel et enleve le control de la fenetre principal.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void finishTutorial()
        {
            parent_.viewPort.Controls.Remove(this);
            parent_.simulationMenuStrip.Enabled = true;
            FonctionsNatives.assignerAutorisationInputClavier(true);
            FonctionsNatives.assignerAutorisationInputSouris(true);

            parent_.simulationMenuStrip.tutorielToolStripMenuItem.Visible = false;
            parent_.simulationMenuStrip.tutorielToolStripMenuItem.Visible = true;
            FonctionsNatives.dessinerOpenGL();
        }
    }
}
