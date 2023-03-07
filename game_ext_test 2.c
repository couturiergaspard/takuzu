#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "game_aux.h"
#include "game.h"
#include "game_ext.h"
/*********************************************/
int test_game_new_ext(){
    square s[] = {S_ZERO, S_EMPTY, S_ONE, S_ZERO};
    game g = game_new_ext(2, 2, s, true, true);
    assert(g);
    if (game_get_square(g, 0, 0) == S_ZERO && game_get_square(g, 0, 1) == S_EMPTY && game_get_square(g, 1, 0) == S_ONE && game_get_square(g, 1, 1) == S_ZERO){ 
        game_delete(g);
        return EXIT_SUCCESS;
    }
    game_delete(g);
    return EXIT_FAILURE;
}
/*************************************************/
int test_game_new_empty_ext(){
    game g = game_new_empty_ext(4, 4, true, true);
    assert(g);
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            if (game_get_square(g, i, j) != S_EMPTY){  
                game_delete(g);
                return EXIT_FAILURE;
            }
        }
    }
    game_delete(g);
    return EXIT_SUCCESS;
}
/***************************************************/
int test_game_nb_rows(){
    square s[] = {S_ZERO, S_EMPTY, S_ONE, S_ZERO};
    game g = game_new_ext(2, 2, s, true, true);  
    assert(g);
    if (game_nb_rows(g) == 2 && game_nb_rows(g)<= 10 && game_nb_rows(g)> 0) { 
        game_delete(g);
        return EXIT_SUCCESS;
    }
    game_delete(g);
    return EXIT_FAILURE;
}
/********************************************************/
int test_game_nb_cols(){
    square s[] = {S_ZERO, S_EMPTY, S_ONE, S_ZERO};
    game g = game_new_ext(2, 2, s, true, true);  
    assert(g);
    if (game_nb_cols(g) == 2 && game_nb_cols(g) <= 10 && game_nb_cols(g) > 0) { 
        game_delete(g);
        return EXIT_SUCCESS;
    }
    game_delete(g);
    return EXIT_FAILURE;
}
/*********************************************************/
int test_game_is_wrapping(){
    square s[]=    {S_ONE, S_ZERO, S_ONE, S_ZERO,
                    S_ZERO, S_ONE, S_ZERO, S_ONE,
                    S_ONE, S_ZERO, S_ONE, S_ZERO,
                    S_ZERO, S_ONE, S_ZERO, S_ONE,};
    game g= game_new_ext(4,4,s,true,true);
    assert(g);

    square s1[]=    {S_ZERO, S_ZERO, S_ONE, S_ZERO,
                    S_ONE, S_ONE, S_ZERO, S_ONE,
                    S_ZERO, S_ZERO, S_ONE, S_ZERO,
                    S_ONE, S_ONE, S_ZERO, S_ONE,};

    game g1= game_new_ext(4,4,s1,false,true);
    assert(g1);
    
    bool test1 = game_is_wrapping(g);
    bool test2 = game_is_wrapping(g1);
    
    if( test1 == true &&   test2 == false){
        game_delete(g);
        game_delete(g1);
        return EXIT_SUCCESS;
    }
    game_delete(g);
    game_delete(g1);
    return EXIT_FAILURE;
}   
/*********************************************************/
int test_game_is_unique(){
    
    square s [] = {S_ZERO, S_ONE,S_ONE,S_ZERO};
    game g = game_new_ext(2,2,s,true,true);
    assert (g);
    
    bool test1 = game_is_unique(g);
    if (test1 == false){
        game_delete(g);
        return EXIT_FAILURE;
    }
    
    square k [] = {S_ZERO, S_ONE,S_ZERO,S_ONE};
    game g1 = game_new_ext(2,2,k,true,false);
    assert(g1);

    bool test2 = game_is_unique(g1);
    if (test2 == true){
        game_delete(g);
        game_delete(g1);
        return EXIT_FAILURE;
    }
    game_delete(g);
    game_delete(g1);
    return EXIT_SUCCESS;
}
/***********************************************************/
int test_game_undo(){
    game g = game_default(); 
    assert(g);
    game_play_move(g, 5, 5, S_ONE);  
    game_play_move(g, 0, 0, S_ZERO); 
    game_undo(g);                          

    if (game_get_number(g,0,0) == 1) {
        game_delete(g);
        return EXIT_FAILURE;
    }
    game_undo(g);  
    if (game_get_number(g, 5, 5) == 2) {
        game_delete(g);
        return EXIT_FAILURE;
    }
    game_delete(g);
    return EXIT_SUCCESS;
    }

int test_game_redo(){
    return EXIT_SUCCESS;
}



/***********************************************************/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "At least one argument expected !\n");
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Starting test of : <%s>"
                    "\n",
            argv[1]);
    if (strcmp("game_new_ext", argv[1]) == 0)
        return test_game_new_ext();

    else if (strcmp("game_new_empty_ext", argv[1]) == 0)
        return test_game_new_empty_ext();

    else if (strcmp("game_nb_rows", argv[1]) == 0)
        return test_game_nb_rows();

    else if (strcmp("game_nb_cols", argv[1]) == 0)
        return test_game_nb_cols();

    else if (strcmp("game_is_wrapping", argv[1]) == 0)
        return test_game_is_wrapping();

    else if (strcmp("game_is_unique", argv[1]) == 0)
        return test_game_is_unique();

    else if (strcmp("game_undo", argv[1]) == 0)
        return test_game_undo();

    else if (strcmp("game_redo", argv[1]) == 0)
        return test_game_redo();

    else
    {
        fprintf(stderr, "Error: Test \"%s\" not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
