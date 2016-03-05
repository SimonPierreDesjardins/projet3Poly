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
/// @brief Classe qui représente le robot du premier projet intégrateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);

	//Permet de modifier les paramètres du robot
	void assignerVitesseRotation(float vitesse);
	void assignerVitesseDroite(float vitesse);
	void assignerVitesseGauche(float vitesse);

	//Permet de récupérer les paramètres du robot.
	float obtenirVitesseDroite() const;
	float obtenirVitesseGauche() const;
    
    // Mise à jour des capteurs du robot. 	
	void mettreAJourCapteurs();
	// Retourne l'états des capeurs du robot.
	// Les 3 premiers indiquent la détection d'une ligne pour les 3 capteurs optiques du suiveur de ligne.
	uint8_t obtenirEtatSuiveurLigne();

    // Méthodes d'affichage permettant le débogage.
    void afficherCapteursOptique() const;
    void afficherCapteursDistance() const;

private:
	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };
	float acceleration_{ 200.0 };
	
	SuiveurLigne suiveurLigne_;
	std::vector<CapteurDistance> capteursDistance_;
};

#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
