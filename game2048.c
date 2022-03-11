#include <stdio.h>
#include <windows.h>

#define size 4
#define winscore 2048

void printarray(int [][size]);
char move(int [][size],char);
void merge(int [][size],char);
int maxscore(int [][size]);

int main(){
	int board[size][size];
	int i,j;
	char state=1;
	char wheremove;
	int score=0 , countscore=0;
	
	//prepare a vacant board
	for( i=0 ; i<size ; i++ ){
		for( j=0 ; j<size ; j++ ){
			board[i][j] = 0;
		}
	}
	
	srand(time(NULL));
	//start the game
	while( state ){
		system("cls");
		
		//make new number in random place
		do{
			i = rand()%size ;
			j = rand()%size ;
		}while( board[i][j]!=0 );
		
		switch( rand()%5 ){
			case 4:
				board[i][j] = 4;
				break;
			default:
				board[i][j] = 2;
				break;
		}
		
		//shwo board
		printarray(board);
		
		//check max score
		score = maxscore(board);
		if( score==winscore ){
			countscore++;
			if( countscore==1 ){
				system("cls");
				system("color B4");
				puts("congratulations!");
				puts("   you win!");
				sleep(5);
				system("cls");
				system("color 0F");
				puts("do you want to continue?");
				puts("press <y> if yes and otherwise press <n>");
				char ch = getch();
				if( ch=='n' ){
					system("cls");
					system("color B4");
					puts("have good times :)");
					return 0;
				}else{
					system("cls");
					system("color B4");
					puts("be ready to continue...");
					sleep(5);
					system("color 0F");
				}
			}
		}
		
		do{
			//get input and update the board
			wheremove = getch();
			
			//update the board
			state = move(board,wheremove);
			merge(board,wheremove);
			if( state!=1 ){
				state = move(board,wheremove);
			}else{
				int temp = move(board,wheremove);
			}
			
			//if state==2 then show the update board
			if( state==2 ){
				system("cls");
				printarray(board);
			}
		}while( state==2 );
		
	}
	
	//fail the course
	system("cls");
	system("color B4");
	puts("game over!");
	printf("your score is %d.",score);
	sleep(5);
	
	
	return 0;
}

void printarray( int board[][size] ){
	int ii,jj, i=0,j=0;
	
	for( jj=0 ; jj<33 ; jj++ ){
		if( jj==0 ){
			putchar(201);
		}else if( jj==32 ){
			putchar(187);
		}else if( jj%8==0 ){
			putchar(203);
		}else{
			putchar(205);
		}
	}
	putchar('\n');
	for( ii=1 ; ii<16 ; ii++ ){
		for( jj=0 ; jj<9 ; jj++ ){
			if( ii%4==0 ){
				if( jj==0 ){
					putchar(204);
				}else if( jj==8 ){
					putchar(185);
				}else if( jj%2==0 ){
					putchar(206);
				}else{
					printf("%c%c%c%c%c%c%c",205,205,205,205,205,205,205);
				}
			}else if( ii%2==0 ){
				if( jj==0 || jj==8 || jj%2==0 ){
					putchar(186);
				}else{
					//print a member of the array
					if( board[i][j]==0 ){
						printf("       ");
					}else{
						printf("%7d",board[i][j]);
					}
					if( j==size-1 ){
						i++;
						j = 0;
					}else{
						j++;
					}
				}
			}else{
				if( jj==0 || jj==8 || jj%2==0 ){
					putchar(186);
				}else{
					printf("       ");
				}
			}
		}
		putchar('\n');
	}
	for( jj=0 ; jj<33 ; jj++ ){
		if( jj==0 ){
			putchar(200);
		}else if( jj==32 ){
			putchar(188);
		}else if( jj%8==0 ){
			putchar(202);
		}else{
			putchar(205);
		}
	}
}

char move( int board[][size] , char wheremove ){
	char canmove=0;
	int i,j, ii,jj;
	
	switch( wheremove ){
		case 'w':
			for( j=0 ; j<size ; j++ ){
				for( i=0 ; i<size-1 ; i++ ){
					if( board[i][j]!=0 ){
						continue;
					}
					for( ii=i+1 ; ii<size ; ii++ ){
						if( board[ii][j]!=0 ){
							board[i][j] = board[ii][j];
							board[ii][j] = 0;
							canmove = 1;
							break;
						}
					}
				}
			}
			break;
		case 'd':
			for( i=0 ; i<size ; i++ ){
				for( j=size-1 ; j>0 ; j-- ){
					if( board[i][j]!=0 ){
						continue;
					}
					for( jj=j-1 ; jj>=0 ; jj-- ){
						if( board[i][jj]!=0 ){
							board[i][j] = board[i][jj];
							board[i][jj] = 0;
							canmove = 1;
							break;
						}
					}
				}
			}
			break;
		case 's':
			for( j=0 ; j<size ; j++ ){
				for( i=size-1 ; i>0 ; i-- ){
					if( board[i][j]!=0 ){
						continue;
					}
					for( ii=i-1 ; ii>=0 ; ii-- ){
						if( board[ii][j]!=0 ){
							board[i][j] = board[ii][j];
							board[ii][j] = 0;
							canmove = 1;
							break;
						}
					}
				}
			}
			break;
		case 'a':
			for( i=0 ; i<size ; i++ ){
				for( j=0 ; j<size ; j++ ){
					if( board[i][j]!=0 ){
						continue;
					}
					for( jj=j+1 ; jj<size ; jj++ ){
						if( board[i][jj]!=0 ){
							board[i][j] = board[i][jj];
							board[i][jj] = 0;
							canmove = 1;
							break;
						}
					}
				}
			}
			break;
	}
	
	if( canmove==0 ){
		for( i=0 ; i<size ; i++ ){
			for( j=0 ; j<size ; j++ ){
				if( board[i][j]==0 ){
					canmove = 2;
					break;
				}
			}
		}
	}
	
	return canmove;
}

void merge( int board[][size] , char wheremove ){
	int i,j ;
	
	switch( wheremove ){
		case 'w':
			for( j=0 ; j<size ; j++ ){
				for( i=0 ; i<size-1 ; i++ ){
					if( board[i][j]==board[i+1][j] ){
						board[i][j] *= 2;
						board[i+1][j] = 0;
					}
				}
			}
			break;
		case 'd':
			for( i=0 ; i<size ; i++ ){
				for( j=size-1 ; j>0 ; j-- ){
					if( board[i][j]==board[i][j-1] ){
						board[i][j] *= 2;
						board[i][j-1] = 0;
					}
				}
			}
			break;
		case 's':
			for( j=0 ; j<size ; j++ ){
				for( i=size-1 ; i>0 ; i-- ){
					if( board[i][j]==board[i-1][j] ){
						board[i][j] *= 2;
						board[i-1][j] = 0;
					}
				}
			}
			break;
		case 'a':
			for( i=0 ; i<size ; i++ ){
				for( j=0 ; j<size-1 ; j++ ){
					if( board[i][j]==board[i][j+1] ){
						board[i][j] *= 2;
						board[i][j+1] = 0;
					}
				}
			}
			break;
	}
	
}

int maxscore( int board[][size] ){
	int i,j, max=0;
	
	for( i=0 ; i<size ; i++ ){
		for( j=0 ; j<size ; j++ ){
			if( board[i][j]>max ){
				max = board[i][j];
			}
		}
	}
	
	return max;
}
