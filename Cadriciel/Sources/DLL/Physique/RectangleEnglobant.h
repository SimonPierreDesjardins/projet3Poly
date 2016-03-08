///////////////////////////////////////////////////////////////////////////////
/// @file RectangleEnglobant.h
/// @author Olivier St-Amour
/// @date 2016-03-02
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef RECTANGLE_ENGLOBANT_H
#define RECTANGLE_ENGLOBANT_H

#include <glm/glm.hpp> 
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class RectangleEnglobant
/// @brief Classe qui représente le rectangle orienté autour d'un objet.
///
///        Cette classe permet de calculer la détection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class RectangleEnglobant
{
public:
    RectangleEnglobant();
    RectangleEnglobant(const glm::dvec3& centre, const double& angle, 
        const double& hauteur, const double& largeur);
    ~RectangleEnglobant();

    inline void assignerPositionCentre(const glm::dvec3& positionCentre);
    inline void assignerAngle(const double& angle);
    inline void assignerHauteur(const double& hauteur);
    inline void assignerLargeur(const double& largeur);
    
    inline glm::dvec3 obtenirPositionCentre() const;
    inline double obtenirAngle() const;
    inline double obtenirHauteur() const;
    inline double obtenirLargeur() const;

    bool calculerPointEstDansRectangle(const glm::dvec3& point) const;
    bool calculerRectangleEstEnIntersection(const RectangleEnglobant& rectangle);

    
    void calculerDistancesCoins(std::vector<glm::dvec3>& distances, const glm::dvec3& point) const;
    void calculerVecteursOrientation(glm::dvec3& orientationLargeur, glm::dvec3& orientationHauteur) const;
    double calculerRayon() const;
    bool calculerIntersectionProjection(const std::vector<glm::dvec3>& distances) const;
    void calculerIntervalleProjection(const std::vector<glm::dvec3>& distances, const glm::dvec3& orientation,
        double& min, double& max) const;
    bool calculerDisjonctionSurIntervalle(const double& min1, const double& max1, 
        const double& min2, const double& max2) const;
private:
    glm::dvec3 positionCentre_{ 0.0, 0.0, 0.0 };
    double angle_{ 0.0 };
    double hauteur_{ 0.0 };
    double largeur_{ 0.0 };
};

inline void RectangleEnglobant::assignerPositionCentre(const glm::dvec3& centre)
{
    positionCentre_ = centre;
}

inline void RectangleEnglobant::assignerAngle(const double& angle)
{
    angle_ = angle;
}

inline void RectangleEnglobant::assignerHauteur(const double& hauteur)
{
    hauteur_ = hauteur;
}

inline void RectangleEnglobant::assignerLargeur(const double& largeur)
{
    largeur_ = largeur;
}

inline glm::dvec3 RectangleEnglobant::obtenirPositionCentre() const
{
    return positionCentre_;
}

inline double RectangleEnglobant::obtenirAngle() const
{
    return angle_;
}

inline double RectangleEnglobant::obtenirHauteur() const
{
    return hauteur_;
}

inline double RectangleEnglobant::obtenirLargeur() const
{
    return largeur_;
}

#endif // RECTANGLE_ENGLOBANT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
