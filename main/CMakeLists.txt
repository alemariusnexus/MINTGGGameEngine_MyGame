idf_component_register(
    SRCS
		audio.cpp
		engine.cpp
		main.cpp
    INCLUDE_DIRS
    PRIV_INCLUDE_DIRS
    REQUIRES
        MINTGGGameEngine
    PRIV_REQUIRES
)

target_compile_options(${COMPONENT_LIB} PRIVATE
    -Wno-missing-field-initializers
    )

spiffs_create_partition_image(spiffs ../spiffs FLASH_IN_PROJECT)
