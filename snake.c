#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define MAX_X 15
#define MAX_Y 15

enum DIRECTION {LEFT = -2, UP, NONE, DOWN, RIGHT};

typedef struct tail_t
{
	int x;
	int y;
} tail_t;
	
typedef struct snake_t
{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
}  snake_t;


struct snake_t initSnake(int x, int y, size_t tsize)
{
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i)
    {
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
	}
	return snake;
}

void printSnake(struct snake_t snake)
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    }
		
    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; ++i)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }
    
    for (int j = 0; j < MAX_Y; ++j)
    {
        for (int i = 0; i < MAX_X; ++i)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

snake_t move_head(snake_t snake, enum DIRECTION direction)
{
    switch (direction)
    {
    case LEFT:
        snake.x--;
        if (snake.x < 0)
        {
            snake.x = MAX_X - 1;
        }
        break;
    
    case RIGHT:
        snake.x++;
        if (snake.x >= MAX_X)
        {
            snake.x = 0;
        }
        break;
    
    case UP:
        snake.y--;
        if (snake.y < 0)
        {
            snake.y = MAX_Y - 1;
        }
        break;
    
    case DOWN:
        snake.y++;
        if (snake.y >= MAX_Y)
        {
            snake.y = 0;
        }
        break;
    }
	return snake;
}	

snake_t move(snake_t snake, enum DIRECTION direction)
{
	for (int i = snake.tsize - 1; i > 0; i--)
    {
		snake.tail[i] = snake.tail[i-1];
	}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
    return move_head(snake, direction);
}	
	
enum DIRECTION input()
{
	if ( !_kbhit() )
	{
		return NONE;
	}
	char key_code = getch();
	switch (key_code)
	{
		case 'W':
		case 'w':
			return UP;
		case 'S':
		case 's':
			return DOWN;
		case 'A':
		case 'a':
			return LEFT;
		case 'D':
		case 'd':
			return RIGHT;
		default:
			return NONE;
	}
}
	
int main()
{
	struct snake_t snake = initSnake( 10, 5, 2);
    enum DIRECTION direction = DOWN;

	printSnake(snake);
	while(1)
	{
		sleep(1);
		enum DIRECTION new_dir = input();
		if(new_dir != NONE && new_dir != -direction)
		{
			direction = new_dir;
		}
		snake = move(snake, direction);
		system("cls");
		printSnake(snake);
	}
	return 0;
}
