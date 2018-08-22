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
//todo aggiungere scelta di tempo massimo raccolta coin o girare liberamente

int viewportW=1000;
int viewportH=1000;

bool isOnHeadlight=false;
bool showTrackMap=false;
bool useWireframe=false;
bool isShadow=false;
bool isPause=false;
bool startPlay=false;
bool timePlay=false;
int timeGame;
float worldLimit=250;
SDL_TimerID timerID;
SDL_TimerID timerVideo;

void  SetEndPlay(){
    bike.Init();
    coin.InitStatusCoin();
    camera.InitIndex();
    point=0;
    isOnHeadlight=false;
    showTrackMap=false;
    useWireframe=false;
    isShadow=false;
    isPause=false;
    startPlay=false;
    timePlay=false;
    SDL_RemoveTimer( timerID );
    SDL_RemoveTimer( timerVideo );

}

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

void drawSphere(double r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

//le normali servono per l'EnvMap
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}

void drawSky(){
    if (useWireframe) {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0,0,0);
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        drawSphere(worldLimit, 20, 20);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glColor3f(1,1,1);
        glEnable(GL_LIGHTING);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,11);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_SPHERE_MAP); // Env map
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_SPHERE_MAP);
        //glColor3f(1,1,1);
        glDisable(GL_LIGHTING);

        //   drawCubeFill();
        drawSphere(worldLimit, 20, 20);

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
    }
}

void drawFloor(){
    const float S=worldLimit; // size
    const float H=-0.2;   // altezza
    const int K=70; //disegna K x K quads

    glBindTexture(GL_TEXTURE_2D, 12);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/( 2*S/K);
    float sx=1/( 2*S/K);
    float s[4]={sx, 0,0, 0};
    float t[4]={0,0,sz, 0};
    glTexGenfv(GL_S, GL_OBJECT_PLANE, t);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, s);

    glBegin(GL_QUADS);
    glNormal3f(0,1,0);// normale verticale uguale x tutti
    for (int x=0; x<K; x++){
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
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawMap(){
    int originX=0;
    int originY=viewportH;
    int maxX=260;
    int maxY=viewportH-260;
    int centroX=maxX/2;
    int centroY=maxY+((originY-maxY)/2);

    int pointX=centroX-(bike.positionOnX*1/2);
    int pointY=centroY+(bike.positionOnZ*1/2);

    glColor3f(1, 0, 0);
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex2d(pointX, pointY);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d(centroX+7, centroY-45);
    glVertex2d(centroX-7, centroY-45);
    glVertex2d(centroX-7, centroY+50);
    glVertex2d(centroX+7, centroY+50);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+43, centroY+40);
    glVertex2d(centroX-7, centroY+40);
    glVertex2d(centroX-7, centroY+55);
    glVertex2d(centroX+43, centroY+55);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+43, centroY+40);
    glVertex2d(centroX+30, centroY+40);
    glVertex2d(centroX+30, centroY+75);
    glVertex2d(centroX+43, centroY+75);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+40, centroY+60);
    glVertex2d(centroX+55, centroY+60);
    glVertex2d(centroX+55, centroY+75);
    glVertex2d(centroX+40, centroY+75);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+83, centroY+52);
    glVertex2d(centroX+45, centroY+52);
    glVertex2d(centroX+45, centroY+65);
    glVertex2d(centroX+83, centroY+65);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+78, centroY+40);
    glVertex2d(centroX+93, centroY+40);
    glVertex2d(centroX+93, centroY+65);
    glVertex2d(centroX+78, centroY+65);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+83, centroY-7);
    glVertex2d(centroX+68, centroY-7);
    glVertex2d(centroX+68, centroY+50);
    glVertex2d(centroX+83, centroY+50);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+68, centroY+7);
    glVertex2d(centroX-43, centroY+7);
    glVertex2d(centroX-43, centroY-7);
    glVertex2d(centroX+68, centroY-7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-31, centroY+7);
    glVertex2d(centroX-46, centroY+7);
    glVertex2d(centroX-46, centroY-45);
    glVertex2d(centroX-31, centroY-45);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+47, centroY-30);
    glVertex2d(centroX-63, centroY-30);
    glVertex2d(centroX-63, centroY-45);
    glVertex2d(centroX+47, centroY-45);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-82, centroY-37);
    glVertex2d(centroX-50, centroY-37);
    glVertex2d(centroX-50, centroY-23);
    glVertex2d(centroX-82, centroY-23);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-82, centroY+15);
    glVertex2d(centroX-67, centroY+15);
    glVertex2d(centroX-67, centroY-66);
    glVertex2d(centroX-82, centroY-66);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-82, centroY-52);
    glVertex2d(centroX+78, centroY-52);
    glVertex2d(centroX+78, centroY-66);
    glVertex2d(centroX-82, centroY-66);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+63, centroY-40);
    glVertex2d(centroX+78, centroY-40);
    glVertex2d(centroX+78, centroY-66);
    glVertex2d(centroX+63, centroY-66);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+71, centroY-50);
    glVertex2d(centroX+56, centroY-50);
    glVertex2d(centroX+56, centroY-17);
    glVertex2d(centroX+71, centroY-17);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX+47, centroY-45);
    glVertex2d(centroX+56, centroY-32);
    glVertex2d(centroX+56, centroY-17);
    glVertex2d(centroX+47, centroY-30);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-23, centroY+45);
    glVertex2d(centroX-37, centroY+45);
    glVertex2d(centroX-37, centroY-7);
    glVertex2d(centroX-23, centroY-7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-23, centroY+46);
    glVertex2d(centroX-50, centroY+46);
    glVertex2d(centroX-50, centroY+32);
    glVertex2d(centroX-23, centroY+32);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-65, centroY+43);
    glVertex2d(centroX-40, centroY+43);
    glVertex2d(centroX-40, centroY+57);
    glVertex2d(centroX-65, centroY+57);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-65, centroY+57);
    glVertex2d(centroX-51, centroY+57);
    glVertex2d(centroX-51, centroY-7);
    glVertex2d(centroX-65, centroY-7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(centroX-65, centroY+8);
    glVertex2d(centroX-67, centroY+15);
    glVertex2d(centroX-67, centroY);
    glVertex2d(centroX-65, centroY-7);
    glEnd();




    glColor3f(0, 1, 0.3);
    glBegin(GL_QUADS);
    glVertex2d(originX, originY);
    glVertex2d(maxX, originY);
    glVertex2d(maxX, maxY);
    glVertex2d(originX, maxY);
    glEnd();
}

