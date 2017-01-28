///////////////////////////////////////////////////////////////////////////////
/// @file RectangleEnglobant.cpp
/// @author Olivier St-Amour
/// @date 2015-02-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "RectangleEnglobant.h"

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <vector>
#include "Utilitaire.h"
#include "CercleEnglobant.h"
#include "AideCollision.h"
#include "Droite3D.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::RectangleEnglobant()
///
/// Constructeur par défaut de la classe
///
/// @param[in] Aucun.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant::RectangleEnglobant()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::RectangleEnglobant(	const glm::dvec3& centre, const double& angle, 
///												const double& hauteur, const double& largeur)
///
/// Constructeur qui initialise les attributs de la classe.
///
/// @param[in]	centre : position centrale du rectangle englobant,
///				angle : angle du rectangle englobant.
///				hauteur : hauteur du rectangle englobant.
///				largeur : largeur du rectangle englobant
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant::RectangleEnglobant(	const glm::dvec3& centre, const double& angle, 
										const double& hauteur, const double& largeur)
        : FormeEnglobanteAbstraite(centre), angle_(angle), hauteur_(hauteur), largeur_(largeur)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::~RectangleEnglobant()
///
/// Destructeur de la classe.
///
/// @param[in]	Aucun.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant::~RectangleEnglobant()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
///
/// Initialise les attributs de la classe selon la boiteEnglobante passée en paramètre.
///
/// @param[in]	boiteEnglobante : la boîte englobante à partir de laquelle on veut créer un rectangleEnglobant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
{
    hauteur_ = glm::abs(boiteEnglobante.coinMax.y - boiteEnglobante.coinMin.y);
    largeur_ = glm::abs(boiteEnglobante.coinMax.x - boiteEnglobante.coinMin.x);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerEstDansLimites(	const double& xMin, const double& xMax,
///													const double& yMin, const double& yMax)
///
/// Détermine si le rectangle englobant est à l'intérieur de la zone passée en paramètre.
///
/// @param[in]	xMin : la valeur en x du coin minimum de la zone.
///				xMax : la valeur en x du coin maximum de la zone.
///				yMin : la valeur en y du coin minimum de la zone.
///				yMax : la valeur en y du coin maximum de la zone.
///
/// @return bool : indique si le rectangle est dans la zone ou non.
///
////////////////////////////////////////////////////////////////////////
bool RectangleEnglobant::calculerEstDansLimites(const double& xMin, const double& xMax,
                                                const double& yMin, const double& yMax) const
{
    const int N_COINS = 4;
    glm::dvec3 coins[N_COINS];
    calculerPositionCoins(coins);
    
    bool coinsDansLimite = true;

    for (int i = 0; i < N_COINS && coinsDansLimite; i++)
    {
        coinsDansLimite = utilitaire::DANS_LIMITESXY(coins[i].x, xMin, xMax,
                                                     coins[i].y, yMin, yMax);
    }
    return coinsDansLimite;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerEstDansForme(const glm::dvec3& point)
///
/// Détermine si le point passé en paramètre est dans le rectangle englobant.
///
/// @param[in]	point : point dont on veut vérifier la position.
///
/// @return bool : indique si oui ou non le point se trouve dans le rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
bool RectangleEnglobant::calculerEstDansForme(const glm::dvec3& point) const
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

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle)
///
/// Détermine s'il y a intersection entre le rectangle englobant actuel et le rectangle englobant passé en paramètre.
///
/// @param[in]	rectangle : rectangle avec lequel on veut vérifier l'intersection.
///
/// @return bool : indique si oui ou non il y a intersection entre les rectangles englobants.
///
////////////////////////////////////////////////////////////////////////
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
            enIntersection = !rectangles[i]->calculerDisjointureSurIntervalle(min, max,
                -dimensions[j] / 2.0, dimensions[j] / 2.0);
        }
    }
    return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const
