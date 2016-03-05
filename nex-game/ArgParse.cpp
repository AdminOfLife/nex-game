#include "stdafx.h"
#include <vector>
#include <string>
#include <set>
#include <map>

#include "ArgParse.h"


using std::vector;
using std::string;
using std::set;
using std::map;


namespace SDI
{

vector<string> parseArgs(int argc, char * argv[])
{
	vector<string> ret;

	for(int i = 0; i < argc; ++i)
		ret.push_back(argv[i]);

	return ret;
}

set<char> parseArgsFlags(int argc, char * argv[])
{
	set<char> ret;

	int idx;

	for(int i = 1; i < argc; ++i)
	{
		if(argv[i][0] != '-' && argv[i][0] != '/')
			continue;

		idx = 1;

		while(argv[i][idx] != '\0')
		{
			if(!isAlphabetic(argv[i][idx]))
				break;

			ret.insert(argv[i][idx]);

			idx++;
		}
	}

	return ret;
}

/*
	This variant collects single character flags that are passed with values,
	such as
		"foo –x=12 –y=true –z=Simon"
	returning {('x', "12") , ('y', "true") , ('z', "Simon")} or
		"bar –a=no –s=Richard –p=88356"
	returning {('a', "no") , ('p', "88356") , ('s', "Richard")}
*/
map<char, string> parseArgsValues(int argc, char * argv[])
{
	map<char, string> ret;

	char arg = 0;

	for (int i = 1; i < argc; ++i)
	{
		// If we're searching for an argument value
		if(arg)
		{
			if (argv[i][0] == '=')
				continue;

			// Was the stored arg a bool flag?
			// If another "-x" arg is found, restart the process
			if (argv[i][0] == '-' && isAlphabetic(argv[i][1]) && argv[i][2] == '\0')
			{
				arg = argv[i][1];
				continue;
			}
			else
			{
				ret[arg] = string(argv[i]);
				arg = 0;
				continue;
			}
		}

		// If not, we're searching for the actual "-x" argument specifier
		if (argv[i][0] == '-' && isAlphabetic(argv[i][1]) && argv[i][2] == '\0')
		{
			arg = argv[i][1];
		}
	}

	return ret;
}


/*
	Helper functions
*/
bool isAlphabetic(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

}