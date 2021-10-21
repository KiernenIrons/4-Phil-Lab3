#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include "Command.h"

class Game;

class Button
{
public:
    Button(float t_posX, float t_posY, TTF_Font* t_font, std::string t_name, Command* t_macro, SDL_Renderer* t_renderer) :
    m_posX(t_posX),
    m_posY(t_posY),
    m_font(t_font),
    m_name(t_name),
    m_macro(t_macro),
    m_renderer(t_renderer)
    {
        m_background.x = m_posX;
        m_background.y = m_posY;
        m_background.w = 150;
        m_background.h = 150;
        initText();
        initCounter(std::to_string(0));
    };
    void setCommand(Command* t_macro) 
    {
        m_macro = t_macro;
    }
    bool isCursorOver();
    virtual void click(MacroCommand* t_macro)
    {
        t_macro->addCommand(m_macro);
        m_count++;
    };
    void update();
    void draw()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(m_renderer, &m_background);
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
        SDL_RenderCopy(m_renderer, m_textTexture,nullptr, &m_text);

        if(m_showCounter)
        {
            SDL_RenderCopy(m_renderer, m_countTexture, nullptr, &m_countText);
        }
    }

private:
    void addBlocks();
    void initText()
    {
        SDL_Surface* surface = TTF_RenderText_Solid(m_font, m_name.c_str(), SDL_Color{0,255,0});
        m_textTexture = SDL_CreateTextureFromSurface(m_renderer, surface);        
        SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_text.w, &m_text.h);        
        m_text.x = m_posX + (m_background.w / 2.0f) - ((m_text.w / 2.0f));
        m_text.y = m_posY + (m_background.h / 2.0f) - (m_text.h / 2.0f);
        if(m_textTexture == nullptr) std::cout << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
    };
    void initCounter(std::string string)
    {
        SDL_Surface* tempSurf = TTF_RenderText_Solid(m_font, string.c_str(), SDL_Color{255,255,255});

        m_countTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurf);

        SDL_QueryTexture(m_countTexture, NULL, NULL, & m_countText.w, & m_countText.h);

        m_countText.x = m_posX + 128 - (m_countText.w / 2.0f);
        m_countText.y = m_posY + 128 + (m_countText.h / 2.0f);

        SDL_FreeSurface(tempSurf);
    };

protected:
    int m_count;
    float m_posX;
    float m_posY;
    bool m_showCounter;
    
    Command* m_macro;
    TTF_Font* m_font;
    std::string m_name;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_textTexture;
    SDL_Texture* m_countTexture;
    SDL_Rect m_background;
    SDL_Rect m_countText;
    SDL_Rect m_text;
};

class MacroButton : public Button
{
public:
    MacroButton(float t_posX, float t_posY, TTF_Font* t_font, std::string t_name, Command* t_macro, SDL_Renderer* t_renderer) : Button(
    t_posX,
    t_posY,
    t_font,
    t_name,
    t_macro,
    t_renderer)
    {
        m_showCounter = false;
        m_removeMacro = false;
    };
    void addMacro(std::function<void(Game*)> t_macro, Game* t_game)
    {
        m_macro = t_macro;
        m_game = t_game;
    };
    void removeMacro(bool t_removeMacro)
    {
        m_removeMacro = t_removeMacro;
    };
    virtual void click(MacroCommand* t_macro)
    {
        if (m_game == nullptr && m_macro == nullptr)
        {
            if (m_removeMacro)
            {
                t_macro->remove();
            }
            else
            {
                t_macro->undo();
            }
        }
        else
        {
            m_macro(m_game);
        }
    };

private:
    bool m_removeMacro;
    std::function<void(Game*)> m_macro;
    Game* m_game;
};