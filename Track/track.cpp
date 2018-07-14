//
// Created by andrea on 14/07/18.
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


#include "track.h"



Mesh trackMesh((char *)"Track/track3.obj");

void Track::InitTrack(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Track::Render() {
    glPushMatrix();
   // glTranslatef(positionOnX+27, positionOnY, positionOnZ-30);
    glTranslatef(positionOnX-10, positionOnY, positionOnZ-20);

    glScalef(-10,10,-10);

    SetupRoadTexture(trackMesh.bbmin, trackMesh.bbmax);
    trackMesh.RenderNxV();


//    glTranslatef(positionOnX, positionOnY, positionOnZ+1.5);
//   // SetupRoadTexture(trackMesh.bbmin, trackMesh.bbmax);
//    trackMesh.RenderNxV();

    glPopMatrix();
}

void Track::SetupRoadTexture(Point3 min, Point3 max){
    glBindTexture(GL_TEXTURE_2D,1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ulilizzo le coordinate OGGETTO
    // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
    // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/(max.Z() - min.Z());
    float sx=1/(max.X() - min.X());
    float s[4]={sx, 0,0, - min.X()*sx };
    float t[4]={0,0,sz,  - min.Z()*sz };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, t);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, s);



/*    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sx=1/(max.X() - min.X());
    float s[4]={max.X()*sx, 0,0, - min.X()*sx };
    glTexGenfv(GL_T, GL_OBJECT_PLANE, s);



*/
}