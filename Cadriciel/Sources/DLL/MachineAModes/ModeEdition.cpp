///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeEdition.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

ModeEdition::ModeEdition()
{
	FacadeModele::obtenirInstance()->assignerEtat(SELECTION);
	visiteurSuppression_ = std::make_unique<VisiteurSuppression>();
}

ModeEdition::~ModeEdition()
{

}

void ModeEdition::gererTouchePlus()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
}

void ModeEdition::gererToucheMoins()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
}

void ModeEdition::gererToucheEchappe()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheEchappe();
}

void ModeEdition::gererToucheC()
{
	FacadeModele::obtenirInstance()->assignerEtat(DUPLICATION);
}

void ModeEdition::gererToucheD()
{
	FacadeModele::obtenirInstance()->assignerEtat(DEPLACEMENT);
}

void ModeEdition::gererToucheE()
{
	FacadeModele::obtenirInstance()->assignerEtat(MISE_A_ECHELLE);
}

void ModeEdition::gererToucheR()
{
	FacadeModele::obtenirInstance()->assignerEtat(ROTATION);
}

void ModeEdition::gererToucheS()
{
	FacadeModele::obtenirInstance()->assignerEtat(SELECTION);
}

void ModeEdition::gererToucheT()
{
	FacadeModele::obtenirInstance()->assignerMode(TEST);
}

void ModeEdition::gererToucheZ()
{
	//FacadeModele::obtenirInstance()->assignerEtat(ZOOM);
}

void ModeEdition::gererToucheCTRLavecS()
{

}

void ModeEdition::gererToucheCTRLavecN()
{

}

void ModeEdition::gererToucheCTRLavecO()
{

}

void ModeEdition::gererTouche1()
{

}

void ModeEdition::gererTouche2()
{

}

void ModeEdition::gererFlecheGauche()
{
	std::cout << "La fleche de gauche est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
}

void ModeEdition::gererFlecheBas()
{
	std::cout << "La fleche du bas est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
}

void ModeEdition::gererFlecheHaut()
{
	std::cout << "La fleche du haut est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
}

void ModeEdition::gererFlecheDroit()
{
	std::cout << "La fleche de droite est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
}

void ModeEdition::gererToucheControlEnfoncee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlEnfoncee();
}

void ModeEdition::gererToucheControlRelachee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlRelachee();
}

void ModeEdition::gererToucheSupprimer()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteurSuppression_.get());
}

