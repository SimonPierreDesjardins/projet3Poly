///////////////////////////////////////////////////////////////////////////////
/// @file CercleEnglobant.h
/// @author Olivier St-Amour
/// @date 2016-03-08
/// @version 2.3
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef CERCLE_ENGLOBANT_H
#define CERCLE_ENGLOBANT_H

#include "FormeEnglobanteAbstraite.h"

///////////////////////////////////////////////////////////////////////////
/// @class FormEnglobante
/// @brief Classe qui représente le rectangle orienté autour d'un objet.
///
///        Cette classe permet de calculer la détection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-03-08
///////////////////////////////////////////////////////////////////////////
class CercleEnglobant : public FormeEnglobanteAbstraite
{
public:
    // Constructeur par défaut.
    CercleEnglobant();
    // Constructeur par paramètres.
    CercleEnglobant(const glm::dvec3& positionCentre, const double& rayon);
    // Destructeur.
    virtual ~CercleEnglobant();

    inline void assignerRayon(const double& rayon);

    inline double obtenirRayon() const;

    virtual bool calculerPointEstDansForme(const glm::dvec3& point) const;

    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;

    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;

    virtual void mettreAJourFormeEnglobante(const glm::dvec3& positionCentre, const double& angle,
        const double& largeur, const double& hauteur);
private:
    double rayon_;
};

inline void CercleEnglobant::assignerRayon(const double& rayon)
{
    rayon_ = rayon;
}

inline double CercleEnglobant::obtenirRayon() const
{
    return rayon_;
}

#endif // CERCLE_ENGLOBANT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////