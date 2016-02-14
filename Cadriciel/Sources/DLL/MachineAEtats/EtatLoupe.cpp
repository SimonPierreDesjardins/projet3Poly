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
		if (estClickDrag()){
			if (dessineRectangle)
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition_, glm::ivec2(x, y));
			else{
				aidegl::initialiserRectangleElastique(anchor);
				// redessiner le rectangle
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
			}
		}
	}
	EtatAbstrait::gererMouvementSouris(x, y);
	
}
