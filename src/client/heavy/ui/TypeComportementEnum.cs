////////////////////////////////////////////////
/// @file   TypeCommandeEnum.cs
/// @author Philippe Marcotte
/// @date   2016-03-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace TypeComportementEnum
{
    public
#endif

/// Enum représentant les comportements que le robot peut adopter
enum TypeComportement {
	DEFAUT,
	SUIVIDELIGNE,
	BALAYAGE180,
	DEVIATIONVERSLAGAUCHE,
	DEVIATIONVERSLADROITE,
	EVITEMENTPARLAGAUCHE,
	EVITEMENTPARLADROITE
};

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////