//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 525
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc, char *argv[])
{
    // Toggle God mode
    bool god = false;
    
    if (argc == 2)
    {
        printf("%s\n", argv[1]);
        god = true;
    }
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    GLine line;

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // click to start game
    waitForClick(); 
    
    // declare x & y velocities
    double x_velocity = 1.7;
    double y_velocity = 1.3;
    
    bool ballMove = false;
    bool paddleMove = false;
    
    // GOD mode argument
    char *key = argv[1];
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
        // God Mode
        if (god == true)
        {
            double y = getY(paddle);
            setLocation(paddle, getX(ball) - (getWidth(paddle) / 2), y);
        }
        // Paddle follow mouse
        GEvent click = getNextEvent(MOUSE_EVENT);
        
        // If mouse clicked
        if (click != NULL)
        {
            if (getEventType(click) == MOUSE_CLICKED)
            {
                ballMove = true;
                updateScoreboard(window, label, points);
            }
            
            if (getEventType(click) == MOUSE_MOVED && ballMove == true)
            {     
                double y = getY(paddle);
                
                if (getX(click) <= getWidth(paddle) / 2)
                { 
                    paddleMove = true;           
                    setLocation(paddle, 0, y);
                }
                else if (getX(click) + getWidth(paddle) >= getWidth(window))
                {
                    paddleMove = true;
                    setLocation(paddle, getWidth(window) - getWidth(paddle), y);
                }
                else 
                {   
                    paddleMove = true;
                    double x = getX(click) - getWidth(paddle) / 2;
                    setLocation(paddle, x, y);
                }
            }
        }
        
        if (ballMove == true)
        {
            move(ball, x_velocity, y_velocity);
            
            if (getX(ball) <= 0)
            {
                x_velocity = -x_velocity;
            }
            else if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                x_velocity = -x_velocity;
            }
            else if (getY(ball) <= 0)
            {
                y_velocity = -y_velocity;
            }
            else if (getY(ball) >= getHeight(window))
            {
                lives -= 1;
                ballMove = false;
                setLocation(ball, (WIDTH - getWidth(ball)) / 2, HEIGHT / 2);
            }
        }
        pause(10);
        
        // Collission with objects
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                y_velocity = -y_velocity;
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                y_velocity = -y_velocity + .2;
                removeGWindow(window, object);
                points += 1;
                updateScoreboard(window, label, points);
              
                // Ball hits first row (cyan)
                if (points > 20)
                {
                    removeGWindow(window, paddle);
                    paddle = newGRect(getX(ball), 514, 50, 12);
                    setColor(paddle, "blue");
                    setFilled(paddle, true);
                    add(window, paddle);
                    setColor(ball, "yellow"); // Change ball color to yellow
                }
                if (points > 40)
                {
                    removeGWindow(window, paddle);
                    paddle = newGRect(getX(ball), 514, 30, 12);
                    setColor(paddle, "magenta");
                    setFilled(paddle, true);
                    add(window, paddle);
                    setColor(ball, "red"); // Change ball color to red
                }              
            }
        }    
    }
    
    if (points == COLS * ROWS)
    {
        GLabel gameOver = newGLabel("YOU WIN");
        setFont(gameOver, "SansSerif-30");
        setColor(gameOver, "gray");
        add(window, gameOver);
        setLocation(gameOver, (WIDTH - getWidth(gameOver)) / 2, HEIGHT / 2);
        
        removeGWindow(window, label);
        removeGWindow(window, ball);
    }
    else if (lives == 0)
    {
        GLabel gameOver = newGLabel("GAME OVER");
        setFont(gameOver, "SansSerif-30");
        setColor(gameOver, "gray");
        add(window, gameOver);
        setLocation(gameOver, (WIDTH - getWidth(gameOver)) / 2, HEIGHT / 2);
        
        removeGWindow(window, label);
        removeGWindow(window, ball);
    } 
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
        // Starting point of bricks on Y axis
        int brick_y = 35;

        for (int i = 0; i < ROWS; i++)
        {
            // Starting point of bricks on X axis
            int brick_x = 6;
            for (int j = 0; j < COLS; j++)
            {
                GRect brick = newGRect(brick_x, brick_y, 35, 10);
                setFilled(brick, true);
                add(window, brick);
                brick_x += 39;
                
                if (i == 0)
                    setColor(brick, "red");
                else if (i == 1)
                    setColor(brick, "orange");
                else if (i == 2)
                    setColor(brick, "yellow");
                else if (i == 3)
                    setColor(brick, "green");
                else if (i == 4)
                    setColor(brick, "cyan");
            }
            brick_y += 20;
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instatiate black ball and add to window
    GOval ball = newGOval(((WIDTH - 20) / 2), (HEIGHT / 2), 20, 20);
    setColor(ball, "black");
    setFilled(ball, true);
    add(window, ball);
   
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(((WIDTH - 80) / 2), 514, 80, 12);
    add(window, paddle);
    setFilled(paddle, true);
    setColor(paddle, "blue");
     
    return paddle;    
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "gray");
    add(window, label);
         
    // Center scoreboard
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
       
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // Update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // Center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
