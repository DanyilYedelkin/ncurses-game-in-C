#include <superkarel.h>

void turn_right();
void turn_around();
void moving_and_picking();
void picking();

int main()
{
    turn_on("task_2.kw");
    set_step_delay(200);

    moving_and_picking();
  
    turn_off();
    return 0;
}
 
void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}
void turn_around()
{
    turn_left();
    turn_left();
}
void moving_and_picking()
{
    while (true)
    {
        if (front_is_clear())
        {
            step();
        } else
        {
            if (right_is_blocked() && left_is_clear())
            {
                turn_left();
            }
            if (left_is_blocked() && right_is_clear())
            {
                turn_right();
            }
        }
        if (beepers_present())
        {
            picking();
        }
        if (front_is_blocked() && left_is_blocked() && right_is_blocked())
        {
            turn_right();
            break;
        }
    }
}
void picking()
{
    if (beepers_present())
    {
        pick_beeper();
        turn_around();
    }
}