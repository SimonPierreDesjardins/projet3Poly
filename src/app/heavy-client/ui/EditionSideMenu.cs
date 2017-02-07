using System;
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

            //setToolTips();
            editionObjectMenu.Width = 0;
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
            setDefaultUnselectedColors();
            selectToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton S : sélection
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)83, (IntPtr)2031617);
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
            setDefaultUnselectedColors();
            MoveToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton D : Déplacement
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)68, (IntPtr)2097153);
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
            setDefaultUnselectedColors();
            RotateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton R : Rotation
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)82, (IntPtr)1245185);
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
            setDefaultUnselectedColors();
            ScaleToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton E : Mise a échelle
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)69, (IntPtr)1179649);
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
            setDefaultUnselectedColors();
            DuplicateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton C : Duplication
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)67, (IntPtr)3014657);
        }

        private void createToolButton_Click(object sender, EventArgs e)
        {
            if (editionObjectMenu.Width == 0)
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
            setDefaultUnselectedColors();
            zoomToolButton.BackColor = Color.FromArgb(0, 102, 204);
            //Bouton Z : Zoom
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)90, (IntPtr)2883585);
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
            //Button Del : Delete
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)46, (IntPtr)22216705);
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
            setDefaultUnselectedColors();
            lineObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(lineObjectPicture);
            //Bouton L : Creation ligne
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)76, (IntPtr)2490368);
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
            setDefaultUnselectedColors();
            postObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(postObjectPicture);
            //Bouton P : Creation poteau
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)80, (IntPtr)1638401);
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
            setDefaultUnselectedColors();
            wallObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            setCurrentObjet(wallObjectPicture);
            //Bouton M : Creation mur
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)77, (IntPtr)3276801);
        }

        private void teleportObjectButton_Click(object sender, EventArgs e)
        {
        }

        private void bridgeObjectButton_Click(object sender, EventArgs e)
        {
        }

        private void setDefaultUnselectedColors()
        {
            if (editionObjectMenu.Width > 0)
                HideObjectMenu.Start();

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

        /*private void setToolTips()
        {
            ToolTip selectToolTip = new ToolTip();
            selectToolTip.AutoPopDelay = 5000;
            selectToolTip.InitialDelay = 1000;
            selectToolTip.ReshowDelay = 500;
            selectToolTip.ShowAlways = true;
            selectToolTip.SetToolTip(selectToolButton, "Select tool");
            selectToolTip.SetToolTip(selectPictureBox, "Select tool");

            ToolTip deplacementToolTip = new ToolTip();
            deplacementToolTip.SetToolTip(MoveToolButton, "move tool");
            deplacementToolTip.SetToolTip(movePictureBox, "move tool");

            ToolTip rotateToolTip = new ToolTip();
            rotateToolTip.SetToolTip(RotateToolButton, "Rotate tool");
            rotateToolTip.SetToolTip(RotateToolButton, "Rotate tool");

            ToolTip scaleToolTip = new ToolTip();
            scaleToolTip.SetToolTip(ScaleToolButton, "Scale tool");
            scaleToolTip.SetToolTip(scalePictureBox, "Scale tool");

            ToolTip duplicateToolTip = new ToolTip();
            duplicateToolTip.SetToolTip(DuplicateToolButton, "Duplicate tool");
            duplicateToolTip.SetToolTip(duplicatePictureBox, "Duplicate tool");

            ToolTip createToolTip = new ToolTip();
            createToolTip.SetToolTip(createToolButton, "Create objects tool");
            createToolTip.SetToolTip(createPictureBox, "Create objects tool");

            ToolTip zoomToolTip = new ToolTip();
            zoomToolTip.SetToolTip(zoomToolButton, "Zoom tool");
            zoomToolTip.SetToolTip(zoomPictureBox, "Zoom tool");

            ToolTip deleteToolTip = new ToolTip();
            deleteToolTip.SetToolTip(deleteToolButton, "Delete tool");
            deleteToolTip.SetToolTip(deletePictureBox, "Delete tool");

            ToolTip currentObjectToolTip = new ToolTip();
            currentObjectToolTip.SetToolTip(currentToolButton, "Current object");
            currentObjectToolTip.SetToolTip(currentObjectPicture, "Current object");

            ToolTip lineToolTip = new ToolTip();
            lineToolTip.SetToolTip(lineObjectButton, "Line object");
            lineToolTip.SetToolTip(lineObjectPicture, "Line object");

            ToolTip greenLineToolTip = new ToolTip();
            greenLineToolTip.SetToolTip(greenLineObjectButton, "Green line object");
            greenLineToolTip.SetToolTip(greenLinePictureBox, "Green line object");

            ToolTip redLineToolTip = new ToolTip();
            redLineToolTip.SetToolTip(redLineObjectButton, "Red line object");
            redLineToolTip.SetToolTip(redLinePictureBox, "Red line object");

            ToolTip postToolTip = new ToolTip();
            postToolTip.SetToolTip(postObjectButton, "Post object");
            ToolTip postToolTip1 = new ToolTip();
            postToolTip1.SetToolTip(postObjectPicture, "Post object");

            ToolTip wallToolTip = new ToolTip();
            wallToolTip.SetToolTip(wallObjectButton, "Wall object");
            wallToolTip.SetToolTip(wallObjectPicture, "Wall object");

            ToolTip teleportorToolTip = new ToolTip();
            teleportorToolTip.SetToolTip(teleportObjectButton, "Teleportor object");
            teleportorToolTip.SetToolTip(teleportorPictureBox, "Teleportor object");

            ToolTip bridgeToolTip = new ToolTip();
            bridgeToolTip.SetToolTip(bridgeObjectButton, "Bridge object");
            bridgeToolTip.SetToolTip(bridgePictureBox, "Bridge object");
        }*/

        /*private void movePictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            ToolTip toolTip = new ToolTip();
            toolTip.AutoPopDelay = 5000;
            toolTip.InitialDelay = 1;
            toolTip.ReshowDelay = 500;
            toolTip.ShowAlways = true;

            toolTip.SetToolTip(movePictureBox, "Move Tool");
        }*/
    }
}
