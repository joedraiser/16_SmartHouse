#include <iostream>
#include <sstream>

enum states
{
    MAIN_POWER=1,
    OUTLETS=2,
    INDOOR_LIGHT=4,
    OUTDOOR_LIGHT=8,
    INDOOR_HEATING=16,
    WATER_HEATING=32,
    CONDITIONING=64
};

int main()
{
    int outsideTemp, insideTemp, isMovementDetected, isLightOn;
    std::stringstream stream;
    std::string input;
    int state = 0;

    for(int hour=0;hour<24;hour++)
    {

        std::cout << "Input " << hour << ":00 environment state (temp outsie, temp inside, outside movement(1 or 0), is internal light ojn(1 or 0): ";
        std::getline(std::cin, input);
        stream.clear();
        stream.str(input);
        stream.seekg(0);

        stream >> outsideTemp >> insideTemp >> isMovementDetected >> isLightOn;
        
        if (outsideTemp < 0)
            state |= WATER_HEATING;
        if (outsideTemp > 5)
            state &= ~WATER_HEATING;

        if (hour > 16 && hour < 5)
            if (isMovementDetected)
                state |= OUTDOOR_LIGHT;
            else
                state &= ~OUTDOOR_LIGHT;
        else
            state &= ~OUTDOOR_LIGHT;

        if (insideTemp < 22)
        {
            state |= INDOOR_HEATING;
            state &= ~CONDITIONING;
        }
        if (insideTemp >= 25)
        {
            state &= ~INDOOR_HEATING;
        }
        if (insideTemp <25)
            state &= ~CONDITIONING;
        if (insideTemp > 30)
        {
            state &= ~INDOOR_HEATING;
            state |= CONDITIONING;
        }

        continue;
    }
    return 0;
}