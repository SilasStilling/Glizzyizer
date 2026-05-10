cmake_minimum_required(VERSION 3.22)

project(Glizzyizer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/MP)
endif()

add_subdirectory(external/JUCE)

juce_add_plugin(Glizzyizer
    COMPANY_NAME            "NewPlug"
    BUNDLE_ID               "com.newplug.glizzyizer"
    PLUGIN_MANUFACTURER_CODE NwPg
    PLUGIN_CODE             Glzy
    FORMATS                 VST3 Standalone
    PRODUCT_NAME            "Glizzyizer"
    IS_SYNTH                FALSE
    NEEDS_MIDI_INPUT        FALSE
    NEEDS_MIDI_OUTPUT       FALSE
    IS_MIDI_EFFECT          FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
)

target_sources(Glizzyizer PRIVATE
    source/PluginProcessor.cpp
    source/PluginEditor.cpp
    source/dsp/Saturator.cpp
    source/dsp/TiltEQ.cpp
    source/dsp/OnionStage.cpp
    source/ui/GlizzyLookAndFeel.cpp
    source/ui/KnobComponent.cpp
)

juce_add_binary_data(GlizzyizerAssets
    HEADER_NAME BinaryData.h
    NAMESPACE   BinaryData
    SOURCES
        resources/glizzyizer_logo.png
        resources/glizzyizer_background.png
        resources/glizzyizer_sausage.png
)

target_compile_definitions(Glizzyizer PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(Glizzyizer
    PRIVATE
        GlizzyizerAssets
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
