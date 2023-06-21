@echo off
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system" && (
    echo [INFO]: Administrative permissions detected. Continuing...
    goto :RunCommands
) || (
    echo [ERR]: This script requires administrative privileges. Please run it as an administrator.
    pause
    exit /b 1
)

echo
:RunCommands
bootrec /FixMbr
bootrec /FixBoot
bootrec /rebuildbcd
bootrec /ScanOS
bootrec /nt60 all /force
pause