void rendering(SDL_Window *window){
    glViewport(0,0, viewportW, viewportH);
    glClearColor(1,1,1,1);// colore sfondo bianco

    // riempe tutto lo screen buffer di pixel color sfondo
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(!startPlay){
        menu.DrawStart(viewportW, viewportH);
    }else {
        menu.DrawMenu(viewportW, viewportH, point);
        glViewport(0, 0, viewportW * 5 / 6, viewportH);//setto la viewport della pista

        if (showTrackMap) {
            drawMap();
        }
        glColor3f(1, 1, 1);//setto il colore bianco di default

        // settiamo la matrice di proiezione
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, //fovy,
                       ((float) viewportW * 5 / 6) / viewportH,//aspect Y/X,
                       0.25,//zNear,
                       500  //zFar
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        // setto la posizione luce
        float tmpv[4] = {0, 1, 2, 0}; // ultima comp=0 => luce direzionale
        glLightfv(GL_LIGHT0, GL_POSITION, tmpv);

        camera.UpdateCamera(bike.orientation, bike.positionOnX, bike.positionOnY, bike.positionOnZ);

        // disegna assi frame MONDO
        static float tmpcol[4] = {1, 1, 1, 1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tmpcol);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 127);


        glEnable(GL_LIGHTING);

        drawSky();
        drawFloor();

        bike.Render();
        track.Render();
        coin.Render();

        if(timePlay){
            //todo giro libero e giro a tempo drawTime


            //todo classifica
        }
        if (isPause) {
            menu.DrawPause(viewportW, viewportH);
        }

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        SetCoordToPixel();
        glEnd();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }
    glFinish();
    // ho finito: buffer di lavoro diventa visibile
    SDL_GL_SwapWindow(window);
}


Uint32 EndTimer( Uint32 interval, void* param ){
    // todo startPlay= false;

    return 0;
}


