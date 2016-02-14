#include "FacadeModele.h"
#include "Vue.h"
#include "EtatLoupe.h"
#include "AideGl.h"
#include "OpenGL_Programme.h"

void EtatLoupe::gererClicGaucheRelache(const int& x, const int& y){
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (estClickDrag()){
		if (toucheAltEnfonce_){
			// unzoom dat shit
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(anchor, glm::ivec2(x, y));
		}
		else{
			// zoom dat shit
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(anchor, glm::ivec2(x, y));
		}
	}

	if (dessineRectangle){
		FacadeModele::obtenirInstance()->continuerAffichage();
		
		aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));

		dessineRectangle = false;
	}
}

void EtatLoupe::gererMouvementSouris(const int & x, const int& y){
	
	if (clicGaucheEnfonce_){
		// Initialisation du rectangle elastique
		if (estClickDrag()){
			if (!dessineRectangle){
				aidegl::initialiserRectangleElastique(anchor);
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
			}	
			// redessiner le rectangle
			aidegl::mettreAJourRectangleElastique(anchor, currentPosition, glm::ivec2(x, y));
		}
	}
	EtatAbstrait::gererMouvementSouris(x, y);
	
}
