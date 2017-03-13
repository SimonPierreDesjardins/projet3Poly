///////////////////////////////////////////////////////////////////////////
/// @file EtatLoupe.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_LOUPE_H
#define ETAT_LOUPE_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"

///////////////////////////////////////////////////////////////////////////
/// @class EtatLoupe
/// @brief �tat repr�sentant le zoom sur une partie de l'�cran
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatLoupe : public EtatAbstrait
{
public:
	EtatLoupe();
	virtual void gererClicGaucheRelache(const int& x, const int& y);

	virtual void gererMouvementSouris(const int & x, const int& y);
private:
	bool dessineRectangle{ false };
};

#endif
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////