#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

//If argument not Integer or one of ()+-*/%
//this exception will be thrown.
class InvalidArgument : public exception{
public:
    InvalidArgument(const string str)throw():error_message("Invalid argument: " + str + "."){}
    virtual const char* what()const throw(){return error_message.c_str();}
private:
    string error_message;
};


class InvalidExpression : public exception{
public:
    virtual const char* what()const throw(){return "Invalid Expression";}

};

class DivideByZero : public exception{
public:
    virtual const char* what()const throw(){return "Dividing by zero";}

};

struct element {
    int value;
    enum ElementType{Number, Plus, Minus, Division, TakeRest,
                     Multipication, OpenBracket, CloseBracket, FirstElement};
    ElementType type;
    short priority;
};

//Parsing string to Reverse Polish Notation
//Exceprions: InvalidArgument, InvalidExpression
queue<element> parseString(string str);

//Calculate RPN expression, return answer
//No Expressions
int calculate(queue<element> &elements);

//Expression: InvalidArgument
element parseElement(string str);

int main()
{
    string input;
    cout << "Enter expression for calculation or enter empty string for quit:" << endl;
    getline(cin, input);
    while (!input.empty()){
        try{
            queue<element> expression = parseString(input);
            cout << input << " = " << calculate(expression) << endl;
        }
        catch(exception &e){
            cerr << e.what() << endl;
        }
        cout << "Enter expression for calculation or enter empty string for quit:" << endl;
        getline(cin, input);
    }
    return 0;
}

element parseElement(string str){
    element tmp;
    try{
        size_t *pos = new size_t;
        tmp.value = stoi(str, pos);
        if (*pos != str.length())
            throw InvalidArgument(str);
        tmp.type = element::Number;
        return tmp;
    }
    catch(invalid_argument &e){
        if (str.length() == 1){
            switch (*str.data()) {
            case '+':
                tmp.type = element::Plus;
                tmp.priority = 1;
                break;
            case '-':
                tmp.type = element::Minus;
                tmp.priority = 1;
                break;
            case '%':
                tmp.type = element::TakeRest;
                tmp.priority = 2;
                break;
            case '/':
                tmp.type = element::Division;
                tmp.priority = 2;
                break;
            case '*':
                tmp.type = element::Multipication;
                tmp.priority = 2;
                break;
            case '(':
                tmp.type = element::OpenBracket;
                tmp.priority = 0;
                break;
            case ')':
                tmp.type = element::CloseBracket;
                tmp.priority = 0;
                break;
            default:
                throw InvalidArgument(str);
            }
        }else{
            throw InvalidArgument(str);
        }
    }
    catch(out_of_range &e){
        throw InvalidArgument(str + "Out of range Integer");
    }
    return tmp;
}

int calculate(queue<element> &elements){
    stack<int> tmpStack;
    while (!elements.empty()) {
        if (elements.front().type == element::Number){
            tmpStack.push(elements.front().value);
        }else{
            int left, right;
            right = tmpStack.top();
            tmpStack.pop();
            left = tmpStack.top();
            tmpStack.pop();
            switch (elements.front().type) {
            case element::Plus:
                tmpStack.push(left + right);
                break;
            case element::Minus:
                tmpStack.push(left - right);
                break;
            case element::Division:
                if (right != 0){
                    tmpStack.push(left / right);
                }else{
                    throw DivideByZero();
                }
                break;
            case element::Multipication:
                tmpStack.push(left * right);
                break;
            case element::TakeRest:
                tmpStack.push(left % right);
                break;
            }
        }
        elements.pop();
    }
    return tmpStack.top();
}

queue<element> parseString(string str){
    stack<element> tmpStack;
    queue<element> elements;
    istringstream buf(str);
    string tmp;
    element previous;
    previous.type = element::FirstElement;
    while (buf >> tmp) {
        element current = parseElement(tmp);
        switch (current.type) {
        case element::Number:
            if (previous.type != element::Number){
                elements.push(current);
            }else{
                throw InvalidExpression();
            }
            break;
        case element::Plus:
        case element::Minus:
            if (previous.type == element::Number ||
                    previous.type == element::CloseBracket ||
                    previous.type == element::FirstElement){
                tmpStack.push(current);
            }else{
                throw InvalidExpression();
            }
            break;
        case element::OpenBracket:
            if (previous.type != element::Number){
                tmpStack.push(current);
            }else{
                throw InvalidExpression();
            }
            break;
        case element::Multipication:
        case element::Division:
        case element::TakeRest:
            if (previous.type == element::Number ||
                    previous.type == element::CloseBracket ||
                    previous.type == element::FirstElement){
                while (!tmpStack.empty()) {
                    if (current.priority > tmpStack.top().priority) break;
                    elements.push(tmpStack.top());
                    tmpStack.pop();
                }
                tmpStack.push(current);
            }else{
                throw InvalidExpression();
            }
            break;
        case element::CloseBracket:
            if (previous.type == element::Number ||
                    previous.type == element::CloseBracket ||
                    previous.type == element::FirstElement){
                if (!tmpStack.empty()){
                    while (tmpStack.top().type != element::OpenBracket) {
                        elements.push(tmpStack.top());
                        tmpStack.pop();
                        if(tmpStack.empty()){
                            throw InvalidExpression();
                        }
                    }
                }else{
                    throw InvalidExpression();
                }
                tmpStack.pop();
            }else{
                throw InvalidExpression();
            }
            break;
        }
        previous.type = current.type;
    }
    while (!tmpStack.empty()) {
        if (tmpStack.top().type != element::OpenBracket){
            elements.push(tmpStack.top());
            tmpStack.pop();
        }else{
            throw InvalidExpression();
        }
    }
    return elements;
}
