#ifndef _CPP_SINGLETON
#define _CPP_SINGLETON

#include <ctime>
#include "audio/SoundSystem.h"
#include "audio/OggStream.h"
#include "TextureLoader.h"
#include "Vectors.h"
#include "RobotArmy.h"
#include "LevelMap.h"
#include "gui/Button.h"
#include "gui/Scrollbar.h"
#include "gui/YesNoDialog.h"
#include "gui/OnScreenBoard.h"
#include "SysConfig.h"
#include "TouchData.h"
#include "Player.h"
#include "LevelList.h"
#include "HighScore.h"
#include "externals.h"

#define BUTTONS 1
#define MENU 4
#define GUI 10
#define LOGO 11
#define BG 5
#define THEEND 13
#define LITESIGN 14
#define GETFULL 15

enum GameStates {TITLE, GAME, HIGHSCORE, LEVELLIST,
                 OPTIONS, HELP, ENTERNAME, ABOUT, WELLDONE,
                 CONTROLCONFIG, SELECTGAME};


struct Joystick{
    Vector3D pos;
    float radius;
    
    Joystick(){
        pos = Vector3D(70, 250, 0);
        radius = 50.0;
    }
};


class Singleton{
    
    void ProcessTouchUp(Vector3D * touch);
    void ProcessTouchDown(Vector3D * touch);
    void ProcessTouchMove(Vector3D * touch);
    
    void drawMainMenu();
    void drawHighScore();
    void highScoreLogic();
    void levelListLogic();
    void drawGame();
    void gameLogic();
    void mainMenuLogic();
    void drawLevelList();
    void AttachDefaultEntitySounds();
    void GoToNextLevel();
    void throwPowerup();
    
    void helpLogic();
    void drawHelp();
    void drawOptions();
    void optionsLogic();
    
    void makeBomb();
    void runLevel(int lev);
    void resetHighScores();
    
    void enterNameLogic();
    void drawEnterName();
    
    void aboutLogic();
    void drawAbout();
    
    void drawWellDone();
    void wellDoneLogic();
    
    void drawSubmisionQuestion();
    void submisionQuestionLogic();
    
    void parseOnlineScores(HighScores& container);
    
    void fetchScore(int type);
    void submitScore(int type);
    
    void setMusicVolume(float vol);
    void playMusic();
    void playNewSong(const char* path);
    
    void updateLevelList();
    
    void drawControlsConfig();
    void controlsConfigLogic();
    
    void drawJoystick();
    void drawBombButton();
    
    void drawSelectGame();
    void selectGameLogic();
    void PlayRegularGame();
    void PlayRandomGame();
    void addScore();

    void handleMainMenuWithKeyboard();
    
    void drawDebugText();
   
public:
    bool Exit;
    
    bool ChangeVolume;
    float MusicVolume;
    bool PlayMusic;
    bool PlayNewSong;
    bool StopMusic;
    
    
    SoundSystem ss;
    OggStream music;
    
    PicsContainer pics;
    
    bool useAccel;
    
    bool sendStats;    //send my level stats
    time_t levelStart;
    time_t levelEnd;
    time_t suspendStart;
    time_t suspendEnd;
    double suspendDuration;
    
    
    int scoreBefore;
    int livesBefore;
    int bombsUsed;
    int jumps;
    char previousLevelName[100];
    char statPostParams[255];
    
    bool getHighScore; //fetch me some scores!
    bool gotHighScore; //got some xml shit
    bool sendScore;   //send my scores quickly
    
    bool failToGetScore; 
    int onlineScoreType; //what type of scores
    char highscorePostParams[255]; //post parameters to send
    int waitForOnlineScoreTics; //wait tics until timeout
    char highScoreFromServer[2024]; //xml thingie
    bool submitOnline; //do I have to send my scores online?
    int onlineScorePage;
    
    int GameCenterScore;
    
    SystemConfig sys;
    
    Vector3D accelerometer;
    Vector3D pos;
    RobotArmy myArmy;
    Player player;
    Vector3D gamepad; //input from real device
    
