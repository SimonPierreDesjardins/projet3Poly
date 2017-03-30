////////////////////////////////////////////////
/// @file   EditionTutorial.cs
/// @author Frédéric Grégoire
/// @date   2016-03-06
///
////////////////////////////////////////////////
#if !__EDITION_TUTORIAL__

/// Permet de partager cet enum entre le C# et le C++
namespace EditionTutorial
{
    public
    #endif

    /// Enum représentant l'état du tutoriel édition dans lequel le programme se trouve
    enum State
    {
        INTRODUCTION,
        SELECT_POST_TOOL,
        CREATING_POST,
        SELECT_LINE_TOOL,
        CREATING_LINE,
        SELECT_TELEPORTOR,
        CREATING_TELEPORTOR,
        SELECT_WALL_TOOL,
        CREATING_WALL,
        SELECT_TOOL,
        SELECTING_OBJECT,
        SELECT_SCALE_TOOL,
        APPLYING_SCALE,
        SELECT_MOVE_TOOL,
        APPLYING_MOVE,
        SELECT_ROTATION_TOOL,
        APPLYING_ROTATION,
        SELECT_DUPLICATE_TOOL,
        APPLYING_DUPLICATE,
        DELETE_TOOL,
        CHANGE_VIEW,
        CONCLUSION
    };

#if !__EDITION_TUTORIAL__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////