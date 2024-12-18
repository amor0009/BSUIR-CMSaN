#include "about.h"

extern int ch;
extern screen_size scr_size;
extern bool exit_flag;
static WINDOW *box_win = NULL;

//Обработчик отрисовки окна "О программе"
static void render_about_window();

//Обработчик события изменения размера окна
static void on_about_resize_handler();

//Обработчик события выхода в основное окно
static void on_about_exit_handler();

//Порядок отрисовки окна "О программе"
static void about_refresher_handler();

/*Закрепление обработчиков за конкретными событиями(клавишами)*/
static const key_handler ABOUT_CONTROL_KEYS_HANDLERS[] = {
    {KEY_RESIZE, on_about_resize_handler},
    {KEY_F(3), on_about_exit_handler},
    {KEY_F(1),settings}
};

/*Констатный массив очереди отрисовки*/
static const render_routes ABOUT_RENDER_LIST[] = {
    render_key_map,
    render_about_window,
};

void about() {
    exit_flag = FALSE;
    refresh();
    about_refresher_handler();
    while ((ch = wgetch(box_win))) {
        default_key_handler(ABOUT_CONTROL_KEYS_HANDLERS, ARRAY_SIZE(ABOUT_CONTROL_KEYS_HANDLERS));
        if (exit_flag) {
            delwin(box_win);
            box_win = NULL;
            return;
        }
    }
}

static void on_about_exit_handler() {
    exit_flag = TRUE;
}

static void about_refresher_handler() {
    curs_set(0);
    getmaxyx(stdscr, scr_size.max_y, scr_size.max_x);
    for (size_t i = 0; i < ARRAY_SIZE(ABOUT_RENDER_LIST);i++) {
        ABOUT_RENDER_LIST[i]();
    }
}

static void on_about_resize_handler() {
    delwin(box_win);
    box_win = NULL;
    about_refresher_handler();
}

static void render_about_window() {
    WINDOW *description_win = newwin(scr_size.max_y - 5, 3 * scr_size.max_x / 4, 2, scr_size.max_x / 8);
    if (box_win == NULL)
        box_win = newwin(scr_size.max_y - 1, scr_size.max_x, 0, 0);
    keypad(box_win, TRUE);
    wbkgd(box_win, COLOR_PAIR(3));
    wbkgd(description_win, COLOR_PAIR(3));
    box(box_win, 0, 0);
    mvwprintw(description_win, 0, 15, PROGRAM_NAME);
    mvwaddstr(description_win, 2, 0, DESCRIPTION);
    mvwaddstr(description_win, 4, 15, DESCRIPTION1);
    mvwaddstr(description_win, 6, 0, DESCRIPTION2);
    mvwaddstr(description_win, 8, 0, DESCRIPTION3);
    mvwaddstr(description_win, 12, 15, DESCRIPTION4);
    mvwaddstr(description_win, 14, 0, DESCRIPTION5);
    mvwaddstr(description_win, 16, 0, DESCRIPTION6);
    mvwaddstr(description_win, 18, 0, DESCRIPTION7);
    mvwaddstr(description_win, 20, 0, DESCRIPTION8);
    mvwaddstr(description_win, 22, 0, DESCRIPTION9);
    mvwaddstr(description_win, 24, 0, DESCRIPTION10);
    mvwaddstr(description_win, 26, 0, DESCRIPTION11);
    mvwaddstr(description_win, 28, 0, DESCRIPTION12);
    mvwaddstr(description_win, 30, 0, DESCRIPTION13);
    wrefresh(box_win);
    wrefresh(description_win);

    delwin(description_win);

}