#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void showscreen (int screen, int width, int height, int length, int* snake, int food) {
	system("cls") ;
	if (screen == 0) {printf("//////////////////////////////////\n//                              //\n//  #### ##  #  ##  #   # ##### //\n// #     # # # #  # #  #  #     //\n//  ###  # # # #### ###   ####  //\n//     # # # # #  # #  #  #     //\n// ####  #  ## #  # #   # ##### //\n//                              //\n//                              //\n//         PRESS RETURN         //\n//                              //\n//////////////////////////////////") ;}
	else  {
		char text[] = "//////////////////////////////////\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//////////////////////////////////" ;
		
		text[snake[0]] = 64 ;
		
		text[width / 2 - 6] = 76 ;
		text[width / 2 - 5] = 69 ;
		text[width / 2 - 4] = 78 ;
		text[width / 2 - 3] = 71 ;
		text[width / 2 - 2] = 84 ;
		text[width / 2 - 1] = 72 ;
		text[width / 2] = 32 ;
		text[width / 2 + 1] = 58 ;
		text[width / 2 + 2] = 32 ;
		int l = length ;
		int d = 100 ;
		for (int i = 0 ; i < 3 ; i++) {
			char c[2] ;
			sprintf(c, "%d", l/d) ;
			text[width / 2 + 3 + i] = c[0] ;
			l -= l/d*d ;
			d /= 10 ;
		}
		
		for (int i = 1 ; i < length ; i++) {text[snake[i]] = 35 ;}
		
		if (food != 0) {text[food] = 43 ;}
		
		if (screen == 2) {
			text[width * (height / 2 - 1) + width / 2 - 3] = 80 ;
			text[width * (height / 2 - 1) + width / 2 - 2] = 65 ;
			text[width * (height / 2 - 1) + width / 2 - 1] = 85 ;
			text[width * (height / 2 - 1) + width / 2] = 83 ;
			text[width * (height / 2 - 1) + width / 2 + 1] = 69 ;
		} else if (screen == 3) {
			text[width * (height / 2 - 1) + width / 2 - 4] = 89 ;
			text[width * (height / 2 - 1) + width / 2 - 3] = 79 ;
			text[width * (height / 2 - 1) + width / 2 - 2] = 85 ;
			text[width * (height / 2 - 1) + width / 2 - 1] = 32 ;
			text[width * (height / 2 - 1) + width / 2] = 87 ;
			text[width * (height / 2 - 1) + width / 2 + 1] = 73 ;
			text[width * (height / 2 - 1) + width / 2 + 2] = 78 ;
		} else if (screen == 4) {
			text[width * (height / 2 - 1) + width / 2 - 5] = 71 ;
			text[width * (height / 2 - 1) + width / 2 - 4] = 65 ;
			text[width * (height / 2 - 1) + width / 2 - 3] = 77 ;
			text[width * (height / 2 - 1) + width / 2 - 2] = 69 ;
			text[width * (height / 2 - 1) + width / 2 - 1] = 32 ;
			text[width * (height / 2 - 1) + width / 2] = 79 ;
			text[width * (height / 2 - 1) + width / 2 + 1] = 86 ;
			text[width * (height / 2 - 1) + width / 2 + 2] = 69 ;
			text[width * (height / 2 - 1) + width / 2 + 3] = 82 ;
		}
		printf("%s", text) ;
	}
}

int setfood(int width, int height, int length, int* snake) {
	srand(time(NULL)) ;
	int x ;
	int y ;
	int b2 = 1 ;
	while (b2) {
		x = rand() % (width - 5) ;
		y = rand() % (height - 3) ;
		int ok = 1 ;
		for (int i = 0 ; i < length ; i++) {
			if (snake[i] == width * (y + 1) + x + 2) {
				ok = 0 ;
				break ;
			}
		}
		if (ok == 1) {break ;}
	}
	return width * (y + 1) + x + 2 ;
}

int main () {
	system("MODE CON: cols=34 lines=12") ;
	system("title SNAKE") ;
	
	int width = 35 ;
	int height = 12 ;
	int length = 1 ;
	int snake[(width - 4) * (height - 2) + 1] ;
	for (int i = 0 ; i < (width - 4) * (height - 2) + 1 ; i++) {snake[i] = 0 ;}
	int orientation = 3 ;
	int food = 0 ;
	int screen = 0 ;
	int frame = 0 ;
	
	showscreen(screen, width, height, length, snake, food) ;
	
	int b = 1 ;
	while (b) {
		if (kbhit()) {
			int key = getch() ;
			if (key == 13) {
				if (screen == 0) {
					screen = 1 ;
					length = 2 ;
					snake[0] = width * (height / 2 - 1) + width / 2 - 1 ;
					snake[1] = width * (height / 2 - 1) + width / 2 ;
					orientation = 4 ;
					frame = 0 ;
					food = setfood(width, height, length, snake) ;
				}
				else if (screen == 1) {screen = 2 ;}
				else if (screen == 2) {screen = 1 ;}
				else {screen = 0 ;}
				showscreen(screen, width, height, length, snake, food) ;
			}
			else if (screen == 1) {
				if (key == 72 && orientation != 3) {orientation = 1 ;}
				else if (key == 80 && orientation != 1) {orientation = 3 ;}
				else if (key == 75 && orientation != 2) {orientation = 4 ;}
				else if (key == 77 && orientation != 4) {orientation = 2 ;}
			}
		}
		
		if (screen == 1 && frame >= 10) {
			frame = 0 ;
			for (int i = 0 ; i < length ; i++) {snake[length - i] = snake[length - i - 1] ;}
			if (orientation == 1) {snake[0] -= width ;}
			else if (orientation == 2) {snake[0] += 1 ;}
			else if (orientation == 3) {snake[0] += width ;}
			else if (orientation == 4) {snake[0] -= 1 ;}
			char text[] = "//////////////////////////////////\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//                              //\n//////////////////////////////////" ;
			if (snake[0] == food) {
				length += 1 ;
				food = setfood(width, height, length, snake) ;
			}
			else {snake[length] = 0 ;}
			if (length == (width - 4) * (height - 2)) {screen = 3 ;}
			else if (text[snake[0]] == 47) {screen = 4 ;}
			else {
				for (int i = 1 ; i < length ; i++) {
					if (snake[i] == snake[0]) {
						screen = 4 ;
						break ;
					}
				}
			}
			showscreen(screen, width, height, length, snake, food) ;
		}
		Sleep(1) ;
		frame += 1 ;
	}
}