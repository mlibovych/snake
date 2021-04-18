#include "inc/Subwindow.h"

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Subwindow::Subwindow(int window_y, int window_x) {
    CreateWindowAndRenderer(window_y, window_x);
}

Subwindow::~Subwindow() {
    SDL_DestroyRenderer(reinterpret_cast<SDL_Renderer*>(m_renderer));
    SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(m_window));
}

void Subwindow::CreateWindowAndRenderer(int window_y, int window_x) {
    if (SDL_CreateWindowAndRenderer(window_x,
                                    window_y,
                                    0,
                                    reinterpret_cast<SDL_Window**>(&m_window),
                                    reinterpret_cast<SDL_Renderer**>(&m_renderer)) < 0)
    {
        throw std::runtime_error(
            "SDL_CreateWindowAndRenderer() failed: " + std::string(SDL_GetError())
        );
    }

    m_wind_id = SDL_GetWindowID(reinterpret_cast<SDL_Window*>(m_window));
}

uint32_t Subwindow::GetWindowId() const {
    return SDL_GetWindowID(reinterpret_cast<SDL_Window*>(m_window));
}

