#include <memory>
#include <thuwerato/Color.hpp>

#define __EMSCRIPTEN__ = 1 // debug

#ifdef __EMSCRIPTEN__
    #define GL_GLEXT_PROTOTYPES
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #define SOKOL_IMPL
    #define SOKOL_GLES2
    #include "sokol/sokol_gfx.h"
    #include "emsc.h"
#else
    #include "sokol/sokol_gfx.h"
    #include "sokol/sokol_app.h"
    #include "sokol/sokol_glue.h"
#endif

namespace thux::App {
    sg_pass_action PassAction;

    void init();

    template <typename Func>
    void loop(Func &&func);

    int Width();
    int Height();

    void InitBackGroundColor(const float& r, const float& g, const float& b, const float& a);
    void BackGroundColor(const float& r, const float& g, const float& b, const float& a);
    thuwerato::Color BackGroundColor();

};

#ifdef __EMSCRIPTEN__
    void thux::App::init() {
        emsc_init("#canvas", EMSC_TRY_WEBGL2);

        /* setup sokol_gfx */
        sg_desc &&desc = {0};
        sg_setup(desc);
        assert(sg_isvalid());
    }

    template <typename Func>
    void thux::App::loop(Func &&func)
    {
        emscripten_set_main_loop(std::forward<Func>(func), 0, 1);
    }

    int thux::App::Width()
    {
        return emsc_width();
    };
    int thux::App::Height()
    {
        return emsc_height();
    };

#else
    void thux::App::init()
    {
        const auto &&desc = sg_desc{.context = sapp_sgcontext()};
        sg_setup(desc);
    }

    //TODO: ネイティブでもコンパイルできるようにする
    template <typename Func>
    void thux::App::loop(Func &&func)
    {
        // emscripten_set_main_loop(std::forward<Func>(func), 0, 1);
    }

    int thux::App::Width()
    {
        return sapp_width();
    };

    int thux::App::Height()
    {
        return sapp_height();
    };
#endif

    void thux::App::InitBackGroundColor(const float& r, const float& g, const float& b, const float& a)
    {
        thux::App::PassAction.colors[0].action = SG_ACTION_CLEAR;
        thux::App::PassAction.colors[0].value = {r, g, b, a};
    };

    void thux::App::BackGroundColor(const float& r, const float& g, const float& b, const float& a)
    {
        thux::App::PassAction.colors[0].value = {r, g, b, a};
    };

    thuwerato::Color thux::App::BackGroundColor()
    {
        return thuwerato::Color(thux::App::PassAction.colors[0].value);
    };