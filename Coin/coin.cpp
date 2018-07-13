//
// Created by andrea on 13/07/18.
//

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


//todo
void Coin::Render(float orientation, float positionOnX, float positionOnY, float positionOnZ) {
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY+0.5, positionOnZ-3);
//    glRotatef(orientation, 0, 1, 0);

    glScalef(-0.3,0.3,-0.3);


    glTranslate(coinMesh.Center());
    glRotatef(coinRotation, 1, 1, 1);
    glTranslate(-coinMesh.Center());

    //glRotatef(coinRotation, 1, 0, 0);
    glColor3f( 255, 215, 0);
    coinMesh.RenderNxV();


    glPopMatrix();
    coinRotation+=speedRotation;
}

void Coin::ChangeState() {

}