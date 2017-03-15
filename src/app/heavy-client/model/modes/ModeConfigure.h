///////////////////////////////////////////////////////////////////////////
/// @file ModeConfigure.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_CONFIGURE_H
#define MODE_CONFIGURE_H

#include "ModeAbstrait.h"
#include <memory>
#include "glm\glm.hpp"
#include "CommandeRobot.h"

//////////////////////////////////////////////////////////////////////////
/// @class ModeConfigure
/// @brief Classe qui repr�sente le mode configure de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode configure
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeConfigure : public ModeAbstrait
{
public:

	//Constructeur par d�faut
	ModeConfigure();

	//Destructeur
	virtual ~ModeConfigure();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	
};


#endif /// MODE_CONFIGURE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////