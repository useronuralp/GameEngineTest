#pragma once
#include "pch.h"
namespace AnorEngine {
	class FileUtils {
	public:
		static ANOR_API std::string read_file(const char* filepath) // a beautiful file reading system look into this later. Advantage of this kind of
			//file reading is that it is very fast.
		{
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}	
	};
}