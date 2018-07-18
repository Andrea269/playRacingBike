//
// Created by andrea on 3/07/18.
//
enum {NBUTTON=4, W=0, S=1, A=2, D=3};

class EventBike{
public:
    void EventButton(int button, bool isPressed, int* comands);
    EventBike(){
        for (int i=0; i<NBUTTON; i++){
            isButtonPres[i]=false;
        }
    }

    bool isButtonPres[NBUTTON];
};

class Bike{
public:
    void Render() const; // disegna la moto a schermo
    void ChangeState();
    Bike(){
        positionOnX, positionOnY, positionOnZ=0.0;
        speedOnX, speedOnY, speedOnZ=0.0;
        orientation=180;
        steeringWheel=0.0;
        handlebars=0.0;
        wheelRotation=0.0;
    }

    //var stato Bike
    EventBike eventBike;
    float positionOnX, positionOnY, positionOnZ;
    float speedOnX, speedOnY, speedOnZ;
    float orientation;
    float steeringWheel;
    float handlebars;
    float wheelRotation;

    //costanti fisica Bike
    const float maxInclinationBike= 35;
    const float maxSteeringHandlebars= 15;
    const float speedSteering= 2;
    const float speedHandlebars= 0.8;
    const float returnSpeedSteering= 0.95;
    const float frictionOnX= 0.8;
    const float frictionOnY= 1.0;
    const float frictionOnZ= 0.999;
    const float acceleration= 0.005;
    const float grip = 0.45;
    const float wheelSpoke = 0.8;
private:
    void RenderBike(bool isShadow) const;
    void OnHeadlight(float x, float y, float z, int intensityLight) const;
};