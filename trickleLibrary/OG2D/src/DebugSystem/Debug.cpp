#include "Debug.h"

void Debug::OutputDebugText(char* outText)
{
	std::ofstream ofs(this->filepath,std::ios::app);
	if (!ofs)
	{
		std::cout << "FileOpenError!" << std::endl;
		return;
	}
	ofs << outText << std::endl;
	ofs.close();
}