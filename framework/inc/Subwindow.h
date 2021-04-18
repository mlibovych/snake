#include <stdint.h>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class Subwindow {
    uint32_t m_wind_id;

protected:
    void *m_window;
    void *m_renderer;

public:
    Subwindow(int window_y, int window_x);
    virtual ~Subwindow();

    void CreateWindowAndRenderer(int window_y, int window_x);
    uint32_t GetWindowId() const;

    virtual void Render() = 0;
};