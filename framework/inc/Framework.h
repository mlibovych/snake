#pragma once

#include <cstdint>

#if defined(_WINDOWS)

    #if defined(FRAMEWORK_PROJECT)
        #define FRAMEWORK_API extern "C" __declspec(dllexport)
    #else
        #define FRAMEWORK_API extern "C" __declspec(dllimport)
    #endif
#else
    #define FRAMEWORK_API 
#endif


// Bonus for any found bugs in the framework!

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a = 0xFF;
};


class Sprite;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h);
FRAMEWORK_API void destroySprite(Sprite* s);

FRAMEWORK_API void drawTestBackground();

FRAMEWORK_API void getScreenSize(int& w, int &h);

FRAMEWORK_API void drawBGColor(Color color);
FRAMEWORK_API void drawRect(int w, int h, int x, int y, Color color);
FRAMEWORK_API Sprite *generateTextTexture(const char *text, int font_size, Color color, int *w, int *h);

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();

FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT = 0x4000004F,
	LEFT = 0x40000050,
	DOWN = 0x40000051,
	UP = 0x40000052,
    ESC = 0x1B,
    P = 0x70,
    ENTER = 0x0D,
	COUNT = 7
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Framework {
public:
	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	// virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	// virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

    virtual bool onQuitEvent(uint32_t win_id) = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};
};


FRAMEWORK_API int run(Framework*);
