#include <wchar.h>
#include "CppSingleton.h"
#include "Utils.h"
#include "gui/Text.h"

#include <sys/stat.h>



void Singleton::setMusicVolume(float vol){
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    MusicVolume = vol;
    ChangeVolume =true;
#else
    music.setVolume(vol);
#endif
}
//------------------------
void Singleton::playMusic(){
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    PlayMusic = true;
#else
    music.playback();
#endif
}
//---------------------
void Singleton::playNewSong(const char * path){
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    PlayNewSong = true;
    sprintf(songName, "data/%s.m4a", path);
#else
    music.stop();
    music.release();
    sprintf(songName, "data/%s.ogg", path);
    music.open(songName);
    music.playback();
#endif
    
}

//---------------------

void Singleton::init(){
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    glViewport(0, 0, 320, 480);
    glRotatef(-90, 0, 0, 1);
    glOrthof(0.0, (GLfloat) 480, (GLfloat) 320, 0.0, 400, -400);
#else
    glOrtho(0.0, (GLfloat) 480, (GLfloat) 320, 0.0, 400, -400);
#endif
    
    pics.initBuffers();
        
    if (!pics.load("data/pics/list.txt"))
        puts("can't find list");
#ifdef LITE
    pics.remove(13);
    pics.loadFile("welldone_lite.tga", 13, 512, 256, "data/pics/", 1);
    pics.loadFile("lite.tga", 14, 128, 50, "data/pics/", 1);
    pics.loadFile("getfull.tga", 15, 256, 171, "data/pics/", 1);
#else
    pics.loadFile("gamemodes.tga", 14, 128, 128, "data/pics/", 1);
#endif
    
    ss.init(0);
    Vector3D p(0,0,0);
    ss.setupListener(p.v, p.v);
    ss.loadFiles("data/sfx/", "audio.txt");
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    music.open("data/music.ogg");
#endif
    
    pos.v[0] = 50;
    pos.v[1] = 270;
    
    
    playregular_button.set(100, 50, 128, 128);
    playrandom_button.set(252, 50, 128, 128);
    selectGameBack_button.set(5, 5, 64, 40, COLOR(0.5f, 0.5f, 0.5f));
    
    b.set(10, 10, 40, 40);
    bomb_button.set(200, 16, 64, 64);
    jump_button.set(215, 135, 64, 64);
    
    changeName_button.set(160, 260, 180, 64);
    
    resume_button.set(40, 22, 170, 48);
    play_button.set(40, 70, 170, 48);
   
    highscore_button.set(40, 118, 170, 48);
    options_button.set(40, 166, 170, 48);
    howtoplay_button.set(40, 214, 170, 48);
    
    resetLevel_button.set(10, 280, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    resetScore_button.set(410, 280, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    
    onlineScorePage_button.set(410, 280, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    
    helpBack_button.set(5, 5, 64, 40, COLOR(0.5f, 0.5f, 0.5f));
    helpPrev_button.set(5, 280, 64, 40);
    helpNext_button.set(411, 280, 64, 40);
    
    backLevels_button.set(10, 10, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    backOptions_button.set(10, 10, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    backControls_button.set(10, 10, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    controlsReset_button.set(405, 10, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    
    controlsOptions_button.set(350, 70, 80, 40, COLOR(0.5f, 0.5f, 0.5f));
    
    randomHighscore_button.set(270, 10, 170, 48);
    randomHighscore_button.pressed = false;
    regularHighscore_button.set(90, 10, 170, 48);
    regularHighscore_button.pressed = true;
    
    GameCenter_button.set(405,75, 64, 64);
    
    onlineScore_button.set(40, 270, 170, 48);
    onlineScore_button.pressed = false;
    localScore_button.set(210, 270, 170, 48);
    localScore_button.pressed = true;
    
    
    highScoresBack_button.set(10, 10, 65, 40, COLOR(0.5f, 0.5f, 0.5f));
    toMainMenu_button.set(440, 280, 40, 40);
    YesNoDlg.set(50, 100, 380, 120);
    SubmitScoreYN.set(50, 100, 380, 120);
    SubmitScoreYN.setText("Submit your score online ?");
    
    about_button.set(430, 270, 40, 40, COLOR(0.3f, 0.5f, 1.0f, 0.9f));
    jrs0ul_button.set(147, 160, 186, 20);
    getfull_button.set(330, 205, 160, 120);

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    char letters[] = "1234567890QWERTYUIOPASDFGHJKL:ZXCVBNM@$&*-/\\!#?_=() .,";
    Keyboard.setChars((const unsigned char*)letters);
    Keyboard.setCharWidth(40);
    Keyboard.setRowLen(10);
    Keyboard.setpos(30, 60);
#endif
    
    
    
    char megabuf[255];
    sprintf(megabuf, "%s/score.dat", DocumentPath);
    highscoresRegular.load(megabuf, 10);
    sprintf(megabuf, "%s/scoreRandom.dat", DocumentPath);
    highscoresRandom.load(megabuf, 10);
    sprintf(megabuf, "%s/settings.cfg", DocumentPath);


    struct stat attrib;
    stat(megabuf, &attrib);
    struct tm * tim;
    time_t rawtime;
    time ( &rawtime );
    tim = localtime ( &rawtime );
    tim->tm_year = 2011 - 1900;
    tim->tm_mon = 2 - 1;
    tim->tm_mday = 22;
    tim->tm_hour = 23;
    time_t old = mktime(tim);
    //printf("%d\n", old);
    double d = difftime(old, attrib.st_mtime);
    if (d > 0){
        puts("deleting old cfg...");
        remove(megabuf);
    }
    //printf("%.0lf\n", d);
    


    //printf("%f %f\n", sys.bombButton.v[0], sys.bombButton.v[1]);

    if (!sys.load(megabuf)){

    #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            sys.pauseButton = Vector3D(15, 64, 0);
    #else
            sys.pauseButton = Vector3D(15, 5, 0);
    #endif
    #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            sys.bombButton = initialBombButtonPos;
    #else
            sys.bombButton = initialBombButtonPosPC;
    #endif

    }

    
    musicVolume_bar.set(100, 140, 5, 100, sys.musicVolume*100 , 2, false);
    sfxVolume_bar.set(100, 200, 5, 100, sys.sfxVolume*100 , 2, false);
    strcpy(nameToEnter, sys.nameToEnter);
    accel_bar.set(100, 260, 5, 100, sys.accelerometerMultiplier*100, 2, false);
    
    joystick.pos = sys.joystick;
    toMainMenu_button.setpos(sys.pauseButton.v[0], sys.pauseButton.v[1]);
    //printf("%f %f\n", sys.bombButton.v[0], sys.bombButton.v[1]);
    bomb_button.setpos(sys.bombButton.v[0], sys.bombButton.v[1]);
    jump_button.setpos(sys.jumpButton.v[0], sys.jumpButton.v[1]);
    
    
    setMusicVolume(sys.musicVolume);
    ss.setVolume(sys.sfxVolume);
    playMusic();
    

    
    useAccel = false;
    
}
//-----------------------
void Singleton::drawEnterName(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    WriteShadedText(120, 10, pics, 0, "Enter your name:");
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    WriteShadedText(90, 30, pics, 0, nameToEnter);
    WriteShadedText(90 + strlen(nameToEnter) * 11, 40, pics, 0, (rand()%2 == 0) ? "_" : " ");
    Keyboard.draw(pics, GUI, 12, 0, COLOR(0.5f, 0.5f, 0.5f, 0.9f));
#endif
    
}
//----------------------
void Singleton::submitScore(int type){
    char tmpName[12];
    strncpy(tmpName, nameToEnter, 12);
    sprintf(highscorePostParams,"name=%s&score=%ld&password=", tmpName, player.score());
    GameCenterScore = player.score();
    onlineScoreType = type;
    sendScore = true;
    onlineScorePage = 0;
    submitOnline = true;
}
//----------------------
void Singleton::addScore(){
    char megabuf[256];
    if (levellist.count()){
        levellist.destroy();
        sprintf(megabuf, "%s/score.dat", DocumentPath);
        highscoresRegular.addScore(nameToEnter, player.score(), 10);
        highscoresRegular.write(megabuf, 10);
        randomHighscore_button.pressed = false;
        regularHighscore_button.pressed = true;
        if (submitOnline){
            submitScore(0);
            onlineScore_button.pressed = true;
            localScore_button.pressed = false;
        }
    }
    else{
        sprintf(megabuf, "%s/scoreRandom.dat", DocumentPath);
        highscoresRandom.addScore(nameToEnter, player.score(), 10);
        highscoresRandom.write(megabuf, 10);
        randomHighscore_button.pressed = true;
        regularHighscore_button.pressed = false;
        if (submitOnline){
            submitScore(1);
            onlineScore_button.pressed = true;
            localScore_button.pressed = false;
        }
    }
}

//-----------------------
void Singleton::enterNameLogic(){
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    float mx = -1;
    float my = -1;
    if (touches.up.count()){
        mx = touches.up[0].v[0];
        my = touches.up[0].v[1];
    }
    unsigned result = Keyboard.getInput(globalKEY, mx, my);
    if (result){
        //printf("%c\n", globalKEY);
            if ((result != 8) && (result != 13) && (strlen(nameToEnter) < 11)&&(result < 127)){

                //printf("char %d\n", result);

                ss.playsound(8);
                unsigned pos = strlen(nameToEnter);
                nameToEnter[pos] = (char)result;
                nameToEnter[pos + 1] = 0;
            }
            else{
                if (result == 8){
                    ss.playsound(8);
                    nameToEnter[strlen(nameToEnter) - 1] = 0;
                }
                else{

                    /*printf("char %d\n", result);
                    if ((strlen(nameToEnter) < 11)){
                        unsigned pos = strlen(nameToEnter);
                        nameToEnter[pos] = (char)result;
                        nameToEnter[pos + 1] = 0;
                    }*/

                }
            }
    }

    
#endif
        if (TextEntered || Keyboard.entered){
            TextEntered = false;
            ss.playsound(8);
            char megabuf[255];
            
            if (strlen(nameToEnter) <= 0){
                strcpy(nameToEnter, "NONAME");
            }
            
            
            strncpy(sys.nameToEnter, nameToEnter, 11);
            strncpy(nameToEnter, sys.nameToEnter, 11);
            sprintf(megabuf, "%s/settings.cfg", DocumentPath);
            sys.write(megabuf);
                
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            Keyboard.reset();
#endif
            gamestate = TITLE;
            //playNewSong("music");
        }
}

//----------------------
void Singleton::drawMainMenu(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    pics.draw(LOGO, 230, 0, 0, false, 0.8f, 0.8f);
    play_button.draw(pics, MENU, 8);
#ifdef LITE
    pics.draw(LITESIGN, 400, 10, 0, false, 0.5f, 0.5f);
#endif
    //playregular_button.draw(pics, 8, 0);
    highscore_button.draw(pics, MENU, 3);
    options_button.draw(pics, MENU, 4);
    howtoplay_button.draw(pics, MENU, 5);
    if (levelCreated)
        resume_button.draw(pics, MENU, 2);
#ifndef LITE
    about_button.draw(pics, GUI, (about_button.pressed)? 6 : 5);
#else
    getfull_button.draw(pics, GETFULL, 0);
#endif
    COLOR bgColor = COLOR(0.5f, 0.5f, 0.5f, 0.7f);
    pics.draw(GUI, 160, 260, 2, false, 180/64.0f, 1.0f, 0 , bgColor, bgColor); 
    WriteShadedText(190, 265, pics, 0, "Welcome,", 1.0f, 1.0f);
    WriteShadedText(190, 285, pics, 0, nameToEnter, 1.0f, 1.0f);
    WriteShadedText(165, 306, pics, 0, "(Tap here to change name)", 0.6f, 0.8f);
  
}
//-----------------------
void Singleton::resetHighScores(){
    char megabuf[255];
    if (regularHighscore_button.pressed){
        sprintf(megabuf, "%s/score.dat", DocumentPath);
        highscoresRegular.destroy();
        highscoresRegular.write(megabuf, 10);
    }
    if (randomHighscore_button.pressed){
        sprintf(megabuf, "%s/scoreRandom.dat", DocumentPath);
        highscoresRandom.destroy();
        highscoresRandom.write(megabuf, 10);
    }
}
//-----------------------
void Singleton::parseOnlineScores(HighScores& container){
    
    container.destroy();
    Xml data;
    wchar_t tmp[2024];
    //puts("parsing...");
    //puts(highScoreFromServer);
    mbstowcs(tmp, highScoreFromServer, 2024);
    data.parse(tmp);
    XmlNode * n = 0;
    n = data.root.getNode(L"Highscores");
    
    if (n){
       
        for (unsigned i = 0; i < n->childrenCount(); i++) {
            XmlNode * score = 0;
            score = n->getNode(i);
            if (score){
                char _name[13];
                XmlNode * nameNode = 0;
                nameNode = score->getNode(L"Name");
                if (nameNode){
                    wcstombs(_name, nameNode->getValue(), 12);
                    //puts(_name);
                }
                XmlNode * pointNode = 0;
                char stmp[20];
                pointNode = score->getNode(L"Points");
                if (pointNode){
                    wcstombs(stmp, pointNode->getValue(), 20);
                    long _score = atoi(stmp);
                    container.addScore(_name, _score, 10);
                }
            }
        }
    }
    container.resetHighscoreIndex();
    data.destroy();
}

//-----------------------
void Singleton::fetchScore(int type){
    
    getHighScore = true;
    gotHighScore = false;
    waitForOnlineScoreTics = 0;
    highScoreFromServer[0] = 0;
    onlineScoreRandom.destroy();
    onlineScoreRegular.destroy();
    onlineScoreType = type;
    failToGetScore = false;
    
}

//-----------------------
void Singleton::highScoreLogic(){


#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

    if ((!Keys[7])&&(OldKeys[7])){
        gamestate = TITLE;
        ss.playsound(8);
    }
#endif


#ifndef LITE  
    if (strlen(highScoreFromServer) < 1){
        if (waitForOnlineScoreTics < MAXWAITFORSCORE)
            waitForOnlineScoreTics++;
    }
    
    if ((waitForOnlineScoreTics == MAXWAITFORSCORE) || (gotHighScore)){
        
        getHighScore = false;
        waitForOnlineScoreTics = 0;
        
        if (gotHighScore){
            gotHighScore = false;
            if (strlen(highScoreFromServer) > 0){
                if (onlineScoreType == 0)
                    parseOnlineScores(onlineScoreRegular);
                else
                    parseOnlineScores(onlineScoreRandom);
            }
        }
        else{
            failToGetScore = true;
        }
    }
#endif
    
    if (touches.down.count()){
        float mx = touches.down[0].v[0];
        float my = touches.down[0].v[1];
        if (GameCenter_button.isPointerOnTop(mx, my)){
            GameCenter_button.c = COLOR(0.5f,0.5f,0.5f);
        }

    }
            
    if (touches.move.count()){
        float mx = touches.move[0].v[0];
        float my = touches.move[0].v[1];
            
        if (GameCenter_button.isPointerOnTop(mx, my)){
            GameCenter_button.c = COLOR(0.5f,0.5f,0.5f);
        }
    }
            
    if (touches.allfingersup){
        GameCenter_button.c = COLOR(1.0f,1.0f,1.0f);  
    }
    
    
    if ((touches.up.count())&&(!touches.down.count())){
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (YesNoDlg.active()){
            if (YesNoDlg.isPointerOnYes(mx, my)){
                resetHighScores();
                YesNoDlg.deactivate();
                ss.playsound(8);
            }
            if (YesNoDlg.isPointerOnNo(mx, my)){
                YesNoDlg.deactivate();
                ss.playsound(8);
            }
            
            return;
        }

        if (!onlineScore_button.pressed){
            if (resetScore_button.isPointerOnTop(mx, my)){
                YesNoDlg.activate();
                ss.playsound(8);
            }
        }
#ifndef LITE      
        
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
        if (GameCenter_button.isPointerOnTop(mx, my)){
            ShowGameCenter = true;
            GameCenter_button.c = COLOR(1.0f,1.0f,1.0f);
            ss.playsound(8);
        }
#endif
        
        if (onlineScorePage_button.isPointerOnTop(mx, my)){
            if (onlineScorePage > 0)
                onlineScorePage = 0;
            else {
                onlineScorePage = 1;
            }
            if (regularHighscore_button.pressed)
                fetchScore(0);
            else 
                fetchScore(1);
            ss.playsound(8);

        }
        
        if (randomHighscore_button.isPointerOnTop(mx, my)){
            randomHighscore_button.pressed = true;
            regularHighscore_button.pressed = false;

            if (onlineScore_button.pressed)
                fetchScore(1);

            ss.playsound(8);
        }
        
        if (regularHighscore_button.isPointerOnTop(mx, my)){
            randomHighscore_button.pressed = false;
            regularHighscore_button.pressed = true;

            if (onlineScore_button.pressed)
                fetchScore(0);

            ss.playsound(8);
        }       
        if (onlineScore_button.isPointerOnTop(mx, my)){
            onlineScore_button.pressed = true;
            localScore_button.pressed = false;
            waitForOnlineScoreTics = 0;
            
            if (regularHighscore_button.pressed)
                fetchScore(0);
            else 
                fetchScore(1);
            ss.playsound(8);
        }
        
        if (localScore_button.isPointerOnTop(mx, my)){
            onlineScore_button.pressed = false;
            localScore_button.pressed = true;
            ss.playsound(8);
        }
#endif
        
        
        if (highScoresBack_button.isPointerOnTop(mx, my)){
            gamestate = TITLE;
            ss.playsound(8);
        }
    }
}
//------------------------
void Singleton::helpLogic(){
    if ((touches.up.count())&&(!touches.down.count())){
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (helpPrev_button.isPointerOnTop(mx, my)){
            if (helpPage > 0){
                helpPage--;
                ss.playsound(8);
            }
        }
        if (helpNext_button.isPointerOnTop(mx, my)){
            if (helpPage < 1){
                helpPage++;
                ss.playsound(8);
            }
        }
        
        if (helpBack_button.isPointerOnTop(mx, my)){
            gamestate = TITLE;
            helpPage = 0;
            ss.playsound(8);
        }
    }
}
//------------------------
void Singleton::optionsLogic(){


#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

    if ((!Keys[7])&&(OldKeys[7])){
        gamestate = TITLE;
        char buf[255];
        if (strlen(sys.nameToEnter) <= 0)
            strcpy(sys.nameToEnter,"Player");
        sprintf(buf, "%s/settings.cfg", DocumentPath);
        sys.write(buf);
        ss.playsound(8);

    }
#endif    
    if ((touches.up.count())&&(!touches.down.count())){
        
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (backOptions_button.isPointerOnTop(mx, my)){
            gamestate = TITLE;
            char buf[255];
            if (strlen(sys.nameToEnter) <= 0)
                strcpy(sys.nameToEnter,"NONAME");
            sprintf(buf, "%s/settings.cfg", DocumentPath);
            sys.write(buf);
            ss.playsound(8);
        }
        
        if (controlsOptions_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            gamestate = CONTROLCONFIG;
            tmplevel.generate(15, 15);
            tmpArmy.create(tmplevel);
        }
        
        if (musicVolume_bar.isPointerOnNextpage(mx, my)){
            musicVolume_bar.pageDown();
            sys.musicVolume = musicVolume_bar.state()/100.0f; 
            setMusicVolume(sys.musicVolume);
            ss.playsound(8);
        }
        if (musicVolume_bar.isPointerOnPrevpage(mx, my)){
            musicVolume_bar.pageUp();
            sys.musicVolume = musicVolume_bar.state()/100.0f; 
           setMusicVolume(sys.musicVolume);
            ss.playsound(8);
            
        }
        if (sfxVolume_bar.isPointerOnNextpage(mx, my)){
            sfxVolume_bar.pageDown();
            sys.sfxVolume = sfxVolume_bar.state()/100.0f; 
            ss.setVolume(sys.sfxVolume);
            ss.playsound(8);
        }
        if (sfxVolume_bar.isPointerOnPrevpage(mx, my)){
            sfxVolume_bar.pageUp();
            sys.sfxVolume = sfxVolume_bar.state()/100.0f; 
            ss.setVolume(sys.sfxVolume);
            ss.playsound(8);
            
        }
        
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        if (accel_bar.isPointerOnNextpage(mx, my)){
            accel_bar.pageDown();
            sys.accelerometerMultiplier = accel_bar.state() / 100.0f;
            ss.playsound(8);
        }
        if (accel_bar.isPointerOnPrevpage(mx, my)){
            accel_bar.pageUp();
            sys.accelerometerMultiplier = accel_bar.state() / 100.0f;
            ss.playsound(8);
        }
#endif
    }
    if (touches.move.count()){
        musicVolume_bar.processInput(touches.move[0].v[0], touches.move[0].v[1]);
        sfxVolume_bar.processInput(touches.move[0].v[0], touches.move[0].v[1]);
        sys.musicVolume = musicVolume_bar.state()/100.0f;
        sys.sfxVolume = sfxVolume_bar.state()/100.0f;
        setMusicVolume(sys.musicVolume);
        ss.setVolume(sys.sfxVolume);

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        accel_bar.processInput(touches.move[0].v[0], touches.move[0].v[1]);
        sys.accelerometerMultiplier = accel_bar.state() / 100.0f;
#endif
    }
    if (touches.down.count()){
        musicVolume_bar.processInput(touches.down[0].v[0], touches.down[0].v[1]);
        sfxVolume_bar.processInput(touches.down[0].v[0], touches.down[0].v[1]);
        sys.musicVolume = musicVolume_bar.state()/100.0f; 
        sys.sfxVolume = sfxVolume_bar.state()/100.0f;
        ss.setVolume(sys.sfxVolume);
        setMusicVolume(sys.musicVolume);

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        accel_bar.processInput(touches.down[0].v[0], touches.down[0].v[1]);
        sys.accelerometerMultiplier = accel_bar.state() / 100.0f;
#endif
    }
}

//------------------------
void Singleton::drawHighScore(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    COLOR bgColor = COLOR(0.5f, 0.5f, 0.5f, 0.6f);
    
    pics.draw(GUI, 0, 58, 0, false, 40/64.0f, 212/64.0f, 0 , bgColor, bgColor); 
    pics.draw(-1, 40, 58, 0, false, 400, 212, 0 , bgColor, bgColor); 
    pics.draw(GUI, 440, 58, 1, false, 40/64.0f, 212/64.0f, 0 , bgColor, bgColor); 
    
    highScoresBack_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    
    COLOR pressed = COLOR(1.0, 1.0, 1.0);
    COLOR notPressed = COLOR(0.5, 0.5, 0.5);
  
#ifndef LITE
    if (randomHighscore_button.pressed){
        randomHighscore_button.c = bgColor;
        randomHighscore_button.draw(pics, GUI, 2);
        randomHighscore_button.c = pressed;
    }
    else
        randomHighscore_button.c = notPressed;
    
    randomHighscore_button.draw(pics, MENU, 1);
    
    if ((randomHighscore_button.pressed)||(regularHighscore_button.pressed)){
        if (onlineScorePage > 0)
            onlineScorePage_button.drawTextnPicture(pics, 7, BUTTONS, 0, "<11");
        else
            onlineScorePage_button.drawTextnPicture(pics, 7, BUTTONS, 0, ">10");
    }
#endif
    
    if (regularHighscore_button.pressed){
        regularHighscore_button.c = bgColor;
        regularHighscore_button.draw(pics, GUI, 2);
        regularHighscore_button.c = pressed;
    }
    else
        regularHighscore_button.c = notPressed;
    regularHighscore_button.draw(pics, MENU, 0);
    
#ifndef LITE
    if (onlineScore_button.pressed){
        onlineScore_button.c = bgColor;
        onlineScore_button.draw(pics, GUI, 3);
        onlineScore_button.c = pressed;
    }
    else
        onlineScore_button.c = notPressed;
    
    onlineScore_button.draw(pics, MENU, 6);
    
    if (localScore_button.pressed){
        localScore_button.c = bgColor;
        localScore_button.draw(pics, GUI, 3);
        localScore_button.c = pressed;
    }
    else
        localScore_button.c = notPressed;
    localScore_button.draw(pics, MENU, 7);
    
#endif
    
    int scorePosY = 75;
    
    if (regularHighscore_button.pressed){
        if (localScore_button.pressed)
            highscoresRegular.display(pics, 0, 15, 10, scorePosY);
#ifndef LITE
        else{
            if (onlineScoreRegular.count())
                onlineScoreRegular.display(pics, 0, 15, 10, scorePosY, (onlineScorePage)? 11 : 1);
            
            if (strlen(highScoreFromServer) < 1){
                if (!failToGetScore)
                    WriteShadedText(200, 150, pics, 0, "Loading...");
                else {
                    WriteShadedText(100, 150, pics, 0, "Could not connect server :(");
                }

            }
        }
#endif
    }
    
    if (randomHighscore_button.pressed){
        if (localScore_button.pressed)
            highscoresRandom.display(pics, 0, 15, 10, scorePosY);
#ifndef LITE
        else{
            if (onlineScoreRandom.count())
                onlineScoreRandom.display(pics, 0, 15, 10, scorePosY, (onlineScorePage)? 11 : 1);
            
            if (strlen(highScoreFromServer) < 1){
                if (!failToGetScore)
                    WriteShadedText(200, 150, pics, 0, "Loading...");
                else {
                    WriteShadedText(100, 150, pics, 0, "Could not connect server :(");
                }
                
            }
            
        }
#endif
    }
#ifndef LITE    
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    GameCenter_button.draw(pics, BUTTONS, 12);
#endif
#endif
    

    if (!onlineScore_button.pressed)
        resetScore_button.drawTextnPicture(pics, 7, BUTTONS, 0, "reset");
    
    if (YesNoDlg.active())
        YesNoDlg.draw(pics, 0, GUI, BUTTONS, 7);
    
  
}
//-------------------------
void Singleton::runLevel(int lev){
    if (!levellist.get(lev)->locked){
        player.setLevel((unsigned)lev);
        
        levellist.loadLevel(player.level(), level, myArmy);  
        playNewSong(level.musicPath);
        AttachDefaultEntitySounds();
        
        
        
        fadeOut = false;
        alpha = 0.0f;
        player.resetLives();
        player.resetScore();
        gamestate = GAME;
        if (myArmy.count())
            myArmy.getRobot(0)->bombs = 5;
        levelCreated = true;
        
        
        time(&levelStart);
        suspendDuration = 0;
        scoreBefore = 0;
        livesBefore = player.lives();
        bombsUsed = 0;
        jumps = 0;
    }
}

//------------------------
void Singleton::levelListLogic(){
    
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

    if ((!Keys[7])&&(OldKeys[7])){

        ss.playsound(8);
#ifdef LITE
        gamestate = TITLE;
#else
        gamestate = SELECTGAME;
#endif

    }


    if (((!Keys[0])&&(OldKeys[0]))||
            ((!Keys[8])&&(OldKeys[8]))){

        ss.playsound(8);
        if (TouchedLevelindex > 0){
            TouchedLevelindex--;

            levellist.y = (TouchedLevelindex > (int)levellist.count()-4)?
                          -80 + (-80 * (levellist.count()-4 - 1)) :
                          (TouchedLevelindex < 3)? 0 : 80 +(-80 * (TouchedLevelindex - 1));
            
        }
    }

    if (((!Keys[1])&&(OldKeys[1]))||
            ((!Keys[9])&&(OldKeys[9]))){
        
        ss.playsound(8);
      
        if (TouchedLevelindex < (int)levellist.count()-1){
            TouchedLevelindex++;
            levellist.y = (TouchedLevelindex > (int)levellist.count()-4)?
                          -80 + (-80 * (levellist.count()-4 - 1)) :
                         (TouchedLevelindex < 3)? 0 : 80 +(-80 * (TouchedLevelindex - 1));

        }

    }
    if ((!Keys[5])&&(OldKeys[5])){

        runLevel(levellist.firstToShow + TouchedLevelindex);
    }
    
#endif

    if ((touches.up.count())&&(!touches.down.count())&&(!touches.move.count())){
        
        Vector3D tmp = oldMoveTouch;
        oldMoveTouch = Vector3D(-1,-1,0);
        
        
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (YesNoDlg.active()){
            if (YesNoDlg.isPointerOnYes(mx, my)){
                levellist.destroy();
                levellist.load("data/levels/list.xml");
                char megabuf[255];
                sprintf(megabuf, "%s/list.xml", DocumentPath);
                
#ifdef LITE
                if (levellist.count() > 8){
                    for (unsigned i = levellist.count()-1; i > 7; i--) {
                        levellist.remove(i);
                    }
                }
#endif
                
                levellist.write(megabuf);
                YesNoDlg.deactivate();
                ss.playsound(8);
            }
            if (YesNoDlg.isPointerOnNo(mx, my)){
                ss.playsound(8);
                YesNoDlg.deactivate();
            }
            
            return;
        }
        
        if (backLevels_button.isPointerOnTop(mx, my)){
            backLevels_button.c =  COLOR(0.5f, 0.5f, 0.5f);
            ss.playsound(8);
#ifdef LITE
            gamestate = TITLE;
#else
            gamestate = SELECTGAME;
#endif
        }
            
        if (resetLevel_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            YesNoDlg.activate();
        }
        //printf("cnt %f %f (%f %f)\n", mx, my, oldTouchDown.v[0], oldTouchDown.v[1]);
        float interval = 10.0f;
        if ((mx < oldTouchDown.v[0] + interval)&&
            (mx > oldTouchDown.v[0] - interval)&&
            (my < oldTouchDown.v[1] + interval)&&
            (my > oldTouchDown.v[1] - interval)){
            //puts("poom");
            if (( mx > 100 ) && ( mx < 420) && (my > 10)){
                //TouchedLevelindex = (my - levellist.y) / 80;
                ss.playsound(8);
                runLevel((my - levellist.y) / 80);
            }
        }
        else{
            Vector3D m = touches.up[0];
            Vector3D diff;
            if (!menumoved){
             //   diff = m - oldTouchDown;
             //   puts("swipe");
            }
            else{
                diff = m - tmp;
                //puts("drag");
            }
            //printf("cnt %f %f (%f %f)\n", mx, my, tmp.v[0], tmp.v[1]);    
            int minY = 300 - 80*(levellist.count());
            
            if (levellist.y + diff.v[1] > 10)
                levellist.y = 10;
            else 
                if (levellist.y + diff.v[1] < minY)
                    levellist.y = minY;
                    else
                        levellist.y = levellist.y + diff.v[1];
           
        }
        menumoved = false;
        TouchedLevelindex = -1;
    }
    //menumoved = false;
    if (touches.move.count()){
        Vector3D m = touches.move[0];
        
        if (( m.v[0] > 100 ) && ( m.v[0] < 420) && (m.v[1] > 10)){
        
            if (oldMoveTouch.v[0] > -1){
                Vector3D diff = m - oldMoveTouch;
                menumoved = true;
                
                int minY = 300 - 80*(levellist.count());
                if (levellist.y + diff.v[1] > 10)
                    levellist.y = 10;
                else 
                    if (levellist.y + diff.v[1] < minY)
                        levellist.y = minY;
                        else
                            levellist.y = levellist.y + diff.v[1];
            }
        
            oldMoveTouch = touches.move[0];
        }
        //oldTouchDown = touches.move[0];
        
        
    }
    
    if (touches.allfingersup){
        backLevels_button.c =  COLOR(0.5f, 0.5f, 0.5f);
    }
    
    if (touches.down.count()){
        float mx = touches.down[0].v[0];
        float my = touches.down[0].v[1];
        
        if (backLevels_button.isPointerOnTop(mx, my)){
            backLevels_button.c = COLOR(0.3f, 0.3f, 0.3f);
        }
        
        if (( mx > 100 ) && ( mx < 420) && (my > 10)){
            TouchedLevelindex = (my - levellist.y) / 80;     
            oldTouchDown = touches.down[0];
        }
    }
}
//-------------------------
void Singleton::drawLevelList(){
    
    COLOR normalPanel(0.5f, 0.5f, 0.5f, 0.5f);
    COLOR bar(0.8f, 0.8f, 0.8f, 0.7f);
    COLOR darkPanel(0.2f, 0.2f, 0.2f, 0.4f);
    
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    
    resetLevel_button.drawTextnPicture(pics,7, BUTTONS, 0, "reset");
    
    backLevels_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    
    
    float height = 300.0f;
    
    //float barheight = (me.differentFishCount()<= 3)?200.0f : (200.0f/100.0f) * (3.8f/(me.differentFishCount()/100.0f));
    //float barY = 50+(100-Rest_FishArea.getY())/(((me.differentFishCount())*50.0f)/200.0f);

    
    float barheight = ((80*4.2f)/((levellist.count()*80)/100.0f))*3.0f;
    //int minY = 300 - 80*(levellist.count());
    float barpos = (10 - levellist.y) / ((levellist.count()*80)/(300 - ((80*4.0f)/((levellist.count()*80)/100.0f))));
    pics.draw(-1, 460, 10, 0, false, 10, height, 0, normalPanel, normalPanel);
    pics.draw(-1, 460, 10 + barpos, 0, false, 10, barheight, 0, bar, bar);
    
    int panelX = 100;
    //Yeah, I guess it's strange, but i'm saving draw calls :)
    for (unsigned long i = 0; i < levellist.count(); i++){
        if (((i * 80 + 80 + levellist.y > 0) || (i * 80 + levellist.y < 320))){
            COLOR bgColor = normalPanel;
            if (TouchedLevelindex == (int)i)
                bgColor = darkPanel;
            int _y = i * 80;
            pics.draw(-1, panelX + 20, levellist.y + _y, 0, false, 300, 78, 0 , bgColor, bgColor); 
        }
    }
    for (unsigned long i = 0; i < levellist.count(); i++){
        
        LevelDescription * d = 0;
        d = levellist.get(i);
        if ((d) && ((i * 80 + 80 + levellist.y > 0) || (i * 80 + levellist.y < 320))){
            COLOR bgColor = normalPanel;
            
            if (TouchedLevelindex == (int)i)
                bgColor = darkPanel;
            int _y = i * 80;
            pics.draw(GUI, panelX,  levellist.y + _y, 0, false, 20/64.0f, 78/64.0f, 0 , bgColor, bgColor); 
            pics.draw(GUI, panelX + 20 + 300, levellist.y + _y, 1, false, 20/64.0f, 78/64.0f, 0 , bgColor, bgColor);
            if (d->locked){
                pics.draw(GUI, panelX + 25, levellist.y + 30 + _y, 4, false, 0.5f, 0.5f);
            }
        }
    }
    
    for (unsigned long i = 0; i < levellist.count(); i++){
        LevelDescription * d = 0;
        d = levellist.get(i);
        
        if ((d) && ((i * 80 + 80 + levellist.y > 0) || (i * 80 + levellist.y < 320))){
            COLOR textColor = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
            
            if (TouchedLevelindex == (int)i)
                textColor = COLOR(0.6f, 0.6f, 0.6f, 1.0f);
            
            int _y = i * 80;
            int nameX = 250 - ((strlen(d->name) * 13.2f)/2);
            WriteShadedText(nameX, levellist.y + 30 + _y, pics, 0, d->name, 1.2f, 1.2f, textColor, textColor);
            char buf[100];
            sprintf(buf, "Level %lu", i+1);
            WriteShadedText(panelX + 10, levellist.y + 15 + _y, pics, 0, buf, 0.8f, 0.8f, textColor, textColor);
        }
    }
    if (YesNoDlg.active())
        YesNoDlg.draw(pics, 0, GUI, BUTTONS, 7);
}
//---------------------------
void Singleton::drawJoystick(){
    pics.draw(BUTTONS, joystick.pos.v[0], joystick.pos.v[1], 4, true,
              (joystick.radius * 2) /64.0f, (joystick.radius * 2)/64.0f, 0, COLOR(1,1,1,0.6f), COLOR(1,1,1,0.6f));
    pics.draw(BUTTONS, pos.v[0], pos.v[1], 5, true,
              38/64.0f, 38/64.0f, 0,
              COLOR(1.0f, 1.0f, 1.0f, 0.9f),
              COLOR(1.0f, 1.0f, 1.0f, 0.9f) );
}
//----------------------------
void Singleton::drawBombButton(){
    if (delayBetweenBombs < ticsBeforeNextBomb){
        char buf[50];
        sprintf(buf, "%ld", (ticsBeforeNextBomb - delayBetweenBombs)/100);
        bomb_button.draw(pics, BUTTONS);
        WriteText(bomb_button.getX() + 23,
                  bomb_button.getY() + 23, pics, 0, buf, 1, 1, COLOR(0,0,0), COLOR(0,0,0));
    }
    else
        bomb_button.draw(pics, BUTTONS, 6);
}

//----------------------
void Singleton::drawGame(){
    
    Robot * r = myArmy.getRobot(0);
    
    pics.draw(level.backgroundPicIndex - 6, 240, 160, 0, true, 1.0f, 1.0f, 0,
              COLOR(alpha, alpha, alpha, 1.0f),
              COLOR(alpha, alpha, alpha, 1.0f)
              );
    level.draw(pics, 2, 240 - r->pos.v[0], 160 - r->pos.v[1], alpha);
    myArmy.draw(pics, 240 - r->pos.v[0],  160 - r->pos.v[1], alpha);
   

    if (r->bombs){
        for (int i = 0; i < r->bombs - 1; i++){
            pics.draw(6, 240 + i * 18, 16, 8, false, 0.5f, 0.5f);
        }
    }

    player.drawLives(pics, 6, 400, 20);

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    drawJoystick();
#endif
  
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    b.c = (b.pressed) ? COLOR(1,1,0,1) : COLOR(1,1,1,0.6f);
    b.draw(pics, BUTTONS, 1);
#endif

    toMainMenu_button.c = COLOR(1,1,1,0.6f);
    toMainMenu_button.draw(pics, BUTTONS, 10);

       
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (!CirclesColide(jump_button.getX()+jump_button.w()/2, jump_button.getY()+jump_button.h()/2,
                       jump_button.w()/2, 240, 160, 8))
        jump_button.draw(pics, BUTTONS, 11);
#endif

    player.drawScore(pics, 0, 400, 5);
    if (r->bombs){
        drawBombButton();
    }
    
       
    int massiItems = (int)r->mass;
    for (int i = 0; i < massiItems; i++)
        pics.draw(BUTTONS, 425, 200 - i*14, 7, false, 16/48.0f, 8/48.0f, 0,
                  COLOR(0,0.9,0,0.8), COLOR(0,0.5,0,0.7));
    int jumpItems = 0;
    if (r->maxJumpHeight > (16.0f * 1.9f))
        jumpItems = (int)((r->maxJumpHeight - (16.0f * 1.9f))/0.2f);
    for (int i = 0; i < jumpItems + 1; i++)
        pics.draw(BUTTONS, 450, 200 - i*14, 7, false, 16/48.0f, 8/48.0f, 0,
                  COLOR(1,0,0,0.8), COLOR(1,0,0,0.7));
    
    
    if ((levellist.count()) && (fadeOut == false) && (alpha < 1.0f)){
        float textX = 240 - strlen(levellist.get(player.level())->name)* 16.5f / 2.0f;
        
        WriteText(textX, 160, pics, 0, levellist.get(player.level())->name, 1.5f, 1.5f,
                  COLOR(1,1,1, 1.0f - alpha), COLOR(0.5f,0.5f,0.5f, 0.7f - (alpha - 0.3f)));
        if (level.gameType == 1)
            WriteText(240-110, 200, pics, 0, "Push everything off!", 1.0f, 1.0f,
                      COLOR(1,1,0, 1.0f - alpha), COLOR(0.5f,0.5f,0.5f, 0.7f - (alpha - 0.3f)));
    }

}
//-----------------------
void Singleton::drawHelp(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    pics.draw(MENU, 260, 8, 5, false, 0.7, 0.7);
    
    
    char pages[2][11][255] = 
                             {{"The main goal is to push all moving enemy",
                               "robots off the tiles to the bottomless pit.",
    #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
                               "Use touch-screen joystick or accelerometer to",
                               "control your robot.",
                               "Tap     to switch between the accelerometer",
                               "or the touch-screen.",
                               "Tap on     to jump. ",
   #else
                               "Use arrow keys on keyboard or gamepad",
                               "joystick to control your robot.",
                               " ",
                               "Press SPACE or first gamepad button",
                               "to jump. ",
    #endif
                               "When you land on on a tile, it will crackle.",
                               "Landing on it second time might completely" ,
                               "brake it. Whatch out, because you can fall in",
                               "through the hole."
    
                               },
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)         
                              {"Also you can use bombs. Tap    to lay a ",
                               "bomb. After some time bomb will detonate",
#else
                              {"Also you can use bombs. Press Left CTRL to lay",
                               "a bomb. After some time bomb will detonate",
#endif
                               
                               "and blast wave will push all enemies that",
                               "were near the center of explosion.",
                               "Be careful, if you will stand in the way of",
                               "the explosion, you will be swept away too.",
                               "After pushing off a crystal, a power-up ",
                               "will fall down ", 
                               "Possible power-ups:",
                               "  +1 to robot mass      +1 extra bomb",
                               "  +1 to jump height "
                                  
                                  
                              }};
    
    COLOR bgColor = COLOR(0.5f, 0.5f, 0.5f, 0.5f);
    pics.draw(-1, 80, 50, 0, false, 320, 259, 0, bgColor, bgColor);
    pics.draw(GUI, 0, 50, 0, false, 80/64.0f, 260/64.0f, 0, bgColor, bgColor);
    pics.draw(GUI, 400, 50, 1, false, 80/64.0f, 260/64.0f, 0, bgColor, bgColor);
    
    
    
    switch(helpPage){
            //                                                                              |
        case 0:{
            
            for (unsigned i = 0; i < 11; i++){
                WriteShadedText(10, 60+i*20, pics, 0,  pages[0][i], 0.9f, 0.9f);
            }
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            pics.draw(BUTTONS, 64, 150, 1, true, 0.5f, 0.5f);
            pics.draw(BUTTONS, 98, 192, 11, true, 0.5f, 0.5f);
#endif
           
        }break;
        case 1:{
            for (unsigned i = 0; i < 11; i++){
                WriteShadedText(10, 60+i*20, pics, 0,  pages[1][i], 0.9f, 0.9f);
            }
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            pics.draw(BUTTONS, 297, 70, 6, true, 0.5f, 0.5f);
#endif
           
            pics.draw(6, 20, 250, 4, true, 0.7f, 0.7f);
            pics.draw(6, 220, 250, 5, true, 0.7f, 0.7f);
           
            pics.draw(6, 20, 275, 6, true, 0.7f, 0.7f);
        }break;
    }
    
    helpBack_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    helpPrev_button.draw(pics, BUTTONS, 8);
    helpNext_button.draw(pics, BUTTONS, 9);
 
}
//-----------------------
void Singleton::drawOptions(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    backOptions_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    
    pics.draw(MENU, 280, 10, 4, false, 0.8, 0.8);
    COLOR bgColor = COLOR(0.5f, 0.5f, 0.5f, 0.5f);
    
    int panelHeight = 250;
    
    pics.draw(-1, 80, 60, 0, false, 320, panelHeight, 0, bgColor, bgColor);
    pics.draw(GUI, 20, 60, 0, false, 
              60/64.0f, panelHeight/64.0f, 0, bgColor, bgColor);
    pics.draw(GUI, 400, 60, 1, false, 
              60/64.0f, panelHeight/64.0f, 0, bgColor, bgColor);
    
    WriteShadedText(100, 80, pics, 0, "Touch-screen controls");
    controlsOptions_button.drawTextnPicture(pics, 7, BUTTONS, 0, "config");
    WriteShadedText(100, 120, pics, 0, "Music volume:");
    musicVolume_bar.draw(pics, BUTTONS, 8, 9);
    WriteShadedText(100, 180, pics, 0, "Sfx volume:");
    sfxVolume_bar.draw(pics, BUTTONS, 8, 9);

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    WriteShadedText(100, 240, pics, 0, "Accelerometer sensitivity:");
    accel_bar.draw(pics, BUTTONS, 8, 9);
#endif
    
}
//-----------------------------
void Singleton::drawControlsConfig(){
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    Robot * r = tmpArmy.getRobot(0);
    tmplevel.draw(pics, 2, 240 - r->pos.v[0], 160 - r->pos.v[1], 0.4f);
    tmpArmy.draw(pics, 240 - r->pos.v[0],  160 - r->pos.v[1], 0.4f);
#endif
    backControls_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    controlsReset_button.drawTextnPicture(pics, 7, BUTTONS, 0, "reset");
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
   
    
    drawJoystick();
    
    bomb_button.draw(pics, BUTTONS, 6);
    
    if (CirclesColide(jump_button.getX()+jump_button.w()/2, jump_button.getY()+jump_button.h()/2,
                      jump_button.w()/2, 240, 160, 8)){
        jump_button.c = COLOR(1.0f,1.0f,1.0f,0.7f);
        jump_button.draw(pics, BUTTONS, 0);
    }
    else{
        jump_button.draw(pics, BUTTONS, 11);
        jump_button.c = COLOR(1.0f,1.0f,1.0f,1.0f);
    }
    
    toMainMenu_button.draw(pics, BUTTONS, 10);
    WriteShadedText(100, 10, pics, 0, "Drag buttons and place them",0.9f);
    WriteShadedText(180, 30, pics, 0, "wherever you want",0.9f);
    WriteShadedText(joystick.pos.v[0], joystick.pos.v[1],
                    pics, 0, "Joystick", 0.6);
    WriteShadedText(bomb_button.getX(), bomb_button.getY()+bomb_button.h()-10,
                    pics, 0, "Lay bombs", 0.6);
    WriteShadedText(jump_button.getX(), jump_button.getY()+jump_button.h()-10,
                    pics, 0, "Jump", 0.6);
    WriteShadedText(toMainMenu_button.getX(), toMainMenu_button.getY()+toMainMenu_button.h()-10,
                    pics, 0, "Pause", 0.6);
    
    
#endif
  
}
//-----------------------------
void Singleton::controlsConfigLogic(){
    
    pos.v[0] = joystick.pos.v[0];
    pos.v[1] = joystick.pos.v[1]; 
    if ((touches.up.count())&&(!touches.down.count())){
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        if (backControls_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            gamestate = OPTIONS;
            tmplevel.destroy();
            tmpArmy.destroy();
            sys.joystick = joystick.pos;
            sys.pauseButton = Vector3D(toMainMenu_button.getX(), toMainMenu_button.getY(), 0);
            sys.bombButton = Vector3D(bomb_button.getX(), bomb_button.getY(), 0);
            sys.jumpButton = Vector3D(jump_button.getX(), jump_button.getY(), 0);
        }
        
        if (controlsReset_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            sys.joystick = Vector3D(70, 250, 0);
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            sys.pauseButton = Vector3D(15, 64, 0);
#else
            sys.pauseButton = Vector3D(15, 5, 0);
#endif
            sys.jumpButton = initialJumpButtonPos;
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
            sys.bombButton = initialBombButtonPos;
#else
            sys.bombButton = initialBombButtonPosPC;
#endif

            joystick.pos = sys.joystick;
            toMainMenu_button.setpos(sys.pauseButton.v[0], sys.pauseButton.v[1]);
            bomb_button.setpos(sys.bombButton.v[0], sys.bombButton.v[1]);
            jump_button.setpos(sys.jumpButton.v[0], sys.jumpButton.v[1]);
        }
        
        dragBombButton = false;
        dragJumpButton = false;
        dragJoystick = false;
        dragPauseButton = false;
    }
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (touches.down.count()){
        int mx = touches.down[0].v[0];
        int my = touches.down[0].v[1];
        if (bomb_button.isPointerOnTop(mx, my)){
            dragBombButton = true;
            dragJoystick = false;
            dragJumpButton = false;
            dragPauseButton = false;
        }
        if (jump_button.isPointerOnTop(mx, my)){
            dragJumpButton = true;
            dragBombButton = false;
            dragJoystick = false;
            dragPauseButton = false;
        }
        if (toMainMenu_button.isPointerOnTop(mx, my)){
            dragPauseButton = true;
            dragJumpButton = false;
            dragBombButton = false;
            dragJoystick = false;
        }
        Vector3D result = touches.down[0] - joystick.pos;
        if ( result.length() <= joystick.radius){
            dragJoystick = true;
            dragBombButton = false;
            dragPauseButton = false;
            dragJumpButton = false;
            
        }
    }
    if (touches.move.count()){
        int mx = touches.move[0].v[0];
        int my = touches.move[0].v[1];
        if (bomb_button.isPointerOnTop(mx, my)){
            dragBombButton = true;
        }
        if (jump_button.isPointerOnTop(mx, my)){
            dragJumpButton = true;
        }
        
        Vector3D result = touches.move[0] - joystick.pos;
        if ( result.length() <= joystick.radius){
            dragJoystick = true;
        }
        if (toMainMenu_button.isPointerOnTop(mx, my)){
            dragPauseButton = true;
        }
        
        if (dragBombButton){
            bomb_button.setpos(mx-bomb_button.w()/2, my-bomb_button.h()/2);
        }
        if (dragPauseButton){
            toMainMenu_button.setpos(mx-toMainMenu_button.w()/2, my-toMainMenu_button.h()/2);
        }
        
        if (dragJumpButton){
            int newx = mx-jump_button.w()/2;
            int newy =  my-jump_button.h()/2;
            if ((newx > 225 - jump_button.w()/2)&&(newx < 255 - jump_button.w()/2)
                &&(newy > 145 - jump_button.h()/2)&&(newy < 175 - jump_button.h()/2 )){
                newx = 240 - jump_button.w()/2;
                newy = 160 - jump_button.h()/2;
               
            }
            
            jump_button.setpos(newx, newy);
        }
        if (dragJoystick){
            joystick.pos = Vector3D(mx, my, 0);
        }
        
    }
#endif
}

//---------------------
void Singleton::aboutLogic(){
    if ((touches.up.count())&&(!touches.down.count())){
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        ss.playsound(8);
        
        
        about_button.pressed = false;
        about_button.c = COLOR(0.3f, 0.5f, 1.0f, 0.9f);
        
        if (jrs0ul_button.isPointerOnTop(mx, my))
            launchjrs0ul = true;
        
        else
            gamestate = TITLE;
       
    }
}


//---------------------
void Singleton::drawAbout(){
    
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    COLOR bgColor = COLOR(0.5f, 0.5f, 0.5f, 0.8f);
    pics.draw(-1, 80, 80, 0, false, 320, 190, 0, bgColor, bgColor);
    pics.draw(GUI, 20, 80, 0, false, 60/64.0f, 190/64.0f, 0, bgColor, bgColor);
    pics.draw(GUI, 400, 80, 1, false, 60/64.0f, 190/64.0f, 0, bgColor, bgColor);
    
    WriteShadedText(240 - 154, 90, pics, 0, "Code, graphics, music, etc.");
    WriteShadedText(240 - 55, 120, pics, 0, "by jrs0ul");
    WriteShadedText(240 - 88, 160, pics, 0, "MORE GAMES...", 1.0f, 1.0f, COLOR(0,0,1));
    WriteShadedText(240 - 93, 165, pics, 0, "________________", 1.0f, 1.0f, COLOR(0,0,1));
    WriteShadedText(240 - 55, 200, pics, 0, "2010-2011");
    
    WriteShadedText(240 - 100, 240, pics, 0, "tap anywhere to continue...", 0.8f, 0.8f);
    
  
}
//-----------------------
void Singleton::drawWellDone(){
    pics.draw(THEEND, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f); 
#ifndef LITE
    WriteShadedText(240 - 124, 100, pics, 0, "GOOD JOB, you made it !", 1.0f, 1.0f);
#endif
}

//-------------------
void Singleton::drawSelectGame(){
    pics.draw(BG, 0, 0, 0, false, 480.0f/512.0f, 320.0f/256.0f);
    selectGameBack_button.drawTextnPicture(pics, 7, BUTTONS, 0, "back");
    
    playregular_button.draw(pics, THEEND+1, 0);
    playrandom_button.draw(pics, THEEND+1, 1);
    pics.draw(MENU, playregular_button.getX(), playregular_button.getY()+120,
              0, false, 0.5f, 0.5f);
    pics.draw(MENU, playrandom_button.getX(), playrandom_button.getY()+120,
              1, false, 0.5f, 0.5f);
    
}

//-------------------
void Singleton::wellDoneLogic(){
    if ((touches.up.count())&&(!touches.down.count())){
        
        
#ifndef LITE        
        submitOnline = true;
        addScore();
        gamestate = HIGHSCORE;
        ss.playsound(8);
        levelCreated = false;
#else
        Button meh;
        Button getIT;
        
        meh.set(17, 260, 140, 60);
        getIT.set(300,240,160, 75);
        
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (meh.isPointerOnTop(mx, my)){
           
            addScore();
            gamestate = HIGHSCORE;
            
            ss.playsound(8);            
            levelCreated = false;
        }
        if (getIT.isPointerOnTop(mx, my)){
            buyGame = true;
        }
        
#endif
    }
}
//----------------
void Singleton::drawDebugText(){
    char buf[50];
    sprintf(buf, "draw calls %d", drawCalls);
    WriteShadedText(5, 5, pics, 0, buf, 0.8f, 0.8f, COLOR(1,0,0), COLOR(1,0,0));
    sprintf(buf, "entities: %lu", myArmy.count());
    WriteShadedText(5, 15, pics, 0, buf, 0.8f, 0.8f, COLOR(1,0,0), COLOR(1,0,0));
    /*if (myArmy.count() > 0){
        for (unsigned i = 0; i < myArmy.count(); i++){
            Robot * r = myArmy.getRobot(i);
            sprintf(buf, "t: %u d: %d f: %d", r->face, r->dead, r->falling);
            WriteShadedText(5, i*15+30, pics, 0, buf, 0.8f, 0.8f, COLOR(1,0,0), COLOR(1,0,0));
        }
    }*/
}

//-------------------
void Singleton::render(){
    
   
    glClear(GL_COLOR_BUFFER_BIT);
    switch(gamestate){
        case TITLE : drawMainMenu(); break;
        case GAME : drawGame(); break;
        case HIGHSCORE : drawHighScore(); break;
        case LEVELLIST : drawLevelList(); break;
        case HELP : drawHelp(); break;
        case OPTIONS : drawOptions(); break;
        case ENTERNAME: drawEnterName(); break;
        case ABOUT: drawAbout(); break;
        case WELLDONE: drawWellDone(); break;
        case CONTROLCONFIG: drawControlsConfig(); break;
        case SELECTGAME: drawSelectGame(); break;
    }
    
    //drawDebugText();
    
    drawCalls = pics.drawBatch();
    
    
}
//----------------------
void Singleton::updateLevelList(){
    LevelList tmpList;
    tmpList.load("data/levels/list.xml");
    for (unsigned i = 0; i < tmpList.count(); i++){
        
        if (i < levellist.count()){
            strncpy(levellist.get(i)->path, tmpList.get(i)->path, 255);
            strncpy(levellist.get(i)->name, tmpList.get(i)->name, 50);
        }
        else{
            LevelDescription newlevel;
            newlevel.locked = true;
            strncpy(newlevel.path, tmpList.get(i)->path, 255);
            strncpy(newlevel.name, tmpList.get(i)->name, 50);
            levellist.add(newlevel);
        }
    }
    
#ifdef LITE
    if (levellist.count() > 8){
        for (unsigned i = levellist.count()-1; i > 7; i--) {
            levellist.remove(i);
        }
    }
#endif
    
    char megabuf[255];
    sprintf(megabuf, "%s/list.xml", DocumentPath);
    levellist.write(megabuf);
    
    tmpList.destroy();
}

//----------------------
void Singleton::PlayRegularGame(){
    
    char megabuf[255];
    sprintf(megabuf, "%s/list.xml", DocumentPath);
    
    if (!levellist.load(megabuf)){
        levellist.load("data/levels/list.xml");
#ifdef LITE
        if (levellist.count() > 8){
            for (unsigned i = levellist.count()-1; i > 7; i--) {
                levellist.remove(i);
            }
        }
#endif
        levellist.write(megabuf);
    }
    else{
        updateLevelList();
    }

    gamestate = LEVELLIST;
}
//----------------------
void Singleton::PlayRandomGame(){
    gamestate = GAME;
    levelCreated = true;
    levellist.destroy();
    myArmy.destroy();
    level.destroy();
    level.generate();
    myArmy.create(level);
    AttachDefaultEntitySounds();
    
    fadeOut = false;
    alpha = 0.0f;
    myArmy.getRobot(0)->bombs = 5;
    player.resetLives();
    player.resetScore();
}

//-----------------------
void Singleton::handleMainMenuWithKeyboard(){
    float shrink = 0.93f;
    COLOR dark = COLOR(0.6f, 0.6f, 0.6f);
    COLOR white = COLOR(1.0f, 1.0f, 1.0f);


    if ((!Keys[7])&&(OldKeys[7]))
        Exit = true;

    if (((!Keys[0])&&(OldKeys[0]))||
            ((!Keys[8])&&(OldKeys[8]))){
        //puts("up");
        touches.allfingersup = false;
        ss.playsound(8);
        activeMenuItem--;
        if (activeMenuItem < ((levelCreated)? 0 : 1))
            activeMenuItem = 4;
        switch(activeMenuItem){
            case 0:{
                    play_button.c = white;
                    play_button.scalex = 1.0f;
                    resume_button.c = dark;
                    resume_button.scalex = shrink;
                   }break;
            case 1:{
                    highscore_button.c = white;
                    highscore_button.scalex = 1.0f;
                    play_button.c = dark;
                    play_button.scalex = shrink;
                   }break;
            case 2:{
                    options_button.c = white;
                    options_button.scalex = 1.0f;
                    highscore_button.c = dark;
                    highscore_button.scalex = shrink;
                   }break;
            case 3:{
                    howtoplay_button.c = white;
                    howtoplay_button.scalex = 1.0f;
                    options_button.c = dark;
                    options_button.scalex = shrink;
                   }break;
            case 4:{

                    play_button.c = white;
                    play_button.scalex = 1.0f;
                    resume_button.c = white;
                    resume_button.scalex = 1.0f;
                    howtoplay_button.c = dark;
                    howtoplay_button.scalex = shrink;
                   }break;
        }

    }

    if (((!Keys[1])&&(OldKeys[1]))||
            ((!Keys[9])&&(OldKeys[9]))){
        //puts("down");

        touches.allfingersup = false;
        ss.playsound(8);
        activeMenuItem++;
        if (activeMenuItem > 4)
            activeMenuItem = (levelCreated)? 0 : 1;
        switch(activeMenuItem){
            case 0:{
                    howtoplay_button.c = white;
                    howtoplay_button.scalex = 1.0f;
                    resume_button.c = dark;
                    resume_button.scalex = shrink;
                   }break;
            case 1:{
                    howtoplay_button.c = white;
                    howtoplay_button.scalex = 1.0f;
                    resume_button.c = white;
                    resume_button.scalex = 1.0f;
                    play_button.c = dark;
                    play_button.scalex = shrink;
                   }break;
            case 2:{
                    play_button.c = white;
                    play_button.scalex = 1.0f;
                    highscore_button.c = dark;
                    highscore_button.scalex = shrink;
                   }break;
            case 3:{
                    highscore_button.c = white;
                    highscore_button.scalex = 1.0f;
                    options_button.c = dark;
                    options_button.scalex = shrink;
                   }break;
            case 4:{
                    options_button.c = white;
                    options_button.scalex = 1.0f;
                    howtoplay_button.c = dark;
                    howtoplay_button.scalex = shrink;
                   }break;
        }


    }

    if ((!Keys[5])&&(OldKeys[5])){
        ss.playsound(8);
        switch(activeMenuItem){
            case 0:{
                    gamestate = GAME;
                    time(&suspendEnd);
                    double diff = difftime(suspendEnd, suspendStart);
                    suspendDuration += diff;
                    printf("suspended for: %.0lf; total: %.0lf\n", diff, suspendDuration);

                   }break;
            case 1:{
#ifndef LITE
                    gamestate = SELECTGAME;
#else
                    PlayRegularGame();
#endif


                   }break;
            case 2:{
                    gamestate = HIGHSCORE;
#ifndef LITE
                    if (onlineScore_button.pressed){
                    if (regularHighscore_button.pressed)
                        fetchScore(0);
                    else 
                        fetchScore(1);

                    }
#endif
                    }break;
            case 3:{gamestate = OPTIONS;}break;
            case 4:{gamestate = HELP;}break;
        }
    }


}
//----------------------
void Singleton::mainMenuLogic(){
    
    float shrink = 0.93f;
    COLOR dark = COLOR(0.6f, 0.6f, 0.6f);
    COLOR white = COLOR(1.0f, 1.0f, 1.0f);
    
    if (strlen(nameToEnter) < 1){
        gamestate = ENTERNAME;
        ActivateEditField = true;
        return;
    }
    if (strlen(nameToEnter) > 11){
        puts(nameToEnter);
        puts(sys.nameToEnter);
        nameToEnter[11]=0;
    
    }
if (touches.allfingersup){
        play_button.c = COLOR(1.0f, 1.0f, 1.0f);
        play_button.scalex = 1.0f;
        highscore_button.c = COLOR(1.0f, 1.0f, 1.0f);
        highscore_button.scalex = 1.0f;
        resume_button.c = COLOR(1.0f, 1.0f, 1.0f);
        resume_button.scalex = 1.0f;
        options_button.c = COLOR(1.0f, 1.0f, 1.0f);
        options_button.scalex = 1.0f;
        howtoplay_button.c = COLOR(1.0f, 1.0f, 1.0f);
        howtoplay_button.scalex = 1.0f;
}

//For PC
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
//printf("%d %d\n", Keys[0], OldKeys[0]);
   handleMainMenuWithKeyboard();    
#endif
    if (touches.down.count()){
        float x = touches.down[0].v[0];
        float y = touches.down[0].v[1];
        
        if (play_button.isPointerOnTop(x, y)){
            play_button.c = dark;
            play_button.scalex = shrink;
            ss.playsound(8);
        }
 
#ifndef LITE
        if (about_button.isPointerOnTop(x, y)){
            about_button.pressed = true;
            about_button.c = COLOR(0.4, 0.6, 1.0f, 0.9f);
        }
#else
        if (getfull_button.isPointerOnTop(x, y)){
            getfull_button.pressed = true;
        }   
#endif
        
        if (highscore_button.isPointerOnTop(x, y)){
            highscore_button.c = dark;
            highscore_button.scalex = shrink;
            ss.playsound(8);
        }

        if (levelCreated){
            if (resume_button.isPointerOnTop(x, y)){
                resume_button.c = dark;
                resume_button.scalex = shrink;
                ss.playsound(8);
            }
        }
        
        if (options_button.isPointerOnTop(x, y)){
            options_button.c = dark;
            options_button.scalex = shrink;
            ss.playsound(8);
        }
        
        if (howtoplay_button.isPointerOnTop(x, y)){
            howtoplay_button.c = dark;
            howtoplay_button.scalex = shrink;
            ss.playsound(8);
        }
        
    }
    
        
    if ((touches.up.count())&&(!touches.oldDown.count())){
        float x = touches.up[0].v[0];
        float y = touches.up[0].v[1];
        
        if (changeName_button.isPointerOnTop(x, y)){
            gamestate = ENTERNAME;
            ActivateEditField = true;
            ss.playsound(8);
        }
        
#ifndef LITE
        if (about_button.pressed){
            gamestate = ABOUT;
        }
#else
        if (getfull_button.pressed){
            buyGame = true;
        }
#endif
        
        play_button.c = COLOR(1.0f, 1.0f, 1.0f);
        play_button.scalex = 1.0f;
        highscore_button.c = COLOR(1.0f, 1.0f, 1.0f);
        highscore_button.scalex = 1.0f;
        resume_button.c = COLOR(1.0f, 1.0f, 1.0f);
        resume_button.scalex = 1.0f;
        options_button.c = COLOR(1.0f, 1.0f, 1.0f);
        options_button.scalex = 1.0f;
        howtoplay_button.c = COLOR(1.0f, 1.0f, 1.0f);
        howtoplay_button.scalex = 1.0f;
        
       
        
        if (play_button.isPointerOnTop(x, y)){
            play_button.c = COLOR(1.0f, 1.0f, 1.0f);
#ifndef LITE
            gamestate = SELECTGAME;
#else
            PlayRegularGame();
#endif
        }
        
        if (highscore_button.isPointerOnTop(x, y)){
            //highscore_button.c = COLOR(1.0f, 1.0f, 1.0f);
            gamestate = HIGHSCORE;
#ifndef LITE
            if (onlineScore_button.pressed){
                if (regularHighscore_button.pressed)
                    fetchScore(0);
                else 
                    fetchScore(1);

            }
#endif
        }

        
        if ((resume_button.isPointerOnTop(x, y))&&(levelCreated)){
            gamestate = GAME;
            time(&suspendEnd);
            double diff = difftime(suspendEnd, suspendStart);
            suspendDuration += diff;
            printf("suspended for: %.0lf; total: %.0lf\n", diff, suspendDuration);
        }
        
        if (options_button.isPointerOnTop(x, y)){
           
            gamestate = OPTIONS;
        }
        if (howtoplay_button.isPointerOnTop(x, y)){
            
            gamestate = HELP;
        }
       
    }
}
//------------------
void Singleton::ProcessTouchUp(Vector3D * touch){
    
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    Vector3D result = joystick.pos - (*touch);
    if ( result.length() <= joystick.radius){
        pos = joystick.pos;
        joyPressed = false;
    }       
#endif
    
    if (toMainMenu_button.isPointerOnTop( touch->v[0], touch->v[1])) {
        ss.playsound(8);
        gamestate = TITLE;
        time(&suspendStart);
    }
    
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (b.isPointerOnTop( touch->v[0], touch->v[1])) {
        b.shiftstate();
        ss.playsound(8);
        useAccel = b.pressed;
    }
#endif

}
//-------------------
void Singleton::ProcessTouchDown(Vector3D * touch){
   
    Robot *r = myArmy.getRobot(0);
    if (jump_button.isPointerOnTop(touch->v[0], touch->v[1])){
        if (r->pos.v[2] == 0.0f){
            r->jumping = true;
            r->playAttachedSound(2, ss.getVolume());
            jumps++;
        }
        return;
    }
    
    Vector3D result = (*touch) - joystick.pos;
    if ( result.length() <= joystick.radius){
        pos = (*touch);
        joyPressed = true;
    }
    else {
        if (joyPressed){
            result.normalize();
            pos = joystick.pos + Vector3D(result.v[0] * joystick.radius, result.v[1] * joystick.radius, 0);
            joyPressed = true;
        }
    }
    
}
//--------------------
void Singleton::ProcessTouchMove(Vector3D * touch){
    
    Vector3D result = (*touch) - joystick.pos ;
    Robot *r = myArmy.getRobot(0);
    if (jump_button.isPointerOnTop(touch->v[0], touch->v[1])){
        if (r->pos.v[2] == 0.0f){
            r->jumping = true;
            r->playAttachedSound(2, ss.getVolume());
        }
        return;
    }
    
    
    if ( result.length() <= joystick.radius){
        pos = *touch;
        joyPressed = true;
    }
    else {
        if (joyPressed){
            
            result.normalize();
            pos = joystick.pos + Vector3D(result.v[0] * joystick.radius, result.v[1] * joystick.radius, 0);
            joyPressed = true;
        }
    }
    
    
    if (bomb_button.isPointerOnTop(touch->v[0], touch->v[1])) {
        if (delayBetweenBombs >= ticsBeforeNextBomb)
            makeBomb();
    }
    
    
    
}
//-----------------------
void Singleton::makeBomb(){
    Robot * p = myArmy.getRobot(0);
    Robot bomb;
    Vector3D sDir = p->getSpriteDirection();
    Vector3D dir = sDir - sDir - sDir;
    bomb.pos = Vector3D(p->pos.v[0] + dir.v[0]* (p->radius + 10.0f),
                        p->pos.v[1] + dir.v[1] * (p->radius + 10.0f),
                        p->pos.v[2]);
    bomb.face = 11;
    bomb.startFrame = 8;
    bomb.speed = 0;
    bomb.dead = false;
    bomb.c = COLOR(1,1,1);
    bomb.radius = 9.0f;
    bomb.mass = initialBombMass;
    bomb.direction = Vector3D(0,0,0);
    bomb.jumping = false;
    bomb.hit = false;
    
    
    
    if (myArmy.isRobotColides(&bomb)){
        ss.playsound(5);
    }
    
    else{
        
        myArmy.add(bomb);
        ss.playsound(6);
        delayBetweenBombs = 0;
        bombsUsed++;
        p->bombs--;
        myArmy.getRobot(myArmy.count() - 1)->attachBuffer(ss, 0, 0);
        myArmy.getRobot(myArmy.count() - 1)->attachBuffer(ss, 1, 1);
        myArmy.getRobot(myArmy.count() - 1)->attachBuffer(ss, 2, 2);
    }
    
    
}

//----------------------
void Singleton::AttachDefaultEntitySounds(){
    for (unsigned long i = 0; i< myArmy.count(); i++){
        myArmy.getRobot(i)->attachBuffer(ss, 0, 0); //bump
        myArmy.getRobot(i)->attachBuffer(ss, 7, 4);
        if (!i){
            myArmy.getRobot(i)->attachBuffer(ss, 1, 1);//slap
            myArmy.getRobot(i)->attachBuffer(ss, 3, 2);//jump
            myArmy.getRobot(i)->attachBuffer(ss, 4, 3);//powerup
            
            
        }
    }
}
//------------------
void Singleton::GoToNextLevel(){
    
    if (levellist.count()){ //playing non-random levels ?
        player.incLevel();
        if (player.level() >= levellist.count()){//you beat the game
            gamestate = WELLDONE;
        }
        else{
            if (levellist.get(player.level())->locked){
                levellist.get(player.level())->locked  = false;
                char listbuf[255];
                sprintf(listbuf, "%s/list.xml", DocumentPath);
                levellist.write(listbuf);
            }
        }
        time(&levelEnd);
        double dif = difftime(levelEnd, levelStart);
        
        //printf("==WIN==level %s took: %.2lf secs, you get %ld pts, lost %d lives, bombs %d, jumps %d\n",
        //       levellist.get(player.level() - 1)->name,
        //       dif, player.score() - scoreBefore, livesBefore - player.lives(), bombsUsed, jumps);
        sprintf(statPostParams,"state=1&level=%s&score=%ld&lives=%d&time=%.2lf&jumps=%d&bombs=%d&ver=1.22&isLite=%d&pirate=%d&password=", 
                               levellist.get(player.level() - 1)->name, player.score() - scoreBefore,
                               livesBefore - player.lives(), dif - suspendDuration, jumps, bombsUsed,
#ifdef LITE
                               1
#else
                               0
#endif
                                , (isPirate)?1:0);
        sendStats = true;
        
        
        levellist.loadLevel(player.level(), level, myArmy);
        playNewSong(level.musicPath);
        AttachDefaultEntitySounds();
        
        time(&levelStart);
        suspendDuration = 0;
        scoreBefore = player.score();
        livesBefore = player.lives();
        bombsUsed = 0;
        jumps = 0;
    }
    else{ //random levels
        level.destroy();
        level.generate();
        myArmy.destroy();
        myArmy.create(level);
        AttachDefaultEntitySounds();
    }
}
//---------------------
void Singleton::throwPowerup(){
    Robot powerup;
    
    powerup.radius = 11.0f;
    unsigned _x = rand() % level.width;
    unsigned _y = rand() % level.height;
    while (level.map[_y][_x].picture == 0){
        _x = rand() % level.width;
        _y = rand() % level.height;
    }
    
    powerup.pos = Vector3D(_x * 32.0f + 16.0f,
                           _y * 32.0f + 16.0f,
                           50);
    powerup.face = 12;
    powerup.startFrame = 4;
    powerup.frame = rand() % 3;
    powerup.speed = 0;
    powerup.dead = false;
    powerup.c = COLOR(1,1,1);
    powerup.mass = powerupMass;
    powerup.direction = Vector3D(0,0,0);
    powerup.jumping = false;
    
    myArmy.add(powerup);
    
    
    myArmy.getRobot(myArmy.count() - 1)->attachBuffer(ss, 0, 0);
    myArmy.getRobot(myArmy.count() - 1)->attachBuffer(ss, 1, 1);  
}

//---------------------
void Singleton::gameLogic(){
    
    
    player.blinkLifeRoutine();
    
    if ((!fadeOut) && (alpha < 1.0f)){
        alpha += 0.007f;
    }
    if ((fadeOut) && (alpha > 0.0f)){
        alpha -= 0.01f;
        if (alpha <= 0.0f ){
            
            
            if (player.lives()<= 0){
                
                time(&levelEnd);
                double dif = difftime(levelEnd, levelStart);
                if (levellist.count()){
                    sprintf(statPostParams,"state=0&level=%s&score=%ld&lives=%d&time=%.2lf&jumps=%d&bombs=%d&ver=1.22&isLite=%d&pirate=%d&password=", 
                            levellist.get(player.level())->name, player.score() - scoreBefore,
                            livesBefore - player.lives(), dif - suspendDuration, jumps, bombsUsed,
#ifdef LITE
                            1
#else
                            0
#endif
                            , (isPirate)?1:0);
                    sendStats = true;
                }
                
                levelCreated = false;
#ifndef LITE
                submitOnline = true;
#else
                submitOnline = false;
#endif
                
                addScore();
                gamestate = HIGHSCORE;
                
                goToNextLevel = false;
            }
            else {
                if (goToNextLevel){
                    GoToNextLevel();
                    goToNextLevel = false;
                }
                else {
                    myArmy.respawn(0, level);
                }
            }
            fadeOut = false;
        }
    }
    //---
    if (alpha < 0.9f)
        return;
    Robot * r = myArmy.getRobot(0);
    //------------
    if (r->bombs){
        if (delayBetweenBombs < ticsBeforeNextBomb){
            delayBetweenBombs++;
        }
    }

    if (Keys[6])
        if (delayBetweenBombs >= ticsBeforeNextBomb)
            makeBomb();

    if (Keys[4]){
        if ((r->pos.v[2] == 0.0f)&&(!r->jumping)){
            r->jumping = true;
            jumps++;
            r->playAttachedSound(2, ss.getVolume());
        }
    }

    if ((!Keys[7])&&(OldKeys[7])){
        gamestate = TITLE;
        time(&suspendStart);
    }

    for (unsigned long i = 0; i < touches.up.count(); i++)
        ProcessTouchUp(&touches.up[i]);
    
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    for (unsigned long i = 0; i < touches.oldDown.count(); i++){
        
        if (bomb_button.isPointerOnTop(touches.oldDown[i].v[0], touches.oldDown[i].v[1])) {
            if (delayBetweenBombs >= ticsBeforeNextBomb)
                makeBomb();
        }
        
    }
    for (unsigned long i = 0; i < touches.move.count(); i++)
        ProcessTouchMove(&touches.move[i]);
          
    for (unsigned long i = 0; i < touches.down.count(); i++)
        ProcessTouchDown(&touches.down[i]);
     
    
    if (touches.allfingersup){
        joyPressed = false;
        pos = joystick.pos;
    }
#endif
    //----------
    Vector3D shift(0.0f, 0.0f, 0.0f);
    
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (useAccel){
        shift.v[0] += -accelerometer.v[1];
        shift.v[1] += -accelerometer.v[0];
    }
    else {
        shift = pos - joystick.pos;
    }
#endif


    //printf("%f \n", gamepad.v[0]);
    float maxPadValue = 40.0f;
    float minPadValue = 0.129f;
    shift.v[0] += (fabs(gamepad.v[0]) > maxPadValue)?
                  ((gamepad.v[0] > 0)? maxPadValue : -maxPadValue) :
                  ((fabs(gamepad.v[0]) < minPadValue)? 0  : gamepad.v[0]);

    shift.v[1] += (fabs(gamepad.v[1]) >maxPadValue)?
                 ((gamepad.v[1] > 0)? maxPadValue : -maxPadValue) :
                  ((fabs(gamepad.v[1]) < minPadValue)? 0 : gamepad.v[1]);

    if (Keys[0])
        shift.v[1] -= acc; 
    if (Keys[1])
        shift.v[1] += acc; 
    if (Keys[2])
        shift.v[0] -= acc; 
    if (Keys[3])
        shift.v[0] += acc; 
    
    
    float speedmultiplier = sys.accelerometerMultiplier;
    if (!useAccel)
        speedmultiplier = 0.01f;
    Vector3D dir = Vector3D(shift.v[0] * speedmultiplier,
                            shift.v[1] * speedmultiplier, 0);
    
    //printf("dir %f %f %f\n", dir.v[0], dir.v[1], dir.v[2]);
    if((dir.length())&&(!r->jumping)&&(!r->hit)){
        //printf("%f \n", dir.length());
        Vector3D sDir = dir;
        sDir.normalize();
        r->setSpriteDirection(sDir);
        
        r->direction = Vector3D(r->direction.v[0] * r->speed,
                                r->direction.v[1] * r->speed,
                                r->direction.v[2] * r->speed)
                                + dir;
        r->speed = (r->direction.length() > 2.5f) ? 2.5f : r->direction.length();
        r->direction.normalize();
    }
    
    unsigned long aliveBotsBefore[13] = {0};
    myArmy.howManyAlive(aliveBotsBefore);
    
    myArmy.react(level); //physics
    unsigned long aliveBotsAfter[13] = {0};
    myArmy.howManyAlive(aliveBotsAfter);
    
    if ((!myArmy.getRobot(0)->dead)&&(aliveBotsAfter[0] < aliveBotsBefore[0])){
        
        long oldScore = player.score();
        
        player.addScore(50);
    
        if (aliveBotsAfter[CRYSTAL] < aliveBotsBefore[CRYSTAL]){
            throwPowerup();      
            player.addScore(-20);
        }
        if (aliveBotsAfter[BOMB] < aliveBotsBefore[BOMB]){
            player.addScore(-50);
        }
        
        if ((oldScore < 1000)&&(player.score() >= 1000)){
            if (player.score() < 3000)
                player.addLife();
            puts("extra life");
        }
        
        if ((oldScore < 3000)&&(player.score() >= 3000)){
            if (player.score() < 6000)
                player.addLife();
            puts("extra life");
        }
        
        if ((oldScore < 6000)&&(player.score() >= 6000)){
            if (player.score() < 12000)
                player.addLife();
            puts("extra life");
        }
        
    }
    
    
    if ((myArmy.getRobot(0)->dead)&&(!fadeOut)){
        player.die();
        
        if (player.lives() > 0)
            fadeOut = true;
    }
    
    bool gameWon = (!level.gameType)? ((aliveBotsAfter[5] == 0)&&(aliveBotsAfter[6] == 0)&&(aliveBotsAfter[10] == 0)) :
                   ((aliveBotsAfter[5] == 0)&&(aliveBotsAfter[6] == 0)&&(aliveBotsAfter[10] == 0)&&(aliveBotsAfter[4] == 0));
    
    if (((player.lives()<= 0)||
        ((!myArmy.getRobot(0)->dead)&&
         (gameWon)))&&(!fadeOut)){
            
        fadeOut = true;
        goToNextLevel = true;
        //puts("next level!");
    }
    ///ARGHHHHH MEM CORRUPTION!!!!!!!
    for (unsigned i = 1; i < myArmy.count() - 1; i++){
        if (myArmy.getRobot(i)->dead)
            myArmy.remove(i);
    } 
    
    ss.setupListener(r->pos.v, r->direction.v);
}
//---------------------
void Singleton::selectGameLogic(){
    
    COLOR dark(0.6f, 0.6f, 0.6f);
    COLOR normal(1.0f, 1.0f, 1.0f);
   

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

    if ((!Keys[7])&&(OldKeys[7])){
        gamestate = TITLE;
        ss.playsound(8);
    }

     if (((!Keys[3])&&(OldKeys[3]))||
            ((!Keys[11])&&(OldKeys[11]))){
            ss.playsound(8);
            activeGameMode++;
            if (activeGameMode > 1)
                activeGameMode = 0;
            if (activeGameMode == 1){
                playrandom_button.c = dark;
                playregular_button.c = normal;
            }
            if (activeGameMode == 0){
                playregular_button.c = dark;
                playrandom_button.c = normal;
            }

     }
     if (((!Keys[2])&&(OldKeys[2]))||
            ((!Keys[10])&&(OldKeys[10]))){
            ss.playsound(8);
            activeGameMode--;
            if (activeGameMode < 0)
                activeGameMode = 1;
            if (activeGameMode == 1){
                playrandom_button.c = dark;
                playregular_button.c = normal;
            }
            if (activeGameMode == 0){
                playregular_button.c = dark;
                playrandom_button.c = normal;
            }

     }
    if ((!Keys[5])&&(OldKeys[5])){
        ss.playsound(8);
        switch(activeGameMode){
            case 0:{
                    PlayRegularGame();
                    playregular_button.c = normal;
                   }break;
            case 1:{
                    PlayRandomGame();
                    playrandom_button.c = normal;
                   }break;
        }
    }


#endif

    
    if (touches.down.count()){
        float mx = touches.down[0].v[0];
        float my = touches.down[0].v[1];
        if (playrandom_button.isPointerOnTop(mx, my))
            playrandom_button.c = dark;
        if (playregular_button.isPointerOnTop(mx, my))
            playregular_button.c = dark;
    }
    if (touches.allfingersup){
        playrandom_button.c = normal;
        playregular_button.c = normal;
    }
    
    
    if (touches.up.count()){
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        if (selectGameBack_button.isPointerOnTop(mx, my)){
            gamestate = TITLE;
            ss.playsound(8);
        }
        
        if (playrandom_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            PlayRandomGame();
            playrandom_button.c = normal;
        }
        if (playregular_button.isPointerOnTop(mx, my)){
            ss.playsound(8);
            PlayRegularGame();
            playregular_button.c = normal;
        }
    }
    
    
}

//---------------------
void Singleton::logic(){
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (music.playing())
        music.update();
#endif
    
    
    
    switch(gamestate){
        case TITLE: mainMenuLogic(); break;
        case GAME: gameLogic(); break;
        case HIGHSCORE: highScoreLogic(); break;
        case LEVELLIST: levelListLogic(); break;
        case OPTIONS: optionsLogic(); break;
        case HELP: helpLogic(); break;
        case ENTERNAME: enterNameLogic(); break;
        case ABOUT: aboutLogic(); break;
        case WELLDONE: wellDoneLogic(); break;
        case CONTROLCONFIG: controlsConfigLogic(); break;
        case SELECTGAME: selectGameLogic(); break;
    }
    
    touches.oldDown.destroy();
    for (unsigned long i = 0; i < touches.down.count(); i++ ){
        Vector3D v = touches.down[i];
        touches.oldDown.add(v);
    }
    touches.up.destroy();
    touches.down.destroy();
    touches.move.destroy();
}
//-------------------------
void Singleton::destroy(){
    
    touches.up.destroy();
    touches.down.destroy();
    touches.move.destroy();
    touches.oldDown.destroy();
    levellist.destroy();
    level.destroy();
    highscoresRegular.destroy();
    highscoresRandom.destroy();
    onlineScoreRandom.destroy();
    onlineScoreRegular.destroy();
    myArmy.destroy();
    
#if (!TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    music.stop();
    music.release();
#endif
    ss.exit();
    
    
    pics.destroy();
}


