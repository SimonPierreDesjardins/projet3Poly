#include "FacadeModele.h"
#include "Vue.h"
#include "EtatLoupe.h"
#include "AideGl.h"

void EtatLoupe::gererClicGaucheEnfonce(const int& x, const int& y){
	EtatAbstrait::gererClicGaucheEnfonce(x, y);

	anchor = glm::ivec2(x, y);
	currentPosition = anchor;

}
void EtatLoupe::gererClicGaucheRelache(const int& x, const int& y){
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (dessineRectangle){

		if (toucheAltEnfonce_){
			// unzoom dat shit
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(anchor, glm::ivec2(x, y));
		}
		else{
			// zoom dat shit
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(anchor, glm::ivec2(x, y));
		}

		dessineRectangle = false;
	}
}

void EtatLoupe::gererMouvementSouris(const int & x, const int& y){
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_){
		
		if (dessineRectangle){
			aidegl::initialiserRectangleElastique(anchor);
			aidegl::mettreAJourRectangleElastique(anchor, currentPosition, glm::ivec2(x, y));
			aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));
		}

		// Verifier si le deplacement est de plus de 3 pixel
		if (!dessineRectangle && (x > anchor.x + 3 || x < anchor.x - 3 || y > anchor.y + 3 || y < anchor.y - 3)){
			// redessiner le rectangle
			
			dessineRectangle = true;
		}

		currentPosition = glm::ivec2(x, y);
	}
}