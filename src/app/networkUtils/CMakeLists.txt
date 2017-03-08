# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

add_library(networkUtils
include/Networking.h
include/Connection.h
include/ConnectionResolver.hpp
include/NetworkLogger.h
include/ServerListener.hpp
include/NetworkObjects.h
Connection.cpp
ConnectionResolver.cpp
NetworkLogger.cpp
ServerListener.cpp
NetworkObjects.cpp
)

set_property(TARGET networkUtils PROPERTY FOLDER "app/network")


target_compile_definitions(networkUtils
    PRIVATE
    ASIO_STANDALONE
    _WIN32_WINNT=0x0501
    _WINSOCK_DEPRECATED_NO_WARNINGS
)