///////////////////////////////////////////////////////////////////////////
/// @file CapteurOptique.h
/// @author Olivier St-Amour
/// @date 2016-02-28
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_OPTIQUE_H
#define CAPTEUR_OPTIQUE_H

#include <memory>
#include "glm\glm.hpp"

////////////////////////////////////////////////////////////////////////////////
/// @class CapteurOptique
/// @brief Classe repr�sentant l'un des 3 capteurs optiques du suiveur de ligne  
///
///        Cette classe s'occupe de g�rer la d�tection des lignes. 
///
/// @author Olivier St-Amour
/// @date 2016-02-25
///////////////////////////////////////////////////////////////////////////////
class CapteurOptique
{
public:
	// Constructeur par d�faut.
	CapteurOptique();
	// Constructeur par param�tres.
	CapteurOptique(const glm::dvec3& positionRelative);
	// Destructeur.
	~CapteurOptique();
    
	// Obtenir l'�tat du capteur.
	inline bool ligneEstDetectee() const;
    // Assigner l'�tat du capteur.
    inline void assignerLigneEstDetectee(const bool& ligneEstDetectee);
    // Obtenir la position courante.  
    inline glm::dvec3 obtenirPositionCourante() const;

	// Mise � jour de l'�tat du capteur.
	void mettreAJourPosition(const glm::dvec3& positionRobot, const double& angleRotationRobot);

private:
	bool ligneEstDetectee_{ false };
	glm::dvec3 positionRelative_{ 0.0, 0.0, 0.0 };
    glm::dvec3 positionCourante_{ 0.0, 0.0, 0.0 };
};

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::ligneEstDetectee() const 
///
/// Cette m�thode retourne l'�tat du capteur optique.
///
/// @return Le capteur a d�tect� une ligne ou non.  
///
////////////////////////////////////////////////////////////////////////////////
inline bool CapteurOptique::ligneEstDetectee() const
{
	return ligneEstDetectee_;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::assignerLigneEstDetectee(const bool& ligneEstDetectee)
///
/// Cette m�thode assigne l'�tat du capteur optique.
///
/// @param[in] ligneEstDectee : indique si une ligne est d�tect�e.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurOptique::assignerLigneEstDetectee(const bool& ligneEstDetectee)
{
    ligneEstDetectee_ = ligneEstDetectee;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::obtenirPositonCourante() const
///
/// Cette m�thode retourne l'�tat du capteur optique.
///
/// @return La position courante du capteur.
///
////////////////////////////////////////////////////////////////////////////////
inline glm::dvec3 CapteurOptique::obtenirPositionCourante() const
{
    return positionCourante_;
}

#endif // CAPTEUR_OPTIQUE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
