#pragma once

#include "Framework.h"
#include "StateMachines/StateManager.h"

class StateMachine;

class Snake : public Framework {
    friend class StateMachine;
	friend class GameState;
    friend class MenuState;

public:
    Snake(int width, int height) noexcept;

	virtual void PreInit(int& width, int& height, bool& fullscreen) noexcept override;

	virtual bool Init() noexcept override;

	virtual void Close() noexcept override;

	virtual bool Tick() override;

	virtual void onKeyPressed(FRKey k) noexcept override;

	virtual void onKeyReleased(FRKey k) noexcept override;

	virtual const char* GetTitle() noexcept override;

	virtual ~Snake() {};

private:
    static constexpr int m_padding = 30, m_menu_height = 100;

    std::unique_ptr<StateManager> m_StateManager;
    int m_window_w, m_window_h;
    int m_playfield_w, m_playfield_height;
    bool m_quit = false;
};