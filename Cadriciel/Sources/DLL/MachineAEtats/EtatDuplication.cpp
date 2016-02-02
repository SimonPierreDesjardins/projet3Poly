///////////////////////////////////////////////////////////////////////////
/// @file EtatDuplication.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatDuplication.h"
#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

EtatDuplication::EtatDuplication()
{
	visiteur_ = std::make_unique<VisiteurDuplication>();
}

EtatDuplication::~EtatDuplication()
{

}

void EtatDuplication::gererEstSurTableConcret(bool positionEstSurTable)
{

}



void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
}