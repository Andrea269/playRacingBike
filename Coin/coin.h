//
// Created by andrea on 13/07/18.
//
#ifndef GRAFICA_COIN_H
#define GRAFICA_COIN_H
#endif //GRAFICA_COIN_H


class Coin{
public:
    void Render(float orientation, float positionOnX, float positionOnY, float positionOnZ); // disegna la moneta a schermo
    void ChangeState();
    Coin(){
        coinRotation=1;
    }

    float coinRotation;
    const float speedRotation = 7;
};