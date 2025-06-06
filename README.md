# canis-template

## ubuntu
gcc gdb git clang ccache cmake libharfbuzz-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev libbz2-dev libglew-dev

cmake -B build/
make -j8 -C build/

## windows
vscode cmake gcc

https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2.zip

https://github.com/Kitware/CMake/releases/download/v3.31.2/cmake-3.31.2-windows-x86_64.msi