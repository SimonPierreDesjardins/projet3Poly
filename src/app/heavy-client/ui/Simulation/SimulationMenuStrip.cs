////////////////////////////////////////////////
/// @file   SimulationMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-02-16
///
////////////////////////////////////////////////
using System;
using System.Windows.Forms;
using ModeEnum;

namespace ui
{
    public partial class SimulationMenuStrip : UserControl
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public SimulationMenuStrip(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public SimulationMenuStrip(Window parent)
        {
            InitializeComponent();
            parent_ = parent;

            menuStrip1.Renderer = new myRenderer();
            menuStrip1.Visible = false;
            crochetPourVue();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'action de retour vers le mode principal
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            goMenuPrincipal();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goMenuPrincipal()
        ///
        /// Cette fonction enlève les composantes du mode simulation, ajoute ceux du
        /// du mode principal et change de mode
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goMenuPrincipal()
        {
            parent_.estEnPause = false;
            parent_.picturePause.Visible = false;

            parent_.mainMenu = new MainMenu(parent_);

            parent_.configuration.deallocateCurrentProfilToolStrip();
            parent_.viewPort.Controls.Remove(parent_.simulationMenuStrip);

            parent_.viewPort.Controls.Add(parent_.mainMenu);
            parent_.mainMenu.Dock = DockStyle.Left;

            Program.peutAfficher = false;
            parent_.viewPort.Refresh();

            FonctionsNatives.assignerMode(Mode.MENU_PRINCIPAL);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue orthographique
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orthoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orthoView();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void orthoView()
        ///
        /// Cette fonction assigne la vue orthographique et change les crochets
        /// pour la vue dans le menuStrip
        ///
        ////////////////////////////////////////////////////////////////////////
        public void orthoView()
        {
            FonctionsNatives.assignerVueOrtho();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue orbite
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            orbiteView();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void orbiteView()
        ///
        /// Cette fonction assigne la vue orbite et change les crochets
        /// pour la vue dans le menuStrip
        ///
        ////////////////////////////////////////////////////////////////////////
        public void orbiteView()
        {
            FonctionsNatives.assignerVueOrbite();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void premierePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Appel l'outil pour la vue première personne
        /// 
        /// @param objet sender: control qui gère l'action
        /// @param EventsArgs e: evenement du click
        ///
        ////////////////////////////////////////////////////////////////////////
        private void premierePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            firstPersonView();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void firstPersonView()
        ///
        /// Cette fonction assigne la vue première personne et change les crochets
        /// pour la vue dans le menuStrip
        ///
        ////////////////////////////////////////////////////////////////////////
        public void firstPersonView()
        {
            FonctionsNatives.assignerVuePremierePersonne();
            FonctionsNatives.redimensionnerFenetre(parent_.viewPort.Width, parent_.viewPort.Height);
            crochetPourVue();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void crochetPourVue()
        ///
        /// Gère l'évènement de changement de visibilité de la barre de menu édition.
        /// 
        ////////////////////////////////////////////////////////////////////////
        private void crochetPourVue()
        {
            switch (FonctionsNatives.obtenirTypeVue())
            {
                case 2:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = false;
                    premierePersonneToolStripMenuItem.Checked = true;
                    break;
                case 1:
                    orbiteToolStripMenuItem.Checked = true;
                    orthoToolStripMenuItem.Checked = false;
                    premierePersonneToolStripMenuItem.Checked = false;
                    break;

                case 0:
                default:
                    orbiteToolStripMenuItem.Checked = false;
                    orthoToolStripMenuItem.Checked = true;
                    premierePersonneToolStripMenuItem.Checked = false;
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void goIntoPause()
        ///
        /// Cette fonction change l'état de la valeure estEnPause et change la
        /// visibilité de l'image pause et du menuStrip en conséquence
        ///
        ////////////////////////////////////////////////////////////////////////
        public void goIntoPause()
        {
            parent_.estEnPause = !parent_.estEnPause;
            parent_.picturePause.Visible = parent_.estEnPause;
            menuStrip1.Visible = parent_.estEnPause;
        }
    }
}
