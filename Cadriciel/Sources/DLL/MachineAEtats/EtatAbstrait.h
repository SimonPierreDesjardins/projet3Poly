///////////////////////////////////////////////////////////////////////////
/// @file EtatAbstrait.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

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
	virtual void gererMouvementSouris(const int & x, const int& y);



	virtual void effectuerOperation() = 0;


};








#endif