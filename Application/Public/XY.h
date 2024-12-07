#pragma once

#include <cstdint>

namespace ApplicationLayer
{

class XY
{
public:
    XY() = default;
    XY(int8_t x, int8_t y) : _x(x), _y(y) {}

    void modify(int8_t xDelta, int8_t yDelta)
    {
        _x += xDelta;
        _y += yDelta;
    }

    int getX() const {return _x;}
    int getY() const {return _y;}

    bool operator==(const XY& other) const
    {
        return _x == other._x && _y == other._y;
    }

private:
    int8_t _x{0};
    int8_t _y{0};
};

} // namespace ApplicationLayer