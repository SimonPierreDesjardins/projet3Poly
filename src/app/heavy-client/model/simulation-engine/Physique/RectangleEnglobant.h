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
/// @brief Classe qui repr�sente le rectangle orient� autour d'un objet.
///
///        Cette classe permet de calculer la d�tection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class RectangleEnglobant : public FormeEnglobanteAbstraite
{
public:
    // Constructeur par d�faut.
    RectangleEnglobant();
    // Constructeur par param�tres.
    RectangleEnglobant(const glm::dvec3& centre, const double & angle, 
        const double& hauteur, const double& largeur);
    // Destructeur.
    ~RectangleEnglobant();

    // Initialiser la forme � partir d'une boite englobante.
    virtual void initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante);

    // Modifications des attributs.
    inline void assignerAngle(const double& angle);
    inline double obtenirAngle() const;

    inline void assignerHauteur(const double& hauteur);
    inline double obtenirHauteur() const;

    inline void assignerLargeur(const double& largeur);
    inline double obtenirLargeur() const;

    void mettreAJour(const glm::dvec3& positionCentre_, const double& angle, const double& hauteur, const double& largeur);


    virtual bool calculerEstDansLimites(const double& xMin, const double& xMax,
                                        const double& yMin, const double& yMax) const;

    // Permet de calculer si un point se trouve dans une forme englobante.
    virtual bool calculerEstDansForme(const glm::dvec3& point) const;

    // Permet de calculer si le rectangle est en intersection avec un cercle.
    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;
    // Permet de calculer si le rectangle est en intersection avec un autre rectangle.
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;
    
    // Calcule des vecteurs d'orientation unitaire.
    void calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const;
    
    virtual glm::dvec3 calculerNormaleCollision(const RectangleEnglobant& rectangle) const;
    virtual glm::dvec3 calculerNormaleCollision(const CercleEnglobant& cercle) const;
    virtual glm::dvec3 calculerNormaleCollision(const glm::dvec3& point) const;

    void calculerPositionCoins(glm::dvec3 coins[4]) const;

    // Calcule d'un cercle autour du rectangle.
    double calculerRayon() const;

    virtual void afficher(const glm::dvec3& origine) const;
    virtual void afficher() const;

private:
    void calculerDistancesPoint(glm::dvec3 distances[4], const glm::dvec3& point) const;

    void calculerIntervalleProjection(glm::dvec3 distances[4], const glm::dvec3& orientation,
        double& min, double& max) const;

    bool calculerDisjointureSurIntervalle(const double& min1, const double& max1, 
        const double& min2, const double& max2) const;

    double angle_{ 0.0 };
    double hauteur_{ 0.0 };
    double largeur_{ 0.0 };
};
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void RectangleEnglobant::assignerAngle(const double& angle)
///
/// Cette fonction assigne l'angle du rectangle englobante.
///
/// @param[in] angle : Angle du rectangle englobant en double.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void RectangleEnglobant::assignerAngle(const double& angle)
{
    angle_ = angle;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void RectangleEnglobant::assignerHauteur(const double& hauteur)
///
/// Cette fonction assigne la hauteur du rectangle englobante.
///
/// @param[in] hauteur : hauteur du rectangle englobant en double.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void RectangleEnglobant::assignerHauteur(const double& hauteur)
{
    hauteur_ = hauteur;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void RectangleEnglobant::assignerLargeur(const double& largeur)
///
/// Cette fonction assigne la largeur du rectangle englobante.
///
/// @param[in] largeur : largeur du rectangle englobant en double.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void RectangleEnglobant::assignerLargeur(const double& largeur)
{
    largeur_ = largeur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double RectangleEnglobant::obtenirAngle() const
///
/// Cette fonction retourne l'angle du rectangle englobant.
///
/// @param[in] Aucun.
///
/// @return double: Angle du rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
inline double RectangleEnglobant::obtenirAngle() const
{
    return angle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double RectangleEnglobant::obtenirHauteur() const
///
/// Cette fonction retourne la hauteur du rectangle englobant.
///
/// @param[in] Aucun.
///
/// @return double: Hauteur du rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
inline double RectangleEnglobant::obtenirHauteur() const
{
    return hauteur_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double RectangleEnglobant::obtenirLargeur() const
///
/// Cette fonction retourne la largeur du rectangle englobant.
///
/// @param[in] Aucun.
///
/// @return double: Largeur du rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
inline double RectangleEnglobant::obtenirLargeur() const
{
    return largeur_;
}

#endif // RECTANGLE_ENGLOBANT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
