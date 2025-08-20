#!/usr/bin/env bash

set -e

# Detect distribution
if command -v lsb_release >/dev/null 2>&1; then
    distro=$(lsb_release -si)
else
    distro=$(uname -s)
fi

# Map dependencies to package names
# key: check target (command or pkg-config name)
# value: package name for package manager
declare -A deps=(
    ["g++"]="g++"
    ["make"]="make"
    ["pkg-config"]="pkg-config"
    ["Qt6Core"]="qt6-base-dev"
)

missing=()
packages=()

for dep in "${!deps[@]}"; do
    pkg="${deps[$dep]}"
    if [[ "$dep" == Qt6Core ]]; then
        if ! pkg-config --exists "$dep" 2>/dev/null; then
            missing+=("$dep")
            packages+=("$pkg")
        fi
    else
        if ! command -v "$dep" >/dev/null 2>&1; then
            missing+=("$dep")
            packages+=("$pkg")
        fi
    fi
done

if [ ${#missing[@]} -eq 0 ]; then
    echo "Todas as dependências estão instaladas."
    exit 0
fi

echo "Dependências faltantes: ${missing[*]}"
read -p "Instalar? [y/N] " reply
if [[ ! "$reply" =~ ^[Yy]$ ]]; then
    echo "Instalação cancelada."
    exit 1
fi

case "$distro" in
    Ubuntu|Debian)
        manager="sudo apt install -y"
        ;;
    Fedora|CentOS|RedHatEnterpriseServer)
        manager="sudo dnf install -y"
        ;;
    Arch|ManjaroLinux)
        manager="sudo pacman -S --noconfirm"
        ;;
    *)
        echo "Distribuição $distro não suportada para instalação automática."
        exit 2
        ;;
esac

if $manager "${packages[@]}"; then
    echo "Instalação concluída."
else
    echo "Falha na instalação."
    exit 3
fi
