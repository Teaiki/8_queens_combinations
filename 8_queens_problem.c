#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void his_reverse(char str[], int len)
{
  int start, end;
  char temp;
  for(start=0, end=len-1; start < end; start++, end--) {
    temp = *(str+start);
    *(str+start) = *(str+end);
    *(str+end) = temp;
  }
}

char* his_itoa(int num, char* str, int base)
{
  int i = 0;
  bool isNegative = false;

  /* A zero is same "0" string in all base */
  if (num == 0) {
    str[i] = '0';
    str[i + 1] = '\0';
    return str;
  }

  /* negative numbers are only handled if base is 10 
     otherwise considered unsigned number */
  if (num < 0 && base == 10) {
    isNegative = true;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
    num = num/base;
  }

  /* Append negative sign for negative numbers */
  if (isNegative){
    str[i++] = '-';
  }

  str[i] = '\0';

  his_reverse(str, i);

  return str;
}

void display_sol(int n_sol, int *dame_y, char **black_bg, char **white_bg, char **queen_black_bg, char **queen_white_bg)
{
  char **grid;
  
  char char_n_sol[2];
  // char_n_sol = n_sol + 48;

  his_itoa(n_sol, char_n_sol, 10);
  
  write(1, "Solution number ", 16);
  write(1, &char_n_sol, 2);
  write(1, "\n\n", 2);
  
  // Initialize grid
  grid = malloc(96 * sizeof(char*));
  for(int j=0 ; j<96 ; j++)
    {
      grid[j] = malloc(192 * sizeof(char));
    }

  // fill grid with chessboard pattern
  for (int j=0 ; j<8 ; j++)
    {
      for(int i=0 ; i<8 ; i++)
	{
	  if((j+i)%2 == 0) // white case
	    {
	      if(j == dame_y[i])
		{
		  for(int k=0 ; k<12 ; k++)
		    {
		      for(int l=0 ; l<24 ; l++)
			{
			  grid[j*12 + k][i*24 + l] = queen_white_bg[k][l];
			}
		    }
		}
	      else
		{
		  for(int k=0 ; k<12 ; k++)
		    {
		      for(int l=0 ; l<24 ; l++)
			{
			  grid[j*12 + k][i*24 + l] = white_bg[k][l];
			}
		    }
		}
	    }
	  if((j+i)%2 == 1) // black case
	    {
	      if(j == dame_y[i])
		{
		  for(int k=0 ; k<12 ; k++)
		    {
		      for(int l=0 ; l<24 ; l++)
			{
			  grid[j*12 + k][i*24 + l] = queen_black_bg[k][l];
			}
		    }
		}
	      else
		{
		  for(int k=0 ; k<12 ; k++)
		    {
		      for(int l=0 ; l<24 ; l++)
			{
			  grid[j*12 + k][i*24 + l] = black_bg[k][l];
			}
		    }
		}
	    }
	}
    }

  for(int j=0 ; j<96 ; j++)
    {
      write(1, grid[j],192);
      write(1,"\n",1);
    }
  write(1, "\n\n\n\n\n\n \0", 7);

  // free grid
  for(int j=0 ; j<96 ; j++)
    {
      free(grid[j]);
    }
  free(grid);
  
}

