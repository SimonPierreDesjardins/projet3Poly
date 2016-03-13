///////////////////////////////////////////////////////////////////////////
/// @file NoeudRouest.h
/// @author Frédéric Grégoire
/// @date 2016-03-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_ROUES_H__
#define __ARBRE_NOEUD_ROUES_H__

#include "NoeudComposite.h"
#include "GL/glew.h"
#include "SuiveurLigne.h"
#include "CapteurDistance.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui représente le robot du premier projet intégrateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRoues : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRoues(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRoues();

	void setPositionRelative(float x, float y, float z);

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);
};

#endif // __ARBRE_NOEUD_ROUES_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
