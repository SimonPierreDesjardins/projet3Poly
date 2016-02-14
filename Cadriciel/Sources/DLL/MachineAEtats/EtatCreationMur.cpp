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

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationMur::EtatCreationMur()
///
/// Constructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationMur::EtatCreationMur()
{
	typeEtat_ = CREATION_MUR;
	visiteurCreationMur_ = std::make_unique<VisiteurCreationMur>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationMur::~EtatCreationMur()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationMur::~EtatCreationMur()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton gauche de la souris est
/// appuyé et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheEnfonce(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction crée un mur au premier clique puis assigne son facteur de mise à échelle
/// et angle de rotation en fonction du deuxième clique.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);	
	if (!estClickDrag() && curseurEstSurTable_)
	{
		//Premier clic
		if (!enCreation_)
		{
			enCreation_ = true;
			vue_->convertirClotureAVirtuelle(x, y, positionPremierClic_);
			visiteurCreationMur_->assignerPositionRelative(positionPremierClic_);
			arbre_->accepterVisiteur(visiteurCreationMur_.get());
			mur_ = visiteurCreationMur_->obtenirReferenceNoeud();
		}
		//Deuxieme clic
		else
		{
			enCreation_ = false;
			mur_ = nullptr;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererToucheEchappe()
///
/// Cette fonction supprime le mur s'il est en création
///
////////////////////////////////////////////////////////////////////////
void EtatCreationMur::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(mur_);
		enCreation_ = false;
		mur_ = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererMouvementSouris(const int& x, const int&y)
///
/// Cette fonction assigne un facteur de mise à échelle
/// et un angle de rotation à un mur s'il est en création.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererEstSurTableConcret(bool positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arrête
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
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
