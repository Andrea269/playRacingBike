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


Mesh coinMesh((char *)"Coin/Coin.obj");

void Coin::InitCoin(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Coin::Render() {
    if(!destroy){
        glPushMatrix();
        glTranslatef(positionOnX, positionOnY, positionOnZ);

        glScalef(-0.25,0.25,-0.25);

        glTranslate(coinMesh.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coinMesh.Center());

        glBindTexture(GL_TEXTURE_2D,0);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        // ulilizzo le coordinate OGGETTO
        // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
        // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
        float sz=1.0/(coinMesh.bbmax.Z() - coinMesh.bbmin.Z());
        float ty=1.0/(coinMesh.bbmax.Y() - coinMesh.bbmin.Y());
        float s[4]={0,0,sz,  - coinMesh.bbmin.Z()*sz };
        float t[4]={0,ty,0,  - coinMesh.bbmin.Y()*ty };
        glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
        glTexGenfv(GL_T, GL_OBJECT_PLANE, t);

        // glColor3f( 255, 215, 0);
        coinMesh.RenderNxV();

        glPopMatrix();
        coinRotation+=speedRotation;
    }
}

int Coin::ChangeState(float x, float z) {
    int res=0;
    if(!destroy && positionOnX>x-rangeBike && positionOnX<x+rangeBike && positionOnZ>z-rangeBike && positionOnZ<z+rangeBike){
        destroy=true;
        res=1;
    }
    return res;
}
