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
namespace TypeCommandeEnum
{
    public
#endif

/// Enum représentant les types de commande pouvant être envoyer au robot
enum TypeCommande{
    INVERSER_MODE_CONTROLE,
    AVANCER,
    RECULER,
    ROTATION_GAUCHE,
    ROTATION_DROITE,
    DEVIATION_GAUCHE,
    DEVIATION_DROITE,
    ARRETER
};

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////