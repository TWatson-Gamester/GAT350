#include "Framebuffer.h"

//#define SLOPE
#define DDA
//#define BRESENHAM

Framebuffer::Framebuffer(Renderer* renderer, int width, int height){
    this->width = width;
    this->height = height;

    texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    pitch = width * sizeof(color_t);
    buffer = new uint8_t[pitch * height];

}

Framebuffer::~Framebuffer(){
    SDL_DestroyTexture(texture);
    delete[] buffer;
}

void Framebuffer::Update(){
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
}

void Framebuffer::Clear(const color_t& color){
    for (int i = 0; i < width * height; i++) {

        ((color_t*)buffer)[i] = color;

        //buffer[i * sizeof(color_t)] = color.r;
        //buffer[i * sizeof(color_t) + 1] = color.g;
        //buffer[i * sizeof(color_t) + 2] = color.b;
        //buffer[i * sizeof(color_t) + 3] = color.a;
    }
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color){
    if (x < 0 || x >= width || y < 0 || y >= height) return;

    int i = x + y * width;

    ((color_t*)buffer)[i] = color;
}

void Framebuffer::DrawRect(int x, int y, int rect_width, int rect_height, const color_t& color){
    for (int sy = y; sy < y + rect_height; sy++) {
        for (int sx = x; sx < x + rect_width; sx++) {
            DrawPoint(sx, sy, color);
        }
    }
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color){
    int dx = x2 - x1; //run
    int dy = y2 - y1; //rise

#if defined(SLOPE)

    if (dx == 0) {
        if (y1 > y2) std::swap(y1, y2);
        for (int y = y1; y <= y2; y++) {
            DrawPoint(x1, y, color);
        }
    } else {

        float m = dy / (float)dx; //slope
        float b = y1 - (m * x1); //y intercept

        if (x1 > x2) std::swap(x1, x2);
        if (std::abs(dx) > std::abs(dy)) {
            if (x1 > x2) std::swap(x1, x2);
            for (int x = x1; x <= x2; x++) {
                int y = (int)round((m * x) + b);
                DrawPoint(x, y, color);
            }
        }
        else {
            if (y1 > y2) std::swap(y1, y2);
            for (int y = y1; y <= y2; y++) {
                int x = (int)round((y - b) / m);
                DrawPoint(x, y, color);
            }
        }
    }
#elif defined(DDA)
    int steps = std::max(std::abs(dx), std::abs(dy));
    float ddx = dx / (float)steps;
    float ddy = dy / (float)steps;

    float x = (float)x1;
    float y = (float)y1;

    for (int i = 0; i < steps; i++) {
        DrawPoint(x, y, color);
        x += ddx;
        y += ddy;
    }

#endif
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color){
    // connect the points to form a triangle
    // draw line from x1,y1 -> x2,y2
    DrawLine(x1, y1, x2, y2, color);
    // draw line from ?? -> ??
    DrawLine(x2, y2, x3, y3, color);
    // draw line from ?? -> ??
    DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawCircle(int x, int y, int radius, const color_t& color){

}

void Framebuffer::DrawSimpleCurve(int x1, int y1, int x2, int y2, int steps, const color_t& color){
    float dt = 1.0f / steps;
    for (int i = 0; i < steps; i++) {
        float t1 = i * dt;
        float t2 = (i + 1) * dt;

        int sx1 = Lerp(x1, x2, t1);
        int sy1 = Lerp(y1, y2, t1);
        int sx2 = Lerp(x1, x2, t2);
        int sy2 = Lerp(y1, y2, t2);


        DrawLine(sx1, sy1, sx2, sy2, color);
    }
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, int steps, const color_t& color){
    float dt = 1.0f / steps;
    for (int i = 0; i < steps; i++) {
        float t1 = i * dt;
        float t2 = (i + 1) * dt;

        float a1 = (float)pow((1.0f - t1), 2.0f);
        float b1 = 2.0f * (1.0f - t1) * t1;
        float c1 = (float)pow(t1, 2.0f);

        int sx1 = a1 * x1 + b1 * x2 + c1 * x3;
        int sy1 = a1 * y1 + b1 * y2 + c1 * y3;

        float a2 = (float)pow((1.0f - t2), 2.0f);
        float b2 = 2.0f * (1.0f - t2) * t2;
        float c2 = (float)pow(t2, 2.0f);

        int sx2 = a2 * x1 + b2 * x2 + c2 * x3;
        int sy2 = a2 * y1 + b2 * y2 + c2 * y3;

        DrawLine(sx1, sy1, sx2, sy2, color);
    }
}

int Framebuffer::Lerp(int a, int b, float t){
    return (int)(a + ((b-a) * t));
}
