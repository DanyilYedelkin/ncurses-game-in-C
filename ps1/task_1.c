#include <superkarel.h>

void turn_right();
void turn_around();
void jump_right();
void jump_left();
void north_face();

int main()
{
    turn_on("task_1.kw");
    set_step_delay(300);

    put_beeper();
    jump_right();
   while (true)
   {
        jump_right();
        if (beepers_present())
        {
           pick_beeper();
           turn_around();
           break;
        }
    }
    while (true)
    {
       jump_left();
       if (beepers_present())
       {
           pick_beeper();
           north_face();
           turn_left();
           break;
       }
    }
 
    turn_off();
    return 0;
}

void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}

void jump_right()
{
    if (right_is_blocked())
    {
        if (front_is_clear())
        {
            step();
        } else
        {
            turn_left();
        }
    } else
    {
        turn_right();
        step();
    }
}
void turn_around()
{
    turn_left();
    turn_left();
}
void jump_left()
{
    if (left_is_blocked())
    {
        if (front_is_clear())
        {
            step();
        } else
        {
            turn_right();
        }
    } else
    {
        turn_left();
        step();
    }
}
void north_face()
{
    while (not_facing_north())
    {
        turn_left();
    }
}