Uint32 UpdateTimerVideo( Uint32 interval, void* param ){
    timeGame--;
    timerVideo = SDL_AddTimer( 1 * 1000, UpdateTimerVideo, (void*)"1 seconds waited!" );
    return 0;
}

void initObj(){
    menu.InitMenu(viewportW, viewportH);

    track.InitTrack(bike.positionOnX, bike.positionOnZ);

    if (!LoadTexture(0,(char *)"Texture/myImage.jpg")){SDL_Quit();}
    if (!LoadTexture(1,(char *)"Texture/Line-V.png")){SDL_Quit();}
    if (!LoadTexture(2,(char *)"Texture/Line-O.png")){SDL_Quit();}
    if (!LoadTexture(3,(char *)"Texture/Curve1.png")){SDL_Quit();}
    if (!LoadTexture(4,(char *)"Texture/Curve2.png")){SDL_Quit();}
    if (!LoadTexture(5,(char *)"Texture/Curve3.png")){SDL_Quit();}
    if (!LoadTexture(6,(char *)"Texture/Curve4.png")){SDL_Quit();}
    if (!LoadTexture(7,(char *)"Texture/Cross4road.png")){SDL_Quit();}
    if (!LoadTexture(8,(char *)"Texture/Cross3road1.png")){SDL_Quit();}
    if (!LoadTexture(9,(char *)"Texture/Cross3road2.png")){SDL_Quit();}
    if (!LoadTexture(11,(char *)"Texture/sky.jpg")){SDL_Quit();}
    if (!LoadTexture(12,(char *)"Texture/greenLawn.jpg")){SDL_Quit();}
}

