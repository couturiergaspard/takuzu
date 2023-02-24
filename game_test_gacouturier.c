#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game_aux.h"
#include "game.h"

int test_dummy(void) { return EXIT_SUCCESS; }

/**********TEST GET NUMBER**********/
int test_game_get_number(void)
{   
    uint i = 0;
    uint j = 0;
    game g = game_default();
    game g_s = game_default_solution();
    assert(g);
    assert(g_s);
    if (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
        game_get_square(g, i, j) == S_IMMUTABLE_ZERO)
    {   
        game_delete(g_s);
        game_delete(g);
        return 1;
    }
    bool testblack = (game_get_number(g_s, 2, 0) == 1);
    bool testwhite = (game_get_number(g_s, 1, 0) == 0);
    bool testempty = (game_get_number(g, 0, 0) == -1);
    if (testblack && testwhite && testempty)
    {
        game_delete(g_s);
        game_delete(g);
        return 0;
    }
    game_delete(g_s);
    game_delete(g);
    return 1;
}

/**********TEST GAME COPY**********/
int test_game_copy()
{
    game g = game_default_solution();
    assert(g);
    game g_test_copy = game_copy(g);
    assert(g_test_copy);
    game g_test = game_new_empty();
    assert(g_test);
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            game_set_square(g_test, i, j, game_get_square(g, i, j));
        }
    }

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            if (game_get_square(g, i, j) != game_get_square(g_test_copy, i, j) ||
                game_get_square(g_test_copy, i, j) != game_get_square(g_test, i, j) ||
                game_get_square(g, i, j) != game_get_square(g_test, i, j))
            {   
                game_delete(g);
                game_delete(g_test_copy);
                game_delete(g_test);
                return 1;
            }
        }
    }
    if (game_equal(g, g_test) && game_equal(g_test_copy, g_test) && game_equal(g, g_test_copy))
    {   
        game_delete(g);
        game_delete(g_test_copy);
        game_delete(g_test);
        return 0;
    }
    game_delete(g);
    game_delete(g_test_copy);
    game_delete(g_test);
    return 1;
}

/**********TEST GAME SET SQUARE**********/
int test_game_set_square(void)
{   
    uint i = 0;
    uint j = 0;
    game g = game_default();
    assert(g);
    if (game_get_square(g, i, j) == S_EMPTY)
    {
        game_set_square(g, i, j, S_ZERO);
        if (game_get_square(g, i, j) == S_ZERO)
        {
            game_delete(g);
            return 0;
        }
    }
    game_delete(g);
    return 1;
}

/**********TEST GAME EQUAL**********/
int test_game_equal()
{
    game g = game_default();
    square q[] = {
        S_EMPTY, S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO};
    game g1 = game_new(q);
    assert(g);
    assert(g1);
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            if (game_get_square(g, i, j) != game_get_square(g1, i, j))
            {
                game_delete(g1);
                game_delete(g);
                return 1;
            }
        }
    }

    game_delete(g1); 
    game_delete(g);
    return 0;
}

/**********TEST GAME DEFAULT**********/
int test_game_default()
{
    game g = game_default();
    assert(g);

    square q[] = {
        S_EMPTY, S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY,
        S_EMPTY, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_EMPTY,
        S_EMPTY, S_EMPTY, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO,
        S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO};
    game tmp = game_new(q); 
    assert(tmp);

    if (game_equal(tmp, g))
    {                     
        game_delete(tmp); 
        game_delete(g);
        return 0;
    }

    game_delete(tmp); 
    game_delete(g);   
    return 1;
}

/**********TEST GAME PRINT**********/
int test_game_print()
{
    game g = game_default(); 
    game_print(g);           
    assert(g);               
    game_delete(g);          
    return 0;                
}

/**********TEST GAME DELETE**********/
int test_game_delete()
{
    game g = game_default(); 
    game_delete(g);          
    assert(g != NULL);       
    return 0;                
}

/*MON MAIN*/
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

    else if (strcmp("game_delete", argv[1]) == 0)
        return test_game_delete();

    else if (strcmp("game_print", argv[1]) == 0)
        return test_game_print();

    else if (strcmp("game_default", argv[1]) == 0)
        return test_game_default();

    else if (strcmp("game_equal", argv[1]) == 0)
        return test_game_equal();

    else if (strcmp("game_set_square", argv[1]) == 0)
        return test_game_set_square();

    else if (strcmp("game_get_number", argv[1]) == 0)
        return test_game_get_number();

    else if (strcmp("game_copy", argv[1]) == 0)
        return test_game_copy();

    return EXIT_SUCCESS;
}
