#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int collatz(const int number);
int opposite_number(const int n, const int number);
void counter(const int input_array[], const int array_size, int result_array[2]);
unsigned long sum_squared(const int line);
int array_min(const int input_array[], const int array_size);
int array_max(const int input_array[], const int array_size);
unsigned long special_counter(const int input_array[], const int array_size);
int special_numbers(const int input_array[], const int array_size, int result_array[]);

int main(){
    //Task 1: Lift a Car
    printf("-----Task 1: Lift a Car-----\n");
    printf("result of the task: ");
	printf("%.4f\n", lift_a_car(2, 80, 1400));
	printf("result of the task: ");
	printf("%.4f\n", lift_a_car(4, 90, 1650));
    printf("\n");

    //Task 2: Unit Price for Toilet Paper
    printf("-----Task 2: Unit Price for Toilet Paper-----\n");
    printf("result of the task: ");
    printf("%.4f\n", unit_price(4.79, 16, 150));
    printf("result of the task: ");
    printf("%.4f\n", unit_price(5.63, 20, 200));
    printf("\n");

    //Task 3: Collatz Conjecture
    printf("-----Task 3: Collatz Conjecture-----\n");
    printf("result of the task: ");
    printf("%d\n", collatz(20));
    printf("result of the task: ");
    printf("%d\n", collatz(35));
    printf("\n");

    //Task 4: Find Opposite Number
    printf("-----Task 4: Find Opposite Number-----\n");
    printf("result of the task: ");
    printf("%d\n", opposite_number(10, 2));
    printf("result of the task: ");
    printf("%d\n", opposite_number(12, 9));
    printf("\n");

    //Task 5: Count Numbers in Array
    printf("-----Task 5: Count Numbers in Array-----\n");
    int input_array[] = {1,2,3,4,5};
    int result_array[2];
    counter(input_array, 5, result_array);
    printf("result of the task: ");
    printf("%d %d\n", result_array[0], result_array[1]);
    printf("\n");

    //Task 6: Pascal's Triangle
    printf("-----Task 6: Pascal's Triangle-----\n");
    printf("result of the task: ");
    printf("%lu\n", sum_squared(1));
    printf("result of the task: ");
    printf("%lu\n", sum_squared(4));
    printf("result of the task: ");
    printf("%lu\n", sum_squared(33));
    printf("\n");

    //Task 7: Min-and-Max Price
    printf("-----Task 7: Min-and-Max Price-----\n");
    printf("result of the task: ");
    printf("%d\n", array_min(input_array, 5));
    printf("result of the task: ");
    printf("%d\n", array_max(input_array, 5));
    printf("result of the task: ");
    printf("%d\n", array_max(NULL, 5));
    printf("\n");

    //Task 8: Task 8: Special Counter
    printf("-----Task 8: Special Counter-----\n");
    int input_array2[] = {11,12,13,14,15};
    printf("result of the task: ");
    printf("%lu\n", special_counter(input_array2, 5));
    printf("\n");

    //Task 9:Task 9: Special Numbers
    printf("-----Task 9: Special Numbers-----\n");
    int input_array3[] = {16,17,4,3,5,2};
    int result_array3[6];
    int count = special_numbers(input_array3, 6, result_array3);
    printf("result of the task: ");
    for(int i = 0; i < count; i++){
      printf("%d ", result_array3[i]);
    }
    printf("\n");

    return 0;
}

float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    float full = (float)stick_length * (float)human_weight / ((float)human_weight + (float)car_weight);
	float result = roundf(full * 100) / 100;

	return result;
}
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    float full = (float)pack_price / ((float)rolls_count * (float)pieces_count/100);
    float result = roundf(full * 100) / 100; 
    return result;
}
int collatz(const int number){
    int typing = number;
    int attempt = 1;
    while (typing != 1){
        if(typing %2 == 0){
            typing = typing/2;
        } else{
            typing = 3*typing + 1;
        }
        attempt++;
    }
    return attempt;
}
int opposite_number(const int n, const int number){
    int half = n/2;
    int opposite;
    if(number < half){
        opposite = half + number;
    } else if(number > half){
        opposite = number - half;
    } else{
        opposite = half;
    }
    return opposite;
}
void counter(const int input_array[], const int array_size, int result_array[2]){
    result_array[0] = 0;
    result_array[1] = 0;
    for(int j = 0; j < array_size; j++){
        if (j %2 == 0){
            result_array[0] = result_array[0] + input_array[j];
        } else{
            result_array[1] = result_array[1] + input_array[j];
        }
    }
}
unsigned long sum_squared(const int line){
    unsigned long long ret = 0;
	int new_line = line + 1;
    unsigned long long row[new_line];

    int j = 0;
    while(j <= line){
        row[j] = 1;
        j++;
    }
    unsigned long long diagonal[new_line];
	for(int k = 0; k < line; k++){
		for (int i = 0; i <= line - k; i++)
		{
			if(i < line - k){
				if(i == 0){
					row[i] = 1;
				}else{
					row[i] = row[i-1] + row[i];
				}
			}
				diagonal[i] = row[i];
		}
	}
    int m = 0;
    while(m < line + 1){
        ret = ret + diagonal[m] * diagonal[m];
        m++;
    }

	return ret;
}
int array_min(const int input_array[], const int array_size){
    int small_number = 2147483647;

    if (input_array == NULL){
        return -1;
    }
    for(int j = 0; j < array_size; j++){
        if (small_number > input_array[j]){
            small_number = input_array[j];
        }
    }
    
    return small_number;
}
int array_max(const int input_array[], const int array_size){
    int big_number = 0;

    if (input_array == NULL){
        return -1;
    }
    for(int j = 0; j < array_size; j++){
        if(big_number < input_array[j]){
            big_number = input_array[j];
        }
    }
    return big_number;
}
unsigned long special_counter(const int input_array[], const int array_size){
    unsigned long sum_even_number = 0;
    unsigned long sum_odd_number = 0;
    unsigned long sum = 0;

    for(int i = 0; i < array_size; i++){
        if (i % 2 == 0){
            sum_even_number = sum_even_number + (unsigned long)input_array[i]; 
        }
        if (i % 2 != 0){
            sum_odd_number = sum_odd_number +(unsigned long)input_array[i] * (unsigned long)input_array[i];
        }
        sum = sum_even_number + sum_odd_number;
    }

        return sum;
}
int special_numbers(const int input_array[], const int array_size, int result_array[]){
    int numbers = 0;
    int i = 0;
    //int sum = 0;
    
    while(i < array_size){
        int number = input_array[i];
        int sum = 0;

        for(int j = i + 1; j < array_size; j++){
            sum = sum + input_array[j];
        }
        if (number > sum){
            result_array[numbers] = number;
            numbers++;
        }
        i++;
    }
    
    return numbers;
}