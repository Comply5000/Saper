#include "Saper.h"

int main()
{
    std::srand((time(NULL)));
    ::ShowWindow(GetConsoleWindow(), SW_HIDE);
    Saper saper;
    while (saper.running())
    {
        saper.update();
        saper.render();
    }

    return 0;
}