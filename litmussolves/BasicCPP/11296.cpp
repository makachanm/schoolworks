#include <iostream>
using namespace std;

class Car{
protected:
    int gas;
    int speed;

public:
    Car(int g, int s) :
        gas(g), speed(s) 
    { }

    void Accel(int a) {
        if(this->gas <= 0) {
            return;
        }
        this->speed += a;
        this->gas -= a;
    }

    void Break(int b) {
        if (this->gas <= 0){
            return;
        }

        if (this->speed - b < 0) {
            this->speed = 0;
            return;
        }

        this->speed -= b;
    }

    void ShowCarState() {
        if ((this->gas) < 0) {
            cout << "(Car) gauge not enough" << endl;
            this->speed = 0;
            this->gas = 0;
            //cout << "(Car) Speed: " << this->speed << ", Gas: " << this->gas << endl;

        } else {
            cout << "(Car) Speed: " << this->speed << ", Gas: " << this->gas << endl;
        } 
    }
};

class HybridCar : public Car {
protected:
    int elec;

public:
    HybridCar(int g, int e, int s):
        Car(g, s), elec(e)
    { }

    void Accel(int a) {
        if (this->elec <= 0){
            return;
        }
        Car::Accel(a);
        this->elec -= a;
    }

    void Break(int b) {
        if (this->elec <= 0){
            return;
        }
        Car::Break(b);
    }

    void ShowCarState() {
        if (((Car::gas) < 0) && ((this->elec < 0))) {
            cout << "(HCar) gauge not enough" << endl;
            this->speed = 0;
            this->gas = 0;
            this->elec = 0;
            //cout << "(HCar) Speed: " << this->speed << ", Gas: " << this->gas << ", Elec: " << this->elec << endl;;

        } else {
            cout << "(HCar) Speed: " << this->speed << ", Gas: " << this->gas << ", Elec: " << this->elec << endl;;
        } 
    }
};

class HybridWaterCar : public HybridCar {
protected:
    int water;

public:
    HybridWaterCar(int g, int e, int w, int s):
        HybridCar(g, e, s), water(w)
    { }

    void Accel(int a) {
        if (this->water <= 0){
            return;
        }
        HybridCar::Accel(a);
        this->water -= a;
    }

    void Break(int b) {
        if (this->water <= 0){
            return;
        }
        HybridCar::Break(b);
    }

    void ShowCarState() {
        if (((Car::gas) < 0) && ((HybridCar::elec < 0)) && ((this->water) < 0)) {
            cout << "(HWCar) gauge not enough" << endl;
            this->speed = 0;
            this->gas = 0;
            this->elec = 0;
            this->water = 0;
            //cout << "(HWCar) Speed: " << this->speed << ", Gas: " << this->gas << ", Elec: " << this->elec << ", Water: " << this->water << endl;

        } else {
            cout << "(HWCar) Speed: " << this->speed << ", Gas: " << this->gas << ", Elec: " << this->elec << ", Water: " << this->water << endl;
        } 
    }
};

int main()
{
    int gas, elec, water, velocity, accel, Break;
    cin >> gas >> elec >> water >> velocity;

    HybridWaterCar hwCar(gas, elec, water, velocity); // 하이브리드 수소차에 들어있는 가솔린, 전기, 물의 양과 속도 초기화
    HybridCar hCar(gas, elec, velocity); // 하이브리드 차에 들어있는 가솔린, 전기의 양과 속도 초기화
    Car car(gas, velocity); // 일반 차에 들어있는 가솔린의 양과 속도 초기화

    hwCar.ShowCarState(); // 하이브리드 수소차를 초기화한 후 차의 상태를 출력
    hCar.ShowCarState(); // 하이브리드 차를 초기화한 후 차의 상태를 출력
    car.ShowCarState(); // 일반 차를 초기화한 후 차의 상태를 출력

    cin >> accel;

    hwCar.Accel(accel); // 하이브리드 수소차를 accel만큼 가속시킴
    hCar.Accel(accel); // 하이브리드 차를accel만큼 가속시킴
    car.Accel(accel); // 일반 차를accel만큼 가속시킴


    hwCar.ShowCarState(); // 하이브리드 수소차를 가속시킨 후 차의 상태를 출력
    hCar.ShowCarState(); // 하이브리드 차를 가속시킨 후 차의 상태를 출력
    car.ShowCarState(); // 일반 차를 가속시킨 후 차의 상태를 출력

    cin >> Break;

    hwCar.Break(Break); // 하이브리드 수소차를 break만큼 감속시킴
    hCar.Break(Break); // 하이브리드 차를break만큼 감속시킴
    car.Break(Break); // 일반 차를break만큼 감속시킴

    hwCar.ShowCarState(); // 하이브리드 수소차를 감속시킨 후 차의 상태를 출력
    hCar.ShowCarState(); // 하이브리드 차를 감속시킨 후 차의 상태를 출력
    car.ShowCarState(); // 일반 차를 감속시킨 후 차의 상태를 출력

    return 0;
}