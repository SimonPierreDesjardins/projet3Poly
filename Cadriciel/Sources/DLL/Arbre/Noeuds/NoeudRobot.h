///////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.h
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_ROBOT_H__
#define __ARBRE_NOEUD_ROBOT_H__

#include "NoeudComposite.h"
#include "GL/glew.h"
#include "SuiveurLigne.h"
#include "CapteurDistance.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui repr�sente le robot du premier projet int�grateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);

	//Permet de modifier les param�tres du robot
	void assignerVitesseRotation(float vitesse);
	void assignerVitesseDroite(float vitesse);
	void assignerVitesseGauche(float vitesse);

	//Permet de r�cup�rer les param�tres du robot. Inutilis�es pour l'instant
	float obtenirVitesseDroite() const;
	float obtenirVitesseGauche() const;


private:
	float angle_{ 0.f };
	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };
	float acceleration_{ 200.0 };
	
	SuiveurLigne SuiveurLigne_;
	std::vector<CapteurDistance> capteursDistance_;
};

#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
