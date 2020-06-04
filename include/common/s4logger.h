#pragma once

#if defined _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4566 )
#endif

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#if defined _MSC_VER
#pragma warning( pop )
#endif


#include "common/s4thread.h"

#include <iostream>
#include <filesystem>

#include <string>
#include <map>

namespace S4{
#define LOG_SIZE_MB (1024 * 1024)
class logger : std::enable_shared_from_this<logger>
{
public:
    typedef std::shared_ptr<logger> Ptr;
	struct param_t
	{
		bool enable_console = true;
		bool enable_file_all = false;
		bool enable_file_all_pure = false;
		bool enable_file_err = false;
		bool enable_file_err_pure = false;
		spdlog::level::level_enum level = spdlog::level::info;
		std::string save_path = ".";
		std::string file_preamble = "S4";
		size_t max_file_size_MB = (size_t)-1;
		size_t max_files = 10;
	};

	static Ptr pInstance() {
		static Ptr _g_pLogger;
		if (!_g_pLogger) {
			init_time_base();

			_g_pLogger = std::make_shared<logger>();
			_g_pLogger->init();
		}

		return _g_pLogger;
	}

	void init(param_t* p = nullptr) noexcept {
		if (p) {
			_param = *p;
		}
		init_console();
		
		init_file_folder();
		init_files_all();
		init_files_err();
	}

	template<typename... Args>
	void err(const std::string& preamble, const char *fmt, const Args &... args)
	{
		std::string s = preamble + fmt;
		if (_file_all) {
			_file_all->error(s.c_str(), args...);
		}
		if (_file_all_pure) {
			_file_all_pure->error(s.c_str(), args...);
		}
		if (_file_err) {
			_file_err->error(s.c_str(), args...);
		}
		if (_file_err_pure	) {
			_file_err_pure->error(s.c_str(), args...);
		}
		if (_console) {
			_console->error(s.c_str(), args...);
		}
	}

	template<typename... Args>
	void info(const std::string& preamble, const char *fmt, const Args &... args)
	{
		std::string s = preamble + fmt;
		if (_file_all) {
			_file_all->info(s.c_str(), args...);
		}
		if (_file_all_pure) {
			_file_all_pure->info(s.c_str(), args...);
		}
		if (_console) {
			_console->info(s.c_str(), args...);
		}
	}

	template<typename... Args>
	void warn(const std::string& preamble, const char *fmt, const Args &... args)
	{
		std::string s = preamble + fmt;
		if (_file_all) {
			_file_all->warn(s.c_str(), args...);
		}
		if (_file_all_pure) {
			_file_all_pure->warn(s.c_str(), args...);
		}
		if (_console) {
			_console->warn(s.c_str(), args...);
		}
	}

	template<typename... Args>
	void trace(const std::string& preamble, const char *fmt, const Args &... args)
	{
		std::string s = preamble + fmt;
		if (_file_all) {
			_file_all->trace(s.c_str(), args...);
		}
		if (_file_all_pure) {
			_file_all_pure->trace(s.c_str(), args...);
		}
		if (_console) {
			_console->trace(s.c_str(), args...);
		}
	}

	template<typename... Args>
	void fatal(const std::string& preamble, const char *fmt, const Args &... args)
	{
		std::string s = preamble + fmt;
		if (_file_all) {
			_file_all->critical(s.c_str(), args...);
		}
		if (_file_all_pure) {
			_file_all_pure->critical(s.c_str(), args...);
		}
		if (_file_err) {
			_file_err->critical(s.c_str(), args...);
		}
		if (_file_err_pure) {
			_file_err_pure->critical(s.c_str(), args...);
		}
		if (_console) {
			_console->critical(s.c_str(), args...);
		}
		flush();
		process_sleep(0.1);
		exit(-1);
	}

	void flush() noexcept{
		if (_file_all) {
			_file_all->flush();
		}
		if (_file_err) {
			_file_err->flush();
		}
		if (_file_all_pure) {
			_file_all_pure->flush();
		}
		if (_file_err_pure) {
			_file_err_pure->flush();
		}
	}

private:
	param_t _param;
	std::shared_ptr<spdlog::logger> _file_all;
	std::shared_ptr<spdlog::logger> _file_all_pure;
	std::shared_ptr<spdlog::logger> _file_err;
	std::shared_ptr<spdlog::logger> _file_err_pure;

	std::map<std::string, std::shared_ptr<spdlog::logger>> _file_loggers;

	std::shared_ptr<spdlog::logger> _console;

