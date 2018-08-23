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
Mesh coin30((char *)"Coin/CoinMesh/coin30.obj");
Mesh coin31((char *)"Coin/CoinMesh/coin31.obj");
Mesh coin32((char *)"Coin/CoinMesh/coin32.obj");
Mesh coin33((char *)"Coin/CoinMesh/coin33.obj");
Mesh coin34((char *)"Coin/CoinMesh/coin34.obj");
Mesh coin35((char *)"Coin/CoinMesh/coin35.obj");
Mesh coin36((char *)"Coin/CoinMesh/coin36.obj");
Mesh coin37((char *)"Coin/CoinMesh/coin37.obj");
Mesh coin38((char *)"Coin/CoinMesh/coin38.obj");
Mesh coin39((char *)"Coin/CoinMesh/coin39.obj");
Mesh coin40((char *)"Coin/CoinMesh/coin40.obj");
Mesh coin41((char *)"Coin/CoinMesh/coin41.obj");
Mesh coin42((char *)"Coin/CoinMesh/coin42.obj");
Mesh coin43((char *)"Coin/CoinMesh/coin43.obj");
Mesh coin44((char *)"Coin/CoinMesh/coin44.obj");
Mesh coin45((char *)"Coin/CoinMesh/coin45.obj");
Mesh coin46((char *)"Coin/CoinMesh/coin46.obj");
Mesh coin47((char *)"Coin/CoinMesh/coin47.obj");
Mesh coin48((char *)"Coin/CoinMesh/coin48.obj");
Mesh coin49((char *)"Coin/CoinMesh/coin49.obj");
Mesh coin50((char *)"Coin/CoinMesh/coin50.obj");
Mesh coin51((char *)"Coin/CoinMesh/coin51.obj");
Mesh coin52((char *)"Coin/CoinMesh/coin52.obj");
Mesh coin53((char *)"Coin/CoinMesh/coin53.obj");
Mesh coin54((char *)"Coin/CoinMesh/coin54.obj");
Mesh coin55((char *)"Coin/CoinMesh/coin55.obj");
Mesh coin56((char *)"Coin/CoinMesh/coin56.obj");
Mesh coin57((char *)"Coin/CoinMesh/coin57.obj");
Mesh coin58((char *)"Coin/CoinMesh/coin58.obj");
Mesh coin59((char *)"Coin/CoinMesh/coin59.obj");

const int MAX_COINS=60;
Mesh* coins[MAX_COINS];
bool destroy[MAX_COINS];

extern bool isShadow;

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
    coins[30]=&coin30;
    coins[31]=&coin31;
    coins[32]=&coin32;
    coins[33]=&coin33;
    coins[34]=&coin34;
    coins[35]=&coin35;
    coins[36]=&coin36;
    coins[37]=&coin37;
    coins[38]=&coin38;
    coins[39]=&coin39;
    coins[40]=&coin40;
    coins[41]=&coin41;
    coins[42]=&coin42;
    coins[43]=&coin43;
    coins[44]=&coin44;
    coins[45]=&coin45;
    coins[46]=&coin46;
    coins[47]=&coin47;
    coins[48]=&coin48;
    coins[49]=&coin49;
    coins[50]=&coin50;
    coins[51]=&coin51;
    coins[52]=&coin52;
    coins[53]=&coin53;
    coins[54]=&coin54;
    coins[55]=&coin55;
    coins[56]=&coin56;
    coins[57]=&coin57;
    coins[58]=&coin58;
    coins[59]=&coin59;
}

void Coin::InitStatusCoin() {
    for (int i = 0; i < MAX_COINS; i++) {
        destroy[i]=false;
    }
    coinDestroy=0;
}

void Coin::Render() {
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY, positionOnZ);

    glScalef(-scale,scale,-scale);
    glBindTexture(GL_TEXTURE_2D,0);

    for (int i = 0; i < MAX_COINS; i++) {
        if(!destroy[i]){
            glPushMatrix();

            glPushMatrix();
            glTranslate(coins[i]->Center());
            glRotatef(coinRotation, 0, 1, 0);
            glTranslate(-coins[i]->Center());
            SetupCoinTexture(coins[i]->bbmin.Z(), coins[i]->bbmax.Z(), coins[i]->bbmin.Y(), coins[i]->bbmax.Y());
            coins[i]->RenderNxV();
            glPopMatrix();

            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_2D);
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
