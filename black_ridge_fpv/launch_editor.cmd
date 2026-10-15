@echo off
setlocal
call "%~dp0scripts\resolve_engine.cmd"
if errorlevel 1 exit /b %errorlevel%
if not exist "%~dp0Content\Maps\FlightTest.umap" (
  echo Initial map is missing. Run build_editor.cmd and initialize_level.cmd first.
  exit /b 3
)
"%UE_ROOT%\Engine\Binaries\Win64\UnrealEditor.exe" "%~dp0BlackRidgeFPV.uproject" /Game/Maps/FlightTest
exit /b %errorlevel%
