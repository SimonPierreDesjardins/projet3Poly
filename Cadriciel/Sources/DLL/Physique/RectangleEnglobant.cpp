#include "RectangleEnglobant.h"

#include <glm/glm.hpp>
#include <vector>
#include "Utilitaire.h"

RectangleEnglobant::RectangleEnglobant()
{
}


RectangleEnglobant::RectangleEnglobant(const glm::dvec3& centre, const double& angle, 
    const double& hauteur, const double& largeur)
        : FormeEnglobanteAbstraite(centre), angle_(angle), hauteur_(hauteur), largeur_(largeur)
{
        
}


RectangleEnglobant::~RectangleEnglobant()
{
}


bool RectangleEnglobant::calculerPointEstDansForme(const glm::dvec3& point) const
{
    // Obtenir les vecteurs unitaires qui représentent l'orientation du rectangle.
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    // Le vecteur qui représente la distance entre le centre du rectangle et le point.
    glm::dvec3 distancePointCentre = point - positionCentre_;

    // La projection du vecteur sur la largeur et la hauteur du rectangle
    double projectionHauteur = glm::dot(distancePointCentre, orientationHauteur);
    double projectionLargeur = glm::dot(distancePointCentre, orientationLargeur);
    
    // Si les projections se situent dans le rectangle, le point est également dans le rectangle.
    return utilitaire::DANS_LIMITESXY(projectionHauteur, -hauteur_ / 2.0, hauteur_ / 2.0,
                                      projectionLargeur, -largeur_ / 2.0, largeur_ / 2.0);
}


bool RectangleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle) const
{     
    const int HAUTEUR = 0;
    const int LARGEUR = 1;

    const int N_RECTANGLES = 2;
    const int N_ORIENTATIONS = 2;

    const int N_COINS = 4;

    const RectangleEnglobant* rectangles[N_RECTANGLES];
    rectangles[0] = this;
    rectangles[1] = &rectangle;

    bool enIntersection = true;
    for (int i = 0; i < N_RECTANGLES && enIntersection; i++)
    {
        glm::dvec3 orientations[N_ORIENTATIONS];
        rectangles[i]->calculerVecteursOrientation(orientations[HAUTEUR], orientations[LARGEUR]);

        glm::dvec3 distances[N_COINS];

        // Index circulaire pour obtenir l'autre rectangle.
        int k = (i + 1) % 2;
         
        // Calcule des distances entre le centre du rectangle courant et les 4 coins de l'autre rectangle. 
        rectangles[k]->calculerDistancesPoint(distances, rectangles[i]->obtenirPositionCentre());

        // On place les dimensions dans un tableau afin de pouvoir les utiliser dans une boucle.
        double dimensions[N_ORIENTATIONS];
        dimensions[HAUTEUR] = rectangles[i]->hauteur_;
        dimensions[LARGEUR] = rectangles[i]->largeur_;

        // Projeter les distances sur chaque vecteur d'orientation du rectangle puis vérifier la disjonction.
        for (int j = 0; j < N_ORIENTATIONS && enIntersection; j++)
        {
            double min, max;
            rectangles[i]->calculerIntervalleProjection(distances, orientations[j], min, max);
            enIntersection = !rectangles[i]->calculerDisjonctionSurIntervalle(min, max,
                -dimensions[j] / 2.0, dimensions[j] / 2.0);
        }
    }
    return enIntersection;
}


void RectangleEnglobant::calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const
{
    // Calcule du vecteur qui représente la hauteur.
    orientationLargeur = { glm::cos(utilitaire::DEG_TO_RAD(angle_)),
                           glm::sin(utilitaire::DEG_TO_RAD(angle_)),
                           0.0 };

    // Calcule rapide de la perpendiculaire du vecteur.
    orientationHauteur = { -orientationLargeur.y, orientationLargeur.x, 0.0 };

    // On normalise les vecteurs pour faciliter d'autres calcules.
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


void RectangleEnglobant::calculerDistancesPoint(glm::dvec3 distances[4], 
    const glm::dvec3& point) const
{
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    // Caculer la distance entre le point et le centre puis 
    // la distance entre le centre et les 2 dimensions.
    glm::dvec3 distancePointCentre = point - positionCentre_;
    glm::dvec3 distanceCentreHauteur = orientationHauteur * hauteur_ / 2.0;
    glm::dvec3 distanceCentreLargeur = orientationLargeur * largeur_ / 2.0;

    // Calculer la distance des coins pour chacun des cadrans. 
    distances[0] = ( distancePointCentre + distanceCentreHauteur + distanceCentreLargeur );
    distances[1] = ( distancePointCentre - distanceCentreHauteur + distanceCentreLargeur );
    distances[2] = ( distancePointCentre - distanceCentreHauteur - distanceCentreLargeur );
    distances[3] = ( distancePointCentre + distanceCentreHauteur - distanceCentreLargeur );
}


void RectangleEnglobant::calculerIntervalleProjection(glm::dvec3 distances[4], 
    const glm::dvec3& orientation, double& min, double& max) const
{
    double projection = 0.0;

    // Initialiser les min/max au premier index.
    min = glm::dot(distances[0], orientation);
    max = glm::dot(distances[0], orientation);

    for (int i = 1; i < 4; i++)
    {
        projection = glm::dot(distances[i], orientation);

        // Trouver les min/max pour la projection.
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
    // Il y a une disjonction si les deux extrémités ne se trouvent pas dans le même intervalle
    // que les deux autres extrémités.

    // min1 --- max1 ---------- min2 --- max2
    bool disjonction12 = max1 < min2;
    // min2 --- max2 ---------- min1 --- max1
    bool disjonction21 = max2 < min1;

    return disjonction12 || disjonction21;
}


void RectangleEnglobant::mettreAJour(const glm::dvec3& positionCentre,
    const double& angle, const double& hauteur, const double& largeur)
{
    positionCentre_ = positionCentre;
    angle_ = angle;
    hauteur_ = hauteur;
    largeur_ = largeur;
}


bool RectangleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    return true;
}
