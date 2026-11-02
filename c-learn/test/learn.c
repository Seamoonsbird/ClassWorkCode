#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 700
#define MAX_PARTICLES 3000
#define PI 3.1415926535f
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

// 粒子结构
typedef struct {
    float x, y;           // 位置
    float vx, vy;         // 速度
    float life;           // 生命周期 (0.0-1.0)
    float maxLife;        // 最大生命
    Uint8 r, g, b, a;     // 颜色
    float size;           // 大小
    float gravity;        // 重力系数
    float drag;           // 阻力系数
    float flicker;        // 闪烁系数
    float flickerSpeed;   // 闪烁速度
    float flickerPhase;   // 闪烁相位
    float brightness;     // 亮度
    float spin;           // 旋转
    float spinSpeed;      // 旋转速度
    float trailLength;    // 尾迹长度
    float trail[10][2];   // 尾迹位置记录
    int trailCount;       // 尾迹数量
    bool isExploded;      // 是否爆炸
    int explosionType;    // 爆炸类型 0:球状 1:心形 2:环状 3:瀑布
} Particle;

Particle particles[MAX_PARTICLES];
int particleCount = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;
Uint32 frameStart, frameTime;
int lastMouseX = 0, lastMouseY = 0;
bool mousePressed = false;

// 颜色渐变
typedef struct {
    Uint8 r, g, b;
} Color;

// 烟花颜色预设
Color fireworkColors[] = {
    {255, 50, 50},    // 红色
    {50, 255, 50},    // 绿色
    {50, 150, 255},   // 蓝色
    {255, 255, 50},   // 黄色
    {255, 50, 255},   // 紫色
    {50, 255, 255},   // 青色
    {255, 150, 50},   // 橙色
    {255, 200, 200},  // 粉色
    {150, 255, 150},  // 浅绿
    {200, 200, 255}   // 浅蓝
};
int numColors = 10;

// 高斯随机数
float gaussianRandom(float mean, float stddev) {
    static float spare;
    static bool hasSpare = false;
    
    if (hasSpare) {
        hasSpare = false;
        return mean + stddev * spare;
    }
    
    hasSpare = true;
    float u, v, s;
    do {
        u = (rand() / (RAND_MAX + 1.0f)) * 2.0f - 1.0f;
        v = (rand() / (RAND_MAX + 1.0f)) * 2.0f - 1.0f;
        s = u * u + v * v;
    } while (s >= 1.0f || s == 0.0f);
    
    s = sqrtf(-2.0f * logf(s) / s);
    spare = v * s;
    return mean + stddev * u * s;
}

// 初始化SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return false;
    }
    
    window = SDL_CreateWindow("🎆 超逼真烟花模拟 - ESC退出 | 空格发射 | 鼠标拖动 | 1-4选择类型", 
                               SDL_WINDOWPOS_CENTERED, 
                               SDL_WINDOWPOS_CENTERED,
                               WIDTH, HEIGHT, 
                               SDL_WINDOW_SHOWN);
    if (!window) {
        printf("创建窗口失败: %s\n", SDL_GetError());
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("创建渲染器失败: %s\n", SDL_GetError());
        return false;
    }
    
    // 启用透明度混合
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    srand(time(NULL));
    return true;
}

