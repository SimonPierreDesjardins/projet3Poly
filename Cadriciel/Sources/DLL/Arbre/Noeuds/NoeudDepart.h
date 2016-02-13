///////////////////////////////////////////////////////////////////////////
/// @file NoeudDepart.h
/// @author Frédéric Grégoire
/// @date 2016-02-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __NOEUD_NOEUD_NOEUDDEPART_H__
#define __ARBRE_NOEUD_NOEUDDEPART_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudDepart
/// @brief Classe qui représente le point départ du projet intégrateur.
///
/// @author Frédéric Grégoire
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudDepart : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudDepart(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudDepart();

	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
//	virtual void mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative);

};


#endif // __ARBRE_NOEUD_NOEUDDEPART_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
