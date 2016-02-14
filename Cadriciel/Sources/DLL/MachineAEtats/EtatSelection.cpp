///////////////////////////////////////////////////////////////////////////
/// @file EtatSelection.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatSelection.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "AideGl.h"
#include "glm\glm.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatSelection::EtatSelection()
///
/// Constructeur par défault. Assigne arbre_ à arbre courant
///
////////////////////////////////////////////////////////////////////////
EtatSelection::EtatSelection()
{
	visiteurSelection_ = std::make_unique<VisiteurSelection>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	vue_ = FacadeModele::obtenirInstance()->obtenirVue();
	typeEtat_ = SELECTION;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatSelection::~EtatSelection()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatSelection::~EtatSelection()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction arrète l'affichage du rectangle élastique et génère un clique gauche sur tous
/// les objets dans le rectangle.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (dessineRectangle){
		FacadeModele::obtenirInstance()->continuerAffichage();

		aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));

		dessineRectangle = false;
	}

	if (estClickDrag())
	{
		gererDragGauche(anchor.x, anchor.y, x, y);
	}
	else
	{
		gererClicGauche((anchor.x + currentPosition_.x) / 2, (anchor.y + currentPosition_.y) / 2);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction affiche un rectangle élastique si le clique gauche est appuyé.
/// Sinon elle ne fait rien.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererMouvementSouris(const int & x, const int& y){

	if (clicGaucheEnfonce_){
		// Initialisation du rectangle elastique
		if (estClickDrag()){

			if (dessineRectangle)
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition_, glm::ivec2(x, y));
			else{
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererClicGauche(const int& x, const int& y)
///
/// Cette fonction sélectionne un objet selon la position de la souris.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererClicGauche(const int& x, const int& y)
{
	visiteurSelection_->assignerEstDrag(false);
	glm::dvec3 positionRelative = { 0.0, 0.0, 0.0 };
	
	if (vue_ != nullptr)
	{
		vue_->convertirClotureAVirtuelle(x, y, positionRelative);
	}
	
	visiteurSelection_->assignerPositionRelative(positionRelative);
	
	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurSelection_.get());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
///
/// Cette fonction crée un rectangle élastique selon la position x et y du début du drag et x et y a la fin.
///
/// @param const int& xAvant: Position initiale en x
/// @paramconst int& yAvant: Position initiale en y
/// @paramconst int& xApres: Position finale en x
/// @paramconst int& yApres: Position finale en y
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	visiteurSelection_->assignerEstDrag(true);
	glm::dvec3 positionRelativeAvant, positionRelativeApres;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xAvant, yAvant, positionRelativeAvant);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xApres, yApres, positionRelativeApres);
	visiteurSelection_->assignerPositionRectElast(positionRelativeAvant, positionRelativeApres);
	
	arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
	arbre_->accepterVisiteur(visiteurSelection_.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererToucheControlEnfoncee()
///
/// Cette fonction gère la touche Control relâchée
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererToucheControlEnfoncee()
{
	visiteurSelection_->assignerControl(true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererToucheControlRelachee()
///
/// Cette fonction gère la touche Control relâchée
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererToucheControlRelachee()
{
	visiteurSelection_->assignerControl(false);
}