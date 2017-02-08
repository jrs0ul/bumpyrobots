#include "Player.h"



void Player::drawScore(PicsContainer& pics, unsigned font, float x, float y){
    char buf[100];
    sprintf(buf, "%ld", _score);
    WriteText(x, y, pics, font, buf);
    
}

//-----------------------------
void Player::drawLives(PicsContainer& pics, unsigned shape, float x, float y){
    int count = _lives;
    if (blinkLife)
        count = (_lives > oldlives)? _lives : oldlives;
    for (int i = 0; i < count; i++){
        if (!((i == count - 1)&&(blinkFrameON == false)))
            pics.draw(shape, x + 16 * i, y, 7, false, 0.5f, 0.5f); 
    }
}
//-------------------------------
void Player::die(){
    if (_lives) {
        oldlives = _lives;
        _lives--;
        blinkLife = true;
        lifeBlinkTics = 0;
        frameTics = 0;
        blinkFrameON = true;
        
    }
}
//----------------------
void Player::addLife(){
    oldlives = _lives;
    _lives++;
    blinkLife = true;
    lifeBlinkTics = 0;
    blinkFrameON = true;
    frameTics = 0;
}

//-------------------
void Player::blinkLifeRoutine(){
    if (blinkLife){
        lifeBlinkTics++;
        if (frameTics < 5)
            frameTics++;
        else{
            frameTics = 0;
            blinkFrameON = !blinkFrameON;
        }
        //puts("blink");
        if (lifeBlinkTics > 50){
            blinkLife = false;
            lifeBlinkTics = 0;
            blinkFrameON = true;
            //oldlives = _lives;
            //puts("blink off");
        }
    }
}
