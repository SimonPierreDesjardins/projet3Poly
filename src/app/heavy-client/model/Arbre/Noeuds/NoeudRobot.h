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

class ProfilUtilisateur;
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
    static const int N_CAPTEURS_DISTANCE{ 3 };

    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_DROITE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_CENTRE;
    static const glm::dvec3 POSITION_CAPTEUR_DISTANCE_GAUCHE;

    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE;
    static const double ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE;    

    using ConteneurCapteursDistance = std::array<CapteurDistance, N_CAPTEURS_DISTANCE>;

	/// Constructeur � partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	void positionDepart();

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(float dt);
	void suivreCamera();

    /// M�thode permettant au robot de v�rifier la collision avec un noeud.
    bool verifierCollision(NoeudPoteau* poteau);
    bool verifierCollision(NoeudMur* noeud);
    bool verifierCollision(NoeudTable* noeud);
    
	//Permet de modifier les param�tres du robot
	inline void assignerVitesseRotation(float vitesse);
	inline void assignerVitesseDroite(float vitesse);
	inline void assignerVitesseGauche(float vitesse);
    inline void assignerMutex(std::mutex* mutex);

    // Calculer les composantes courantes de vitesse du robot.
    void calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslationCourante, double& vitesseAngulaireCourante) const;
    // Calculer les composantes de d'une collision en fonction d'une normale de collision.
    void calculerComposantesCollision(const glm::dvec3& normale, glm::dvec3& viteseTranslationCollision,
                                      double& vitesseAngulaireCollision) const;
	//Permet de positionner les roues
	void positionnerRoues();

	//Permet de r�cup�rer les param�tres du robot.
	inline float obtenirVitesseDroite() const;
	inline float obtenirVitesseGauche() const;

	inline void assignerEstEnCollision(bool collision);
    
	// Retourne l'�tats des capeurs du robot.
    inline SuiveurLigne* obtenirSuiveurLigne();
    inline ConteneurCapteursDistance* obtenirCapteursDistance();

private:
	//Vitesse des moteurs du robot
	float vitesseRotation_{ 0.f };
	float vitesseDroite_{ 0.f };
	float vitesseGauche_{ 0.f };

	float vitesseRotationCourante_{ 0.f };
	float vitesseCouranteDroite_{ 0.f };
	float vitesseCouranteGauche_{ 0.f };

    glm::dvec3 vitesseTranslationCollision_{0.0, 0.0, 0.0};
    double vitesseAngulaireCollision_{ 0.0 };

    glm::dvec3 dernierePositionRelative_;
    double dernierAngleRotation_;

	float angle_{ 0.f };
	float acceleration_{ 70.0 };

	bool optionDebug{ true };

	// Les attributs du robot.
	ProfilUtilisateur* profil_{ nullptr };
    RectangleEnglobant rectangleEnglobant_;
    SuiveurLigne* suiveurLigne_{ nullptr };
    ConteneurCapteursDistance* capteursDistance_{ nullptr };

    std::unique_ptr<VisiteurDetectionRobot> visiteur_{ nullptr };
    ArbreRendu* arbre_{ nullptr };

    // Mise � jour des attributs du robot.
	void mettreAJourCapteurs();
    void mettreAJourPosition(const float& dt);
    void effectuerCollision(const double& dt);
    void reinitialiserPosition();
    virtual void mettreAJourFormeEnglobante();
    std::mutex* mutexControleRobot_{ nullptr };

	bool estEnCollision_{ false };
    bool enCollision_{ false };

	NoeudAbstrait* table_;
	NoeudRoues* roueGauche_;
	NoeudRoues* roueDroite_;
	
	ControleurLumiere* controleurLumiere_{ nullptr };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
///
/// Cette fonction retourne une r�f�rence sur le suiveur de ligne.
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
/// Cette fonction retourne une r�f�rence le conteneur de capteurs de distance.
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
/// @param[in] vitesse : vitesse que l'on souhaite assigner � l'attribut vitesseRotation_.
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
    rectangleEnglobant_.assignerEnCollision(collision);
}

inline void NoeudRobot::assignerMutex(std::mutex* mutex)
{
    mutexControleRobot_ = mutex;
}


#endif // __ARBRE_NOEUD_ROBOT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
