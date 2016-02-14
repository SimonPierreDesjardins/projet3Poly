///////////////////////////////////////////////////////////////////////////
/// @file NoeudDuplication.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDDUPLICATION_H__
#define __ARBRE_NOEUDS_NOEUDDUPLICATION_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudDuplication
/// @brief Classe qui représente temporairement un groupe d'objets à dupliquer
///
/// @author Olivier St-Amour
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudDuplication : public NoeudComposite
{
public:

	/// Constructeur
	NoeudDuplication(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudDuplication();
	/// Affiche la table.
	virtual void afficherConcret() const;
	inline std::shared_ptr<NoeudAbstrait> obtenirDuplication(int indice);
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<NoeudAbstrait> NoeudDuplication::obtenirDuplication(int indice)
///
/// Cette fonction retourne le noeud d'un des objets présentement duppliqué se situant à l'indice donné.
///
/// @param indice : l'indice à lequel se situe le noeud voulu.
///
/// @return : Aucune
////////////////////////////////////////////////////////////////////////

inline std::shared_ptr<NoeudAbstrait> NoeudDuplication::obtenirDuplication(int indice)
{
	if ((indice >= 0) && (indice < enfants_.size())) 	
	{		 
		return enfants_[indice];
	}
	else 
	{
		return nullptr;
	}
}

#endif // __ARBRE_NOEUDS_NOEUDDUPLICATION_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////