set(TEST_SRC
	rgw/InterfaceNative.cpp
	rgw/InterfaceNative.h
	rgw/Client.h)

source_group("test" FILES ${TEST_SRC})

add_library(prototype-model
	SHARED
	${TEST_SRC})
	
	set_property(TARGET prototype-model PROPERTY FOLDER "prototype/heavy-client")