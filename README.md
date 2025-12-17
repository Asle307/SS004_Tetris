## Note
- Before compiling and running, run the following commands (if msys2 gcc is used):
`pacman -S mingw-w64-x86_64-sfml` (To download SFML)
- Following [SFML tutorial](https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/#compiling-an-sfml-program), run the following the get the final .exe:
```
g++ -c main.cpp
// Remember to add audio
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
