# game-of-life

> [Conway's Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), written in c

![choose level](https://github.com/ArtskydJ/game-of-life/blob/master/screenshots/choose-preset.PNG)
![game play](https://github.com/ArtskydJ/game-of-life/blob/master/screenshots/random.PNG)
![game over](https://github.com/ArtskydJ/game-of-life/blob/master/screenshots/gosper-glider-gun.PNG)
![game over](https://github.com/ArtskydJ/game-of-life/blob/master/screenshots/lightweight-spaceship.PNG)

## How to compile

- Get MinGW
- Run this command:

```bash
gcc -std=c99 -o bin/GameOfLife.exe GameOfLife.c -lmingw32 -lSDLmain -lSDL -lSDL_ttf -mwindows
```

## Known issues

- That intro screen is ugly, and only the first column works

## License

[VOL](http://veryopenlicense.com)
