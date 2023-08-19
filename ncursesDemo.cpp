#include <ncurses.h>

using namespace std;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *localwin);

int main(void)
{

WINDOW *menu;
int height = 0, width = 0, starty = 0, startx = 0;
int ch = 0;

initscr();
noecho();

keypad(stdscr,TRUE);

printw("Press F1 to exit program");

height = 3;
width =  10;
starty = (LINES - height)/2;
startx = (COLS - width)/2;

refresh();

menu = create_newwin(height, width, starty, startx);

while((ch = getch()) != KEY_F(1))
{
  switch(ch)
 {
  case KEY_UP:
  destroy_win(menu);
  menu = create_newwin(height, width, --starty, startx);
  break;

  case KEY_DOWN:
  destroy_win(menu);
  menu = create_newwin(height, width, ++starty, startx);
  break;

  case KEY_LEFT:
  destroy_win(menu);
  menu = create_newwin(height, width, starty, --startx);
  break;

  case KEY_RIGHT:
  destroy_win(menu);
  menu = create_newwin(height, width, starty, ++startx);
  break;
 }
}

endwin();
return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *localwin = newwin(height, width, starty, startx);
  box(localwin,0,0);
  wrefresh(localwin);
  return localwin; 
}

void destroy_win(WINDOW *localwin)
{
  wborder(localwin,' ',' ',' ',' ',' ',' ',' ',' ');
  wrefresh(localwin);
  delwin(localwin);
}
