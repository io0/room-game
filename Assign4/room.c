#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	char command[20];
	char cmana[10];
	char cgold[10];
	int mana;
	int gold;
	char arr[1000];
	int n=1+atoi(getenv("CONTENT_LENGTH"));
	int i=0;
	int j;
 
	fgets(arr,n, stdin); 
	//array will look like "command=____&inventory=_%2C_”

	//find the first “=”
	for(i=0; i<=n && arr[i] != '='; i++); 
	i++;
	j=0;

	//Next, copy the command into the command[], or scan until the “&”
	for(i; i<=n && arr[i] != '&'; i++){ 
		command[j] = arr[i];
		j++;
	}
	command[j] ='\0';//command will now equal the command sent

	//create mana and cmana
	for (i; i<n && arr[i] != '='; i++);//go through to the next “=”(where inventory start)
	i++;
	j=0;
	for(i; arr[i] != '%'; i++){
		cmana[j]= arr[i];
		j++;
	}
	cmana[j]='\0';
	mana=atoi(cmana);

	//create cgold and golc
	for(i;i<=n && arr[i] !='C'; i++);
	i++;
	j=0;
	for(i; arr[i] != '\0'; i++){
		cgold[j]= arr[i];
		j++;
	}
	cgold[j]=arr[i];
	j++;
	cgold[j]='\0';
	gold=atoi(cgold);
	
	//Processing
	//if Player has 0 mana, then they are dead, display "you are dead" screen and add all mana and gold to room's resources and mark as unoccupied
	if(mana==0){
		//Add mana and gold to room's resources, and mark as unoccupied

                //first we will get the resources of the room by reading the resources.csv file
                //then we will update them so that the gold and the mana is added to the hidden resources of the room
                //reading the file
                int manaOfRoom = 0;
                int goldOfRoom = 0;
                int statusOfRoom = 0;
         
                FILE *fPointer1;
                fPointer1 = fopen("./resources.csv", "r");
                fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
                fclose(fPointer1);

                //now we rewrite the resources.csv file with the appropriate changes
                //we add the mana of the player to the mana of the room
                //we add the gold of the room to the gold of the player
                //if the is dead, then room is now not occupied
                FILE *fPointer2;
                fPointer2 = fopen("./resources.csv", "w");
                fprintf(fPointer2,"%d,%d,%d" , manaOfRoom+mana, goldOfRoom+gold , 0);
                fclose(fPointer2);


		//write a webpage
	        printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	        printf("<html>");
		printf("<br><br><br>");
	        printf("<body style=background-color:powderblue;>");
		 printf("<h1><center><big><b>You fought bravely... till the very end</b> </big></center></h1>");
		printf("<center> <h2> You were brave and strong. Unfortuately, that isn't always enough in this world.<br> You perished, trying to accomplish a feat that few dare to try. <br>Your sacrifice and life will always be remembered... </h2></center>");
		printf("</body><html>");
	}

	//if Player has 100 gold, then they win. Display "you win" page
	else if (gold == 100){
		 //write a webpage
	        printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	        printf("<html>");
		printf("<br><br><br>");
	        printf("<body style=background-color:powderblue;>");
		printf("<h1><center><big><b>Congratulations!</b> </big></center></h1>");
		printf("<center><h2> You are victorious! You have won the day and all mankind stands in awe of your accomplishments! <br>You have perservered through countless challenges, but you have emmerged triumphant! Well done! <br>Your deeds will be told for many years to come!</center> </h2>");
		printf("</body></html>");
	}

	//Else, command processing
	//EXIT marks room as unoccupied, adds all gold and mana to room's resources, and displays "sorry to see you leave" page
	else if( strcmp(command,"EXIT")==0 || strcmp(command,"exit")==0 ){
		//marks room as empty, adds all gold and mana to room's resources
                
                //first we will get the resources of the room by reading the resources.csv file
                //then we will update them so that the gold and the mana is added to the hidden resources of the room
                //reading the file
                int manaOfRoom = 0;
                int goldOfRoom = 0;
                int statusOfRoom = 0;
         
                FILE *fPointer1;
                fPointer1 = fopen("./resources.csv", "r");
                fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
                fclose(fPointer1);

                //now we rewrite the resources.csv file with the appropriate changes
                //we add the mana of the player to the mana of the room
                //we add the gold of the room to the gold of the player
                //if the player typed EXIT, then room is now not occupied  
                FILE *fPointer2;
                fPointer2 = fopen("./resources.csv", "w");
                fprintf(fPointer2,"%d,%d,%d" , manaOfRoom+mana, goldOfRoom+gold , 0);
                fclose(fPointer2);


		//Displays "Sorry to see you go" page
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
                printf("<html>");
                printf("<br><br><br>");
                printf("<body style=background-color:powderblue;>");
                printf("<h1><center><big><b>We're sorry to see you go D: <b> </big></center></h1>");
                printf("<center><h2> Alas, all good things must come to and end. <br> You must go, and we understand. If you ever decide to return, we will be here. <br> Till then, be happy and safe and may the winds of fate always favour you!</center> </h2>");
                printf("</body></html>");
	}
	
	//DROP n, drop n gold. For each gold dropped, get 1 mana. Make sure that amount of gold dropped doesn't exceed amount of gold that they have
	else if( strncmp(command,"drop+",5)==0 || strncmp(command,"DROP+",5)==0){
                printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<html>");
		printf("<head><center>");
                printf("<big><b>Welcome!</b> </big></center></head>");

                printf("<body style=background-color:powderblue;>");

                printf("<br>   <center><img src=https://oceandrive.com/get/files/image/migration/2387_content_locker-room.jpg>   </center>");

                printf("<br>    <center><form action=transporter.py method=post> <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL>  <input type=submit value=North> </form></ceinter>", mana, gold);

                printf(" <center> <form action=transporter.py method=post style=display:inline; > <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL> <input type=submit value=West> </form>", mana, gold);

                printf("<form action=../cgi-bin/room.cgi method=post style=display:inline;>  <input type=text name=command > <input type=hidden name=inventory value=%d,%d> <input type=submit>  </form>", mana, gold);

                 printf("<form action=transporter.py method=post style=display:inline;> <input type=hidden name=inventory value=%d,%d> <input type=hidden name=URL value=URL> <input type=submit value=East> </form> </center>",mana, gold);

                 printf("<br> <center><form action=transporter.py method=post>  <input type=hidden name=inventory value=%d,%d>  <input type=hidden name=URL value=URL>  <input type=submit value=South> </form></center>", mana, gold);

		int count=0;
		char dchar[15];
		n=strlen(command);
		int drop;
		for (count; count<n && command[count] != '+'; count++);//till “+”
  		count++;
       		j=0;
        	for(count; count<n; count++){
                	dchar[j]= command[count];
                	j++;
        	}
        	dchar[j]='\0';
        	drop=atoi(dchar);
		if(drop > gold){//print out "You don't have that much gold!
		 	printf("<p><center> You don't have %d gold, I'm afraid. You only have %d gold. You cannot drop more gold than you have. </p></center>",drop, gold);
		        printf("<p><center> You have %d gold and %d mana</p></center>",gold, mana);
		        printf("</body></html>");
		}
		else{
			int d= drop/2;
			gold = gold-drop;
			mana= mana+d;
		
			printf("<p> You dropped %d gold and gained %d mana", drop, d);
		        printf("<p><center> You have %d gold and %d mana</p></center>",gold, mana);
		        printf("</body></html>");

                        //first we will get the resources of the room by reading the resources.csv file
                        //then we will update them so that the gold is added to the hidden resources of the room
                        //reading the file
                        int manaOfRoom = 0;
                        int goldOfRoom = 0;
                        int statusOfRoom = 0;
           
                        FILE *fPointer1;
                        fPointer1 = fopen("./resources.csv", "r");
                        fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
                        fclose(fPointer1);

                        //now we rewrite the resources.csv file with the appropriate changes
                        //if the player just dropped gold, the room remains occupied  
                        FILE *fPointer2;
                        fPointer2 = fopen("./resources.csv", "w");
                        fprintf(fPointer2,"%d,%d,%d" , manaOfRoom, goldOfRoom+drop , 1);
                        fclose(fPointer2);
		}

	}

	//PLAY activates the game
	else if( strcmp(command,"PLAY")==0 || strcmp(command,"play")==0){
		 printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
                printf("<html>");
                printf("<br><br><br>");
                printf("<body style=background-color:powderblue;>");
                 printf("<h1><center><big><b>Are you sure you want to play the game?</b> </big></center></h1>");
		printf("<center><form action=play.cgi method=post style=display:inline;> <input type=hidden name=inventory value=%d,%d> <input type=submit value=Yes></form>", mana, gold);
		printf ("<form action=../cgi-bin/room.cgi method=post style=display:inline;> <input type=hidden name=command value=refresh> <input type=hidden name=inventory value=%d,%d>  <input type=submit value=No></form>", mana, gold);
		printf("</center></body></html>");

	}		

	//REFRESH redraws room with player inventory updated.  
	else if ( strcmp(command,"REFRESH")==0 || strcmp(command,"refresh")==0){
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<html>");
		printf("<head><center>");
		printf("<big><b>Welcome!</b> </big></center></head>");

		printf("<body style=background-color:powderblue;>");

		printf("<br>   <center><img src=https://oceandrive.com/get/files/image/migration/2387_content_locker-room.jpg>   </center>");

	        printf("<br>    <center><form action=hello.py method=post> <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL>  <input type=submit value=North> </form></ceinter>", mana, gold);

	        printf(" <center> <form action=transporter.py method=post style=display:inline; > <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL> <input type=submit value=West> </form>", mana, gold);

	        printf("<form action=../cgi-bin/room.cgi method=post style=display:inline;>  <input type=text name=command > <input type=hidden name=inventory value=%d,%d> <input type=submit>  </form>", mana, gold);

	        printf("<form action=http://cs.mcgill.ca/~cfang5/cgi-bin/transporter.py method=post style=display:inline;> <input type=hidden name=inventory value=%d,%d> <input type=hidden name=URL value=http://www.cs.mcgill.ca/~mxiong4/cgi-bin/room.cgi> <input type=submit value=East> </form> </center>",mana, gold);

	        printf("<br> <center><form action=transporter.py method=post>  <input type=hidden name=inventory value=%d,%d>  <input type=hidden name=URL value=URL>  <input type=submit value=South> </form></center>", mana, gold);

	        printf("<p><center> You have %d gold and %d mana</p></center>",gold, mana);
	        printf("</body></html>");

                //first we will get the resources of the room by reading the resources.csv file
                //then we will update them so that the status of the room is set to occupied
                //reading the file
                int manaOfRoom = 0;
                int goldOfRoom = 0;
                int statusOfRoom = 0;
         
                FILE *fPointer1;
                fPointer1 = fopen("./resources.csv", "r");
                fscanf(fPointer1,"%d,%d,%d", &manaOfRoom, &goldOfRoom, &statusOfRoom);
                fclose(fPointer1);

                //now we rewrite the resources.csv file with the appropriate changes
                //the status of the room will be set to occupied
                FILE *fPointer2;
                fPointer2 = fopen("./resources.csv", "w");
                fprintf(fPointer2,"%d,%d,%d" , manaOfRoom, goldOfRoom , 1);
                fclose(fPointer2);
	
	}
	else{
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	        printf("<html>");
	        printf("<head><center>");
	        printf("<big><b>Welcome!</b> </big></center></head>");

	        printf("<body style=background-color:powderblue;>");

	        printf("<br>   <center><img src=https://oceandrive.com/get/files/image/migration/2387_content_locker-room.jpg>   </center>");

	        printf("<br>    <center><form action=teleport.py> <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL>  <input type=submit value=North> </form></ceinter>", mana, gold);

	        printf(" <center> <form action=teleport.py style=display:inline; > <input type=hidden name=inventory value=%d,%d>   <input type=hidden name=URL value=URL> <input type=submit value=West> </form>", mana, gold);

	        printf("<form action=../cgi-bin/room.cgi method=post style=display:inline;>  <input type=text name=command > <input type=hidden name=inventory value=%d,%d> <input type=submit>  </form>", mana, gold);

	        printf("<form action=teleport.py style=display:inline;> <input type=hidden name=inventory value=%d,%d> <input type=hidden name=URL value=URL> <input type=submit value=East> </form> </center>",mana, gold);

	        printf("<br> <center><form action=teleport.py>  <input type=hidden name=inventory value=%d,%d>  <input type=hidden name=URL value=URL>  <input type=submit value=South> </form></center>", mana, gold);
	
		printf("<center> Sorry! You just said \"%s\", which is not a known command.<br> The possible commands are al follows: <br><p> drop n: \tYou lose n peices of gold. For every 2 peices of gold that you drop, you recieve 1 mana. <br> play: \t To play this room's game. You can exit the game at any time by using the command \"quit\". If you win, you will get gold and mana. <br> exit: \t This means that you exit the room and the game. All progress will be lost. <br> refresh: \t To save you inventory (or to see what you have in your inventory. Remember, you need to have 100 gold to win, if you have 0 mana you die, and traveling between rooms costs 1 mana).</p></center>", command);
		printf("<p><center> You have %d gold and %d mana</p></center>",gold, mana);
	        printf("</body></html>");	
	}
}
