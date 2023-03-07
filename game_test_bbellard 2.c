#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "game_aux.h"
#include "game.h"

/**************************** TEST DUMMY*****************************/
int test_dummy(void)
{
    return EXIT_SUCCESS;
}

/********************TEST GAME NEW EMPTY***************************/
int test_game_new_empty(void)
{
    game g = game_new_empty();
    assert(g);

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            if (game_get_square(g, i, j) != S_EMPTY)
            {
                game_delete(g);
                return EXIT_FAILURE;
            }
        }
    }
    game_delete(g);
    return EXIT_SUCCESS;
}
/******************TEST GAME NEW**************************/
int test_game_new(void)
{
    game g = game_default();
    assert(g);
    square G1[] = {
        S_EMPTY, S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO};
    game g1 = game_new(G1);
    assert(g1);
    if (game_equal(g, g1))
    {
        game_delete(g);
        game_delete(g1);
        return EXIT_SUCCESS;
    }
    game_delete(g);
    game_delete(g1);
    return EXIT_FAILURE;
}

/*****************TEST GAME GET SQUARE*************************/
int test_game_get_square(void)
{
    game g = game_default();
    assert(g);
    game g_s = game_default_solution();
    assert(g_s);
    bool test1 = (game_get_square(g, 0, 1) == S_IMMUTABLE_ONE);
    bool test2 = (game_get_square(g, 0, 2) == S_IMMUTABLE_ZERO);
    bool test3 = (game_get_square(g, 0, 3) == S_EMPTY);
    game_delete(g);
    game_delete(g_s);
    if (test1 && test2 && test3)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
/*******************TEST GAME GET NEXT SQUARE**************************/
int test_game_get_next_square(void)
{   
    uint i = 0;
    uint j = 0;
    direction dir = DOWN;
    uint dist = 1;
    cgame g = game_default();
    if(g == NULL || i >= DEFAULT_SIZE || j>= DEFAULT_SIZE || dist > 2){
        exit(EXIT_FAILURE);
    }
    
    assert(g);
 
    bool testb = (game_get_next_square(g, i, j, dir, dist) == S_EMPTY);
    game_delete(g);
    if (testb==true)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
/**********************TEST GAME GET NEXT NUMBER****************************/
int test_game_get_next_number(void)
{
    uint i = 0;
    uint j = 0;
    direction dir = DOWN;
    uint dist = 1;
    cgame g = game_default();
    if(g == NULL || i >= DEFAULT_SIZE || j>= DEFAULT_SIZE || dist > 2){
        exit(EXIT_FAILURE);
    }

    assert(g);

    bool test1 = (game_get_next_number(g, i, j, dir, dist) == -1);
    game_delete(g);
    if (test1 == true)
    {   
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
/**************************TEST GAME DEFAULT SOLUTION***********************************/
int test_game_default_solution(void)
{
    game g1 = game_default_solution();
    assert(g1);

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            if (game_has_error(g1, i, j) != 0)
            {
                game_delete(g1);
                return EXIT_FAILURE;
            }
        }
    }
    game_delete(g1);
    return EXIT_SUCCESS;
}
/******************************************************/

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
    if (strcmp("dummy", argv[1]) == 0)
        return test_dummy();

    else if (strcmp("game_new", argv[1]) == 0)
        return test_game_new();

    else if (strcmp("game_new_empty", argv[1]) == 0)
        return test_game_new_empty();

    else if (strcmp("game_get_square", argv[1]) == 0)
        return test_game_get_square();

    else if (strcmp("game_get_next_square", argv[1]) == 0)
        return test_game_get_next_square();

    else if (strcmp("game_get_next_number", argv[1]) == 0)
        return test_game_get_next_number();

    else if (strcmp("game_default_solution", argv[1]) == 0)
        return test_game_default_solution();

    else
    {
        fprintf(stderr, "Error: Test \"%s\" not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
