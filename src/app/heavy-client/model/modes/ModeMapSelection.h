///////////////////////////////////////////////////////////////////////////
// @file ModeMapSelection.h
// @author Olivier St-Amour
// @date 2017-03-07
// @version 1.0
//
// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_MAP_SELECTION_H
#define MODE_MAP_SELECTION_H

#include "ModeAbstrait.h"

#include "EventHandler.h"

//////////////////////////////////////////////////////////////////////////
// @class ModeMapSelection
// @brief Classe qui repr�sente le mode de s�lection de map
//
//        Cette classe s'occupe de g�rer la logique lors de la s�lection de cartes
//
// @author Simon-Pierre Desjardins
// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeMapSelection : public ModeAbstrait
{
public:
	//Constructeur par d�faut
	ModeMapSelection() = default;

	//Destructeur
	virtual ~ModeMapSelection() = default;
};

#endif // MODE_CONFIGURE_H

///////////////////////////////////////////////////////////////////////////////
// @}
///////////////////////////////////////////////////////////////////////////////
