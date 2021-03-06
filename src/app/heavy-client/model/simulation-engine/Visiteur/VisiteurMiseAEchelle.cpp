///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelle.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAEchelle.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"
#include "map-session\MapSession.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::VisiteurMiseAEchelle()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::VisiteurMiseAEchelle()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
{
}

void VisiteurMiseAEchelle::resizeSelectedEntities(ArbreRendu* tree, engine::MapSession* mapSession)
{
	mapSession_ = mapSession;
	tree->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::initialiser(ArbreRendu* noeud)
///
/// Fonction qui initialise les valeurs du vecteur facteursDimensionsInitiaux_
/// selon les facteurs de dimensions des enfants de la table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::initialiser(ArbreRendu* noeud)
{
	// Vider le vecteur de facteurs de dimensions intiaux.
	facteursDimensionsInitiaux_.clear();
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		facteursDimensionsInitiaux_.push_back(table->chercher(i)->getPhysicsComponent().scale.x);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::reinitialiser(ArbreRendu* noeud)
///
/// Fonction qui reinitialise les facteurs de dimensions des enfants de la 
/// table selon le vecteur facteursDimensionsInitiaux_.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::reinitialiser(ArbreRendu* noeud, engine::MapSession* mapSession)
{
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		NoeudAbstrait* child = table->chercher(i);
		child->getPhysicsComponent().scale.x = (facteursDimensionsInitiaux_[i]);
		mapSession->localEntityPropertyUpdated(child, Networking::SCALE, glm::vec3(facteursDimensionsInitiaux_[i], 0.0, 0.0));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(ArbreRendu* noeud)
///
/// Fonction servant � donner l'acc�s au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudTable* noeud)
///
/// Fonction servant � donner l'acc�s aux enfants de la table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants desquels on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudTable* noeud)
{
	NoeudAbstrait* enfant = nullptr;
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne() && 
			enfant->getOwnerId() == mapSession_->getThisUserId())
		{
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudPoteau* noeud)
///
/// Fonction modifiant le facteur de dimension du poteau pass� en param�tre.
///
/// @param[in] noeud : Le noeud Poteau duquel on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudPoteau* noeud)
{
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	double facteurMiseAEchelle = physics.scale.x + facteurMiseAEchelle_;
	if (facteurMiseAEchelle >= 0) {
		physics.scale.x = facteurMiseAEchelle;
		mapSession_->localEntityPropertyUpdated(noeud, Networking::SCALE, glm::vec3(facteurMiseAEchelle, facteurMiseAEchelle, 0.0));
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
///
/// Fonction modifiant le facteur de dimension du mur pass� en param�tre.
///
/// @param[in] noeud : Le noeud Mur duquel on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
{
	PhysicsComponent& physics = noeud->getPhysicsComponent();
	double facteurMiseAEchelle = physics.scale.x + facteurMiseAEchelle_ * 2;
	if (facteurMiseAEchelle >= 0) 
	{
		physics.scale.x = facteurMiseAEchelle;
		mapSession_->localEntityPropertyUpdated(noeud, Networking::SCALE, glm::vec3(facteurMiseAEchelle, 0.0, 0.0));
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////