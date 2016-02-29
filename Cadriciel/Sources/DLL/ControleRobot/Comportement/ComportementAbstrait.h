///////////////////////////////////////////////////////////////////////////////
/// @file ComportementAbstrait.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_ABSTRAIT
#define COMPORTEMENT_ABSTRAIT

#include <memory>
#include "rapidjson\writer.h"
#include "rapidjson\document.h"
#include "./../../Enum/TypeComportementEnum.cs"

namespace rapidjson {
	class FileWriteStream;
}

///////////////////////////////////////////////////////////////////////////
/// @class ComportementAbstrait
/// @brief Classe de base qui définit le comportement du robot.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les comportements que le robot peut adopter. 
///		   
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementAbstrait
{
public:
	ComportementAbstrait();
	ComportementAbstrait(TypeComportement prochainComportement);
	ComportementAbstrait(const rapidjson::Value& comportementJSON);
	virtual ~ComportementAbstrait();

	// Assure la reinitialisation du comportement avant son execution
	virtual void initialiser() = 0;

	// Traite l'execution du comportement
	virtual void mettreAJour() = 0;

	TypeComportement obtenirComportementSuivant();

	void assignerComportementSuivant(TypeComportement prochainComportement);

	virtual void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

protected:
	virtual void fromJson(const rapidjson::Value& comportementJSON);

private:
	// Le comportement a adopter une fois les conditions de fin de ce comportement sont atteintes.
	TypeComportement comportementSuivant_;
};

#endif // COMPORTEMENT_ABSTRAIT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////