int my_8_queens(char **black_bg, char **white_bg, char **queen_black_bg, char **queen_white_bg)
{
  char dame1[2];
  char dame2[2];
  char dame3[2];
  char dame4[2];
  char dame5[2];
  char dame6[2];
  char dame7[2];
  char dame8[2];
  int c1,c2,c3,c4,c5,c6,c7,c8;
  int n_sol;
  
  char line[9] = "12345678\0";
  int dame_y[8];
  
  float cd21, cd31, cd41, cd51, cd61, cd71, cd81;
  float cd32, cd42, cd52, cd62, cd72, cd82;
  float cd43, cd53, cd63, cd73, cd83;
  float cd54, cd64, cd74, cd84;
  float cd65, cd75, cd85;
  float cd76, cd86;
  float cd87;

  int flag2, flag3, flag4, flag5, flag6, flag7;
  
  
  dame1[0] = 'a';
  dame2[0] = 'b';
  dame3[0] = 'c';
  dame4[0] = 'd';
  dame5[0] = 'e';
  dame6[0] = 'f';
  dame7[0] = 'g';
  dame8[0] = 'h';

  n_sol = 0;
  for(c1 = 0 ; c1 < 8 ; c1++)
    {
      dame1[1] = line[c1];
      for(c2 = 0 ; c2 < 8 ; c2++)
	{
	  if(c2 != c1)
	    {
	      dame2[1] = line[c2];
	      cd21 = (float)(dame2[1]-dame1[1])/(dame2[0]-dame1[0]); //Calcul du coefficient directeur
	      flag2 = 0;
	      if(cd21 != 1 && cd21 !=-1)
		{
		  flag2 = 1;
		}
	      for(c3 = 0 ; c3 < 8 ; c3++)
		{
		  if(c3 != c2 && c3 != c1 && flag2 == 1)
		  
		    {
		      dame3[1] = line[c3];
		      cd31 = (float)(dame3[1]-dame1[1])/(dame3[0]-dame1[0]);
		      cd32 = (float)(dame3[1]-dame2[1])/(dame3[0]-dame2[0]);
		      flag3 = 0;
		      if(cd31 != 1 && cd31 !=-1 && cd32 !=1 && cd32 != -1)
			{
			  flag3 = 1;
			}
		      for(c4 = 0 ; c4 < 8  ; c4++)
			{
			  if(c4 != c3 && c4 != c2 && c4 != c1 && flag3 == 1)
			  
			    {
			      dame4[1] = line[c4];
			      cd41 = (float)(dame4[1]-dame1[1])/(dame4[0]-dame1[0]);
			      cd42 = (float)(dame4[1]-dame2[1])/(dame4[0]-dame2[0]);
			      cd43 = (float)(dame4[1]-dame3[1])/(dame4[0]-dame3[0]);
			      flag4 = 0;
			      if(cd41 != 1 && cd41 !=-1 && cd42 !=1 && cd42 != -1 && cd43 != 1 && cd43 != -1)
				{
				  flag4 = 1;
				}
			      for(c5 = 0 ; c5 < 8 ; c5++)
				{
				  if(c5 != c4 && c5 != c3 && c5 != c2 && c5 != c1 && flag4==1)
				  
				    {
				      dame5[1] = line[c5];
				      cd51 = (float)(dame5[1]-dame1[1])/(dame5[0]-dame1[0]);
				      cd52 = (float)(dame5[1]-dame2[1])/(dame5[0]-dame2[0]);
				      cd53 = (float)(dame5[1]-dame3[1])/(dame5[0]-dame3[0]);
				      cd54 = (float)(dame5[1]-dame4[1])/(dame5[0]-dame4[0]);
				      flag5 = 0;
				      if(cd51 != 1 && cd51 !=-1 && cd52 !=1 && cd52 != -1 && cd53 != 1 && cd53 != -1 && cd54 != 1 && cd54 != -1)
					{
					  flag5 = 1;
					}
				      for(c6 = 0 ; c6 < 8 ; c6++)
					{
					  if(c6 != c5 && c6 != c4 && c6 != c3 && c6 != c2 && c6 != c1 && flag5 ==1)
					  
					    {
					      dame6[1] = line[c6];
					      cd61 = (float)(dame6[1]-dame1[1])/(dame6[0]-dame1[0]);
					      cd62 = (float)(dame6[1]-dame2[1])/(dame6[0]-dame2[0]);
					      cd63 = (float)(dame6[1]-dame3[1])/(dame6[0]-dame3[0]);
					      cd64 = (float)(dame6[1]-dame4[1])/(dame6[0]-dame4[0]);
					      cd65 = (float)(dame6[1]-dame5[1])/(dame6[0]-dame5[0]);
					      flag6 = 0;
					      if(cd61 != 1 && cd61 !=-1 && cd62 !=1 && cd62 != -1 && cd63 != 1 && cd63 != -1 && cd64 != 1 && cd64 != -1 && cd65 != 1 && cd65 != -1)
						{
						  flag6 = 1;
						}
					      for(c7 = 0 ; c7 < 8 ; c7++)
						{
						  if(c7 != c6 && c7 != c5 && c7 != c4 && c7 != c3 && c7 != c2 && c7 != c1 && flag6 == 1)
						  
						    {
						      dame7[1] = line[c7];
						      cd71 = (float)(dame7[1]-dame1[1])/(dame7[0]-dame1[0]);
						      cd72 = (float)(dame7[1]-dame2[1])/(dame7[0]-dame2[0]);
						      cd73 = (float)(dame7[1]-dame3[1])/(dame7[0]-dame3[0]);
						      cd74 = (float)(dame7[1]-dame4[1])/(dame7[0]-dame4[0]);
						      cd75 = (float)(dame7[1]-dame5[1])/(dame7[0]-dame5[0]);
						      cd76 = (float)(dame7[1]-dame6[1])/(dame7[0]-dame6[0]);
						      flag7 = 0;
						      if(cd71 != 1 && cd71 !=-1 && cd72 !=1 && cd72 != -1 && cd73 != 1 && cd73 != -1 && cd74 != 1 && cd74 != -1 && cd75 != 1 && cd75 != -1 && cd76 != 1 && cd76 != -1)
							{
							  flag7 = 1;
							}
						      for(c8 = 0 ; c8 < 8 ; c8++)
							{
							  if(c8 != c7 && c8 != c6 && c8 != c5 && c8 != c4 && c8 != c3 && c8 != c2 && c8 != c1 && flag7 ==1)
							  
							    {
							      dame8[1] = line[c8];
							      cd81 = (float)(dame8[1]-dame1[1])/(dame8[0]-dame1[0]); 
							      cd82 = (float)(dame8[1]-dame2[1])/(dame8[0]-dame2[0]);
							      cd83 = (float)(dame8[1]-dame3[1])/(dame8[0]-dame3[0]);
							      cd84 = (float)(dame8[1]-dame4[1])/(dame8[0]-dame4[0]);
							      cd85 = (float)(dame8[1]-dame5[1])/(dame8[0]-dame5[0]);			  
							      cd86 = (float)(dame8[1]-dame6[1])/(dame8[0]-dame6[0]);
							      cd87 = (float)(dame8[1]-dame7[1])/(dame8[0]-dame7[0]);
							      
							      if(cd81 != 1 && cd81 !=-1 && cd82 != 1 && cd82 != -1 && cd83 != 1 && cd83 != -1 && cd84 != 1 && cd84 != -1 && cd85 != 1 && cd85 != -1 && cd86 != 1 && cd86 != -1 && cd87 != 1 && cd87 != -1)
								{
								  n_sol = n_sol +1;
								  write(1, dame1, 2);
								  write(1, ",",1);
								  write(1, dame2, 2);
								  write(1, ",",1);
								  write(1, dame3, 2);
								  write(1, ",",1);
								  write(1, dame4, 2);
								  write(1, ",",1);
								  write(1, dame5, 2);
								  write(1, ",",1);
								  write(1, dame6, 2);
								  write(1, ",",1);
								  write(1, dame7, 2);
								  write(1, ",",1);
								  write(1, dame8, 2);
								  write(1, "\n",1);

								  dame_y[0] = dame1[1] - 49;
								  dame_y[1] = dame2[1] - 49;
								  dame_y[2] = dame3[1] - 49;
								  dame_y[3] = dame4[1] - 49;
								  dame_y[4] = dame5[1] - 49; 
								  dame_y[5] = dame6[1] - 49;
								  dame_y[6] = dame7[1] - 49;
								  dame_y[7] = dame8[1] - 49;

								  
								  display_sol(n_sol, dame_y, black_bg, white_bg, queen_black_bg, queen_white_bg);
								  }
							    }
							}
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }  
}

char **generate_black_bg()
{
  char **pattern;

  pattern = malloc(12 * sizeof(char*));
  for(int j=0 ; j<12 ; j++)
    {
      pattern[j] = malloc(24 * sizeof(char));
    }

  for(int j=0 ; j<12 ; j++)
    {
      strncpy(pattern[j], "@@@@@@@@@@@@@@@@@@@@@@@@", 24);
    }
  return pattern;
}

char **generate_white_bg()
{
  char **pattern;

  pattern = malloc(12 * sizeof(char*));
  for(int j=0 ; j<12 ; j++)
    {
      pattern[j] = malloc(24 * sizeof(char));
    }
  
  for(int j=0 ; j<12 ; j++)
    {
      strncpy(pattern[j], "                        ", 24);
    }

  return pattern;
}

char **generate_queen_black_bg()
{
  char **pattern;
  pattern = malloc(12 * sizeof(char*));
  for(int j=0 ; j<12 ; j++)
    {
      pattern[j] = malloc(24 * sizeof(char));
    }
  
  strncpy(pattern[0],  "@@@@@@@@@@@@@@@@@@@@@@@@", 24);
  strncpy(pattern[1],  "@@@@@@@@@@_()_@@@@@@@@@@", 24);
  strncpy(pattern[2],  "@@@@@@@@_/____\\_@@@@@@@@", 24);
  strncpy(pattern[3],  "@@@@@@@@\\      /@@@@@@@@", 24);
  strncpy(pattern[4],  "@@@@@@@@@\\____/@@@@@@@@@", 24);
  strncpy(pattern[5],  "@@@@@@@@@(____)@@@@@@@@@", 24);
  strncpy(pattern[6],  "@@@@@@@@@@|  |@@@@@@@@@@", 24);
  strncpy(pattern[7],  "@@@@@@@@@@|__|@@@@@@@@@@", 24);
  strncpy(pattern[8],  "@@@@@@@@@/____\\@@@@@@@@@", 24);
  strncpy(pattern[9],  "@@@@@@@@(______)@@@@@@@@", 24);
  strncpy(pattern[10], "@@@@@@@(________)@@@@@@@", 24);
  strncpy(pattern[11], "@@@@@@@/________\\@@@@@@@", 24);
  
  return pattern;
}

char **generate_queen_white_bg()
{
  char **pattern;
  pattern = malloc(12 * sizeof(char*));
  for(int j=0 ; j<12 ; j++)
    {
      pattern[j] = malloc(24 * sizeof(char));
    }
  
  strncpy(pattern[0],  "                        ", 24);
  strncpy(pattern[1],  "          _()_          ", 24);
  strncpy(pattern[2],  "        _/____\\_        ", 24);
  strncpy(pattern[3],  "        \\      /        ", 24);
  strncpy(pattern[4],  "         \\____/         ", 24);
  strncpy(pattern[5],  "         (____)         ", 24);
  strncpy(pattern[6],  "          |  |          ", 24);
  strncpy(pattern[7],  "          |__|          ", 24);
  strncpy(pattern[8],  "         /____\\         ", 24);
  strncpy(pattern[9],  "        (______)        ", 24);
  strncpy(pattern[10], "       (________)       ", 24);
  strncpy(pattern[11], "       /________\\       ", 24);
  
  return pattern;
}

void free_patterns(char **black_bg, char **white_bg, char **queen_black_bg, char **queen_white_bg)
{
  for(int j=0 ; j<12 ; j++)
    {
      free(black_bg[j]);
      free(white_bg[j]);
      free(queen_black_bg[j]);
      free(queen_white_bg[j]);
    }
  free(black_bg);
  free(white_bg);
  free(queen_black_bg);
  free(queen_white_bg);
}

int main()
{
  char **black_bg, **white_bg, **queen_black_bg, **queen_white_bg;

  // Memory allocation for patterns
  black_bg = generate_black_bg();
  white_bg = generate_white_bg();
  queen_black_bg = generate_queen_black_bg();
  queen_white_bg = generate_queen_white_bg();
  
  my_8_queens(black_bg, white_bg, queen_black_bg, queen_white_bg);

  // Free memory for pattern
  free_patterns(black_bg, white_bg, queen_black_bg, queen_white_bg);
  return(0);
}