int main(int argc, char* argv[]){
    static int comands[NBUTTON] = {SDLK_w, SDLK_s, SDLK_a, SDLK_d};

    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_Joystick *joystick = SDL_JoystickOpen(0);
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



    glEnable(GL_POLYGON_OFFSET_FILL); // caro openGL sposta i
    // frammenti generati dalla
    // rasterizzazione poligoni
    glPolygonOffset(1,1);

    initObj();

    bool cond=true;
    SDL_TimerID timerID;
    while(cond){
        SDL_Event event;
        if(!isPause){
            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                        bike.eventBike.EventButton(event.key.keysym.sym, true, comands);
                        if(event.key.keysym.sym==SDLK_RSHIFT | event.key.keysym.sym==SDLK_LSHIFT){
                            camera.EventShift(true);
                        }
                        switch (event.key.keysym.sym){
                            case SDLK_TAB://On/Off visualizza mappa
                                showTrackMap=!showTrackMap;
                                break;
                            case SDLK_l://On/Off faro moto
                                isOnHeadlight=!isOnHeadlight;
                                break;
                            case SDLK_p:
                                isPause=!isPause;
                                rendering(window);
                                break;
                            case SDLK_F1://cambia camera
                                camera.UpdateIndexCamera();
                                break;
                            case SDLK_F2://On/Off visualizza wireframe
                                useWireframe=!useWireframe;
                                break;
                            case SDLK_F3://On/Off visualizza ombre
                                isShadow=!isShadow;
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        bike.eventBike.EventButton(event.key.keysym.sym, false, comands);
                        if(event.key.keysym.sym==SDLK_RSHIFT | event.key.keysym.sym==SDLK_LSHIFT){
                            camera.EventShift(false);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        switch (menu.ButtonPress(event.button.x, event.button.y)){
                            case 1://On/Off faro moto
                                isOnHeadlight=!isOnHeadlight;
                                break;
                            case 2://On/Off visualizza ombre
                                isShadow=!isShadow;
                                break;
                            case 3://On/Off visualizza wireframe
                                useWireframe=!useWireframe;
                                break;
                            case 4://cambia camera
                                camera.UpdateIndexCamera();
                                break;
                            case 5://On/Off visualizza mappa
                                showTrackMap=!showTrackMap;
                                break;
                            case 6://esci
                                SetEndPlay();
                                break;
                            case 9:
                                startPlay= true;
                                timePlay=true;
                                timeGame=60;
                                //todo startTimer
                                timerID = SDL_AddTimer( 60 * 1000, EndTimer, (void*)"60 seconds waited!" );
                                timerVideo = SDL_AddTimer( 1 * 1000, UpdateTimerVideo, (void*)"1 seconds waited!" );
                                break;
                            case 10:
                                startPlay= true;
                                timePlay=false;
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
                    case SDL_JOYAXISMOTION:
                        if(event.jaxis.axis==0){
                            if(event.jaxis.value>3200){
                                bike.eventBike.EventButton(SDLK_d, true, comands);
                                bike.eventBike.EventButton(SDLK_a, false, comands);
                            }
                            if(event.jaxis.value<-3200){
                                bike.eventBike.EventButton(SDLK_a, true, comands);
                                bike.eventBike.EventButton(SDLK_d, false, comands);
                            }
                            if(event.jaxis.value<=3200 && event.jaxis.value>=-3200 ){
                                bike.eventBike.EventButton(SDLK_a, false, comands);
                                bike.eventBike.EventButton(SDLK_d, false, comands);
                            }
                        }
                        break;
                    case SDL_JOYBUTTONDOWN:
                        switch (event.jbutton.button){
                            case 0://Triangolo-->
                                bike.eventBike.EventButton(SDLK_w, true, comands);
                                break;
                            case 1://Cerchio-->On/Off faro moto
                                isOnHeadlight=!isOnHeadlight;
                                break;
                            case 2://X-->
                                bike.eventBike.EventButton(SDLK_s, true, comands);
                                break;
                            case 3://Quadrato-->On/Off visualizza mappa
                                showTrackMap=!showTrackMap;
                                break;
                            case 4://L2-->On/Off visualizza wireframe
                                useWireframe=!useWireframe;
                                break;
                            case 5://R2-->Camera retromarcia
                                camera.EventShift(true);
                                break;
                            case 6://L1-->On/Off visualizza ombre
                                isShadow=!isShadow;
                                break;
                            case 7://R1-->cambia camera
                                camera.UpdateIndexCamera();
                                break;
                            case 8://SELECT-->esci
                                SetEndPlay();
                                break;
                            case 9://START-->pausa
                                isPause=!isPause;
                                rendering(window);
                                break;
                        }
                        break;
                    case SDL_JOYBUTTONUP:
                        if(event.jbutton.button==0){
                            bike.eventBike.EventButton(SDLK_w, false, comands);
                        }
                        if(event.jbutton.button==1){
                            bike.eventBike.EventButton(SDLK_s, false, comands);
                        }
                        if(event.jbutton.button==5){
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
                    case SDL_QUIT:
                        cond=false;
                        break;
                }
            }else{
                bike.ChangeState();
                point=coin.ChangeState(bike.positionOnX, bike.positionOnZ);
                rendering(window);
            }
        }else{
            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym==SDLK_p){
                            isPause=!isPause;
                            rendering(window);
                        }
                        break;
                    case SDL_JOYBUTTONDOWN:
                        if(event.jbutton.button==8){
                            SetEndPlay();
                        }
                        if(event.jbutton.button==9){
                            isPause=!isPause;
                            rendering(window);
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
                    case SDL_QUIT:
                        cond=false;
                        break;
                }
            }
        }
    }
    SDL_GL_DeleteContext(sdlContext);
    SDL_DestroyWindow(window);
    SDL_Quit ();
    return (0);
}

/**
 *
 * Tastiera
 *
 * W --> Accellera
 * S --> Decellera sino a retromarcia
 * A --> Svolta a sinistra
 * D --> Svolta a destra
 *
 * P --> Mette il gioco in pausa
 * L --> Accende faro moto
 * SHIFT --> Camera retromarcia
 * TAB --> Visualizza mappa
 * F1 --> Cambia telecamera; Esistono 5 telecamere diverse
 * F2 --> Cambia l'uso dei Wireframe
 * F3 --> Scegli se visualizzare o meno l'ombra degli oggetti
 *
 *
 *
 *
 * Joystick
 *
 * Freccia sinistra --> Svolta a sinistra
 * Freccia destra --> Svolta a destra
 *
 * Triangolo-->Accellera
 * Cerchio-->On/Off faro moto
 * X-->Decellera sino a retromarcia
 * Quadrato-->On/Off visualizza mappa
 *
 * L1-->On/Off visualizza ombre
 * L2-->On/Off visualizza wireframe
 * R1-->Cambia camera
 * R2-->Camera retromarcia
 *
 * START--> Mette il gioco in pausa
 * SELECT-->Esce dal gioco
 *
 *
 */