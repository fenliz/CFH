#include "Core\Application.h"

#include <GL\glew.h>

using namespace CFH;

int main(int argc, char* argv[])
{
	Application* application = new Application();
	application->Start();
	return 0;
}