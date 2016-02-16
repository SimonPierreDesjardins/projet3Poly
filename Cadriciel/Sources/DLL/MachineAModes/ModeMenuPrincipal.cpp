///////////////////////////////////////////////////////////////////////////
/// @file ModeMenuPrincipal.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeMenuPrincipal.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ModeMenuPrincipal::ModeMenuPrincipal()
///
/// Constructeur par d�faut pour le mode du menu principal
///
////////////////////////////////////////////////////////////////////////

ModeMenuPrincipal::ModeMenuPrincipal()
{
	FacadeModele::obtenirInstance()->assignerEtat(SELECTION);
	typeMode_ = MENU_PRINCIPAL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeMenuPrincipal::~ModeMenuPrincipal()
///
/// Destructeur de la classe ModeMenuPrincipal
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////

ModeMenuPrincipal::~ModeMenuPrincipal()
{
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////