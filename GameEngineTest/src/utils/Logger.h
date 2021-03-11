#pragma once
#include "spdlog/logger.h" //you can write your own wrapper for this library in the future.
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define INFO(...) GameEngineTest::Logger::getConsole()->info(__VA_ARGS__)
#define WARN(...) GameEngineTest::Logger::getConsole()->warn(__VA_ARGS__)
#define CRITICAL(...) GameEngineTest::Logger::getConsole()->critical(__VA_ARGS__)

namespace GameEngineTest {
	
	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> console;
	public:
		static void init();
	public:
		static std::shared_ptr<spdlog::logger>& getConsole() { return console; }
	};

}

