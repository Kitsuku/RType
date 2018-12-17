//
// EPITECH PROJECT, 2018 
// CPP_rtype_2018
// File description:
// Transform
//

#ifndef CPP_RTYPE_2018_TRANSFORM_HPP
        #define CPP_RTYPE_2018_TRANSFORM_HPP

        #include <ostream>
        #include "Vector.hpp"

namespace Engine {
        class Transform {
        public:
                // Ctor & Dtor
                Transform();
                Transform(const Vector &pos, const Vector &rota,
                                                const Vector &scale);
                ~Transform();
                // Getter
                const Vector    &getPosition() const noexcept;
                const Vector    &getRotation() const noexcept;
                const Vector    &getScale() const noexcept;
                // Methods
                void    move(const Vector &translation) noexcept;
                void    rotate(const Vector &rotation) noexcept;
                void    place(const Vector &position) noexcept;
        private:
                Vector  _position;
                Vector  _rotation;
                Vector  _scale = Vector(1.0, 1.0);
        };
}
        // Extern operator
        std::ostream     &operator<<(std::ostream &stream,
                                const Engine::Transform &target)
                                noexcept;

#endif /* !CPP_RTYPE_2018_TRANSFORM_HPP */
