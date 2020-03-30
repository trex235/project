#include <stdio.h>
#include <math.h>

#define MAX_BATTLE_SIZE (15)
#define CELL_SIZE (5)
#define MAX_MOVE_RANGE (25)
#define MAX_NORMAL_ATTACK_RANGE (10)
#define NORMAL_ATTACK_STRENGTH (10)

enum BattleResult{POSITIVE_WIN, NEGATIVE_WIN, NO_RESULT};

void initBattle(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int * actual_length, int * actual_width);
void initBattleActionOrder(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width, int * action_order);
void displayBoard(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width);
void attack(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate);
void move(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                     int first_length_index, int first_width_index, int second_length_index, int second_width_index);
double getDistance(int first_length_index, int first_width_index, int second_length_index, int second_width_index);
enum BattleResult getBattleResult(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width);
void findClosestEnemy(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                     int first_length_index, int first_width_index, int * closest_enemy_length, int * closest_enemy_width);

int main()
{
    int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE] = {{0}};
    int battlefield_action_order[2 * MAX_BATTLE_SIZE * MAX_BATTLE_SIZE + 1];
    int  actual_length, actual_width, current_action_index = 0;
    int enemy_first_index, enemy_second_index;

    scanf("%d %d",&actual_length,&actual_width);


    initBattle(battlefield, &actual_length, &actual_width);
    battlefield_action_order[0]=-1;

    while (NO_RESULT == getBattleResult(battlefield, actual_length, actual_width)) {
            if (-1 == battlefield_action_order[current_action_index]) {
                initBattleActionOrder(battlefield,actual_length,actual_width,&battlefield_action_order[0]);
                current_action_index=0;
            }
             findClosestEnemy(battlefield,actual_length, actual_width,battlefield_action_order[current_action_index],battlefield_action_order[current_action_index+1],&enemy_first_index,&enemy_second_index);
             if(getDistance(battlefield_action_order[current_action_index],battlefield_action_order[current_action_index+1],enemy_first_index,enemy_second_index)<=10){
                attack(battlefield,enemy_first_index,enemy_second_index);}
             else{
                    move(battlefield,actual_length,actual_width,battlefield_action_order[current_action_index],battlefield_action_order[current_action_index+1],enemy_first_index,enemy_second_index);
             }
            current_action_index += 2;

    }

    switch(getBattleResult(battlefield, actual_length, actual_width)) {
        case POSITIVE_WIN:
            printf("Positive win!\n");
            break;
        case  NEGATIVE_WIN:
            printf("Negative win!\n");
            break;
        default:
            break;
    }
    displayBoard(battlefield, actual_length, actual_width);
    return 0;
}

void initBattle(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int * actual_length, int * actual_width) {
    int i,j;
for (i=0;i<* actual_length;i++){
    for(j=0;j<* actual_width;j++)
    {
        scanf("%d", &battlefield[i][j]);
    }
}
}

void initBattleActionOrder(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width, int * action_order){
    int i, j, k = 0;
     for (i = 0; i < actual_length; i++) {
        for (j = 0; j < actual_width; j++) {
            if (battlefield[i][j] !=0 ) {
                *(action_order+k) =i;
                *(action_order+k+1)=j;
                k=k+2;
            }
        }
     }
     *(action_order + k) = -1;
}

double getDistance(int first_length_index, int first_width_index, int second_length_index, int second_width_index) {
    int length_delta = (second_length_index - first_length_index) * CELL_SIZE;
    int width_delta = (second_width_index - first_width_index) * CELL_SIZE;
    int value_to_square = length_delta * length_delta + width_delta * width_delta;
    return sqrt(value_to_square);
}

enum BattleResult getBattleResult(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width) {
int i,j, countpos=0, countneg=0;
for(i=0;i<actual_length;i++){
    for(j=0;j<actual_width;j++){
        if (battlefield[i][j]<0){
            countneg++;}
        if (battlefield[i][j]>0){
            countpos++;}}}
    if ((countpos==0)&&(countneg>0)){
        return NEGATIVE_WIN;}
    if((countpos>0)&&(countneg==0)){
         return POSITIVE_WIN;}
    else{
        return NO_RESULT;}
    }


