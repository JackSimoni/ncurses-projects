#include <ncurses.h>

using namespace std;

// Use functions

WINDOW * create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW * localwin);

int main(void) {

WINDOW * menu;
int height = 0, width = 0, startx = 0, starty = 0;
int ch = 0;


initscr();

cbreak();
noecho();
keypad(stdscr, TRUE);

height = 3, width = 10;
starty = (LINES - height)/2;
startx = (COLS - width)/2;
printw("Press F1 to exit");
refresh();
menu = create_newwin(height, width, starty, startx);

while((ch = getch()) != KEY_F(1))
{
  switch(ch)
  {
	case KEY_LEFT:
	destroy_win(menu);
	menu = create_newwin(height,width,starty,--startx);
	break;

	case KEY_RIGHT:
	destroy_win(menu);
	menu = create_newwin(height,width,starty,++startx);
	break;

	case KEY_UP:
	destroy_win(menu);
	menu = create_newwin(height,width,--starty,startx);
	break;

	case KEY_DOWN:
	destroy_win(menu);
	menu = create_newwin(height,width,++starty,startx);
	break;
  }

}

endwin();

return 0;

}

WINDOW * create_newwin(int height, int width, int starty, int startx)
{
  WINDOW * localwin;
  localwin = newwin(height, width, starty, startx);
  box(localwin,0,0); // 0,0 is default box visuals
  wrefresh(localwin); // Update window to show box. W/O this command, only in memory
  return localwin;
}

void destroy_win(WINDOW * localwin)
{
  wborder(localwin,' ',' ',' ',' ',' ',' ',' ',' ');
  wrefresh(localwin);
  delwin(localwin);
}
