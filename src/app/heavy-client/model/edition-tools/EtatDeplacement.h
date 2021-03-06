///////////////////////////////////////////////////////////////////////////
/// @file EtatDeplacement.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_DEPLACEMENT_H
#define ETAT_DEPLACEMENT_H

#include "OnlineTool.h"
#include "VisiteurTypes.h"

///////////////////////////////////////////////////////////////////////////
/// @class EtatDeplacement
/// @brief �tat repr�sentant le d�placement d'un objet
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatDeplacement : public OnlineTool
{
public:
	EtatDeplacement(client_network::ClientMapSession* mapSession);
	virtual ~EtatDeplacement();
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);

protected:
	virtual void reinitialiser();

private:
	VisiteurVerificationQuad visiteurVerificationQuad_;
	VisiteurDeplacement visiteurDeplacement_;

	glm::dvec3 dernierePositionVirtuelle_{ glm::dvec3() };
	glm::dvec3 positionVirtuelleInitiale_{ glm::dvec3() };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
