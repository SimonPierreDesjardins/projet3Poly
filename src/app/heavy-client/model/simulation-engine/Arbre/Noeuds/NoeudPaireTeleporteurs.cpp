////////////////////////////////////////////////
/// @file   NoeudPaireTeleporteurs.cpp
/// @author DGI-2990
/// @date   2007-01-25
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudPaireTeleporteurs.h"
#include <cassert>
#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudPaireTeleporteurs::NoeudPaireTeleporteurs(const std::string& type)
//
// Ne fait qu'appeler la version de la classe de base.
//
// @param[in] id				 : L'identifiant du noeud.
// @param[in] type               : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudPaireTeleporteurs::NoeudPaireTeleporteurs(uint32_t id, const std::string& type)
	: NoeudComposite{ id, type }
{
	type_ = PAIRTELEPORT_ENTITY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::~NoeudComposite()
///
/// Destructeur qui détruit tous les enfants du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaireTeleporteurs::~NoeudPaireTeleporteurs()
{
	//detruire ses enfants;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaireTeleporteurs::afficherConcret() const
{
	glPushMatrix();

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();


	glPopMatrix();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaireTeleporteurs::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::ajouter( shared_ptr<NoeudAbstrait> enfant )
///
/// Ajoute un noeud enfant au noeud courant.
///
/// @param[in] enfant: Noeud à ajouter.
///
/// @return Vrai si l'ajout a réussi, donc en tout temps pour cette classe.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaireTeleporteurs::ajouter(std::shared_ptr<NoeudAbstrait> enfant)
{
	enfant->assignerParent(this);
	enfants_.push_back(enfant);
	if (enfants_.size() == 2)
	{
		enfants_.at(0)->assignerTeleporteur(enfants_.at(1).get());
		enfants_.at(1)->assignerTeleporteur(enfants_.at(0).get());
	}
	else
	{
		enfants_.at(0)->assignerTeleporteur(nullptr);
	}



	return true;

}




////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
