@ECHO OFF
setlocal
if not defined axoloti_runtime (
   @REM set axoloti_runtime=%~sdp0\.. ??
   set axoloti_runtime=%~sdp0
)
call %~sdp0\path.bat
call %~sdp0\test_env.bat

cd %axoloti_firmware%
call %axoloti_firmware%\compile_firmware_win.bat %1

endlocal
