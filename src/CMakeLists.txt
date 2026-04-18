include("${_build_cmake_local}")

message("Adding library: ${PISUBMARINE_MODULE_NAME}")
add_library(${PISUBMARINE_MODULE_NAME} INTERFACE
        "../public/PiSubmarine/Battery/Telemetry/Api/IProvider.h"
        "../public/PiSubmarine/Battery/Telemetry/Api/State.h"
)
target_include_directories(${PISUBMARINE_MODULE_NAME} INTERFACE "../public")
PiSubmarineInitTarget(${PISUBMARINE_MODULE_NAME})

PiSubmarineAddDependency("https://github.com/PiSubmarine/Error.Api" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Error.Api)

PiSubmarineAddDependency("https://github.com/PiSubmarine/Units" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Units)
