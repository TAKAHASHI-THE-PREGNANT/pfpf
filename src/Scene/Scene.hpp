#pragma once

namespace Scene {
    class Interface;

    template <class _Scene>
    concept Concept = requires(_Scene scene) {
      scene.update();
    };
}

class Scene::Interface {
public:
  virtual ~Interface(){};
  virtual void update() = 0;
};