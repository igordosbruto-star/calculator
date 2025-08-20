@echo off
setlocal
call "%~dp0check_dependencies.bat" || exit /b 1

set "VSCODE_DIR=.vscode"

if not exist "%VSCODE_DIR%" (
    mkdir "%VSCODE_DIR%"
)

if not exist "%VSCODE_DIR%\tasks.json" (
    (
        echo {
        echo     "version": "2.0.0",
        echo     "tasks": [
        echo         {
        echo             "label": "build",
        echo             "type": "shell",
        echo             "command": "make",
        echo             "args": [
        echo                 "cli"
        echo             ],
        echo             "options": {
        echo                 "cwd": "${workspaceFolder}/src/duke"
        echo             },
        echo             "group": "build",
        echo             "problemMatcher": [
        echo                 "$gcc"
        echo             ]
        echo         }
        echo     ]
        echo }
    ) > "%VSCODE_DIR%\tasks.json"
)

if not exist "%VSCODE_DIR%\launch.json" (
    (
        echo {
        echo     "version": "0.2.0",
        echo     "configurations": [
        echo         {
        echo             "name": "Debug app",
        echo             "type": "cppdbg",
        echo             "request": "launch",
        echo             "program": "${workspaceFolder}/src/duke/app",
        echo             "args": [],
        echo             "stopAtEntry": false,
        echo             "cwd": "${workspaceFolder}/src/duke",
        echo             "environment": [],
        echo             "externalConsole": false,
        echo             "MIMode": "gdb",
        echo             "preLaunchTask": "build"
        echo         }
        echo     ]
        echo }
    ) > "%VSCODE_DIR%\launch.json"
)

if not exist "%VSCODE_DIR%\c_cpp_properties.json" (
    (
        echo {
        echo     "configurations": [
        echo         {
        echo             "name": "Linux",
        echo             "includePath": [
        echo                 "${workspaceFolder}/include",
        echo                 "${workspaceFolder}/third_party"
        echo             ],
        echo             "defines": [],
        echo             "compilerPath": "/usr/bin/g++",
        echo             "cStandard": "c11",
        echo             "cppStandard": "c++17",
        echo             "intelliSenseMode": "linux-gcc-x64"
        echo         }
        echo     ],
        echo     "version": 4
        echo }
    ) > "%VSCODE_DIR%\c_cpp_properties.json"
)

echo VSCode configuration created.
