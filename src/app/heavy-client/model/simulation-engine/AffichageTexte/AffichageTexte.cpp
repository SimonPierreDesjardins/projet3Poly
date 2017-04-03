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
	assert(!fontCentury_.Error());
	fontCentury_.FaceSize(26);
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
	duree_ = 0.0;
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
	// Valeurs arbitraires afin de placer le texte 
    FTPoint positionProfil(OFFSET_X, dimensions.y - OFFSET_Y, 0.0);
    FTPoint positionTemps(OFFSET_X, OFFSET_Y, 0.0);
	FTPoint positionPieces(dimensions.x - OFFSET_X - 100, dimensions.y - OFFSET_Y, 0.0);
	//Rajouter la position des pieces des autres joueurs
	FTPoint positionFinModePieces(dimensions.x - OFFSET_X - 700, dimensions.y - OFFSET_Y - 50, 0.0);
	FTPoint positionAvantDebutCourse(dimensions.x - OFFSET_X - 700, dimensions.y - OFFSET_Y - 50, 0.0);
	FTPoint positionTempsFinal(dimensions.x - OFFSET_X - 700, dimensions.y - OFFSET_Y - 50, 0.0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // TODO: figurer comment changer la couleur du texte.
    glColor3f(1.0, 1.0, 1.0);
	if (tempsFinal_)
	{
		std::string secondesCourse{ std::to_string((int)(profil_->obtenirRaceTime()) % 60) };
		if (secondesCourse.size() < 2)
		{
			secondesCourse.insert(0, "0");
		}
		std::string minutesCourse{ std::to_string(((int)(profil_->obtenirRaceTime()) / 60) % 60) };
		if (minutesCourse.size() < 2)
		{
			minutesCourse.insert(0, "0");
		}

		// Formatage du temps sous la forme "MM : SS".
		std::string tempsFinalCourse = "Le premier joueur a fini avec un temps de " + minutesCourse + " : " + secondesCourse;
		font_.Render(tempsFinalCourse.c_str(), -1, positionTempsFinal);

	}
	if (avantDebutCourse_)
	{
		std::string avantDebut = "Le depart de la course va debuter a 1 minute";

		font_.Render(avantDebut.c_str(), -1, positionAvantDebutCourse);
	}
	if (piecesEstAffiche_)
	{
		std::string pieceString = std::to_string(profil_->obtenirPieces());
		pieceString = pieceString + " pieces";

		font_.Render(pieceString.c_str(), -1, positionPieces);
	}
	if (finModePieces_)
	{
		std::string finMode = "Fin du mode pieces, retourner au menu principal!";

		fontCentury_.Render(finMode.c_str(), -1, positionFinModePieces);
	}
    if (profilEstAffiche_)
    {
        std::string profil = profil_->obtenirNomDernierProfil();
        font_.Render(profil.c_str(), -1, positionProfil);
    }

    if (tempsEstAffiche_)
    {
        std::chrono::time_point<std::chrono::system_clock> courant = std::chrono::system_clock::now();

		duree_ = 0.0;
        if (!enPause_)
        {
            // Si on ne se trouve pas en pause, on affiche la durée entre le début et le temps courant.
			duree_ = std::chrono::duration<double>(courant - debut_).count() + duree_;
        }
        else
        {
            // Si on se trouve en pause, on affiche la durée entre la pause et le temps courant.
			duree_ = std::chrono::duration<double>(pause_ - debut_).count();
        }

        std::string secondes{ std::to_string((int)duree_ % 60) };
        // Conserver le format SS si le temps est moins de 10 sec.
        if (secondes.size() < 2)
        {
            secondes.insert(0, "0");
        }

        std::string minutes{ std::to_string(((int)duree_ / 60) % 60) };
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::obtenirDuree()
///
/// Fonction qui permet d'obtenir la durée écoulé du mode.
///
/// @return durée écoulée (double)
///
////////////////////////////////////////////////////////////////////////
double AffichageTexte::obtenirDuree()
{
	return duree_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::assignerPiecesEstAfficher(bool estAffiche)
///
/// Fonction qui d'afficher le nombre de pièces collectées
///
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::assignerPiecesEstAfficher(bool estAffiche)
{
	piecesEstAffiche_ = estAffiche;
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::assignerFinModePiecesEstAfficher(bool estAffiche)
///
/// Fonction qui d'afficher la fin du mode pieces
///
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::assignerFinModePiecesEstAfficher(bool estAffiche)
{
	finModePieces_ = estAffiche;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::assignerAvantDebutCourse(bool estAffiche)
///
/// Fonction qui affiche un texte indiquant quand la course va commencer
///
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::assignerAvantDebutCourse(bool estAffiche)
{
	avantDebutCourse_ = estAffiche;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::assignerTempsFinal(bool estAffiche)
///
/// Fonction qui affiche un texte indiquant le temps a la fin de la course
///
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void AffichageTexte::assignerTempsFinal(bool estAffiche)
{
	tempsFinal_ = estAffiche;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool AffichageTexte::obtenirTempsFinal()
///
/// Fonction qui retourne si le temps final est affichee
///
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
bool AffichageTexte::obtenirTempsFinal()
{
	return tempsFinal_;

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////