	static std::string _time_base;
	static std::filesystem::path _file_folder;

	Mutex _mux;
private:
	static void init_time_base() {
		char upTime[64];
		time_t utc;
		time(&utc);
		utc += 3600 * 8;
		struct tm ltm = *gmtime(&utc);
		strftime(upTime, 64, "%Y_%m_%d__%H_%M_%S", &ltm);
		_time_base = std::string(upTime);
	}

	void init_file_folder(void) {
		_file_folder = _param.save_path;
		if (std::filesystem::exists(_file_folder)) {
			if (!std::filesystem::is_directory(_file_folder)) {
				if (!std::filesystem::create_directory(_file_folder)) {
					std::cerr << "create_directory(" << _file_folder << ") fail!" << std::endl;
					throw std::exception("logger init fail!");
				}
			}
		}
		else
		{
			if (!std::filesystem::create_directories(_file_folder)) {
				std::cerr << "create_directory(" << _file_folder << ") fail!" << std::endl;
				throw std::exception("logger init fail!");
			}
		}
	}
	void init_console() {
		if (_param.enable_console) {
			if (!_console) {
				_console = spdlog::create<spdlog::sinks::stdout_color_sink_mt>("console");
				_console->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %^%v%$");
			}
			_console->set_level(_param.level);
		}
		else if(_console){
			spdlog::drop("console");
			_console = nullptr;
		}
	}

	void init_file(const std::string& name_preamble, bool enable, bool pure, bool error) {
		std::shared_ptr<spdlog::logger> pLogger;
		std::string name = name_preamble + _time_base;
		if (error) {
			name += "_err";
		}
		if (pure) {
			name += "_pure";
		}
		
		std::filesystem::path file_path = _file_folder / (name + ".log");

		if (!enable) {
			if (_file_loggers.count(name) != 0) {
				spdlog::drop(name);
				_file_loggers.erase(name);
			}
			return;
		}

		//enable
		if (_file_loggers.count(name) != 0) {
			pLogger = _file_loggers.at(name);
			if (((spdlog::sinks::rotating_file_sink_mt*)spdlog::get(name)->sinks()[0].get())->filename() != file_path.string()) {	//redirect file path
				_file_loggers.erase(name);
				pLogger = nullptr;
			}
		}

		if (!pLogger) {
			pLogger = spdlog::create<spdlog::sinks::rotating_file_sink_mt>(name, file_path.string(), _param.max_file_size_MB * LOG_SIZE_MB, _param.max_files);
			_file_loggers[name] = pLogger;
			//spdlog::sinks::rotating_file_sink_mt* raw = (spdlog::sinks::rotating_file_sink_mt*)pLogger->sinks()[0].get();
			//std::cout << raw->filename() << std::endl;
		}
		if (pure) {
			pLogger->set_pattern("[%l] %^%v%$");
		}
		else {
			pLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %^%v%$");
		}

		if (error) {
			pLogger->set_level(spdlog::level::err);
		}
		else {
			pLogger->set_level(_param.level);
		}
	}

	void init_files_all() {
		init_file(_param.file_preamble, _param.enable_file_all, false, false);
		init_file(_param.file_preamble, _param.enable_file_all_pure, true, false);

		if (_file_loggers.count(_param.file_preamble + _time_base)) {
			_file_all = _file_loggers.at(_param.file_preamble + _time_base);
		}
		else {
			_file_all = nullptr;
		}
		if (_file_loggers.count(_param.file_preamble + _time_base + "_pure")) {
			_file_all_pure = _file_loggers.at(_param.file_preamble + _time_base + "_pure");
		}
		else {
			_file_all_pure = nullptr;
		}
	}
	void init_files_err() {
		init_file(_param.file_preamble, _param.enable_file_err, false, true);
		init_file(_param.file_preamble, _param.enable_file_err_pure, true, true);
		if (_file_loggers.count(_param.file_preamble + _time_base + "_err")) {
			_file_err = _file_loggers.at(_param.file_preamble + _time_base + "_err");
		}
		else {
			_file_err = nullptr;
		}
		if (_file_loggers.count(_param.file_preamble + _time_base + "_err_pure")) {
			_file_err_pure = _file_loggers.at(_param.file_preamble + _time_base + "_err_pure");
		}
		else {
			_file_err_pure = nullptr;
		}
	}

