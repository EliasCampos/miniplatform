# Miniplatform

A very simple platform game.

## How to build the game (for Debian-based distributions)

First, install SFML library:
```shell script
sudo apt-get install libsfml-dev
```
To find other ways to install SFML library, referense official documentation:  \
https://www.sfml-dev.org/tutorials/2.5/start-linux.php

Then, install last version of CMake. You can download it here:
https://cmake.org/download/  \
(Some help to update CMake version could be found here:\
https://askubuntu.com/questions/829310/how-to-upgrade-cmake-in-ubuntu)

Then run next commands:
```shell script
mkdir build
cmake -B build/
cmake --build build/
```

Now, executable file is available in `build/` directory as `miniplatform`.
Just run it:
```shell script
./build/miniplatform
```
