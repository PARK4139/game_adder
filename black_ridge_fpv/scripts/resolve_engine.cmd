@echo off
rem UE_ROOT can point to a custom installation; otherwise use the standard path.
if not defined UE_ROOT set "UE_ROOT=%ProgramFiles%\Epic Games\UE_5.8"
if not exist "%UE_ROOT%\Engine\Binaries\Win64\UnrealEditor.exe" (
  echo Unreal Engine 5.8 not found. Install the latest stable 5.8 hotfix or set UE_ROOT.
  exit /b 2
)
exit /b 0
