///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <queue>
#include <memory>

#include "MapSession.h"
#include "FacadeModele.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"

#include "VisiteurDuplication.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication()
///
/// Constructeur. Il initialise l'attribut centreSelection_ selon la sélection.
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication(client_network::MapSession* mapSession)
	: mapSession_(mapSession)
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	calculerCentreSelection(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::~VisiteurDuplication()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud Duplication au noeud Table passé en paramètre selon la sélection actuelle.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter la duplication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudTable* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_DUPLICATION);
	noeud->ajouter(nouveauNoeud);
	mapSession_->localEntityCreated(nouveauNoeud.get());
	duplication_ = nouveauNoeud.get();

	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		// The child has to be selected and owned by this user.
		if (enfant->estSelectionne() && enfant->getOwnerId() == mapSession_->getThisUserId()) 
		{
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudPoteau* noeud)
///
/// Fonction qui crée et ajoute un noeud Poteau au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Poteau que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudPoteau* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	nouveauNoeud->assignerPositionCourante(noeud->obtenirPositionCourante());
	nouveauNoeud->assignerSelection(noeud->estSelectionne());
	duplication_->ajouter(nouveauNoeud);

	mapSession_->localEntityCreated(nouveauNoeud.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudMur* noeud)
///
/// Fonction qui crée et ajoute un noeud Mur au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Mur que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudMur* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_MUR);

	nouveauNoeud->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	nouveauNoeud->assignerPositionCourante(noeud->obtenirPositionCourante());
	nouveauNoeud->assignerSelection(noeud->estSelectionne());
	duplication_->ajouter(nouveauNoeud);

	mapSession_->localEntityCreated(nouveauNoeud.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudLigne* noeud)
///
/// Fonction qui crée et ajoute un noeud Ligne au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Ligne que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudLigne* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouvelleLigne = arbre->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);

	nouvelleLigne->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouvelleLigne->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	nouvelleLigne->assignerPositionCourante(noeud->obtenirPositionCourante());
	nouvelleLigne->assignerSelection(noeud->estSelectionne());

	nouvelleLigne_ = nouvelleLigne.get();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) 
	{		
		noeud->chercher(i)->accepterVisiteur(this);
	}
	duplication_->ajouter(nouvelleLigne);
	mapSession_->localEntityCreated(nouvelleLigne.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudSegment* noeud)
///
/// Fonction qui crée et ajoute un noeud Segment au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Segment que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudSegment* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Creer le nouveau segment et copier les attributs du segment.
	std::shared_ptr<NoeudAbstrait> nouveauSegment = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);	
	nouveauSegment->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauSegment->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauSegment->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouveauSegment->assignerPositionCourante(noeud->obtenirPositionCourante());
	nouveauSegment->assignerSelection(noeud->estSelectionne());
	nouvelleLigne_->ajouter(nouveauSegment);

	mapSession_->localEntityCreated(nouveauSegment.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudJonction* noeud)
///
/// Fonction qui crée et ajoute un noeud Jonction au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Jonction que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudJonction* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	
	// Creer la nouvelle jonction et copier la position relative.
	std::shared_ptr<NoeudAbstrait> nouvelleJonction = arbre->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);
	nouvelleJonction->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouvelleJonction->assignerPositionCourante(noeud->obtenirPositionCourante());
	nouvelleJonction->assignerSelection(noeud->estSelectionne());
	nouvelleLigne_->ajouter(nouvelleJonction);

	mapSession_->localEntityCreated(nouvelleJonction.get());
}

void VisiteurDuplication::copyDuplicatedObjects(NoeudAbstrait* duplication)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	NoeudAbstrait* table = arbre->chercher("table");

	std::queue<NoeudAbstrait*> entitiesToCopy;

	// Ajouter les enfants de la duplication dans la queue de copies.
	for (unsigned int i = 0; i < duplication->obtenirNombreEnfants(); i++) 
	{
		entitiesToCopy.push(duplication->chercher(i));
	}

	// Non-recurisve top-down copy of all the children and sub-children of the
	// duplication onto the table.
	while (!entitiesToCopy.empty())
	{
		NoeudAbstrait* toCopy = entitiesToCopy.front();
		entitiesToCopy.pop();

		std::shared_ptr<NoeudAbstrait> copy = arbre->creerNoeud(toCopy->getType());

		// Copy the properties.
		NoeudAbstrait* toCopyParent = toCopy->obtenirParent();
		copy->assignerPositionRelative(toCopyParent->obtenirPositionCourante() - toCopy->obtenirPositionCourante());
		copy->assignerPositionCourante(toCopy->obtenirPositionCourante());
		copy->assignerFacteurMiseAEchelle(toCopy->obtenirFacteurMiseAEchelle());
		copy->assignerAngleRotation(toCopy->obtenirAngleRotation());

		table->ajouter(copy);
		mapSession_->localEntityCreated(copy.get());

		// Push the children into the queue.
		for (unsigned int i = 0; i < toCopy->obtenirNombreEnfants(); i++) 
		{
			entitiesToCopy.push(toCopy->chercher(i));
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::calculerCentreSelection(NoeudAbstrait* noeud)
///
/// Fonction qui calcule le centre de la sélection actuelle en faisant la moyenne des points extrêmes de la sélection.
///
/// @param[in] noeud : Le noeud Abstrait que l'on veut dupliquer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::calculerCentreSelection(NoeudAbstrait* noeud)
{
	if (noeud->obtenirNombreEnfants() < 1) return;
	// Initialiser les minimums et les maximums 
	double minX = 0.0;
	double maxX = 0.0;
	double minY = 0.0;
	double maxY = 0.0;
	double x = 0.0;
	double y = 0.0;
	bool estPremierSelectionne = true;
	NoeudAbstrait* enfant = nullptr;
	// Trouver les min / max dans les positions des noeuds sur la table.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne() && enfant->estDuplicable()) {
			x = enfant->obtenirPositionRelative().x;
			y = enfant->obtenirPositionRelative().y;

			if (x > maxX || estPremierSelectionne) {
				maxX = x;
			}
			if (x < minX || estPremierSelectionne) {
				minX = x;
			}
			if (y > maxY || estPremierSelectionne) {
				maxY = y; 
			}
			if (y < minY || estPremierSelectionne) {
				minY = y;
			}
			if (estPremierSelectionne) {
				estPremierSelectionne = false;
			}
		}
	}
	// Calculer et assigner la position relative à la ligne
	centreSelection_= { (minX + maxX) / 2.0, (minY + maxY) / 2.0, 0.0 };
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////