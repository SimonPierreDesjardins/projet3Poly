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

    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_DROITE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_CENTRE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_GAUCHE;

    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE;

    using ConteneurCapteursDistance = std::array<CapteurDistance, N_CAPTEURS_DISTANCE>;

	/// Constructeur à partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudRobot();

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);

    /// Méthode permettant au robot de vérifier la collision avec un noeud.
    void verifierCollision(NoeudPoteau* poteau);
    void verifierCollision(NoeudMur* noeud);
    void verifierCollision(NoeudTable* noeud);
    
	//Permet de modifier les paramètres du robot
	inline void assignerVitesseRotation(float vitesse);
	void assignerVitesseDroite(float vitesse);
	void assignerVitesseGauche(float vitesse);

	//Permet de récupérer les paramètres du robot.
	float obtenirVitesseDroite() const;
	float obtenirVitesseGauche() const;
    
	// Retourne l'états des capeurs du robot.
    inline SuiveurLigne* obtenirSuiveurLigne();     
    inline void assignerReferenceSuiveurLigne(SuiveurLigne* suiveurLigne);

    inline ConteneurCapteursDistance* obtenirCapteursDistance();
    inline void assignerReferenceCapteurDistance(ConteneurCapteursDistance* capteursDistance);

    void afficherFormeEnglobante() const;

private:
	//Vitesse des moteurs du robot
	float vitesseRotation_{ 0.f };
	float vitesseDroite_{ 0.f };
	float vitesseGauche_{ 0.f };
	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };

	float angle_{ 0.f };
	float acceleration_{ 200.0 };
   
    SuiveurLigne* suiveurLigne_{ nullptr };
    ConteneurCapteursDistance* capteursDistance_{ nullptr };

    std::unique_ptr<VisiteurDetectionRobot> visiteur_{ nullptr };
    ArbreRendu* arbre_{ nullptr };

    /// Méthode permettant au robot d'effectuer la collision.
    void effectuerCollision(/*Insérer les paramètres nécéssaires pour effectuer la collision ici.*/);

    // Mise à jour des attributs du robot.
	void mettreAJourCapteurs();
    void mettreAJourPosition(const float& dt);
    void mettreAJourRectangleEnglobant();
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
