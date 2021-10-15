#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char *formula;
char expression[30];
int parenthesis_count = 0, parenthesis_location[2], counter, formula_size, expression_size, sign_location = -1;

void signInterpreter(char sign){
    switch (sign) {
        case '^':
            puts("Exponant found !");
            break;
        case 'x':
        case 'X':
        case '*':
            puts("Multiplication found !");
            break;
        case '/':
            puts("Division found !");
            break;
        case '+':
            puts("Addition found !");
            break;
        case '-':
            puts("Substraction found !");
            break;
        default:
            break;
    }
}

void signFinder(char sign){
    counter = 0;

    if (sign == '('){
        while (counter<formula_size){
            if (formula[counter] == '('){
                parenthesis_location[0] = counter;
            }
            else if (formula[counter] == ')'){
                parenthesis_location[1] = counter + 1;
                break;
            }
            counter++;
        }
    }
    else {
        while (counter<expression_size){
            if (expression[counter] == sign){
                sign_location = counter;
                signInterpreter(sign);
                break;
            }
            else {
                counter++;
            }
        }
    }
}

void priorityCalc(void){
    // search for sign in the formula then replace with the result and forward to next priority detection
    int i = 0;
    parenthesis_location[0] = -1;

    signFinder('(');
    if (parenthesis_location[0] != -1){
        for(counter=parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    expression_size = strlen(expression);

    signFinder('^');
    signFinder('*');
    signFinder('x');
    signFinder('X');
    signFinder('/');
    signFinder('+');
    signFinder('-');
    
    
    if (parenthesis_count == 0){
        printf("The result is %s\n", formula);
    }
    else {
        --parenthesis_count;
        priorityCalc();
    }
}

void parenthesisCounter(void){
    // search for parenthesis in the formula in order to get a stop condition
    for(counter=0; counter<formula_size; counter++){
        if (formula[counter] == '(' || formula[counter] == ')'){
            parenthesis_count++;
        }
    }
    
    if (parenthesis_count%2 != 0){
        puts("Parenthesis count incorrect it won't work");
    }
    else{
        parenthesis_count = parenthesis_count / 2;
        if (parenthesis_count == 0){
            for (counter = 0; counter>formula_size; counter++){
                expression[counter] = formula[counter];
            }
        }
        priorityCalc();
    }
}

int main(int argc, char **argv){
    if (argc > 3){
        puts("Too many args");
        return 1;
    }
    else if (argc == 1) {
        puts("Not yet implemented");
        return 0;
    }
    else if (argc == 2) {
        formula = argv[1];
        formula_size = strlen(argv[1]);
        printf("The formula provided is %s\n", formula);
        parenthesisCounter();
        return 0;
    }
    else if (argc == 2){
        puts("Not yet implemented");
        return 0;
    }
}