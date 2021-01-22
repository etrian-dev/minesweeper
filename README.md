# Yet another minesweeper clone
**written in C++ using SFML for the GUI**  
The program is a clone of the famous game Minesweeper.
In order to compile it, just clone the repository and then compile it with the following command:  
```
g++ [-g] [-D DEBUG] -o minesweeper src/* -lsfml-graphics -lsfml-window -lsfml-system
```
The `-g` and `-D DEBUG` options are needed to get verbose debugging information (and cheat).
It is assumed that the compilation is launched from within the main directory of the repo,
otherwise just alter the path to the source files. It's also assumed that sfml is already installed in the default location for your system, so that the compiler can find it directly upon linking. Otherwise, specify its path [as explained here](https://www.sfml-dev.org/tutorials/2.5/start-linux.php).  
### Compilation Requirements
* C++ compiler that supports c++17 or above  
(tested with g++)
* Developement files for the SFML library  
(tested with 2.5.1, but any recent enough version should be fine)
### Features
* Three standard difficulties available:
	1. easy: 9 x 9 grid, 10 mines
	1. medium: 16 x 16 grid, 40 mines
	1. hard: 16 x 30 grid, 99 mines
* The user can set custom game parameters (rows, columns, mines) within some bounds
* Random placement of mines uses the Mersenne Twister engine provided by c++'s standard library [(link)](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)  
(Note that the generation of the board is done after the first move, so one cannot lose instantly)
* Recursive uncovering of adjacent cells with value 0
### License
The code is licensed under the GPLv3 license, a copy of which is provided in the file [COPYING](./COPYING)
### Have fun!
