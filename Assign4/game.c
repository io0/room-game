#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){

	char arr[1000];
	char command[20];
	char cmana[10];
	char ctmana[10];
	char cgold[10];
	char ctgold[10];
	int mana;
	int gold;
	int tmana;
	int tgold;
	int n = 1+atoi(getenv("CONTENT_LENGTH"));
	int i = 0;
	int j = 0;
	
	// Iterates to the first '='
	fgets(arr, n, stdin);
	for ( ; i<=n && arr[i]!= '='; i++);
	i++;
	
	// Handle win condition
	if (strncmp(arr, "takemana", 8) == 0){
		// Reads room inventory
		
		int manaOfRoom = 0;
	        int goldOfRoom = 0;
	        int statusOfRoom = 0;
	
	        FILE *fPointer1;
	        fPointer1 = fopen("./resources.csv", "r");
	        fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
	        fclose(fPointer1);		

		// Store value of takemana		
		for ( ; arr[i] != '&'; i++){
			ctmana[j] = arr[i];
			j++;
		}
		ctmana[j] = '\0';
		// Iterate until the next '='
		for ( ; i<n && arr[i] != '='; i++);
		i++;
		j=0;
		// Store value of takegold
		for ( ; i<=n && arr[i] !='&'; i++){
			ctgold[j] = arr[i];
			j++;
		}
		ctgold[j] = '\0';
		// Iterate until the next '='
		for ( ; i<n && arr[i] != '='; i++);
		i++;
		j=0;
		// Store value of player inventory
		for ( ; arr[i] != '%'; i++){
			cmana[j] = arr[i];
			j++;
		}
		cmana[j] = '\0';
		mana = atoi(cmana);
		
		for (; i<=n && arr[i] !='C'; i++);
		i++;
		j = 0;
		for ( ; arr[i] != '\0'; i++){
			cgold[j] = arr[i];
			j++;
		}
		cgold[j] = arr[i];
		j++;
		cgold[j] = '\0';
		gold = atoi(cgold);
		
		tmana = atoi(ctmana);
		tgold = atoi(ctgold);
		if (tmana + tgold <= 5 && tmana <= manaOfRoom && tgold <= goldOfRoom){
		// Edit room inventory			
			FILE *fPointer2;
                        fPointer2 = fopen("./resources.csv", "w");
                        fprintf(fPointer2,"%d,%d,%d" , manaOfRoom - tmana, goldOfRoom - tgold, 1);
                        fclose(fPointer2);

			printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	                printf("<html>");
	                printf("<br><br><br>");
	                printf("<body style=background-color:powderblue;>");
	                printf("<h1><center><big><b>You won %d mana and %d gold!</b> </big></center></h1>", tmana, tgold);
			printf("<center><form action=room.cgi method=post style=display:inline;> <input type=hidden name=command value=refresh><input type=hidden name=inventory value=%d,%d> <input type=submit value=Return></form>", mana + tmana, gold + tgold);
			printf("</center></body></html>");

		} else {
			printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
        	        printf("<html>");
        	        printf("<br><br><br>");
        	        printf("<body style=background-color:powderblue;>");
        	        printf("<h1><center><big><b>You won!</b> </big></center></h1>");
			printf("<center>The room currently has %d mana and %d gold </center>", manaOfRoom, goldOfRoom);
			printf("<center><br><p>Please enter a valid amount of mana and gold to proceed.</p></br>");
			printf("<form action=play.cgi method=post style=display:inline;> <p>How much mana would you like?</p><br><input type=text name=takemana></br><p>How much gold would you like?</p><input type=text name=takegold><input type=hidden name=inventory value=%d,%d> <br><input type=submit></form></br>", mana, gold);
			printf("</center></body></html>");		
		}
	} else {
	// Entry into game
	if (strncmp(arr, "inventory", 9) == 0){
		for ( ; arr[i] != '%'; i++){
			cmana[j] = arr[i];
			j++;
		}
		cmana[j] = '\0';
		mana = atoi(cmana);
		
		for (; i<=n && arr[i] !='C'; i++);
		i++;
		j = 0;
		for ( ; arr[i] != '\0'; i++){
			cgold[j] = arr[i];
			j++;
		}
		cgold[j] = arr[i];
		j++;
		cgold[j] = '\0';
		gold = atoi(cgold);
	// After winning		
	} else {
		for ( ; i<=n && arr[i] != '&'; i++){
			command[j] = arr[i];
			j++;
		}
		command[j] = '\0';
		for ( ; i<n && arr[i] != '='; i++);
		i++;
		j=0;
		for ( ; arr[i] != '%'; i++){
			cmana[j] = arr[i];
			j++;
		}
		cmana[j] = '\0';
		mana = atoi(cmana);
		
		for (; i<=n && arr[i] !='C'; i++);
		i++;
		j = 0;
		for ( ; arr[i] != '\0'; i++){
			cgold[j] = arr[i];
			j++;
		}
		cgold[j] = arr[i];
		j++;
		cgold[j] = '\0';
		gold = atoi(cgold);
	}

	if (strcmp(command,"QUIT") == 0 || strcmp(command,"quit") == 0){
		 printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
                printf("<html>");
                printf("<br><br><br>");
                printf("<body style=background-color:powderblue;>");
                 printf("<h1><center><big><b>Are you sure you want to quit the game?</b> </big></center></h1>");
                printf("<center><form action=../cgi-bin/room.cgi method=post style=display:inline;> <input type=hidden name=command value=refresh> <input type=hidden name=inventory value=%d,%d> <input type=submit value=Yes></form>", mana, gold);
                printf ("<form action=../cgi-bin/play.cgi method=post style=display:inline;> <input type=hidden name=inventory value=%d,%d>  <input type=submit value=No></form>", mana, gold);
                printf("</center></body></html>");


	} else if (atoi(command) == 4){
		// Reads room inventory
		int manaOfRoom = 0;
	        int goldOfRoom = 0;
	        int statusOfRoom = 0;
	
	        FILE *fPointer1;
	        fPointer1 = fopen("./resources.csv", "r");
	        fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
	        fclose(fPointer1);

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
                printf("<html>");
                printf("<br><br><br>");
                printf("<body style=background-color:powderblue;>");
                printf("<h1><center><big><b>You won!</b> </big></center></h1>");
		printf("<center>The room currently has %d mana and %d gold </center>", manaOfRoom, goldOfRoom);
		printf("<center><form action=play.cgi method=post style=display:inline;> <p>How much mana would you like?</p><br><input type=text name=takemana></br><p>How much gold would you like?</p><input type=text name=takegold><input type=hidden name=inventory value=%d,%d> <br><input type=submit></form></br>", mana, gold);
		printf("</center></body></html>");

	} else {
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<html><head><center><big><b>How many toenails does an elephant have?</b> </big></center></head>");
	printf("<body style=background-color:powderblue;><br><center><img src=https://c532f75abb9c1c021b8c-e46e473f8aadb72cf2a8ea564b4e6a76.ssl.cf5.rackcdn.com/2016/08/31/27ti5gwrzr_Julie_Larsen_Maher_3242_African_Elephant_UGA_06_30_10_hr.jpg width=\"45%%\" height=\"60%%\"></center>");
	if (strncmp(arr, "inventory", 9)) {
		if (atoi(command)){
		printf("<center><h2>Wrong! Please try again. </h2></h2></center>");
		} else {
		printf("<center><h2>Please enter a valid guess. </h2></center>");
		}
	} else {
	printf("<center><h2>Please enter your guess:</h2></center>");
	}
	printf("<br><center><form action=./play.cgi method=post style=display:inline;><input type=text name=command><input type=hidden name=inventory value=%d,%d>  <input type=\"submit\"></form></center><br></body></html>", mana, gold);
}
}
}
