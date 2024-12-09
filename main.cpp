

//
//   The Main Project 
//
//

#include <iostream>
#include <raylib.h>

using namespace std;

bool paused = false;

Color re_ball = Color{ 255,55,225,150 };
Color green = Color{ 25,255,55,150 };
Color dark_blue = Color{ 59,87, 105, 255 };
Color ashley_blue = Color{ 55,85, 110, 255 };
Color teal = Color{ 42, 180, 152, 255 };
Color Yellow = Color{ 243, 213, 91, 255 };



int kp = 0, kc = 0;
int re_hit = 0;
int hit = 0;
int player_score = 0;
int bot_score = 0;
int speed1 = 4;
int speed2 = 4;
int speed3 = 4;
int speed4 = 4;
int speed5 = 4;
int speed6 = 4;
const float increase = 1.5;
const char* winner = NULL;
char name[20];




class Teleport {
public:

    int x1, y1, radius1;
    int x2, y2, radius2;
    int x3, y3, radius3;
    int x4, y4, radius4;
    void Draw() {
        DrawCircle(x1, y1, radius1, BLACK);
        DrawCircle(x2, y2, radius2, BLACK);
        DrawCircle(x3, y3, radius3, BLACK);
        DrawCircle(x4, y4, radius4, BLACK);
    }

};
Teleport tel;

class RewardBall {
public:
    float re_x, re_y;
    int re_speed_x, re_speed_y;
    int re_radius;
    int z = GetRandomValue(1, 100) % 5;
    void Draw() {
        if (z <= 2)
        {
            DrawCircle(re_x, re_y, re_radius, re_ball);
        }
        else {
            DrawCircle(re_x, re_y, re_radius, green);
        }
    }

    void Update() {
        re_x += re_speed_x;
        re_y += re_speed_y;



        if (re_y + re_radius >= GetScreenHeight() || re_y - re_radius <= 0)
        {
            re_speed_y *= -1;

        }if ((re_x + re_radius >= GetScreenWidth()) || re_hit)
        {
            if (re_x + re_radius >= GetScreenWidth())
            {
                kc = 0;
                kp = 0;
            }
            re_hit = 0;
            z = GetRandomValue(1, 100) % 5;
            ResetBall();
        }

        if ((re_x - re_radius <= 0) || re_hit)
        {
            if (re_x - re_radius <= 0)
            {
                kc = 0;
                kp = 0;
            }

            re_hit = 0;
            z = GetRandomValue(1, 100) % 5;
            ResetBall();
        }
    }

    void ResetBall() {
        // i can generate the reward ball for any where i want 
        // by using random values just like i used in the direction of speed (hopefully next day!!)
        re_hit = 0;
        int pos_choices1[14] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        int pos_choices2[3] = { 2,3,4 };
        int t = GetRandomValue(1, 2);
        if (t == 1)
        {
            re_x = GetScreenWidth() / pos_choices1[GetRandomValue(0, 13)];
            re_y = GetScreenHeight() / pos_choices1[GetRandomValue(0, 13)];
        }
        else
        {
            re_x = GetScreenWidth() / pos_choices1[GetRandomValue(0, 13)] * pos_choices2[GetRandomValue(0, 2)];
            re_y = GetScreenHeight() / pos_choices1[GetRandomValue(0, 13)] * pos_choices2[GetRandomValue(0, 2)];

        }

        
        int speed_choices[2] = { -1,1 };
        re_speed_x *= speed_choices[GetRandomValue(0, 1)];
        re_speed_y *= speed_choices[GetRandomValue(0, 1)];
    }

};
RewardBall rewardball;


