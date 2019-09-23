#include <stdio.h>
#include <stdlib.h>

/**
 *  File:                   IntegerOverflow.c
 *  CWE-190:                Integer Overflow
 *  Description:            This is an example of an Integer Overflow vulnerability written in C. 
 *                          This program will add two numbers together and output its solution. 
 *                          If a user enters in a value that has a total greater than the max 
 *                          value of an integer data type (2147483647), it will overflow the variable and return a negative number.
 * 
*/

void AdditionFunction(int number1, int number2){
    int solution = number1 + number2;
    
    printf("\n\n%d + %d = %d\n", number1, number2, solution);  

    printf("your total is %d\n", solution); // Solutions that are greater than 2147483647 it will overflow the "solution" integer variable. 
}


void SubtractionFunction(int number1, int number2){
    int solution = number1 - number2;
    
    printf("\n\n%d - %d = %d\n", number1, number2, solution);  
    printf("your total is %d", solution); // Solutions that are greater than 2147483647 it will overflow the "solution" integer variable. 
}

int isOverflow(int result, int previousResult)
{
    if (abs(result) < 10)
    {
        return 0;
    }

    int remainForOverflowCheck = (abs(result) - previousResult) % 10;

    if (remainForOverflowCheck > 0)
    {
        return 1;
    }

    return 0;
}

int reverse(int x)
{
    int abs_x = (int)abs(x);

    int result = 0;
    int previousResult = 0;
    int logFrom10 = floor(log10((double)abs_x)); // 計算輸入值之於10的對數天花板

    int i = pow(10, logFrom10);
    int currentMutiplier = 1;

    while (i >= 1)
    {
        previousResult = result;
        int currentRemain = abs_x % i;
        result += (abs_x - currentRemain) / i * currentMutiplier;

        if (isOverflow(result, previousResult))
        {
            result = 0;
            break;
        }

        i /= 10;
        abs_x = currentRemain;
        currentMutiplier *= 10;
    }

    if (x < 0)
    {
        result = result * -1;
    }

    return result;
}


int main()
{
     int result = reverse(2147483647);

    int n1, n2;
    int selection;
    
    printf ("\033[32;1m [*] Hello, This is a basic calculator that either Adds or Subtracts two numbers together.  \033[0m\n");

    printf ("\033[32;1m [*] Please Enter Number 1:  \033[0m\n");
    scanf("%d", &n1);
    
    printf ("\033[32;1m [*] Please Enter Number 2:  \033[0m\n");
    scanf("%d", &n2);
    
    //Selection Mathmatical Operation
    printf ("\n\033[32;1m [*] Press 1 - Addition\n [*] Press 2 - Subtraction\033[0m\n");
    scanf("%d", &selection);
    
    
    if (selection == 1){
        AdditionFunction(n1, n2);

    
        
    } else if (selection == 2){
        SubtractionFunction(n1, n2);
    
        
    } else {
        printf ("\033[31;1m [*] ERROR!  \033[0m\n");
        printf ("\033[31;1m [*] No option was selected.  \033[0m\n");
        printf ("\033[31;1m [*] Program is exiting.  \033[0m\n");

        return 0;
    }
}