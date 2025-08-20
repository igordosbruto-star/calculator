# PowerShell script to check and optionally install project dependencies
# Similar to scripts/check_deps.sh but for Windows.

$ErrorActionPreference = "Stop"

# Map dependencies to package identifiers for winget and Chocolatey
$deps = @{
    "g++"       = @{winget="GNU.Mingw-w64"; choco="mingw"; cmd="g++"}
    "make"      = @{winget="GnuWin32.Make"; choco="make"; cmd="make"}
    "gdb"       = @{winget="GnuWin32.GDB";  choco="gdb";  cmd="gdb"}
    "pkg-config"= @{winget="pkgconfiglite.pkgconfiglite"; choco="pkgconfiglite"; cmd="pkg-config"}
    "Qt6Core"   = @{winget="Qt.Qt6";        choco="qt6-base"; cmd="pkg-config --exists Qt6Core"}
}

$missing = @()

foreach ($name in $deps.Keys) {
    $checkCmd = $deps[$name].cmd
    if ($name -eq "Qt6Core") {
        $p = Start-Process -FilePath pkg-config -ArgumentList "--exists", "Qt6Core" -NoNewWindow -PassThru -Wait -ErrorAction SilentlyContinue
        if ($p.ExitCode -ne 0) { $missing += $name }
    } else {
        if (-not (Get-Command $checkCmd.Split()[0] -ErrorAction SilentlyContinue)) {
            $missing += $name
        }
    }
}

if ($missing.Count -eq 0) {
    Write-Host "Todas as dependências estão instaladas."
    exit 0
}

Write-Host "Dependências faltantes: $($missing -join ', ')"
$reply = Read-Host "Instalar? [y/N]"
if ($reply -notmatch '^[Yy]$') {
    Write-Host "Instalação cancelada."
    exit 1
}

if (Get-Command winget -ErrorAction SilentlyContinue) {
    foreach ($dep in $missing) {
        $pkg = $deps[$dep].winget
        if ($pkg) {
            Write-Host "Instalando $pkg via winget..."
            winget install --id $pkg -e --silent --accept-package-agreements --accept-source-agreements
        } else {
            Write-Host "Sem mapeamento winget para $dep"
        }
    }
} elseif (Get-Command choco -ErrorAction SilentlyContinue) {
    foreach ($dep in $missing) {
        $pkg = $deps[$dep].choco
        if ($pkg) {
            Write-Host "Instalando $pkg via choco..."
            choco install $pkg -y
        } else {
            Write-Host "Sem mapeamento choco para $dep"
        }
    }
} else {
    Write-Host "Nenhum gerenciador de pacotes suportado encontrado (winget ou choco)."
    exit 2
}

Write-Host "Verificação concluída."
