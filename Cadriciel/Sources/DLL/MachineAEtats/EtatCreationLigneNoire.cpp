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
	// Effacer la ligne si on change d'outil lors d'une création.
	if (enCreation_ && ligne_ != nullptr && segment_ != nullptr)
	{
		NoeudAbstrait* table = ligne_->obtenirParent().get();
		table->effacer(ligne_);
	}
	ligne_ = nullptr;
	segment_ = nullptr;
	positionsClic_.clear();
	assignerSymbolePointeur(true);
}

void EtatCreationLigneNoire::gererClicGaucheEnfonce(const int& x, const int& y)
{
}

void EtatCreationLigneNoire::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!curseurEstSurTable_) return;
	
	FacadeModele* facade = FacadeModele::obtenirInstance().get();
	ArbreRenduINF2990* arbre = facade->obtenirArbreRenduINF2990().get();
	vue::Vue* vue = facade->obtenirVue().get();

	// Calcul et assignation de la position virtuelle.
	glm::dvec3 positionVirtuelle;
	vue->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	positionsClic_.push_back(positionVirtuelle);

	// Premier clic avec ou sans CTRL enfoncee.
	if (!enCreation_)
	{
		enCreation_ = true;

		arbre->accepterVisiteur(visiteur_.get());
		ligne_ = visiteur_->obtenirReferenceNoeud();

		segment_ = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		ligne_->ajouter(segment_);

	}
	// Clic subsequent avec CTRL enfoncee.
	else if (enCreation_ && toucheCtrlEnfonce_)
	{
		segment_ = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		ligne_->ajouter(segment_);
	}
	// Clic subsequent sans CTRL enfoncee (dernier clic).
	else if (enCreation_ && !toucheCtrlEnfonce_)
	{
		calculerPositionCentreLigne();
		ligne_ = nullptr;
		segment_ = nullptr;
		enCreation_ = false;
		positionsClic_.clear();
	}
}

void EtatCreationLigneNoire::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(ligne_);
		ligne_ = nullptr;
		segment_ = nullptr;
		enCreation_ = false;
		positionsClic_.clear();
	}
}

void EtatCreationLigneNoire::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererEstSurTable(positionVirtuelle);

	if (enCreation_)
	{
		assert(segment_ != nullptr);

		// Calculer et assigner l'angle de rotation.
		double angle = utilitaire::calculerAngleRotation(positionsClic_.back(), positionVirtuelle);
		segment_->assignerAngleRotation(angle);
		
		// Calculer et assigner le facteur de mise à échelle.
		double distance = utilitaire::calculerDistanceHypothenuse(positionsClic_.back(), positionVirtuelle);
		segment_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		glm::dvec3 positionRelative = utilitaire::calculerPositionEntreDeuxPoints(positionsClic_.back(), positionVirtuelle);
		segment_->assignerPositionRelative(positionRelative);
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


void EtatCreationLigneNoire::calculerPositionCentreLigne()
{
	// Si le vecteur de positions est vide, on sort.
	if (positionsClic_.empty()) return;

	// Initialiser les minimums et les maximums 
	double minX = positionsClic_[0][0];
	double maxX = positionsClic_[0][0];
	double minY = positionsClic_[0][1];
	double maxY = positionsClic_[0][1];

	// Trouver les min / max dans les positions des clics.
	for (int i = 0; i < positionsClic_.size(); i++)
	{
		if (positionsClic_[i][0] > maxX)
		{
			maxX = positionsClic_[i][0];
		}
		if (positionsClic_[i][0] < minX)
		{
			minX = positionsClic_[i][0];
		}
		if (positionsClic_[i][1] > maxY)
		{
			maxY = positionsClic_[i][1];
		}
		if (positionsClic_[i][1] < minY)
		{
			minY = positionsClic_[i][1];
		}
	}
	// Calculer et assigner la position relative à la ligne
	glm::dvec3 centre = { (minX + maxX) / 2, (minY + maxY) / 2, 0 };
	ligne_->assignerPositionRelative(centre);

	// Ajuster la position relative des segments.
	glm::dvec3 positionEnfant;
	for (unsigned int i = 0; i < ligne_->obtenirNombreEnfants(); i++)
	{
		positionEnfant = ligne_->chercher(i)->obtenirPositionRelative();
		positionEnfant -= centre;
		ligne_->chercher(i)->assignerPositionRelative(positionEnfant);
	}
	std::cout << "calcul centre: " << centre[0] << " : " << centre[1] << std::endl;
}

void EtatCreationLigneNoire::gererEstSurTableConcret(bool positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		if (segment_ != nullptr)
		{
			segment_->assignerAffiche(true);
		}
		assignerSymbolePointeur(curseurEstSurTable_);
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (segment_ != nullptr)
		{
			segment_->assignerAffiche(false);
		}
		assignerSymbolePointeur(curseurEstSurTable_);
	}
}

