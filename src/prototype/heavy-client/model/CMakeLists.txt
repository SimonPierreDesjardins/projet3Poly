set(TEST_SRC
	rgw/InterfaceNative.cpp
	rgw/InterfaceNative.h
	rgw/Client.h
	rgw/Client.cpp)

source_group("test" FILES ${TEST_SRC})

include_directories(
	${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
	${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

add_library(prototype-model
	SHARED
	${TEST_SRC})
	
	set_property(TARGET prototype-model PROPERTY FOLDER "prototype/heavy-client")

target_link_libraries(prototype-model
		networkUtils)