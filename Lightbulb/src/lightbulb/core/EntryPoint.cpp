#include "lbpch.h"

#include "lightbulb/App.h"

int main()
{
	
#ifdef CONFIG_DEBUG
	Log::init("App");
#endif

	auto app = lightbulb::createApp();
	app->run();

#ifdef CONFIG_DEBUG
	system("pause");
#endif
	return 0;
}