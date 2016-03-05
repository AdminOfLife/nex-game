/*
	Logger

	Barnaby Keene 2015
*/

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>

using std::string;


#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#define log_init		Logger::inst()->Logger::init
#define log_lvl			Logger::inst()->level

#ifdef _DEBUG
#define logs(l)			Logger::scoped_logger(l, __FILE__, __LINE__).stream()
#define logc(l, m)		Logger::inst()->out(l, __FILE__, __LINE__, m);
#define logf(l, m, ...)	Logger::inst()->outf(l, __FILE__, __LINE__, m, __VA_ARGS__);

#else // ifdef _DEBUG

// To remove unnecessary code when in release mode
#define logs(l)			std::cerr
#define logc(l, m)
#define logf(l, m, ...)

#endif // #ifdef _DEBUG


enum Output
{
	file,
	console
};

class Logger
{

public:
	static Logger* inst()
	{
		static Logger* instance_ = new Logger();

		return instance_;
	}

	struct Level
	{
		char idx;
		string name;
	};

	/*
		The scoped_logger concept and some code was posted by Stack Overflow
		user "Xeo" on 2014/03/12 and was accessed by me on 2016/01/15.
		(http://stackoverflow.com/a/9669945)
	*/
	struct scoped_logger
	{
		scoped_logger(Level level, string file, int line)
		{
			level_ = level;
			file_ = file;
			line_ = line;
		}

		std::stringstream& stream()
		{
			return ss_;
		}

		~scoped_logger()
		{
			Logger::inst()->out(level_, file_, line_, ss_.str());
		}

	private:
		std::stringstream ss_;
		Level level_;
		string file_;
		int line_;
	};

	void init();
	void init(Level);
	void init(string outputFile);
	void init(Level, string outputFile);
	void init(string outputFile, int argc, char* argv[]);
	void init(int argc, char* argv[]);

	Level add_level(int idx, string name);

	void level(Level l);
	void out(Level l, string file, int line, string msg);
	void outf(Level l, string file, int line, string msg, ...);

private:
	Logger() {};
	Logger(Logger const&) {};
	void operator=(Logger const&) {};

	void init_();
	void initargs_(int argc, char * argv[]);
	void initfile_(string filename);

	vector<Level> levels_;
	Level level_;
	Output output_;
	string outputFileName_;
	std::ofstream outputFile_;
	vector<std::string> buffer_;

	void send(Level l, string msg, string file, int line = -1);
	bool active(Level l);
};

/*
	These are constructed upon init_()
*/
extern Logger::Level DEBUG_NONE;
extern Logger::Level DEBUG_CALLBACKS;
extern Logger::Level DEBUG_CALLBACKS_DEEP;
extern Logger::Level DEBUG_CORE;
extern Logger::Level DEBUG_CORE_DEEP;
extern Logger::Level DEBUG_INTERNAL;
extern Logger::Level DEBUG_INTERNAL_DEEP;
extern Logger::Level DEBUG_INTERFACE;
extern Logger::Level DEBUG_INTERFACE_DEEP;
extern Logger::Level DEBUG_LOOPS;

#endif
