#include <iostream>
#include <sstream>

enum states
{
    MAIN_POWER=1,
    OUTLETS=2,
    INDOOR_LIGHT=4,
    OUTDOOR_LIGHT=8,
    HEATING=16,
    CONDITIONING=32
};

int main()
{
    int outsideTemp, insideTemp, isMovementDetected, isLightOn;
    std::stringstream stream;
    std::string input;

    for(int hour=0;hour<24;hour++)
    {

        std::cout << "Input " << hour << ":00 environment state: ";
        std::getline(std::cin, input);
        stream << input;
        stream >> outsideTemp >> insideTemp >> isMovementDetected >> isLightOn;
        continue;
    }
    return 0;
}
