#include <superkarel.h> 

void turn_right();
void turn_around();
void floor_cleaning();
void floor_making();
void turning();
void run_forest_run();

int main()
{
    turn_on("task_3.kw");
    set_step_delay(90);
  
    while (true)
    {
        floor_cleaning();
        turn_around();
        floor_making();
        turning();
        if (front_is_clear())
        {
            break;
        }
    }
    while (front_is_clear())
    {
        floor_cleaning();
        turn_around();
        floor_making();
        turning();
        if (front_is_blocked() && right_is_blocked())
        {
            turn_left();
            break;
        }
    }
  
    run_forest_run();
  
    turn_off();
    return 0;
}
  
void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}
void floor_cleaning()
{
    while (true)
    {
        if (beepers_present())
        {
            pick_beeper();
            if (front_is_blocked())
            {
                break;
            }
        } else
        {
            if (front_is_clear())
            {
                step();
            } else
            {
                break;
            }
        }
    }
}
void floor_making()
{
    while (true)
    {
        turn_right();
        if (front_is_clear() && beepers_in_bag())
        {
            step ();
            if (beepers_present())
            {
                turn_around();
                step();
                put_beeper();
            }
            if (no_beepers_present())
            {
                turn_around();
                step();
            }
            turn_right();
            if (front_is_clear())
            {
                step();
            }
            if (front_is_blocked())
            {
                break;
            }
        } else
        {
            turn_left();
            if (beepers_in_bag())
            {
                put_beeper();
            }
            if (front_is_blocked() && no_beepers_in_bag())
            {
                break;
            }
            step();
            while (true)
            {
                turn_right();
                if (front_is_blocked() && beepers_in_bag())
                {
                    turn_left();
                    put_beeper();
                    step();
                } else
                {
                    turn_left();
                    if (front_is_clear())
                    {
                        step();
                    }
                }
                if (front_is_blocked() && no_beepers_in_bag())
                {
                    break;
                }
            }
        }
        if (front_is_blocked() && no_beepers_in_bag())
        {
            break;
        }
    }
}
void turning()
{
    while (true)
    {
        if (facing_east())
        {
            turn_right();
            step();
            turn_right();
            if (front_is_clear())
            {
                break;
            }
        }
        if (facing_west())
        {
            turn_left();
            if (front_is_blocked() && right_is_blocked())
            {
                break;
            }
            step();
            turn_left();
            if (front_is_clear())
            {
                break;
            }
        }
    }
}
void turn_around()
{ 
    turn_left();
    turn_left();
}
void run_forest_run()
{
    while (front_is_clear())
    {
        step();
    }
    if (front_is_blocked() && right_is_blocked())
    {
        turn_left();
    }
    while (front_is_clear())
    {
        step();
    }
 
    if (beepers_present())
    {
        turn_left();
        while (front_is_clear())
        {
           step();
        }
    } else
    {
       turn_left();
       while (true)
       {
            if (no_beepers_present())
            {
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
                    turn_right();
                    step();
                    turn_right();
                }
            } else
            {
                while(front_is_clear())
                {
                    step();
                }
                break;
            }
        }
    }
    turn_around();
} 