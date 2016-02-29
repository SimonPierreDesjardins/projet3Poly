///////////////////////////////////////////////////////////////////////////////
/// @file ComporterSuiviLigne.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_SUIVI_LIGNE
#define COMPORETMENT_SUIVI_LIGNE

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui implémente le comportement de suivi de ligne du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementSuiviLigne : public ComportementAbstrait
{
public:
	ComportementSuiviLigne();
	ComportementSuiviLigne(TypeComportement prochainComportement);
	ComportementSuiviLigne(const rapidjson::Value& comportementJSON);
	virtual ~ComportementSuiviLigne();

	void initialiser();

	void mettreAJour();
};

#endif // COMPORTEMENT_SUIVI_LIGNE

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////