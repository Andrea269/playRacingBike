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
Mesh inclinationReference((char *)"Bike/BikeMesh/InclinationReference.obj");

extern bool startPlay;
extern bool timePlay;
extern int secondsStart;
extern bool isOnHeadlight;
extern bool isShadow;
extern float worldLimit;
extern bool isOnTrack;


void EventBike::Init(){
    for (int i=0; i<NBUTTON; i++){
        isButtonPres[i]=false;
    }
}


void EventBike::EventButton(int button, bool isPressed, int* comands){
    bool condComands=false;
    if(startPlay){
        if(timePlay){
            if(secondsStart<0){
                condComands=true;
            }
        }else{
            condComands=true;
        }
    }
    if(condComands){
        for (int i=0; i<NBUTTON; i++){
            if(button==comands[i]){
                isButtonPres[i]=isPressed;
            }
        }
    }
}

void Bike::Init() {
    positionOnX=0.0;
    positionOnY=0.0;
    positionOnZ=0.0;
    speedOnX=0.0;
    speedOnY=0.0;
    speedOnZ=0.0;
    orientation=180;
    steeringWheel=0.0;
    handlebars=0.0;
    wheelRotation=0.0;

    frictionOnX= 0.8;
    frictionOnY= 1.0;
    frictionOnZ= 0.99;
    eventBike.Init();
}

void Bike::Render() const{
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY, positionOnZ);
    glRotatef(orientation, 0, 1, 0);

    RenderBike(false);
    if(isShadow){
        RenderBike(true);
    }

    glPopMatrix();
}

void Bike::OnHeadlight(float x, float y, float z, int intensityLight) const{

    glEnable(intensityLight);

    float col0[4]= {0.8,0.8,0.0,1};
    glLightfv(intensityLight, GL_DIFFUSE, col0);

    float col1[4]= {0.5,0.5,0.0,1};
    glLightfv(intensityLight, GL_AMBIENT, col1);

    float tmpPos[4] = {x,y,z,  1}; // ultima comp=1 => luce posizionale
    glLightfv(intensityLight, GL_POSITION, tmpPos );

    float tmpDir[4] = {0,0,1,  0}; // ultima comp=1 => luce posizionale
    glLightfv(intensityLight, GL_SPOT_DIRECTION, tmpDir );

    glLightf (intensityLight, GL_SPOT_CUTOFF, 30);
    glLightf (intensityLight, GL_SPOT_EXPONENT,5);

    glLightf(intensityLight,GL_CONSTANT_ATTENUATION,0);
    glLightf(intensityLight,GL_LINEAR_ATTENUATION,0.1);

}

void Bike::RenderBike(bool isShadow) const{

    glPushMatrix();
    if(isShadow){
        glColor3f(0.4,0.4,0.4); // colore fisso
        glTranslatef(0,0.06,0); // alzo l'ombra di un epsilon per evitare z-fighting con il pavimento
        glScalef(1.01,0,1.01);  // appiattisco sulla Y, ingrandisco dell'1% sulla Z e sulla X
        glDisable(GL_LIGHTING); // niente lighing per l'ombra
    }else{
        glEnable(GL_LIGHTING);
    }
    glScalef(-0.4,0.4,-0.4);
    glRotatef(-2, 0, 0, 1);//allineamento moto
    glTranslate(  inclinationReference.Center() );
    glRotatef(steeringWheel, 0, 0, 1);//inclinazione moto per svolta destra o sinistra
    glTranslate(  -inclinationReference.Center() );
    if(!isShadow){

        if(isOnHeadlight){
            OnHeadlight(0, 2.5, 1.3, GL_LIGHT1 + 4);
        }else {
            glDisable(GL_LIGHT1 + 4);
        }
    }
    //glTranslatef(0, -backWheel.bbmin.Y(), 0);

    if(!isShadow){
        glColor3f(0, 0, 1);
    }
    bodyBike.RenderNxV();
    if(!isShadow){
        glColor3f(0, 0, 0);
    }
    seat.RenderNxV();

    glPushMatrix();
    glTranslate(  backWheel.Center() );
    glRotatef(-wheelRotation, 1, 0, 0);//rotazione ruota
    glRotatef(-2, 0, 0, 1);//allineamento ruota
    glTranslate( -backWheel.Center() );
    if(!isShadow){
        glColor3f(0.2, 0.2, 0.2);
    }
    backWheel.RenderNxV();
    if(!isShadow){
        glColor3f(0.9, 0.9, 0.9);
    }
    backWheelRim.RenderNxV();
    glPopMatrix();

    shell.RenderNxV();

    glPushMatrix();
    glTranslate(  frontWheel.Center() );
    glRotatef(handlebars ,0,1,0);
    glTranslate( -frontWheel.Center() );

    cylinder.RenderNxV();
    brakes.RenderNxV();
    if(!isShadow){
        glColor3f(0, 0, 0);
    }
    knobs.RenderNxV();
    if(!isShadow){
        glColor3f(1, 1, 1);
    }
    glass.RenderNxV();

    glPushMatrix();
    glTranslate(  frontWheel.Center() );
    glRotatef(-wheelRotation, 1, 0, 0);//rotazione ruota
    glRotatef(-2, 0, 0, 1);//allineamento ruota
    glTranslate( -frontWheel.Center() );
    if(!isShadow){
        glColor3f(0.2, 0.2, 0.2);
    }
    frontWheel.RenderNxV();
    if(!isShadow){
        glColor3f(0.9, 0.9, 0.9);
    }
    frontWheelRim.RenderNxV();
    glPopMatrix();
    glPopMatrix();
    if(isShadow){
        glEnable(GL_LIGHTING);
        glColor3f(1,1,1); // colore fisso
    }
    glPopMatrix();

}

void Bike::ChangeState(){
    if(isOnTrack){
        frictionOnX= 0.8;
        frictionOnZ= 0.99;
    }else{
        frictionOnX= 0.98;
        frictionOnZ= 1;
    }

    float limitBike=(pow(positionOnX,2))+(pow(positionOnZ,2));
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

    //se la posizione della moto oltrepassa i limiti del mondo non permetto l'aggiornamento della posizione
    if(limitBike<pow(worldLimit-2,2)){
        positionOnX+=speedOnX;//aggiorno posizione moto sull'asse X
        positionOnZ+=speedOnZ;//aggiorno posizione moto sull'asse X
    }else{
        if(positionOnX<0){
            positionOnX+=0.1;
        }else{
            positionOnX-=0.1;
        }
        if(positionOnZ<0){
            positionOnZ+=0.1;
        }else{
            positionOnZ-=0.1;
        }
    }
}