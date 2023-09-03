#include <iostream>


#define isP() false


bool (isP) () {
    return true;
}

/*bool isValidPCons(char str[]) {
    int len= strlen(str);

    cStack<char> stack;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            stack.Push(str[i]);
        }
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (stack.IsEmpty() == true) {
                return false;
            }

            char c = stack.Top();

            // Difference between similar ASCII chars = { 1, 2 }
            if (str[i] - c > 2) {
                return false;
            }

            stack.Pop();
        }
    }

    return stack.IsEmpty();
}*/


int main(int argc, char *argv[]) {
    return 0;
}