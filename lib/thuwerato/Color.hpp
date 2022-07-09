#include <array>

namespace thuwerato {
    template <class _ColorType>
    concept ColorConcept = requires(_ColorType color)
    {
        color.r;
        color.g;
        color.b;
        color.a;
    };

    class Color;
}

// TODO: 違う色空間などの変換などしたい RGB->HSV->YIQ
class thuwerato::Color
{  
public:
    union {
        std::array<float, 4> value;
        struct {float r, g, b, a;};
    };

    Color(const float& r, const float& g, const float& b, const float& a) : r(r), g(g), b(b), a(a) {}
    Color(const std::array<float, 4>& rgba) : value(rgba) {}

    Color(const float& r, const float& g, const float& b) : r(r), g(g), b(b)
    {
        this->a = 1.0f;
    }

    template <thuwerato::ColorConcept _Color>
    Color(_Color&& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

    template <thuwerato::ColorConcept _Color>
    Color(const _Color&& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

    ~Color() {

    }

    float operator[](const int index){
        return this->value[index];
    }
};