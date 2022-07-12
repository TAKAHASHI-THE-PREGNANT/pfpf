#include "App/App.hpp"
#include "Scene/FirstScene.hpp"

sapp_desc sokol_main(int argc, char *argv[]) {
  FirstScene *firstScene = new FirstScene();
  App::loadScene(firstScene);

  return (sapp_desc){
      .init_cb = App::init,
      .frame_cb = App::update,
      .cleanup_cb = App::cleanup,
      .window_title = "window title",
      .width = 800,
      .height = 600,
      .icon.sokol_default = true,
  };
}