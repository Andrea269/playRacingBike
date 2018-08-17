//
// Created by andrea on 7/07/18.
//

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "menu.h"
TTF_Font *fontText;
SDL_Color colorTemp;

void Menu::Init(){
    if (! TTF_WasInit () && TTF_Init () == - 1) {
        printf ("TTF_Init:% s \n", TTF_GetError ());
        exit (1);
    }
    fontText=TTF_OpenFont("Roboto-Light.ttf", 20);
    colorTemp = {0,0,0,0};
}

//inizializzo il menu
void Menu::InitMenu(int width, int height){
    int startMenuW = (width*5/6) + indentMenu;
    heightMenu=height;
    itemsMenu[0].id = "Punteggio: ";
    itemsMenu[0].x = startMenuW;
    itemsMenu[0].y = height-50;
    itemsMenu[0].w = 150;
    itemsMenu[0].h = 30;

    itemsMenu[1].id = "On/Off Faro moto";
    itemsMenu[1].x = startMenuW;
    itemsMenu[1].y = ((height/7)*6)-50;
    itemsMenu[1].w = 150;
    itemsMenu[1].h = 30;

    itemsMenu[2].id = "On/Off Ombra";
    itemsMenu[2].x = startMenuW;
    itemsMenu[2].y = ((height/7)*5)-50;
    itemsMenu[2].w = 150;
    itemsMenu[2].h = 30;

    itemsMenu[3].id = "On/Off Wireframe";
    itemsMenu[3].x = startMenuW;
    itemsMenu[3].y = ((height/7)*4)-50;
    itemsMenu[3].w = 150;
    itemsMenu[3].h = 30;

    itemsMenu[4].id = "Cambia camera";
    itemsMenu[4].x = startMenuW;
    itemsMenu[4].y = ((height/7)*3)-50;
    itemsMenu[4].w = 150;
    itemsMenu[4].h = 30;

    itemsMenu[5].id = "Mappa";
    itemsMenu[5].x = startMenuW;
    itemsMenu[5].y = ((height/7)*2)-50;
    itemsMenu[5].w = 70;
    itemsMenu[5].h = 30;

    itemsMenu[6].id = "Esci";
    itemsMenu[6].x = startMenuW;
    itemsMenu[6].y = (height/7)-50;
    itemsMenu[6].w = 50;
    itemsMenu[6].h = 30;

    itemsMenu[7].id = "PAUSA";
    itemsMenu[7].x = startMenuW/2;
    itemsMenu[7].y = height*3/5;
    itemsMenu[7].w = 100;
    itemsMenu[7].h = 70;


    itemsMenu[8].id = "Giro a tempo";
    itemsMenu[8].x = (width/2)-100;
    itemsMenu[8].y = height*2/6;
    itemsMenu[8].w = 200;
    itemsMenu[8].h = 70;


    itemsMenu[9].id = "Giro libero";
    itemsMenu[9].x = (width/2)-100;
    itemsMenu[9].y = height*4/6;
    itemsMenu[9].w = 200;
    itemsMenu[9].h = 70;
}

void Menu::DrawButton(int totalPoint){
    structMenu item;
    char* id;
    int x,y,w,h;
    int *wx;
    int *hx;

    SDL_Surface *renderText;
    SDL_Surface *intermediary;
    //setto il font del testo
    int initI=0;
    int limitElement=-3;
    if(totalPoint==-1){
        initI=(sizeof(itemsMenu)/ sizeof(itemsMenu[0]))-3;
        limitElement=-2;
    }
    if(totalPoint==-2){
        initI=(sizeof(itemsMenu)/ sizeof(itemsMenu[0]))-2;
        limitElement=0;
    }

    for (int i = initI; i < (sizeof(itemsMenu)/ sizeof(itemsMenu[0]))+limitElement; ++i) {
        item=itemsMenu[i];
        if(i==0){
            id=(char *)(item.id+to_string(totalPoint)).c_str();
        }else{
            id=(char *)(item.id).c_str();
        }
        x=item.x;
        y=item.y;
        w=item.w;
        h=item.h;

        //Viene utilizzato SDL_TTF per il render del testo del bottone codificandolo secondo il font scelto
        renderText=TTF_RenderText_Blended(fontText, id, colorTemp);
        wx = &renderText->w;
        hx = &renderText->h;

        //Creo una maschewra RGB per il testo
        intermediary = SDL_CreateRGBSurface(3, *wx, *hx, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        SDL_BlitSurface(renderText, 0, intermediary, 0);

        // Tell GL about our new texture
        glBindTexture(GL_TEXTURE_2D, 10);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, *wx, *hx, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, intermediary->pixels);
        glEnable(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(renderText);
        SDL_FreeSurface(intermediary);


        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_BLEND);
        //prepara il render della texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 10);

        // disegno bottone
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x, y);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x+w , y);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x+w , y+h );
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x, y+h );
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        //bordo bottone
        if(!i==(sizeof(itemsMenu)/ sizeof(itemsMenu[0]))-3){
            glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex2i(x-1,y-1);
            glVertex2i(x+w+1, y-1);
            glVertex2i(x+w+1, y+h+1);
            glVertex2i(x-1,y+h+1);
            glEnd();
        }
    }
}

void Menu::DrawMenu(int width, int height, int totalPoint){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    DrawButton(totalPoint);

    //Background
    glColor3ub(200, 200, 200);
    glBegin(GL_QUADS);
    glVertex2i(width * 5/6, 0);
    glVertex2i(width, 0);
    glVertex2i(width, height);
    glVertex2i(width * 5/6, height);
    glEnd();
}

int Menu::ButtonPress(int cordX, int cordY){
    int ret= sizeof(itemsMenu)/ sizeof(itemsMenu[0]);
    int i = 0;
    structMenu item;
    while(i < ret){
        item=itemsMenu[i];
        if(item.x<cordX && (item.x+item.w)>cordX && (heightMenu-item.y)>cordY && (heightMenu-item.y-item.h)<cordY){
            ret=i;
        }
        i++;
    }
    return ret;
}

void Menu::DrawPause(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawButton(-1);
}

void Menu::DrawStart(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawButton(-2);
}