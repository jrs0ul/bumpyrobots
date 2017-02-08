#ifndef PLAYER_H
#define PLAYER_H

#include "TextureLoader.h"
#include "gui/Text.h"
#include "externals.h"

class Player{
    long _score;
    int  _lives;
    int oldlives;
    unsigned currentLevel;
    bool blinkLife;
    bool blinkFrameON;
    int lifeBlinkTics;
    int frameTics;
    
public:
    
    Player(){
        _score = 0;
        _lives = defaultLivesCount;
        oldlives = _lives;
        currentLevel = 0;
        lifeBlinkTics = 0;
        frameTics = 0;
        blinkFrameON = true;
    }
    
    void drawScore(PicsContainer& pics, unsigned font, float x, float y);
    void drawLives(PicsContainer& pics, unsigned shape, float x, float y);
    void resetScore(){_score = 0;}
    void resetLevel(){currentLevel = 0;}
    void setLevel(unsigned lev){currentLevel = lev;}
    void incLevel(){currentLevel++;}
    unsigned level(){return currentLevel;}
    long score(){return _score;}
    void addScore(long ns){_score += ns;}
    void resetLives(){_lives = defaultLivesCount;
                      oldlives = _lives;}
    int  lives(){return _lives;}
    
    void die();
    void addLife();
    
    void blinkLifeRoutine();
    
};

#endif //PLAYER_H

