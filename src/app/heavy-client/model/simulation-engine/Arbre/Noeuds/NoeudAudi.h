///////////////////////////////////////////////////////////////////////////
/// @file NoeudAudi.h
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
/// @version 1.0
///
/// @addtogroup inf3900 LOG3900
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_AUDI_H__
#define __ARBRE_NOEUD_AUDI_H__

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
/// @class NoeudTruck
/// @brief Classe qui représente le modele de Truck.
///
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
///////////////////////////////////////////////////////////////////////////
class NoeudAudi : public NoeudRobot
{
public:

	/// Constructeur à partir du type du noeud.
	NoeudAudi(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudAudi();

	//Permet de positionner les roues
	void positionnerRoues();

	void assignerCouleurs(int modele, int a, int r, int g, int b);

	void afficherConcret() const;

	void suivreCamera(vue::Vue* vue);

	void setCouleurDefault(int piece, bool default);

	void initialisationCouleurs(int* roues, int* modele);

private:

	// Les attributs du robot.


	NoeudRoues* roueGauche2_;
	NoeudRoues* roueDroite2_;

};


#endif // __ARBRE_NOEUD_AUDI_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
