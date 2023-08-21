#include <iostream>
#include <string>
#include <ncurses.h>
#include "nfunctions.h"

using namespace std;

// Create a window that asks for two choices. One is to access a moving window that has a message stamped on it. The other is to just exit the program.

int main()
{

initscr(); // start ncurses mode

cbreak(); // Allows CTRL + C as a command that allows to exit programs
noecho(); // Key presses are no longer recorded to the terminal
curs_set(0); // Makes cursor invisible
keypad(stdscr,TRUE); // Allows larger variety of key presses to the standard/default ncurses window. May call this multiple times, as new windows are created.

WINDOW * menu;
WINDOW * movingWin;
WINDOW * trapdoor;
WINDOW * question;

int height, width, starty, startx;

starty = LINES - 10;
startx =  75;
width = COLS - 150;
height = 10;

refresh();

menu = create_newwin(height, width, starty, startx);

keypad(menu, TRUE);

string choices[2] = {"1. Deploy Character", "2. Exit Program"};

int choice;
int highlight = 0;

while(1)
{

	for(int i = 0; i < 2; i++)
	{
	  if(i == highlight)
	  wattron(menu, A_STANDOUT);

	  mvwprintw(menu, i + 1, 1, "%s", choices[i].c_str());
	  wattroff(menu, A_STANDOUT);
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
	  if(highlight == 2)
	  highlight = 1;
	  break;

	  default:
	  break;
	}

	if(choice == 10)
	break;

}

int movement;

height = 1;
width = 2;
starty = (LINES - height)/2;
startx = (COLS - width)/2;

int y;
int x;

refresh();

if(highlight == 0)
{

  int local_while1_answer;
  int local_while1_highL;
  wclear(menu);
  destroy_win(menu);

  refresh();

  movingWin = create_newwin(height, width, starty, startx);
  trapdoor = create_newwin(5, 10, LINES - 20, COLS - 20);

  keypad(movingWin, TRUE);

  while((movement = getch()) != KEY_F(1))
  {
	mvwprintw(trapdoor, 0, 0, "##########");
	mvwprintw(trapdoor, 1, 0, "##########");
	mvwprintw(trapdoor, 2, 0, "##########");
	mvwprintw(trapdoor, 3, 0, "##########");
	mvwprintw(trapdoor, 4, 0, "##########");
	wrefresh(trapdoor);
	wrefresh(movingWin);

	switch(movement)
	{
	  case KEY_UP:
	  destroy_win(movingWin);
	  movingWin = create_newwin(height, width, --starty, startx);
	  break;

	  case KEY_DOWN:
	  destroy_win(movingWin);
	  movingWin = create_newwin(height, width, ++starty, startx);
	  break;

	  case KEY_RIGHT:
	  destroy_win(movingWin);
	  movingWin = create_newwin(height, width, starty, ++startx);
	  break;

	  case KEY_LEFT:
	  destroy_win(movingWin);
	  movingWin = create_newwin(height, width, starty, --startx);
	  break;

	  default:
	  break;

	}

	if(movement == 10 && starty >= LINES - 20 && starty <= LINES - 20 + 5 && startx >= COLS - 20 && startx <= COLS - 20 + 10)
	{

	  refresh();
	  question = create_newwin(10, COLS - 150, LINES - 10, 75);
	  keypad(question, TRUE);
	  string questions[2] = {"1. Go through the trapdoor.", "2. Not yet."};
	  int answer;
	  int highL = 0;
	 
	  while(1)
	  {
		for(int i = 0; i < 2; i++)
		{
		  if(i == highL)
		  wattron(question, A_STANDOUT);

		  mvwprintw(question, i + 1, 1, "%s", questions[i].c_str());
		  wattroff(question, A_STANDOUT);
		}

		answer = wgetch(question);

		switch(answer)
	       {
		case KEY_UP:
		highL--;
		if(highL == -1)
		highL = 0;
		break;

		case KEY_DOWN:
		highL++;
		if(highL == 2);
		highL = 1;
		break;

		default:
		break;
	       }

		local_while1_answer = answer;
		local_while1_highL = highL;
 
		if(answer == 10 && highL == 1)
		{
		 wclear(question);
		 destroy_win(question);
		 wrefresh(movingWin);
		 break;
		}
		
		else if(answer == 10 && highL == 0)
		{
		  wclear(movingWin);
		  wclear(trapdoor);
		  wclear(question);
		  destroy_win(movingWin);
		  destroy_win(trapdoor);
		  destroy_win(question);
		  break;
		}

		if(local_while1_answer == 10 && local_while1_highL == 0)
		break;
  	}

		if(local_while1_answer == 10 && local_while1_highL == 0)
		break;
	}

  }
}

if(highlight != 1)
{char message[44] = {'H','e','l','l','o',' ','S','e','v','e','r','i','a','n', ',' ,' ','w','e','l','c','o','m','e',' ','b','a','c','k',' ','t','o',' ','T','h','e',' ','C','i','t','a','d','e','l','.'};

for(int i = 0; i < 44; i++)
{
 addch(message[i]);
 napms(125);
 refresh();
}

getch();

}


endwin(); // end ncurses mode and dellocate memory

return 0; // return 0 if program has compiled correctly

}

