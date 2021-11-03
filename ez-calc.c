#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char expression[100], formula[100], sign;
int parenthesis_location[2], formula_size, expression_size, sign_location = 0, number_one_length, number_two_length;
float number_one, number_two, result, remain = 0;

void errorCheck(void) {
    if (sign != '|') {
        if (number_one_length == 0 || number_two_length == 0){
            puts("You cannot operate without numbers");
            exit(4);
        }
    }
    else {
        if (number_two_length == 0){
            puts("You cannot operate without numbers");
            exit(4);
        }
        else if (number_one_length != 0) {
            puts("You cannot put a number before a '|'");
            exit(2);
        }
    }

    if (sign == '/' || sign == '%') {
        if (number_one == 0 || number_two == 0){
            puts("You cannot divide by 0");
            exit(3);
        }
    }

}

void parenthesisReplacer(void) {
    char tmp_formula[100];
    int counter = 0, i = 0, f = 0, supposed_length, result_length;
    counter = 0;
    // Calculate the future length of the formula
    result_length = strlen(expression);
    supposed_length = formula_size - expression_size + result_length;

    while (counter < supposed_length) {

	    // if the character should be changed then get it from the expression
	    if (counter >= parenthesis_location[0] && f != result_length){
                if (expression[f] == '('){
                    ++f;
                }
                else if (expression[f] == ')'){
                    ++f;
                    i = i + expression_size;
                }
                else{
                    tmp_formula[counter++] = expression[f++];
                }
            } else {
		// if the character doesn't need to be changed
                tmp_formula[counter++] = formula[i++];
            }
        }
    tmp_formula[counter++] = '\0';

    // put tmp_expression into expression
    for (counter = 0; counter <= 100; counter++) {
        formula[counter] = tmp_formula[counter];
    }
}

void expressionRewriter(void) {
    char tmp_expression[100], str_result[100];
    int counter = 0, i = 0, f = 0, supposed_length, result_length;
    // Convert float result into a string
    sprintf(str_result, "%.2f", result);
    result_length = strlen(str_result);
    // Calculate the future length of the expression
    supposed_length = (strlen(expression) + strlen(str_result) + 1 ) - ( number_one_length + number_two_length);

    while (counter < supposed_length) {
        // if the character doesn't need to be changed then put it in tmp_expression
        if (counter < (sign_location - number_one_length) || f == result_length + 1){
            tmp_expression[counter++] = expression[i++];
        }
        // if the character should be changed then get it from the result
        else if (counter >= (sign_location - number_one_length) && f != result_length){
            if (str_result[f] == '-'){
                tmp_expression[counter++] = 'n';
		f++;
            }
            else {
            tmp_expression[counter++] = str_result[f++];
            }
        }
        // if the result has been fully put in place continue putting from the expression
        else if (f == result_length){
            f++;
            i = i + number_one_length + number_two_length + 1;
        }
    }
    // put tmp_expression into expression
    for (counter = 0; counter <= 100; counter++) {
        expression[counter] = tmp_expression[counter];
    }
}

void numberFinder(void) {
    char number[100];
    int counter = 0, i = 0;
    // loop through the expression

    for (counter = 0; counter <= expression_size; counter++){
        if (counter <= sign_location){
	    // if sign location not attained put data in number
            if ((expression[counter] >= '0' && expression[counter] <= '9') || expression[counter] == '.'){
                number[i++] = expression[counter];
            } else if (expression[counter] == ','){
                number[i++] = '.';
            } else if (expression[counter] == 'n' || expression[counter] == 'N'){
                number[i++] = '-';
            } else if (expression[counter] == sign) {
                // if sign is hit put the number 
		number[i++] = '\0';
                number_one_length = strlen(number);
                number_one = atof(number);
                i = 0;
		// then restart i
            } else {
                // if a character should be not be put restart i
		i = 0;
            }
        }
        else if (counter > sign_location){
	    // put characters in number until a non valid sign is hit
            if ((expression[counter] >= '0' && expression[counter] <= '9') || expression[counter] == '.') {
		number[i++] = expression[counter];
            } else if (expression[counter] == ','){
                number[i++] = '.';
            } else if (expression[counter] == 'n' || expression[counter] == 'N'){
                number[i++] = '-';
            } else {
		break;
	    }
	}
    }
    number[i++] = '\0';
    number_two_length = strlen(number);
    number_two = atof(number);
}

