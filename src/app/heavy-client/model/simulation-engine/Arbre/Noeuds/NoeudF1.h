///////////////////////////////////////////////////////////////////////////
/// @file NoeudF1.h
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
/// @version 1.0
///
/// @addtogroup inf3900 LOG3900
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_F1_H__
#define __ARBRE_NOEUD_F1_H__

#include "NoeudComposite.h"
#include "SuiveurLigne.h"
#include "CapteurDistance.h"
#include "RectangleEnglobant.h"
#include "CercleEnglobant.h"
#include "VisiteurDetectionRobot.h"
#include <mutex>
#include <array>
#include "ControleurLumiere.h"
#include "NoeudTypes.h"

class ProfilUtilisateur;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudF1
/// @brief Classe qui représente le modele de Truck.
///
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
///////////////////////////////////////////////////////////////////////////
class NoeudF1 : public NoeudRobot
{
public:

	/// Constructeur à partir du type du noeud.
	NoeudF1(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudF1();

	//Permet de positionner les roues
	void positionnerRoues();

	void assignerCouleurs(int modele, int a, int r, int g, int b);

	void afficherConcret() const;

	void suivreCamera();

	void setCouleurDefault(int piece, bool default);

private:

	// Les attributs du robot.


	NoeudRoues* roueGauche2_;
	NoeudRoues* roueDroite2_;

};


#endif // __ARBRE_NOEUD_F1_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
