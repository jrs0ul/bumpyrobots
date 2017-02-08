/***************************************************************************
 *   Copyright (C) 2008 by jrs0ul   *
 *   jrs0ul@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef WIN32
#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"OpenGl32.lib")
#pragma comment(lib,"GLU32.lib")
#endif
//--------------------------------------


#ifdef WIN32
    #ifdef _MSC_VER
        #include <SDL.h>
        #include <SDL_opengl.h>
    #else
        #include <SDL/SDL.h>
        #include <SDL/SDL_opengl.h>
    #endif
#else
    #include <SDL/SDL.h>
    #include <SDL/SDL_opengl.h>
#endif





#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>


#include "../../src/Image.h"
#include "../../src/TextureLoader.h"
#include "../../src/RobotArmy.h"
#include "../../src/LevelMap.h"
#include "../../src/Utils.h"
#include "../../src/gui/Button.h"
#include "../../src/gui/SelectMenu.h"
#include "../../src/gui/Text.h"
#include "../../src/Xml.h"
//#include "SelectMenu.h"


#ifdef WIN32
#ifdef _DEBUG
#include <crtdbg.h>//ieskoti memory leaku
#endif
#endif


int SCREENW = 640;
int SCREENH = 480;

Uint32 tick = 0;

PicsContainer pics;

bool _QuitApp = false;


LevelMap map;
RobotArmy myArmy;

Button mygtai[40];

int tilex,tiley;
bool SHOW_ENTITIES= true;
bool SHOW_LEV1= true;
bool SELECT_LEV1= true;
bool SELECT_ENT= false;
bool SHOW_DUDE = true;
bool SELECT_DUDE = false;


Vector3D mapPos = Vector3D(0,0,0);

unsigned char GlobalKey;
int oldmousekey,bm;
int mx,my;

Tile currenttile;
int currentchar = 0;
unsigned char firsttile=0;

int charsIDs[]={4,5,6,10};
int spriteIDs[]={2,1,11,0};

COLOR dudeColor = COLOR(1,1,1);
float dudeMass = 1.0f;
float dudeRadius = 16.0f;
SelectMenu FileMenu;

Xml data;

char MapIn[255];
char MapOut[255];

//=======================================================================
static void QuitApp(){
    _QuitApp = true;
}
//----------------------------------------------------------
static void process_events ( void ){

    SDL_Event event;
    while ( SDL_PollEvent ( &event ) ){

        switch ( event.type ){
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym ){
                    case SDLK_ESCAPE:{
                        QuitApp();
                    }
                    break;
                    default:{}
                }
                break;
            case SDL_QUIT:

                QuitApp();
                break;
            default:{}
        }
    }
}

//------------------------------------------------------
int FPS ( void ){
    static int time = 0, FPS = 0, frames = 0, frames0 = 0;
    if ( ( int ) SDL_GetTicks() >= time )
    {
        FPS = frames-frames0;
        time = SDL_GetTicks() +1000;
        frames0 = frames;
    }
    frames = frames+1;
    return FPS;
}
//-------------------------------------------
void DrawPanel(){

    pics.draw(-1, 0, 0, 0, false, SCREENW, 100, 0,
                COLOR(0, 0, 1, 0.5f),
                COLOR(0, 0, 1, 0.5f)
                );
    char buf[100];
    sprintf ( buf,"FPS: %d ",FPS() );
    WriteText ( SCREENW-128,10,pics,0, buf,0.7f, 0.7f );

    sprintf ( buf,"tilex:%d tiley:%d ",tilex, tiley );
    WriteText ( 10,10, pics,0, buf, 0.7f, 0.7f );

    if ( SHOW_LEV1 )
        mygtai[0].draw ( pics,2,5 );
    else
        mygtai[0].draw ( pics,2,4 );

   


    if ( SELECT_DUDE )
        mygtai[25].c =  COLOR(1.0f,0,0);
    else
        mygtai[25].c = COLOR(1,1,1);

    mygtai[25].draw ( pics, 1,0 );


    if ( SHOW_ENTITIES )
        mygtai[13].draw ( pics,2,5 );
    else
        mygtai[13].draw ( pics,2,4 );

    if ( SELECT_LEV1 )
        mygtai[6].c = COLOR(1.0f,0,0);
    else
        mygtai[6].c = COLOR(1,1,1);


    mygtai[6].draw ( pics,2,0 );

    if ( SELECT_ENT )
        mygtai[14].c = COLOR(1.0f,0,0);
    else
        mygtai[14].c = COLOR(1,1,1);

    mygtai[14].draw ( pics, 2, 8 );

    mygtai[3].c = currenttile.c;
    mygtai[3].draw ( pics, 3, firsttile);
    mygtai[4].c = currenttile.c;
    mygtai[4].draw ( pics,3,firsttile+1);
    mygtai[5].c = currenttile.c;
    mygtai[5].draw ( pics,3,firsttile+2);

    mygtai[9].draw ( pics,2,6 );
    mygtai[10].draw ( pics,2,7 );

    mygtai[15].draw ( pics,2,6 );
    mygtai[16].c = dudeColor;
    mygtai[16].draw ( pics, 6, spriteIDs[currentchar]);
    mygtai[17].draw ( pics,2,7 );
    mygtai[18].draw ( pics,2,9 );

    WriteText(mygtai[19].getX() + 10, mygtai[19].getY()-16, pics, 0, "r");
    mygtai[19].draw(pics, 2, 6);
    mygtai[20].draw(pics, 2, 7);
    WriteText(mygtai[21].getX() + 10, mygtai[21].getY()-16, pics, 0, "g");
    mygtai[21].draw(pics, 2, 6);
    mygtai[22].draw(pics, 2, 7);
    WriteText(mygtai[23].getX() + 10, mygtai[23].getY()-16, pics, 0, "b");
    mygtai[23].draw(pics, 2, 6);
    mygtai[24].draw(pics, 2, 7);

    WriteText(mygtai[26].getX() + 10, mygtai[26].getY()-16, pics, 0, "r");
    mygtai[26].draw(pics, 2, 6);
    mygtai[27].draw(pics, 2, 7);
    WriteText(mygtai[28].getX() + 10, mygtai[28].getY()-16, pics, 0, "g");
    mygtai[28].draw(pics, 2, 6);
    mygtai[29].draw(pics, 2, 7);
    WriteText(mygtai[30].getX() + 10, mygtai[30].getY()-16, pics, 0, "b");
    mygtai[30].draw(pics, 2, 6);
    mygtai[31].draw(pics, 2, 7);

    sprintf(buf, "%.2f", dudeRadius);
    WriteText(mygtai[32].getX() + 10, mygtai[32].getY()-16, pics, 0, buf, 0.8f, 0.8f);
    mygtai[32].draw(pics, 2, 6);
    mygtai[33].draw(pics, 2, 7);

    sprintf(buf, "%.2f", dudeMass);
    WriteText(mygtai[34].getX() + 10, mygtai[34].getY()-16, pics, 0, buf, 0.8f, 0.8f);
    mygtai[34].draw(pics, 2, 6);
    mygtai[35].draw(pics, 2, 7);

    mygtai[36].draw ( pics, 2, 10 );


}
//-----------------------------------------------------------
static void RenderScreen ( void ){

    glClear ( GL_COLOR_BUFFER_BIT );

    if ( SHOW_LEV1 )
        map.draw ( pics, 3, mapPos.v[0], mapPos.v[1],
                  1, SCREENW, SCREENH);

    if ( SHOW_ENTITIES )
        myArmy.draw(pics, mapPos.v[0], mapPos.v[1], 1,
                SCREENW, SCREENH);

    DrawPanel();

    if (FileMenu.active())
        FileMenu.draw(pics, 0, 0, 0, 0, 
                      COLOR(0.6f, 0.6f, 0.6f, 0.8f),
                      COLOR(0.6f, 0.6f, 0.6f, 0.8f),
                      false);


    pics.draw (5, mx, my);
    pics.drawBatch();

    //glDisable ( GL_BLEND );

    glFlush();
    //----------------------
    SDL_GL_SwapBuffers( );
}
//--------------------------------------------------------
static void SetupOpengl ( int width, int height ){

    glEnable ( GL_TEXTURE_2D );
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_LIGHTING );
    glDisable ( GL_DITHER );

    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();

    gluOrtho2D ( 0.0, ( GLdouble ) SCREENW, ( GLdouble ) SCREENH, 0.0 );

    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glTranslatef ( 0.375, 0.375, 0. );

    glPushAttrib ( GL_DEPTH_BUFFER_BIT );

    glClearColor ( 0, 0, 0, 1.0 );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );


    pics.initBuffers();
    if (!pics.load ( "pics/clist.txt" )){
        puts("Cannot find picture list!");
        _QuitApp = true;
    }
}
//------------------------------------------
void SaveLevel(const char * path){
    Xml dat;
    XmlNode lev;
    lev.setName(L"Level");
    XmlNode tiles;
    XmlNode robos;
    map.putToXMLNode(&tiles);
    myArmy.putToXMLNode(&robos);
    lev.addChild(tiles);
    lev.addChild(robos);
    dat.root.addChild(lev);
    dat.write(path);
    dat.destroy();
}
//--------------------------------------
void BuildFileMenu(){
    Lines l;
    GetFileList("../data/levels", l);
    SMenu selection;
    for (unsigned i = 0; i < l.l.count(); i++){
        char ext[4];
        memcpy(ext, &l.l[i].t[strlen(l.l[i].t) - 3], 3);
        ext[3] = '\0';
        if (strcmp(ext, "map") == 0){
            MenuItem item;
            strncpy(item.name, l.l[i].t, 255);
            memcpy(item.value, l.l[i].t, strlen(l.l[i].t) - 4);
            item.value[strlen(l.l[i].t) - 4] = 0;
            //puts(item.value);
            selection.add(item);
        }
    }
    l.l.destroy();

    int _height = (SCREENH / 4) * 3;

    FileMenu.init(
                  SCREENW / 2 - 200,
                  SCREENH / 2 - (_height/2),
                  selection,
                  0, _height);
    FileMenu.arrowFrames[0] = 5;
    FileMenu.arrowFrames[1] = 2;
    FileMenu.arrowFrames[2] = 3;
    FileMenu.setTitle("Open level...");
    selection.destroy();
    FileMenu.activate();
}

//------------------------------------------------
bool LoadLevel(const char * path){
    Xml lev;
    
    if (!lev.load(path))
        return false;
    
    map.destroy();
    myArmy.destroy();
    XmlNode * level = 0;
    level = lev.root.getNode(L"Level");
    if (level){
        
        XmlNode * entities = 0;
        XmlNode * tiles = 0;
        entities = level->getNode(L"Entities");
        if (entities) {
            myArmy.loadFromXMLNode(entities);
        }
        tiles = level->getNode(L"Tiles");
        if (tiles) {
            map.loadFromXMLNode(tiles);
        }
    }
    
    lev.destroy();

    return true;

}


//----------------------------------------------------------------
void CheckKeys()
{
    Uint8 * keys;
    keys = SDL_GetKeyState ( NULL );

    oldmousekey = bm;
    bm = SDL_GetMouseState ( &mx,&my );

    //------------------------------
    GlobalKey = 0;
    if ( keys[SDLK_UP] == SDL_PRESSED )
        GlobalKey = 38;
    if ( keys[SDLK_DOWN] == SDL_PRESSED )
        GlobalKey = 40;
    if ( keys[SDLK_RETURN] == SDL_PRESSED )
        GlobalKey = 13;

    //------------------------------

    if ( keys[SDLK_UP] ){
        Vector3D v ( 0, 1.0f, 0 );
        mapPos = mapPos + v;
    }
    if ( keys[SDLK_LEFT] ){
        Vector3D v ( 1.0f,0,0 );
        mapPos = mapPos + v;
    }
    if ( keys[SDLK_DOWN] ){
        Vector3D v ( 0,-1.0f, 0 );
        mapPos = mapPos + v;
    }
    if ( keys[SDLK_RIGHT] ){
        Vector3D v ( -1.0f,0,0 );
        mapPos = mapPos + v;
    }


    


    if (FileMenu.active()){
        SoundSystem SS;
        if (!FileMenu.selected){
            FileMenu.getInput(GlobalKey, mx, my);
            if (FileMenu.selected){
                char path[256];
                sprintf(path, "../data/levels/%s.map", 
                        FileMenu.selection.items[FileMenu.state].value);
                if (!LoadLevel(path))
                    printf("Level %s not found !\n", path);
                else
                    strcpy(MapOut, path);
            }
        }
        else{
            FileMenu.deactivate();
            FileMenu.destroy();
        }

        return;

    }




    if ( ( mx<SCREENW ) && ( mx>0 )
            && ( my<SCREENH ) && ( my>0 ) ){
        if ( my >100 ){
            tilex= ( (int)(mx - mapPos.v[0])) /32;
            tiley= ( (int)(my - mapPos.v[1])) /32;
        }
    }

    if ( my >100 ){
        if ( ( bm & SDL_BUTTON ( 1 ) ) ){
            if ( SELECT_LEV1 )
                map.setTile ( tilex, tiley, currenttile );

            if ( SELECT_DUDE ){
                myArmy.getRobot(0)->pos = Vector3D(mx - mapPos.v[0], my - mapPos.v[1],0 );
            }
        }

        if ((!bm) && (oldmousekey & SDL_BUTTON(2))){
            if (SELECT_LEV1){
                if ((((unsigned)tilex) < map.width) && (((unsigned)tiley) < map.height))
                    currenttile = map.map[tiley][tilex];
            }

            if (SELECT_ENT){
                for ( unsigned i = 1; i < myArmy.count(); i++ ){
                    Robot * e = 0;
                    e = myArmy.getRobot( i );
                    if (e){
                        if ( CirclesColide( e->pos.v[0] + mapPos.v[0],
                                            e->pos.v[1] + mapPos.v[1], e->radius, mx, my, 8.0f ) ){
                       
                            //puts("yay");
                            dudeColor = e->c;
                            dudeMass = e->mass;
                            dudeRadius = e->radius;
                            for (unsigned a = 0; a < 4; a++)
                                if (charsIDs[a] == (int)e->face){
                                    currentchar = a;
                                    break;
                                }
                            break;
                        }
                    }
                }

            }
        }

        if ( ( !bm ) && ( oldmousekey & SDL_BUTTON ( 1 ) ) ){
            if ( SELECT_ENT ){
                Robot dude;
                dude.pos = Vector3D ( mx - mapPos.v[0], my - mapPos.v[1], 0 );
                dude.direction = Vector3D(0,0,0);
                dude.radius = dudeRadius;
                dude.speed = 0;
                dude.c = dudeColor;
                dude.mass = dudeMass;
                dude.falling = false;
                dude.jumping = false;
                dude.face =   charsIDs[currentchar];
                switch(dude.face){
                    case PLAYER   :  dude.startFrame = 7; break;
                    case CRYSTAL  :  dude.startFrame = 2; break;
                    case SPIKEY   :  dude.startFrame = 1; break;
                    case ASTARER  :  dude.startFrame = 11; break;
                    case ASSAULTER:  dude.startFrame = 0; break;
                }

                myArmy.add( dude );
            }
        }

        if ( ( bm & SDL_BUTTON ( 3 ) ) ){
            if ( SELECT_LEV1 ){
                Tile empty;
                empty.c = COLOR(0,0,0);
                empty.picture = 0;
                map.setTile ( tilex,tiley, empty );
            }
            
            if ( SELECT_ENT ){
                for ( unsigned i = 1; i < myArmy.count(); i++ ){
                    Robot * e;
                    e = myArmy.getRobot( i );
                    if ( CirclesColide( e->pos.v[0] + mapPos.v[0], e->pos.v[1] + mapPos.v[1], e->radius, mx, my, 8.0f ) ){
                        puts("colide");
                        myArmy.remove( i );
                        break;
                    }
                }
            }
        }

    }
    else{
        if ( ( bm & SDL_BUTTON ( 1 ) ) ){

            if ( ( mygtai[19].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[0] < 1.0f)
                    dudeColor.c[0]+= 0.01f;
            if ( ( mygtai[20].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[0] > 0.0f)
                    dudeColor.c[0]-= 0.01f;
            if ( ( mygtai[21].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[1] < 1.0f)
                    dudeColor.c[1]+= 0.01f;
            if ( ( mygtai[22].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[1] > 0.0f)
                    dudeColor.c[1]-= 0.01f;
            if ( ( mygtai[23].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[2] < 1.0f)
                    dudeColor.c[2]+= 0.01f;
            if ( ( mygtai[24].isPointerOnTop ( mx, my ) ) )
                if (dudeColor.c[2] > 0.0f)
                    dudeColor.c[2]-= 0.01f;
            //---------------
            if ( ( mygtai[26].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[0] < 1.0f)
                    currenttile.c.c[0]+= 0.01f;
            if ( ( mygtai[27].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[0] > 0.0f)
                    currenttile.c.c[0]-= 0.01f;
            if ( ( mygtai[28].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[1] < 1.0f)
                    currenttile.c.c[1]+= 0.01f;
            if ( ( mygtai[29].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[1] > 0.0f)
                    currenttile.c.c[1]-= 0.01f;
            if ( ( mygtai[30].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[2] < 1.0f)
                    currenttile.c.c[2]+= 0.01f;
            if ( ( mygtai[31].isPointerOnTop ( mx, my ) ) )
                if (currenttile.c.c[2] > 0.0f)
                    currenttile.c.c[2]-= 0.01f;
            //---------------
            //
            if ( ( mygtai[32].isPointerOnTop ( mx, my ) ) )
                if (dudeRadius < 36.0f)
                    dudeRadius+= 0.5f;
            if ( ( mygtai[33].isPointerOnTop ( mx, my ) ) )
                if (dudeRadius > 8.0f)
                    dudeRadius-= 0.5f;
           

        }

        if ( ( !bm ) && ( oldmousekey & SDL_BUTTON ( 1 ) ) ){

            if ( ( mygtai[34].isPointerOnTop ( mx, my ) ) )
                if (dudeMass < 20.0f)
                    dudeMass+= 0.05f;
            if ( ( mygtai[35].isPointerOnTop ( mx, my ) ) )
                if (dudeMass > 0.0f)
                    dudeMass-= 0.05f;



            if ( ( mygtai[0].isPointerOnTop ( mx, my )))
                SHOW_LEV1 = !SHOW_LEV1;
            if ( ( mygtai[13].isPointerOnTop ( mx, my )))
                SHOW_ENTITIES = !SHOW_ENTITIES;

            if ( ( mygtai[3].isPointerOnTop ( mx, my )))
                currenttile.picture = firsttile;
            if ( ( mygtai[4].isPointerOnTop ( mx, my )))
                currenttile.picture = firsttile+1;
            if ( ( mygtai[5].isPointerOnTop ( mx, my )))
                currenttile.picture = firsttile+2;

            if ( ( mygtai[6].isPointerOnTop ( mx, my ) ) )
                SELECT_LEV1 = !SELECT_LEV1;

            //-----------------------
           



            if ( ( mygtai[25].isPointerOnTop ( mx, my ) ) )
                SELECT_DUDE = !SELECT_DUDE;


            if ( ( mygtai[14].isPointerOnTop ( mx, my ) ) )
                SELECT_ENT = !SELECT_ENT;

            if ( ( mygtai[9].isPointerOnTop ( mx, my ) ) )
                if ( firsttile>0 )
                    firsttile--;

            if ( ( mygtai[10].isPointerOnTop ( mx, my ) ) )
                if ( firsttile+3 < pics.getInfo ( 2 )->htileh*pics.getInfo ( 2 )->htilew )
                    firsttile++;
            if ( ( mygtai[15].isPointerOnTop ( mx, my ) ) )
                if ( currentchar > 0 )
                    currentchar--;
            if ( ( mygtai[17].isPointerOnTop ( mx, my ) ) )
                if ( currentchar < 3 )
                    currentchar++;
           
            if ( ( mygtai[18].isPointerOnTop ( mx, my ) ) )
                SaveLevel( MapOut );

            if ( ( mygtai[36].isPointerOnTop ( mx, my ) ) )
                if (!FileMenu.active()){
                    BuildFileMenu();
                }


        }
    }
}







//-----------------------------------------------------------------
int main ( int argc, char* argv[] ){

    srand ( time ( 0 ) );
    data.load( "conf.xml");
    char abuf[255];
    XmlNode * settings = 0;
    settings = data.root.getNode(L"Settings");
    if (settings){
        XmlNode * _width = 0;
        _width = settings->getNode(L"width");
        if (_width){
            wcstombs(abuf, _width->getValue(),255);
            SCREENW = atoi ( abuf );
        }
        if ( !SCREENW )
            SCREENW = 640;
        XmlNode * _height = 0;
        _height = settings->getNode(L"height");
        if (_height){
            wcstombs(abuf, _height->getValue(), 255);
            SCREENH = atoi ( abuf );
        }
        if ( !SCREENH )
            SCREENH = 480;
        wcstombs ( MapIn, settings->getNode(L"mapIN")->getValue(), 255 );
        wcstombs ( MapOut, settings->getNode(L"mapOUT")->getValue(), 255 );
    }
    data.destroy();

    mygtai[0].set ( 10,20,32,32 );
    mygtai[1].set ( 46,20,32,32 );
    mygtai[2].set ( 82,20,32,32 );
    mygtai[11].set ( 118,20,32,32 );
    mygtai[13].set ( 64,20,32,32 );

    mygtai[6].set ( 10,55,32,32 );
    mygtai[7].set ( 46,55,32,32 );
    mygtai[8].set ( 82,55,32,32 );
    mygtai[12].set ( 118,55,32,32 );
    mygtai[14].set ( 64,55,32,32 );


    mygtai[9].set ( 104,55,32,32 );
    mygtai[3].set ( 150,55,32,32 );
    mygtai[4].set ( 196,55,32,32 );
    mygtai[5].set ( 232,55,32,32 );
    mygtai[10].set ( 278,55,32,32 );

    mygtai[15].set ( 104,20,32,32 );
    mygtai[16].set ( 150,20,32,32 );
    mygtai[17].set ( 196,20,32,32 );

    mygtai[18].set ( 580,20,32,32 );


    mygtai[19].set ( 230,20,16,16 );
    mygtai[20].set ( 250,20,16,16 );
    mygtai[21].set ( 270,20,16,16 );
    mygtai[22].set ( 290,20,16,16 );
    mygtai[23].set ( 310,20,16,16 );
    mygtai[24].set ( 330,20,16,16 );

    mygtai[26].set ( 310,55,16,16 );
    mygtai[27].set ( 330,55,16,16 );
    mygtai[28].set ( 350,55,16,16 );
    mygtai[29].set ( 370,55,16,16 );
    mygtai[30].set ( 390,55,16,16 );
    mygtai[31].set ( 410,55,16,16 );

    mygtai[32].set(370, 20, 16, 16);
    mygtai[33].set(390, 20, 16, 16);

    mygtai[34].set(440, 20, 16, 16);
    mygtai[35].set(460, 20, 16, 16);

    mygtai[25].set ( 500, 55, 32, 32 );
    mygtai[36].set ( 580, 55, 32, 32 );

    currenttile.c = COLOR(1,1,1);

    const SDL_VideoInfo* info = NULL;

    int width = 0;
    int height = 0;
    int bpp = 0;

    // Flags we will pass into SDL_SetVideoMode.
    int flags = 0;

    // First, initialize SDL's video subsystem.
    puts ( "Trying SDL_INIT..." );
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
    {

        fprintf ( stderr, "Video initialization failed: %s\n",
                  SDL_GetError( ) );
        QuitApp();
    }
    puts ( "SDL_INIT succsess!" );

    // Let's get some video information.
    info = SDL_GetVideoInfo( );

    if ( !info )
    {
        // This should probably never happen.
        fprintf ( stderr, "Video query failed: %s\n",
                  SDL_GetError( ) );
        QuitApp();
    }


    width = SCREENW;
    height = SCREENH;
    bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );


    flags = SDL_OPENGL;//| SDL_FULLSCREEN;

    if ( SDL_SetVideoMode ( width, height, bpp, flags ) == 0 )
    {

        fprintf ( stderr, "Video mode set failed: %s\n",
                  SDL_GetError( ) );
        QuitApp();
    }

    SDL_ShowCursor ( 0 );
    SDL_WM_SetCaption ( "bumped", "SATAN" );

    SetupOpengl ( width, height );


    unsigned mapWidth = 0;
    unsigned mapHeight = 0;
    if (argc > 1){
        mapWidth = (unsigned)atoi(argv[1]);
        mapHeight = (unsigned)atoi(argv[2]);
        if ((mapWidth <= 0)||(mapWidth > 100))
            mapWidth = 13;
        if ((mapHeight <= 0)||(mapHeight > 100))
            mapHeight = 13;
    }

    map.generate(mapWidth, mapHeight);
    myArmy.create(map);

    while ( !_QuitApp ){

        if ( SDL_GetTicks() > tick ){
            CheckKeys();
            RenderScreen();
            tick = SDL_GetTicks() +11;
        }

        else SDL_Delay ( 1 );
        process_events();
    }


    pics.destroy();
    myArmy.destroy();
    map.destroy();

    SDL_Quit();

#ifdef WIN32
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
#endif


    return 0;
}

