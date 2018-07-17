//
// Created by andrea on 1/07/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include "Bike/bike.h"
#include "Camera/camera.h"
#include "Menu/menu.h"
#include "Coin/coin.h"
#include "Track/track.h"

using namespace std;
Bike bike;
Camera camera;
Menu menu;
Coin coin;
Track track;
int point=0;

int viewportW=1000;
int viewportH=1000;

bool isOnHeadlight=false;
bool showTrackMap=false;
bool useWireframe=false;
//float viewAlpha=20, viewBeta=40; // angoli che definiscono la vista

void  SetCoordToPixel(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1,-1,0);
    glScalef(2.0/viewportW, 2.0/viewportH, 1);
}

bool LoadTexture(int textbind,char *filename){
    GLenum texture_format;

    SDL_Surface *s = IMG_Load(filename);
    if (!s) return false;

    if (s->format->BytesPerPixel == 4){     // contiene canale alpha
        if (s->format->Rmask == 0x000000ff){
            texture_format = GL_RGBA;
        }
        else{
            texture_format = GL_BGRA;
        }
    } else if (s->format->BytesPerPixel == 3){     // non contiene canale alpha
        if (s->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    } else {
        printf("[ERROR] the image is not truecolor\n");
        exit(1);
    }

    glBindTexture(GL_TEXTURE_2D, textbind);
    gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            3,
            s->w, s->h,
            texture_format,
            GL_UNSIGNED_BYTE,
            s->pixels
    );
    glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR );
    glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR );
    return true;
}

void rendering(SDL_Window *window){


    glViewport(0,0, viewportW, viewportH);


    glClearColor(0,1,1,1);// colore sfondo

    // riempe tutto lo screen buffer di pixel color sfondo
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    menu.DrawMenu(viewportW, viewportH, point);
    glViewport(0, 0, viewportW *5/6, viewportH);//setto la viewport della pista

    // settiamo la matrice di proiezione
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 80, //fovy,
                    ((float)viewportW*5/6) / viewportH,//aspect Y/X,
                    0.25,//zNear,
                    100  //zFar
    );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    // setto la posizione luce
    float tmpv[4] = {0,1,2,  0}; // ultima comp=0 => luce direzionale
    glLightfv(GL_LIGHT0, GL_POSITION, tmpv );

    camera.UpdateCamera(bike.orientation, bike.positionOnX, bike.positionOnY, bike.positionOnZ);

    // disegna assi frame MONDO
    static float tmpcol[4] = {1,1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tmpcol);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 127);



    bike.Render();
    track.Render();
    coin.Render();

    //todo disegnare sfondo pavimento oltre pista
    //todo disegnare cielo


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);


    SetCoordToPixel();
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glFinish();
    // ho finito: buffer di lavoro diventa visibile
    SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[]){
    static int comands[NBUTTON] = {SDLK_w, SDLK_s, SDLK_a, SDLK_d};

    SDL_Init( SDL_INIT_VIDEO );
    Uint32 idWindow;

    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    SDL_Window *window=SDL_CreateWindow("Racing Bike", 0, 0, viewportW, viewportH, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext sdlContext=SDL_GL_CreateContext(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); // rinormalizza le normali prima di usarle

    glFrontFace(GL_CW); // consideriamo Front Facing le facce ClockWise
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    menu.InitMenu(viewportW, viewportH);

    track.InitTrack(bike.positionOnX, bike.positionOnZ);

    if (!LoadTexture(0,(char *)"Texture/myImage.jpg")) return 0;
    if (!LoadTexture(1,(char *)"Texture/Line-V.png")) return 0;
    if (!LoadTexture(2,(char *)"Texture/Line-O.png")) return 0;
    if (!LoadTexture(3,(char *)"Texture/Curve1.png")) return 0;
    if (!LoadTexture(4,(char *)"Texture/Curve2.png")) return 0;
    if (!LoadTexture(5,(char *)"Texture/Curve3.png")) return 0;
    if (!LoadTexture(6,(char *)"Texture/Curve4.png")) return 0;
    if (!LoadTexture(7,(char *)"Texture/Cross4road.png")) return 0;
    if (!LoadTexture(8,(char *)"Texture/Cross3road1.png")) return 0;
    if (!LoadTexture(9,(char *)"Texture/Cross3road2.png")) return 0;

    bool cond=true;
    while(cond){
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    bike.eventBike.EventButton(event.key.keysym.sym, true, comands);
                    if(event.key.keysym.sym==SDLK_RSHIFT | event.key.keysym.sym==SDLK_LSHIFT){
                        camera.EventShift(true);
                    }
                    switch (event.key.keysym.sym){
                        case SDLK_TAB://todo implementare funzione rendering mappa
                            showTrackMap=!showTrackMap;
                            break;
                        case SDLK_l:
                            isOnHeadlight=!isOnHeadlight;
                            break;
                        case SDLK_F1:
                            camera.UpdateIndexCamera();
                            break;
                        case SDLK_F2:
                            useWireframe=!useWireframe;
                            break;
                        case SDLK_F3:
                            break;
                        case SDLK_F4:
                            break;
                        case SDLK_F5:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    bike.eventBike.EventButton(event.key.keysym.sym, false, comands);
                    if(event.key.keysym.sym==SDLK_RSHIFT | event.key.keysym.sym==SDLK_LSHIFT){
                        camera.EventShift(false);
                    }
                    break;
                case SDL_WINDOWEVENT:// dobbiamo ridisegnare la finestra
                    if (event.window.event==SDL_WINDOWEVENT_EXPOSED){
                        rendering(window);
                    }else{
                        idWindow = SDL_GetWindowID(window);
                        if (event.window.windowID == idWindow)  {
                            switch (event.window.event)  {
                                case SDL_WINDOWEVENT_SIZE_CHANGED:  {
                                    viewportW = event.window.data1;
                                    viewportH = event.window.data2;
                                    glViewport(0,0,viewportW,viewportH);
                                    menu.InitMenu(viewportW, viewportH);
                                    rendering(window);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (menu.ButtonPress(event.button.x, event.button.y)){//todo altre voci menu
                        case 0://esci
                            cond= false;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.state & SDL_BUTTON(1)){
                        camera.UpdateView(event.motion.xrel, event.motion.yrel);
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    camera.UpdateEyeDistance(event.wheel.y > 0, event.wheel.y < 0);
                    break;
                case SDL_QUIT:
                    cond=false;
                    break;
            }
        }else{
            bike.ChangeState();
            point=coin.ChangeState(bike.positionOnX, bike.positionOnZ);
            rendering(window);
        }
    }

    SDL_GL_DeleteContext(sdlContext);
    SDL_DestroyWindow(window);
    SDL_Quit ();
    return (0);
}

/**
 *
 * W --> Accellera
 * S --> Decellera sino a retromarcia
 * A --> Svolta a sinistra
 * D -->  Svolta a destra
 *
 * F1 --> Cambia telecamera; Esistono 5 telecamere diverse
 * SHIFT --> Camera retromarcia
 * F2 --> Cambia l'uso dei Wireframe
 *
 *
 *
 *
 *
 */