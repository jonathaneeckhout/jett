#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <map>

#include "jett/utils/vector.hpp"

class Renderer
{
public:
    Renderer(const std::string &title, Vector window_size);
    ~Renderer();

    void clear();
    void present();

    Vector getWindowSize() { return window_size_; }
    void setWindowSize(Vector size);

    void setWindowTitle(const std::string &title);

    void drawRect(Vector position, Vector size, SDL_Color color);

private:
    SDL_Window *window_ = nullptr;

    SDL_Renderer *renderer_ = nullptr;

    Vector window_size_;
};