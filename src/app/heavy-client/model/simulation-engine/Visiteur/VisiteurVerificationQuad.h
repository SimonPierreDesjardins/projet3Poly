///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationQuad.h
/// @author Olivier St-Amour
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_VERIFICATION_QUAD_H
#define VISITEUR_VERIFICATION_QUAD_H

#include "VisiteurAbstrait.h"
#include <memory>
#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Visiteur permettant d'effectuer la vérification de la boite englobante
/// d'un objet pour qu'il soit sur la table.
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurVerificationQuad : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurVerificationQuad();

	/// Destructeur.
	virtual ~VisiteurVerificationQuad();

	/// Obtenir si tous les objets sont dans la zone de simulation.
	inline bool objetsDansZoneSimulation();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDuplication* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudDepart* noeud);
	virtual void visiter(NoeudTeleporteur* noeud);
	virtual void visiter(NoeudPaireTeleporteurs* noeud);

private:
	bool verifierPointEstSurTable(glm::dvec3 point);
	bool objetsDansZoneSimulation_;
    utilitaire::BoiteEnglobante boiteTable_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::objetsDansZoneSimulation()
///
/// Retourne l'attribut objetsDansZoneSimulation_ indiquant si les objets sont dans les limites de la table.
///
/// @param[in] Aucun
///
/// @return bool : Booléen qui indique si les objets sont dans les limites de la table.
///
////////////////////////////////////////////////////////////////////////
inline bool VisiteurVerificationQuad::objetsDansZoneSimulation()
{
	return objetsDansZoneSimulation_;
}

#endif // VISITEUR_VERIFICATION_QUAD

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////