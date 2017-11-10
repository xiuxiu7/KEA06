#this is required
SET(CMAKE_SYSTEM_NAME Generic)

#bypass toolchain compiler check
INCLUDE(CMakeForceCompiler) 
CMAKE_FORCE_C_COMPILER(gcc GNU)
CMAKE_FORCE_CXX_COMPILER(g++ GNU)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH $ENV{KEA_TOOLCHAIN})

# specify the cross compiler
SET(CMAKE_C_COMPILER "${CMAKE_FIND_ROOT_PATH}/bin/arm-none-eabi-gcc")
SET(CMAKE_ASM_COMPILER "${CMAKE_FIND_ROOT_PATH}/bin/arm-none-eabi-gcc")

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
