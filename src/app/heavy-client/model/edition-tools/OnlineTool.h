///////////////////////////////////////////////////////////////////////////
/// @file OnlineTool.h
/// @author 
/// @date 2017-03-13
/// @version 1.0
///
/// @addtogroup inf3900 INF3900
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ONLINE_TOOL_H
#define ONLINE_TOOL_H

namespace client_network
{
	class ClientMapSession;
}

#include "EtatAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class EtatAbstrait
/// @brief Classe de base pour chaque état
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les états pouvant être présent dans le modèle
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class OnlineTool : public EtatAbstrait
{
public:
	OnlineTool(client_network::ClientMapSession* mapSession);
	virtual ~OnlineTool() = 0;

protected:
	client_network::ClientMapSession* mapSession_;

	OnlineTool() = delete;
};

#endif /// ONLINE_TOOL_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
