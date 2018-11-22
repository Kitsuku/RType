//
// EPITECH PROJECT, 2018
// rtype
// File description:
// vector
//

#ifndef VECTOR_HPP_
        #define VECTOR_HPP_

namespace Engine {
        class Vector {
        public:
                // Ctor & Dtor
                Vector(float x = 0.0, float y = 0.0);
                ~Vector();
                // Operator
                const Vector &operator+=(const Vector &other) noexcept;
                const Vector &operator=(const Vector &other) noexcept;
                // Setter
                void setX(float x) noexcept;
                void setY(float y) noexcept;
                // Getter
                float getX() const noexcept;
                float getY() const noexcept;
        private:
                float   _x;
                float   _y;
        };
}

#endif /* !VECTOR_HPP_ */
