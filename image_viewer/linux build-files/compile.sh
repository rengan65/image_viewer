echo compiling
g++ main.cpp tinyfiledialogs.c -o MyImageViewer $(pkg-config --cflags --libs sdl3 sdl3-image sdl3-ttf )
./MyImageViewer