void displayBoard(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width) {
    int i, j;
    for (i = 0; i < actual_length; i++) {
        for (j = 0; j < actual_width; j ++){
            printf("|%4d", battlefield[i][j]);
        }
        printf("|\n");
    }
}

void move(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                     int first_length_index, int first_width_index, int second_length_index, int second_width_index) {

 int distance,i=0,j=0,shora=first_length_index,amoda=first_width_index;
 distance=getDistance(first_length_index,first_width_index,second_length_index,second_width_index);
   for(i=0;i<actual_length;i++)
  {
      for(j=0;j<actual_width;j++){
       if(battlefield[i][j]==0){
            if ((getDistance(first_length_index,first_width_index,i,j)<=25)&&
            (getDistance(i,j,second_length_index,second_width_index)<distance)){
           distance=getDistance(i,j,second_length_index,second_width_index);
           shora=i;
           amoda=j;
           continue; }
        if ((getDistance(first_length_index,first_width_index,i,j)<=25)&&
            (getDistance(i,j,second_length_index,second_width_index)==distance)){

            distance=getDistance(i,j,second_length_index,second_width_index);
            if(i<shora){
                shora=i;
                amoda=j;}
            if(i==shora){
                if(j>amoda){
                    amoda=j;}}
       }}
      }}
    if((shora==first_length_index)&&(amoda==first_width_index)){
        battlefield[shora][amoda]=battlefield[first_length_index][first_width_index];}
    else{battlefield[shora][amoda]=battlefield[first_length_index][first_width_index];
        battlefield[first_length_index][first_width_index]=0;
    }


}

void attack(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int attacked_first_coordinate, int attacked_second_coordinate) {
  if(battlefield[attacked_first_coordinate][attacked_second_coordinate]<0){
        if(battlefield[attacked_first_coordinate][attacked_second_coordinate]>-10){
           battlefield[attacked_first_coordinate][attacked_second_coordinate]=0;}
         else{ battlefield[attacked_first_coordinate][attacked_second_coordinate]+=10;}}
  else{
        if( battlefield[attacked_first_coordinate][attacked_second_coordinate]<10){
             battlefield[attacked_first_coordinate][attacked_second_coordinate]=0;}
        else{
    battlefield[attacked_first_coordinate][attacked_second_coordinate]-=10;}}
}

void findClosestEnemy(int battlefield [MAX_BATTLE_SIZE][MAX_BATTLE_SIZE], int actual_length, int actual_width,
                     int first_length_index, int first_width_index, int * closest_enemy_length, int * closest_enemy_width) {
  int i,j,distance,smallest=100,shora=0,amoda=actual_width;
  for(i=0;i<actual_length;i++)
  {
      for(j=0;j<actual_width;j++)
      {
          if((battlefield[first_length_index][first_width_index]>0)&&(battlefield[i][j]<0))
          {
              distance=getDistance(first_length_index,first_width_index,i,j);
              if(distance<smallest){
                smallest=distance;
                shora=i;
                amoda=j;}
              if(distance==smallest){
                if(i>shora){
                    shora=i;
                    amoda=j;}
                if(i==shora){
                    if(j<amoda){
                        amoda=j;
                    }}}}
          if((battlefield[first_length_index][first_width_index]<0)&&(battlefield[i][j]>0))
          {
              distance=getDistance(first_length_index,first_width_index,i,j);
              if(distance<smallest){
                smallest=distance;
                shora=i;
                amoda=j;}
              if(distance==smallest){
                if(i>shora){
                    shora=i;
                    amoda=j;}
                if(i==shora){
                    if(j<amoda){
                        amoda=j;
                    }}}}
        }}
       * closest_enemy_length=shora;
       * closest_enemy_width=amoda;

      }
