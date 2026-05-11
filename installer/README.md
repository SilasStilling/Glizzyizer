# Glizzyizer Installer

Builds a Windows installer for the Glizzyizer VST3 using [Inno Setup](https://jrsoftware.org/isdl.php).

## Prerequisites

1. Build the plugin in **Release**:
   ```powershell
   & "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build build --config Release
   ```
2. Install Inno Setup 6 from https://jrsoftware.org/isdl.php

## Build the installer

From this folder:

```powershell
& "C:\Program Files (x86)\Inno Setup 6\ISCC.exe" Glizzyizer.iss
```

The installer is written to `installer\Output\Glizzyizer-<version>-Setup.exe`.

## What it does

- Installs `Glizzyizer.vst3` (bundle) into `C:\Program Files\Common Files\VST3\Glizzyizer.vst3`
- Requires admin (installs under Program Files)
- Bumps version in `Glizzyizer.iss` (`MyAppVersion`) to match `CMakeLists.txt` for each release
