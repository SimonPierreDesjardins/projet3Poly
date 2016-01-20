#ifndef ETAT_ABSTRAIT_H
#define ETAT_ABSTRAIT_H


class EtatAbstrait
{
public:
	EtatAbstrait();
	virtual ~EtatAbstrait();

	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);

	virtual void effectuerOperation() = 0;
};








#endif