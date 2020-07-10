#include "rtpch.h"

#include "raytracer/App.h"

int main()
{
	
#ifdef CONFIG_DEBUG
	Log::init("App");
#endif

	auto app = std::make_unique<App>();
	app->run();

#ifdef CONFIG_DEBUG
	system("pause");
#endif

	return 0;
}