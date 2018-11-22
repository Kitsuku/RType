//
// EPITECH PROJECT, 2018 
// CPP_rtype_2018
// File description:
// Transform
//

#ifndef CPP_RTYPE_2018_TRANSFORM_HPP
        #define CPP_RTYPE_2018_TRANSFORM_HPP

        #include "Vector.hpp"

namespace Engine {
        class Transform {
        public:
                // Ctor & Dtor
                Transform();
                Transform(const Vector &pos, const Vector &rota,
                                                const Vector &scale);
                ~Transform();
                // Operator
                // Setter
                // Getter
                const Vector    &getPosition() const noexcept;
                const Vector    &getRotation() const noexcept;
                const Vector    &getScale() const noexcept;
                // Methods
                void    move(const Vector &translation) noexcept;
                void    rotate(const Vector &rotation) noexcept;
        private:
                Vector  _position;
                Vector  _rotation;
                Vector  _scale;
        };
}

#endif /* !CPP_RTYPE_2018_TRANSFORM_HPP */
