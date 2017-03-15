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
        /// @fn private void switchInstruction()
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

                case (int)EditionTutorial.State.SELECTING_OBJECT:
                    selectingObjectState();
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

                case (int)EditionTutorial.State.DELETE_TOOL:
                    applyingDeleteTool();
                    break;

                case (int)EditionTutorial.State.SELECT_WALL_TOOL:
                    selectWallToolState();
                    break;

                case (int)EditionTutorial.State.CREATING_WALL:
                    creatingAWallObjectState();
                    break;

                case (int)EditionTutorial.State.SELECT_ROTATION_TOOL:
                    selectRotationToolState();
                    break;

                case (int)EditionTutorial.State.APPLYING_ROTATION:
                    applyingRotationToolState();
                    break;

                case (int)EditionTutorial.State.SELECT_LINE_TOOL:
                    selectLineToolState();
                    break;

                case (int)EditionTutorial.State.CREATING_LINE:
                    creatingALineObjectState();
                    break;

                case (int)EditionTutorial.State.CHANGE_VIEW:
                    changeViewSate();
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
        /// @fn private void introductionState()
        ///
        /// Cette fonction présente une introduction pour le tutoriel d'édition
        /// Change le text présent dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void introductionState()
        {
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            nextLabel.Text = "Suivant";
            nextPictureBox.Image = ui.Properties.Resources.RightArrow;
            nextButton.Visible = true;
            previousLabel.Text = "Précédent";
            previousButton.Visible = false;

            instructionBox.Items.Clear();
            string instruction = "Bienvenu au tutoriel interactif pour le mode Édition! \n\n" +
                                 "Dans ce tutoriel, les outils disponible vous seront expliqué en détail et " +
                                 "vous devrez suivre les actions requises afin de pouvoir passer à la prochaine " +
                                 "étape. \n\n" + "Afin de ne pas vous encombrer la vue, cette boîte de dialogue est " +
                                 "déplaçable si vous cliquer sur la partie bleu et déplacer votre souris en maintenant la touche gauche enfoncé.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectPostCreateToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// creation de poteau pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectPostCreateToolState()
        {
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            nextButton.Visible = false;
            previousButton.Visible = true;

            parent_.editionTutorielSideMenu.createToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.createPictureBox.Image = 
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.createPictureBox.Image, Color.White);
            parent_.editionTutorielSideMenu.postObjectButton.Enabled = true;
            parent_.editionTutorielSideMenu.postObjectPicture.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.postObjectPicture.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme première tâche, vous devez sélectionner l'outil pour la création de poteau. \n" +
                                 "Pour accéder à cet outil, vous devez cliquer sur l'icon créer objet dans le menu du côté, puis " +
                                 "sélectionner le poteau dans le menu qui apparaîtra. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'P' afin de sélectionner l'outil création de poteau et " +
                                 "ce dernier s'ajoutera au menu de gauche";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void creatingAPostObjectState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// creation de poteau pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void creatingAPostObjectState()
        {
            instructionBox.Items.Clear();
            string instruction = "Maintenant que vous avez l'outil pour la création de poteau, vous devez en ajouter un à la carte. \n\n" +
                                 "Pour ce faire, il suffit d'appuyer le button gauche de la souris sur un endroit disponible de la table et " +
                                 "de le relâcher à l'endroit ou vous voulez positionner le poteau.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectLineToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// creation de ligne pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectLineToolState()
        {
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.createToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.createPictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.createPictureBox.Image, Color.White);
            parent_.editionTutorielSideMenu.lineObjectButton.Enabled = true;
            parent_.editionTutorielSideMenu.lineObjectPicture.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.lineObjectPicture.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme deuxième tâche, vous devez sélectionner l'outil pour la création de ligne. \n" +
                                 "Pour accéder à cet outil, vous devez cliquer sur l'icon créer objet dans le menu du côté, puis " +
                                 "sélectionner la ligne dans le menu qui apparaîtra. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'L' afin de sélectionner l'outil création de ligne et " +
                                 "ce dernier s'ajoutera au menu de gauche";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void creatingALineObjectState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// creation de line pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void creatingALineObjectState()
        {
            instructionBox.Items.Clear();
            string instruction = "Maintenant que vous avez l'outil pour la création de ligne, vous devez en ajouter une à la carte. \n\n" +
                                 "Pour ce faire, il suffit d'appuyer le button gauche de la souris sur un endroit disponible de la table et " +
                                 "de le relâcher. Vous pouvez alors créer la ligne de la longueur que vous voulez. De plus, pour créer des " + 
                                 "segments à cette ligne, vous pouvez maintenir la touche 'CTRL' enfoncer et ré-appuyer sur le clique gauche de la souris. " +
                                 "Pour terminer la création de ligne, il suffit de lâcher la touche 'CTRL' et appuyer sur le clique gauche de la souris.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectWallToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// creation de mur pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectWallToolState()
        {
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.createToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.createPictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.createPictureBox.Image, Color.White);
            parent_.editionTutorielSideMenu.wallObjectButton.Enabled = true;
            parent_.editionTutorielSideMenu.wallObjectPicture.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.wallObjectPicture.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme troisième tâche, vous devez sélectionner l'outil pour la création de mur. \n" +
                                 "Pour accéder à cet outil, vous devez cliquer sur l'icon créer objet dans le menu du côté, puis " +
                                 "sélectionner le mur dans le menu qui apparaîtra. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'M' afin de sélectionner l'outil création de mur et " +
                                 "ce dernier s'ajoutera au menu de gauche";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void creatingAWallObjectState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// creation de mur pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void creatingAWallObjectState()
        {
            instructionBox.Items.Clear();
            string instruction = "Maintenant que vous avez l'outil pour la création de mur, vous devez en ajouter un à la carte. \n\n" +
                                 "Pour ce faire, il suffit d'appuyer le button gauche de la souris sur un endroit disponible de la table et " +
                                 "de le relâcher. Vous pouvez alors créer la ligne de la longueur que vous voulez. " +
                                 "Pour terminer la création du mur, il suffit d'appuyer à nouveau sur le clique gauche de la souris.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectSelectToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// sélection pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectSelectToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();
            FonctionsNatives.UnselectAllObjects();
            parent_.verificationDuNombreElementChoisi();

            parent_.editionTutorielSideMenu.selectToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.selectPictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.selectPictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Il serait bien d'apporter des changements aux objets nouvellement créés. \n\n" +
                                 "Pour ce faire, vous devez sélectionner l'outil de sélection. \n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'S' afin de sélectionner l'outil de sélection et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectingObjectState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// sélection pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectingObjectState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            instructionBox.Items.Clear();
            string instruction = "Pour sélectionner un objet, il suffit de déplacer la souris par dessus celui-ci et de cliquer " +
                                 "sur l'objet avec le bouton gauche de la souris. Vous pouvez également créer un rectangle élastisque " +
                                 "en maintenant le bouton gauche de la souris enfoncer et déplacer la souris. Tous les objets à l'intérieur " +
                                 "du rectangle seront choisi. \n\n" +
                                 "Pour completer cette étape, sélectionnez le dernier mur créé.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectScaleToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// redimensionnement pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectScaleToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.ScaleToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.scalePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.scalePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Une fois qu'un objet est sélectionner on peut y utiliser plusieurs outils comme une mise-à-échelle, une rotation, une duplication, une translation ou une suppression. \n\n" +
                                 "On débutera par l'outil de redimensionnement. \n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'E' afin de sélectionner l'outil de redimensionnement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyingScaleToolState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// redimensionnement pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void applyingScaleToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            instructionBox.Items.Clear();
            string instruction = "Pour appliquer cette outils il suffit d'appuyer sur le bouton gauche de la souris et de la déplacer vers le haut " +
                                 "pour agrandir l'objet ou vers le bas pour réduire la dimension de l'objet. \n\n" +
                                 "Pour compléter cette étape il vous suffit de modifier le facteur de redimensionnement de l'objet sélectionné.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectMoveToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// déplacement pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectMoveToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.MoveToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.movePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.movePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme deuxième outil, on choisira l'outil de déplacement des objets. \n\n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'D' afin de sélectionner l'outil de déplacement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyingMoveToolState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// déplacement pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void applyingMoveToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            instructionBox.Items.Clear();
            string instruction = "Pour appliquer cette outils il suffit d'appuyer sur le bouton gauche de la souris et de la déplacer dans la " +
                                 "direction de votre choix. Il est important que l'objet reste sur la table ou il sera replacé a sa position initiale. \n\n" +
                                 "Pour compléter cette étape il vous suffit de déplacer l'objet sélectionné.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectScaleToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// rotation pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectRotationToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.RotateToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.rotatePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.rotatePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme troisième outil, on choisira l'outil de rotations des objets. \n\n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'D' afin de sélectionner l'outil de déplacement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyingRotationToolState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// rotation pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void applyingRotationToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            instructionBox.Items.Clear();
            string instruction = "Pour appliquer cette outils il suffit d'appuyer sur le bouton gauche de la souris et de la déplacer dans la " +
                                 "direction de votre choix. Un déplacement vers le haut fera une rotation horaire alors qu'une rotation vers le bas " +
                                 "fera le contraire. Il est important que les objets reste sur la table ou il sera replacé a sa position initiale. \n\n" +
                                 "Pour compléter cette étape il vous suffit de modifier l'angle de rotation des objets sélectionnés.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectDuplicateToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner l'outil de
        /// duplication pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions. Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void selectDuplicateToolState()
        {
            parent_.editionTutorielModificationPanel.ajusteToMode();
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielSideMenu.DuplicateToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.duplicatePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.duplicatePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme quatrième outil, on choisira l'outil de dupplication. \n\n" +
                                 "Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'C' afin de sélectionner l'outil de déplacement et " +
                                 "ce dernier sera activé";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyingDuplicateToolState()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// duplication pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void applyingDuplicateToolState()
        {
            instructionBox.Items.Clear();
            string instruction = "Cet outil duplicate le ou les objets choisi. Il est donc très utile pour conserver les modifications faites par les autres outils. \n\n" +
                                 "Pour appliquer la duplication, il vous suffit de cliquer à l'endroit désiré sur la zone de simulation et " +
                                 "l'outil créera les objets. Il est important que tous les objets soit sur la table ou ils ne seront pas créés. \n\n" +
                                 "Pour completer cette étape, il vous suffit d'utiliser l'outil pour créer un autre poteau.";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void applyingDeleteTool()
        ///
        /// Cette fonction présente les instructions pour l'application de l'outil de
        /// supression pour le tutoriel d'édition. Change le text présent 
        /// dans les instructions.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void applyingDeleteTool()
        {
            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            FonctionsNatives.SelectAllTutorialObjects();

            parent_.editionTutorielSideMenu.deleteToolButton.Enabled = true;
            parent_.editionTutorielSideMenu.deletePictureBox.Image =
                parent_.editionTutorielSideMenu.ChangeColor((Bitmap)parent_.editionTutorielSideMenu.deletePictureBox.Image, Color.White);

            instructionBox.Items.Clear();
            string instruction = "Comme dernier outil, on appliquera l'outil de supression. \n\n" +
                                 "Pour les besoins de ce tutoriel, tous les objets créés ont été sélectionner. L'outil de suppression enlevera tous les objets " +
                                 "selectionnés de la zone de simulation. Comme les autres outils, il est disponible dans le menu situé à votre gauche. \n" +
                                 "Vous pouvez également utiliser la touche rapide 'DEL' afin d'appliquer l'outil";
            instructionBox.Items.Add(instruction);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectScaleToolState()
        ///
        /// Cette fonction présente les instructions pour selectionner la caméra orbite
        /// pour le tutoriel d'édition. Change le text présent dans les instructions. 
        /// Active le ui nécessaire.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void changeViewSate()
        {
            nextButton.Visible = false;
            previousButton.Visible = false;

            parent_.editionTutorielSideMenu.setDefaultUnselectedColors();
            parent_.editionTutorielSideMenu.disableAllControls();
            FonctionsNatives.UnselectCurrentTool();

            parent_.editionTutorielMenuStrip.vuesToolStripMenuItem.Enabled = true;

            instructionBox.Items.Clear();
            string instruction = "Comme dernière tâche du tutoriel, il vous suffit de changer la vue. La vue orbite permet de voir les objets sous un angle " +
                                 "différent. Comme avec la caméra actuel, vous pouvez déplacer la vue avec les flèches et vous pouvez vous approcher ou vous éloigner " +
                                 "avec la molette de la souris. \n\n" +
                                 "Les caméras se trouvent dans l'onglet du menu en haut. Vous pouvez également utiliser les touche rapide, soit '1' pour la caméra " +
                                 "orthographique ou la touche '2' pour la caméra orbite.";
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
            parent_.editionTutorielMenuStrip.vuesToolStripMenuItem.Enabled = false;

            previousLabel.Text = "Début";
            previousButton.Visible = true;

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
            parent_.editionModificationPanel = new EditionModificationPanel(parent_);

            parent_.viewPort.Controls.Remove(this);
            parent_.viewPort.Controls.Remove(parent_.editionTutorielSideMenu);
            parent_.viewPort.Controls.Remove(parent_.editionTutorielMenuStrip);
            parent_.viewPort.Controls.Remove(parent_.editionTutorielModificationPanel);

            parent_.viewPort.Controls.Add(parent_.editionSideMenu);
            parent_.editionSideMenu.Dock = DockStyle.Left;

            parent_.viewPort.Controls.Add(parent_.editionMenuStrip);
            parent_.editionMenuStrip.Dock = DockStyle.Top;

            parent_.editionModificationPanel.Location = new Point(parent_.viewPort.Width - parent_.editionModificationPanel.Width,
                                                                  parent_.editionMenuStrip.Height);
            parent_.editionModificationPanel.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            parent_.editionModificationPanel.Visible = false;
            parent_.viewPort.Controls.Add(parent_.editionModificationPanel);

            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);

            Program.peutAfficher = true;
            FonctionsNatives.assignerMode(Mode.EDITION);

            FonctionsNatives.dessinerOpenGL();
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void previousButton_Click(object sender, EventArgs e)
        ///
        /// Appel la fonction pour faire changer l'état vers un état antérieur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void previousButton_Click(object sender, System.EventArgs e)
        {
            previousState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void previousState()
        ///
        /// Décrémente l'état du tutoriel et appel switchInstruction pour changer le
        /// text présenté à l'utilisateur
        ///
        ////////////////////////////////////////////////////////////////////////
        public void previousState()
        {
            switch (state_)
            {
                case (int)EditionTutorial.State.INTRODUCTION:
                    break;

                case (int)EditionTutorial.State.SELECT_POST_TOOL:
                case (int)EditionTutorial.State.CREATING_POST:
                case (int)EditionTutorial.State.CREATING_LINE:
                case (int)EditionTutorial.State.CREATING_WALL:
                case (int)EditionTutorial.State.SELECTING_OBJECT:
                case (int)EditionTutorial.State.APPLYING_SCALE:
                case (int)EditionTutorial.State.APPLYING_MOVE: 
                case (int)EditionTutorial.State.APPLYING_ROTATION: 
                case (int)EditionTutorial.State.APPLYING_DUPLICATE:
                case (int)EditionTutorial.State.CHANGE_VIEW:
                    state_--;
                    break;

                case (int)EditionTutorial.State.SELECT_LINE_TOOL:
                case (int)EditionTutorial.State.SELECT_WALL_TOOL:
                case (int)EditionTutorial.State.SELECT_TOOL:
                case (int)EditionTutorial.State.SELECT_SCALE_TOOL:
                case (int)EditionTutorial.State.SELECT_MOVE_TOOL:
                case (int)EditionTutorial.State.SELECT_ROTATION_TOOL:
                case (int)EditionTutorial.State.SELECT_DUPLICATE_TOOL:
                case (int)EditionTutorial.State.DELETE_TOOL:
                    state_ -= 2;
                    break;

                case (int)EditionTutorial.State.CONCLUSION:
                    state_ = 0;
                    break;
            }
            switchInstruction();
            FonctionsNatives.UpdateEditionTutorialState(state_);
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nextButton_Click(object sender, EventArgs e)
        ///
        /// Appel la fonction nextState qui passe au prochain état du tutoriel
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nextButton_Click(object sender, System.EventArgs e)
        {
            nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void nextState()
        ///
        /// Incrémente l'état du tutoriel et appel switchInstruction pour changer le
        /// text présenté à l'utilisateur
        ///
        ////////////////////////////////////////////////////////////////////////
        public void nextState()
        {
            state_++;
            switchInstruction();

            FonctionsNatives.UpdateEditionTutorialState(state_);
            maxUserControl();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public int GetState()
        ///
        /// Fonction qui retourne l'état du tutoriel
        /// 
        /// @return int: Le numéro représentant l'état du tutoriel
        ///
        ////////////////////////////////////////////////////////////////////////
        public int GetState()
        {
            return state_;
        }

        private void TitleButton_Click(object sender, EventArgs e)
        {
            if (this.Height > 30)
                minUserControl();
            else
                maxUserControl();
        }

        private void minMaxButton_Click(object sender, EventArgs e)
        {
            if (this.Height > 30)
                minUserControl();
            else
                maxUserControl();
        }

        private void minUserControl()
        {
            tutorialPanel.BackColor = Color.FromArgb(26, 32, 40);
            this.Height = 30;
            //70 sideMenu edition ouvert
            this.Location = new Point(70, parent_.viewPort.Height - this.Height);
            this.Anchor = (AnchorStyles.Bottom | AnchorStyles.Left);
            minMaxPictureBox.Image = Properties.Resources.Maximize;
            FonctionsNatives.dessinerOpenGL();
        }

        private void maxUserControl()
        {
            tutorialPanel.BackColor = Color.FromArgb(0, 102, 204);
            this.Height = 306;

            this.Location = new Point(parent_.viewPort.Width / 2 - this.Width / 2,
                                      parent_.viewPort.Height / 2 - this.Height / 2);
            this.Anchor = AnchorStyles.None;
            minMaxPictureBox.Image = Properties.Resources.Minimize;
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction pour le CallBack du c++ au c#
        ///
        ////////////////////////////////////////////////////////////////////////
        public void WaitingForModelCallBack()
        {
            ChangeEditionTutorialState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction pour le CallBack du c++ au c#
        ///
        ////////////////////////////////////////////////////////////////////////
        private delegate void Callback();
        // Ensure it doesn't get garbage collected
        private Callback mInstance;
        private void InterfaceFunctionChangeStateTutoriel()
        {
            state_++;
            switchInstruction();
            FonctionsNatives.UpdateEditionTutorialState(state_);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// Fonction pour le CallBack du c++ au c#
        ///
        ////////////////////////////////////////////////////////////////////////
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

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void UnselectCurrentTool();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void UnselectAllObjects();

        [DllImport(@"model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SelectAllTutorialObjects();
    }
}