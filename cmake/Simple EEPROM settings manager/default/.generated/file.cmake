# The following variables contains the files used by the different stages of the build process.
set(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)
set(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_compile "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c")
set_source_files_properties(${Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Simple_EEPROM_settings_manager_default_default_XC8_FILE_TYPE_link)

# The (internal) path to the resulting build image.
set(Simple_EEPROM_settings_manager_default_internal_image_name "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/Simple EEPROM settings manager/default/default.elf")

# The name of the resulting image, including namespace for configuration.
set(Simple_EEPROM_settings_manager_default_image_name "Simple_EEPROM_settings_manager_default_default.elf")

# The name of the image, excluding the namespace for configuration.
set(Simple_EEPROM_settings_manager_default_original_image_name "default.elf")

# The output directory of the final image.
set(Simple_EEPROM_settings_manager_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/Simple EEPROM settings manager")
