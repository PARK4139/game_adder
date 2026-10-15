@echo off
setlocal
call "%~dp0scripts\resolve_engine.cmd"
if errorlevel 1 exit /b %errorlevel%
call "%UE_ROOT%\Engine\Build\BatchFiles\Build.bat" BlackRidgeFPVEditor Win64 Development "-Project=%~dp0BlackRidgeFPV.uproject" -WaitMutex -NoHotReloadFromIDE
exit /b %errorlevel%
