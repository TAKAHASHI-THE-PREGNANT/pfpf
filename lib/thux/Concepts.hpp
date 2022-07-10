#pragma once

namespace thux::Concepts {
    template <class _Scene>
    concept Scene = requires(_Scene scene)
    {
        scene.setup();
        scene.update();
    };
};