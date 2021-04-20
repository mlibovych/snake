#pragma once

#include <memory>

#include "Framework.h"
#include "StateMachines/StateManager.h"

constexpr int cell_width = 16;

class StateMachine;


class Snake : public Framework {
    friend class StateMachine;
	friend class GameState;
    friend class MenuState;
    friend class ScoreboardState;
    friend class DeathState;

public:
    Snake(int width, int height) noexcept;

	virtual void PreInit(int& width, int& height, bool& fullscreen) noexcept override;

	virtual bool Init() noexcept override;

	virtual void Close() noexcept override;

	virtual bool Tick() override;

	virtual void onKeyPressed(FRKey k) noexcept override;
    virtual void onKeyPressed(int32_t k) noexcept override;

	virtual void onKeyReleased(FRKey k) noexcept override;

	virtual const char* GetTitle() noexcept override;

	virtual ~Snake() {};

    int AlignHorizontally(int tex_w, int text_padding) {
        return (m_window_w - (tex_w + (2 * text_padding))) / 2;
    }

private:
    static constexpr int m_padding = 30, m_menu_height = 100;

    std::unique_ptr<StateManager> m_StateManager;
	
    int m_width, m_height;
    int m_window_w, m_window_h;
    int m_playfield_w, m_playfield_h;
    bool m_quit = false;
};