void signInterpreter(void) {
    // if the sign is found proceed with calculation then replace part of the expression
    numberFinder();
    errorCheck();
    switch (sign) {
        case '^':
            result = powf(number_one, number_two);
            remain = 0;
            break;
        case '|':
            result = sqrt(number_two);
            remain = 0;
            break;
        case 'x':
        case 'X':
        case '*':
            result = number_one * number_two;
            remain = 0;
            break;
        case '/':
            result = number_one / number_two;
            remain = 0;
            break;
        case '%':
            result = number_one / number_two;
            remain = fmod(number_one, number_two);
            break;
        case '+':
            result = number_one + number_two;
            remain = 0;
            break;
        case '-':
            result = number_one - number_two;
            remain = 0;
            break;
        default:
            break;
    }
    printf("Calculating : %s\n", expression);
    expressionRewriter();
    printf("Resulting : %s\n\n", expression);
}

void signFinder(char *tab) {
    int i = 0, tab_len = strlen(tab);
    int counter = 0;
    // if we search for opening parenthesis search for both parenthesis
    if (tab[0] == '('){
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
            for (i = 0; i < tab_len; i++){
                if (expression[counter] == tab[i]) {
		    sign = tab[i];
                    sign_location = counter;
                    signInterpreter();
		    counter = 0;
                }
	    }
            counter++;
        }
    }
}

void priorityCalc(int parenthesis_count) {
    int counter = 0;
    // search for sign in the formula then replace with the result and forward to next priority detection
    char sign_tab_parenthesis[2] = {'(', '\0'};
    char sign_tab_exponant[3] = {'^', '|', '\0'};
    char sign_tab_multiplication[6] = {'x', 'X', '*', '/', '%', '\0'};
    char sign_tab_addition[3] = {'+', '-', '\0'};
    int i = 0;
    parenthesis_location[0] = -1;

    // going thru the PEMDAS order
    signFinder(sign_tab_parenthesis);
    // if parenthesis_location[0] is not -1 there is still parenthesis
    if (parenthesis_location[0] != -1){
        for(counter=parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    // else there is no parenthesis
    else {
        for (counter = 0; counter<formula_size; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    expression_size = strlen(expression);
    signFinder(sign_tab_exponant);
    signFinder(sign_tab_multiplication);
    signFinder(sign_tab_addition);

    if (parenthesis_count == 0){
        if (remain == 0){
            printf("The result is %.2f\n", result);
        }
        else{
            printf("The result is %.2f and remainder is %.0f\n", result, remain);
        }
    }
    else {
        // start a recursion if there is still parenthesis
        parenthesisReplacer();
        priorityCalc(--parenthesis_count);
    }
}

void parenthesisCounter(void) {
    int parenthesis_count = 0, counter = 0;
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
        priorityCalc(parenthesis_count/2);
    }
}

int main(int argc, char **argv) {
    char authorized_char[27] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '.', ',', '(', ')', 'n', 'N', '^', '|', 'x', 'X', '*', '/', '%', '+', '-', '\0'};
    int counter = 0, good = 0, i;
    if (argc != 2){
        puts("You need to use the command like ./calc \"formula\"");
        return 1;
    }
    else if (argc == 2) {
       // if help is asked show help                                           
       if (argv[1][0] == '-' && (argv[1][1] == 'H' || argv[1][1] == 'h')){     
            puts("In order to calculate some thing you must write your command like this : ");
            puts("./calc \"2+2\"");                                             
            puts("Authorized character are the numbers, parenthesis and operands.");
            puts("In order to mark a negative number you need to use a \"n\" before it");
            puts("In order to get the square root of a number put a \"|\" before it");
            puts("In order to get the power of a number use \"^\" as an operand");
            puts("In order to get the remain of an euclidean division use \"\%\" as an operand");
            return 0;                                                           
        }                 
        formula_size = strlen(argv[1]);
        for(counter=0; counter<formula_size; counter++){
            for (i = 0; i < 27 ; i++){
		// check for unauthorized characters
                if (argv[1][counter] == authorized_char[i]){
                    good = 1;
                }
            }
            if (good != 1){
		// if an unauthorised character show that there is a problem
                puts("You inputed a wrong character !");
                exit(1);
            } else {
		// else update formula
                if (formula[counter] != ' '){
                    formula[counter] = argv[1][counter];
                }
                good = 0;
            }
        }
        formula[formula_size+1] = '\0';
        printf("The formula provided is %s\n\n", formula);
        parenthesisCounter();
        return 0;
    }
}
