////////////////////////////////////////////////
/// @file   ModeEnum.cs
/// @author Philippe Marcotte
/// @date   2016-03-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace ModeEnum
{
    public
#endif

/// Enum représentant le mode dans lequel le programme se trouve
enum Mode
    {
        MENU_PRINCIPAL,
        SIMULATION,
        EDITION,
        CONFIGURE,
        TEST,
        PERSONALIZE,
        TUTORIAL_EDITION,
        PIECES
    };

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////