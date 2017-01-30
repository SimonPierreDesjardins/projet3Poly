
include_external_msproject(prototype-ui 
    ${CMAKE_SOURCE_DIR}/src/prototype/heavy-client/ui/ui.csproj)

set_property(TARGET prototype-ui PROPERTY FOLDER "prototype/heavy-client")