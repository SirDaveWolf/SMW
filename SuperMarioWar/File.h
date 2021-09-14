#pragma once

#include <string>
#include <sstream>
#include <fstream>

namespace SMW
{
	class File
	{
	public:
		static std::string ReadAllText(const std::string& filename)
		{
			std::stringstream buffer;

			auto configFile = std::ifstream(filename, std::ifstream::in);
			buffer << configFile.rdbuf();

			configFile.close();

			return buffer.str();
		}
	};
}

