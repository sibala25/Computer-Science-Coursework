#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;


bool valid(const string& infix);
void convert(const string& infix, string& postfix);
int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result) {
    if (!valid(infix)) {
        return 1;
    }
    stack<bool> operand;
    convert(infix, postfix);

    
    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] == 'T') {
            operand.push(true);
        }
        else if (postfix[i] == 'F') {
            operand.push(false);
        }
        else if (postfix[i] == '!') {
            bool current_op = operand.top();
            operand.pop();
            if (current_op == true) {
                operand.push(false);
            }
            if (current_op == false) {
                operand.push(true);
            }
        }
        else {
            bool operand2 = operand.top();
            operand.pop();
            bool operand1 = operand.top();
            operand.pop();

            if (postfix[i] == '&') { // TT = T     TF/FT = F     FF = F
                operand.push(operand1 && operand2);
            }
            if (postfix[i] == '|') { // TT = T     TF/FT = T     FF = F
                operand.push(operand1 || operand2);
            }
        }
    }
    result = operand.top();
    return 0;
}

bool valid(const string& infix) {
    string infix2 = "";
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] != ' ') {
            infix2+=infix[i];
        }
    }
    
    // cannot be the empty string
    if (infix2.length() < 1) {
        return false;
    }
    // if len 1, needs to just be T or F
    if (infix2.length() == 1) {
        if (infix2[0] == 'T' || infix2[0] == 'F') {
            return true;
        }
        return false;
    }
    
    stack<char> pars;
    for (int i = 0; i < infix2.length(); i++) {
        switch (infix2[i]) {
            case 'T':
            case 'F':
                if (i < infix2.length() - 1) {
                    if (infix2[i+1] == 'T' || infix2[i+1] == 'F' || infix2[i+1] == '(') {     // T/F cannot follow another T/F
                        return false;
                    }
                }
                break;
            case '(':
                if (i == infix2.length() - 1) {
                    return false;
                }
                pars.push(infix2[i]);
    
                if (i < infix2.length() - 1) {
                    if (infix2[i+1] == '|' || infix2[i+1] == '&'|| infix2[i+1] == ')') {  // must be followed by operand or !
                        return false;
                    }
                }
                break;
            case ')':
                if (pars.empty()) {                                                 // ')' does not have a valid matching '('
                    return false;
                }
                pars.pop();

                if (i < infix2.length() - 1) {
                    if (infix2[i+1] == 'T' || infix2[i+1] == 'F'|| infix2[i+1] == '(' || infix2[i+1] == '!') {  // must be followed by operator
                        return false;
                    }
                }
                break;
            case '&':
            case '|':
            case '!':
                if (i == infix2.length() - 1) {                                     // operators cannot be last thing in string
                    return false;
                }
                if (infix2[i+1] == ')' || infix2[i+1] == '&' || infix2[i+1] == '|') { // operators cannot be followed by binary operators or ')'
                    return false;
                }
                break;
            default:
                return false;
        }
    }
    if (!pars.empty()) { // if not empty, that means one '(' does not have matching ')'
        return false;
    }
    return true;
}

void convert(const string& infix, string& postfix) {
    string infix2 = "";
    
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] != ' ') {
            infix2+=infix[i];
        }
    }
    
    postfix = "";
    stack<char> op;
    for(int ch = 0; ch < infix2.size(); ch++) {
        switch (infix2[ch]) {
            case 'T':
            case 'F':
                postfix+=infix2[ch];
                break;
            case '(':
                op.push(infix2[ch]); // need to edit loop, this is adding index
                break;
            case ')':
                while (op.top() != '(') {
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            case '!':
                while (!op.empty() && op.top() != '(' && infix2[ch] >= op.top() && op.top() != '!') {
                    postfix+=op.top();
                    op.pop();
                }
                op.push(infix2[ch]);
                break;
            case '|':
            case '&':
                while (!op.empty() && op.top() != '(' && infix2[ch] >= op.top()) { // and prec of ch  <= prec of stack top
                    postfix+=op.top();
                    op.pop();
                }
                op.push(infix2[ch]);
                break;
            default:
                break;
        }
    }
    while (!op.empty()) {
        postfix+=op.top();
        op.pop();
    }
}

int main() {
    // from spec
    assert(valid("T"));
    assert(valid("(F)"));
    assert(valid("T&(F)"));
    assert(valid("T & !F"));
    assert(valid("!(F|T)"));
    assert(valid("!F|T"));
    assert(valid("(T)"));
    assert(valid("T|F&F"));
    assert(valid("T&!(F|T&T|F)|!!!(F&T&F)"));
    
    assert(!valid("(T))"));
    assert(!valid("(!(F|T)))("));
    assert(!valid("(!(F|T)"));
    assert(!valid("F F"));
    assert(!valid("T(F|T)"));

    
    string pf;
    bool answer;
    // from spec
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);

    cout << "Passed all tests" << endl;
    return 0;
}
