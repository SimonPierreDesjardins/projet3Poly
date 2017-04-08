////////////////////////////////////////////////
/// @file   MapJoin.cs
/// @author Frederic Gregoire
/// @date   2016-04-05
///
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace MapJoin
{
    public
#endif

/// Enum représentant le changement de confidentiallite dune map en ligne
enum Response
    {
        MAP_JOINED,
        MAP_FULL,
        MAP_WRONG_PASSWORD
    };

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////