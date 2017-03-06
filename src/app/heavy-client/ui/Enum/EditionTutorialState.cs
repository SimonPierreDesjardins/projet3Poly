////////////////////////////////////////////////
/// @file   EditionTutorial.cs
/// @author Frédéric Grégoire
/// @date   2016-03-06
///
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace EditionTutorial
{
    public
    #endif

    /// Enum représentant le mode dans lequel le programme se trouve
    enum State
    {
        INTRODUCTION,
        SELECT_POST_TOOL,
        CREATING_POST,
        SELECT_TOOL,
        SELECTING_POST,
        SELECT_SCALE_TOOL,
        APPLYING_SCALE,
        SELECT_MOVE_TOOL,
        APPLYING_MOVE,
        SELECT_DUPLICATE_TOOL,
        APPLYING_DUPLICATE,
        CONCLUSION
    };

    #if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////