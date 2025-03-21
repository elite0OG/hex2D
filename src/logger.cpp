#include"logger.h"

void Hlog(unsigned int LOG, const char* v)
{
	switch (LOG) {
	case LOG_INFO:
		printf("\x1b[32mLOG_INFO: %s\n\x1b[0m", v);
		break;
	case LOG_WARN:
		printf("\x1b[33mLOG_WARN: %s\n\x1b[0m", v);
		break;
	case LOG_ERROR:
		printf("\x1b[31mLOG_ERROR: %s\n\x1b[0m", v);
		break;
	default:
		printf("\x1b[37mLOG_NOR: %s\n\x1b[0m", v);
		break;
	}

}

void Hlog(unsigned int LOG, std::string v)
{

	switch (LOG) {
	case LOG_INFO:
		std::cout << "\x1b[32mLOG_INFO: " << v << "\x1b[0m\n";
		break;
	case LOG_WARN:
		std::cout << "\x1b[33mLOG_WARN: " << v << "\x1b[0m\n";
		break;
	case LOG_ERROR:
		std::cout << "\x1b[31mLOG_ERROR: " << v << "\x1b[0m\n";
		break;
	default:
		std::cout << "\x1b[37mLOG_NOR: " << v << "\x1b[0m\n";  // Default case
		break;
	}
}