///////////////////////////////////////////////////////////////////////////
/// @file ModeConfigure.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeConfigure.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeConfigure::ModeConfigure()
///
/// Constructeur par d�faut pour le mode configure
///
////////////////////////////////////////////////////////////////////////
ModeConfigure::ModeConfigure()
{
	typeMode_ = CONFIGURE;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeConfigure::~ModeConfigure()
///
/// Destructeur de la classe ModeConfigure
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeConfigure::~ModeConfigure()
{
}

void ModeConfigure::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////