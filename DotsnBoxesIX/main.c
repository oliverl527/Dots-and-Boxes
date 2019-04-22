#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

lua_State *L, *M;
int counter = 0;

struct square {
	int my_sqr; bool top; bool bottom; bool left; bool right;
};
struct square board [100];

int get_opponent_name() {
	if (counter % 2 == 0){
        lua_getglobal(M, "get_name");
     lua_call(M, 0, 1); // 1 arg, 1 return
      char * p2_name =  lua_tostring(M, -1);
      lua_pushstring(L, p2_name);
	}
	else{
    lua_getglobal(L, "get_name");
     lua_call(L, 0, 1); // 1 arg, 1 return
      char * p1_name =  lua_tostring(L, -1);
      lua_pushstring(M, p1_name);
	}
	return 1;
}

int sqr_info(lua_State *N){
    int s_n = (int) lua_tonumber(N, -1);
    bool c = (bool)((board[s_n].top == board[s_n].bottom == board[s_n].left == board[s_n].right && board[s_n].right == true));
     bool m = (bool)((board[s_n].my_sqr%2) == (counter%2));
     double s = (double)((int)board[s_n].top + (int)board[s_n].bottom + (int)board[s_n].left + (int)board[s_n].right);
     bool t = (bool)board[s_n].top;
     bool b = (bool)board[s_n].bottom;
     bool l = (bool)board[s_n].left;
     bool r = (bool)board[s_n].right;
    lua_pushboolean(N, c);
     lua_pushboolean(N, m);
     lua_pushnumber(N, s);
     lua_pushboolean(N, t);
     lua_pushboolean(N, b);
     lua_pushboolean(N, l);
     lua_pushboolean(N, r);
    return 7;
}

