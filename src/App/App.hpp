#pragma once

#include <Color.hpp>
#include "../Scene/Scene.hpp"
#include <any>
#include <utility>

// #define __EMSCRIPTEN__ = 1 // debug

#define SOKOL_IMPL
#if defined(_WIN32)
#define SOKOL_D3D11
#elif defined(__EMSCRIPTEN__)
#define SOKOL_GLES2
#elif defined(__APPLE__)
// NOTE: on macOS, sokol.c is compiled explicitely as ObjC
#define SOKOL_METAL
#else
#define SOKOL_GLCORE33
#endif
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#ifdef __EMSCRIPTEN__
  #include "emsc.h"
#endif

class App {
private:
  static inline sg_pass_action PassAction;
  static inline Scene::Interface *Scene;
  // sapp_desc skolAppDesc;

public:
  App(){};
  ~App(){};

public:
  static inline void init() {
#ifdef __EMSCRIPTEN__
    emsc_init("#canvas", EMSC_TRY_WEBGL2);
    sg_desc &&desc = {0};
    sg_setup(desc);
#else
    auto &&desc = sg_desc{.context = sapp_sgcontext()};
    sg_setup(desc);
#endif
  }
  
public:
    static inline int width() {
      return sapp_width();
    };

public:
    static inline int height() {
      return sapp_height();
    };

public:
    void loadScene(Scene::Interface *scene) {
      // TODO: あってるかわかんないのでデバッガでアドレス確認しとく一応
      App::Scene = scene;
    }

public:
  static inline void transitionScene(Scene::Interface *scene) {
    App::Scene = scene;
  }

public:
  static inline void update() {

    // sceneクラスをupdateとdrawに分けてdrawの前に呼び出したほうがいいかも
    sg_begin_default_pass(&(App::PassAction), App::width(),
                          App::height());

    App::Scene->update();

    sg_end_pass();
    sg_commit();
  }

public:
  static void cleanup(void) { sg_shutdown(); }

public:
  sapp_desc desc() {
    return (sapp_desc) {
      .init_cb = App::init,
      .frame_cb = App::update,
      .cleanup_cb = App::cleanup,
      .window_title = "window title",
      .width = 800, .height = 600,
      .icon.sokol_default = true,
    };
  }

public:
  static inline void initBackGroundColor(const float &r, const float &g,
                                         const float &b, const float &a) {
    App::PassAction.colors[0].action = SG_ACTION_CLEAR;
    App::PassAction.colors[0].value = {r, g, b, a};
  };

public:
  static inline void backGroundColor(const float &r, const float &g,
                                     const float &b, const float &a) {
    App::PassAction.colors[0].value = {r, g, b, a};
  };

public:
  static inline thuwerato::Color backGroundColor() {
    return thuwerato::Color(App::PassAction.colors[0].value);
  };
};