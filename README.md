# A blank for a SDL2-based platformer game
Attention, this repository does not contain (and never will) a playable game. The goal is to show basic principles to my students, so it is only a demo repo.
Here is an example of what is inside:

![](https://github.com/ssloy/sdl2-demo/raw/main/capture.gif)

At the moment of this writing the repository contains mere 332 lines of code:
```sh
ssloy@khronos:~/+/sdl2-demo/src$ cat *.cpp *.h | wc -l
332
```


# Compilation
```sh
git clone --recurse-submodules https://github.com/ssloy/sdl2-demo.git &&
cd sdl2-demo &&
mkdir build &&
cd build &&
cmake .. &&
make -j &&
./sdl2-demo
```

You can open the project in Gitpod, a free online dev environment for GitHub:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/ssloy/sdl2-demo)


On open, the editor will compile & run the program as well as open the resulting image in the editor's preview.
Just change the code in the editor and rerun the script (use the terminal's history) to see updated images.
Note how awesome Gitpod is, it allows to run SDL2 games directly in the browser!

