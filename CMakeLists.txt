cmake_minimum_required(VERSION 3.14)
project(CrossWordQuest VERSION 1.0 LANGUAGES CXX)

# ── C++ standard ──────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Qt5 specific settings ─────────────────────────────────────
set(CMAKE_AUTOMOC ON)   # auto-runs moc for Q_OBJECT classes
set(CMAKE_AUTORCC ON)   # auto-processes .qrc resource files
set(CMAKE_AUTOUIC ON)   # auto-processes .ui files (if any)

# ── Find Qt5 ─────────────────────────────────────────────────
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

# ── Source files ──────────────────────────────────────────────
set(SOURCES
    main.cpp
    Homepage.cpp
)

set(HEADERS
    Homepage.h
)

# ── Executable ────────────────────────────────────────────────
# WIN32 flag hides the console window on Windows
add_executable(CrossWordQuest WIN32
    ${SOURCES}
    ${HEADERS}
)

# ── Link Qt5 modules ──────────────────────────────────────────
target_link_libraries(CrossWordQuest PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# ── Qt5 Windows deployment (copies Qt DLLs next to .exe) ──────
if(WIN32)
    find_program(WINDEPLOYQT windeployqt
        HINTS "${Qt6_DIR}/../../../bin"
    )
    if(WINDEPLOYQT)
        add_custom_command(TARGET CrossWordQuest POST_BUILD
            COMMAND ${WINDEPLOYQT}
                --no-translations
                --no-system-d3d-compiler
                $<TARGET_FILE:CrossWordQuest>
            COMMENT "Running windeployqt..."
        )
    endif()
endif()
