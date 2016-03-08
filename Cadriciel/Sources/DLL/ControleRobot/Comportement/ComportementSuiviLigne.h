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
#include <ctime>
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
	ComportementSuiviLigne(ControleRobot* controleRobot);
	virtual ~ComportementSuiviLigne();

	void initialiser();

	void mettreAJour();

private:

	time_t heurePerteLigne_;

	// Flag dictant si le suiveur de ligne tente de brièvement retrouver sa ligne
	bool rechercheLigne{ true };
};

#endif COMPORTEMENT_SUIVI_LIGNE

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////