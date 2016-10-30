#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include "dx11renderer.h"

union SDL_Event;
struct SDL_Window;

namespace ice
{

namespace rendering
{

class DisplayManager
{
public:
    struct Options
    {
        const char* pTitle;
        size_t screenWidth;
        size_t screenHeight;
    };

public:
    DisplayManager(const Options& options)
        : options_(options)
    {}

public:
    bool Init();
    void HandleWindowEvents(SDL_Event* pWindowEvents, unsigned numEvents);
    dx11rendering::DX11Renderer& GetRenderer() { return renderer_; }
    Options GetOptions() const { return options_; }

private:
    dx11rendering::DX11Renderer renderer_;
    Options options_;
    SDL_Window* pWindow_;
};

} // namespace rendering

} // namespace ice

#endif // DISPLAYMANAGER_H
