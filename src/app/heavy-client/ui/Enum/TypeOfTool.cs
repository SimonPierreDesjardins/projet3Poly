////////////////////////////////////////////////
/// @file   VehiculePiece.cs
/// @author Frédéric Grégoire
/// @date   2016-03-01
///
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace TypeOfTool
{
    public
    #endif

    /// Enum représentant la piece d'un véhicule
    enum Tool
        {
            NONE,
            CREATION_LIGNE,
            CREATION_MUR,
            CREATION_POTEAU,
            DEPLACEMENT,
            DUPLICATION,
            LOUPE,
            MISE_A_ECHELLE,
            ROTATION,
            SELECTION
        };

    #if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////