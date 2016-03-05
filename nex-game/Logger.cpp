#include "stdafx.h"
#include <string>
#include <cstdarg>
#include <ostream>

#include "Logger.h"
#include "ArgParse.h"

using std::string;


/*
	These are constructed upon init_()
*/
Logger::Level DEBUG_NONE;
Logger::Level DEBUG_CALLBACKS;
Logger::Level DEBUG_CALLBACKS_DEEP;
Logger::Level DEBUG_CORE;
Logger::Level DEBUG_CORE_DEEP;
Logger::Level DEBUG_INTERNAL;
Logger::Level DEBUG_INTERNAL_DEEP;
Logger::Level DEBUG_INTERFACE;
Logger::Level DEBUG_INTERFACE_DEEP;
Logger::Level DEBUG_LOOPS;


void Logger::init()
{
	init_();

	output_ = console;
}

void Logger::init(Level l)
{
	init_();

	level_ = l;
	output_ = console;
}

void Logger::init(string filename)
{
	init_();
	initfile_(filename);
}

void Logger::init(Level l, string filename)
{
	init_();
	initfile_(filename);

	level_ = l;
}

void Logger::init(string filename, int argc, char* argv[])
{
	init_();
	initargs_(argc, argv);
	initfile_(filename);
}

void Logger::init(int argc, char* argv[])
{
	init_();
	initargs_(argc, argv);

	output_ = console;
}

void Logger::init_()
{
	DEBUG_NONE				= add_level(0, "NONE");
	DEBUG_CALLBACKS			= add_level(1, "CALLBACKS");
	DEBUG_CALLBACKS_DEEP	= add_level(2, "CALLBACKS_DEEP");
	DEBUG_CORE				= add_level(3, "CORE");
	DEBUG_CORE_DEEP			= add_level(4, "CORE_DEEP");
	DEBUG_INTERNAL			= add_level(5, "INTERNAL");
	DEBUG_INTERNAL_DEEP		= add_level(6, "INTERNAL_DEEP");
	DEBUG_INTERFACE			= add_level(7, "INTERFACE");
	DEBUG_INTERFACE_DEEP	= add_level(8, "INTERFACE_DEEP");
	DEBUG_LOOPS				= add_level(9, "LOOPS");
}

void Logger::initargs_(int argc, char* argv[])
{
	map<char, string> args = SDI::parseArgsValues(argc, argv);
	Level l;

	if(args.find('d') != args.end())
	{
		for (int i = 0, j = levels_.size(); i < j; ++i)
		{
			l = levels_.at(i);
			if (args['d'].compare(l.name) == 0)
			{
				level_ = l;
			}
		}
	}

	if (args.find('f') != args.end())
	{
		initfile_(args['f']);
	}
}

void Logger::initfile_(string filename)
{
	std::stringstream ss;
	std::time_t t = std::time(NULL);
	char formatted[128];

	strftime(formatted, 128, filename.c_str(), std::localtime(&t));

	output_ = file;
	outputFileName_ = formatted;
	outputFile_.open(string(formatted), std::fstream::out | std::fstream::app);
}

Logger::Level Logger::add_level(int idx, string name)
{
	Level l;
	l.idx = idx;
	l.name = name;
	levels_.push_back(l);
	return l;
}

void Logger::level(Level l)
{
	level_ = l;
}

void Logger::out(Level l, string file, int line, string msg)
{
	if(l.idx < level_.idx)
		return;

	send(l, msg, file, line);
}

void Logger::outf(Level l, string file, int line, string msg, ...)
{
	if(l.idx < level_.idx)
		return;

	size_t len = msg.length() + 1;
	char* buffer = new char[len];

	va_list va;
	va_start(va, msg);

	vsprintf_s(buffer, len, msg.c_str(), va);
	send(l, buffer, file, line);

	va_end(va);
	delete buffer;
}

void Logger::send(Level l, string msg, string file, int line)
{
	std::stringstream ss;
	std::time_t t = std::time(NULL);
	char datetime[20];

	strftime(datetime, 20, "%Y/%m/%d %H:%M:%S", std::localtime(&t));

	if(line > -1)
		ss << datetime << "[" << file << ":" << line << " @ " << l.name << "] " << msg;

	else
		ss << datetime << "[" << file << " @ " << l.name << "] " << msg;

	std::cout << ss.str() << std::endl;

	if(output_ != console)
	{
		outputFile_ << ss.str() << std::endl;
	}
}
