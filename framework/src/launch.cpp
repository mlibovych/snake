/*=============================================================================
	launch.cpp: basic framework
	Copyright 2018 Dragonslake, LLC. All Rights Reserved.
=============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "inc/Framework.h"


static SDL_Renderer *g_renderer;
static int g_width = 800;
static int g_height = 600;
static int g_framework_initialized = false;

/*
 * structure declarations
 */

class Sprite {
public:
	Sprite():w(0), h(0), tex(nullptr) {}

	int w, h;
	SDL_Texture* tex;
};

FRAMEWORK_API Sprite* createSprite(const char* path)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Texture* texture = IMG_LoadTexture(g_renderer, path);
	if (!texture) {
		fprintf(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
		return nullptr;
	}


	Sprite* s = new Sprite();
	if (!s)
	{
		fprintf(stderr, "Not enough memory\n");
		SDL_Quit();
		exit(1);
	}

	SDL_QueryTexture(texture, NULL, NULL, &s->w, &s->h);

	s->tex = texture;

	return s;
}

FRAMEWORK_API void destroySprite(Sprite* s)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(s);

	if (s->tex)
	{
		SDL_DestroyTexture(s->tex);
	}

	delete s;
}

FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h)
{
	SDL_assert(s);
	w = s->w;
	h = s->h;
}

FRAMEWORK_API void drawSprite(Sprite* sprite, int x, int y)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	SDL_assert(sprite);

	SDL_Rect r;
	r.w = sprite->w;
	r.h = sprite->h;
	r.x = x;
	r.y = y;
	SDL_RenderCopy(g_renderer, sprite->tex, NULL, &r);
}

FRAMEWORK_API void getScreenSize(int& w, int &h)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Rect viewport;
	SDL_RenderGetViewport(g_renderer, &viewport);
	w = viewport.w;
	h = viewport.h;
}

FRAMEWORK_API unsigned int getTickCount()
{
	return SDL_GetTicks();
}

FRAMEWORK_API void drawBGColor(Color color) {
    SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(g_renderer);
}

FRAMEWORK_API void drawRect(int w, int h, int x, int y, Color color)
{
    if (!g_renderer)
        return;
    
    SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect{x, y, w, h};

    SDL_RenderFillRect(g_renderer, &rect);
}

FRAMEWORK_API void drawText(char *text)
{
    if (!g_renderer)
        return;
}

/* Draw a Gimpish background pattern to show transparency in the image */
static void draw_background(SDL_Renderer *renderer, int w, int h)
{
    SDL_Color col[2] = {
        { 0x66, 0x66, 0x66, 0xff },
        { 0x99, 0x99, 0x99, 0xff },
    };
    int i, x, y;
    SDL_Rect rect;

    rect.w = 8;
    rect.h = 8;
    for (y = 0; y < h; y += rect.h) {
        for (x = 0; x < w; x += rect.w) {
            /* use an 8x8 checkerboard pattern */
            i = (((x ^ y) >> 3) & 1);
            SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);

            rect.x = x;
            rect.y = y;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}


FRAMEWORK_API void drawTestBackground()
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Rect viewport;
	SDL_RenderGetViewport(g_renderer, &viewport);
	return draw_background(g_renderer, viewport.w, viewport.h);
}

FRAMEWORK_API void showCursor(bool bShow)
{
	SDL_ShowCursor(bShow?1:0);
}

FRAMEWORK_API Sprite *generateTextTexture(const char *text, int font_size, Color color) {
    TTF_Font* font = TTF_OpenFont("./Framework/fonts/font.ttf", font_size);

    if (!font) {
        std::cerr << "Could not load font! Label will remain empty. Error: " 
                  << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, {color.r, color.g, color.b, color.a});

    if (!surfaceMessage) {
        std::cerr << "Could not create surface for a label! Label will remain empty. Error: " 
                    << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return nullptr;
    }

    SDL_Texture *label_tex = SDL_CreateTextureFromSurface(
        g_renderer,
        surfaceMessage
    );

    if (!label_tex) {
        std::cerr << "Could not create texture from surface! Label will remain empty. Error: " 
                    << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_FreeSurface(surfaceMessage);
        return nullptr;
    }

    Sprite *sprite = new Sprite;

    if (!sprite) {
        std::cerr << "Not enough memory!" << std::endl;
        std::terminate();
    }

    if (TTF_SizeText(font, text, &sprite->w, &sprite->h)) {
        std::cerr << "Could not determine label texture size! Label will remain empty. Error: " 
                    << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_FreeSurface(surfaceMessage);
        delete sprite;
        return nullptr;
    }

    sprite->tex = label_tex;

    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);

    return sprite;
}

bool GKeyState[(int)FRKey::COUNT] = {};

FRAMEWORK_API int run(Framework* framework)
{
    SDL_Window *window;
    Uint32 flags;
    int done;
    SDL_Event event;

	for (int i = 0; i < (int)FRKey::COUNT; ++i)
	{
		GKeyState[i] = false;
	}

	Framework* GFramework = framework;

	bool fullscreen = false;
	GFramework->PreInit(g_width, g_height, fullscreen);
	
    flags = SDL_WINDOW_HIDDEN;
	if (fullscreen) {
		SDL_ShowCursor(0);
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
        return(2);
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    if (SDL_CreateWindowAndRenderer(0, 0, flags, &window, &g_renderer) < 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        return(2);
    }

	{
        /* Show the window */
        SDL_SetWindowTitle(window, GFramework->GetTitle());
        SDL_SetWindowSize(window, g_width, g_height);
        SDL_ShowWindow(window);

		g_framework_initialized = true;


		if (!GFramework->Init())
		{
			fprintf(stderr, "Framework::Init failed\n");
			SDL_Quit();
			exit(1);
		}

        done = 0;
        while ( ! done ) {
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                    case SDL_KEYUP:
                        switch (event.key.keysym.sym) {
                            case SDLK_RIGHT:
                            case SDLK_LEFT:
                            case SDLK_DOWN:
                            case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								if (GKeyState[key_index])
								{
									GFramework->onKeyReleased((FRKey)key_index);
									GKeyState[key_index] = false;
								}
								break;
							}
                            case SDLK_ESCAPE:
								done = 1;
                            break;
	                        default:
		                        break;
                        }
                        break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
						case SDLK_RIGHT:
						case SDLK_LEFT:
						case SDLK_DOWN:
						case SDLK_UP:
						{
							int key_index = (event.key.keysym.sym - SDLK_RIGHT);
							if (!GKeyState[key_index])
							{
								GFramework->onKeyPressed((FRKey)key_index);
								GKeyState[key_index] = true;
							}
						}
							break;

						default:
							break;
						}
						break;
                    case SDL_MOUSEBUTTONDOWN:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), false);
						}
						break;
                    case SDL_MOUSEBUTTONUP:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), true);
						}
                        break;
					case SDL_MOUSEMOTION:
						GFramework->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                        break;
                    case SDL_QUIT:
                        done = 1;
                        break;
                    case SDL_WINDOWEVENT:
                        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                            GFramework->onQuitEvent(event.window.windowID);
                        break;
                    default:
                        break;
                }
            }

			done |= GFramework->Tick() ? 1 : 0;

            SDL_RenderPresent(g_renderer);

            // SDL_Delay(1);
        }
    }

	GFramework->Close();

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(window);

	g_framework_initialized = false;

    /* We're done! */
    TTF_Quit();
    SDL_Quit();
    return(0);
}
