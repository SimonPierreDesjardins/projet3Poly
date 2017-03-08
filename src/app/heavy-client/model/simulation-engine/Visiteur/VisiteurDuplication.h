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
 
///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Visiteur permettant d'effectuer une duplication d'un objet
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurDuplication();

	/// Destructeur.
	virtual ~VisiteurDuplication();

	inline void assignerEnDuplication(bool enDuplication);
	inline NoeudAbstrait* obtenirDuplication();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);	
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudJonction* noeud);
	virtual void visiter(NoeudDuplication* noeud);

private:

	void calculerCentreSelection(NoeudAbstrait* noeud);
	glm::dvec3 centreSelection_{ 0.0, 0.0, 0.0 };
	bool enDuplication_{ false };
	NoeudAbstrait* nouvelleLigne_{ nullptr };
	NoeudAbstrait* duplication_{ nullptr };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::assignerEnDuplication(bool enDuplication)
///
/// Assigne l'attribut enDuplication qui indique si une duplication est en cours
///
/// @param[in] enDuplication : valeur que l'on veut affigner � l'attribut.
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
/// Retourne l'attribut duplication_ qui repr�sente le noeud dupliqu�.
///
/// @param[in] Aucun.
///
/// @return NoeudAbstrait* : noeud dupliqu�.
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