//
// Created by andrea on 13/07/18.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>

#include "coin.h"

#include "../Mesh/mesh.h"

// todo creare monete nel file blender della pista in posti precisi

Mesh coin1((char *)"Coin/coin1.obj");
Mesh coin2((char *)"Coin/coin2.obj");
Mesh coin3((char *)"Coin/coin3.obj");
Mesh coin4((char *)"Coin/coin4.obj");

void Coin::InitCoin(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Coin::Render() {
    if(!destroy){
        glPushMatrix();
        glTranslatef(positionOnX, positionOnY, positionOnZ);

        glScalef(-10,10,-10);
        glBindTexture(GL_TEXTURE_2D,0);

        glPushMatrix();
        SetupCoinTexture(coin1.bbmin, coin1.bbmax);
        glTranslate(coin1.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coin1.Center());
        coin1.RenderNxV();
        glPopMatrix();

        glPushMatrix();
        SetupCoinTexture(coin2.bbmin, coin2.bbmax);
        glTranslate(coin2.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coin2.Center());
        coin2.RenderNxV();
        glPopMatrix();

        glPushMatrix();
        SetupCoinTexture(coin3.bbmin, coin3.bbmax);
        glTranslate(coin3.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coin3.Center());
        coin3.RenderNxV();
        glPopMatrix();

        glPushMatrix();
        SetupCoinTexture(coin4.bbmin, coin4.bbmax);
        glTranslate(coin4.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coin4.Center());
        coin4.RenderNxV();
        glPopMatrix();


        glPopMatrix();
        coinRotation+=speedRotation;
    }
}

int Coin::ChangeState(float x, float z) {//todo modificare
    int res=0;
    if(!destroy && positionOnX>x-rangeBike && positionOnX<x+rangeBike && positionOnZ>z-rangeBike && positionOnZ<z+rangeBike){
        destroy=true;
        res=1;
    }
    return res;
}

void Coin::SetupCoinTexture(Point3 min, Point3 max){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ulilizzo le coordinate OGGETTO
    // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
    // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/(max.Z() - min.Z());
    float ty=1.0/(max.Y() - min.Y());
    float s[4]={0,0,sz,  - min.Z()*sz };
    float t[4]={0,ty,0,  - min.Y()*ty };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, t);
}
