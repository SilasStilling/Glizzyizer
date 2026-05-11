; Inno Setup script for Glizzyizer VST3
; Build VST3 in Release first, then compile this with Inno Setup (ISCC.exe).

#define MyAppName        "Glizzyizer"
#define MyAppVersion     "0.1.0"
#define MyAppPublisher   "NewPlug"
#define MyAppURL         "https://github.com/SilasStilling/NewPlug"
#define VST3SourceDir    "..\build\Glizzyizer_artefacts\Release\VST3\Glizzyizer.vst3"

[Setup]
AppId={{A4C2B9E7-7E2F-4F4B-9C1D-1E3D5A8B2F11}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
DefaultDirName={commoncf64}\VST3\Glizzyizer.vst3
DefaultGroupName={#MyAppName}
DisableDirPage=yes
DisableProgramGroupPage=yes
UninstallDisplayName={#MyAppName} {#MyAppVersion}
OutputDir=Output
OutputBaseFilename=Glizzyizer-{#MyAppVersion}-Setup
Compression=lzma2/ultra
SolidCompression=yes
WizardStyle=modern
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
PrivilegesRequired=admin

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "{#VST3SourceDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
; No shortcuts for a VST3 — host scans the install folder

[Code]
function InitializeSetup(): Boolean;
var
  SourcePath: String;
begin
  SourcePath := ExpandConstant('{src}\..\build\Glizzyizer_artefacts\Release\VST3\Glizzyizer.vst3\Contents\x86_64-win\Glizzyizer.vst3');
  if not FileExists(SourcePath) then
  begin
    MsgBox('Glizzyizer.vst3 not found at:' #13#10 + SourcePath + #13#10 #13#10 'Build the project in Release first.', mbError, MB_OK);
    Result := False;
    exit;
  end;
  Result := True;
end;
