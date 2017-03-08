///////////////////////////////////////////////////////////////////////////
/// @file AffichageTexte.cpp
/// @author Olivier St-Amour
/// @date 2016-03-29
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <string>
#include <FTGL/ftgl.h>
#include "ProjectionOrtho.h"
#include "ProfilUtilisateur.h"
#include "Vue.h"
#include "AffichageTexte.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn AffichageTexte::AffichageTexte()
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
AffichageTexte::AffichageTexte(vue::Vue* vue, ProfilUtilisateur* profil)
	: vue_{ vue }, profil_{ profil }
{
    assert(!font_.Error());
    font_.FaceSize(16);
    reinitialiserChrono();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn AffichageTexte::~AffichageTexte()
///
/// Destructeur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
AffichageTexte::~AffichageTexte()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::demarrerChrono()
///
/// Fonction qui permet de démarrer le chronomètre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::demarrerChrono()
{
    if (enPause_)
    {
        // Le temps du début est le temps courant soustrait du temps à la dernière pause.
        debut_ = std::chrono::system_clock::now() - (pause_ - debut_);
        enPause_ = false;
    }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::pauseChrono()
///
/// Fonction qui permet de mettre en pause le chronomètre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::pauseChrono()
{
    if (!enPause_)
    {
        pause_ = std::chrono::system_clock::now();
        enPause_ = true;
    }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::reinitialiserChrono()
///
/// Fonction qui permet de réinitialiser (0) le chronomètre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::reinitialiserChrono()
{
    debut_ = std::chrono::system_clock::now();
    pause_ = std::chrono::system_clock::now();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::afficher()
///
/// Fonction qui permet de faire l'affiche du profil et du chrono.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::afficher()
{
    glm::ivec2 dimensions = vue_->obtenirProjection().obtenirDimensionCloture();
    
    // Positionner le texte à un certain décallage par rapport à la clôture.
    FTPoint positionProfil(OFFSET_X, dimensions.y - OFFSET_Y, 0.0);
    FTPoint positionTemps(OFFSET_X, OFFSET_Y, 0.0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // TODO: figurer comment changer la couleur du texte.
    glColor3f(1.0, 1.0, 1.0);

    if (profilEstAffiche_)
    {
        std::string profil = profil_->obtenirNomDernierProfil();
        font_.Render(profil.c_str(), -1, positionProfil);
    }

    if (tempsEstAffiche_)
    {
        std::chrono::time_point<std::chrono::system_clock> courant = std::chrono::system_clock::now();

        double duree = 0.0;
        if (!enPause_)
        {
            // Si on ne se trouve pas en pause, on affiche la durée entre le début et le temps courant.
            duree = std::chrono::duration<double>(courant - debut_).count() + duree;
        }
        else
        {
            // Si on se trouve en pause, on affiche la durée entre la pause et le temps courant.
            duree = std::chrono::duration<double>(pause_ - debut_).count();
        }

        std::string secondes{ std::to_string((int)duree % 60) };
        // Conserver le format SS si le temps est moins de 10 sec.
        if (secondes.size() < 2)
        {
            secondes.insert(0, "0");
        }

        std::string minutes{ std::to_string(((int)duree / 60) % 60) };
        // Conserver le format MM si le temps est moins de 10 minutes.
        if (minutes.size() < 2)
        {
            minutes.insert(0, "0");
        }

        // Formatage du temps sous la forme "MM : SS".
        std::string compteur = minutes + " : " + secondes;
        font_.Render(compteur.c_str(), -1, positionTemps);
    }
    glPopAttrib();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////