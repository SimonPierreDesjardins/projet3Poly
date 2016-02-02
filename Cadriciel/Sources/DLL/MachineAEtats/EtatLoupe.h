#ifndef ETAT_LUPE_H
#define ETAT_LUPE_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"


class EtatLoupe : public EtatAbstrait
{
public:
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);

	virtual void gererMouvementSouris(const int & x, const int& y);

private:
	glm::ivec2 anchor;
	glm::ivec2 currentPosition;
	bool rectum{ false };
};

#endif