// 初始化粒子
void initParticle(Particle* p, float x, float y, bool isExploded, int explosionType, int colorIndex) {
    p->x = x;
    p->y = y;
    p->life = 1.0f;
    p->maxLife = 0.8f + (rand() / (float)RAND_MAX) * 0.4f;  // 随机生命长度
    p->isExploded = isExploded;
    p->explosionType = explosionType;
    p->size = 1.5f + (rand() / (float)RAND_MAX) * 2.5f;
    p->gravity = 0.05f + (rand() / (float)RAND_MAX) * 0.1f;
    p->drag = 0.985f + (rand() / (float)RAND_MAX) * 0.01f;
    p->flicker = 0.1f + (rand() / (float)RAND_MAX) * 0.2f;
    p->flickerSpeed = 10.0f + (rand() / (float)RAND_MAX) * 20.0f;
    p->flickerPhase = (rand() / (float)RAND_MAX) * 2 * PI;
    p->brightness = 0.8f + (rand() / (float)RAND_MAX) * 0.2f;
    p->spin = (rand() / (float)RAND_MAX) * 2 * PI;
    p->spinSpeed = (rand() / (float)RAND_MAX) * 0.2f - 0.1f;
    p->trailLength = 0;
    p->trailCount = 0;
    
    Color c = fireworkColors[colorIndex % numColors];
    p->r = c.r;
    p->g = c.g;
    p->b = c.b;
    p->a = 255;
    
    if (!isExploded) {
        // 上升阶段
        float baseSpeed = 6.0f + (rand() / (float)RAND_MAX) * 3.0f;
        float variance = 0.5f;
        p->vx = gaussianRandom(0.0f, variance);
        p->vy = -baseSpeed;
        
        // 上升粒子是白色/黄色
        p->r = 255;
        p->g = 255;
        p->b = 200;
    } else {
        // 爆炸阶段 - 根据爆炸类型设置速度
        switch (explosionType) {
            case 0: { // 标准球状
                float angle = (rand() / (float)RAND_MAX) * 2 * PI;
                float speed = 1.5f + (rand() / (float)RAND_MAX) * 3.0f;
                p->vx = cosf(angle) * speed;
                p->vy = sinf(angle) * speed;
                break;
            }
            case 1: { // 心形
                float t = (rand() / (float)RAND_MAX) * 2 * PI;
                float x = 16 * sinf(t) * sinf(t) * sinf(t);
                float y = -(13 * cosf(t) - 5 * cosf(2*t) - 2 * cosf(3*t) - cosf(4*t));
                p->vx = x * 0.08f;
                p->vy = y * 0.08f;
                break;
            }
            case 2: { // 环状
                float angle = (rand() / (float)RAND_MAX) * 2 * PI;
                float radius = 2.0f + (rand() / (float)RAND_MAX) * 1.5f;
                p->vx = cosf(angle) * radius;
                p->vy = sinf(angle) * radius;
                break;
            }
            case 3: { // 瀑布效果
                p->vx = (rand() / (float)RAND_MAX) * 4.0f - 2.0f;
                p->vy = 1.5f + (rand() / (float)RAND_MAX) * 3.0f;
                p->gravity = 0.02f;  // 较小的重力
                p->size = 1.0f + (rand() / (float)RAND_MAX) * 1.5f;
                break;
            }
        }
    }
}

// 更新尾迹
void updateTrail(Particle* p) {
    // 记录当前位置到尾迹数组
    for (int i = 9; i > 0; i--) {
        p->trail[i][0] = p->trail[i-1][0];
        p->trail[i][1] = p->trail[i-1][1];
    }
    p->trail[0][0] = p->x;
    p->trail[0][1] = p->y;
    
    if (p->trailCount < 10) {
        p->trailCount++;
    }
    p->trailLength = 1.0f;
}

// 发射新烟花
void launchFirework(int explosionType) {
    if (particleCount < MAX_PARTICLES - 200) {
        int x = rand() % (WIDTH - 300) + 150;
        int y = HEIGHT;
        int colorIndex = rand() % numColors;
        
        Particle* p = &particles[particleCount];
        initParticle(p, x, y, false, explosionType, colorIndex);
        
        // 为上升粒子添加一些随机性
        p->vx += (rand() / (float)RAND_MAX) * 0.8f - 0.4f;
        p->size = 2.0f;
        p->maxLife = 3.0f;  // 上升阶段更长
        
        particleCount++;
    }
}

