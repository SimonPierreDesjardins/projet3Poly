///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDefaut.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_DEFAUT
#define COMPORTEMENT_DEFAUT

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementDefaut
/// @brief Classe qui impl�mente le comportement par d�faut du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementDefaut : public ComportementAbstrait
{
public:
	ComportementDefaut();
	ComportementDefaut(TypeComportement prochainComportement);
	ComportementDefaut(const rapidjson::Value& comportementJSON);
	virtual ~ComportementDefaut();

	void initialiser();

	void mettreAJour();
};

#endif // COMPORTEMENT_DEFAUT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
