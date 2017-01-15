#ifndef COMPRESSION_UNZIP_HPP_
#define COMPRESSION_UNZIP_HPP_

#include <ioapi.h>
#include <unzip.h>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>

# include "application/compression.hpp"

namespace dtcc
{
	class unzip
	{
	public:
		unzip();
		~unzip(void);

		bool open(const char* filename);
		void close();
		bool isOpen();

		bool openEntry(const char* filename);
		void closeEntry();
		bool isOpenEntry();
		unsigned int getEntrySize();

		const std::vector<std::string>& getFilenames();
		const std::vector<std::string>& getFolders();

		unzip& operator >> (std::ostream& os);

	private:
		void readEntries();

	private:
		unzFile			zipFile_;
		bool			entryOpen_;

		std::vector<std::string> files_;
		std::vector<std::string> folders_;
	};
}

#endif