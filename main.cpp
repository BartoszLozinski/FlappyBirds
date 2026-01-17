#include "UI/UI.hpp"

int main(int argc, char* argv[])
{
    UI ui(argc, argv);
    ui.showMainWindow();
    ui.RunExec();

    return 0;
};
