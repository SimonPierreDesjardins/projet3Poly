# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
)

add_library(server 
Connection.cpp
Connection.h
ConnectionResolver.cpp
ConnectionResolver.hpp
NetworkLogger.h
NetworkLogger.cpp
ServerListener.cpp
ServerListener.hpp
)

set_property(TARGET server PROPERTY FOLDER "app/server")


target_compile_definitions(server
PRIVATE
ASIO_STANDALONE
)