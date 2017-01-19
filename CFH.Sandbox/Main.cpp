#include "Core\Application.h"
#include "Core\Messaging\Messages.h"
#include "Core\Timing\GameTime.h"

#include <GL\glew.h>

using namespace CFH;

class GraphicsDevice
{
public:
	GraphicsDevice(Application* application)
	{
		application->UpdateSubscribe([this](GameTime* gameTime) { Update(gameTime); });
		application->RenderSubscribe([this]() { Render(); });
	}

	void Initialize()
	{
	}

	void Update(GameTime* gameTime)
	{
	}

	void Render()
	{
	}
};

int main(int argc, char* argv[])
{
	Application* application = new Application();
	GraphicsDevice* device = new GraphicsDevice(application);

	application->Initialize(800, 600, L"CFH Sandbox");
	device->Initialize();
	
	application->Start();

	delete application;
	delete device;
	return 0;
}