int main(int argc, char *argv[])
{
    //  setting up the board
    int i = 0, boxes = 100;
    int edge_num = 0;
int sqr_num = 0;
    srand(time(NULL));
    counter = rand()%2;
    while(i < 100){
        board[i].my_sqr = -1;
        board[i].top = false;
        board[i].bottom = false;
        board[i].left = false;
        board[i].right = false;
        i++;
    }
    i = 0;
    //  setting up the states
     if(NULL == (L = luaL_newstate())) {
          printf("couldn't create state");
     }
     luaL_openlibs(L);
     lua_register(L, "sqr_info", sqr_info);
     lua_register(L, "get_opponent_name", get_opponent_name);

     if(luaL_dofile(L, argv[1])) {
          printf("doing file");
     }
     if(NULL == (M = luaL_newstate())) {
          printf("couldn't create state");
     }
     luaL_openlibs(M);
     lua_register(M, "sqr_info", sqr_info);
     lua_register(M, "get_opponent_name", get_opponent_name);


     if(luaL_dofile(M, argv[2])) {
          printf("doing file");
     }
     lua_getglobal(L, "get_name");
     lua_call(L, 0, 1); // 1 arg, 1 return
      char * p1_name =  lua_tostring(L, -1);
     lua_getglobal(M, "get_name");
     lua_call(M, 0, 1); // 1 arg, 1 return
      char * p2_name =  lua_tostring(M, -1);

     while(boxes > 0){
     // Getting the turn
     if(counter%2 == 0){
            lua_settop(L, 0);

     lua_getglobal(L, "turn");
     // TODO: Change the Lua program so that no number is pushed in or out
     lua_call(L, 0, 2); // 1 arg, 1 return

     sqr_num =  lua_tointeger(L, -2);
     edge_num = lua_tointeger(L, -1);
     }
     else{
            //lua_settop(M, 0);
     lua_getglobal(M, "turn");
     // TODO: Change the Lua program so that no number is pushed in or out;
     lua_call(M, 0, 2); // 1 arg, 1 return

     sqr_num =  lua_tointeger(M, -2);
     edge_num= lua_tointeger(M, -1);
     }
      // counter for the LUA game
    if (sqr_num < 0 || sqr_num > 99 || edge_num < 0 || edge_num > 3 || board[sqr_num].my_sqr != -1 ||
        (edge_num == 0 && board[sqr_num].top == true) || (edge_num == 1 && board[sqr_num].bottom == true) ||
        (edge_num == 2 && board[sqr_num].left == true) || (edge_num == 3 && board[sqr_num].right == true)) {
        continue;
    }
    int count = boxes;
    if (edge_num == 0) {	// sets the square
			board[sqr_num].top = true;
			if (sqr_num - 10 >= 0) {
				board[sqr_num - 10].bottom = true;
				if ((int)(board[sqr_num - 10].right) + (int)(board[sqr_num - 10].left) + (int)(board[sqr_num - 10].top) + (int)(board[sqr_num - 10].bottom) == 4) {
					board[sqr_num - 10].my_sqr = (counter % 2);
					count--;
				}
			}
		}
		else if (edge_num == 1) {
			board[sqr_num].bottom = true;
			if (sqr_num + 10 < 100) {
				board[sqr_num + 10].top = true;
				if ((int)(board[sqr_num + 10].right) + (int)(board[sqr_num].left + 10) + (int)(board[sqr_num + 10].top) + (int)(board[sqr_num + 10].bottom) == 4) {
					board[sqr_num + 10].my_sqr = (counter % 2);
					count--;
				}

			}
		}
		else if (edge_num == 2) {
			board[sqr_num].left = true;
			if (sqr_num - 1 >= 0 && sqr_num % 10 != 0) {
				board[sqr_num - 1].right = true;
				if ((int)(board[sqr_num - 1].right) + (int)(board[sqr_num - 1].left) + (int)(board[sqr_num - 1].top) + (int)(board[sqr_num - 1].bottom) == 4) {
					board[sqr_num - 1].my_sqr = (counter % 2);
					count--;
				}
			}
		}
		else if (edge_num == 3) {
			board[sqr_num].right = true;
			if (sqr_num + 1 < 100 && ((sqr_num + 1) % 10 != 0)) {
				board[sqr_num + 1].left = true;
				if ((int)(board[sqr_num + 1].right) + (int)(board[sqr_num + 1].left) + (int)(board[sqr_num + 1].top) + (int)(board[sqr_num + 1].bottom) == 4) {
					board[sqr_num + 1].my_sqr = (counter % 2);
					count--;
				}
			}
		}
		if ((int)(board[sqr_num].right) + (int)(board[sqr_num].left) + (int)(board[sqr_num].top) + (int)(board[sqr_num].bottom) == 4) {
			board[sqr_num].my_sqr = (counter % 2);
			count--;
		}
		if (count < boxes) {
			boxes = count;
			continue;
		}
    counter++;
     }
    int sum = 0;
	while (i < 100) {
		sum += board[i].my_sqr;
		i++;
	}
	i = 0;
	if (sum > 50) {
		printf("\n%s is the winner!\n\n", p2_name);
	}
	else if (sum < 50) {
		printf("\n%s is the winner!\n\n", p1_name);
	}
	else {
		printf("\nIts a tie!\n\n");
	}

	printf("Scores:\n");
	printf("%d - %s\n", (100 - sum), p1_name);
	printf("%d - %s\n", sum, p2_name);
	while (i < 100) {
		if (i % 10 == 0) {
			printf("\n");
		}
		printf("%d ", (board[i].my_sqr + 1));
		i++;
	}
	i = 0;
	printf("\n\n");
    counter = 0;
	if (sum > 50) {
     lua_getglobal(L, "i_lose");
     lua_call(L, 0, 1); // 1 arg, 1 return
     char * p1_saying =  lua_tostring(L, -1);
     counter = 1;
     lua_getglobal(M, "i_win");
     lua_call(M, 0, 1); // 1 arg, 1 return
      char * p2_saying =  lua_tostring(M, -1);
      printf("%s says: %s\n", p1_name, p1_saying);
        printf("%s says: %s\n", p2_name, p2_saying);
	}
	else if (sum < 50) {
     lua_getglobal(L, "i_win");
     lua_call(L, 0, 1); // 1 arg, 1 return
     char * p1_saying =  lua_tostring(L, -1);
    counter = 1;
     lua_getglobal(M, "i_lose");
     lua_call(M, 0, 1); // 1 arg, 1 return
     char * p2_saying =  lua_tostring(M, -1);
     printf("%s says: %s\n", p1_name, p1_saying);
        printf("%s says: %s\n", p2_name, p2_saying);
	}
	else {

     lua_getglobal(L, "i_win");
     lua_call(L, 0, 1); // 1 arg, 1 return
     char * p1_saying =  lua_tostring(L, -1);
    counter = 1;
     lua_getglobal(M, "i_win");
     lua_call(M, 0, 1); // 1 arg, 1 return
     char * p2_saying =  lua_tostring(M, -1);
        printf("Winning Statements:\n%s says: %s\n", p1_name, p1_saying);
        printf("%s says: %s\n\n", p2_name, p2_saying);
    counter = 0;
     lua_getglobal(L, "i_lose");
     lua_call(L, 0, 1); // 1 arg, 1 return
     p1_saying =  lua_tostring(L, -1);
    counter = 1;
     lua_getglobal(M, "i_lose");
     lua_call(M, 0, 1); // 1 arg, 1 return
      p2_saying =  lua_tostring(M, -1);
        printf("Losing Statements:\n%s says: %s\n", p1_name, p1_saying);
        printf("%s says: %s\n\n", p2_name, p2_saying);
	}
     lua_close(L);
     lua_close(M);

     return EXIT_SUCCESS;
}
