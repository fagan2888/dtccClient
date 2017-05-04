#pragma once
#ifndef WEB_WORKER_HPP_
#define WEB_WORKER_HPP_

#include <sstream>
#include <boost/asio.hpp>

#include "application/workerBase.hpp"
#include "application/connections/https.hpp"
#include "application/connections/http.hpp"
#include "application/readers/reader.hpp"
#include "application/writer.hpp"
#include "utils/debugger.hpp"
#include "settings.hpp"

namespace dtcc
{
	class worker : public workerBase<worker>
	{
	public:
		worker(settings::worker & settings, writeDelegate write, const std::string name = "worker");
		~worker();

		void work();

	private:
		void connect_callback(bool result);
		void reader_callback(const std::string & msg, bool result);
		std::string filename();

		// void error_callback() // TODO
		settings::worker & settings_;

		std::unique_ptr<boost::thread> t_;
		boost::condition_variable cv_;
		bool terminate_;
		boost::mutex m_;

		boost::shared_ptr<boost::asio::io_service::work> ioTask_;
		boost::shared_ptr<boost::asio::io_service> io_;

		boost::shared_ptr<connection> cnx_;
		boost::shared_ptr<reader> reader_;
		writeDelegate write_;

		std::string filename_;
		int counter_;
		int nFailure_;
	};
}

#endif