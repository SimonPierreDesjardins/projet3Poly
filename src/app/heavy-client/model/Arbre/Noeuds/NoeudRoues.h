///////////////////////////////////////////////////////////////////////////
/// @file NoeudRoues.h
/// @author Fr�d�ric Gr�goire
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


class NoeudRobot;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudRoues
/// @brief Classe qui repr�sente les roues du robot.
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-03-13
///////////////////////////////////////////////////////////////////////////
class NoeudRoues : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRoues(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRoues();

	void setVitesseCourante(float vitesse);

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
	float vitesseCourante_{ 0.f };
};

#endif // __ARBRE_NOEUD_ROUES_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
