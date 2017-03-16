///////////////////////////////////////////////////////////////////////////
/// @file EtatMiseAEchelle.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_MISE_A_ECHELLE_H
#define ETAT_MISE_A_ECHELLE_H

#include "OnlineTool.h"
#include "VisiteurVerificationQuad.h"
#include "VisiteurMiseAEchelle.h"

///////////////////////////////////////////////////////////////////////////
/// @class EtatMiseAEchelle
/// @brief État représentant la mise à échelle d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatMiseAEchelle : public OnlineTool
{
public:
	EtatMiseAEchelle(client_network::MapSession* mapSession);
	virtual ~EtatMiseAEchelle();
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);

protected:
	virtual void reinitialiser();

private:
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	std::unique_ptr<VisiteurMiseAEchelle> visiteurMiseAEchelle_{ nullptr };

	double dernierePositionY_{ 0.0 };
	double positionInitialeY_{ 0.0 };
	double surplusMouvement_{ 0.0 };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
