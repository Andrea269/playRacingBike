//
// Created by andrea on 1/07/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <string>

#include "Bike/bike.h"
#include "Camera/camera.h"
#include "Menu/menu.h"

using namespace std;
Bike bike;//todo radrizzare da blander la moto e alzare ruota avanti
Camera camera;
Menu menu;

int viewportW=1000;
int viewportH=1000;

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

void drawFloor(){
    const float S=20; // size
    const float H=0;   // altezza
    const int K=400; //disegna K x K quads

    // disegna KxK quads
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6); // colore uguale x tutti i quads
    glNormal3f(0,1,0);       // normale verticale uguale x tutti
    for (int x=0; x<K; x++)
        for (int z=0; z<K; z++) {
            float x0=-S + 2*(x+0)*S/K;
            float x1=-S + 2*(x+1)*S/K;
            float z0=-S + 2*(z+0)*S/K;
            float z1=-S + 2*(z+1)*S/K;
            glVertex3d(x0, H, z0);
            glVertex3d(x1, H, z0);
            glVertex3d(x1, H, z1);
            glVertex3d(x0, H, z1);
        }
    glEnd();
}

void rendering(SDL_Window *window){


    glViewport(0,0, viewportW, viewportH);


    glClearColor(1,1,1,1);// colore sfondo

    // riempe tutto lo screen buffer di pixel color sfondo
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    menu.DrawMenu(viewportW, viewportH);
    glViewport(0, 0, viewportW * 4/5, viewportH);//setto la viewport della pista

    // settiamo la matrice di proiezione
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 80, //fovy,
                    ((float)viewportW*4/5) / viewportH,//aspect Y/X,
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


    drawFloor();
    bike.Render();



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

    SDL_Window *window=SDL_CreateWindow("Recing Bike", 0, 0, viewportW, viewportH, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext sdlContext=SDL_GL_CreateContext(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); // rinormalizza le normali prima di usarle

    glFrontFace(GL_CW); // consideriamo Front Facing le facce ClockWise
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    menu.InitMenu(viewportW, viewportH);
    rendering(window);

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
 * F1 --> Cambia camera ne esistono 5
 * SHIFT --> Camera retromarcia
 * F2 --> Cambia l'uso dei Wireframe
 *
 *
 *
 *
 *
 */