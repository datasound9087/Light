#include "lbpch.h"

#include "lightbulb/App.h"

void func3(int y)
{

	y = 0;
}

void func2(int& u)
{
	u = 0;
}

void func(int* i)
{
	*i = 0;
}

int main()
{
	
#ifdef CONFIG_DEBUG
	Log::init("App");
#endif

	int i = 5;
	func(&i);
	func2(i);
	func3(i);
	//i will be 0 here

	auto app = lightbulb::createApp();
	app->run();

#ifdef CONFIG_DEBUG
	system("pause");
#endif
	return 0;
}