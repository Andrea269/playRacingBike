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

//inizializzo il menu
void Menu::InitMenu(int width, int height){// todo impostare voci menu e relativa posizione
    int startMenuW = (width*5/6) + indentMenu;
    heightMenu=height;
    itemsMenu[0].id = "Esci";
    itemsMenu[0].x = startMenuW;
    itemsMenu[0].y = (height/7)-50;
    itemsMenu[0].w = 50;
    itemsMenu[0].h = 30;

/*
    menu[0].id = "Esci";
    menu[0].x = startMenuW;
    menu[0].y = 15;
    menu[0].w = 34;
    menu[0].h = 30;

    menu[1].id = "TEXTURE";
    menu[1].x = startMenuW;
    menu[1].y = height - 200;
    menu[1].w = 84;
    menu[1].h = 24;

    menu[2].id = "WIREFRAME";
    menu[2].x = startMenuW;
    menu[2].y = height - 250;
    menu[2].w = 110;
    menu[2].h = 24;

    menu[3].id = "Zoom [ + ]";
    menu[3].x = startMenuW;
    menu[3].y = height - 300;
    menu[3].w = 110;
    menu[3].h = 24;

    menu[4].id = "Zoom [ - ]";
    menu[4].x = startMenuW;
    menu[4].y = height - 330;
    menu[4].w = 110;
    menu[4].h = 24;

    menu[5].id = "LIGHT(Plane)";
    menu[5].x = startMenuW;
    menu[5].y = height - 150;
    menu[5].w = 110;
    menu[5].h = 24;
*/
}

void Menu::DrowButton(){
    structMenu item;
    for (int i = 0; i < (sizeof(itemsMenu)/ sizeof(itemsMenu[0])); ++i) {
        item=itemsMenu[i];
        char* id=(char *)(item.id).c_str();
        int x=item.x;
        int y=item.y;
        int w=item.w;
        int h=item.h;

        //setto il font del testo
        TTF_Font *fontText=TTF_OpenFont("Roboto-Light.ttf", 20);
        SDL_Color colorTemp = {0,0,0,0};
        //Viene utilizzato SDL_TTF per il render del testo del bottone codificandolo secondo il font scelto
        SDL_Surface *renderText=TTF_RenderText_Blended(fontText, id, colorTemp);
        int *wx = &renderText->w;
        int *hx = &renderText->h;

        //Creo una maschewra RGB per il testo
        SDL_Surface *intermediary = SDL_CreateRGBSurface(3, *wx, *hx, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
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
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(x-1,y-1);
        glVertex2i(x+w+1, y-1);
        glVertex2i(x+w+1, y+h+1);
        glVertex2i(x-1,y+h+1);
        glEnd();
    }


}

//todo capire perchè il menù viene renderizzato male
void Menu::DrawMenu(int width, int height, int totalPoint){//todo gestire la visualizzazione dei coin raccolti
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (! TTF_WasInit () && TTF_Init () == - 1) {
        printf ("TTF_Init:% s \n", TTF_GetError ());
        exit (1);
    }

    DrowButton();

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