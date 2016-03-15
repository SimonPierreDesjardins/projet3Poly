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
#include "SuiveurLigne.h"
#include "CapteurDistance.h"

#include "RectangleEnglobant.h"
#include "CercleEnglobant.h"
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

    static const glm::dvec3 POSITION_RELATIVE_CERCLE_ENGLOBANT;
    static const double RAYON_CERCLE_ENGLOBANT;

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
    bool verifierCollision(NoeudPoteau* poteau);
    bool verifierCollision(NoeudMur* noeud);
    bool verifierCollision(NoeudTable* noeud);
    
	//Permet de modifier les paramètres du robot
	inline void assignerVitesseRotation(float vitesse);
	inline void assignerVitesseDroite(float vitesse);
	inline void assignerVitesseGauche(float vitesse);

	//Permet de positionner les roues
	void positionnerRoues();

	//Permet de récupérer les paramètres du robot.
	inline float obtenirVitesseDroite() const;
	inline float obtenirVitesseGauche() const;

	inline void assignerEstEnCollision(bool collision);
    
	// Retourne l'états des capeurs du robot.
    inline SuiveurLigne* obtenirSuiveurLigne();
    inline ConteneurCapteursDistance* obtenirCapteursDistance();


private:
	//Vitesse des moteurs du robot
	float vitesseRotation_{ 0.f };
	float vitesseDroite_{ 0.f };
	float vitesseGauche_{ 0.f };

protected:

	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };

	float vitesseDroiteCollision_{ 0.f };
	float vitesseGaucheCollision_{ 0.f };

	float angle_{ 0.f };
	float acceleration_{ 70.0 };


    RectangleEnglobant rectangleEnglobant_;
   
    SuiveurLigne* suiveurLigne_{ nullptr };
    ConteneurCapteursDistance* capteursDistance_{ nullptr };

    std::unique_ptr<VisiteurDetectionRobot> visiteur_{ nullptr };
    ArbreRendu* arbre_{ nullptr };

    /// Méthode permettant au robot d'effectuer la collision.
    void effectuerCollision(glm::dvec3 normale);

    // Mise à jour des attributs du robot.
	void mettreAJourCapteurs();
    void mettreAJourPosition(const float& dt);
    void mettreAJourRectangleEnglobant();

	bool estEnCollision_{ false };

	NoeudAbstrait* table_;

	NoeudRoues* roueGauche_;
	NoeudRoues* roueDroite_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
///
/// Cette fonction retourne une référence sur le suiveur de ligne.
///
/// @param[in] Aucune.
///
/// @return SuiveurLigne* : un pointeur sur le suiveur de ligne.
///
////////////////////////////////////////////////////////////////////////
inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
{
    return suiveurLigne_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
///
/// Cette fonction retourne une référence le conteneur de capteurs de distance.
///
/// @param[in] Aucune.
///
/// @return ConteneurCapteursDistance* : un pointeur sur le conteneur (un std::array).
///
////////////////////////////////////////////////////////////////////////
inline NoeudRobot::ConteneurCapteursDistance* NoeudRobot::obtenirCapteursDistance()
{
    return capteursDistance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirVitesseDroite() const
///
/// Cette fonction retourne la vitesse du moteur de droite
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de droite.
///
////////////////////////////////////////////////////////////////////////
inline float NoeudRobot::obtenirVitesseDroite() const
{
	return vitesseDroite_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirVitesseGauche() const
///
/// Cette fonction retourne la vitesse du moteur de gauche
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de gauche.
///
////////////////////////////////////////////////////////////////////////
inline float NoeudRobot::obtenirVitesseGauche() const
{
	return vitesseGauche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseDroite() const
///
/// Cette modifie la vitesse de rotation du moteur de droite.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudRobot::assignerVitesseDroite(float vitesse)
{
	vitesseDroite_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseGauche() const
///
/// Cette modifie la vitesse de rotation du moteur de gauche.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de gauche.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudRobot::assignerVitesseGauche(float vitesse)
{
	vitesseGauche_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseRotation() const
///
/// Cette modifie la vitesse de rotation angulaire.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner à l'attribut vitesseRotation_.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudRobot::assignerVitesseRotation(float vitesse)
{
	vitesseRotation_ = vitesse;
}

inline void NoeudRobot::assignerEstEnCollision(bool collision)
{
	estEnCollision_ = collision;
}
#endif // __ARBRE_NOEUD_ROBOT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
