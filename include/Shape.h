#ifndef SHAPE_H
#define SHAPE_H
#include "MathUtils.h"

class Shape
{
    public:
        Shape(Vector2f);
        Vector2f get_position();
        void     set_position(Vector2f);
        virtual ~Shape() = default;

    protected:
        Vector2f position;
};

#endif // SHAPE_H
