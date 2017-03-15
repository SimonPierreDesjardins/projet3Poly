///////////////////////////////////////////////////////////////////////////
/// @file NoeudDuplication.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDDuplication_H__
#define __ARBRE_NOEUDS_NOEUDDuplication_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudDuplication
/// @brief Noeud qui représente une duplication lors de l'utilisation 
///		   de l'outil duplication.
///
/// @author Olivier St-Amour
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudDuplication : public NoeudComposite
{
public:

	/// Constructeur
	NoeudDuplication(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudDuplication();
	/// Affiche la table.
	virtual void afficherConcret() const;
	/// Obtenir le pointeur intelligent d'un noeud dans le but de faire un transfert de possession.
	inline std::shared_ptr<NoeudAbstrait> obtenirDuplication(const int& indice);
	//virtual void mettreAJourQuadEnglobantConcret();
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<NoeudAbstrait> NoeudDuplication::obtenirDuplication(const int& indice)
///
/// Cette fonction permet de retourner l'enfant d'un noeud duplication.
///
/// @param[in] indice : l'indice correspondant à l'enfant de la duplication.
///
/// @return un shared_ptr sur l'enfant.
///
////////////////////////////////////////////////////////////////////////
inline std::shared_ptr<NoeudAbstrait> NoeudDuplication::obtenirDuplication(const int& indice)
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