@echo off
setlocal
call "%~dp0scripts\resolve_engine.cmd"
if errorlevel 1 exit /b %errorlevel%
"%UE_ROOT%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "%~dp0BlackRidgeFPV.uproject" -run=pythonscript "-script=%~dp0scripts\initialize_level.py" -unattended -nosplash -stdout -FullStdOutLogOutput
exit /b %errorlevel%
