
#include "lbpch.h"
#include "Window.h"

#ifdef PLATFORM_WINDOWS
	#include "platform/desktop/DesktopWindow.h"
#endif


std::unique_ptr<Window> Window::create(const WindowProps& props)
{
#ifdef PLATFORM_WINDOWS
	return std::make_unique<DesktopWindow>(props);
#else
	#error "Only Desktop supported"
	return nullptr;
#endif 

}
