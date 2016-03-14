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
#include "RectangleEnglobant.h"
#include "VisiteurDetectionRobot.h"
#include <array>

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
    static const int N_CAPTEURS_DISTANCE{ 3 };
    using ConteneurCapteursDistance = std::array<CapteurDistance, N_CAPTEURS_DISTANCE>;

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
	void assignerVitesseDroiteCourante(float vitesse);
	void assignerVitesseGaucheCourante(float vitesse);

	//Permet de récupérer les paramètres du robot.
	float obtenirVitesseDroite() const;
	float obtenirVitesseGauche() const;
	float obtenirVitesseDroiteCourante() const;
	float obtenirVitesseGaucheCourante() const;
    
	// Retourne l'états des capeurs du robot.
    inline SuiveurLigne* obtenirSuiveurLigne();     
    inline void assignerReferenceSuiveurLigne(SuiveurLigne* suiveurLigne);

    inline ConteneurCapteursDistance* obtenirCapteursDistance();
    inline void assignerReferenceCapteurDistance(ConteneurCapteursDistance* capteursDistance);

    void afficherFormeEnglobante() const;

    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_DROITE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_CENTRE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_GAUCHE;

    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE;

private:
    // Mise à jour
	void mettreAJourCapteurs();
    void mettreAJourPosition(const float& dt);
    void mettreAJourRectangleEnglobant();

	float angle_{ 0.f };
	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };
	float acceleration_{ 200.0 };
   
    SuiveurLigne* suiveurLigne_{ nullptr };
    ConteneurCapteursDistance* capteursDistance_{ nullptr };

    std::unique_ptr<VisiteurDetectionRobot> visiteur_{ nullptr };
    ArbreRendu* arbre_{ nullptr };
};

inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
{
    return suiveurLigne_;
}

inline NoeudRobot::ConteneurCapteursDistance* NoeudRobot::obtenirCapteursDistance()
{
    return capteursDistance_;
}

#endif // __ARBRE_NOEUD_ROBOT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
