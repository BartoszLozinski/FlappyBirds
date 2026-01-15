#include "Gameplay/Gameplay.hpp"
#include "UI/UI.hpp"

int main(int argc, char* argv[])
{
    UI ui(argc, argv);
    ui.showMainWindow();
    ui.RunExec();
    //Gameplay{}.Run();

    return 0;
};
