#include "thux/init.hpp"

void draw()
{
    /* animate clear colors */
    const float prevG = thux::App::BackGroundColor().g;
    const float &&g = prevG < 1.f ? prevG + 0.1f : 0.f;

    thux::App::BackGroundColor(1.0f, g, 0.0f, 1.0f);

    
    // 描画の最初に呼ばれる
    sg_begin_default_pass(&thux::App::PassAction, thux::App::Width(), thux::App::Height());

    // 描画の最後に呼ばれる
    sg_end_pass();
    sg_commit();
}

int main()
{
    thux::App::init();
    thux::App::InitBackGroundColor(1.0f, 0.0f, 0.0f, 1.0f);

    thux::App::loop(draw);
    return 0;
}
