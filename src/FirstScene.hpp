#pragma once

#include "thux/App.hpp"

class FirstScene {
public:
    FirstScene()
    {

    };

    ~FirstScene()
    {

    };

    void setup()
    {
        thux::App::InitBackGroundColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    void update() const
    {
        /* animate clear colors */
        const float prevG = thux::App::BackGroundColor()[1];
        const float &&g = prevG < 1.f ? prevG + 0.1f : 0.f;

        thux::App::BackGroundColor(1.0f, g, 0.0f, 1.0f);

    }
};