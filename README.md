# Minesweeper clone, written in C++ with SFML 2.5.1.
The program is a clone of the famous game Minesweeper.
In order to compile it, just clone the repository and then compile it with the following command:
> g++ [-g] [-D DEBUG] -std=c++17 -o minesweeper src/* -lsfml-graphics -lsfml-window -lsfml-system
### Requirements
* g++ (or equivalent) that supports c++17
* SFML library installed in the default PATH (tested with version 2.5.1, but it should work with any recent enough version)
### Features
* Three standard difficulties available (easy, medium, hard)
* Custom game parameters (rows, columns, mines) within some limits
* Random placement of mines uses the Mersenne Twister engine provided by c++'s standard library [link](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)
* Recursive uncovering of adjacent cells with value 0
### License
The code is licensed under the GPLv3 license, a copy of which has been provided in the file COPYING
### Have fun!
