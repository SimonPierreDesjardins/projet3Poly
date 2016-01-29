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
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		glm::dvec3 positionRelative;
		for (int i = 0; i < 3; i++)
		{
			positionRelative[i] = referenceDernierNoeud_->obtenirParent()->obtenirPositionRelative()[i] - positionPremierClic_[i];
		}
		nouveauNoeud->assignerPositionRelative(positionRelative);

		/*
		visiteur_->assignerPositionRelative(positionPremierClic_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());

		referenceDernierNoeud_ = visiteur_.get()->obtenirReferenceNoeud();
		*/
	}
	// Dernier Clic avec CTRL relachee
	else
	{
		enCreation_ = false;
		referencePremierNoeud_ = nullptr;
		referenceDernierNoeud_ = nullptr;
	}
}

void EtatCreationLigneNoire::gererToucheEchappe()
{
	if (enCreation_)
	{
		//TODO: Changer pour reference premier Noeud.
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(referencePremierNoeud_);
		enCreation_ = false;
	}
}

void EtatCreationLigneNoire::gererMouvementSouris(const int& x, const int& y)
{
	glm::dvec3 positionVirtuelle;
	glm::dvec3 nouvellePosition;
	double angle = 0;
	double distance = 0;

	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);



		angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionVirtuelle);
		angle = angle - referenceDernierNoeud_->obtenirParent()->obtenirAngleRotation();


		referenceDernierNoeud_->assignerAngleRotation(angle);

		distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionVirtuelle);

		//distance = referenceDernierNoeud_->obtenirParent()->obtenirFacteurDimension();
		referenceDernierNoeud_->assignerFacteurDimension(distance);

		nouvellePosition = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionVirtuelle);
		

		nouvellePosition =  nouvellePosition - referenceDernierNoeud_->obtenirParent()->obtenirPositionRelative();
		referenceDernierNoeud_->assignerPositionRelative(nouvellePosition);
		std::cout << nouvellePosition[0] << " : " << nouvellePosition[1] << " : " << nouvellePosition[2] << " : " << angle << " : " << distance << std::endl;
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