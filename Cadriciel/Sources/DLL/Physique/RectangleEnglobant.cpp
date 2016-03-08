#include "RectangleEnglobant.h"

#include <glm/glm.hpp>
#include <vector>
#include "Utilitaire.h"

RectangleEnglobant::RectangleEnglobant()
{
}

RectangleEnglobant::RectangleEnglobant(const glm::dvec3& centre, const double& angle, 
    const double& hauteur, const double& largeur)
        : positionCentre_(centre), angle_(angle), hauteur_(hauteur), largeur_(largeur)
{
        
}

RectangleEnglobant::~RectangleEnglobant()
{
}


bool RectangleEnglobant::calculerPointEstDansRectangle(const glm::dvec3& point) const
{
    // Obtenir les vecteurs unitaires qui représentent l'orientation du rectangle.
    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    // Le vecteur qui représente la distance entre le centre du rectangle et le point.
    glm::dvec3 v = point - positionCentre_;

    // La projection du vecteur sur la largeur et la hauteur du rectangle
    double projectionHauteur = glm::dot(v, orientationHauteur);
    double projectionLargeur = glm::dot(v, orientationLargeur);
    
    // Si les projections se situent dans le rectangle, le point est également dans le rectangle.
    return utilitaire::DANS_LIMITESXY(projectionHauteur, -hauteur_ / 2.0, hauteur_ / 2.0,
                                      projectionLargeur, -largeur_ / 2.0, largeur_ / 2.0);
}


bool RectangleEnglobant::calculerRectangleEstEnIntersection(const RectangleEnglobant& rectangle)
{     
    std::vector<glm::dvec3> distances;
    rectangle.calculerDistancesCoins(distances, positionCentre_);

    return false;
}


void RectangleEnglobant::calculerVecteursOrientation(glm::dvec3& orientationLargeur, glm::dvec3& orientationHauteur) const
{
    orientationLargeur = { glm::cos(utilitaire::DEG_TO_RAD(angle_)),
                           glm::sin(utilitaire::DEG_TO_RAD(angle_)),
                           0.0 };
    orientationHauteur = { -orientationLargeur.y, orientationLargeur.x, 0.0 };
    glm::normalize(orientationLargeur);
    glm::normalize(orientationHauteur);
}


double RectangleEnglobant::calculerRayon() const
{
    // Obtenir les vecteurs unitaires qui représente l'orientation du rectangle.
    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);
    orientationHauteur *= hauteur_;
    orientationLargeur *= largeur_;
    return glm::distance(orientationHauteur, orientationLargeur);
}

void RectangleEnglobant::calculerDistancesCoins(std::vector<glm::dvec3>& distances, const glm::dvec3& point) const
{
    distances.clear();

    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    glm::dvec3 distancePointCentre = point - positionCentre_;
    glm::dvec3 distanceCentreHauteur = orientationHauteur * hauteur_;
    glm::dvec3 distanceCentreLargeur = orientationLargeur * largeur_;

    // Calculer les coins pour chacun des cadrans. 
    distances.push_back( distancePointCentre + distanceCentreHauteur + distanceCentreLargeur );
    distances.push_back( distancePointCentre - distanceCentreHauteur + distanceCentreLargeur );
    distances.push_back( distancePointCentre - distanceCentreHauteur - distanceCentreLargeur );
    distances.push_back( distancePointCentre + distanceCentreHauteur - distanceCentreLargeur );
}

bool RectangleEnglobant::calculerIntersectionProjection(const std::vector<glm::dvec3>& distances) const
{
    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);
    
    bool intersection = true;

    double minL, maxL; 
    calculerIntervalleProjection(distances, orientationLargeur, minL, maxL);
    intersection = calculerDisjonctionSurIntervalle(minL, maxL, -largeur_ / 2.0, largeur_ / 2.0);
    if (intersection)
    {
        double minH, maxH;
        calculerIntervalleProjection(distances, orientationHauteur, minH, maxH);
        intersection = calculerDisjonctionSurIntervalle(minH, maxH, -hauteur_ / 2.0, hauteur_ / 2.0);
    }
    return intersection;
}

void RectangleEnglobant::calculerIntervalleProjection(const std::vector<glm::dvec3>& distances, const glm::dvec3& orientation,
    double& min, double& max) const
{
    double projection = 0.0;

    min = glm::dot(distances[0], orientation);
    max = glm::dot(distances[0], orientation);

    for (int i = 1; i < distances.size(); i++)
    {
        projection = glm::dot(distances[i], orientation);

        // Trouver les min/max pour la projection sur la hauteur.
        if (projection < min)
        {
            min = projection;
        }
        if (projection > max)
        {
            max = projection;
        }
    }
}
bool RectangleEnglobant::calculerDisjonctionSurIntervalle(const double& min1, const double& max1,
    const double& min2, const double& max2) const
{
    // Il y a une disjonction si les deux points ne se trouvent pas dans l'intervalle.
    // min1 ----- max1 ---------- min2 --- max2
    bool disjonction12 = max1 < min2;
    // min2 ----- max2 ---------- min1 --- max1
    bool disjonction21 = max2 < min1;
    return !(disjonction12 || disjonction21);
}
