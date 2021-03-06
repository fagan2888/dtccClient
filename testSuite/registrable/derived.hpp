#ifndef REGISTRABLE_DERIVED_HPP_
#define REGISTRABLE_DERIVED_HPP_

#include <iostream>

#include "registrable/base.hpp"

namespace testSuite
{
	class derived : public base
	{
	public:
		derived(char c) : base() {}
		virtual std::string foo() { return "hello world!"; }
	private:
		static dtcc::registerType < base, std::string, derived, char> register_;
	};
}

#endif
