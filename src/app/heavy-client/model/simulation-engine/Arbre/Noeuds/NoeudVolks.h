///////////////////////////////////////////////////////////////////////////
/// @file NoeudVolks.h
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
/// @version 1.0
///
/// @addtogroup inf3900 LOG3900
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_VOLKS_H__
#define __ARBRE_NOEUD_VOLKS_H__

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
/// @class NoeudTruck
/// @brief Classe qui repr�sente le modele de Truck.
///
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
///////////////////////////////////////////////////////////////////////////
class NoeudVolks : public NoeudComposite
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
	NoeudVolks(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudVolks();

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

	void assignerCouleurs(int modele, int a, int r, int g, int b);

	void assignerMode(int mode);

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

	glm::dvec3 vitesseTranslationCollision_{ 0.0, 0.0, 0.0 };
	double vitesseAngulaireCollision_{ 0.0 };

	glm::dvec3 dernierePositionRelative_;
	double dernierAngleRotation_;

	float angle_{ 0.f };
	float acceleration_{ 70.0 };

	//attribut pour la couleur

	bool optionDebug{ true };

	// Les attributs du robot.
	ProfilUtilisateur* profil_{ nullptr };
	RectangleEnglobant rectangleEnglobant_;
	SuiveurLigne* suiveurLigne_{ nullptr };
	ConteneurCapteursDistance* capteursDistance_{ nullptr };

	/*std::unique_ptr<VisiteurDetectionRobot> visiteur_{ nullptr };*/
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
	float* couleur_;
	bool estCouleurDefaut_ = true;
	int mode_;

	ControleurLumiere* controleurLumiere_{ nullptr };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* NoeudVolks::obtenirSuiveurLigne()
///
/// Cette fonction retourne une r�f�rence sur le suiveur de ligne.
///
/// @param[in] Aucune.
///
/// @return SuiveurLigne* : un pointeur sur le suiveur de ligne.
///
////////////////////////////////////////////////////////////////////////
inline SuiveurLigne* NoeudVolks::obtenirSuiveurLigne()
{
	return suiveurLigne_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* NoeudVolks::obtenirSuiveurLigne()
///
/// Cette fonction retourne une r�f�rence le conteneur de capteurs de distance.
///
/// @param[in] Aucune.
///
/// @return ConteneurCapteursDistance* : un pointeur sur le conteneur (un std::array).
///
////////////////////////////////////////////////////////////////////////
inline NoeudVolks::ConteneurCapteursDistance* NoeudVolks::obtenirCapteursDistance()
{
	return capteursDistance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVolks::obtenirVitesseDroite() const
///
/// Cette fonction retourne la vitesse du moteur de droite
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de droite.
///
////////////////////////////////////////////////////////////////////////
inline float NoeudVolks::obtenirVitesseDroite() const
{
	return vitesseDroite_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVolks::obtenirVitesseGauche() const
///
/// Cette fonction retourne la vitesse du moteur de gauche
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de gauche.
///
////////////////////////////////////////////////////////////////////////
inline float NoeudVolks::obtenirVitesseGauche() const
{
	return vitesseGauche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVolks::assignerVitesseDroite() const
///
/// Cette modifie la vitesse de rotation du moteur de droite.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudVolks::assignerVitesseDroite(float vitesse)
{
	vitesseDroite_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVolks::assignerVitesseGauche() const
///
/// Cette modifie la vitesse de rotation du moteur de gauche.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de gauche.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudVolks::assignerVitesseGauche(float vitesse)
{
	vitesseGauche_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVolks::assignerVitesseRotation() const
///
/// Cette modifie la vitesse de rotation angulaire.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner � l'attribut vitesseRotation_.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudVolks::assignerVitesseRotation(float vitesse)
{
	vitesseRotation_ = vitesse;
}

inline void NoeudVolks::assignerEstEnCollision(bool collision)
{
	estEnCollision_ = collision;
	rectangleEnglobant_.assignerEnCollision(collision);
}

inline void NoeudVolks::assignerMutex(std::mutex* mutex)
{
	mutexControleRobot_ = mutex;
}


#endif // __ARBRE_NOEUD_VOLKS_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
