///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_DEVIATION
#define COMPORTEMENT_DEVIATION

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementDeviation
/// @brief Classe qui implémente le comportement de deviation du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementDeviation : public ComportementAbstrait
{
public:
	ComportementDeviation();
	ComportementDeviation(TypeComportement prochainComportement);
	ComportementDeviation(const rapidjson::Value& comportementJSON);
	ComportementDeviation(TypeComportement prochainComportement, double angleMax);
	virtual ~ComportementDeviation();

	void initialiser();

	void mettreAJour();

	void setAngleMaxRotation(double angle);

	inline double obtenirMaxAngle();

	virtual void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	virtual void fromJson(const rapidjson::Value& comportementJSON);

private:
	// La variation relative d'angle maximale que la déviation doit atteindre
	double maxAngle_;

	// L'angle que doit atteindre le robot pour que la déviation soit considérée accomplie.
	double angleCible_;

	// Définit si la déviation doit se faire vers la gauche ou bien vers la droite
	bool gauche;

	// Flag dictant au comportement d'ignorer la ligne
	bool ignorerLigne_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ComportementDeviation::obtenirMaxAngle()
///
/// Retourne l'angle maximal à atteindre lors de la déviation
///
/// @return double L'angle maximal à atteindre.
///
////////////////////////////////////////////////////////////////////////
inline double ComportementDeviation::obtenirMaxAngle(){
	return maxAngle_;
}

#endif // COMPORTEMENT_DEVIATION

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
