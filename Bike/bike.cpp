//
// Created by andrea on 3/07/18.
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

#include "bike.h"

#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"

//todo radrizzare da blander la moto e alzare ruota avanti

Mesh bodyBike((char *)"Bike/BikeMesh/BodyBike.obj");
Mesh seat((char *)"Bike/BikeMesh/SeatBike.obj");
Mesh glass((char *)"Bike/BikeMesh/GlassBike.obj");
Mesh shell((char *)"Bike/BikeMesh/ShellBike.obj");
Mesh frontWheel((char *)"Bike/BikeMesh/FrontWheelBike.obj");
Mesh frontWheelRim((char *)"Bike/BikeMesh/FrontWheelRimBike.obj");
Mesh backWheel((char *)"Bike/BikeMesh/BackWheelBike.obj");
Mesh backWheelRim((char *)"Bike/BikeMesh/BackWheelRimBike.obj");
Mesh cylinder((char *)"Bike/BikeMesh/CylinderBike.obj");
Mesh knobs((char *)"Bike/BikeMesh/KnobsBike.obj");
Mesh brakes((char *)"Bike/BikeMesh/BrakesBike.obj");

extern bool isOnHeadlight;

void EventBike::EventButton(int button, bool isPressed, int* comands){
    for (int i=0; i<NBUTTON; i++){
        if(button==comands[i]){
            isButtonPres[i]=isPressed;
        }
    }
}


void Bike::Render() const{//todo ruote oscillano SISTEMARE
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY, positionOnZ);
    glRotatef(orientation, 0, 1, 0);

    if(isOnHeadlight){
        OnHeadlight(0, 0, 0);
    }

    RenderBike(false);

    //RenderBike(true); todo


    glPopMatrix();
}

void Bike::OnHeadlight(float x, float y, float z) const{//todo implementare faro moto con luce direzionale


/*


//(float x, float y, float z, int lightN, bool useHeadlight)
        int usedLight=GL_LIGHT1 + lightN;

        if(useHeadlight)
        {
            glEnable(usedLight);

            float col0[4]= {0.8,0.8,0.0,  1};
            glLightfv(usedLight, GL_DIFFUSE, col0);

            float col1[4]= {0.5,0.5,0.0,  1};
            glLightfv(usedLight, GL_AMBIENT, col1);

            float tmpPos[4] = {x,y,z,  1}; // ultima comp=1 => luce posizionale
            glLightfv(usedLight, GL_POSITION, tmpPos );

            float tmpDir[4] = {0,0,-1,  0}; // ultima comp=1 => luce posizionale
            glLightfv(usedLight, GL_SPOT_DIRECTION, tmpDir );

            glLightf (usedLight, GL_SPOT_CUTOFF, 30);
            glLightf (usedLight, GL_SPOT_EXPONENT,5);

            glLightf(usedLight,GL_CONSTANT_ATTENUATION,0);
            glLightf(usedLight,GL_LINEAR_ATTENUATION,1);
        }
        else
            glDisable(usedLight);
*/
}

void Bike::RenderBike(bool isShadow) const{//todo modificare per disegnare anche l'ombra della moto ciè senza colori e proiettata a terra

    glScalef(-0.03,0.03,-0.03);
    glTranslate(  bodyBike.Center() );
    glRotatef(steeringWheel, 0, 0, 1);//inclinazione moto per svolta destra o sinistra
    glTranslate(  -bodyBike.Center() );


    glTranslatef(0, -backWheel.bbmin.Y(), 0);

    glColor3f(0, 0, 1);
    bodyBike.RenderNxV();
    glColor3f(0, 0, 0);
    seat.RenderNxV();

    glPushMatrix();
    glTranslate(  backWheel.Center() );
    glRotatef(-wheelRotation, 1, 0, 0);
    glTranslate( -backWheel.Center() );
    glColor3f(0.2, 0.2, 0.2);
    backWheel.RenderNxF();
    glColor3f(0.9, 0.9, 0.9);
    backWheelRim.RenderNxV();
    glPopMatrix();

    shell.RenderNxV();

    glPushMatrix();
    glTranslate(  frontWheel.Center() );
    glRotatef(handlebars ,0,1,0);
    glTranslate( -frontWheel.Center() );

    cylinder.RenderNxV();
    brakes.RenderNxV();
    glColor3f(0, 0, 0);
    knobs.RenderNxV();
    glColor3f(1, 1, 1);
    glass.RenderNxV();

    glPushMatrix();
    glTranslate(  frontWheel.Center() );
    glRotatef(-wheelRotation, 1, 0, 0);
    glTranslate( -frontWheel.Center() );
    glColor3f(0.2, 0.2, 0.2);
    frontWheel.RenderNxF();
    glColor3f(0.9, 0.9, 0.9);
    frontWheelRim.RenderNxV();
    glPopMatrix();
    glPopMatrix();

}

void Bike::ChangeState(){
    // da velocità frame mondo a velocità frame moto
    float angleOrientation=orientation*M_PI/180.0;
    float cosOrietation = cos(angleOrientation);
    float sinOrietation = sin(angleOrientation);

    float speedOnXBike = (cosOrietation*speedOnX - sinOrietation*speedOnZ)*frictionOnX;//velocità attuale moto asse X
    float speedOnZBike = (sinOrietation*speedOnX + cosOrietation*speedOnZ)*frictionOnZ;//velocità attuale moto asse Z


    if(eventBike.isButtonPres[W]){//accellero
        speedOnZBike-=acceleration;
    }
    if(eventBike.isButtonPres[S]){//retromarcia
        speedOnZBike+=acceleration;
    }
    if(eventBike.isButtonPres[A]){//sterzo a sinistra
        if(steeringWheel>-maxInclinationBike){
            steeringWheel-=speedSteering;
        }
        if(handlebars<maxSteeringHandlebars){
            handlebars+=speedHandlebars;
        }
    }
    if(eventBike.isButtonPres[D]){//sterzo a destra
        if(steeringWheel<maxInclinationBike){
            steeringWheel+=speedSteering;
        }
        if(handlebars>-maxSteeringHandlebars){
            handlebars-=speedHandlebars;
        }
    }
    if(!eventBike.isButtonPres[A] && !eventBike.isButtonPres[D]){//ritorno sterzo
        steeringWheel*=returnSpeedSteering;
        handlebars*=returnSpeedSteering;
    }

    //aggiorno stato moto
    orientation = orientation - (speedOnZBike*grip)*-steeringWheel;//aggiorno orientamento moto
    wheelRotation+=(360.0*speedOnZBike)/(2.0*M_PI*wheelSpoke);//aggiorno velocita rotazione ruote
    speedOnX = cosOrietation*speedOnXBike + sinOrietation*speedOnZBike;//aggiorno velocità moto sull'asse X in relazione all'ambiente
    speedOnZ = cosOrietation*speedOnZBike - sinOrietation*speedOnXBike;//aggiorno velocità moto sull'asse Z in relazione all'ambiente
    positionOnX+=speedOnX;//aggiorno posizione moto sull'asse X
    positionOnZ+=speedOnZ;//aggiorno posizione moto sull'asse Z
}