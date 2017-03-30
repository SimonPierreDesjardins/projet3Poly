////////////////////////////////////////////////
/// @file   ConfigureControlEnum.cs
/// @author Philippe Marcotte
/// @date   2016-03-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#if !__LINE__

/// Permet de partager cet enum entre le C# et le C++
namespace ConfigureControlEnum
{
    public
    #endif

    ///Enum représentant chaque composante de la fenêtre Configure que l'on veut pouvoir modifier à partir du modèle
    enum ConfigureControl
        {
            PROFIL_CB,
            AVANCER_TXT_BOX,
            RECULER_TXT_BOX,
            ROTATION_GAUCHE_TXT_BOX,
            ROTATION_DROITE_TXT_BOX,
            MODE_TXT_BOX,
            SUIVI_LIGNE_CB,
            BALAYAGE_CB,
            DEVIATION_GAUCHE_CB,
            DEVIATION_GAUCHE_TXT_BOX,
            DEVIATION_DROITE_CB,
            DEVIATION_DROITE_TXT_BOX,
            EVITEMENT_GAUCHE_CB,
            EVITEMENT_GAUCHE_ANGLE_TXT_BOX,
            EVITEMENT_GAUCHE_DUREE_TXT_BOX,
            EVITEMENT_DROITE_CB,
            EVITEMENT_DROITE_ANGLE_TXT_BOX,
            EVITEMENT_DROITE_DUREE_TXT_BOX,
            ZONE_DANGER_DROIT_CB,
            ZONE_DANGER_CENTRE_CB,
            ZONE_DANGER_GAUCHE_CB,
            ZONE_SECURITAIRE_DROIT_CB,
            ZONE_SECURITAIRE_CENTRE_CB,
            ZONE_SECURITAIRE_GAUCHE_CB,
            LARGEUR_DANGER_DROIT_TXT_BOX,
            LARGEUR_DANGER_CENTRE_TXT_BOX,
            LARGEUR_DANGER_GAUCHE_TXT_BOX,
            LARGEUR_SECURITAIRE_DROIT_TXT_BOX,
            LARGEUR_SECURITAIRE_CENTRE_TXT_BOX,
            LARGEUR_SECURITAIRE_GAUCHE_TXT_BOX,
            CAPTEUR_DIST_DROIT_CB,
            CAPTEUR_DIST_CENTRE_CB,
            CAPTEUR_DIST_GAUCHE_CB,
            SUIVEUR_LIGNE_CB,
            DEBUG_OPTIONS_CB,
            DEBUG_COMPORTEMENTS_CB,
            DEBUG_ECLAIRAGE_CB,
            DEBUG_CAPTEURS_CB
        };

    #if !__LINE__
}
#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////