    HighScores highscoresRegular;
    HighScores highscoresRandom;
    HighScores onlineScoreRegular;
    HighScores onlineScoreRandom;
    
    
    char DocumentPath[255];
    
    char songName[255];
    
    
    Joystick joystick;
    LevelMap level;
    TouchData touches;
    unsigned char Keys[20];
    unsigned char OldKeys[20];
    int activeMenuItem;
    int activeGameMode;
    float acc;

    Button b;
    
    Button playregular_button;
    Button playrandom_button;
    Button selectGameBack_button;
    Button changeName_button;
    
    Button play_button;
    Button resume_button;
    Button highscore_button;
    Button options_button;
    Button howtoplay_button;
    Button resetLevel_button;
    Button backLevels_button;
    Button backOptions_button;
    Button backControls_button;
    Button controlsReset_button;
    Button controlsOptions_button;
    Button resetScore_button;
    Button onlineScorePage_button;
    
    Button helpBack_button;
    Button helpNext_button;
    Button helpPrev_button;
    
    Button randomHighscore_button;
    Button regularHighscore_button;
    Button onlineScore_button;
    Button localScore_button;
    Button GameCenter_button;
    
    Button highScoresBack_button;
    Button toMainMenu_button;
    
    Button about_button;
    Button getfull_button;
    Button jrs0ul_button;
    bool launchjrs0ul;
    
    ScrollBar musicVolume_bar;
    ScrollBar sfxVolume_bar;
    ScrollBar accel_bar;
    
    YesNoDialog YesNoDlg;
    YesNoDialog SubmitScoreYN;
    
    //-----
    Button bomb_button;
    Button jump_button;
    long delayBetweenBombs;
    
    //---
    
    GameStates gamestate;
    
    bool goToNextLevel;
    bool fadeOut;
    float alpha;
    
    bool levelCreated;
    
    bool joyPressed;
    
    LevelList levellist;
    int TouchedLevelindex;
    
    int helpPage;
    
    OnScreenKeyboard Keyboard;
    char nameToEnter[256];
    
    bool ActivateEditField;
    bool TextEntered;
    int globalKEY;
    //---
    
    bool dragJumpButton;
    bool dragBombButton;
    bool dragJoystick;
    bool dragPauseButton;
    
    LevelMap tmplevel;
    RobotArmy tmpArmy;
    
    bool buyGame;
    
    bool ShowGameCenter;
    
    bool isPirate;
    
    Vector3D oldMoveTouch;
    
    Vector3D oldTouchDown;
    bool menumoved;
    
    int drawCalls;

    
    
    Singleton(){
        dragJumpButton = false;
        dragBombButton = false;
        dragJoystick = false;
        dragPauseButton = false;
        gamestate = TITLE;
        Exit = false;
        alpha = 0.0f;
        fadeOut = false;
        goToNextLevel = false;
        levelCreated = false;
        joyPressed = false;
        delayBetweenBombs = 0;
        helpPage = 0;
        TouchedLevelindex = -1;
        ActivateEditField = false;
        TextEntered = false;
        
        launchjrs0ul = false;
        acc = 36.0f;
        
        getHighScore = false;
        gotHighScore= false;
        waitForOnlineScoreTics = 0;
        onlineScoreType = 0;
        onlineScorePage = 0;
        sendScore = false;
        sendStats = false;
        submitOnline = false;
        failToGetScore = false;
        
        ChangeVolume = false;
        MusicVolume = 0.0f;
        PlayMusic = false;
        StopMusic = false;
        PlayNewSong = false;
        
        buyGame = false;
        GameCenterScore = 0;
        ShowGameCenter = false;
        isPirate = false;
        
        suspendDuration = 0;
        activeMenuItem = 1;
        activeGameMode = 0;
        Exit = false;
        oldMoveTouch = Vector3D(0,0,0);
        menumoved = false;
        drawCalls = 0;
       
    
    }
    
    void init();
    void logic();
    void render();
    void destroy();
    
};





#endif //_CPP_SINGLETON

