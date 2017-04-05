////////////////////////////////////////////////
/// @file   Authentification.cs
/// @author Frédéric Grégoire
/// @date   2016-03-06
///
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace AuthenticationAction
{
    public
#endif

    /// Enum les actions d'authentification
    enum Authentication
    {
        CREATION_SUCCESS,
        AUTEHNTIFICATION_SUCCESS,
        NEW_ALREADY_EXIST,
        EXISTING_FAIL,
        EXISTING_ALREADY_CONNECTED
    };

#if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
