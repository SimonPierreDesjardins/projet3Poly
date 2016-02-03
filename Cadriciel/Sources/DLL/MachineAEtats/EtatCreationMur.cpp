///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationMur.h"
#include "FacadeModele.h"

#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

EtatCreationMur::EtatCreationMur()
{
	std::cout << "Creation de mur" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationMur>();
}

EtatCreationMur::~EtatCreationMur()
{

}

void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
{
}

void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
{
	if (!curseurEstSurTable_) return;
	
	//Premier clic
	if (!enCreation_)
	{
		enCreation_ = true;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		visiteur_->assignerPositionRelative(positionPremierClic_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		mur_ = visiteur_.get()->obtenirReferenceNoeud();
	}
	//Deuxieme clic
	else
	{
		enCreation_ = false;
		mur_ = nullptr;
	}
}

void EtatCreationMur::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(mur_);
		enCreation_ = false;
		mur_ = nullptr;
	}
}

void EtatCreationMur::gererMouvementSouris(const int& x, const int&y)
{
	EtatAbstrait::gererMouvementSouris(x, y);

	// Calculer la position virtuelle.
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererEstSurTable(positionVirtuelle);

	if (enCreation_)
	{		
		// Calculer et assigner de l'angle de rotation.
		double angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionVirtuelle);
		mur_->assignerAngleRotation(angle);
		
		// Calculer et assigner le facteur de mise à échelle.
		double distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionVirtuelle);
		mur_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		glm::dvec3 nouvellePosition = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionVirtuelle);
		mur_->assignerPositionRelative(nouvellePosition);
	}
}

void EtatCreationMur::gererEstSurTableConcret(bool positionEstSurTable)
{
	EtatAbstrait::gererEstSurTableConcret(positionEstSurTable);

	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		if (mur_ != nullptr)
		{
			mur_->assignerAffiche(true);
		}
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (mur_ != nullptr)
		{
			mur_->assignerAffiche(false);
		}
	}
}