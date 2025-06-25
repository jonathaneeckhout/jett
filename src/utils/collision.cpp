#include "jett/utils/collision.hpp"

bool pointCollidesWithRect(Vector point_position, Vector rect_position, Vector rect_size)
{
    return point_position.x >= rect_position.x &&
           point_position.x <= rect_position.x + rect_size.x &&
           point_position.y >= rect_position.y &&
           point_position.y <= rect_position.y + rect_size.y;
}