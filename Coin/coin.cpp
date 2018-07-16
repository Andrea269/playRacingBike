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

#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"

// todo creare monete nel file blender della pista in posti precisi
const int MAX_COINS=4;
Mesh coin1((char *)"Coin/coin1.obj");
Mesh coin2((char *)"Coin/coin2.obj");
Mesh coin3((char *)"Coin/coin3.obj");
Mesh coin4((char *)"Coin/coin4.obj");
Mesh* coins[MAX_COINS];
bool destroy[MAX_COINS];

void Coin::InitCoin() {
    coins[0]=&coin4;
    coins[1]=&coin1;
    coins[2]=&coin2;
    coins[3]=&coin3;
    for (int i = 0; i < MAX_COINS; i++) {
        destroy[i]=false;
    }
}

void Coin::Render() {
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY, positionOnZ);

    glScalef(-scale,scale,-scale);
    glBindTexture(GL_TEXTURE_2D,0);

    for (int i = 0; i < MAX_COINS; i++) {
        if(!destroy[i]){
            glPushMatrix();
            SetupCoinTexture(coins[i]->bbmin.Z(), coins[i]->bbmax.Z(), coins[i]->bbmin.Y(), coins[i]->bbmax.Y());
            glTranslate(coins[i]->Center());
            glRotatef(coinRotation, 1, 1, 1);
            glTranslate(-coins[i]->Center());
            coins[i]->RenderNxV();
            glPopMatrix();
        }
    }

    glPopMatrix();
    coinRotation+=speedRotation;
}

int Coin::ChangeState(float xBike, float zBike) {
    float x=-xBike/scale;
    float z=-zBike/scale;
    for (int i = 0; i < MAX_COINS; i++) {
        if(!destroy[i]){
            if(coins[i]->Center().X()>x-rangeBike && coins[i]->Center().X()<x+rangeBike &&
               coins[i]->Center().Z()>z-rangeBike && coins[i]->Center().Z()<z+rangeBike){
                destroy[i]=true;
                coinDestroy++;
            }
        }
    }
    return coinDestroy;
}

void Coin::SetupCoinTexture(float minZ, float maxZ, float minY, float maxY){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ulilizzo le coordinate OGGETTO
    // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
    // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/(maxZ - minZ);
    float ty=1.0/(maxY - minY);
    float s[4]={0,0,sz,  - minZ*sz };
    float t[4]={0,ty,0,  - minY*ty };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, t);
}
