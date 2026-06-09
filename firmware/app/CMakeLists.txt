# ------------------------------------------------------------------------------
# Firmware entry point
# ------------------------------------------------------------------------------

add_executable(firmware

    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f0xx_it.c
)

target_include_directories(firmware PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# ------------------------------------------------------------------------------
# Output directory (ELF dans build/)
# ------------------------------------------------------------------------------

set_target_properties(firmware PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_NAME "firmware"
    PREFIX ""
    SUFFIX ".elf"
)

# ------------------------------------------------------------------------------
# Link firmware modules
# ------------------------------------------------------------------------------

target_link_libraries(firmware PRIVATE

    platform_stm32f072
    drivers
    core
    services
)

# ------------------------------------------------------------------------------
# Disable heavy C++ runtime features
# ------------------------------------------------------------------------------

target_compile_options(firmware PRIVATE

    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)

# ------------------------------------------------------------------------------
# Post-build actions
# Generate .bin / .hex and print firmware size
# ------------------------------------------------------------------------------

add_custom_command(TARGET firmware POST_BUILD

    # BIN
    COMMAND ${CMAKE_OBJCOPY}
        -O binary
        $<TARGET_FILE:firmware>
        ${CMAKE_BINARY_DIR}/firmware.bin

    # HEX
    COMMAND ${CMAKE_OBJCOPY}
        -O ihex
        $<TARGET_FILE:firmware>
        ${CMAKE_BINARY_DIR}/firmware.hex

    # ASM
    COMMAND ${CMAKE_OBJDUMP}
        -d -S -C -l
        $<TARGET_FILE:firmware>
        > ${CMAKE_BINARY_DIR}/firmware.asm

    # SIZE
    COMMAND ${CMAKE_SIZE}
        $<TARGET_FILE:firmware>
)