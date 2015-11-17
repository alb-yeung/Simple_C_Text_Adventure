#include <stdio.h>
#include <stdlib.h>

int state; 
int food;
int mail;

char *locations[] = {
	"You're in your backyard. Your house is to the east.\n",
	"You're in your house. Nice and cozy. Your backyard is to the west, your roof is to the north and the main road is to the south.\n",
	"You're on the roof of your house. Your house is to the south.\n",
	"You're at your friend's house. The main road is to the west.\n",
	"You're at the main road. Your house is to the north, your friend's house is to the west and food is to the east.\n",
	"You're at Chipotle and you get food. The main road is to the west.\n",
	"You're at the post office. You get your mail. You should probably open it at home. The main road is to the north and the is to the south.\n",
	"Hi you're at state 7. This is a placeholder. Go north to get back to the post office.\n"
};

int nextstate[] = {
	//north,east,south,west,openmail
	//From backyard
	0,1,0,0,0,
	//From home
	2,1,4,0,1,
	//From roof
	2,2,1,2,2,
	//From friend's house
	3,4,3,3,3,
	//From main road
	1,5,6,3,4,
	//From food
	5,5,5,4,5,
	//From post office
	4,6,7,6,6,
	//From state 7
	6,7,7,7,7
};

char actions[] = "neswo";

int get_action(){
	char input[1000];
	while(1){
		printf(">>");
		scanf("%s", input);
		int i;
		for (i = 0; actions[i] != '\0'; ++i){
            if (input[0] == actions[i]){
             	return i;
             }
	     }
		printf("I didn't quite understand that command. Use north, east, south, west, or openmail.\n");
	}
	return 0;
}

int main(){
	state = 1;
	food = 0;
	mail = 0;

	int action;

	printf("\n\nWelcome to Get Your Mail Simulator 2015!\n");
	printf("Use north, east, south, west, or openmail to get around.\n\n\n");
	printf("The mail came in today.\n");

	while(1){
		//Print location of where we are
		printf("%s",locations[state]);

		if (state == 5){
			food = 1;
		}
		if (state == 6){
			mail = 1;
		}

		action = get_action();

		//win condition
		if (state == 1 && mail == 1 && action == 4){
			printf("You open your mail at home. You win.\n");
			exit(0);
		}
		//try to access win condition 
		if (action == 4){
			if (mail == 0){
				printf("You don't even have your mail!\n");
			}else{
				printf("Wait until you're home to open it!\n");
			}
		}
		//try to get to post office without food
		if (state == 4 && action == 2 && food == 0){
			printf("You feel hungry and it's a long walk to the post office.\n");
			printf("You should get food first.\n");
			action = 4;
		}

		state = nextstate[5*state + action];
	}

}







