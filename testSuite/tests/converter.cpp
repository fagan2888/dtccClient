#ifndef DTCC_TEST_COMPRESSION_CPP_
#define DTCC_TEST_COMPRESSION_CPP_

#include "converter.hpp"
#include "utils/converter.hpp"

namespace testSuite
{
	void converter::charToInt()
	{
		BOOST_TEST_MESSAGE("Testing conversion from char to int...");

		int32_t val = 2147381647;

		dtcc::util::converter<int32_t, char[4]> forward;
		forward.t1_ = val;

		dtcc::util::converter<char[4], int32_t> backward;
		memcpy(backward.t1_, forward.t2_, sizeof(forward.t2_));

		int32_t res = backward.t2_;

		if (val != res)
		{
			BOOST_ERROR("\n" <<
				" Failed!" <<
				" Expected result: " << val << "\n"
				" Obtained: " << res);
		}
	}

	void converter::stringToDoubleThousandSeparator()
	{
		std::string input = "1,234,567.89";

		std::istringstream buffer(input);
		buffer.imbue(std::locale(""));

		double res;
		buffer >> res;

		double val = 1234567.89;

		if (std::abs(res - val) > 0.001)
		{
			BOOST_ERROR("\n" <<
				" Failed!" <<
				" Expected result: " << val << "\n"
				" Obtained: " << res);
		}
	}

	boost::unit_test_framework::test_suite * converter::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("compression Tests");
		suite->add(BOOST_TEST_CASE(&converter::charToInt));
		suite->add(BOOST_TEST_CASE(&converter::stringToDoubleThousandSeparator));
		return suite;
	}
}
#endif
