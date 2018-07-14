//
// Created by andrea on 13/07/18.
//
#ifndef GRAFICA_COIN_H
#define GRAFICA_COIN_H
#endif //GRAFICA_COIN_H


class Coin{
public:
    void InitCoin(float x, float z);
    void Render(); // disegna la moneta a schermo
    int ChangeState(float x, float z);
    Coin(){
        coinRotation=1;
        positionOnY=0.5;
        positionOnX, positionOnZ=0;
        destroy=false;
    }

    float positionOnX, positionOnY, positionOnZ;
    float coinRotation;
    bool destroy;
    const float speedRotation = 7;
    const float rangeBike = 1.5;
};