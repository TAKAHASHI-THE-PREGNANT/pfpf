#pragma once

#include "../App/App.hpp"
#include "Scene.hpp"

class FirstScene : public Scene::Interface {
public:
  FirstScene() { App::initBackGroundColor(1.0f, 0.0f, 0.0f, 1.0f); };

  ~FirstScene(){

  };

  void update() {
    /* animate clear colors */
    const float prevG = App::backGroundColor()[1];
    const float &&g = prevG < 1.f ? prevG + 0.1f : 0.f;

    App::backGroundColor(1.0f, g, 0.0f, 1.0f);

    }
};