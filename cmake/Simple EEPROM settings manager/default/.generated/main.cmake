include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Simple_EEPROM_settings_manager_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemble)
add_library(Simple_EEPROM_settings_manager_default_default_XC8_assemble OBJECT ${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemble})
    Simple_EEPROM_settings_manager_default_default_XC8_assemble_rule(Simple_EEPROM_settings_manager_default_default_XC8_assemble)
    list(APPEND Simple_EEPROM_settings_manager_default_library_list "$<TARGET_OBJECTS:Simple_EEPROM_settings_manager_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(Simple_EEPROM_settings_manager_default_default_XC8_assemblePreprocess OBJECT ${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemblePreprocess})
    Simple_EEPROM_settings_manager_default_default_XC8_assemblePreprocess_rule(Simple_EEPROM_settings_manager_default_default_XC8_assemblePreprocess)
    list(APPEND Simple_EEPROM_settings_manager_default_library_list "$<TARGET_OBJECTS:Simple_EEPROM_settings_manager_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_compile)
add_library(Simple_EEPROM_settings_manager_default_default_XC8_compile OBJECT ${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_compile})
    Simple_EEPROM_settings_manager_default_default_XC8_compile_rule(Simple_EEPROM_settings_manager_default_default_XC8_compile)
    list(APPEND Simple_EEPROM_settings_manager_default_library_list "$<TARGET_OBJECTS:Simple_EEPROM_settings_manager_default_default_XC8_compile>")
endif()

add_executable(${Simple_EEPROM_settings_manager_default_image_name} ${Simple_EEPROM_settings_manager_default_library_list})

target_link_libraries(${Simple_EEPROM_settings_manager_default_image_name} PRIVATE ${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
Simple_EEPROM_settings_manager_default_link_rule(${Simple_EEPROM_settings_manager_default_image_name})


# Post build target to copy built file to the output directory.
add_custom_command(TARGET ${Simple_EEPROM_settings_manager_default_image_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${Simple_EEPROM_settings_manager_default_output_dir}
                    COMMAND ${CMAKE_COMMAND} -E copy ${Simple_EEPROM_settings_manager_default_image_name} ${Simple_EEPROM_settings_manager_default_output_dir}/${Simple_EEPROM_settings_manager_default_original_image_name}
                    BYPRODUCTS ${Simple_EEPROM_settings_manager_default_output_dir}/${Simple_EEPROM_settings_manager_default_original_image_name})
