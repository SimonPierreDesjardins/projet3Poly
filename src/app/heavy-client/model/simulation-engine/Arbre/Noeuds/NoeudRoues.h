///////////////////////////////////////////////////////////////////////////
/// @file NoeudRoues.h
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
#include "ProfilUtilisateur.h"


class NoeudRobot;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudRoues
/// @brief Classe qui représente les roues du robot.
///
/// @author Frédéric Grégoire
/// @date 2016-03-13
///////////////////////////////////////////////////////////////////////////
class NoeudRoues : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRoues(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRoues();

	void setVitesseCourante(float vitesse);

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	void setRightWheel(bool isRight);
	void assignerCouleurs(int modele, int a, int r, int g, int b);
	void setCouleurDefault(int piece, bool default);

private:
	float vitesseCourante_{ 0.f };
	bool isRightWheel{ false };
	float* couleur_;
	bool estCouleurDefaut_ = true;
};

#endif // __ARBRE_NOEUD_ROUES_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
