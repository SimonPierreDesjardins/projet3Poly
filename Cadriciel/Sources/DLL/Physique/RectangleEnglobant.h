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

    inline void assignerCentre(const glm::dvec3& centre);
    inline void assignerAngle(const double& angle);
    inline void assignerHauteur(const double& hauteur);
    inline void assignerLargeur(const double& largeur);
    
    inline glm::dvec3 obtenirCentre() const;
    inline double obtenirAngle() const;
    inline double obtenirHauteur() const;
    inline double obtenirLargeur() const;

    bool calculerPointEstDansRectangle(const glm::dvec3& point);
    bool calculerRectangleEstEnIntersection(const RectangleEnglobant& rectangle);

private:
    glm::dvec3 centre_{ 0.0, 0.0, 0.0 };
    double angle_{ 0.0 };
    double hauteur_{ 0.0 };
    double largeur_{ 0.0 };
};

inline void RectangleEnglobant::assignerCentre(const glm::dvec3& centre)
{
    centre_ = centre;
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

inline glm::dvec3 RectangleEnglobant::obtenirCentre() const
{
    return centre_;
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