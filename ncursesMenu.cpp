#include <iostream>
#include <string>
#include <ncurses.h>
#include "nfunctions.h"

using namespace std;

int main()
{

WINDOW * menu;
int height, width, starty, startx;
char selectKey;
char scrollKey;

initscr();
noecho();
cbreak();
keypad(stdscr, TRUE);

height = 10;
width = COLS - 60;
starty = LINES - 10;
startx = 30;

refresh();

menu = create_newwin(height, width, starty, startx);

keypad(menu,TRUE);
curs_set(0);

const string choices[3] = {"Option One", "Option Two", "Option Three"};
int choice;
int highlight = 0;

while(1)
{

  for(int i = 0; i < 3; i++)
  {
    if(i == highlight)
     wattron(menu,A_REVERSE);
    mvwprintw(menu, i+1, 1,"%s", choices[i].c_str());
    wattroff(menu, A_REVERSE);
  }

  choice = wgetch(menu);

  switch(choice)
{
  case KEY_UP:
  highlight--;
  if(highlight == -1)
  highlight = 0;
  break;

  case KEY_DOWN:
  highlight++;
  if(highlight == 3)
  highlight = 2;
  break;

  default:
  break;
}

if(choice == 10)
break;
}

printw("Your choice was %s", choices[highlight].c_str());
getch();
endwin();

return 0;
}
