# Glizzyizer

A saturation/distortion plugin for FL Studio (and any VST3 host), inspired by Sausage Fattener.

Four controls:

- **Girth** — drive into a tanh waveshaper for thick saturation
- **Mustard** — tilt EQ (negative = darker, positive = brighter)
- **Onions** — toggles a presence boost + high-frequency stereo widener
- **Serve** — output gain in dB

Built with [JUCE](https://juce.com) as VST3 + Standalone.

## Build (Windows, Visual Studio 2022)

JUCE is included as a git submodule. After cloning:

```powershell
git submodule update --init --recursive

# Configure with the CMake bundled with Visual Studio 2022
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -S . -B build -G "Visual Studio 17 2022" -A x64

# Build Release
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build build --config Release
```

The VST3 will be at `build\Glizzyizer_artefacts\Release\VST3\Glizzyizer.vst3`. The standalone executable will be at `build\Glizzyizer_artefacts\Release\Standalone\Glizzyizer.exe`.

## Install in FL Studio

Copy `Glizzyizer.vst3` into your VST3 folder (default `C:\Program Files\Common Files\VST3\`) and rescan plugins in FL Studio (Options → Manage Plugins → Find more plugins).
