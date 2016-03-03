#include "RectangleEnglobant.h"

#include <glm/glm.hpp>
#include "Utilitaire.h"

RectangleEnglobant::RectangleEnglobant()
{
}

RectangleEnglobant::RectangleEnglobant(const glm::dvec3& centre, const double& angle, 
    const double& hauteur, const double& largeur)
        : centre_(centre), hauteur_(hauteur), largeur_(largeur), angle_(angle)
{
}

RectangleEnglobant::~RectangleEnglobant()
{
}


bool RectangleEnglobant::calculerPointEstDansRectangle(const glm::dvec3& point)
{
    // Obtenir les vecteurs unitaires qui représentent l'orientation du rectangle.
    glm::dvec3 orientationLargeur = { glm::cos(utilitaire::DEG_TO_RAD(angle_)),
                                      glm::sin(utilitaire::DEG_TO_RAD(angle_)),
                                      0.0 };
    glm::dvec3 orientationHauteur = { -orientationLargeur.y, orientationLargeur.x, 0.0 };
    glm::normalize(orientationLargeur);
    glm::normalize(orientationHauteur);

    // Le vecteur qui représente la distance entre le centre du rectangle et le point.
    glm::dvec3 v = point - centre_;

    // La projection du vecteur sur la largeur et la hauteur du rectangle
    double projectionHauteur = glm::dot(v, orientationHauteur);
    double projectionLargeur = glm::dot(v, orientationLargeur);
    
    // Si les projections se situent dans le rectangle, le point est également dans le rectangle.
    return utilitaire::DANS_LIMITESXY(projectionHauteur, -hauteur_ / 2.0, hauteur_ / 2.0,
                                      projectionLargeur, -largeur_ / 2.0, largeur_ / 2.0);
}

bool RectangleEnglobant::calculerRectangleEstEnIntersection(const RectangleEnglobant& rectangle)
{
    return true;
}


