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

    virtual void initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante);

    inline void assignerRayon(const double& rayon);
    inline double obtenirRayon() const;

    virtual bool calculerEstDansForme(const glm::dvec3& point) const;
    // Permet de calculer si un rectangle est dans la forme englobante. 
    virtual bool calculerEstDansForme(const RectangleEnglobant& rectangle) const;
    // Permet de calculer si un cercle est dans la forme englobante.
    virtual bool calculerEstDansForme(const CercleEnglobant& cercle) const;

    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;
        
	virtual bool calculerCollision(const RectangleEnglobant& rectangle, glm::dvec3& normale) const;
	virtual bool calculerCollision(const CercleEnglobant& rectangle, glm::dvec3& normale) const;

    virtual void afficher(const glm::dvec3& origine) const;
    virtual void afficher() const;

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
