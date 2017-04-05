
include_directories(
    ui/enum)

# Ajout de la librairie utilitaire
add_subdirectory(util)

# Ajout de la librairie model
add_subdirectory(model)

# Ajout du projet C# pour l'interface graphique
include_external_msproject(ui 
    ${CMAKE_SOURCE_DIR}/src/app/heavy-client/ui/ui.csproj)

set_property(TARGET ui PROPERTY FOLDER "app/heavy-client")