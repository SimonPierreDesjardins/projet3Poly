﻿using System;
using System.Drawing;
using System.Windows.Forms;

namespace ui
{
    public partial class EditionSideMenu : UserControl
    {
        Window parent_;

        public EditionSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            setToolTips();
            editionObjectMenu.Width = 0;
            selectTool();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsSelection__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, sélection
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void selectToolButton_Click(object sender, EventArgs e)
        {
            selectTool();
        }

        public void selectTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            selectToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_S, (IntPtr)2031617);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsDéplacement__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, déplacement
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MoveToolButton_Click(object sender, EventArgs e)
        {
            moveTool();
        }

        public void moveTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            MoveToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_D, (IntPtr)2097153);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsRotation__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, rotation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void RotateToolButton_Click(object sender, EventArgs e)
        {
            rotateTool();
        }

        public void rotateTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            RotateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_R, (IntPtr)1245185);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsMiseAEchelle__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, mise à échelle
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ScaleToolButton_Click(object sender, EventArgs e)
        {
            scaleTool();
        }

        public void scaleTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            ScaleToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_E, (IntPtr)1179649);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsDuplication__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, duplication
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void DuplicateToolButton_Click(object sender, EventArgs e)
        {
            duplicateTool();
        }

        public void duplicateTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            DuplicateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_C, (IntPtr)3014657);
        }

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
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, zoom
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomToolButton_Click(object sender, EventArgs e)
        {
            zoomTool();
        }

        public void zoomTool()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            zoomToolButton.BackColor = Color.FromArgb(0, 102, 204);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_Z, (IntPtr)2883585);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Supprime tous les objets sélectionnés
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du clique
        ///
        ////////////////////////////////////////////////////////////////////////
        private void deleteToolButton_Click(object sender, EventArgs e)
        {
            deleteTool();
        }

        public void deleteTool()
        {
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_Del, (IntPtr)22216705);
            //supprimerToolStripMenuItem.Enabled = false;
            parent_.verificationDuNombreElementChoisi();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationLigne__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation ligne noire
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void lineObjectButton_Click(object sender, EventArgs e)
        {
            lineObject();
        }

        public void lineObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            lineObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(lineObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_L, (IntPtr)2490368);
        }

        private void greenLineObjectButton_Click(object sender, EventArgs e)
        {
        }

        private void redLineObjectButton_Click(object sender, EventArgs e)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationPoteau__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation poteau
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void postObjectButton_Click(object sender, EventArgs e)
        {
            postObject();
        }

        public void postObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            postObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(postObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_P, (IntPtr)1638401);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void outilsCreationMurs__Click(object sender, EventArgs e)
        ///
        /// Cette fonction change l'état et la couleur du bouton sur la barre d'outils
        /// qui correspond à l'état, creation mur
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void wallObjectButton_Click(object sender, EventArgs e)
        {
            wallObject();
        }

        public void wallObject()
        {
            hideObjectMenu();
            setDefaultUnselectedColors();
            wallObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(wallObjectPicture);
            FonctionsNatives.repartirMessage((int)256, (IntPtr)Constants.Key_M, (IntPtr)3276801);
        }

        private void teleportObjectButton_Click(object sender, EventArgs e)
        {
        }

        private void bridgeObjectButton_Click(object sender, EventArgs e)
        {
        }

        private void hideObjectMenu()
        {
            if (editionObjectMenu.Width > 0)
            {
                ShowObjectMenu.Stop();
                HideObjectMenu.Start();
            }
        }

        private void setDefaultUnselectedColors()
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

        private void setCurrentObjet(PictureBox objectPicture)
        {
            currentToolButton.BackColor = Color.FromArgb(0, 102, 204);
            currentObjectPicture.Image = objectPicture.Image;
            currentToolButton.Visible = true;
        }

        private void HideObjectsMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width > 0)
                editionObjectMenu.Width -= 5;
            else
                HideObjectMenu.Stop();
        }

        private void ShowObjectsMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width < 35)
                editionObjectMenu.Width += 5;
            else
                ShowObjectMenu.Stop();
        }

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
                    if (actualColor.A > 175)
                        newBitmap.SetPixel(i, j, newColor);
                    //else
                        //newBitmap.SetPixel(i, j, actualColor);
                }
            }
            return newBitmap;
        }
    }
}