//
// Created by andrea on 13/07/18.
//
#ifndef GRAFICA_COIN_H
#define GRAFICA_COIN_H
#endif //GRAFICA_COIN_H


class Coin{
public:
    void InitCoin();
    void Render(); // disegna la moneta a schermo
    int ChangeState(float x, float z);
    Coin(){
        coinRotation=1;
        positionOnY=0.1;
        positionOnX, positionOnZ=0;
        coinDestroy=0;
        InitCoin();
    }

    float positionOnX, positionOnY, positionOnZ;
    float coinRotation;
    int coinDestroy;
    const float speedRotation = 7;
    const float rangeBike = 0.1;
    const float scale = 10;
private:
    void SetupCoinTexture(float minZ, float maxZ, float minY, float maxY);
};