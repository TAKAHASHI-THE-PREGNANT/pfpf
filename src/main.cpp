#include "App/App.hpp"
#include "Scene/FirstScene.hpp"

sapp_desc sokol_main(int argc, char *argv[]) {
    auto app = App();
  
  FirstScene *firstScene = new FirstScene();
  app.loadScene(firstScene);

  return app.desc();
}