///////////////////////////////////////////////////////////////////////////////
/// @file ComporterEvitement.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_EVITEMENT
#define COMPORTEMENT_EVITEMENT

#include "ComportementAbstrait.h"
#include <ctime>

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui implémente le comportement d'évitement du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementEvitement : public ComportementAbstrait
{
public:
	ComportementEvitement(ControleRobot* noeudRobot);
	virtual ~ComportementEvitement();

	void initialiser();

	void mettreAJour();

	void setAngleMaxRotation(double angle);

	void setTempsMaxReculons(double temps);

private:
	// Flag informant le comportement qu'il s'agit d'un évitement pivot gauche
	bool gauche;

	// Flag dictant au comportement d'ignorer les lignes rencontrées
	bool ignorerLigne_;

	time_t startTime_;

	// Le nombre de secondes que le comportement force le reculons
	double maxTemps_;

	// L'angle relative a atteindre pour que le pivot soit complet
	double maxAngle_;

	// L'angle absolue a atteindre pour changement de comportment
	double angleCible_;
};

#endif // COMPORTEMENT_EVITEMENT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////