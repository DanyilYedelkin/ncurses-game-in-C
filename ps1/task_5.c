#include <superkarel.h>

void turn_right();
void turn_around();
void putting_beepers();
void find_center();
void north_face();
void left_stand();

int main()
{
    turn_on("task_5.kw");
    set_step_delay(300);
  
    left_stand();
    putting_beepers();
    find_center();
    turn_right();
    find_center();
    north_face();

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
void putting_beepers()
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
        }
        if (front_is_blocked() && no_beepers_present())
        {
            turn_left();
            put_beeper();
            step();
        }
        if (front_is_blocked() &&  beepers_present())
        {
            turn_left();
            break;
        }
    }
}
void find_center()
{
    if (front_is_clear())
    {
        step();
        step();
        find_center();
        if (front_is_blocked())
        {
            turn_around();
        }
        step();
    }
}
void north_face()
{
    while(not_facing_north())
    {
        turn_left();
    }
}
void left_stand()
{
    north_face();
    turn_right();
    while (front_is_clear())
    {
        step();
    }
    turn_right();
    while (front_is_clear())
    {
        step();
    }
    turn_around();
}