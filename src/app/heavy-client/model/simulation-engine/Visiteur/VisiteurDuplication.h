///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DUPLICATION_H
#define VISITEUR_DUPLICATION_H

#include "VisiteurAbstrait.h"

namespace engine
{
	class MapSession;
}


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Visiteur permettant d'effectuer une duplication d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDuplication(engine::MapSession* mapSession);

	/// Destructeur.
	virtual ~VisiteurDuplication();

	inline void assignerEnDuplication(bool enDuplication);

	inline NoeudAbstrait* obtenirDuplication();
	void copyDuplicatedObjects(NoeudAbstrait* noeud);

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);	
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudJonction* noeud);
	virtual void visiter(NoeudTeleporteur* noeud);


private:

	VisiteurDuplication() = delete;

	engine::MapSession* mapSession_;

	void calculerCentreSelection(NoeudAbstrait* noeud);
	glm::dvec3 centreSelection_{ 0.0, 0.0, 0.0 };
	bool enDuplication_{ false };
	NoeudAbstrait* nouvelleLigne_{ nullptr };
	NoeudAbstrait* duplication_{ nullptr };

	void copyChildren(NoeudAbstrait* entity, NoeudAbstrait* copy);
};

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::assignerEnDuplication(bool enDuplication)
///
/// Assigne l'attribut enDuplication qui indique si une duplication est en cours
///
/// @param[in] enDuplication : valeur que l'on veut affigner à l'attribut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurDuplication::assignerEnDuplication(bool enDuplication)
{
	enDuplication_ = enDuplication;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::obtenirDuplication()
///
/// Retourne l'attribut duplication_ qui représente le noeud dupliqué.
///
/// @param[in] Aucun.
///
/// @return NoeudAbstrait* : noeud dupliqué.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* VisiteurDuplication::obtenirDuplication()
{
	return duplication_;
}

#endif // VISITEUR_DUPLICATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////