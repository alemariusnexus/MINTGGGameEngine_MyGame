idf_component_register(
    SRCS
		audio.cpp
		engine.cpp
		main.cpp
    INCLUDE_DIRS
    PRIV_INCLUDE_DIRS
    REQUIRES
		driver
        MINTGGGameEngine
    PRIV_REQUIRES
)

spiffs_create_partition_image(spiffs ../spiffs FLASH_IN_PROJECT)
