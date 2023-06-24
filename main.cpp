#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#define TUILES 5

void dessiner_les_tuiles(int tour, int NoTuile, int y);
void dessiner_les_emplacements(int tour);
int tuile_vide(int NoTour);
int valider(int De, int A);
int deplacement(int De, int A);
void jouer();

using namespace std;
HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int tours[3][TUILES];
int tourSup[3]={TUILES-1, -1, -1};
int essaies=0;
int score=0;

void gotoxy(int x, int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size){
	if(size==0){
		size=20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible=visible;
	lpCursor.dwSize=size;
	SetConsoleCursorInfo(console, &lpCursor);
}

main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	char choix;
	do{
		system("cls");
		gotoxy(19, 10);printf("€ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ€");
		gotoxy(19, 11);printf("€                                                                                  €");
		gotoxy(19, 12);printf("€   ﬂﬂﬂ€ﬂﬂﬂ  €ﬂﬂﬂﬂﬂ€  €     €  €ﬂﬂﬂﬂ€      €     €  €ﬂﬂﬂﬂﬂ€  €‹    €  €ﬂﬂﬂﬂﬂ€  €   €");
		gotoxy(19, 13);printf("€      €     €     €  €     €  €    €      €     €  €     €  € €   €  €     €  €   €");
		gotoxy(19, 14);printf("€      €     €     €  €     €  €ﬂﬂﬂﬂﬂ€     €ﬂﬂﬂﬂﬂ€  €ﬂﬂﬂﬂﬂ€  €  €  €  €     €  €   €");
		gotoxy(19, 15);printf("€      €     €     €  €     €  €     €     €     €  €     €  €   € €  €     €  €   €");
		gotoxy(19, 16);printf("€      ﬂ     ﬂﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂﬂ  ﬂ     ﬂ     ﬂ     ﬂ  ﬂ     ﬂ  ﬂ    ﬂﬂ  ﬂﬂﬂﬂﬂﬂﬂ  ﬂ   €");
		gotoxy(19, 17);printf("€                                                                                  €");
		gotoxy(19, 18);printf("ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ");
		gotoxy(43, 20);printf("1.- COMMENCER\t\t 2.- QUITTER");
		gotoxy(37, 22);printf("- Copyright HAITI DEVELOPPEURS - Tous droit reserv%cs -",130);
		choix=getche();
		switch(choix){
			case '1':{
				jouer();
				break;
			}
			case '2':{
				system("cls");
				gotoxy(50, 20);printf("\t\tA LA PROCHAINE");
				getch();
				exit(0);
				break;
			}
		}
	}while(1);
	return 0;
}

//methode permet de dessiner les tuiles
void dessiner_les_tuiles(int tour, int NoTuile, int y){
	int x;
	if (tour==1)
		x=35;
	else if(tour==2)
		x=61;
	else if(tour==3)
		x=87;

	x-=NoTuile*2;

	//largeur des tuiles
	for(int j=0;j<((NoTuile)*4)-1;j++){
		gotoxy(x, y);
		printf("±");
		x++;
	}
}

void dessiner_les_emplacements(int tour){
	int x, y=19;
	//premier Tuile
	for(int i=13; i<=20;i++){
		gotoxy(34, i);printf("€");
	}
	gotoxy(24, 20);printf("ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ");
	gotoxy(34, 21);printf("1");

	//deuxieme Tuile
	for(int i=13; i<=20;i++){
		gotoxy(60, i);printf("€");
	}
	gotoxy(50, 20);printf("ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ");
	gotoxy(60, 21);printf("2");

	//troisieme Tuile
	for(int i=13; i<=20;i++){
		gotoxy(86, i);printf("€");
	}
	gotoxy(76, 20);printf("ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ");
	gotoxy(86, 21);printf("3");

	for(int i=0; i<5; i++){
		dessiner_les_tuiles(tour, tours[tour-1][i], y);
		y--;
	}
}

int tuile_vide(int NoTour){
	for(int i=0; i<TUILES; i++){
		if(tours[NoTour][i]!=0)
			return 0;
	}
	return 1;
}

int valider(int De, int A){
	if(!tuile_vide(A)){
		if(tours[De][tourSup[De]] < tours[A][tourSup[A]])
			return 1;
		else
			return 0;
	}
	return 1;
}

int deplacement(int De, int A){
	if(tuile_vide(De))
		return 0;
	if(valider(De, A)){
		if(tours[De][tourSup[De]] != 0){
			tourSup[A]++;
			tours[A][tourSup[A]] = tours[De][tourSup[De]];
			tours[De][tourSup[De]] = 0;
			tourSup[De]--;
			return 1;
		}
	}
	return 0;
}

void jouer(){
	int De, A;
	for(int i=0; i<TUILES; i++){
		tours[0][i]=TUILES-i;
	}
	for(int i=0; i<TUILES; i++){
		tours[1][i]=0;
	}
	for(int i=0; i<11; i++){
		tours[2][i]=0;
	}
	do{
		system("cls");
		gotoxy(53, 2);printf(" H D   G A M E");
		gotoxy(23, 4);printf("€€€€€€€€€€€€€€€€€€€€€€");
		gotoxy(43, 4);printf("     T O U R    D ' H A N O I  ");
		gotoxy(76, 4);printf("€€€€€€€€€€€€€€€€€€€€€€");
		 	dessiner_les_emplacements(1);
		 	dessiner_les_emplacements(2);
		 	dessiner_les_emplacements(3);
		 	gotoxy(40, 25);
			 printf("Pour d%cplacer une tuile vers une autre tuile:",130);
			 gotoxy(34, 26);printf("--vous devez appuyer sur le num%cro o%c la tuile se trouve.",130,151);
			 gotoxy(30, 27);printf("--apr%cs, appuyer au num%cro auquel vous voulez que la tuile aille",138,130);
			 gotoxy(24, 23);
			 printf("D%cplacer tuile (1, 2, 3): ",130);
			 scanf("%d",&De);
			 gotoxy(74, 23);
			 printf("Vers tuile (1, 2, 3): ");
			 scanf("%d",&A);
			 	if(A<1 || A>3)
			 		continue;
			 	if(De<1 || De>3)
			 		continue;
			 	if(De==A)
			 		continue;
			 		De--;
			 		A--;
			 	deplacement(De, A);
			 	if(kbhit()){
			 		char ch=getch();
			 		if(ch=='a' || ch=='A'){
					 }
					if(ch=='d' || ch=='D'){
					 }
					if(ch==27){
					 	break;
					 }
				 }
	}while(1);
}



