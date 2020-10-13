#include <superkarel.h>

void turn_right();
void beepers();
void find_and_picking();

int main()
{
    turn_on("task_6.kw");
    set_step_delay(300);
  
    find_and_picking();

    turn_off();
    return 0;
}
  
void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}
void beepers()
{
    while (no_beepers_present())
    {
        step();
    }
}
void find_and_picking()
{
    while (no_beepers_present())
    {
        beepers();
        if (beepers_present())
        {
            pick_beeper();
            while (not_facing_north())
            {
                turn_left();
            }
        }
        if (beepers_present())
        {
            pick_beeper();
            turn_left();
        }
        if (beepers_present())
        {
            pick_beeper();
            turn_left();
        }
        if (beepers_present())
        {
            pick_beeper();
            turn_left();
        }
        if (beepers_present())
        {
            pick_beeper();
            break;
        }
    }
}