///////////////////////////////////////////////////////////////////////////
/// @file CapteurDistance.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include "RectangleEnglobant.h"

class NoeudPoteau;
class NoeudMur;

enum PositionCapteurDistance
{
    CAPTEUR_DISTANCE_DROITE,
    CAPTEUR_DISTANCE_CENTRE,
    CAPTEUR_DISTANCE_GAUCHE
};

enum EtatCapteurDistance
{
    AUCUNE_DETECTION,
    DETECTION_ZONE_SECURITAIRE,
    DETECTION_ZONE_DANGER
};

//#include "./../../Enum/TypeComportementEnum.cs"

///////////////////////////////////////////////////////////////////////////
/// @class CapteurDistance
/// @brief Classe qui représente un capteur de distance du robot.  
///
///        Cette classe s'occupe de gérer la détection des poteaux et des murs. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class CapteurDistance
{
public:
    // Constructeur par défaut.
    CapteurDistance();
    // Constructeur par paramètres.
    CapteurDistance(const glm::dvec3& positionCentre, const double& angle);
    //Destructeur
    ~CapteurDistance();

    // Méthodes permettant de mettre à jour l'état du capteur.
    void verifierDetection(NoeudPoteau* noeud);
    void verifierDetection(NoeudMur* noeud);
    void mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot);

    // Méthode permettant de manipuler l'état du capteur.
    inline EtatCapteurDistance obtenirEtat();
    inline void reinitialiserEtat();

    // Méthode de modification des attributs.
    void assignerActif(bool estActif);
    void assignerParametreZoneDanger(/*TypeComportement comportement,*/ double distance);
    void assignerParametreZoneSecuritaire(/*TypeComportement comportement,*/ double distance);

    // Méthode permettant de manipuler la largeur des zones de détection.
    inline void assignerLargeurZoneSecuritaire(const double& largeur);
    inline void assignerLargeurZoneDanger(const double& largeur);

    // Afficher le capteur de distance.
    void afficher() const;

    // Attributs constants publiques.
    static const double HAUTEUR;
    static const double MAX_LARGEUR_TOTALE;
    static const double LARGEUR_DEFAUT;

private:
    bool estActif_{ true };
    
    double largeurDanger_{ 5.0 };
    double largeurSecuritaire_{ 5.0 };

    EtatCapteurDistance etat_{ AUCUNE_DETECTION };
    glm::dvec3 positionCapteur_;

    RectangleEnglobant zoneSecuritaire_;
    RectangleEnglobant zoneDanger_;
    
    glm::dvec3 positionRelative_;
    double angleRelatif_;
};


////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline void CapteurDistance::assignerHauteurZoneSecuritaire(const double& largeur)
///
/// Cettre méthode permet d'assigner une largeur à la zone sécuritaire du
/// capteur de distance.
///
/// @param[in] hauteur : indique la hauteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerLargeurZoneSecuritaire(const double& largeur)
{
    zoneSecuritaire_.assignerLargeur(largeur);
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline void CapteurDistance::assignerHauteurZoneDanger(const double& largeur)
///
/// Cettre méthode permet d'assigner une largeur à la zone de danger du
/// capteur de distance.
///
/// @param[in] hauteur : indique la hauteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerLargeurZoneDanger(const double& largeur)
{
    zoneDanger_.assignerLargeur(largeur);
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline EtatCapteurDistance CapteurDistance::obtenirEtat()
///
/// Cette méthode retourne l'état du capteur de distance.
///
/// @return Un enum indiquant s'il y a une détection dans l'une des zones de
///         détection.
///
////////////////////////////////////////////////////////////////////////////////
inline EtatCapteurDistance CapteurDistance::obtenirEtat()
{
    return etat_;
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline void CapteurDistance::reinitialiserEtat()
///
/// Cette méthode permet de réinitialiser l'état du capteur à aucune détection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::reinitialiserEtat()
{
    etat_ = AUCUNE_DETECTION;
}

#endif // CAPTEUR_DISTANCE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
