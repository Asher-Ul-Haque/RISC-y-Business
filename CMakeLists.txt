cmake_minimum_required(VERSION 3.0)
project(RISCY-Business)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags to suppress warnings and use GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -Wall -fpermissive")  # Suppress all warnings
endif()

# Locate SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/build
)

# Set up your source files
set(SOURCES_SIMULATORCLI
    ${PROJECT_SOURCE_DIR}/include/bit/bit.c
    ${PROJECT_SOURCE_DIR}/include/logger/logger.c
    ${PROJECT_SOURCE_DIR}/src/simulator/simulator.c
    ${PROJECT_SOURCE_DIR}/src/simulator/register/registers.c
    ${PROJECT_SOURCE_DIR}/src/simulator/memory/memory.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executorManager/executorManager.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/BTypeExecutor/BTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/ITypeExecutor/ITypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/JTypeExecutor/JTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/RTypeExecutor/RTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/STypeExecutor/STypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/UTypeExecutor/UTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/simulatorCLI.c
)

set(SOURCES_RISCY_IDE
    ${PROJECT_SOURCE_DIR}/include/bit/bit.c
    ${PROJECT_SOURCE_DIR}/include/logger/logger.c
    ${PROJECT_SOURCE_DIR}/src/simulator/simulator.c
    ${PROJECT_SOURCE_DIR}/src/simulator/register/registers.c
    ${PROJECT_SOURCE_DIR}/src/simulator/memory/memory.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executorManager/executorManager.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/BTypeExecutor/BTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/ITypeExecutor/ITypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/JTypeExecutor/JTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/RTypeExecutor/RTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/STypeExecutor/STypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/simulator/instructionExecutor/executors/UTypeExecutor/UTypeExecutor.c
    ${PROJECT_SOURCE_DIR}/src/assembler/instructions.cpp
    ${PROJECT_SOURCE_DIR}/include/utility/animationUtilities.cpp
    ${PROJECT_SOURCE_DIR}/include/utility/menuUtilities.cpp
    ${PROJECT_SOURCE_DIR}/include/utility/mouseUtilities.cpp
    ${PROJECT_SOURCE_DIR}/include/utility/soundUtilities.cpp
    ${PROJECT_SOURCE_DIR}/include/utility/textEditorUtilities.cpp
    ${PROJECT_SOURCE_DIR}/src/gui/loadingScreen/loadingScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/gui/startScreen/startScreen.cpp
    ${PROJECT_SOURCE_DIR}/src/gui/dialogBox/dialogBox.cpp
    ${PROJECT_SOURCE_DIR}/src/gui/editor/editor.cpp
    ${PROJECT_SOURCE_DIR}/src/gui/main.cpp
)

if(BUILD_SIMULATOR_CLI)
    # Set output directory for executables
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

    # Add the executable
    add_executable(RISCY-Simulator ${SOURCES_SIMULATORCLI})
elseif(BUILD_RISCY_IDE)
    # Set output directory for executables
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

    # Add the executable
    add_executable(RISCY-IDE ${SOURCES_RISCY_IDE})

    # Link SFML libraries to your executable
    target_link_libraries(RISCY-IDE sfml-graphics sfml-window sfml-system sfml-audio)
endif()


