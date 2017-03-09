
set(INTERFACE_SRC
    Interface.h
    Interface.cpp
)
source_group("." FILES ${INTERFACE_SRC})

add_library(ui-model-interface SHARED
    ${INTERFACE_SRC}
)

set_property(TARGET ui-model-interface PROPERTY FOLDER "app/heavy-client")
set_property(TARGET ui-model-interface PROPERTY COMPILE_FLAGS "/clr")