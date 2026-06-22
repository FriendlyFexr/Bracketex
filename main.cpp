#include <bits/stdc++.h>

using namespace std;
int main() {
    int length;
    string input;
    cin >> length;
    cin >> input;

    if (length % 2 != 0) {
        cout << "Invalid"; // must have even amount
        return 0;
    }

    int parenthesesConst = 0; // +1 for opens, -1 for closes
    int bracketConst = 0;
    int braceConst = 0;

    string priorityAscendingOrder = "";

    for (int i = 0; i < length; i++) {
        char ltr = input[i];
        bool isOpening = false;
        if (ltr == '(') {
            parenthesesConst += 1;
            isOpening = true;
            priorityAscendingOrder.append("1");
        }
        else if (ltr == ')') {
            parenthesesConst -= 1;
        }
        else if (ltr == '[') {
            isOpening = true;
            bracketConst += 1;
            priorityAscendingOrder.append("2");
        }
        else if (ltr == ']') {
            bracketConst -= 1;
        }
        else if (ltr == '{') {
            isOpening = true;
            braceConst += 1;
            priorityAscendingOrder.append("3");
        }
        else if (ltr == '}') {
            braceConst -= 1;
        }
        if (parenthesesConst < 0 || bracketConst < 0 || braceConst < 0) {
            cout << "Invalid"; // because ())( is invalid. 
            return 0;
        }
        // if closing, then must follow priority order.
        if (!isOpening) {
            string currentSpin = "0";
            string highestPriority = string(1, priorityAscendingOrder.back());
            if (ltr == ')') { currentSpin = "1"; }
            else if (ltr == ']') { currentSpin = "2"; }
            else if (ltr == '}') { currentSpin = "3"; }

            if (currentSpin != highestPriority) {
                //cout << currentSpin + " " + priorityAscendingOrder;
                cout << "Invalid";
                return 0;
            }
            else {
                priorityAscendingOrder.pop_back();
            }
        }
    }

    if (parenthesesConst == 0 && bracketConst == 0 && braceConst == 0) {
        cout << "Valid";
    }
    else {
        cout << "Invalid";
    }
    return 0;
}