#include "Core\Application.h"

using namespace CFH;

int main(int argc, char* argv[])
{
	Application* application = new Application();

	application->Run();
	return 0;
}