	//void init_file_all() {
	//	if (_param.enable_file_all) {
	//		std::string file_name = _param.file_preamble + _time_base + ".log";
	//		std::string file_name_pure = _param.file_preamble + _time_base + "_pure.log";
	//		std::filesystem::path file_path = _file_folder / file_name;
	//		std::filesystem::path file_path_pure = _file_folder / file_name_pure;
	//		if (_file_all && spdlog::get("file_all")->name() != file_path.string()) {	//need new file_all log
	//			spdlog::drop("file_all");
	//			spdlog::drop("file_all_pure");
	//			_file_all = nullptr;
	//			_file_all_pure = nullptr;
	//		}
	//		if (!_file_all) {
	//			_file_all = spdlog::create<spdlog::sinks::rotating_file_sink_mt>("file_all", file_path.string(), _param.max_file_size_MB * LOG_SIZE_MB, _param.max_files);
	//			_file_all_pure = spdlog::create<spdlog::sinks::rotating_file_sink_mt>("file_all_pure", file_path_pure.string(), _param.max_file_size_MB * LOG_SIZE_MB, _param.max_files);

	//			_file_all->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %^%v%$");
	//			_file_all_pure->set_pattern("[%l] %^%v%$");
	//		}
	//		_file_all->set_level(_param.level);
	//		_file_all_pure->set_level(_param.level);
	//	}
	//	else if (_file_all) {
	//		spdlog::drop("file_all");
	//		spdlog::drop("file_all_pure");
	//		_file_all = nullptr;
	//		_file_all_pure = nullptr;
	//	}
	//}

	//void init_file_err() {
	//	if (_param.enable_file_err) {
	//		std::string file_name = _param.file_preamble + _time_base + "_err.log";
	//		std::string file_name_pure = _param.file_preamble + _time_base + "_err_pure.log";
	//		std::filesystem::path file_path = _file_folder / file_name;
	//		std::filesystem::path file_path_pure = _file_folder / file_name_pure;
	//		if (_file_err && spdlog::get("file_err")->name() != file_path.string()) {	//need new file_err log
	//			spdlog::drop("file_err");
	//			spdlog::drop("file_err_pure");
	//			_file_err = nullptr;
	//			_file_err_pure = nullptr;
	//		}
	//		if (!_file_err) {
	//			_file_err = spdlog::create<spdlog::sinks::rotating_file_sink_mt>("file_err", file_path.string(), _param.max_file_size_MB * LOG_SIZE_MB, _param.max_files);
	//			_file_err_pure = spdlog::create<spdlog::sinks::rotating_file_sink_mt>("file_err_pure", file_path_pure.string(), _param.max_file_size_MB * LOG_SIZE_MB, _param.max_files);

	//			_file_err->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %^%v%$");
	//			_file_err_pure->set_pattern("[%l] %^%v%$");
	//		}
	//		_file_err->set_level(spdlog::level::err);
	//		_file_err_pure->set_level(spdlog::level::err);
	//	}
	//	else if (_file_err) {
	//		spdlog::drop("file_err");
	//		spdlog::drop("file_err_pure");
	//		_file_err = nullptr;
	//		_file_err_pure = nullptr;
	//	}
	//}

};

#define	TRACE(...) {S4::logger::pInstance()->trace("[global]", __VA_ARGS__);}
#define	INFO(...) {S4::logger::pInstance()->info("[global]", __VA_ARGS__);}
#define	WARN(...) {S4::logger::pInstance()->warn("[global]", __VA_ARGS__);S4::logger::pInstance()->flush();}
#define	ERR(...) {S4::logger::pInstance()->err("[global]", __VA_ARGS__);S4::logger::pInstance()->flush();}
#define	FATAL(...) {S4::logger::pInstance()->fatal("[global]", __VA_ARGS__);}

#define CREATE_LOCAL_LOGGER(NAME) static const char * __LCL_NAME__ = "["#NAME"] ";

#define LCL_TRAC(...) {S4::logger::pInstance()->trace(__LCL_NAME__, __VA_ARGS__);}
#define	LCL_INFO(...) {S4::logger::pInstance()->info(__LCL_NAME__, __VA_ARGS__);}
#define	LCL_WARN(...) {S4::logger::pInstance()->warn(__LCL_NAME__, __VA_ARGS__);S4::logger::pInstance()->flush();}
#define	LCL_ERR(...) {S4::logger::pInstance()->err(__LCL_NAME__, __VA_ARGS__);S4::logger::pInstance()->flush();}
#define	LCL_FATAL(...) {S4::logger::pInstance()->fatal(__LCL_NAME__, __VA_ARGS__);}

}//namespace S4