/* Program to play Tic-Tac-Toe */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
void initialize_board(void);
void print_boardwithNum(void);
void print_board(void);
void game_starts(void);
int whoisthefirst(void);
void playerstep(void);
void computerstep(void);
void midcomputerstep(void);
char check_winner(void);
int restart(void);
void hardcomputerstep(void);
int comwinfirst(char);
void choose_difficulty(void);

char board[9];
char com, user;
int difficulty,move;

int main(void)
{  
  printf("\nwelcome to the Tic-Tac-Toe game. \n");
  print_boardwithNum();

  while(1)
  {
  initialize_board();
  choose_difficulty();
  if(whoisthefirst() == 0)
  {
    com = 'O';
    user = 'X';
  }
  else
  {
    com = 'X';
    user ='O';
  }

  game_starts();
    if(restart() != 1)
      break;   
  }
  return 0;
}

/* Make sure board is empty at the beginning. */
void initialize_board(void)
{
  int i;
  for (i = 0; i < 9; i++)
      board[i] = ' ';
}

/* print game board. */
void print_board(void) 
{
  printf("\n");
  printf("%2c |%2c |%2c\n",board[0],board[1],board[2]);
  printf("---+---+---\n");
  printf("%2c |%2c |%2c\n",board[3],board[4],board[5]);
  printf("---+---+---\n");
  printf("%2c |%2c |%2c\n",board[6],board[7],board[8]);
  printf("\n\n");
}

/* Show the game board order. */
void print_boardwithNum(void) 
{
  printf("\n");
  printf(" 1 | 2 | 3 \n");
  printf("---+---+---\n");
  printf(" 4 | 5 | 6 \n");
  printf("---+---+---\n");
  printf(" 7 | 8 | 9 \n\n");
  printf("Enter in the number corresponds to what space you want to play.\n");

}

/* Determine who plays first. */
int whoisthefirst(void)
{
  char First;
  printf("Are you going to play first? (y/n) ");
  getchar();
  while (1)
  {
      First = getchar();
      if((First!= 'y') && (First != 'Y') && (First != 'n') && (First != 'N'))
      {    
          printf("Enter (y/n), please.\n");
          while(First !='\n' && First != EOF)
          First = getchar();
      }
      else
          break;
  }

  if ((First == 'y') || (First == 'Y'))
  {
    printf("\nUser = O, Com = X. \n\n");
    printf("Mission: Connect three O's in a row to win a game.\n");   
    return 1;
  }
  else
  {
    printf("\nUser = X, Com = O. \n\n");
    printf("Mission: Connect three X's or in a row to win a game.\n");   
    return 0;
  }
}

void choose_difficulty(void)
{ 
  char i ;
  printf("\n\nchoose com difficulty.\n1.easy\n2.medium.\n3.hard\n");
  scanf("%s",&i);

  while(1)
  {switch(i)
   {
    case '1':
    difficulty = 1;
    return;
    case '2':
    difficulty = 2;
    return;
    case '3':
    difficulty = 3;
    return;
    default: 
    printf("Enter 1 ~ 3, please.\n");
    scanf("%s",&i);
    
    }
  }
}


void game_starts(void)
{ 
  int step;
  for (step = 1; step <= 9; step++)
  {
    if(step % 2 == 1)
    {
      if (com == 'O')
        {
          switch(difficulty)
          {
          case 1:
          computerstep();
          break;
          case 2:
          midcomputerstep();
          break;
          case 3:
          hardcomputerstep();
          break;
          default:
          break; 
          }
        }

      else
        playerstep();
    }
    else if (step % 2 == 0)
    {
      if (com == 'X')
        {
          switch(difficulty)
          {
          case 1:
          computerstep();
          break;
          case 2:
          midcomputerstep();
          break;
          case 3:
          hardcomputerstep();
          break;
          default:
          break; 
          }
        }
      else
        playerstep();
    }

    print_board();

    if(check_winner() == com) 
    {
      printf ("You lose! You need more practice. Haha\n");
      return;
    }
  
    else if(check_winner() == user)
    {
      printf("Congrats, you win! I cannot stop you...\n");
      return;
    }
   
  }
    {
      printf("This game is draw. Nice game!\n");
      return;
    }
}


char check_winner(void) /* check if there is a winner */
{
  int i;

  for(i=0; i<9; i+=3)  /* check rows */
    if(board[i] != ' ' && board[i]==board[i+1] && board[i+1]==board[i+2])
      return board[i];

  for(i=0; i<3; i+=1)  /* check columns */
    if(board[i] != ' ' && board[i]==board[i+3] && board[i+3]==board[i+6]) 
      return board[i];

  /* check diagonals */
  if(board[0]==board[4] && board[4]==board[8])
       return board[0];

  if(board[2]==board[4] && board[4]==board[6])
       return board[2];

  return ' ';
}

void playerstep(void)
{
  int i,flag;
  printf("Enter a number between 1 and 9 for your move.\n");
  while(1)
  {
  flag = scanf("%d",&i); 
  i--;
  getchar();
  if(!flag)
    {
    printf("Please enter a number! \n");
    continue;
    }
   else
   break; 
  }
  
  
  if(board[i]!=' ' || i > 9 || i < 0)
  {
    printf("Oops! You entered the wrong number or this place has been taken.\n");
    playerstep();
  }
  else
  {
    board[i] = user;
    printf("You chose %d.\n", i+1);
  }
}

