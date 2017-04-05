////////////////////////////////////////////////
/// @file   OnlineRaceMenuStrip.cs
/// @author Frédéric Grégoire
/// @date   2017-03-29
///
////////////////////////////////////////////////
using System;

namespace ui
{
    public partial class OnlineRaceMenuStrip : SimMenuStrip
    {
        Window parent_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public OnlineRaceMenuStrip(Window parent)
        ///
        /// Cette fonction initialize les controles sur user control et assigne les attributs.
        ///
        /// @param Window parent: reference a la fenetre principal du programme
        /// 
        ////////////////////////////////////////////////////////////////////////
        public OnlineRaceMenuStrip(Window parent) : base(parent)
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
        override public void goMenuPrincipal()
        {
            base.goMenuPrincipal();
            parent_.viewPort.Controls.Remove(this);
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
        override public void orthoView()
        {
            base.orthoView();
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
        override public void orbiteView()
        {
            base.orbiteView();
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
        override public void firstPersonView()
        {
            base.firstPersonView();
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
        override public void goIntoPause()
        {
            base.goIntoPause();
            parent_.picturePause.Visible = parent_.estEnPause;
            menuStrip1.Visible = parent_.estEnPause;
        }
    }
}