///
/// Calcul les vecteurs (unitaires) d'orientation du rectangle englobant et les met dans les variables passées en paramètres.
///
/// @param[in]	orientationHauteur : variable dans laquelle on met le vecteur correspondant à l'orientation de la hauteur du rectangle englobant.
///				orientationLargeur : variable dans laquelle on met le vecteur correspondant à l'orientation de la largeur du rectangle englobant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const
{
    // Calcule du vecteur qui représente la hauteur.
    orientationLargeur = { glm::cos(utilitaire::DEG_TO_RAD(angle_)),
                           glm::sin(utilitaire::DEG_TO_RAD(angle_)),
                           0.0 };

    // Calcule rapide de la perpendiculaire du vecteur.
    orientationHauteur = { -orientationLargeur.y, orientationLargeur.x, 0.0 };

    // On normalise les vecteurs pour faciliter d'autres calcules.
    orientationLargeur = glm::normalize(orientationLargeur);
    orientationHauteur = glm::normalize(orientationHauteur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerRayon() const
///
/// Calcul le rayon d'un cercle autour du rectangle.
///
/// @param[in]	Aucun.
///
/// @return double : le rayon du cercle.
///
////////////////////////////////////////////////////////////////////////
double RectangleEnglobant::calculerRayon() const
{
    // Obtenir les vecteurs unitaires qui représente l'orientation du rectangle.
    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    orientationHauteur *= hauteur_;
    orientationLargeur *= largeur_;

    return glm::distance(orientationHauteur, orientationLargeur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerDistancesPoint(	glm::dvec3 distances[4], 
///													const glm::dvec3& point) const
///
/// Calcul la distance entre les coins du rectangle englobant et le point passé en paramètre et met les valeurs dans la variable coins passée en paramètre.
///
/// @param[in]	distances : tableau de 4 vecteurs dans lequel on met les valeurs correspondant à la distance entre chaque coin du rectangle et le point passé en paramètre.
///				point : point duquel on veut la distance avec les coins du rectangle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerIntervalleProjection(	glm::dvec3 distances[4], 
///															const glm::dvec3& orientation, double& min, double& max) const
///
/// Projette les quatres vecteurs passés en paramètre sur l'orientation passée en paramètre et retourne l'intervalle de ces projections via les variables min et max passées en paramètre.
///
/// @param[in]	distances : les quatres vecteurs que l'on veut projeter.
///				orientation : le vecteur sur lequel on fait les projections.
///				min : valeur minimum de l'intervalle intervalle calculé.
///				max : valeur maximum du l'intervalle intervalle calculé.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerDisjointureSurIntervalle(	const double& min1, const double& max1,
///																const double& min2, const double& max2) const
///
/// Détermine si les deux intervalles passés en paramètre sont en disjointure.
///
/// @param[in]	min1 : valeur minimum du premier intervalle.
///				max1 : valeur maximum du premier intervalle.
///				min2 : valeur minimum du deuxième intervalle.
///				max2 : valeur maximum du deuxième intervalle.
///
/// @return bool : indique si oui ou non les intervalles sont en disjointure (séparés).
///
////////////////////////////////////////////////////////////////////////
bool RectangleEnglobant::calculerDisjointureSurIntervalle(const double& min1, const double& max1,
    const double& min2, const double& max2) const
{
    // Il y a une disjointure si les deux extrémités ne se trouvent pas dans le même intervalle
    // que les deux autres extrémités.

    // min1 --- max1 ---------- min2 --- max2
    bool disjointure12 = max1 < min2;
    // min2 --- max2 ---------- min1 --- max1
    bool disjointure21 = max2 < min1;

    return disjointure12 || disjointure21;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::mettreAJour(const glm::dvec3& positionCentre,
///										const double& angle, const double& hauteur, const double& largeur)
///
/// Met à jour les attributs de la classe selon les données passées en paramètres.
///
/// @param[in]	positionCentre : position du centre du rectangle englobant.
///				angle : angle du rectangle englobant.
///				hauteur : hauteur du rectangle englobant.
///				largeur : largeur du rectangle englobant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::mettreAJour(const glm::dvec3& positionCentre,
    const double& angle, const double& hauteur, const double& largeur)
{
    positionCentre_ = positionCentre;
    angle_ = angle;
    hauteur_ = hauteur;
    largeur_ = largeur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerIntersection(const CercleEnglobant& cercle)
///
/// Détermine s'il y a intersection entre le rectangle englobant actuel et le cercle englobant passé en paramètre.
///
/// @param[in]	cercle : cercle avec lequel on veut vérifier l'intersection.
///
/// @return bool : indique si oui ou non il y a intersection entre le rectangle et le cercle.
///
////////////////////////////////////////////////////////////////////////
bool RectangleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    glm::dvec3 positionCercle = cercle.obtenirPositionCentre();
    const int HAUTEUR = 0;
    const int LARGEUR = 1;
    const int N_ORIENTATIONS = 2;
    glm::dvec3 orientations[N_ORIENTATIONS];
    calculerVecteursOrientation(orientations[HAUTEUR], orientations[LARGEUR]);

    glm::dvec3 distances[4];
    calculerDistancesPoint(distances, positionCercle);
    
    double rayon = cercle.obtenirRayon();

    glm::dvec3 distanceCentres = positionCercle - positionCentre_;
    glm::dvec3 orientationDistanceCentre = glm::normalize(distanceCentres);
    
    double min = 0.0;
    double max = 0.0;
    calculerIntervalleProjection(distances, orientationDistanceCentre, min, max);
    bool intersection = !calculerDisjointureSurIntervalle(-rayon, rayon, min, max);

    for (int i = 0; i < N_ORIENTATIONS && intersection; i++)
    {
        min = 0.0;
        max = 0.0;

        calculerIntervalleProjection(distances, orientations[i], min, max);
        intersection = !calculerDisjointureSurIntervalle(-rayon, rayon, min, max);
    }
    return intersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::afficher(const glm::dvec3& origine)
///
/// Affiche le rectangle englobant autour de l'objet.
///
/// @param[in]	origine : point de repère selon lequel le rectangle englobant est afficher.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::afficher(const glm::dvec3& origine) const
{
    glm::dvec3 positionRelative = positionCentre_ - origine;

    glPushMatrix();

    if (enCollision_)
    {
        glColor3d(0.0, 1.0, 0.0);
    }
    else
    {
        glColor3d(1.0, 0.0, 0.0);
    }

    glTranslated(positionRelative.x, positionRelative.y, 0.0);
    glRotated(angle_, 0.0, 0.0, 1.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3d(largeur_ / 2.0, hauteur_ / 2.0, 5.0);
	glVertex3d(-largeur_ / 2.0, hauteur_ / 2.0, 5.0);
	glVertex3d(-largeur_ / 2.0, -hauteur_ / 2.0, 5.0);
	glVertex3d(largeur_ / 2.0, -hauteur_ / 2.0, 5.0);

	glEnd();
    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::afficher()
///
/// Appelle la fonction afficher avec la table comme origine. 
///
/// @param[in]	Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::afficher() const
{
    afficher({ 0.0, 0.0, 5.0 });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerPositionCoins(glm::dvec3 coins[4])
///
/// Calcule les coins du rectangle englobant et les met dans la variable passée en paramètre.
///
/// @param[in]	coins : tableau contenant les variables dans lesquelles ont met la position des coins du rectangle englobant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RectangleEnglobant::calculerPositionCoins(glm::dvec3 coins[4]) const
{
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    glm::dvec3 distanceCentreHauteur = orientationHauteur * hauteur_ / 2.0;
    glm::dvec3 distanceCentreLargeur = orientationLargeur * largeur_ / 2.0;

    coins[0] = positionCentre_ + distanceCentreLargeur + distanceCentreHauteur;
    coins[1] = positionCentre_ - distanceCentreLargeur + distanceCentreHauteur;
    coins[2] = positionCentre_ - distanceCentreLargeur - distanceCentreHauteur;
    coins[3] = positionCentre_ + distanceCentreLargeur - distanceCentreHauteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerNormaleCollision(const RectangleEnglobant& rectangle) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	rectangle : rectangle avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 RectangleEnglobant::calculerNormaleCollision(const RectangleEnglobant& rectangle) const
{
    const int N_COINS = 4;

    // Calculer les coins de ce rectangle.
    glm::dvec3 coins_[4];
    calculerPositionCoins(coins_);

    glm::dvec3 normale = { 0.0, 0.0, 0.0 };

    // On commence par vérifier si ou ou plusieurs coins est dans l'autre rectangle.
    bool coinDansAutreRectangle = false;
    for (int i = 0; i < N_COINS; i++)
    {
        bool coinDansRectangle = rectangle.calculerEstDansForme(coins_[i]);
        if (coinDansRectangle)
        {
            normale += rectangle.obtenirPositionCentre() - coins_[i];
            coinDansAutreRectangle = true;
        }
    }

    if (!coinDansAutreRectangle)
    {
        // Calculer les coins de l'autre rectangle.
        glm::dvec3 coins[4];
        rectangle.calculerPositionCoins(coins);

        // Initialier la recherche de la droite en collision
        math::Droite3D droiteEnCollision(coins_[0], coins_[1]);
        double minDistanceDroite = droiteEnCollision.distancePoint(coins[0]);
        
        // Trouver la droite la plus proche du coin en collision.
        for (int i = 1; i < N_COINS; i++)
        {
            // Indexe circulaire pour créer une droite avec deux coins adjacents.
            int k = (i + 1) % N_COINS;
            math::Droite3D droite(coins_[i], coins_[k]);

            for (int j = 0; j < N_COINS; j++)
            {
                // La droite la plus proche du coin est la droite en collision.
                double distanceDroite = droite.distancePoint(coins[j]);
                if (distanceDroite < minDistanceDroite)
                {
                    minDistanceDroite = distanceDroite;
                    droiteEnCollision = droite;
                }
            }
        }
        // la normale est la perpendiculaire de l'orientation de la droite.
        glm::dvec3 orientationDroite = droiteEnCollision.lireVecteur();
        normale = { -orientationDroite.y, orientationDroite.x, 0.0 };
    }
    return glm::normalize(normale);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerNormaleCollision(const CercleEnglobant& cercle) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	cercle : cercle avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 RectangleEnglobant::calculerNormaleCollision(const CercleEnglobant& cercle) const
{
    glm::dvec3 coins[4];
    calculerPositionCoins(coins);
    int j = 0;
    bool collisionSegment = false;
    double minDistance = glm::distance(cercle.obtenirPositionCentre(), coins[0]);
    glm::dvec3 coinEnCollision = coins[0];
    glm::dvec3 normale = { 0.0, 0.0, 0.0 };
    for (int i = 0; i < 4; i++)
    {
        j = (i + 1) % 4;
        // Vérifier une intersection avec un segment.
        aidecollision::DetailsCollision details = aidecollision::calculerCollisionSegment(coins[i], coins[j],
            cercle.obtenirPositionCentre(),
            cercle.obtenirRayon(),
            false);
        // Si la collision est de type segment
        if (details.type == aidecollision::COLLISION_SEGMENT)
        {
            //normale += details.direction;
            normale += cercle.obtenirPositionCentre() - positionCentre_;
            collisionSegment = true;
        }
        
        // Le coin le plus proche du centre du cercle est le coin en collision.
        double distanceCoinCentre = glm::distance(cercle.obtenirPositionCentre(), coins[i]);
        if (distanceCoinCentre < minDistance)
        {
            minDistance = distanceCoinCentre;
            coinEnCollision = coins[i];
        }
    }
    // Si on ne trouve pas de collision de type segment, la normale de collision est la distance entre le centre du cercle et le coin.
    if (!collisionSegment)
    {
        normale += cercle.obtenirPositionCentre() - coinEnCollision;
    }
    return glm::normalize(normale);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant::calculerNormaleCollision(const glm::dvec3& point) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	point : point avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 RectangleEnglobant::calculerNormaleCollision(const glm::dvec3& point) const
{
    const int N_COINS = 4;
    glm::dvec3 coins[N_COINS];
    calculerPositionCoins(coins);

    // Initialier la recherche de la droite en collision
    math::Droite3D droiteEnCollision(coins[0], coins[1]);
    double minDistanceDroite = droiteEnCollision.distancePoint(point);
    
    // Trouver la droite la plus proche du coin en collision.
    for (int i = 1; i < N_COINS; i++)
    {
        // Indexe circulaire pour créer une droite avec deux coins adjacents.
        int k = (i + 1) % N_COINS;
        math::Droite3D droite(coins[i], coins[k]);

        // La droite la plus proche du coin est la droite en collision.
        double distanceDroite = droite.distancePoint(point);
        if (distanceDroite < minDistanceDroite)
        {
            minDistanceDroite = distanceDroite;
            droiteEnCollision = droite;
        }
    }
    // la normale est la perpendiculaire de l'orientation de la droite.
    glm::dvec3 orientationDroite = droiteEnCollision.lireVecteur();
    glm::dvec3 normale = { orientationDroite.y, -orientationDroite.x, 0.0 };
    return glm::normalize(normale);
}
