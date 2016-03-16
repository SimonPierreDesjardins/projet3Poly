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

#include "FormeEnglobanteAbstraite.h"

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
class RectangleEnglobant : public FormeEnglobanteAbstraite
{
public:
    // Constructeur par défaut.
    RectangleEnglobant();
    // Constructeur par paramètres.
    RectangleEnglobant(const glm::dvec3& centre, const double & angle, 
        const double& hauteur, const double& largeur);
    // Destructeur.
    ~RectangleEnglobant();

    // Initialiser la forme à partir d'une boite englobante.
    virtual void initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante);

    // Modifications des attributs.
    inline void assignerAngle(const double& angle);
    inline void assignerHauteur(const double& hauteur);
    inline void assignerLargeur(const double& largeur);
    
    // Accès aux attributs.
    inline double obtenirAngle() const;
    inline double obtenirHauteur() const;
    inline double obtenirLargeur() const;

    void mettreAJour(const glm::dvec3& positionCentre_, const double& angle, const double& hauteur, const double& largeur);

    // Permet de calculer si un point se trouve dans une forme englobante.
    virtual bool calculerEstDansForme(const glm::dvec3& point) const;
    // Permet de calculer si un rectangle est dans la forme englobante. 
    virtual bool calculerEstDansForme(const RectangleEnglobant& rectangle) const;
    // Permet de calculer si un cerlce est dans la forme englobante.
    virtual bool calculerEstDansForme(const CercleEnglobant& cercle) const;

    // Permet de calculer si le rectangle est en intersection avec un cercle.
    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;
    // Permet de calculer si le rectangle est en intersection avec un autre rectangle.
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;
    
    // Calcule des vecteurs d'orientation unitaire.
    void calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const;
    
	virtual bool calculerCollision(const RectangleEnglobant& rectangle, glm::dvec3& normale) const;
	virtual bool calculerCollision(const CercleEnglobant& rectangle, glm::dvec3& normale) const;

    // Calcule d'un cercle autour du rectangle.
    double calculerRayon() const;

    virtual void afficher(const glm::dvec3& origine) const;
    virtual void afficher() const;

private:
    void calculerDistancesPoint(glm::dvec3 distances[4], const glm::dvec3& point) const;

    void calculerIntervalleProjection(glm::dvec3 distances[4], const glm::dvec3& orientation,
        double& min, double& max) const;

    bool calculerDisjonctionSurIntervalle(const double& min1, const double& max1, 
        const double& min2, const double& max2) const;

    void calculerPositionCoins(glm::dvec3 coins[4]);

    double angle_{ 0.0 };
    double hauteur_{ 0.0 };
    double largeur_{ 0.0 };
};

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
