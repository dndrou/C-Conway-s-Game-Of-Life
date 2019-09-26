#include <stdio.h>
#include <stdbool.h>

#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

int parseGens(char* str);
void clear(char (*matrix)[GRIDY][GRIDX], int current);
void printLife(char (*matrix)[GRIDY][GRIDX], int current);
/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */
int main(int argc, char *argv[])
{
    int counter=0;
    char* generationChar=argv[2];
    int generation=0;
    char matrix[2][GRIDY][GRIDX];
    char** secondMatrix;
    int current=0, future=1;
    int flag=0;
    //error catching
    if(argc !=3){
        printf("error wrong number of inputs");
        return -1;
    }

    //set all array slots to DEAD for a default intialization
    for(int yval=0;yval<GRIDY;yval++){
        for(int xval=0;xval<GRIDX;xval++){
            matrix[current][yval][xval] = DEAD;
            matrix[future][yval][xval] = DEAD;
        }
    }
    //read in rle file
    secondMatrix = parse_life(argv[1]);
    //if [x][y] in the rle equals live set to live in the main array being used
    for(int yvalue=0;yvalue<GRIDY;yvalue++){
        for(int xvalue=0;xvalue<GRIDX;xvalue++){
            if((int) secondMatrix[yvalue][xvalue] == (int) LIVE){
                matrix[current][yvalue][xvalue] = LIVE;
            }else{
                matrix[current][yvalue][xvalue] = DEAD;
            }    
        }
    }
    //parse the num of generations 
    generation = parseGens(generationChar);
    
    //uncomment to print out what the starting grid looks like and what generation was set to be
    // printf("%d",generation);
    //  printf("\nstarting gen \n \n");
    // printLife(matrix, current);
    
    //flag = 0 so flag < generation runs how ever many times generation was specified to be
    while(flag < generation){
        //for y and x 
        for(int celly=0;celly<GRIDY;celly++){
            for(int cellx=0;cellx<GRIDX;cellx++){
                //set cell counter to 0
                    counter = 0;
                    //if current index is not out of bounds, and is LIVE increment counter ect.
                    if(cellx-1 > -1 && (int) matrix[current][celly][cellx-1]== (int) LIVE){
                            counter++;
                    }
                    if(celly-1 > -1 && (int) matrix[current][celly-1][cellx]== (int) LIVE ){
                            counter++;
                    }
                    if(celly-1>-1 && cellx-1>-1 &&(int) matrix[current][celly-1][cellx-1]==(int) LIVE){
                            counter++;
                    }
                    if(celly+1<GRIDY && cellx+1<GRIDX &&(int) matrix[current][celly+1][cellx+1]==(int) LIVE){
                            counter++;
                    }
                    if( celly+1<GRIDY && (int) matrix[current][celly+1][cellx]==(int) LIVE){
                        counter++;
                    }
                    if(cellx+1 < GRIDX && (int) matrix[current][celly][cellx+1]== (int) LIVE){
                            counter++;
                    }
                    if((celly+1)<GRIDY && cellx-1>-1 && (int) matrix[current][celly+1][cellx-1]==(int) LIVE){
                            counter++;
                    }
                    if(celly-1>-1 && cellx+1 < GRIDX  &&(int) matrix[current][celly-1][cellx+1]==(int) LIVE){
                        counter++;
                    }
                    //if cell is Dead and counter == 3 then set to live
                    //else if cell is Live and counter is 2< or >3 set to dead
                    //else if cell is LIVE and counter == 2 || == 3 keep the cell alive
                    //else just set it to dead
                    // all changes made to "future" grid
                    if((int) matrix[current][celly][cellx] ==(int) DEAD && counter==3){
                    matrix[future][celly][cellx] = LIVE;
                    
                }
                    else  if((int) matrix[current][celly][cellx] == (int) LIVE && counter<2){
                    matrix[future][celly][cellx] = DEAD;
                }
                    else  if((int) matrix[current][celly][cellx] == (int) LIVE && counter>3){
                    matrix[future][celly][cellx] = DEAD;
                }
                    else if((int) matrix[current][celly][cellx] == (int) LIVE && (counter == 2 || counter == 3)){
                        matrix[future][celly][cellx] = LIVE;
                    }
                    else{
                        matrix[future][celly][cellx] = DEAD;
                    }
        }

    }
        //increment flag
         flag++;
         //swap future and current so future = current and current = future
         future = (future+1)%2;
         current = (current+1)%2;
         // printf("\n");
         // printLife(matrix, current);
         // printf("\n");

         //now that the old current is new future, set new future to be an empty grid
         for(int i = 0; i<GRIDY; i++){
             for(int j =0; j<GRIDX; j++){
                 matrix[future][i][j] = DEAD;
             }
         }
    }
           
        // printf("\nfinal gen\n");
    //after everything is done, print the final result
    printLife(matrix, current);
            
    return 0;
}


int parseGens(char *str){
    char placeVal;
    int numNums=0, countPlaces=0, placeValInt=0, placeMultiple=1, result=0, otherNum=0;
    
    for(numNums=0;str[numNums]!='\0';numNums++){
    }
    
    for(countPlaces=numNums; countPlaces>-1; countPlaces--){
        placeVal = str[countPlaces];
        
        if(placeVal == '0'){
            placeValInt = 0;
        }
        if(placeVal == '1'){
            placeValInt = 1;
        }
        if(placeVal == '2'){
            placeValInt = 2;
        }
        if(placeVal == '3'){
            placeValInt = 3;
        }
        if(placeVal == '4'){
            placeValInt = 4;
        }
        if(placeVal == '5'){
            placeValInt = 5;
        }
        if(placeVal == '6'){
            placeValInt = 6;
        }
        if(placeVal == '7'){
            placeValInt = 7;
        }
        if(placeVal == '8'){
            placeValInt = 8;
        }
        if(placeVal == '9'){
            placeValInt = 9;
        }
            for(int i=0; i<otherNum; i++){
                placeMultiple = placeMultiple * 10;
            }
        
            placeValInt = placeMultiple * placeValInt;
            result = result + placeValInt;
            placeMultiple = 1;
            otherNum++;
    } result = result/10;     
    return result;
}

void printLife(char (*matrix)[GRIDY][GRIDX], int current){
        for(int y=0;y<GRIDY;y++){
            for(int x=0;x<GRIDX;x++){
                //for every index print the char, and if you are at the end of a row print new line (ascii value)
                putchar(matrix[current][y][x]);
                 if(x == GRIDX-1){
                        putchar(10);
                    }    
                    
              }
            
    }
}
