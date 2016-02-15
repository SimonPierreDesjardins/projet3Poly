///////////////////////////////////////////////////////////////////////////////
/// @file EtatLoupe.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2016-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "EtatLoupe.h"
#include "AideGl.h"
#include "OpenGL_Programme.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatLoupe::gererClicGaucheRelache(const int& x, const int& y)
///
/// Zoom sur la zone et unzoom de la zone si la touche alt est enfoncée
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatLoupe::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (estClickDrag()) {
		if (toucheAltEnfonce_) {
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(anchor, glm::ivec2(x, y));
		}
		else{
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(anchor, glm::ivec2(x, y));
		}
	}

	if (dessineRectangle) {
		FacadeModele::obtenirInstance()->continuerAffichage();
		aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));
		dessineRectangle = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatLoupe::gererMouvementSouris(const int & x, const int& y)
///
/// Crée un rectangle élastique si le bouton gauche est appuyé sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatLoupe::gererMouvementSouris(const int & x, const int& y)
{
	
	if (clicGaucheEnfonce_) {
		// Initialisation du rectangle elastique
		if (estClickDrag()) {
			if (dessineRectangle)
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition_, glm::ivec2(x, y));

			else {
				aidegl::initialiserRectangleElastique(anchor);
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
				//Placer notre nouveau rectangle initial, assure fonctionnement de mise à jour
				aidegl::mettreAJourRectangleElastique(anchor, anchor, glm::ivec2(x, y));
			}	
		}
		//TODO Arrêter de dessiner un rectangle si on quite le clickdrag
	}
	EtatAbstrait::gererMouvementSouris(x, y);
	
}
