///////////////////////////////////////////////////////////////////////////////
/// @file cercleenglobant.h
/// @author olivier st-amour
/// @date 2016-03-08
/// @version 2.3
///
/// @addtogroup inf2990 inf2990
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

    void mettreAJour(const glm::dvec3& positionCentre, const double& rayon);

    virtual bool calculerEstDansLimites(const double& xMin, const double& xMax,
                                        const double& yMin, const double& yMax) const;

    virtual bool calculerEstDansForme(const glm::dvec3& point) const;

    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;
        
    virtual glm::dvec3 calculerNormaleCollision(const RectangleEnglobant& rectangle) const;
    virtual glm::dvec3 calculerNormaleCollision(const CercleEnglobant& cercle) const;
    virtual glm::dvec3 calculerNormaleCollision(const glm::dvec3& point) const;

    virtual void afficher(const glm::dvec3& origine) const;
    virtual void afficher() const;

private:
    double rayon_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void CercleEnglobant::assignerRayon(const double& rayon)
///
/// Cette fonction assigne un rayon au cercle
///
/// @param[in] rayon: le rayon du cercle en double.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void CercleEnglobant::assignerRayon(const double& rayon)
{
    rayon_ = rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double CercleEnglobant::obtenirRayon() const
///
/// Cette fonction retourne le rayon du cercle.
///
/// @param[in] Aucun.
///
/// @return rayon du cercle.
///
////////////////////////////////////////////////////////////////////////
inline double CercleEnglobant::obtenirRayon() const
{
    return rayon_;
}

#endif // CERCLE_ENGLOBANT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
