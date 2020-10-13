#include <superkarel.h>

void turn_around();
void stick();
void making_stick();

int main()
{
    turn_on("task_4.kw");
    set_step_delay(300);
  
    while (beepers_in_bag())
    {
        turn_left();
        stick();
        turn_left();
        if (front_is_blocked() && right_is_blocked())
        {
            break;
        }
        step();
    }
  
    turn_off();
    return 0;
}
  
void turn_around()
{
    turn_left();
    turn_left();
}
void stick()
{
    while (beepers_in_bag())
    {
        if (beepers_present())
        {
            making_stick();
            turn_around();
            making_stick();
            break;
        }
        if (front_is_clear())
        {
            step();
        } else
        {
            turn_around();
            while (front_is_clear())
            {
                step();
            }
            break;
        }
    }
}
void making_stick()
{
    while (beepers_in_bag())
    {
        if (no_beepers_present())
        {
            put_beeper();
        }
        if (front_is_clear())
        {
            step();
        } else
        {
            break;
        }
    }
}