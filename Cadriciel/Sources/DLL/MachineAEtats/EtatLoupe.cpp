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

	if (rectum){
		
		
		
		if (toucheAltEnfonce_){
			// unzoom dat shit

		}
		else{
			// zoom dat shit
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(anchor, glm::ivec2(x, y));
		}

		rectum = false;
	}
}

void EtatLoupe::gererMouvementSouris(const int & x, const int& y){
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_){
		
		if (rectum){
			aidegl::initialiserRectangleElastique(anchor);
			aidegl::mettreAJourRectangleElastique(anchor, currentPosition, glm::ivec2(x, y));
			aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));
			
		}
		// Verifier si le deplacement est de plus de 3 pixel
		if (!rectum && (x > anchor.x + 3 || x < anchor.x - 3 || y > anchor.y + 3 || y < anchor.y - 3)){

			// redessiner le rectangle

			rectum = true;
		}

		currentPosition = glm::ivec2(x, y);
	}
}