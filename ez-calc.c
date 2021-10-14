#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <math.h>


char *expression;
char *formula;
int parenthesis_count = 0, parenthesis_location[2], counter, formula_size, expression_size, sign_location = -1;

void parenthesisCalc(void){
    // search for parenthesis in the formula then forwards the expression found between the parenthesis to next priority detection
    char *expr_temp = "";
    int i = 0;

    counter = 0;

    while (counter<formula_size){
        if (formula[counter] == '('){
            parenthesis_location[0] = counter+1;
        }
        else if (formula[counter] == ')'){
            parenthesis_location[1] = counter;
            break;
        }
        counter++;
    }

    for(counter=++parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
        strcat(expr_temp, formula[counter]);
    }
    printf("%s\n", expr_temp);
    expression_size = strlen(expr_temp);
    printf("%s\n", expression);
    exponentCalc();
}

void exponentCalc(void){
    // search for exponent in the formula then replace with the result and forward to next priority detection
    printf("%s\n", expression);
    signFinder('^');
    printf("%d\n", sign_location);
    
    multiplicationCalc();
}

void multiplicationCalc(void){
    // search for multiplication in the formula then replace with the result and forward to next priority detection
    signFinder('*');
    signFinder('x');
    signFinder('X');
    printf("%d\n", sign_location);
    
    divisionCalc();
}

void divisionCalc(void){
    // search for division in the formula then replace with the result and forward to next priority detection
    signFinder('/');
    printf("%d\n", sign_location);
    
    additionCalc();
}

void additionCalc(void){
    // search for addition in the formula then replace with the result and forward to next priority detection
    signFinder('+');
    printf("%d\n", sign_location);

    substractionCalc();
}

void substractionCalc(void){
    // search for substraction in the formula then replace with the result and forward to next priority detection
    signFinder('-');
    printf("%d\n", sign_location);
    
    if (parenthesis_count == 0){
        printf("The result is %s\n", formula);
    }
    else {
        --parenthesis_count;
        parenthesisCalc();
    }
}

void parenthesisCounter(void){
    // search for parenthesis in the formula in order to get a stop condition
    int opening_parenthesis_count=0;
    int closing_parenthesis_count=0;
    int counter;

    for(counter=0; counter<formula_size; counter++){
        if (formula[counter] == 40){
            opening_parenthesis_count++;
        }
        else if (formula[counter] == 41){
            closing_parenthesis_count++;
        }
    }
    
    if (opening_parenthesis_count != closing_parenthesis_count){
        puts("Parenthesis count incorrect it won't work");
    }
    else if (opening_parenthesis_count == 0 && closing_parenthesis_count == 0){
        parenthesis_count = 0;
        exponentCalc();
    }
    else {
        parenthesis_count = opening_parenthesis_count;
        parenthesisCalc();
    }
}

void signFinder(char sign){
    counter = 0;
    printf("%s\n", expression);

    while (counter<expression_size){
        if (expression[counter] == sign){
            sign_location = counter;
            break;
        }
        else {
            counter++;
        }
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
        formula_size = strlen(formula);
        printf("The formula provided is %s\n", formula);
        parenthesisCounter();
        return 0;
    }
    else if (argc == 2){
        puts("Not yet implemented");
        return 0;
    }
}