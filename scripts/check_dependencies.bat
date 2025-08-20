@echo off
where g++ >nul 2>nul || (
    echo ERRO: g++ não encontrado. Instale o compilador e tente novamente.
    exit /b 1
)

where make >nul 2>nul || (
    echo ERRO: make não encontrado. Instale o make e tente novamente.
    exit /b 1
)

where gdb >nul 2>nul || (
    echo ERRO: gdb não encontrado. Instale o depurador e tente novamente.
    exit /b 1
)
