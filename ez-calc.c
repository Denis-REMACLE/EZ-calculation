#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *formula;
char expression[30];
int parenthesis_count = 0, parenthesis_location[2], counter, formula_size, expression_size, sign_location = -1;

void signInterpreter(char sign){
    // if the sign is found proceed with calculation then replace formula (or part of it if there is parenthesis) with expression
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
    // if we search for opening parenthesis search for both parenthesis
    if (sign == '('){
        while (counter<formula_size){
            // if opening parenthesis found add counter to location[0] keep searching for opening parenthesis
            if (formula[counter] == '('){
                parenthesis_location[0] = counter;
            }
            // else if closing parenthesis found add counter to location[1] and stop searching
            else if (formula[counter] == ')'){
                parenthesis_location[1] = counter + 1;
                break;
            }
            counter++;
        }
    }
    // If searching an operator search only for the operator
    else {
        while (counter<expression_size){
            // if operator found send to interpretation
            if (expression[counter] == sign){
                sign_location = counter;
                signInterpreter(sign);
                break;
            }
            counter++;
        }
    }
}

void priorityCalc(void){
    // search for sign in the formula then replace with the result and forward to next priority detection
    int i = 0;
    parenthesis_location[0] = -1;

    // going thru the PEMDAS order
    signFinder('(');
    // if parenthesis_location[0] is not -1 there is still parenthesis
    if (parenthesis_location[0] != -1){
        for(counter=parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    // else there is no parenthesis
    else {
        for (counter = 0; counter>formula_size; counter++){
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
        // start a recursion if there is still parenthesis
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
    
    // if parenthesis_count is odd there is an issue
    if (parenthesis_count%2 != 0){
        puts("Parenthesis count incorrect it won't work");
    }
    // else we are good to go
    else{
        parenthesis_count = parenthesis_count / 2;
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