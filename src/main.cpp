#include "thux/App.hpp"
#include "FirstScene.hpp"

int main()
{
    thux::App::init();

    thux::App::loadScene(FirstScene());
    return 0;
}
