#ifndef ETAT_ABSTRAIT_H
#define ETAT_ABSTRAIT_H


class EtatAbstrait
{
public:
	EtatAbstrait();
	virtual ~EtatAbstrait();
	virtual void effectuerOperation() = 0;
};








#endif