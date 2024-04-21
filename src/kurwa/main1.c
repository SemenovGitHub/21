#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "polska_math.h"
#include "polska_parcer.h"

int main() {
    char expression[100];
        
    printf("Введите выражение в польской нотации: ");
    fgets(expression, 100, stdin);
    
    double result = polska_parcer(expression, );
    
    printf("Результат выражения %s = %.2f\n", expression, result);
    
    return 0;
}
