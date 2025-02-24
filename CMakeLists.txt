cmake_minimum_required(VERSION 3.23)
project(GRAPH_DELAY VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(JUCE_COPY_PLUGIN_AFTER_BUILD ON)

#
# Dependencies.
# 1. Create a dependencies folder in our project.
# 2. Get CPM (cmake package manager).
# 3. Use CPM to get JUCE.
#
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
include(cmake/get_cpm.cmake)
include(cmake/get_juce.cmake)

#
# Plugin configuration.
#
juce_add_plugin(${PROJECT_NAME}
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME maiken                         # Specify the name of the plugin's author
        IS_SYNTH FALSE                              # Is this a synth or an effect?
        NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
        NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
        IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
        # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE MAPC               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE P009                            # A unique four-character plugin id with exactly one upper-case character
        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "Graph Delay")                 # The name of the final executable, which can differ from the target name

juce_generate_juce_header(${PROJECT_NAME})

set(PROJECT_SOURCES
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/gui/interval_control/IntervalButton.cpp
        source/gui/interval_control/IntervalButtons.cpp
        source/gui/look_and_feel/CustomLookAndFeel.cpp
        source/gui/widgets/CustomLabel.cpp
        source/gui/widgets/CustomToggleButton.cpp
        source/gui/widgets/RotaryControl.cpp
        source/gui/widgets/RotaryWithLabel.cpp
        source/gui/xy_graph/XyGraph.cpp
        source/gui/xy_graph/XyGraphCanvas.cpp
        source/gui/xy_graph/XyGraphOverlay.cpp
        source/gui/xy_graph/XyGraphThumb.cpp
)

set(PROJECT_HEADERS
        source/PluginEditor.h
        source/PluginProcessor.h
        source/gui/interval_control/IntervalButton.h
        source/gui/interval_control/IntervalButtons.h
        source/gui/look_and_feel/CustomLookAndFeel.h
        source/gui/look_and_feel/Theme.h
        source/gui/widgets/CustomLabel.h
        source/gui/widgets/CustomToggleButton.h
        source/gui/widgets/RotaryControl.h
        source/gui/widgets/RotaryWithLabel.h
        source/gui/xy_graph/XyGraph.h
        source/gui/xy_graph/XyGraphCanvas.h
        source/gui/xy_graph/XyGraphOverlay.h
        source/gui/xy_graph/XyGraphThumb.h
        source/utility/GlobalConstants.h
)

target_sources(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/interval_control
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/look_and_feel
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/xy_graph
        ${CMAKE_CURRENT_SOURCE_DIR}/source/utility
)

# JUCE modules make use of compile definitions to switch certain features on/off.
# If there's a particular feature you need that's not on by default,
# check the module header for the correct flag to set here.
target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
