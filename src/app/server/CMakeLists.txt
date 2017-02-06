# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/src/app/server/include
)

add_library(server 
include/Networking.h
include/Connection.h
include/ConnectionResolver.hpp
include/NetworkLogger.h
include/ServerListener.hpp
Connection.cpp
ConnectionResolver.cpp
NetworkLogger.cpp
ServerListener.cpp
)

set_property(TARGET server PROPERTY FOLDER "app/server")


target_compile_definitions(server
PRIVATE
ASIO_STANDALONE
)