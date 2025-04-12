#include "Rect.h"

glm::vec2 Crayon::Rect::getTopLeftRaw() const
{
    return origin;
}

glm::vec2 Crayon::Rect::getTopRightRaw() const
{
    return origin + glm::vec2( extent.x, 0.f );
}

glm::vec2 Crayon::Rect::getBottomRightRaw() const
{
    return origin + glm::vec2( extent.x, extent.y );
}

glm::vec2 Crayon::Rect::getBottomLeftRaw() const
{
    return origin + glm::vec2( 0.f, extent.y );
}

float Crayon::Rect::getMinXRaw() const
{
    return origin.x;
}

float Crayon::Rect::getMaxXRaw() const
{
    return origin.x+extent.x;
}

float Crayon::Rect::getMinYRaw() const
{
    return origin.y;
}

float Crayon::Rect::getMaxYRaw() const
{
    return origin.y + extent.y;
}




