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
const int MAX_COINS=10;//todo numero effettivo
Mesh coin0((char *)"Coin/CoinMesh/coin0.obj");
Mesh coin1((char *)"Coin/CoinMesh/coin1.obj");
Mesh coin2((char *)"Coin/CoinMesh/coin2.obj");
Mesh coin3((char *)"Coin/CoinMesh/coin3.obj");
Mesh coin4((char *)"Coin/CoinMesh/coin4.obj");
Mesh coin5((char *)"Coin/CoinMesh/coin5.obj");
Mesh coin6((char *)"Coin/CoinMesh/coin6.obj");
Mesh coin7((char *)"Coin/CoinMesh/coin7.obj");
Mesh coin8((char *)"Coin/CoinMesh/coin8.obj");
Mesh coin9((char *)"Coin/CoinMesh/coin9.obj");
/*
Mesh coin10((char *)"Coin/CoinMesh/coin10.obj");
Mesh coin11((char *)"Coin/CoinMesh/coin11.obj");
Mesh coin12((char *)"Coin/CoinMesh/coin12.obj");
Mesh coin13((char *)"Coin/CoinMesh/coin13.obj");
Mesh coin14((char *)"Coin/CoinMesh/coin14.obj");
Mesh coin15((char *)"Coin/CoinMesh/coin15.obj");
Mesh coin16((char *)"Coin/CoinMesh/coin16.obj");
Mesh coin17((char *)"Coin/CoinMesh/coin17.obj");
Mesh coin18((char *)"Coin/CoinMesh/coin18.obj");
Mesh coin19((char *)"Coin/CoinMesh/coin19.obj");
Mesh coin20((char *)"Coin/CoinMesh/coin20.obj");
Mesh coin21((char *)"Coin/CoinMesh/coin21.obj");
Mesh coin22((char *)"Coin/CoinMesh/coin22.obj");
Mesh coin23((char *)"Coin/CoinMesh/coin23.obj");
Mesh coin24((char *)"Coin/CoinMesh/coin24.obj");
Mesh coin25((char *)"Coin/CoinMesh/coin25.obj");
Mesh coin26((char *)"Coin/CoinMesh/coin26.obj");
Mesh coin27((char *)"Coin/CoinMesh/coin27.obj");
Mesh coin28((char *)"Coin/CoinMesh/coin28.obj");
Mesh coin29((char *)"Coin/CoinMesh/coin29.obj");
*/
Mesh* coins[MAX_COINS];
bool destroy[MAX_COINS];

void Coin::InitCoin() {
    coins[0]=&coin0;
    coins[1]=&coin1;
    coins[2]=&coin2;
    coins[3]=&coin3;
    coins[4]=&coin4;
    coins[5]=&coin5;
    coins[6]=&coin6;
    coins[7]=&coin7;
    coins[8]=&coin8;
    coins[9]=&coin9;
    /*
    coins[10]=&coin10;
    coins[11]=&coin11;
    coins[12]=&coin12;
    coins[13]=&coin13;
    coins[14]=&coin14;
    coins[15]=&coin15;
    coins[16]=&coin16;
    coins[17]=&coin17;
    coins[18]=&coin18;
    coins[19]=&coin19;
    coins[20]=&coin20;
    coins[21]=&coin21;
    coins[22]=&coin22;
    coins[23]=&coin23;
    coins[24]=&coin24;
    coins[25]=&coin25;
    coins[26]=&coin26;
    coins[27]=&coin27;
    coins[28]=&coin28;
    coins[29]=&coin29;
     */
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
