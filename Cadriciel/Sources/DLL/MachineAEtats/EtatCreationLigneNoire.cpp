///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationLigneNoire.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

EtatCreationLigneNoire::EtatCreationLigneNoire()
{
	std::cout << "Creation de ligne" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationLigne>();
}

EtatCreationLigneNoire::~EtatCreationLigneNoire()
{

}

void EtatCreationLigneNoire::gererClicGaucheEnfonce(const int& x, const int& y)
{
	//std::cout << x << " " << y << std::endl;
}

void EtatCreationLigneNoire::gererClicGaucheRelache(const int& x, const int& y)
{
	//Premier clic
	if (!enCreation_)
	{
		enCreation_ = true;
		dernierePositionLigne_ = { 0, 0, 0 };
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		visiteur_->assignerPositionRelative(positionPremierClic_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		
		referencePremierNoeud_ = visiteur_.get()->obtenirReferenceNoeud();
		referenceDernierNoeud_ = referencePremierNoeud_;
	}
	//Clic avec CTRL enfoncee
	else if (enCreation_ && toucheCtrlEnfonce_)
	{
		// Création du nouveau noeud et assignation au parent.
		std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
		referenceDernierNoeud_->ajouter(nouveauNoeud);
		referenceDernierNoeud_ = nouveauNoeud;

		// Assigner la position relative au nouveau noeud.
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionDeuxiemeClic_);
		dernierePositionLigne_ = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionDeuxiemeClic_);
		positionPremierClic_ = positionDeuxiemeClic_;

	}
	// Dernier Clic avec CTRL relachee
	else
	{
		dernierePositionLigne_ = { 0, 0, 0 };
		referencePremierNoeud_ = nullptr;
		referenceDernierNoeud_ = nullptr;
		enCreation_ = false;
	}
}

void EtatCreationLigneNoire::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(referencePremierNoeud_);
		
		dernierePositionLigne_ = { 0, 0, 0 };
		referencePremierNoeud_ = nullptr;
		referenceDernierNoeud_ = nullptr;
		enCreation_ = false;
	}
}

void EtatCreationLigneNoire::gererMouvementSouris(const int& x, const int& y)
{
	glm::dvec3 positionCurseur;
	glm::dvec3 nouvellePositionLigne;
	glm::dvec3 positionRelativeLigne;
	double angle = 0;
	double distance = 0;

	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionCurseur);

		angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionCurseur);
		//angle = angle - referenceDernierNoeud_->obtenirParent()->obtenirAngleRotation();

		referenceDernierNoeud_->assignerAngleRotation(angle);

		distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionCurseur);
		//distance = distance / referenceDernierNoeud_->obtenirParent()->obtenirFacteurDimension();

		referenceDernierNoeud_->assignerFacteurDimension(distance);

		nouvellePositionLigne = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionCurseur);		
		positionRelativeLigne = nouvellePositionLigne - dernierePositionLigne_;
		referenceDernierNoeud_->assignerPositionRelative(positionRelativeLigne);
	}
}

void EtatCreationLigneNoire::gererToucheControlEnfoncee()
{
	if (!toucheCtrlEnfonce_)
	{
		toucheCtrlEnfonce_ = true;
	}
}

void EtatCreationLigneNoire::gererToucheControlRelachee()
{
	toucheCtrlEnfonce_ = false;
}

void EtatCreationLigneNoire::effectuerOperation()
{

}