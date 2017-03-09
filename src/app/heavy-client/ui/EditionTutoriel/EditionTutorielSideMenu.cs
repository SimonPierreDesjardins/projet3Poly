﻿////////////////////////////////////////////////
/// @file   EditionSideMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class EditionTutorielSideMenu : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EditionSideMenu(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public EditionTutorielSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            setToolTips();
            editionObjectMenu.Width = 0;

            disableAllControls();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectToolButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de l'outil sélectioné
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void selectToolButton_Click(object sender, EventArgs e)
        {
            selectTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void selectTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, sélection
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void selectTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            selectToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_S, (IntPtr)2031617);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MoveToolButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil déplacment.
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MoveToolButton_Click(object sender, EventArgs e)
        {
            moveTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void moveTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, déplacement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void moveTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            MoveToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_D, (IntPtr)2097153);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_MOVE_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RotateToolButton_Click(object sender, EventArgs e)
        ///
        ///  Appel l'outil de rotation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void RotateToolButton_Click(object sender, EventArgs e)
        {
            rotateTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void rotateTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, rotation
        ///
        ////////////////////////////////////////////////////////////////////////
        public void rotateTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            RotateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_R, (IntPtr)1245185);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_ROTATION_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ScaleToolButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil de redimensionnement
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ScaleToolButton_Click(object sender, EventArgs e)
        {
            scaleTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void scaleTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, mise à échelle
        ///
        ////////////////////////////////////////////////////////////////////////
        public void scaleTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            ScaleToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_E, (IntPtr)1179649);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_SCALE_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void DuplicateToolButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil de duplication
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void DuplicateToolButton_Click(object sender, EventArgs e)
        {
            duplicateTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void duplicateTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, duplication
        ///
        ////////////////////////////////////////////////////////////////////////
        public void duplicateTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            DuplicateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_C, (IntPtr)3014657);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_DUPLICATE_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void createToolButton_Click(object sender, EventArgs e)
        ///
        /// Fait apparaître le menu pour la création d'objet
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void createToolButton_Click(object sender, EventArgs e)
        {
            HideObjectMenu.Stop();
            ShowObjectMenu.Start();

            setDefaultUnselectedColors();
            createToolButton.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsZoom__Click(object sender, EventArgs e)
        ///
        /// Appel l'outil zoom
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomToolButton_Click(object sender, EventArgs e)
        {
            zoomTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void zoomTool()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, zoom
        ///
        ////////////////////////////////////////////////////////////////////////
        public void zoomTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            zoomToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_Z, (IntPtr)2883585);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void deleteToolButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil supprimer
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void deleteToolButton_Click(object sender, EventArgs e)
        {
            deleteTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deleteTool()
        ///
        /// Supprime tous les objets sélectionnés
        ///
        ////////////////////////////////////////////////////////////////////////
        public void deleteTool()
        {
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_Del, (IntPtr)22216705);
            parent_.verificationDuNombreElementChoisi();

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.DELETE_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void lineObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil création ligne
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void lineObjectButton_Click(object sender, EventArgs e)
        {
            lineObject();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void lineObject()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne noire
        ///
        ////////////////////////////////////////////////////////////////////////
        public void lineObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            lineObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(lineObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_L, (IntPtr)2490368);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_LINE_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void greenLineObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil création ligne verte
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void greenLineObjectButton_Click(object sender, EventArgs e)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void greenLineObject()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne verte
        ///
        ////////////////////////////////////////////////////////////////////////
        public void greenLineObject()
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void redLineObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil création ligne rouge
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void redLineObjectButton_Click(object sender, EventArgs e)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void redLineObject()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne rouge
        ///
        ////////////////////////////////////////////////////////////////////////
        public void redLineObject()
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void postObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil création de poteau
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void postObjectButton_Click(object sender, EventArgs e)
        {
            postObject();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void postObject()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation poteau
        ///
        ////////////////////////////////////////////////////////////////////////
        public void postObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            postObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(postObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_P, (IntPtr)1638401);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_POST_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void wallObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outils création mur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void wallObjectButton_Click(object sender, EventArgs e)
        {
            wallObject();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void wallObject()
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation mur
        ///
        ////////////////////////////////////////////////////////////////////////
        public void wallObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            wallObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(wallObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_M, (IntPtr)3276801);

            if (parent_.editionTutorielInstructions.GetState() == (int)EditionTutorial.State.SELECT_WALL_TOOL)
                parent_.editionTutorielInstructions.nextState();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void teleportObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outils création téléporteur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void teleportObjectButton_Click(object sender, EventArgs e)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bridgeObjectButton_Click(object sender, EventArgs e)
        ///
        /// Appel l'outils création pont
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bridgeObjectButton_Click(object sender, EventArgs e)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void hideObjectMenu()
        ///
        /// Cache le menu pour la création d'objet.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void hideObjectMenu()
        {
            if (editionObjectMenu.Width > 0)
            {
                ShowObjectMenu.Stop();
                HideObjectMenu.Start();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void setDefaultUnselectedColors()
        ///
        /// Remet la couleur par défaut à tous les controles présent dans le menu
        /// d'outil et le menu de création d'objet.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void setDefaultUnselectedColors()
        {
            //Tools
            selectToolButton.BackColor = Color.Transparent;
            MoveToolButton.BackColor = Color.Transparent;
            RotateToolButton.BackColor = Color.Transparent;
            ScaleToolButton.BackColor = Color.Transparent;
            DuplicateToolButton.BackColor = Color.Transparent;
            zoomToolButton.BackColor = Color.Transparent;
            createToolButton.BackColor = Color.Transparent;

            //Objects
            lineObjectButton.BackColor = Color.Transparent;
            greenLineObjectButton.BackColor = Color.Transparent;
            redLineObjectButton.BackColor = Color.Transparent;
            postObjectButton.BackColor = Color.Transparent;
            wallObjectButton.BackColor = Color.Transparent;
            teleportObjectButton.BackColor = Color.Transparent;
            bridgeObjectButton.BackColor = Color.Transparent;

            currentToolButton.BackColor = Color.Transparent;
            currentToolButton.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setCurrentObjet(PictureBox objectPicture)
        ///
        /// Met l'image de l'objet dans le menu d'outil
        /// 
        /// @param PictureBox objectPicture: L'image à insérer
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setCurrentObjet(PictureBox objectPicture)
        {
            currentToolButton.BackColor = Color.FromArgb(0, 102, 204);
            currentObjectPicture.Image = objectPicture.Image;
            currentToolButton.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void HideObjectsMenu_Tick(object sender, EventArgs e)
        ///
        /// Cache le menu de création d'objet lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
        private void HideObjectsMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width > 0)
                editionObjectMenu.Width -= 5;
            else
                HideObjectMenu.Stop();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ShowObjectsMenu_Tick(object sender, EventArgs e)
        ///
        /// Montre le menu de création d'objet lorsque le timer est activé
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du timer
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ShowObjectsMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width < 35)
                editionObjectMenu.Width += 5;
            else
                ShowObjectMenu.Stop();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setToolTips()
        ///
        /// Initialise tous les tooltip pour les controles présents dans les menus
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setToolTips()
        {
            //Tools
            selectToolButton.toolTip.SetToolTip(selectPictureBox, "Outil de sélection [S]");
            MoveToolButton.toolTip.SetToolTip(movePictureBox, "Outil de déplacement [D]");
            RotateToolButton.toolTip.SetToolTip(rotatePictureBox, "Outil de rotation [R]");
            ScaleToolButton.toolTip.SetToolTip(scalePictureBox, "Outil de redimmensionnement [E]");
            DuplicateToolButton.toolTip.SetToolTip(duplicatePictureBox, "Outil de duplication [C]");
            createToolButton.toolTip.SetToolTip(createPictureBox, "Créer objet");
            zoomToolButton.toolTip.SetToolTip(zoomPictureBox, "Outil de zoom [Z]");
            deleteToolButton.toolTip.SetToolTip(deletePictureBox, "Outil de supresion [DEL]");

            //Objects
            lineObjectButton.toolTip.SetToolTip(lineObjectPicture, "Objet ligne [L]");
            greenLineObjectButton.toolTip.SetToolTip(greenLinePictureBox, "Objet ligne verte []");
            redLineObjectButton.toolTip.SetToolTip(redLinePictureBox, "Objet ligne rouge []");
            postObjectButton.toolTip.SetToolTip(postObjectPicture, "Objet poteau [P]");
            wallObjectButton.toolTip.SetToolTip(wallObjectPicture, "Objet mur [M]");
            teleportObjectButton.toolTip.SetToolTip(teleportorPictureBox, "Objet téléporteur []");
            bridgeObjectButton.toolTip.SetToolTip(bridgePictureBox, "Objet viaduc []");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        ///
        /// Change la couleur d'un image par une nouvelle couleur.
        /// 
        /// @param Bitmap scrBitmap: le bitmap de l'image qui doit être modifié
        /// @param Color newColor: La nouvelle couleur de l'image
        ///
        ////////////////////////////////////////////////////////////////////////
        public Bitmap ChangeColor(Bitmap scrBitmap, Color newColor)
        {
            Color actualColor;
            //make an empty bitmap the same size as scrBitmap
            Bitmap newBitmap = new Bitmap(scrBitmap.Width, scrBitmap.Height);
            for (int i = 0; i < scrBitmap.Width; i++)
            {
                for (int j = 0; j < scrBitmap.Height; j++)
                {
                    //get the pixel from the scrBitmap image
                    actualColor = scrBitmap.GetPixel(i, j);
                    // > 150 because.. Images edges can be of low pixel colr. if we set all pixel color to new then there will be no smoothness left.
                    if (actualColor.A > 100)
                        newBitmap.SetPixel(i, j, newColor);
                    //else
                        //newBitmap.SetPixel(i, j, actualColor);
                }
            }
            return newBitmap;
        }

        public void disableAllControls()
        {
            //Tools
            selectToolButton.Enabled = false;
            selectPictureBox.Image = ChangeColor((Bitmap)selectPictureBox.Image, Color.Gray);
            MoveToolButton.Enabled = false;
            movePictureBox.Image = ChangeColor((Bitmap)movePictureBox.Image, Color.Gray);
            RotateToolButton.Enabled = false;
            rotatePictureBox.Image = ChangeColor((Bitmap)rotatePictureBox.Image, Color.Gray);
            ScaleToolButton.Enabled = false;
            scalePictureBox.Image = ChangeColor((Bitmap)scalePictureBox.Image, Color.Gray);
            DuplicateToolButton.Enabled = false;
            duplicatePictureBox.Image = ChangeColor((Bitmap)duplicatePictureBox.Image, Color.Gray);
            createToolButton.Enabled = false;
            createPictureBox.Image = ChangeColor((Bitmap)createPictureBox.Image, Color.Gray);
            zoomToolButton.Enabled = false;
            zoomPictureBox.Image = ChangeColor((Bitmap)zoomPictureBox.Image, Color.Gray);
            deleteToolButton.Enabled = false;
            deletePictureBox.Image = ChangeColor((Bitmap)deletePictureBox.Image, Color.Gray);

            //Objects
            lineObjectButton.Enabled = false;
            lineObjectPicture.Image = ChangeColor((Bitmap)lineObjectPicture.Image, Color.Gray);
            greenLineObjectButton.Enabled = false;
            greenLinePictureBox.Image = ChangeColor((Bitmap)greenLinePictureBox.Image, Color.Gray);
            redLineObjectButton.Enabled = false;
            redLinePictureBox.Image = ChangeColor((Bitmap)redLinePictureBox.Image, Color.Gray);
            postObjectButton.Enabled = false;
            postObjectPicture.Image = ChangeColor((Bitmap)postObjectPicture.Image, Color.Gray);
            wallObjectButton.Enabled = false;
            wallObjectPicture.Image = ChangeColor((Bitmap)wallObjectPicture.Image, Color.Gray);
            teleportObjectButton.Enabled = false;
            teleportorPictureBox.Image = ChangeColor((Bitmap)teleportorPictureBox.Image, Color.Gray);
            bridgeObjectButton.Enabled = false;
            bridgePictureBox.Image = ChangeColor((Bitmap)bridgePictureBox.Image, Color.Gray);
        }
    }
}
