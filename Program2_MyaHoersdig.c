/*
Mya Hoersdig
EECS 348 Lab3 Problem 2
Given an integer representing a score in a National Football League (NFL) game, write a program 
to determine all possible combinations of scoring plays that can result in that score. 
 
A scoring plays in an NFL game can be the following: 
 
 Touchdown (TD) worth 6 points 
 Field goal (FG) worth 3 points 
 Safety worth 2 points 
 Touchdown (TD) + 2-point conversion worth 8 points 
 Touchdown (TD) + 1-point field goal worth 7 points 
 
The program should continue to prompt the user for a score until a value less than or equal to 
1 is entered, at which point the program should terminate. For each score entered, the program 
should display all possible combinations of scoring plays that result in that score.  
*/
#include <stdio.h>

void game_score(int score) {
    int td, fg, safety, td_2pt, td_fg, plays = 0;

    for (td_2pt = 0; td_2pt <= score/8; td_2pt++) {
        for(td = 0; td <= (score - td_2pt*8)/6; td++) {
            for(td_fg = 0; td_fg <= (score - td_2pt*8 - td*6)/7; td_fg++) {
                for(fg = 0; fg <= (score - td_2pt*8 - td*6 - td_fg*7)/3; fg++) {
                    for(safety = 0; safety <= (score - td_2pt*8 - td*6 - td_fg*7 - fg*3)/2; safety++) {

                        if(td*6 + fg*3 + safety*2 + td_2pt*8 + td_fg*7 == score) {
                            plays++;
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td_2pt, td_fg, td, fg, safety);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int score;

    while(1) {
        printf("\nEnter 0 or 1 to STOP\nEnter the NFL score: ");
        scanf("%d", &score);

        if(score <= 1) {
            break;
        }
        printf("possible combinations of scoring plays:\n");
        game_score(score);
    }
}