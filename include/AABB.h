#ifndef AABB_H
#define AABB_H

#include <Shape.h>
#include "MathUtils.h"

class AABB : public Shape
{
    public:
        AABB(Vector2f, int, int);

        void set_width(int);
        void set_height(int);

        int  get_width();
        int  get_height();

    protected:
        int width;
        int height;
};

#endif // AABB_H
