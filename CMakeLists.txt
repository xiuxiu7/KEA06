cmake_minimum_required (VERSION 2.8)
# 项目信息
project (nioday_kea06_app)

message("CMake system name is ${CMAKE_SYSTEM_NAME}")

enable_language(ASM)


SET(CMAKE_LINKER "$ENV{KEA_TOOLCHAIN}/bin/arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "$ENV{KEA_TOOLCHAIN}/bin/arm-none-eabi-objcopy")
SET(CMAKE_OBJDUMP "$ENV{KEA_TOOLCHAIN}/bin/arm-none-eabi-objdump")
SET(CMAKE_SIZE "$ENV{KEA_TOOLCHAIN}/bin/arm-none-eabi-size")

file(GLOB_RECURSE SRCS "${PROJECT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE INCS "${PROJECT_SOURCE_DIR}/src/*.h")


SET(SRCS "${SRCS};${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/core/M0/boot.S")
SET(SRCS "${SRCS};${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/core/M0/dispatch.S")

SET(INCS "${INCS};${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/types.inc")
SET(INCS "${INCS};${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/core/M0/psp_prv.inc")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE)
include_directories(${PROJECT_SOURCE_DIR}/src/Static_Code)
include_directories(${PROJECT_SOURCE_DIR}/src/Sources)
include_directories(${PROJECT_SOURCE_DIR}/src/Generated_Code)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/config)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/include)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/kernel)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/core)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/compiler)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/core/M0)
include_directories(${PROJECT_SOURCE_DIR}/src/MQXLITE/psp/cortex_m/compiler/cwgcc)
include_directories(${PROJECT_SOURCE_DIR}/src/Static_Code/PDD)
include_directories(${PROJECT_SOURCE_DIR}/src/Static_Code/System)
include_directories(${PROJECT_SOURCE_DIR}/src/Static_Code/IO_Map)
include_directories(${PROJECT_SOURCE_DIR}/src/Sources/task)
include_directories(${PROJECT_SOURCE_DIR}/src/Sources/dev)

SET(MCU_FLAGS "-march=armv6-m -mcpu=cortex-m0plus -mthumb")

SET(LINK_SCRIPT "${PROJECT_SOURCE_DIR}/src/ProcessorExpert.ld")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -fno-builtin")

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m0plus  -L -g3  -O0 -ffunction-sections -fdata-sections -fmessage-length=0 -fsigned-char -Wl,--gc-sections,-T${LINK_SCRIPT},-Map,${PROJECT_NAME}.map  -specs=nano.specs -specs=nosys.specs -Xlinker")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -mthumb -mcpu=cortex-m0plus -fsigned-char  -O0 -g3 -W -fmessage-length=0 -ffunction-sections -fdata-sections")

SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}  -mthumb -mcpu=cortex-m0plus -fsigned-char  -O0 -g3 -W -fmessage-length=0 -ffunction-sections -fdata-sections")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRCS} ${INCS})

target_link_libraries(${PROJECT_NAME} c gcc m)

set(BIN_FILE ${PROJECT_NAME}.bin)
add_custom_command(OUTPUT ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -R .uinit_ram -O binary ${PROJECT_NAME} ${BIN_FILE}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Generate APP BIN file")

set(HEX_FILE ${PROJECT_NAME}.hex)
add_custom_command(OUTPUT ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -R .uinit_ram -O ihex ${PROJECT_NAME} ${HEX_FILE}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Generate APP HEX file")

# link any custom command to target ALL
add_custom_target(${PROJECT_NAME}_bin ALL
    DEPENDS ${BIN_FILE}
    DEPENDS ${HEX_FILE})


# flash target
add_custom_target(flash
    COMMAND JLinkExe -commandfile ${PROJECT_SOURCE_DIR}/tools/jlink_flash_cmd_all
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

# flash target
add_custom_target(flash_erase
    COMMAND JLinkExe -commandfile ${PROJECT_SOURCE_DIR}/tools/jlink_flash_cmd_erase
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})