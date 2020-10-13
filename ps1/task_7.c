#include <superkarel.h>

void turn_right();
void turn_around();
void make_floor();
void find_holes();
void check_holes();
   
int main()
{
    turn_on("task_7.kw");
    set_step_delay(300);
  
    make_floor();
    while (front_is_clear())
    {
        find_holes();
        check_holes();
        if (front_is_blocked())
        {
            break;
        }
    }
    turn_around();
    while (front_is_clear() && beepers_present())
    {
        while (beepers_present())
        {
            pick_beeper();
        }
        step();
        if (front_is_blocked())
        {
            turn_around();
            while (beepers_present())
            {
                pick_beeper();
            }
            while (front_is_clear())
            {
                step();
            }
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
void turn_around()
{  
    turn_left();
    turn_left();
}
void make_floor()
{
    while (beepers_in_bag())
    {
        put_beeper();
        put_beeper();
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
            turn_around();
            break;
        }
    }
}
void find_holes()
{
    while (beepers_in_bag())
    {
        if (left_is_clear())
        {
            turn_left();
            break;
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
void check_holes()
{
    if (front_is_blocked())
    {
        return;
    }
    step();
    put_beeper();
    while (beepers_in_bag())
    {
        if (left_is_clear())
        {
            turn_left();
            step();
        } else
        {
            if (front_is_clear())
            {
                step();
            } else
            {
                turn_right();
            }
        }
        if (beepers_present())
        {
            pick_beeper();
            if (beepers_present())
            {
                put_beeper();
                turn_around();
                step();
                put_beeper();
                turn_around();
                step();
                turn_left();
                if (front_is_clear())
                {
                    step();
                }
            } else
            {
                step();
                turn_left();
                if (front_is_clear())
                {
                    step();
                }
            }
            break;
        }
    }
}