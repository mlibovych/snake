#pragma once

#include "Framework.h"
#include "StateMachine.h"

class StateMachine;

class Snake : public Framework {
    friend class StateMachine;

public:
    Snake(int width, int height) noexcept;

	virtual void PreInit(int& width, int& height, bool& fullscreen) noexcept override;

	virtual bool Init() noexcept override;

	virtual void Close() noexcept override;

	virtual bool Tick() override;

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) noexcept override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) noexcept override;

	virtual void onKeyPressed(FRKey k) noexcept override;

	virtual void onKeyReleased(FRKey k) noexcept override;

    virtual bool onQuitEvent(uint32_t win_id) noexcept override;

	virtual const char* GetTitle() noexcept override;

	virtual ~Snake() {};

private:
    static constexpr int m_padding = 30, m_menu_height = 100;

    std::unique_ptr<StateMachine> m_StateMachine;
    int m_width, m_height;
};