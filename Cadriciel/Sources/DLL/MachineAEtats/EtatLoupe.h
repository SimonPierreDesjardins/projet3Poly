#ifndef ETAT_LOUPE_H
#define ETAT_LOUPE_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"


class EtatLoupe : public EtatAbstrait
{
public:
	virtual void gererClicGaucheRelache(const int& x, const int& y);

	virtual void gererMouvementSouris(const int & x, const int& y);
private:
	bool dessineRectangle{ false };
};

#endif