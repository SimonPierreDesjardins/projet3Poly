﻿////////////////////////////////////////////////
/// @file   PersonnalisationSideMenu.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using ModeEnum;
using System.Drawing;
using System.Windows.Forms;
using System.Text;

namespace ui
{
    public partial class PersonnalisationSideMenu : UserControl
    {
        Window parent_;
        ColorSelector wheelColorSelector;
        ColorSelector robotColorSelector;
        ModeleSelector carSelector;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PersonnalisationSideMenu(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public PersonnalisationSideMenu(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            wheelColorSelector = new ColorSelector((int)VehiculePiece.VehiculePiece.WHEELS);
            robotColorSelector = new ColorSelector((int)VehiculePiece.VehiculePiece.BODY);
            carSelector = new ModeleSelector();

            StringBuilder str = new StringBuilder(100);
            FonctionsNatives.obtenirCheminFichierZoneDefaut(str, str.Capacity);
            string PathToDefaultZone = str.ToString();

            FonctionsNatives.assignerCheminFichierZone(PathToDefaultZone);
            FonctionsNatives.charger();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void returnMainMenu_Button_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void returnMainMenu_Button_Click(object sender, System.EventArgs e)
        {
            goMenuPrincipal();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goMenuPrincipal()
        ///
        /// Cette fonction enlève les composantes du mode personnalisation, ajoute ceux du
        /// du mode principal et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goMenuPrincipal()
        {
            setDefaultUnselectedColors();
            parent_.viewPort.Controls.Remove(parent_.personnalisationSideMenu);
            parent_.mainMenu = new MainMenu(parent_);

            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            parent_.viewPort.Visible = true;
            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void wheelColor_Button_Click(object sender, EventArgs e)
        ///
        /// Affiche la palette de couleur pour permettre a l'utilisateur de modifier
        /// la couleur des roues
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void wheelColor_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            wheelColorLabel.ForeColor = Color.Silver;
            wheelColor_Button.BackColor = Color.FromArgb(0, 102, 204);

            if (parent_.viewPort.Controls.Contains(wheelColorSelector))
                return;

            wheelColorSelector = new ColorSelector((int)VehiculePiece.VehiculePiece.WHEELS);
            parent_.viewPort.Controls.Add(wheelColorSelector);
            wheelColorSelector.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            wheelColorSelector.Location = new Point(parent_.viewPort.Width - wheelColorSelector.Width, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void carColor_Button_Click(object sender, EventArgs e)
        ///
        /// Affiche la palette de couleur pour permettre a l'utilisateur de modifier
        /// la couleur du chasis
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void carColor_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            robotColorLabel.ForeColor = Color.Silver;
            carColor_Button.BackColor = Color.FromArgb(0, 102, 204);

            if (parent_.viewPort.Controls.Contains(robotColorSelector))
                return;

            robotColorSelector = new ColorSelector((int)VehiculePiece.VehiculePiece.BODY);
            parent_.viewPort.Controls.Add(robotColorSelector);
            robotColorSelector.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            robotColorSelector.Location = new Point(parent_.viewPort.Width - robotColorSelector.Width, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void carChange_Button_Click(object sender, EventArgs e)
        ///
        /// Permet a l'utilisateur de changer le chasis (modele obj)
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void carChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            robotChangeLabel.ForeColor = Color.Silver;
            carChange_Button.BackColor = Color.FromArgb(0, 102, 204);

            parent_.viewPort.Controls.Add(carSelector);
            carSelector.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
            carSelector.Location = new Point(parent_.viewPort.Width - carSelector.Width, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void tableChange_Button_Click(object sender, EventArgs e)
        ///
        /// Permet a l'utilisateur de changer la table (modele obj)
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void tableChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            changeTableLabel.ForeColor = Color.Silver;
            tableChange_Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void musicChange_Button_Click(object sender, EventArgs e)
        ///
        /// Permet a l'utilisateur de changer la musique lors de la simulation
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void musicChange_Button_Click(object sender, System.EventArgs e)
        {
            setDefaultUnselectedColors();
            musicChangeLabel.ForeColor = Color.Silver;
            musicChange_Button.BackColor = Color.FromArgb(0, 102, 204);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setDefaultUnselectedColors(object sender, EventArgs e)
        ///
        /// Remet la couleur par défaut aux boutons et enlève la palette de couleur
        /// si elle est présent en appliquant les changements
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setDefaultUnselectedColors()
        {
            returnMainMenu_Button.BackColor = Color.Transparent;
            wheelColor_Button.BackColor = Color.Transparent;
            carColor_Button.BackColor = Color.Transparent;
            carChange_Button.BackColor = Color.Transparent;
            tableChange_Button.BackColor = Color.Transparent;
            musicChange_Button.BackColor = Color.Transparent;

            returnLabel.ForeColor = Color.Silver;
            wheelColorLabel.ForeColor = Color.Silver;
            robotColorLabel.ForeColor = Color.Silver;
            robotChangeLabel.ForeColor = Color.Silver;
            changeTableLabel.ForeColor = Color.Silver;
            musicChangeLabel.ForeColor = Color.Silver;

            if (parent_.viewPort.Controls.Contains(wheelColorSelector))
            {
                wheelColorSelector.applyChanges();
                parent_.viewPort.Controls.Remove(wheelColorSelector);
            }   
            else if (parent_.viewPort.Controls.Contains(robotColorSelector))
            {
                robotColorSelector.applyChanges();
                parent_.viewPort.Controls.Remove(robotColorSelector);
            }
            else if (parent_.viewPort.Controls.Contains(carSelector))
            {
                parent_.viewPort.Controls.Remove(carSelector);
            }

        }
    }
}