// 在指定位置发射烟花
void launchFireworkAt(int x, int y, int explosionType) {
    if (particleCount < MAX_PARTICLES - 200) {
        int colorIndex = rand() % numColors;
        Particle* p = &particles[particleCount];
        initParticle(p, x, y, false, explosionType, colorIndex);
        p->size = 2.0f;
        p->maxLife = 3.0f;
        particleCount++;
    }
}

// 创建爆炸
void createExplosion(float x, float y, int explosionType, int colorIndex) {
    int explosionCount = 80 + rand() % 120;
    
    for (int i = 0; i < explosionCount; i++) {
        if (particleCount < MAX_PARTICLES) {
            Particle* p = &particles[particleCount];
            initParticle(p, x, y, true, explosionType, colorIndex);
            
            // 添加一些随机性
            p->vx += gaussianRandom(0.0f, 0.2f);
            p->vy += gaussianRandom(0.0f, 0.2f);
            
            // 随机大小
            p->size *= 0.5f + (rand() / (float)RAND_MAX);
            
            particleCount++;
        }
    }
}

// 更新粒子
void updateParticles() {
    for (int i = 0; i < particleCount; i++) {
        Particle* p = &particles[i];
        
        if (p->life <= 0) continue;
        
        // 更新尾迹
        updateTrail(p);
        
        // 更新位置
        p->x += p->vx;
        p->y += p->vy;
        
        // 物理效果
        p->vy += p->gravity;  // 重力
        
        if (p->isExploded) {
            // 爆炸粒子的物理
            p->vx *= p->drag;
            p->vy *= p->drag;
            
            // 空气阻力导致的随机扰动
            p->vx += gaussianRandom(0.0f, 0.01f);
            p->vy += gaussianRandom(0.0f, 0.01f);
            
            // 旋转
            p->spin += p->spinSpeed;
            
            // 闪烁效果
            p->flickerPhase += p->flickerSpeed * 0.01f;
            float flicker = 1.0f + sinf(p->flickerPhase) * p->flicker;
            p->brightness = 0.7f + 0.3f * flicker;
            
            // 生命周期减少速度取决于爆炸类型
            float decayRate = 0.01f;
            if (p->explosionType == 3) decayRate = 0.005f;  // 瀑布效果更慢
            p->life -= decayRate;
        } else {
            // 上升粒子
            p->life -= 0.003f;
            
            // 上升粒子到达顶点时爆炸
            if (p->vy >= -0.5f) {
                createExplosion(p->x, p->y, p->explosionType, rand() % numColors);
                p->life = 0;
            }
        }
        
        // 边界检查
        if (p->x < -50 || p->x > WIDTH + 50 || p->y < -50 || p->y > HEIGHT + 50) {
            p->life = 0;
        }
    }
}

// 绘制粒子尾迹
void drawParticleTrail(Particle* p) {
    if (p->trailCount < 2) return;
    
    float alphaStep = 0.8f / p->trailCount;
    for (int i = 0; i < p->trailCount - 1; i++) {
        float alpha = 0.1f + alphaStep * i;
        float size = p->size * (0.3f + 0.7f * i / p->trailCount);
        
        SDL_SetRenderDrawColor(renderer, 
            p->r * alpha, 
            p->g * alpha, 
            p->b * alpha, 
            (Uint8)(alpha * 100));
        
        int x1 = (int)p->trail[i][0];
        int y1 = (int)p->trail[i][1];
        int x2 = (int)p->trail[i+1][0];
        int y2 = (int)p->trail[i+1][1];
        
        // 绘制线条连接尾迹点
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        
        // 绘制尾迹点
        SDL_Rect rect = {x1 - (int)size/2, y1 - (int)size/2, (int)size, (int)size};
        SDL_RenderFillRect(renderer, &rect);
    }
}

