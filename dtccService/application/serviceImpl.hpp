#pragma once
#ifndef SERVICE_IMPL_HPP_
#define SERVICE_IMPL_HPP_

#include <boost/thread.hpp>

#include "application/logger.hpp"
#include "application/writer.hpp"
#include "application/worker.hpp"
#include "application/service.hpp"
#include "utils/debugger.hpp"

#include "settings.hpp"

namespace dtcc
{
	class serviceImpl : public service
	{
		friend service;	
	public:
		serviceImpl(const settings &settings) : service("dtccService", true, false, false)
		{
			settings_ = settings;
		}

	protected:
		virtual void onStart(DWORD dwArgc, LPSTR * pszArgv)
		{
			run_ = true;
			LOG_INFO() << "activating service... ";
			boost::thread * thr = new boost::thread(boost::bind(&serviceImpl::startWorkers, this));
			LOG_INFO() << "activation completed";
			thr->detach();
		}
		virtual void onStop() { run_ = false; boost::this_thread::sleep(boost::posix_time::milliseconds(5000)); }
		virtual void onPause() { run_ = false; }
		virtual void onContinue() { run_ = true; }
		virtual void onShutdown() { run_ = false; }

	private:
		void startWorkers()
		{
			writeDelegate f(boost::bind(&writer::write, &w_, _1));

			workers_.resize(settings_.workers_.size());

			for (int i = 0; i < settings_.workers_.size(); i++)
			{
				std::string id = boost::lexical_cast<std::string>(i);
				workers_[i] = boost::shared_ptr<worker>(new worker(settings_.workers_[i], f, "worker " + id));
			}

			for (auto & i : workers_) i->start();
		}

		bool run_;
		settings settings_;
		std::vector<boost::shared_ptr<worker>> workers_;
		writer w_;
	};
}

#endif