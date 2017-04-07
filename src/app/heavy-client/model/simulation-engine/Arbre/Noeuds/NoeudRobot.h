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
#include <mutex>
#include <array>
#include "ControleurLumiere.h"
#include <stack>


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

	class Engine
	{
	public:
		float targetVelocity = 0.0;
		void updateVelocity(float dt);

		inline void setWheelToCenterRadius(double radius);

		inline double getTangentialVelocity() const;
		inline double getAngularVelocity() const;
		inline void resetVelocity();

		inline double getLinearFriction() const;
		inline double getAngularFriction() const;

	private:
		const double POWER = 5.0;
		double angularFriction_ = POWER;
		double tangentialVelocity_ = 0.0;
		double angularVelocity_ = 0.0;
		double radius_ = 1.0;
	};

	Engine leftEngine;
	Engine rightEngine;

    using ConteneurCapteursDistance = std::array<CapteurDistance, N_CAPTEURS_DISTANCE>;

	/// Constructeur à partir du type du noeud.
	NoeudRobot(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	void positionDepart();
	inline void giveSensors(ConteneurCapteursDistance* distanceSensors, SuiveurLigne* lineSensor);

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);
	virtual void suivreCamera();

    /// Méthode permettant au robot de vérifier la collision avec un noeud.
    bool verifierCollision(NoeudPoteau* poteau);
    bool verifierCollision(NoeudMur* noeud);
    bool verifierCollision(NoeudTable* noeud);
	bool verifierCollision(NoeudTeleporteur* noeud);
	bool verifierCollision(NoeudPiece* piece);
	bool verifierCollision(NoeudRobot* robot);

	// Permet de modifier les paramètres du robot
	inline void assignerVitesseRotation(float vitesse);

	//Permet de positionner les roues
	virtual void positionnerRoues();

    void mettreAJourPosition(float dt);
    void effectuerCollision(double dt);

	virtual void assignerCouleurs(int modele, int a, int r, int g, int b);

	void assignerMode(int mode);

	inline void assignerEstEnCollision(bool collision);
    
	// Retourne l'états des capeurs du robot.
    inline SuiveurLigne* obtenirSuiveurLigne();
    inline ConteneurCapteursDistance* obtenirCapteursDistance();
	inline RectangleEnglobant& getBoundingBox();

	virtual void setCouleurDefault(int piece,bool default);

	std::stack <NoeudAbstrait*> getTableauCoins();

	std::stack <NoeudAbstrait*> tableauCoins;


protected:

    glm::dvec3 vitesseTranslationCollision_{0.0, 0.0, 0.0};
    double vitesseAngulaireCollision_{ 0.0 };

    glm::dvec3 dernierePositionRelative_;
    double dernierAngleRotation_;

	float angle_{ 0.f };

	//attribut pour la couleur

	bool optionDebug{ true };

	// Les attributs du robot.
    RectangleEnglobant rectangleEnglobant_;
    SuiveurLigne* suiveurLigne_{ nullptr };
    ConteneurCapteursDistance* capteursDistance_{ nullptr };

    ArbreRendu* arbre_{ nullptr };

    // Mise à jour des attributs du robot.
	void mettreAJourCapteurs();
    void reinitialiserPosition();
    virtual void mettreAJourFormeEnglobante();

	bool estEnCollision_{ false };

	NoeudAbstrait* table_;
	NoeudRoues* roueGauche_;
	NoeudRoues* roueDroite_;
	NoeudRoues* roueGauche2_;
	NoeudRoues* roueDroite2_;
	NoeudTeleporteur* teleporteurCourant_{nullptr};

	float* couleur_;
	bool estCouleurDefaut_ = true;
	int mode_;
	bool teleporteurCollision_ = false;
	bool teleportationFaite_ = false;

	void updateEnginesRadius();

    // Calculer les composantes de d'une collision en fonction d'une normale de collision.
	void calculerComposantesCollision(const glm::dvec3& normale);
	void calculerComposantesCollision(const glm::dvec3& normale, NoeudRobot* entity);
	
	ControleurLumiere* controleurLumiere_{ nullptr };
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
	physics_.angularVelocity.z = vitesse;
}

inline void NoeudRobot::assignerEstEnCollision(bool collision)
{
	estEnCollision_ = collision;
    rectangleEnglobant_.assignerEnCollision(collision);
}

inline RectangleEnglobant& NoeudRobot::getBoundingBox()
{
	return rectangleEnglobant_;
}

inline void NoeudRobot::giveSensors(ConteneurCapteursDistance* distanceSensors, SuiveurLigne* lineSensor)
{
	capteursDistance_ = distanceSensors;
	suiveurLigne_ = lineSensor;
}

inline double NoeudRobot::Engine::getTangentialVelocity() const
{
	return tangentialVelocity_;
}

inline double NoeudRobot::Engine::getAngularVelocity() const
{
	return angularVelocity_;
}

inline void NoeudRobot::Engine::resetVelocity()
{
	tangentialVelocity_ = 0.0;
	angularVelocity_ = 0.0;
}

inline void NoeudRobot::Engine::setWheelToCenterRadius(double radius)
{
	if (!utilitaire::EGAL_ZERO(radius))
	{
		radius_ = radius;
		angularFriction_ = std::abs(POWER / radius_);
	}
}

inline double NoeudRobot::Engine::getLinearFriction() const
{
	return POWER;
}

inline double NoeudRobot::Engine::getAngularFriction() const
{
	return angularFriction_;
}


#endif // __ARBRE_NOEUD_ROBOT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
