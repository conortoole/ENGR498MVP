#include <Arduino\SerialClass.h>
#include "Send.h"
#include "led.h"


class LED{
    private:
        int port = 0;
        emum colors
        {
            red = "255,0,0"
            green = "0,255,0"
            blue = "0,0,255"
        }
        
    public:
        LED(int port){
            this.port = port;
            pinMode(this.port, OUTPUT);
        }

        bool turnOn() {
            digitalWrite(port, HIGH);
            return true;
        }

        bool turnOff() {
            digitalWrite(port, LOW);
            return true;
        }

        bool changeColor(){
            ////insert code here
            return true
        }


};