///////////////////////////////////////////////////////////////////////////
/// @file NoeudDupliquation.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDDUPLIQUATION_H__
#define __ARBRE_NOEUDS_NOEUDDUPLIQUATION_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class VisiteurAbstrait;

class NoeudDupliquation : public NoeudComposite
{
public:

	/// Constructeur
	NoeudDupliquation(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudDupliquation();
	/// Affiche la table.
	virtual void afficherConcret() const;
	inline std::shared_ptr<NoeudAbstrait> obtenirDuplication(int indice);
//	virtual void mettreAJourQuadEnglobantConcret();
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:

};

inline std::shared_ptr<NoeudAbstrait> NoeudDupliquation::obtenirDuplication(int indice)
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