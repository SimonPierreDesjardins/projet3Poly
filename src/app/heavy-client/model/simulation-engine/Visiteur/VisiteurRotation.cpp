///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "map-session\MapSession.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation()
///
/// Constructeur. Il calcul le centre de la sélection du noeud Table.
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::~VisiteurRotation()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::~VisiteurRotation()
{
}

void VisiteurRotation::rotateSelectedObjects(ArbreRendu* tree, engine::MapSession* mapSession)
{
	mapSession_ = mapSession;
	tree->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudTable* noeud)
///
/// Fonction servant à donner l'accès aux noeuds enfants sélectionnés de la table passée en paramètre.
///
/// @param[in] noeud : Les enfants de la table auxquels ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudTable* noeud)
{
	calculerCentreSelection(noeud);
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		// Child has to be selected by me.
		if (enfant != nullptr && enfant->estSelectionne() &&
			enfant->getOwnerId() == mapSession_->getThisUserId()) {
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudPoteau* noeud)
///
/// Fonction qui modifie la position du noeud Poteau passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Poteau auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudPoteau* noeud)
{
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudMur* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud Mur passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Mur auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMur* noeud)
{
	// Assigner le nouvel angle de rotation.
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	physics.rotation.z += angleRotation_;
	mapSession_->localEntityPropertyUpdated(noeud, Networking::ROTATION, glm::vec3(physics.rotation));
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudTeleporteur* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud teleporteur passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud teleporteur auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudTeleporteur* noeud)
{
	// Assigner le nouvel angle de rotation.
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	physics.rotation.z += angleRotation_;
	mapSession_->localEntityPropertyUpdated(noeud, Networking::ROTATION, glm::vec3(physics.rotation));
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudLigneCourseAbstrait* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud ligne de course passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud ligne de course auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudLigneCourseAbstrait* noeud)
{
	// Assigner le nouvel angle de rotation.
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	physics.rotation.z += angleRotation_;
	assignerNouvellePositionRelative(noeud);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudDepart* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud Depart passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Depart auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudDepart* noeud)
{
	// Assigner le nouvel angle de rotation.
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	physics.rotation.z += angleRotation_;
	mapSession_->localEntityPropertyUpdated(noeud, Networking::ROTATION, glm::vec3(physics.rotation));
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudLigne* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation des enfants (segments) du noeud Ligne passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Ligne auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudLigne* ligne)
{
	assignerNouvellePositionRelative(ligne);
	PhysicsComponent& linePhysics = ligne->getPhysicsComponent();
	for (unsigned int i = 0; i < ligne->obtenirNombreEnfants(); i++) 
    {
		NoeudAbstrait* enfant = ligne->chercher(i);
		PhysicsComponent& childPhysics = enfant->getPhysicsComponent();

		glm::dvec3 updatedChildRelativePosition{ 0.0, 0.0, 0.0 };
		utilitaire::calculerPositionApresRotation(childPhysics.relativePosition, updatedChildRelativePosition, angleRotation_);

		childPhysics.relativePosition = updatedChildRelativePosition;
		mapSession_->localEntityPropertyUpdated(enfant, Networking::RELATIVE_POSITION, glm::vec3(childPhysics.relativePosition));

		childPhysics.absolutePosition = updatedChildRelativePosition + linePhysics.absolutePosition;
		mapSession_->localEntityPropertyUpdated(enfant, Networking::ABSOLUTE_POSITION, glm::vec3(childPhysics.absolutePosition));
		
		childPhysics.rotation.z += angleRotation_;
		mapSession_->localEntityPropertyUpdated(enfant, Networking::ROTATION, glm::vec3(childPhysics.rotation));
	}

	linePhysics.rotation.z += angleRotation_;
	mapSession_->localEntityPropertyUpdated(ligne, Networking::ROTATION, glm::vec3(linePhysics.rotation));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
///
/// Fonction qui calcule le centre de la sélection en faisant la moyenne des points extrêmes de tous les objets sélectionnés.
///
/// @param[in] noeud : Le noeud auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
{
    if (!noeud) return;
    unsigned int nEnfants = noeud->obtenirNombreEnfants();
	if (!nEnfants) return;

	// Initialiser les minimums et les maximums 
    NoeudAbstrait* enfant = noeud->chercher(0);

    double minX = 0;
    double maxX = 0;
	double minY = 0;
    double maxY = 0;
    
    bool premierEnSelection = true;
	
	// Trouver les min / max dans les positions des noeuds sur la table.
	for (unsigned int i = 0; i < nEnfants; i++)
	{
		enfant = noeud->chercher(i);
		// If the object is selected by me.
		if (enfant != nullptr && enfant->estSelectionne() &&
			enfant->getOwnerId() == mapSession_->getThisUserId())
		{
			PhysicsComponent& childPhysics = enfant->getPhysicsComponent();

            // Trier en x.
			if (childPhysics.absolutePosition.x > maxX || premierEnSelection) 
            {
				maxX = childPhysics.absolutePosition.x;
			}
			if (childPhysics.absolutePosition.x < minX || premierEnSelection) 
            {
				minX = childPhysics.absolutePosition.x;
			}
            // Trier en y.
			if (childPhysics.absolutePosition.y > maxY || premierEnSelection)
            {
				maxY = childPhysics.absolutePosition.y; 
			}
			if (childPhysics.absolutePosition.y < minY || premierEnSelection)
            {
				minY = childPhysics.absolutePosition.y;
			}
            
            // Toggle l'initialisation du min / max.
            if (premierEnSelection)
            {
                premierEnSelection = false;
            }
		}
	}
	// Calculer et assigner le centre de selection.
	centreSelection_= { (minX + maxX) / 2.0, (minY + maxY) / 2.0, 0.0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
///
/// Fonction qui calcule la nouvelle position du noeud passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
{
	PhysicsComponent& physics = noeud->getPhysicsComponent();

	glm::dvec3 distanceCentreSelection = physics.relativePosition - centreSelection_;
	glm::dvec3 updatedPosition = { 0.0, 0.0, 0.0 };

	utilitaire::calculerPositionApresRotation(distanceCentreSelection, updatedPosition, angleRotation_);
	updatedPosition += centreSelection_;

	physics.relativePosition = updatedPosition;
	physics.absolutePosition = updatedPosition;

	mapSession_->localEntityPropertyUpdated(noeud, Networking::ABSOLUTE_POSITION, glm::vec3(updatedPosition));
	mapSession_->localEntityPropertyUpdated(noeud, Networking::RELATIVE_POSITION, glm::vec3(updatedPosition));
}

void VisiteurRotation::visiter(NoeudPaireTeleporteurs* noeud)
{
	calculerCentreSelection(noeud);
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		// Child has to be selected by me.
		if (enfant != nullptr && enfant->estSelectionne() &&
			enfant->getOwnerId() == mapSession_->getThisUserId()) {
			enfant->accepterVisiteur(this);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////