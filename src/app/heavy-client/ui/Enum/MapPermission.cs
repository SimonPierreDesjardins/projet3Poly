////////////////////////////////////////////////
/// @file   MapPermission.cs
/// @author Frederic Gregoire
/// @date   2016-04-05
///
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace MapPermission
{
    public
#endif

/// Enum représentant le changement de confidentiallite dune map en ligne
enum Permission
    {
        CHANGED_PUBLIC,
        CHANGED_PRIVATE,
        CHANGED_DENIED
    };

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////