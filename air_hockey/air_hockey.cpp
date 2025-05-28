/*
 * File:        air_hockey.cpp
 * Author:      Ali Younes    <younes.al@northeastern.edu>
 * Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
 * Description: Fully-functional ASCII Air-Hockey (C++14 safe)
 */

#include <ncurses.h>
#include <cstring>          // strlen
#include <vector>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <ctime>
#include "key.hpp"
#include "ball.hpp"
#include "slider.hpp"
#include "air_hockey.hpp"

//────────────── Best-10 persistence (C++14 style, no init-statement) ──────────
static const char *SAVE_DIR  = "saves";
static const char *SAVE_FILE = "saves/save_best_10.game";

static void recordRounds(int r)
{
    mkdir(SAVE_DIR, 0755);

    std::vector<int> best;
    std::ifstream in(SAVE_FILE);
    int x;
    while (in >> x && best.size() < 10) best.push_back(x);
    in.close();

    best.push_back(r);
    std::sort(best.begin(), best.end());
    if (best.size() > 10) best.resize(10);

    std::ofstream out(SAVE_FILE, std::ofstream::trunc);
    for (int n : best) out << n << '\n';
}

//────────────── Nice-looking centered text helpers ───────────────────────────
static void centerPrint(int row, const char *txt)
{
    int h, w; getmaxyx(stdscr, h, w);
    int col = (w - std::strlen(txt)) / 2;
    mvprintw(row, col, "%s", txt);
}

//────────────── Welcome / Game-over screens ──────────────────────────────────
static void welcome(int &plen, int &rounds, int &goalW, int &diff)
{
    clear(); echo();
    centerPrint(1, "Welcome to 2-Player Air Hockey!");
    centerPrint(3, "Controls  Top: W/S/A/D   Bottom: arrows");
    centerPrint(4, "          P = pause/resume   Q = quit");

    mvprintw(6,  4, "Paddle length (4-7): ");               refresh(); scanw("%d", &plen);
    mvprintw(8,  4, "Odd number of rounds (>0): ");         refresh(); scanw("%d", &rounds);
    mvprintw(10, 4, "Goal width (<= play area): ");         refresh(); scanw("%d", &goalW);
    mvprintw(12, 4, "Difficulty 1=Easy 2=Med 3=Hard: ");    refresh(); scanw("%d", &diff);

    noecho(); clear(); refresh();
}

static void goodbye(int ts, int bs)
{
    clear();
    centerPrint(5, "Game Over!");
    centerPrint(7, ts > bs ? "Top player wins!" : "Bottom player wins!");

    char buf[64];
    std::snprintf(buf, sizeof(buf), "Final score  Top:%d  Bottom:%d", ts, bs);
    centerPrint(9, buf);
    centerPrint(11, "Press any key to exit.");

    refresh(); nodelay(stdscr, false); getch();
}

//────────────── Obstacle drawing ─────────────────────────────────────────────
static void drawObs(const std::vector<std::pair<int,int>> &obs)
{
    attron(COLOR_PAIR(5));
    for (auto &p : obs) mvaddch(p.second, p.first, 'X');
    attroff(COLOR_PAIR(5));
}