class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        if (hit == 3)
        {
            DrawCircle(x, y, radius, ORANGE);
        }
        else {
            DrawCircle(x, y, radius, Yellow);
        }
    
    }

    void Update() {
        x += speed_x;
        y += speed_y;


        if ((x + radius <= tel.x1 + tel.radius1) && (x - radius >= tel.x1 - tel.radius1) && (y + radius <= tel.y1 + tel.radius1) && (y - radius >= tel.y1 - tel.radius1))
        {
            //tc = 0;
            //int v1[4] = { tel.x1,tel.x2,tel.x3,tel.x4 };
            //int v2[4] = { tel.y1,tel.y2,tel.y3,tel.y4 };
            //int s = GetRandomValue(0, 3);
            //x = v1[s];
            //y = v2[s];
            x = tel.x2;
            y = tel.y2;
        }
        if ((x + radius <= tel.x4 + tel.radius4) && (x - radius >= tel.x4 - tel.radius4) && (y + radius <= tel.y4 + tel.radius4) && (y - radius >= tel.y4 - tel.radius4))
        {
            //tc = 0;
            //int v1[4] = { tel.x1,tel.x2,tel.x3,tel.x4 };
            //int v2[4] = { tel.y1,tel.y2,tel.y3,tel.y4 };
            //int s = GetRandomValue(0, 3);
            //x = v1[s];
            //y = v2[s];
            x = tel.x3;
            y = tel.y3;
        }

        if (hit == 3)
        {
            y += (1.0005 * speed_y);
            x += (1.0005 * speed_x);

        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) // bot will get some marks
        {
            bot_score++;
            hit = 0;
            if (bot_score==5)
            {
                winner = "BOT wins";
                bot_score = 0;
                player_score = 0;
                hit = 0;
                ResetBall();
            }
           
            ResetBall();
        }
        if (x - radius <= 0) // player will get some marks
        {
            player_score++;
            hit = 0;
            if (player_score==5)
            {
                winner = "Player wins";
                player_score = 0;
                bot_score = 0;
                hit = 0;
                ResetBall();
            }
            
            ResetBall();
        }

    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        hit = 0;
        int speed_choices[2] = { 1, -1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }

        LimitMovement();
    }
};

class CPU_Paddle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y = y - speed;
        }
        else {
            y = y + speed;
        }

        LimitMovement();
    }
};

class Obstacle {
public:
    float x = 640 + 180, y = 100, width, height;
    float x1 = x + 20, y1 = y + 500, x2 = x - 650, y2 = y + 100, x3 = x - 500, y3 = y + 600, x4 = x - 325, y4 = y + 225, x5 = x - 285, y5 = y + 550;
    void Draw() {
        //right obs
        DrawRectangle(x, y, width, height, RED);
        DrawRectangle(x1, y1, width, height, RED);
        //left obs
        DrawRectangle(x2, y2, width, height, RED);
        DrawRectangle(x3, y3, width, height, RED);
        //middle obs
        DrawRectangle(x4, y4, width, height, RED);
        DrawRectangle(x5, y5, width, height, RED);
    }
public:



    void LimitMoveofObs(float y) {

        if (y <= 0)
        {
            y = 0;
        }if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }

    }
public:
    void Update() {

        y += speed1;
        y1 += speed2;
        y2 += speed3;
        y3 += speed4;
        y4 += speed5;
        y5 += speed6;

        if (y + height >= GetScreenHeight() || y - height <= 0)
        {
            speed1 *= -1;

        }

        if (y1 + height >= GetScreenHeight() || y1 - height <= 0)
        {
            speed2 *= -1;

        }
        if (y2 + height >= GetScreenHeight() || y2 - height <= 0)
        {
            speed3 *= -1;

        }
        if (y3 + height >= GetScreenHeight() || y3 - height <= 0)
        {
            speed4 *= -1;

        }
        if (y4 + height >= GetScreenHeight() || y4 - height <= 0)
        {
            speed5 *= -1;

        }
        if (y5 + height >= GetScreenHeight() || y5 - height <= 0)
        {
            speed6 *= -1;

        }

        LimitMoveofObs(y);
        LimitMoveofObs(y1);
        LimitMoveofObs(y2);
        LimitMoveofObs(y3);
        LimitMoveofObs(y4);
        LimitMoveofObs(y5);

    }


};
Obstacle obs;

Ball ball;
Paddle player;
CPU_Paddle bot;

