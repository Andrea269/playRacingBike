//
// Created by andrea on 7/07/18.
//

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "camera.h"

//inizializzo i dati delle camere
void Camera::InitCamera(){
    //camera posizionata dietro la moto
    cameras[0].distance= 2.9;
    cameras[0].height= 1;
    cameras[0].plusAngle= 0;
    cameras[0].plusEY= 1;
    //camera posizionata d'avanti alla moto
    cameras[1].distance= 0.1;
    cameras[1].height= 1.5;
    cameras[1].plusAngle= -10;
    cameras[1].plusEY= 0.1;
    //camera con vista dall'alto
    cameras[2].distance= 2.9;
    cameras[2].height= 1;
    cameras[2].plusAngle= 0;
    cameras[2].plusEY= 6;
    //camera pilota
    cameras[3].distance= 0.5;
    cameras[3].height= 1.5;
    cameras[3].plusAngle= 0;
    cameras[3].plusEY= 0;
}

void Camera::UpdateCamera(float orientation, float positionOnX, float positionOnY, float positionOnZ){

    if(indexCamera==4){
        glTranslatef(0,0,-eyeDistance);
        glRotatef(viewBeta,  1,0,0);
        glRotatef(viewAlpha, 0,1,0);
    }else{
        double eyeX, eyeY, eyeZ, centerX, centerY, centerZ;
        double angleOrientation;
        double cosOrietation;
        double sinOrietation;
        if(oppositeView){
            angleOrientation= (180+orientation)*M_PI/180.0;
            double cosOrietation= cos(angleOrientation);
            double sinOrietation= sin(angleOrientation);
            eyeX= positionOnX + cameras[3].distance * sinOrietation;
            eyeY= positionOnY + cameras[3].height + cameras[3].plusEY;
            eyeZ= positionOnZ + cameras[3].distance * cosOrietation;
            centerX= positionOnX - cameras[3].distance * sinOrietation;
            centerY= positionOnY + cameras[3].height+0.2;
            centerZ= positionOnZ - cameras[3].distance * cosOrietation;
        }else{
            angleOrientation= (cameras[indexCamera].plusAngle+orientation)*M_PI/180.0;
            cosOrietation= cos(angleOrientation);
            sinOrietation= sin(angleOrientation);
            eyeX= positionOnX + cameras[indexCamera].distance * sinOrietation;
            eyeY= positionOnY + cameras[indexCamera].height + cameras[indexCamera].plusEY;
            eyeZ= positionOnZ + cameras[indexCamera].distance * cosOrietation;
            centerX= positionOnX - cameras[indexCamera].distance * sinOrietation;
            centerY= positionOnY + cameras[indexCamera].height;
            centerZ= positionOnZ - cameras[indexCamera].distance * cosOrietation;
        }
        gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
    }
}

void Camera::EventShift(bool cond){
    oppositeView=cond;
}

void Camera::UpdateIndexCamera(){
    indexCamera=(indexCamera+1)% ((sizeof(cameras)/ sizeof(cameras[0]))+1);
}

void Camera::UpdateEyeDistance(bool greater0, bool lower0){

    if(indexCamera==4){
        // avvicino il punto di vista (zoom in)
        if (greater0) {
            eyeDistance=eyeDistance*0.9;
            if (eyeDistance<1){
                eyeDistance = 1;
            }
        }
        // allontano il punto di vista (zoom out)
        if (lower0) {
            eyeDistance=eyeDistance/0.9;
        }
    }

}

void Camera::UpdateView(float x, float y){
    if (indexCamera==4) {
        viewAlpha+=x;
        viewBeta +=y;
        //per non andare sotto la pista
        if (viewBeta<+5){
            viewBeta=+5;
        }
        if (viewBeta>+90){
            viewBeta=+90;
        }
    }
}