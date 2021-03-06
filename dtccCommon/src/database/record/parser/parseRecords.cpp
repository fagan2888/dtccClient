#include "parseRecords.hpp"

#include <boost/spirit/include/qi.hpp>

namespace dtcc
{
	namespace parser
	{
		bool parseRecords(	std::string::iterator iter					,
							std::string::iterator end					, 
							std::vector<database::tradeRecord> & recs	,
							const boost::gregorian::date & dt			)
		{
			// skip the header
			while (*iter++ != '\n');

			if (iter == end)
			{
				// the file is empty
				return true;
			}
			else
			{
				// create the grammar
				tradeRecordGrammar<std::string::iterator, ascii::blank_type> g(dt);

				return (boost::spirit::qi::phrase_parse(iter, end, g, boost::spirit::ascii::blank, recs) && iter == end);
			}
		}
	}
}