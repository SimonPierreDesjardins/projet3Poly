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
class NoeudTable;

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

#include "ComportementAbstrait.h"
#include "rapidjson\writer.h"
#include "rapidjson\document.h"

namespace rapidjson {
	class FileWriteStream;
}

///////////////////////////////////////////////////////////////////////////
/// @class CapteurDistance
/// @brief Classe qui repr�sente un capteur de distance du robot.  
///
///        Cette classe s'occupe de g�rer la d�tection des poteaux et des murs. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class CapteurDistance
{
public:
    // Constructeur par d�faut.
    CapteurDistance();

	//Constructeur par param�tre
	CapteurDistance(glm::dvec3 positionRelative, double angleRelatif, bool estActif, 
        TypeComportement comportementDanger, double largeurDanger, 
        TypeComportement comportementSecuritaire, double largeurSecuritaire);

	//Constructeur par param�tre
	CapteurDistance( glm::dvec3 positionRelative, double angleRelatif, const rapidjson::Value& capteurJSON);

    //Destructeur
    ~CapteurDistance();

    // M�thodes permettant de mettre � jour l'�tat du capteur.
    void verifierDetection(NoeudPoteau* poteau);
    void verifierDetection(NoeudMur* mur);
    void verifierDetection(NoeudTable* table);
    void mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot);

    // M�thode permettant de manipuler l'�tat du capteur.
    inline EtatCapteurDistance obtenirEtat();
    inline void reinitialiserEtat();

    // M�thode de modification des attributs.
    void assignerActif(bool estActif);

    // Afficher le capteur de distance.
    void afficher() const;

    // Attributs constants publiques.
    static const double HAUTEUR;
    static const double MAX_LARGEUR_TOTALE;
    static const double LARGEUR_DEFAUT;

	inline void assignerParametreZoneDanger(TypeComportement comportement, double largeur);
	inline void assignerParametreZoneSecuritaire(TypeComportement comportement, double largeur);

	inline bool obtenirEstActif();

	inline TypeComportement obtenirComportementZoneDanger();
	inline TypeComportement obtenirComportementZoneSecuritaire();

	inline double obtenirLargeurDanger();
	inline double obtenirLargeurSecuritaire();

	void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

private:
    bool estActif_{ true };

    TypeComportement comportementDanger_;
    TypeComportement comportementSecuritaire_;
    
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
/// Cettre m�thode permet d'assigner une largeur � la zone s�curitaire du
/// capteur de distance.
///
/// @param[in] largeur : indique la largeur.
/// @param[in] comportement : indique le comportement apr�s une d�tection d'obstacle. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerParametreZoneDanger(TypeComportement comportement, double largeur)
{
    zoneSecuritaire_.assignerLargeur(largeur);
    comportementDanger_ = comportement;
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline void CapteurDistance::assignerParametreZoneSecuritaire(TypeComportement comportement, double largeur)
///
/// Cettre m�thode permet d'assigner une largeur � la zone de danger du
/// capteur de distance ainsi que le prochain comportement.
///
/// @param[in] largeur : indique la largeur.
/// @param[in] comportement : indique le comportement apr�s une d�tection d'obstacle. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerParametreZoneSecuritaire(TypeComportement comportement, double largeur)
{
    zoneDanger_.assignerLargeur(largeur);
    comportementSecuritaire_ = comportement;
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline EtatCapteurDistance CapteurDistance::obtenirEtat()
///
/// Cette m�thode retourne l'�tat du capteur de distance.
///
/// @return Un enum indiquant s'il y a une d�tection dans l'une des zones de
///         d�tection.
///
////////////////////////////////////////////////////////////////////////////////
inline EtatCapteurDistance CapteurDistance::obtenirEtat()
{
    return etat_;
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline void CapteurDistance::reinitialiserEtat()
///
/// Cette m�thode permet de r�initialiser l'�tat du capteur � aucune d�tection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::reinitialiserEtat()
{
    etat_ = AUCUNE_DETECTION;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool CapteurDistance::obtenirEstActif()
///
/// Retourne si le capteur est actif ou non
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////////////
inline bool CapteurDistance::obtenirEstActif(){
	return estActif_;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline TypeComportement CapteurDistance::obtenirComportementZoneDanger()
///
/// Retourne le comportement � adopter dans une zone de danger
///
/// @return TypeComportement
///
////////////////////////////////////////////////////////////////////////////////
inline TypeComportement CapteurDistance::obtenirComportementZoneDanger(){
	return comportementDanger_;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline TypeComportement CapteurDistance::obtenirComportementZoneSecuritaire()
///
/// Retourne le comportement � adopter dans une zone s�curitaire
///
/// @return TypeComportement
///
////////////////////////////////////////////////////////////////////////////////
inline TypeComportement CapteurDistance::obtenirComportementZoneSecuritaire(){
	return comportementSecuritaire_;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline double CapteurDistance::obtenirLargeurDanger()
///
/// Retourne la largeur de la zone de danger
///
/// @return double
///
////////////////////////////////////////////////////////////////////////////////
inline double CapteurDistance::obtenirLargeurDanger(){
	return largeurDanger_;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline double CapteurDistance::obtenirLargeurSecuritaire()
///
/// Retourne la largeur de la zone s�curitaire
///
/// @return double
///
////////////////////////////////////////////////////////////////////////////////
inline double CapteurDistance::obtenirLargeurSecuritaire(){
	return largeurSecuritaire_;
}

#endif // CAPTEUR_DISTANCE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
