#include <iostream>

#include "jett/core/renderer.hpp"

Renderer::Renderer(const std::string &title, Vector window_size) : window_size_(window_size)
{
    window_ = SDL_CreateWindow(title.c_str(),
                               static_cast<int>(window_size_.x),
                               static_cast<int>(window_size_.y),
                               SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if (!window_)
    {
        throw std::runtime_error("Failed to create window");
    }

    renderer_ = SDL_CreateRenderer(window_, NULL);
    if (!renderer_)
    {
        throw std::runtime_error("Failed to create renderer");
    }

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer_);

    SDL_DestroyWindow(window_);
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer_);
}

void Renderer::setWindowSize(Vector size)
{
    window_size_ = size;

    SDL_SetWindowSize(window_, static_cast<int>(window_size_.x), static_cast<int>(window_size_.y));
}

void Renderer::setWindowTitle(const std::string &title)
{
    SDL_SetWindowTitle(window_, title.c_str());
}

void Renderer::drawRect(Vector position, Vector size, SDL_Color color)
{
    SDL_FRect rect = {position.x, position.y, size.x, size.y};

    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer_, &rect);
}