void computerstep(void)
{
  int i;
  for (i = 0; i < 9; i++)
    if (board[i] == ' ')
    {
        board[i] = com;
        printf("computer chose %d.\n",i+1);
        break;
    }    
}

void midcomputerstep(void)
{
   /* randomize the AI's move */
   srand(time(NULL) );
   move = random()% 9;      
        
      if(board[move] == ' ')
      {
         board[move] = com;;
         printf("computer chose %d.\n",move+1);
      }
      else
      midcomputerstep();

      return;
     
}


void hardcomputerstep(void)
{
  int i,move;
  
    if (comwinfirst(com) != 0)
    return;
    if (comwinfirst(user) != 0)
    return;
  
        
      if(board[4]==' ')
      {
      board[4] = com;
      printf("computer chose %d.\n",5);
      }
      else if(board[0]==' ')
      {
      board[0] = com;
      printf("computer chose %d.\n",1);
      }
      else if(board[2]==' ')
      {
      board[2] = com;
      printf("computer chose %d.\n",3);
      }
      else if(board[6]==' ')
      {
      board[6] = com;
      printf("computer chose %d.\n",7);
      }
      else if(board[8]==' ')
      {
      board[8] = com;
      printf("computer chose %d.\n",9);
      }
      else 
      midcomputerstep();
      return;    
}

int comwinfirst(char S)
{
  int i;
  for(i = 0; i < 9; i+=3)
  {
    if(board[i] == board[i+1] && board[i]== S && board[i+2]==' ')
    {
      board[i+2] = com;
      printf("computer chose %d.\n",i+3);
      return 1;
    }
    if (board[i+1]== board[i+2] && board[i+1]== S && board[i]== ' ')
    {
      board[i] = com;
      printf("computer chose %d.\n",i+1);
      return 1;
    }
    if (board[i]== board[i+2] && board[i]== S && board[i+1]== ' ')
    {
      board[i+1] = com;
      printf("computer chose %d.\n",i+2);
      return 1;
    }
  }
   for(i = 0; i < 3; i++)
  {
    if(board[i] == board[i+3] && board[i]== S && board[i+6]== ' ')
    {
      board[i+6] = com;
      printf("computer chose %d.\n",i+7);
      return 1;
    }
    if (board[i+3]== board[i+6] && board[i+3]== S && board[i]== ' ')
    {
      board[i] = com;
      printf("computer chose %d.\n",i+1);
      return 1;
    }
    if (board[i]== board[i+6] && board[i]== S && board[i+3]== ' ')
    {
      board[i+3] = com;
      printf("computer chose %d.\n",i+4);
      return 1;
    }
  }
    if(board[0] == board[4] && board[0] == S && board[8]== ' ')
    {
      board[8] = com;
      printf("computer chose %d.\n",9);
      return 1;
    }
    if (board[0]== board[8] && board[0] == S && board[4]== ' ')
    {
      board[4] = com;
      printf("computer chose %d.\n",5);
      return 1;
    }
    if (board[4]== board[8] && board[4] == S && board[0] ==' ')
    {
      board[0] = com;
      printf("computer chose %d.\n",1);
      return 1;
    }
    if(board[2] == board[4] && board[2] == S && board[6]== ' ')
    {
      board[6] = com;
      printf("computer chose %d.\n",7);
      return 1;
    }
    if (board[2]== board[6] && board[2] == S && board[4]== ' ')
    {
      board[4] = com;
      printf("computer chose %d.\n",5);
      return 1;
    }
    if (board[4]== board[6] && board[4] == S && board[2]== ' ')
    {
      board[2] = com;
      printf("computer chose %d.\n",3);
      return 1;
    }
      if (board[0]== board[8] && board[0] == user && board[4] != ' ')
      {
        while(1)
        {  
          srand(time(NULL) );
          move = random()% 9;      
          if(move%2==1 && board[move] == ' ')
          {
            board[move] = com;;
            printf("computer chose %d.\n",move+1);
            return 1;
          }
        }
      }
      if (board[2]== board[6] && board[2] == user && board[4] != ' ')
      {
        while(1)
        {  
          srand(time(NULL) );
          move = random()% 9;      
          if(move%2==1 && board[move] == ' ')
          {
            board[move] = com;;
            printf("computer chose %d.\n",move+1);
            return 1;
          }
        }
      }
    return 0;
}

/* Restart game. */
int restart(void)
{
  char First;
  printf("Do you want to restart the game (y/n)?");
  
  while (1)
  {
      First = getchar();
      if((First!= 'y') && (First != 'Y') && (First != 'n') && (First != 'N'))
      {    
          printf("Enter (y/n), please.\n");
          while(First !='\n' && First != EOF)
          First = getchar();  
      }
      else
          break;
  }

  if ((First == 'y') || (First == 'Y'))
  {
    printf("I'm ready to play again!!!\n"); 
    return 1;
  }
  else
    {
    printf("Hope to see you soon. Bye bye !!\n");
    return 0;
    }
}


