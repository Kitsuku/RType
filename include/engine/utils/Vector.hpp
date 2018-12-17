//
// EPITECH PROJECT, 2018
// rtype
// File description:
// vector
//

#ifndef VECTOR_HPP_
        #define VECTOR_HPP_

        #include <ostream>
        #include <fstream>

namespace Engine {
        class Vector {
        public:
                // Ctor & Dtor
                Vector(std::ifstream &stream);
                Vector(float x = 0.0, float y = 0.0);
                ~Vector();
                // Operator
                const Vector    &operator+=(const Vector &other) noexcept;
                const Vector    &operator=(const Vector &other) noexcept;
                bool            operator==(const Vector &other)
                                                        const noexcept;
                bool            operator!=(const Vector &other)
                                                        const noexcept;
                // Setter
                void    setX(float x) noexcept;
                void    setY(float y) noexcept;
                void    setNull() noexcept;
                // Getter
                bool    isNull() const noexcept;
                float   getX() const noexcept;
                float   getY() const noexcept;
                // Method
                void    serialize(std::ostream &stream) const noexcept;
        private:
                float   _x;
                float   _y;
        };
}

        // Extern operator
        std::ostream      &operator<<(std::ostream &stream,
                                const Engine::Vector &target)
                                noexcept;

#endif /* !VECTOR_HPP_ */