int main() {


    cout << "Game started\n" << endl;
    cout << "Enter your name: ";
    scanf_s("%s", name);
    for (int i = 0; name[i] != '\0'; i++) {
        name[i] = toupper(name[i]);
    }


    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "The pong game!");
    SetTargetFPS(60);
    //initialiazing teleportation things

    tel.x1 = 420;
    tel.y1 = 150;
    tel.radius1 = 50;
    tel.x2 = 420;
    tel.y2 = 650;
    tel.radius2 = 50;
    tel.x3 = 720;
    tel.y3 = 150;
    tel.radius3 = 50;
    tel.x4 = 720;
    tel.y4 = 650;
    tel.radius4 = 50;

    //initializing reward ball things
    rewardball.re_radius = 40;
    rewardball.re_x = screen_width / 2;
    rewardball.re_y = screen_height / 2;
    rewardball.re_speed_x = 5;
    rewardball.re_speed_y = 5;

    // Initializing Ball things
    ball.x = screen_width / 2.0;
    ball.y = screen_height / 2.0;
    ball.radius = 20;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Initializing Player things
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    // Initializing Bot things
    bot.width = 25;
    bot.height = 120;
    bot.x = 10;
    bot.y = screen_height / 2 - bot.height / 2;
    bot.speed = 6;
    //obstacle things
    obs.x = screen_width / 2 + 180;
    obs.y = 100;
    obs.width = 30;
    obs.height = 60;

    

    while (WindowShouldClose() == false) {
        BeginDrawing();

        if (IsKeyPressed(KEY_SPACE))
        {
            paused = !paused;
        }
        // Updating
        if (!winner && !paused) {
            ball.Update();
            if (!kc)
            {
                player.Update();
            }
            if (!kp)
            {
                bot.Update(ball.y);
            }

            rewardball.Update();
            obs.Update();
        }

        if (winner && IsKeyPressed(KEY_ENTER)) {
            winner = NULL;
        }


        // Check if there is a collision 

        // collision between player and the ball
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
            hit += 1;
            ball.speed_x *= -1;
            
        }

        //collision between bot and the ball
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ bot.x, bot.y, bot.width, bot.height })) {
            hit += 1;
            ball.speed_x *= -1;
           
        }

        //collision between obstacles and ball
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x,obs.y,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
           

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x1,obs.y1,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
          

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x2,obs.y2,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
           

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x3,obs.y3,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
           

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x4,obs.y4,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
           

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ obs.x5,obs.y5,obs.width,obs.height }))
        {

            ball.speed_x *= -1;
           
        }

        //collision with paddles and reward ball

        if (CheckCollisionCircleRec(Vector2{ rewardball.re_x,rewardball.re_y }, rewardball.re_radius, Rectangle{ player.x,player.y,player.width,player.height }))
        {

            re_hit = 1;
            if (kp == 1)
            {
                kp = 0;
                kc = 0;
            }
            else
            {
                kp = 1;
                kc = 0;
            }

        }

        if (CheckCollisionCircleRec(Vector2{ rewardball.re_x,rewardball.re_y }, rewardball.re_radius, Rectangle{ bot.x,bot.y,bot.width,bot.height }))
        {
            re_hit = 2;
            if (kc == 1)
            {
                kc = 0;
                kp = 0;
            }
            else {
                kc = 1;
                kp = 0;
            }



        }




        // Drwaring 
        ClearBackground(ashley_blue);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, dark_blue);
        DrawCircle(screen_width / 2, screen_height / 2, 150, teal);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        ball.Draw();
        tel.Draw();
        obs.Draw();
        rewardball.Draw();
        bot.Draw();
        player.Draw();

        DrawText("BOT", 40, 10, 80, WHITE);
        DrawText(TextFormat("%i", bot_score), screen_width / 2 - 150, 20, 80, WHITE);
        DrawText(name, screen_width / 2 + 40, 10, 80, WHITE);
        DrawText(TextFormat("%i", player_score), screen_width - 150, 20, 80, WHITE);
        if (winner) {
            int winner_width = MeasureText(winner, 120);
            const  char* StartAgain = "Press enter key to start again or press Esc to exit...";
            int StartAgain_width = MeasureText(StartAgain, 25);

            DrawText(winner, screen_width / 2 - winner_width / 2, screen_height / 2 - 60, 120, YELLOW);
            DrawText(StartAgain, screen_width / 2 - StartAgain_width / 2, screen_height / 2 + 120, 25, BLACK);
            // winner = NULL;
        }

        if (paused)
        {
            DrawText("Paused", 300, 300, 180, BROWN);
        }


        EndDrawing();
    }
   

    CloseWindow();

    return 0;
}
