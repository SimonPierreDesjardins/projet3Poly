# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

add_executable(server
ChatClientContainer.cpp
ServerStarter.cpp
)

target_link_libraries(server networkUtils)

set_property(TARGET server PROPERTY FOLDER "prototype/server")

target_compile_definitions(server
PRIVATE
)