#pragma comment(lib, "SDL2_ttf.lib")
#include "Menu.h"

Menu::Menu(std::string _path, int _sizeFont)
    :path(_path), sizeFont(_sizeFont) {}

void Menu::AddText(std::string str, SDL_Rect _rect, SDL_Renderer* renderer, SDL_Color textColor)
{
    text.push_back(std::move(std::unique_ptr<Font>(new Font(path, _rect, sizeFont))));
    text.back()->ChangeText(str, renderer);
}

void Menu::UpdateColor(SDL_Renderer* renderer)
{
    for (size_t i = 0; i < text.size(); i++)
    {
        if(i == menuPosition)
           text[i]->ChangeColor(67, 182, 59, renderer);
        else
           text[i]->ChangeColor(225, 225, 225, renderer);
    }
}

bool Menu::UpMenuPosition()
{
    if (menuPosition + 1 < text.size())
    {
        menuPosition++;
        return true;
    }
    return false;
}

bool Menu::DownMenuPosition()
{
    if (menuPosition > 0)
    {
        menuPosition--;
        return true;
    }
    return false;
}