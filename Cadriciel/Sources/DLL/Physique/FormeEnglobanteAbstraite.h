///////////////////////////////////////////////////////////////////////////////
/// @file FormeEnglobanteAbstraite.h
/// @author Olivier St-Amour
/// @date 2016-03-02
/// @version 2.4
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef FORME_ENGLOBANTE_ABSTRAITE_H
#define FORME_ENGLOBANTE_ABSTRAITE_H

#include <glm/glm.hpp> 
#include <vector>

class RectangleEnglobant;
class CercleEnglobant;

///////////////////////////////////////////////////////////////////////////
/// @class FormeEnglobante
/// @brief Classe qui représente le rectangle orienté autour d'un objet.
///
///        Cette classe permet de calculer la détection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class FormeEnglobanteAbstraite
{
public:
    // Constructeur par défaut.
    FormeEnglobanteAbstraite();
    // Constructeur par paramètres.
    FormeEnglobanteAbstraite(const glm::dvec3& position);
    // Destructeur.
    virtual ~FormeEnglobanteAbstraite() = 0;

    // Assigner la position du centre de la forme.
    inline void assignerPositionCentre(const glm::dvec3& positionCentre);
    // Obtenir la position du centre de la forme.
    inline glm::dvec3 obtenirPositionCentre() const;

    // Permet de calculer si un point se trouve dans une forme englobante.
    virtual bool calculerPointEstDansForme(const glm::dvec3& point) const = 0;
    // Permet de calculer si une forme est en intersection avec un cercle.
    virtual bool calculerIntersection(const CercleEnglobant& cercle) const = 0;
    // Permet de calculer si une forme est en intersection avec un rectangle.
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const = 0;
    
protected:
    glm::dvec3 positionCentre_{ 0.0, 0.0, 0.0 };
};

inline void FormeEnglobanteAbstraite::assignerPositionCentre(const glm::dvec3& positionCentre)
{
    positionCentre_ = positionCentre;
}

inline glm::dvec3 FormeEnglobanteAbstraite::obtenirPositionCentre() const
{
    return positionCentre_;
}

#endif // FORME_ENGLOBANTE_ABSTRAITE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