//────────────── Main game ────────────────────────────────────────────────────
void air_hockey()
{
    // ncurses + colours
    initscr(); cbreak(); noecho(); keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_WHITE,  COLOR_BLACK); // text / goals
    init_pair(2, COLOR_CYAN,   COLOR_BLACK); // arena
    init_pair(3, COLOR_GREEN,  COLOR_BLACK); // paddles
    init_pair(4, COLOR_RED,    COLOR_BLACK); // puck
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // obstacles

    // prompts
    int plen, rounds, goalW, diff;
    welcome(plen, rounds, goalW, diff);
    int needToWin = rounds / 2 + 1;
    nodelay(stdscr, true);

    // arena in half-screen
    int termH, termW; getmaxyx(stdscr, termH, termW);
    int zoneW = std::max(termW / 2, 40);
    int zoneH = std::max(termH / 2, 12);
    int ox = (termW - zoneW) / 2;
    int oy = (termH - zoneH) / 2;

    int goalX = ox + (zoneW - goalW) / 2;

    // difficulty
    long delayNS = 70'000'000;  // easy
    int nObs = 0;
    if (diff == 2) delayNS = 50'000'000;
    if (diff == 3) { delayNS = 30'000'000; nObs = 2; }

    // obstacles
    std::srand(std::time(nullptr));
    std::vector<std::pair<int,int>> obs;
    for (int i = 0; i < nObs; ++i)
        obs.emplace_back( ox + 1 + std::rand() % (zoneW-2),
                          oy + 1 + std::rand() % (zoneH-2) );

    // objects
    zone_t   *zone = init_zone(ox, oy, zoneW, zoneH);
    ball_t   *ball = init_ball(ox + zoneW/2, oy + zoneH/2, 1, 1);
    slider_t *top  = init_slider(ox + zoneW/2, oy + 2,        'T', plen);
    slider_t *bot  = init_slider(ox + zoneW/2, oy + zoneH-3,  'U', plen);

    int ts = 0, bs = 0, frame = 0;
    bool paused = false;

    //──────────────────────── loop ────────────────────────
    while (ts < needToWin && bs < needToWin)
    {
        frame++;
        int ch, code = read_escape(&ch);
        if (code == REGCHAR && (ch == 'q' || ch == 'Q')) break;
        if (code == REGCHAR && (ch == 'p' || ch == 'P')) paused = !paused;

        if (!paused)
        {
            // erase previous frame
            undraw_zone(zone);
            undraw_slider(top);
            undraw_slider(bot);
            undraw_ball(ball);

            // bottom paddle
            if (code == LEFT  && bot->upper_left_x > ox+1)                      --bot->upper_left_x;
            if (code == RIGHT && bot->upper_left_x < ox+zoneW-bot->length)      ++bot->upper_left_x;
            if (code == UP    && bot->upper_left_y > oy+1)                      --bot->upper_left_y;
            if (code == DOWN  && bot->upper_left_y < oy+zoneH-2)                ++bot->upper_left_y;
            // top paddle
            if (code == A && top->upper_left_x > ox+1)                          --top->upper_left_x;
            if (code == D && top->upper_left_x < ox+zoneW-top->length)          ++top->upper_left_x;
            if (code == W && top->upper_left_y > oy+1)                          --top->upper_left_y;
            if (code == S && top->upper_left_y < oy+zoneH-2)                    ++top->upper_left_y;

            // clamp paddles (extra safety)
            top->upper_left_x = std::max(top->upper_left_x, ox+1);
            top->upper_left_x = std::min(top->upper_left_x, ox+zoneW-top->length);
            top->upper_left_y = std::max(top->upper_left_y, oy+1);
            top->upper_left_y = std::min(top->upper_left_y, oy+zoneH-2);

            bot->upper_left_x = std::max(bot->upper_left_x, ox+1);
            bot->upper_left_x = std::min(bot->upper_left_x, ox+zoneW-bot->length);
            bot->upper_left_y = std::max(bot->upper_left_y, oy+1);
            bot->upper_left_y = std::min(bot->upper_left_y, oy+zoneH-2);

            // move puck every other frame for smoother play
            if (frame % 2 == 0)
            {
                moveBall(ball);
                int bx = ball->upper_left_x;
                int by = ball->upper_left_y;

                // goal detection (interior rows oy+1 and oy+zoneH-1)
                if (by == oy+1 && bx >= goalX && bx < goalX + goalW)
                {
                    ++bs;
                    ball->upper_left_x = ox + zoneW/2;
                    ball->upper_left_y = oy + zoneH/2;
                    ball->speed_y = 1;     // serve downward
                    continue;              // skip bounce logic this frame
                }
                if (by == oy+zoneH-1 && bx >= goalX && bx < goalX + goalW)
                {
                    ++ts;
                    ball->upper_left_x = ox + zoneW/2;
                    ball->upper_left_y = oy + zoneH/2;
                    ball->speed_y = -1;    // serve upward
                    continue;
                }

                // obstacle bounce
                for (auto &p : obs)
                    if (bx == p.first && by == p.second)
                    {
                        ball->speed_x = -ball->speed_x;
                        ball->speed_y = -ball->speed_y;
                    }

                // wall bounce
                if (bx <= ox+1)                { ball->upper_left_x = ox+1;           ball->speed_x = -ball->speed_x; }
                if (bx >= ox+zoneW-1)          { ball->upper_left_x = ox+zoneW-1;     ball->speed_x = -ball->speed_x; }
                if (by <= oy+1)                { ball->upper_left_y = oy+1;           ball->speed_y = -ball->speed_y; }
                if (by >= oy+zoneH-1)          { ball->upper_left_y = oy+zoneH-1;     ball->speed_y = -ball->speed_y; }

                // paddle collisions
                checkCollisionSlider(bot, ball);
                checkCollisionSlider(top, ball);
                checkCollisionWithZone(ball, zone);  // (kept for corner cases)
            }

            // draw arena
            attron(COLOR_PAIR(2)); draw_zone(zone); attroff(COLOR_PAIR(2));

            // draw dashed goal gates
            attron(COLOR_PAIR(1));
            for (int dx = 0; dx < goalW; ++dx)
            {
                mvaddch(oy,          goalX+dx, '-');
                mvaddch(oy+zoneH,    goalX+dx, '-');
            }
            attroff(COLOR_PAIR(1));

            drawObs(obs);
            attron(COLOR_PAIR(3)); draw_slider(top); draw_slider(bot); attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(4)); draw_ball(ball); attroff(COLOR_PAIR(4));

            attron(COLOR_PAIR(1));
            mvprintw(0,2,"T:%d  B:%d  R:%d/%d", ts, bs, std::min(ts+bs+1, rounds), rounds);
            attroff(COLOR_PAIR(1));
        }

        refresh();
        struct timespec tspec{0, delayNS}; nanosleep(&tspec, nullptr);
    }

    recordRounds(ts + bs);
    goodbye(ts, bs);
    endwin();
}

