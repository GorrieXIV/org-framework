#!/bin/sh

# Installs dependencies for compiling origins

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        # GNU/Linux
        echo "Installing libraries: libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libboost-all-dev..."
        apt-get update;
        apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libboost-all-dev -y;
elif [[ "$OSTYPE" == "darwin"* ]]; then
        # Mac OS
        echo "Installing libraries: cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer boost..."
        if [[ $(which brew) ]]; then
            brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer boost || true;
        elif [[ $(which port) ]]; then
            echo "MacPorts was detected but is not yet supported, please install brew."
        else
            echo "Missing brew: install brew and then run me again!"
        fi
elif [[ "$OSTYPE" == "cygwin" ]]; then
        # Cygwin
        echo "Cygwin systems are not yet supported.";
elif [[ "$OSTYPE" == "msys" ]]; then
        # MinGW & Git Bash
        echo "msys systems are not yet supported.";
elif [[ "$OSTYPE" == "win32" ]]; then
        # Windows
        echo "Windows systems are not yet supported.";
elif [[ "$OSTYPE" == "freebsd"* ]]; then
        # FreeBSD
        echo "FreeBSD systems are not yet supported.";
else
        echo "No supported operating system detected :(";
fi