// 绘制粒子
void drawParticles() {
    for (int i = 0; i < particleCount; i++) {
        Particle* p = &particles[i];
        
        if (p->life <= 0) continue;
        
        // 绘制尾迹
        if (p->isExploded) {
            drawParticleTrail(p);
        }
        
        // 计算当前大小和透明度
        float lifeRatio = p->life / p->maxLife;
        float currentSize = p->size * lifeRatio;
        Uint8 alpha = (Uint8)(p->life * 255 * p->brightness);
        
        if (currentSize < 0.5f) currentSize = 0.5f;
        
        // 设置颜色
        SDL_SetRenderDrawColor(renderer, 
            (Uint8)(p->r * p->brightness), 
            (Uint8)(p->g * p->brightness), 
            (Uint8)(p->b * p->brightness), 
            alpha);
        
        // 绘制粒子
        int size = (int)currentSize;
        if (size < 1) size = 1;
        
        if (p->isExploded && p->explosionType == 2) {
            // 环状爆炸绘制为圆环
            SDL_Rect outer = {(int)p->x - size, (int)p->y - size, size * 2, size * 2};
            SDL_Rect inner = {(int)p->x - size/2, (int)p->y - size/2, size, size};
            SDL_RenderDrawRect(renderer, &outer);
            SDL_RenderDrawRect(renderer, &inner);
        } else {
            // 普通粒子绘制为实心矩形
            SDL_Rect rect = {(int)p->x - size/2, (int)p->y - size/2, size, size};
            SDL_RenderFillRect(renderer, &rect);
            
            // 添加高光效果
            if (size > 2) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha / 2);
                SDL_Rect highlight = {(int)p->x - size/4, (int)p->y - size/4, size/2, size/2};
                SDL_RenderFillRect(renderer, &highlight);
            }
        }
    }
}

// 清理死亡粒子
void cleanupParticles() {
    int alive = 0;
    for (int i = 0; i < particleCount; i++) {
        if (particles[i].life > 0) {
            particles[alive] = particles[i];
            alive++;
        }
    }
    particleCount = alive;
}

// 处理输入
void handleInput(int* explosionType) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_SPACE:
                    launchFirework(*explosionType);
                    break;
                case SDLK_1:
                    *explosionType = 0;
                    break;
                case SDLK_2:
                    *explosionType = 1;
                    break;
                case SDLK_3:
                    *explosionType = 2;
                    break;
                case SDLK_4:
                    *explosionType = 3;
                    break;
                case SDLK_r:
                    particleCount = 0;
                    break;
                case SDLK_c:
                    // 清屏
                    SDL_SetRenderDrawColor(renderer, 5, 5, 20, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    break;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            mousePressed = true;
            SDL_GetMouseState(&lastMouseX, &lastMouseY);
            launchFireworkAt(lastMouseX, HEIGHT, *explosionType);
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            mousePressed = false;
        } else if (event.type == SDL_MOUSEMOTION && mousePressed) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (abs(x - lastMouseX) > 20 || abs(y - lastMouseY) > 20) {
                launchFireworkAt(x, HEIGHT, *explosionType);
                lastMouseX = x;
                lastMouseY = y;
            }
        }
    }
}

// 绘制星星背景
void drawStars() {
    static bool starsInitialized = false;
    static int starX[200], starY[200], starSize[200], starBrightness[200];
    
    if (!starsInitialized) {
        for (int i = 0; i < 200; i++) {
            starX[i] = rand() % WIDTH;
            starY[i] = rand() % (HEIGHT / 2);
            starSize[i] = rand() % 3 + 1;
            starBrightness[i] = 100 + rand() % 155;
        }
        starsInitialized = true;
    }
    
    for (int i = 0; i < 200; i++) {
        // 星星闪烁
        int brightness = starBrightness[i] + (int)(sinf(SDL_GetTicks() * 0.001f + i) * 20);
        if (brightness < 50) brightness = 50;
        if (brightness > 255) brightness = 255;
        
        SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 200);
        SDL_Rect star = {starX[i], starY[i], starSize[i], starSize[i]};
        SDL_RenderFillRect(renderer, &star);
    }
}

