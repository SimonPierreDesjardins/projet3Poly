using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

            editionObjectMenu.Width = 0;
            editionToolsMenu.Width = 0;

            ShowFullTools.Start();
        }

        private void ShowObjetMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width >= 200)
                ShowObjetMenu.Stop();
            else
                editionObjectMenu.Width += 5; 
        }

        private void ShowFullToolsTimer_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionToolsMenu.Width >= 200)
                ShowFullTools.Stop();
            else
                editionToolsMenu.Width += 5;                
        }

        private void HideFullMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionObjectMenu.Width != 0)
            {
                if (editionObjectMenu.Width > 0)
                    editionObjectMenu.Width -= 5;
                else
                    HideFullMenu.Stop();
            }
            else
            {
                if (editionToolsMenu.Width > 0)
                    editionToolsMenu.Width -= 5; 
                else
                    HideFullMenu.Stop();
            }
        }

        private void ShowSideToolMenu_Tick(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionToolsMenu.Width > 35)
                editionToolsMenu.Width -= 5;
            else
                ShowSideToolMenu.Stop();
        }

        public void animationHidingMenu()
        {
            HideFullMenu.Start();
            while (HideFullMenu.Enabled)
            {
                Application.DoEvents();
            }
        }

        private void menuToolButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.dessinerOpenGL();
            if (editionToolsMenu.Width >= 200)
                ShowSideToolMenu.Start();
            else
                ShowFullTools.Start();
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
            setDefaultUnselectedColors();
            selectToolButton.BackColor = Color.FromArgb(0, 102, 204);
            selectionLabel.ForeColor = Color.FromArgb(178, 216, 255);
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
            setDefaultUnselectedColors();
            MoveToolButton.BackColor = Color.FromArgb(0, 102, 204);
            deplacementLabel.ForeColor = Color.FromArgb(178, 216, 255);
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
            setDefaultUnselectedColors();
            RotateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            rotationLabel.ForeColor = Color.FromArgb(178, 216, 255);
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
            setDefaultUnselectedColors();
            ScaleToolButton.BackColor = Color.FromArgb(0, 102, 204);
            scaleLabel.ForeColor = Color.FromArgb(178, 216, 255);
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
            setDefaultUnselectedColors();
            DuplicateToolButton.BackColor = Color.FromArgb(0, 102, 204);
            duplicateLabel.ForeColor = Color.FromArgb(178, 216, 255);
            //Bouton C : Duplication
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)67, (IntPtr)3014657);
        }

        private void createToolButton_Click(object sender, EventArgs e)
        {
            animationHidingMenu();
            ShowObjetMenu.Start();
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
            setDefaultUnselectedColors();
            zoomToolButton.BackColor = Color.FromArgb(0, 102, 204);
            zoomLabel.ForeColor = Color.FromArgb(178, 216, 255);
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
            //Button Del : Delete
            parent_.viewPort.Focus();
            FonctionsNatives.repartirMessage((int)256, (IntPtr)46, (IntPtr)22216705);
            //supprimerToolStripMenuItem.Enabled = false;
            parent_.verificationDuNombreElementChoisi();
        }

        private void returnObjetButton_Click(object sender, EventArgs e)
        {
            animationHidingMenu();
            ShowFullTools.Start();
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
            setDefaultUnselectedColors();
            lineObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            lineLabel.ForeColor = Color.FromArgb(178, 216, 255);
            setCurrentObjet(lineObjectPicture, "Ligne noire");
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
            setDefaultUnselectedColors();
            postObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            postLabel.ForeColor = Color.FromArgb(178, 216, 255);
            setCurrentObjet(postObjectPicture, "Poteau");
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
            setDefaultUnselectedColors();
            wallObjectButton.BackColor = Color.FromArgb(0, 102, 204);
            wallLabel.ForeColor = Color.FromArgb(178, 216, 255);
            setCurrentObjet(wallObjectPicture, "Mur");
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
            //Tools
            selectToolButton.BackColor = Color.Transparent;
            MoveToolButton.BackColor = Color.Transparent;
            RotateToolButton.BackColor = Color.Transparent;
            ScaleToolButton.BackColor = Color.Transparent;
            DuplicateToolButton.BackColor = Color.Transparent;
            zoomToolButton.BackColor = Color.Transparent;

            selectionLabel.ForeColor = Color.Silver;
            deplacementLabel.ForeColor = Color.Silver;
            rotationLabel.ForeColor = Color.Silver;
            scaleLabel.ForeColor = Color.Silver;
            duplicateLabel.ForeColor = Color.Silver;
            zoomLabel.ForeColor = Color.Silver;
            currentObjectName.ForeColor = Color.Silver;

            //Objects
            lineObjectButton.BackColor = Color.Transparent;
            greenLineObjectButton.BackColor = Color.Transparent;
            redLineObjectButton.BackColor = Color.Transparent;
            postObjectButton.BackColor = Color.Transparent;
            wallObjectButton.BackColor = Color.Transparent;
            teleportObjectButton.BackColor = Color.Transparent;
            bridgeObjectButton.BackColor = Color.Transparent;

            lineLabel.ForeColor = Color.Silver;
            greenLigneLabel.ForeColor = Color.Silver;
            redLineLabel.ForeColor = Color.Silver;
            postLabel.ForeColor = Color.Silver;
            wallLabel.ForeColor = Color.Silver;
            teleportorLabel.ForeColor = Color.Silver;
            bridgeLabel.ForeColor = Color.Silver;

            currentToolButton.BackColor = Color.Transparent;
            currentToolButton.Visible = false;
        }

        private void setCurrentObjet(PictureBox objectPicture, String objectname)
        {
            currentToolButton.BackColor = Color.FromArgb(0, 102, 204);
            currentObjectName.ForeColor = Color.FromArgb(178, 216, 255);
            currentObjectName.Text = objectname;
            currentObjectPicture.Image = objectPicture.Image;
            currentToolButton.Visible = true;
        }
    }
}
