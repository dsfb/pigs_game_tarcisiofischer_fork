#ifndef __COLLISION_ENUMS_HPP
#define __COLLISION_ENUMS_HPP

enum class CollisionType {
    NO_COLLISION = 0,
    TILEMAP_COLLISION = 1,
    BOTTOM_ONLY_COLLISION = 3,
    DANGEROUS_COLLISION = 4
};

enum class CollisionSide {
    LEFT_COLLISION = 0,
    RIGHT_COLLISION = 1,
    TOP_COLLISION = 2,
    BOTTOM_COLLISION = 3
};

#endif