// 绘制UI
void drawUI(int explosionType, int fps, int particleCount) {
    // 绘制半透明背景
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_Rect uiRect = {10, 10, 350, 150};
    SDL_RenderFillRect(renderer, &uiRect);
    SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
    SDL_RenderDrawRect(renderer, &uiRect);
    
    // 这里可以添加文本（实际项目中应使用SDL_ttf）
    // 简单用矩形表示UI元素
    
    // 爆炸类型指示器
    const char* typeNames[] = {"球状", "心形", "环状", "瀑布"};
    SDL_Color typeColors[] = {
        {255, 100, 100, 255},
        {255, 100, 200, 255},
        {100, 200, 255, 255},
        {100, 255, 100, 255}
    };
    
    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(renderer, 
            typeColors[i].r, typeColors[i].g, typeColors[i].b, 
            explosionType == i ? 255 : 100);
        
        SDL_Rect typeRect = {30, 30 + i * 25, 15, 15};
        SDL_RenderFillRect(renderer, &typeRect);
        
        if (explosionType == i) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &typeRect);
        }
    }
}

int main(int argc, char* argv[]) {
    printf("🎆 超逼真烟花模拟 v2.0\n");
    printf("=====================\n");
    printf("控制说明:\n");
    printf("  ESC     - 退出程序\n");
    printf("  空格键  - 发射随机烟花\n");
    printf("  鼠标点击/拖动 - 在指定位置发射\n");
    printf("  1-4键   - 选择爆炸类型\n");
    printf("  R键     - 重置所有粒子\n");
    printf("  C键     - 清屏\n");
    printf("\n爆炸类型:\n");
    printf("  1 - 球状爆炸\n");
    printf("  2 - 心形爆炸\n");
    printf("  3 - 环状爆炸\n");
    printf("  4 - 瀑布效果\n");
    printf("=====================\n");
    
    if (!initSDL()) {
        return 1;
    }
    
    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;
    int launchTimer = 0;
    int explosionType = 0;  // 当前爆炸类型
    
    // 初始发射几个烟花
    for (int i = 0; i < 3; i++) {
        launchFirework(explosionType);
        SDL_Delay(100);
    }
    
    // 主循环
    while (running) {
        frameStart = SDL_GetTicks();
        
        handleInput(&explosionType);
        
        // 更新粒子
        updateParticles();
        cleanupParticles();
        
        // 随机发射新烟花
        launchTimer++;
        if (launchTimer >= 120) {  // 每2秒发射一个
            launchFirework(explosionType);
            launchTimer = 0;
        }
        if (rand() % 100 == 0) {  // 随机发射
            launchFirework(explosionType);
        }
        
        // 渲染
        // 渐变夜空背景
        for (int y = 0; y < HEIGHT; y++) {
            int blue = 10 + y * 20 / HEIGHT;
            int darkBlue = 5 + y * 10 / HEIGHT;
            SDL_SetRenderDrawColor(renderer, darkBlue, darkBlue, blue + 10, 255);
            SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
        }
        
        drawStars();        // 绘制星星
        drawParticles();    // 绘制烟花
        drawUI(explosionType, frames, particleCount);  // 绘制UI
        
        // 显示FPS
        frames++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000) {
            char title[150];
            sprintf(title, "🎆 烟花模拟 | FPS: %d | 粒子数: %d | 类型: %s | 空格键发射 | ESC退出", 
                    frames, particleCount, 
                    explosionType == 0 ? "球状" : 
                    explosionType == 1 ? "心形" : 
                    explosionType == 2 ? "环状" : "瀑布");
            SDL_SetWindowTitle(window, title);
            frames = 0;
            lastTime = currentTime;
        }
        
        SDL_RenderPresent(renderer);
        
        // 控制帧率
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    
    // 清理
    printf("\n程序退出，清理资源...\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("烟花模拟已关闭。\n");
    return 0;
}