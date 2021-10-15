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
    int outsideTemp, insideTemp;
    std::string isMovementDetected, isLightOn;
    std::stringstream stream;
    std::string input;
    int state = 0;

    int lightTemp = 5000;

    for(int hour=0;hour<24;hour++)
    {
        if (hour <= 16 && hour >= 0)
            lightTemp = 5000;
        else
            lightTemp = 5000 - 2300*(hour-16) / 8;

        std::cout << "Input " << hour << ":00 environment state (temp outsie, temp inside, outside movement(yes or no), is internal light on(on or off): ";
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
        {
            if (isMovementDetected == "yes")
                state |= OUTDOOR_LIGHT;
            else if (isMovementDetected == "no")
                state &= ~OUTDOOR_LIGHT;
        }
        else
            state &= ~OUTDOOR_LIGHT;

        if (isLightOn == "on")
            state |= INDOOR_LIGHT;
        else if (isLightOn == "off")
            state &= ~INDOOR_LIGHT;

        if (insideTemp < 22)
        {
            state |= INDOOR_HEATING;
            state &= ~CONDITIONING;
        }

        if (insideTemp >= 25)
            state &= ~INDOOR_HEATING;

        if (insideTemp <25)
            state &= ~CONDITIONING;

        if (insideTemp > 30)
        {
            state &= ~INDOOR_HEATING;
            state |= CONDITIONING;
        }

        std::cout << "\nCurrent state:\n";

        if (state & MAIN_POWER)
            std::cout << "Main power switch is on\n";
        else
            std::cout << "Main power switch is off\n";

        if (state & OUTLETS)
            std::cout << "Outlets are on\n";
        else
            std::cout << "Outlets are off\n";

        if (state & INDOOR_LIGHT)
            std::cout << "Indoor light is on, light temperature is " << lightTemp << std::endl;
        else
            std::cout << "Indoor light is off\n";

        if (state & OUTDOOR_LIGHT)
            std::cout << "Outdoor light is on\n";
        else
            std::cout << "Outdoor light is off\n";

        if (state & INDOOR_HEATING)
            std::cout << "Indoor heating is on\n";
        else
            std::cout << "Indoor heating is off\n";

        if (state & WATER_HEATING)
            std::cout << "Water heating is on\n";
        else
            std::cout << "Water heating is off\n";

        if (state & CONDITIONING)
            std::cout << "Conditioner is on\n\n";
        else
            std::cout << "Conditioner is off\n\n";
    }

    return 0;
}