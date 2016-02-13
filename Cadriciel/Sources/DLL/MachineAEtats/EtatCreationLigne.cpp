///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationLigne.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

EtatCreationLigne::EtatCreationLigne()
{
	typeEtat_ = CREATION_LIGNE_NOIRE;
	visiteurCreationLigne_ = std::make_unique<VisiteurCreationLigne>();
}

EtatCreationLigne::~EtatCreationLigne()
{
	// Effacer la ligne si on change d'outil lors d'une cr�ation.
	if (enCreation_ && ligne_ != nullptr && segment_ != nullptr)
	{
		NoeudAbstrait* table = ligne_->obtenirParent();
		table->effacer(ligne_);
	}
	ligne_ = nullptr;
	segment_ = nullptr;
	positionsClic_.clear();
	assignerSymbolePointeur(true);
}

void EtatCreationLigne::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!curseurEstSurTable_) return;
	
	FacadeModele* facade = FacadeModele::obtenirInstance();
	ArbreRenduINF2990* arbre = facade->obtenirArbreRenduINF2990();
	vue::Vue* vue = facade->obtenirVue();

	// Calcul et assignation de la position virtuelle.
	glm::dvec3 positionVirtuelle;
	vue->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	positionsClic_.push_back(positionVirtuelle);

	// Premier clic avec ou sans CTRL enfoncee.
	if (!enCreation_)
	{
		enCreation_ = true;
		//std::cout << "Premier clic position: " << positionVirtuelle[0] << " : " << positionVirtuelle[1] << std::endl;
		arbre->accepterVisiteur(visiteurCreationLigne_.get());
		ligne_ = visiteurCreationLigne_->obtenirReferenceNoeud();

		std::shared_ptr<NoeudAbstrait> nouveauNoeud  = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		segment_ = nouveauNoeud.get();
		ligne_->ajouter(nouveauNoeud);

	}
	// Clic subsequent avec CTRL enfoncee.
	else if (enCreation_ && toucheCtrlEnfonce_)
	{
		std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		std::shared_ptr<NoeudAbstrait> jonction = arbre->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);
		jonction->assignerPositionRelative(positionVirtuelle);
		segment_ = nouveauNoeud.get();
		ligne_->ajouter(jonction);
		ligne_->ajouter(nouveauNoeud);
	}
	// Clic subsequent sans CTRL enfoncee (dernier clic).
	else if (enCreation_ && !toucheCtrlEnfonce_)
	{
		//std::cout << "Deuxieme clic position: " << positionVirtuelle[0] << " : " << positionVirtuelle[1] << std::endl;
		calculerPositionCentreLigne();
		ligne_ = nullptr;
		segment_ = nullptr;
		enCreation_ = false;
		positionsClic_.clear();
	}
}

void EtatCreationLigne::gererToucheEchappe()
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

void EtatCreationLigne::gererMouvementSouris(const int& x, const int& y)
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
		
		// Calculer et assigner le facteur de mise � �chelle.
		double distance = utilitaire::calculerDistanceHypothenuse(positionsClic_.back(), positionVirtuelle);
		segment_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		glm::dvec3 positionRelative = utilitaire::calculerPositionEntreDeuxPoints(positionsClic_.back(), positionVirtuelle);
		segment_->assignerPositionRelative(positionRelative);
	}
}

void EtatCreationLigne::gererToucheControlEnfoncee()
{
	if (!toucheCtrlEnfonce_)
	{
		toucheCtrlEnfonce_ = true;
	}
}

void EtatCreationLigne::gererToucheControlRelachee()
{
	toucheCtrlEnfonce_ = false;
}

void EtatCreationLigne::calculerPositionCentreLigne()
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
	// Calculer et assigner la position relative � la ligne
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
	ligne_->mettreAJourQuadEnglobant();
	//std::cout << "calcul centre: " << centre[0] << " : " << centre[1] << std::endl;
}

void EtatCreationLigne::gererEstSurTableConcret(bool positionEstSurTable)
{
	EtatAbstrait::gererEstSurTableConcret(positionEstSurTable);

	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		if (segment_ != nullptr)
		{
			segment_->assignerAffiche(true);
		}
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (segment_ != nullptr)
		{
			segment_->assignerAffiche(false);
		}
	}
}