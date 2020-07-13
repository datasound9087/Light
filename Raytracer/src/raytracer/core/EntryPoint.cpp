#include "rtpch.h"

#include "raytracer/App.h"

int main()
{
	
#ifdef CONFIG_DEBUG
	Log::init("App");
#endif

	std::string p = "#type vertex\r";
	std::string t = "#type";
	std::string v = "vertex";
	INFO(p.find(t) == 0);
	INFO(p.find(v));

	auto app = std::make_unique<App>();
	app->run();

#ifdef CONFIG_DEBUG
	system("pause");
#endif
	return 0;
}