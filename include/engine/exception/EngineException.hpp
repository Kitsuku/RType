//
// EPITECH PROJECT, 2018
// rtype
// File description:
// engine exception
//

#ifndef ENGINEEXCEPTION_HPP_
	#define ENGINEEXCEPTION_HPP_

	#include <string>
	#include <exception>

namespace Engine {
	class EngineException : public std::exception {
	public:
		// Ctor & Dtor
		EngineException(const std::string &msg);
		virtual ~EngineException() override = default;
		// Method
		const char	*what() const noexcept override;
	private:
		const std::string	_msg;
	};
}

#endif /* !ENGINEEXCEPTION_HPP_ */
