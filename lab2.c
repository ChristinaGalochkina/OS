#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void *printFunc(void *arg){
    char ch;	
    while (!feof(arg)){

        fread(&ch, 1, 1, arg);
 	printw("%c", ch);
	napms(100); 
	refresh();
    }
    pthread_exit(NULL);
}

int main(){
	initscr();
	FILE * readFile = fopen("filename", "r");              
	if (!readFile){	
		printw("\nCan`t open file\n");
		endwin();
		return 0;
	}
	
	keypad(stdscr, true);
	noecho();
	pthread_t print;

	printw("c to start, s to pause, q to exit \n");
	
	bool check = false;
	while(!check){

		char input = getch();
		switch(input){
			case 'c':
				{
				pthread_create(&print, NULL, printFunc, readFile);
				break;
				}	
			case 's':
				{
				 printw("\nPause. c to start, s to pause, q to exit \n");
				 pthread_cancel(print);
				 break;
				}
			case 'q': 
				{
				pthread_cancel(print);
				check = true; 
				break;
				}
			default :
				{
				printw("\nwrong key. c to start, s to pause, q to exit \n");
				break;
				}
			
		}
		refresh();
	}
	
	close (readFile);
	endwin();
	return 0;
}


