////////////////////////////////////////////////
/// @file   EditionTutorielInstructions.cs
/// @author Frédéric Grégoire
/// @date   2017-03-04
///
////////////////////////////////////////////////
using ModeEnum;
using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ui
{
    public partial class EditionTutorielInstructions : UserControl
    {
        int state_;
        Window parent_;
        bool _capturingMoves;

        Point MouseDownLocation;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EditionTutorielInstructions(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public EditionTutorielInstructions(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            parent_ = parent;

            state_ = 0;
            switchInstruction();
            FonctionsNatives.UpdateEditionTutorialState(state_);
            previousButton.Visible = false;

            instructionBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            instructionBox.MeasureItem += instructionBox_MeasureItem;
            instructionBox.DrawItem += instructionBox_DrawItem;

            mInstance = new Callback(InterfaceFunctionChangeStateTutoriel);
            SetCallback(mInstance);
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
                case (int)EditionTutorial.State.INTRODUCTION:
                    introductionState();
                    break;

                case (int)EditionTutorial.State.SELECT_POST_TOOL:
                    selectPostCreateToolState();
                    break;

                case (int)EditionTutorial.State.CREATING_POST:
                    creatingAPostObjectState();
                    break;

                case (int)EditionTutorial.State.SELECT_TOOL:
                    selectSelectToolState();
                    break;

                case (int)EditionTutorial.State.SELECTING_POST:
                    selectingPostObject();
                    break;

                case (int)EditionTutorial.State.SELECT_SCALE_TOOL:
                    selectScaleToolState();
                    break;

                case (int)EditionTutorial.State.APPLYING_SCALE:
                    applyingScaleToolState();
                    break;

                case (int)EditionTutorial.State.SELECT_MOVE_TOOL:
                    selectMoveToolState();
                    break;

                case (int)EditionTutorial.State.APPLYING_MOVE:
                    applyingMoveToolState();
                    break;

                case (int)EditionTutorial.State.SELECT_DUPLICATE_TOOL:
                    selectDuplicateToolState();
                    break;

                case (int)EditionTutorial.State.APPLYING_DUPLICATE:
                    applyingDuplicateToolState();
                    break;

                case (int)EditionTutorial.State.CONCLUSION:
                    conclusionState();
                    break;

                default:
                    finishTutorial();
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
            nextButton.Visible = true;
            previousButton.Visible = false;

            instructionBox.Items.Clear();
            string instruction = "Bienvenu au tutoriel interactif pour le mode Édition! \n\n" +
                                 "Dans ce tutoriel, les outils disponible vous seront expliqué en détail et " +
                                 "vous devrez suivre les actions requises afin de pouvoir passer à la prochaine " +
                                 "étape. \n\n" + "Afin de ne pas vous encombrer la vue, cette boîte de dialogue est " +
                                 "déplaçable si vous cliquer sur la partie bleu et déplacer votre souris en maintenant la touche gauche enfoncé.";
            instructionBox.Items.Add(instruction);
        }

        private void selectPostCreateToolState()
        {
            nextButton.Visible = false;
            previousButton.Visible = true;

            parent_.editionTutorielSideMenu.createToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.createPictureBox.Image = 
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.createPictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme première tâche, vous devez sélectionner l'outil pour la création de poteau. \n" +
                                 "Pour accéder à cet outil, vous devez cliquer sur l'icon créer objet dans le menu du côté, puis " +
                                 "sélectionner le poteau dans le menu qui apparaîtra. \n\n" +
                                 "Vous pouvez également utiliser la touche rapide 'P' afin de sélectionner l'outil création de poteau et " +
                                 "ce dernier s'ajoutera au menu de gauche";
            instructionBox.Items.Add(instruction);
        }

        private void creatingAPostObjectState()
        {
            instructionBox.Items.Clear();
            string instruction = "Maintenant que vous avez l'outil pour la création de poteau, vous devez en ajouter un à la carte. \n\n" +
                                 "Pour ce faire, il suffit d'appuyer le button gauche de la souris sur un endroit disponible de la table et " +
                                 "de le relâcher à l'endroit ou vous voulez positionner le poteau.";
            instructionBox.Items.Add(instruction);
        }

        private void selectSelectToolState()
        {
            parent_.editionTutorielSideMenu.disableAllControls();
            parent_.editionTutorielSideMenu.selectToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.selectPictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.selectPictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Maintenant que vous avez créé un poteau, il serait bien d'y apporter des changements. \n\n" +
                                 "Pour ce faire, vous devez sélectionner l'outil de sélection. \n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'S' afin de sélectionner l'outil de sélection et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        private void selectingPostObject()
        {
            instructionBox.Items.Clear();
            string instruction = "Applique le select Tool";
            instructionBox.Items.Add(instruction);
        }

        private void selectScaleToolState()
        {
            parent_.editionTutorielSideMenu.disableAllControls();
            parent_.editionTutorielSideMenu.ScaleToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.scalePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.scalePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Maintenant que le poteau est sélectionner on peut y apporter des changements. \n\n" +
                                 "On débutera pour une l'outil de redimensionnement. \n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'E' afin de sélectionner l'outil de redimensionnement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        private void applyingScaleToolState()
        {
            instructionBox.Items.Clear();
            string instruction = "Applique le scale";
            instructionBox.Items.Add(instruction);
        }

        private void selectMoveToolState()
        {
            parent_.editionTutorielSideMenu.disableAllControls();
            parent_.editionTutorielSideMenu.MoveToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.movePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.movePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "On peut également déplacer le poteau à l'aide de l'outil de déplacement. \n\n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'D' afin de sélectionner l'outil de déplacement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        private void applyingMoveToolState()
        {
            instructionBox.Items.Clear();
            string instruction = "Applique le move";
            instructionBox.Items.Add(instruction);
        }

        private void selectDuplicateToolState()
        {
            parent_.editionTutorielSideMenu.disableAllControls();
            parent_.editionTutorielSideMenu.DuplicateToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.duplicatePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.duplicatePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Afin d'ajouter des objets à notre table, on peut dupliquer un ou plusieurs objets avec l'outil de duplication. \n\n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'C' afin de sélectionner l'outil de déplacement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        private void applyingDuplicateToolState()
        {
            nextLabel.Text = "Suivant";
            nextPictureBox.Image = ui.Properties.Resources.RightArrow;
            nextButton.Visible = false;

            instructionBox.Items.Clear();
            string instruction = "Applique le duplicate";
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
            nextLabel.Text = "Terminé";
            nextPictureBox.Image = ui.Properties.Resources.confirm;
            nextButton.Visible = true;

            instructionBox.Items.Clear();
            string instruction = "Vous avez maintenant complété le tutoriel pour l'Édition! \n\n" +
                                 "Vous pouvez toujours refaire le tutoriel pour l'Édition en sélectionnant l'option 'Tutoriel' dans le menu au haut de l'écran, " +
                                 "lorsque vous êtes en train d'éditer une map.";
            instructionBox.Items.Add(instruction);
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
            parent_.editionSideMenu = new EditionSideMenu(parent_);
            parent_.editionMenuStrip = new EditionMenuStrip(parent_);

            parent_.viewPort.Controls.Remove(this);
            parent_.viewPort.Controls.Remove(parent_.editionTutorielSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionTutorielMenuStrip);

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            Program.peutAfficher = true;

            FonctionsNatives.assignerMode(Mode.EDITION);
            parent_.verificationDuNombreElementChoisi();

            FonctionsNatives.dessinerOpenGL();
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
            previousState();
        }

        public void previousState()
        {
            state_--;
            switchInstruction();

            FonctionsNatives.UpdateEditionTutorialState(state_);
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
            nextState();
        }

        public void nextState()
        {
            state_++;
            switchInstruction();

            FonctionsNatives.UpdateEditionTutorialState(state_);
        }

        private void tutorialPanel_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button != MouseButtons.Left)
                return;

            MouseDownLocation = e.Location;
            _capturingMoves = true;
        }

        private void tutorialPanel_MouseUp(object sender, MouseEventArgs e)
        {
            if (_capturingMoves)
            {
                _capturingMoves = false;
            }
        }

        private void tutorialPanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (!_capturingMoves)
                return;

            int X = this.Location.X - (MouseDownLocation.X - e.X);
            int Y = this.Location.Y - (MouseDownLocation.Y - e.Y);

            if (X < parent_.editionSideMenu.Width || (X + this.Width) > parent_.viewPort.Width)
                return;
            if (Y < parent_.editionMenuStrip.Height || (Y + this.Height) > parent_.viewPort.Height)
                return;

            this.Location = new Point(X, Y);
            FonctionsNatives.dessinerOpenGL();
        }

        public int GetState()
        {
            return state_;
        }

        public void WaitingForModelCallBack()
        {
            ChangeEditionTutorialState();
        }

        private delegate void Callback();
        // Ensure it doesn't get garbage collected
        private Callback mInstance;
        private void InterfaceFunctionChangeStateTutoriel()
        {
            // Do something...
            Console.WriteLine("wooohoooo");
            state_++;
            switchInstruction();
            FonctionsNatives.UpdateEditionTutorialState(state_);
        }

        [DllImport("model.dll")]
        private static extern void SetCallback(Callback fn);

        [DllImport("model.dll")]
        private static extern void ChangeEditionTutorialState();
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
        public static extern void UpdateEditionTutorialState(int currentState);
    }
}