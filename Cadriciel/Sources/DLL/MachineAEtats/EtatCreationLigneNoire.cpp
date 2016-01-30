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
	//HCURSOR handle = GetCursor();
	//SetSystemCursor(handle, 32650);

	// Effacer la ligne si on change d'outil lors d'une création.
	if (enCreation_ && ligne_ != nullptr && segment_ != nullptr)
	{
		NoeudAbstrait* table = ligne_->obtenirParent().get();
		table->effacer(ligne_);
	}
	ligne_ = nullptr;
	segment_ = nullptr;
	positionsClic_.clear();
}

void EtatCreationLigneNoire::gererClicGaucheEnfonce(const int& x, const int& y)
{
	//std::cout << x << " " << y << std::endl;
}

void EtatCreationLigneNoire::gererClicGaucheRelache(const int& x, const int& y)
{
	FacadeModele* facade = FacadeModele::obtenirInstance().get();
	ArbreRenduINF2990* arbre = facade->obtenirArbreRenduINF2990().get();
	// Premier clic avec ou sans CTRL enfoncee.
	if (!enCreation_ && curseurEstSurTable_)
	{
		enCreation_ = true;
		facade->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_); 
		arbre->accepterVisiteur(visiteur_.get());
		ligne_ = visiteur_->obtenirReferenceNoeud();
		segment_ = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		ligne_->ajouter(segment_);
		positionsClic_.push_back(positionPremierClic_);
	}
	// Clic subsequent avec CTRL enfoncee.
	else if (enCreation_ && toucheCtrlEnfonce_ && curseurEstSurTable_)
	{
		// Création du nouveau noeud et assignation au parent.
		segment_ = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
		ligne_->ajouter(segment_);

		// Assigner la position
		facade->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		positionsClic_.push_back(positionPremierClic_);
	}
	// Clic subsequent sans CTRL enfoncee (dernier clic).
	else if (enCreation_ && !toucheCtrlEnfonce_ && curseurEstSurTable_)
	{
		facade->obtenirVue()->convertirClotureAVirtuelle(x, y, positionDeuxiemeClic_);
		positionsClic_.push_back(positionDeuxiemeClic_);
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
	glm::dvec3 positionCurseur;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionCurseur);
	
	if (estSurTable(positionCurseur))
	{
		if (!curseurEstSurTable_)
		{
			curseurEstSurTable_ = true;
			if (segment_ != nullptr)
			{
				segment_->assignerAffiche(true);
			}
			// TODO: Ajouter changement de curseur ici.
			//HCURSOR handle = GetCursor();
			//SetSystemCursor(handle, 32650);
			std::cout << "in" << std::endl;
		}
	}
	else if (curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (segment_ != nullptr)
		{
			segment_->assignerAffiche(false);
		}
		std::cout << "out" << std::endl;
		//TODO: Ajouter changement de curseur ici.
		//HCURSOR handle = GetCursor();
		//SetSystemCursor(handle, 32648);
	}

	glm::dvec3 nouvellePosition;
	double angle = 0;
	double distance = 0;

	if (enCreation_)
	{
		assert(segment_ != nullptr);
		// Calculer et assigner l'angle relatif.
		angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionCurseur);
		segment_->assignerAngleRotation(angle);
		
		// Calculer et assigner le facteur de dimension.
		distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionCurseur);
		segment_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		nouvellePosition = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionCurseur);
		segment_->assignerPositionRelative(nouvellePosition);
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
	// Si le vecteur de clic est vide on sort.
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
	for (int i = 0; i < ligne_->obtenirNombreEnfants(); i++)
	{
		positionEnfant = ligne_->chercher(i)->obtenirPositionRelative();
		positionEnfant -= centre;
		ligne_->chercher(i)->assignerPositionRelative(positionEnfant);
	}
	std::cout << "calcul centre: " << centre[0] << " : " << centre[1] << std::endl;
}

