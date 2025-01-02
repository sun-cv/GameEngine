#pragma once

#include <cmath>


class Vector2
{
    private:
    public:
        float x;
        float y;
        Vector2()                             = default;
        Vector2(float xin, float yin)         : x(xin), y(yin) {};
        Vector2& add(const Vector2& input)
        {
            x += input.x;
            y += input.y;
            return *this;
        }
        Vector2& subtract(const Vector2& input)
        {
            x-= input.x;
            y-= input.y;
            return *this;
        }
        Vector2& scale(float input)
        {
            x *= input;
            y *= input;
            return *this;
        }
        Vector2& divide(float input)
        {
            x /= input;
            y /= input;
            return *this;
        }
        bool operator ==  (const Vector2& input) const
        {
            return (x == input.x) && (y == input.y);
        }
        Vector2 operator + (const Vector2& input) const
        {
            return Vector2((x + input.x), (y + input.y));
        }
        Vector2 operator * (float input) const
        {
            return Vector2((x * input), (y * input));
        }
        Vector2 operator / (float input) const
        {
            return Vector2((x / input), (y / input));
        }
        float magnitude() const
        {
            return sqrtf((x * x) + (y * y));
        }
        float dot(const Vector2& input) const
        { 
            return (x * input.x) + (y * input.y); 
        }
        Vector2 normalize() const
        {
            float mag = magnitude();
            return Vector2((x / mag), (y / mag));
        }
        float distance(const Vector2& input) const
        {
            return sqrtf((input.x -x) * (input.x -x) + (input.y - y) * (input.y - y));
            
        }
        float angle(const Vector2& input) const 
        { 
            float mag1 = magnitude();
            float mag2 = input.magnitude();
            if (mag1 == 0.0f || mag2 == 0.0f)
            { 
                return 0.0f;
            }
            float dotProduct = dot(input);
            float magnitudes = mag1 * mag2;
            float ratio = dotProduct / magnitudes;
            if (ratio < -1.0f) ratio = -1.0f;
            if (ratio > 1.0f) ratio = 1.0f; 
            return acosf(ratio);
        }
};
