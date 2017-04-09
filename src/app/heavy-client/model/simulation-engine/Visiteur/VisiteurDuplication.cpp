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

#include "map-session\MapSession.h"
#include "NoeudTypes.h"
#include "ArbreRenduINF2990.h"

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
VisiteurDuplication::VisiteurDuplication(engine::MapSession* mapSession)
	: mapSession_(mapSession)
{
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
	arbre_ = noeud;
	noeud->chercher(0)->accepterVisiteur(this);
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
	calculerCentreSelection(noeud);

	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre_->creerNoeud(ArbreRenduINF2990::NOM_DUPLICATION);

	PhysicsComponent& physics = nouveauNoeud->getPhysicsComponent();
	physics.absolutePosition = centreSelection_;
	physics.relativePosition = centreSelection_;

	nouveauNoeud->assignerSelection(true);
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
void VisiteurDuplication::visiter(NoeudPoteau* post)
{
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& postPhysics = post->getPhysicsComponent();

	copyPhysics.relativePosition = postPhysics.relativePosition - centreSelection_;
	copyPhysics.absolutePosition = postPhysics.absolutePosition;
	copyPhysics.scale = postPhysics.scale;
	copy->assignerSelection(post->estSelectionne());

	duplication_->ajouter(copy);
	mapSession_->localEntityCreated(copy.get());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudTeleporteur* noeud)
///
/// Fonction qui crée et ajoute un noeud teleporteur au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud teleporteur que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudTeleporteur* noeud)
{
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_TELEPORTEUR);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.scale = physics.scale;
	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = copyPhysics.relativePosition - centreSelection_;

	duplication_->ajouter(copy);

	// TODO server notification here.
	mapSession_->localEntityCreated(copy.get());
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
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_MUR);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.rotation = physics.rotation;
	copyPhysics.scale = physics.scale;
	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = physics.relativePosition - centreSelection_;

	copy->assignerSelection(noeud->estSelectionne());

	duplication_->ajouter(copy);

	mapSession_->localEntityCreated(copy.get());
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
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.scale = physics.scale;
	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = physics.relativePosition - centreSelection_;

	copy->assignerSelection(noeud->estSelectionne());

	nouvelleLigne_ = copy.get();
	duplication_->ajouter(copy);
	mapSession_->localEntityCreated(copy.get());

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) 
	{		
		noeud->chercher(i)->accepterVisiteur(this);
	}
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
	// Creer le nouveau segment et copier les attributs du segment.
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);	

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.rotation = physics.rotation;
	copyPhysics.scale = physics.scale;
	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = physics.relativePosition;

	copy->assignerSelection(noeud->estSelectionne());
	nouvelleLigne_->ajouter(copy);

	mapSession_->localEntityCreated(copy.get());
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
	// Creer la nouvelle jonction et copier la position relative.
	std::shared_ptr<NoeudAbstrait> copy = arbre_->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = physics.relativePosition;
	copy->assignerSelection(noeud->estSelectionne());

	nouvelleLigne_->ajouter(copy);
	mapSession_->localEntityCreated(copy.get());
}

void VisiteurDuplication::copyChildren(NoeudAbstrait* entity, NoeudAbstrait* copy)
{
	// We need to copy all the children (probably only if this is a line).
	uint32_t nChildren = entity->obtenirNombreEnfants();
	for (uint32_t j = 0; j < nChildren; ++j)
	{
		NoeudAbstrait* child = entity->chercher(j);
		std::shared_ptr<NoeudAbstrait> childCopy = arbre_->creerNoeud(child->getType());

		PhysicsComponent& childPhysics = child->getPhysicsComponent();
		PhysicsComponent& copyPhysics = childCopy->getPhysicsComponent();

		copyPhysics.relativePosition = childPhysics.relativePosition;
		copyPhysics.absolutePosition = childPhysics.absolutePosition;
		copyPhysics.scale = childPhysics.scale;
		copyPhysics.rotation = childPhysics.rotation;

		copy->ajouter(childCopy);
		mapSession_->localEntityCreated(childCopy.get());
	}
}

void VisiteurDuplication::copyDuplicatedObjects(NoeudAbstrait* duplication)
{
	NoeudAbstrait* table = arbre_->chercher(0);
	glm::dvec3 duplicationRelativePosition = duplication->getPhysicsComponent().relativePosition;

	// Iterate over the duplication children
	uint32_t nDuplicationChildren = duplication->obtenirNombreEnfants();
	for (uint32_t i = 0; i < nDuplicationChildren; i++) 
	{
		NoeudAbstrait* child = duplication->chercher(i);

		// Copy the properties.
		std::shared_ptr<NoeudAbstrait> childCopy = arbre_->creerNoeud(child->getType());

		PhysicsComponent& childPhysics = child->getPhysicsComponent();
		PhysicsComponent& copyPhysics = childCopy->getPhysicsComponent();

		copyPhysics.rotation = childPhysics.rotation;
		copyPhysics.scale = childPhysics.scale;
		copyPhysics.absolutePosition = childPhysics.absolutePosition;
		copyPhysics.relativePosition = childPhysics.relativePosition + duplicationRelativePosition;

		copyChildren(child, childCopy.get());

		// Add to table and notify the server.
		table->ajouter(childCopy);
		mapSession_->localEntityCreated(childCopy.get());

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
			glm::dvec3 relativePosition = enfant->getPhysicsComponent().relativePosition;
			x = relativePosition.x;
			y = relativePosition.y;

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

void VisiteurDuplication::visiter(NoeudPaireTeleporteurs* noeud)
{
	/*ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> copy = arbre->creerNoeud(ArbreRenduINF2990::NOM_PAIRTELEPORT);

	PhysicsComponent& copyPhysics = copy->getPhysicsComponent();
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	copyPhysics.scale = physics.scale;
	copyPhysics.absolutePosition = physics.absolutePosition;
	copyPhysics.relativePosition = physics.relativePosition - centreSelection_;

	copy->assignerSelection(noeud->estSelectionne());

	nouvelleLigne_ = copy.get();
	duplication_->ajouter(copy);
	mapSession_->localEntityCreated(copy.get());

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}*/
	//voir si on veut faire duplication ou non, ceci ne marche pas pour l'instant
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////