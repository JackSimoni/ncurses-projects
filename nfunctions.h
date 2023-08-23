#include <ncurses.h>

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

void wprint2DArray(WINDOW *localwin, int height, int width, int starty, int startx, char character)
{

 for(int i = starty; i <= height; i++)
         for(int j = startx; j <= width; j++)
                 mvwaddch(localwin, i, j, character);
}
