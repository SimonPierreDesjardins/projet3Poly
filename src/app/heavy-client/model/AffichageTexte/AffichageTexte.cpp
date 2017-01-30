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
#include "FacadeModele.h"
#include "ProjectionOrtho.h"
#include "ProfilUtilisateur.h"
#include "AffichageTexte.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn AffichageTexte::AffichageTexte()
///
/// Constructeur par d�faut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
AffichageTexte::AffichageTexte()
{
    assert(!font_.Error());
    font_.FaceSize(16);
    profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    vue_ = FacadeModele::obtenirInstance()->obtenirVue();
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
/// Fonction qui permet de d�marrer le chronom�tre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::demarrerChrono()
{
    if (enPause_)
    {
        // Le temps du d�but est le temps courant soustrait du temps � la derni�re pause.
        debut_ = std::chrono::system_clock::now() - (pause_ - debut_);
        enPause_ = false;
    }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::pauseChrono()
///
/// Fonction qui permet de mettre en pause le chronom�tre de l'affichage.
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
/// Fonction qui permet de r�initialiser (0) le chronom�tre de l'affichage.
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
    glm::ivec2 dimensions = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
    
    // Positionner le texte � un certain d�callage par rapport � la cl�ture.
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
            // Si on ne se trouve pas en pause, on affiche la dur�e entre le d�but et le temps courant.
            duree = std::chrono::duration<double>(courant - debut_).count() + duree;
        }
        else
        {
            // Si on se trouve en pause, on affiche la dur�e entre la pause et le temps courant.
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