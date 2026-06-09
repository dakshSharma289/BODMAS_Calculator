#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

bool isNum(char input){
    if(input == '+'){
        return false;
    }else if(input == '-'){
        return false;
    }else if(input == 'x'){
        return false;
    }else if(input == '/'){
        return false;
    }else if(input == '('){
        return false;
    }else if(input == ')'){
        return false;
    }else{
        return true;
    }
}

bool notNumber(string input){
    for(int i = 0; i < input.length(); i++){
        if(!isNum(input[i])){
            return true;
        }
    }
    return false;
}

string resolveBODMAS(string input){
    while(notNumber(input)){
        int operatorPos = 0;
        char opp = 'n';
        int firstOperandPos = 0;
        int secondOperandPos = input.length();
        string firstOperand;
        string secondOperand;
        string result;
        for(int i = 0; i < input.length(); i++){
            if(input[i] == 'x'){
                operatorPos = i;
                opp = 'x';
                break;
            }
            if(input[i] == '/'){
                operatorPos = i;
                opp = '/';
                break;
            }
        }
        if(opp != 'n'){
                for(int i = operatorPos - 1; i > -1; i--){
                    if(!isNum(input[i])){
                        break;
                }
                firstOperandPos = i;
            }

            firstOperand = input.substr(firstOperandPos, operatorPos - firstOperandPos);
            
            for(int i = operatorPos + 1; i < input.length(); i++){
                    if(!isNum(input[i])){
                        break;
                }
                secondOperandPos = i;
            }
            secondOperand = input.substr(operatorPos + 1, secondOperandPos - operatorPos);

            if(opp == 'x'){
                result = to_string(stod(firstOperand) * stod(secondOperand));
            }
            if(opp == '/'){
                result = to_string(stod(firstOperand) / stod(secondOperand));
            }
            input = input.replace(firstOperandPos, secondOperandPos - firstOperandPos + 1, result);
            continue;
        }
        for(int i = 0; i < input.length(); i++){
            if(input[i] == '+'){
                operatorPos = i;
                opp = '+';
                break;
            }
            if(input[i] == '-'){
                operatorPos = i;
                opp = '-';
                break;
            }
        }
        if(opp != 'n'){
            for(int i = operatorPos - 1; i > -1; i--){
                if(!isNum(input[i])){
                    break;
                }
                firstOperandPos = i;
            }
            firstOperand = input.substr(firstOperandPos, operatorPos - firstOperandPos);
            for(int i = operatorPos + 1; i < input.length(); i++){
                if(!isNum(input[i])){
                    break;
                }
                secondOperandPos = i;
            }
            secondOperand = input.substr(operatorPos + 1, secondOperandPos - operatorPos);
        
            if(opp == '+'){
                result = to_string(stod(firstOperand) + stod(secondOperand));
            }
            if(opp == '-'){
                result = to_string(stod(firstOperand) - stod(secondOperand));
            }
            input = input.replace(firstOperandPos, secondOperandPos - firstOperandPos + 1, result);
        }
    }
    string output = input;
    return output;
}

string resolveInnermostBracket(string input){

    int openingBracketPos = -1;
    int closingBracketPos = input.length();
    string exp = input;
    string output = input;

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '('){
            openingBracketPos = i;
        }
        if(input[i] == ')'){
            closingBracketPos = i;
            break;
        }
    }
    exp = input.substr(openingBracketPos+1, closingBracketPos-openingBracketPos-1);
    exp = resolveBODMAS(exp);
    if(openingBracketPos == -1){
        output = input.replace(0, input.length(), exp);
        return output;
    }else {
        output = input.replace(openingBracketPos, closingBracketPos - openingBracketPos + 1, exp);
        return output;
    }
}

int main(){

    for(int i = 0; i < 10; i++){
        string question;
        string ans;

        cout << "enter the question : " << endl;

        cin >> question;

        cout << endl;

        while(notNumber(question)){
            question = resolveInnermostBracket(question);
        }
        cout << endl << question << endl;;
    }
    return 0;
}