#include <iostream>
#include <string>
#include <emscripten/emscripten.h>

extern "C" {

    EMSCRIPTEN_KEEPALIVE
    bool check_brackets(const char* str) {
        std::string input(str);
        int length = input.length();

        // 1. Length check
        if (length % 2 != 0) {
            return false;
        }

        int parenthesesConst = 0; 
        int bracketConst = 0;
        int braceConst = 0;
        std::string priorityAscendingOrder = "";

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

            // 2. Prevent negative counts
            if (parenthesesConst < 0 || bracketConst < 0 || braceConst < 0) {
                return false; 
            }

            // 3. Process closing brackets
            if (!isOpening) {
                // Critical Fix: If closing bracket appears before any opening bracket
                if (priorityAscendingOrder.empty()) {
                    return false;
                }

                std::string currentSpin = "0";
                std::string highestPriority = std::string(1, priorityAscendingOrder.back());
                
                if (ltr == ')') { currentSpin = "1"; }
                else if (ltr == ']') { currentSpin = "2"; }
                else if (ltr == '}') { currentSpin = "3"; }

                if (currentSpin != highestPriority) {
                    return false;
                }
                else {
                    priorityAscendingOrder.pop_back();
                }
            }
        }

        // 4. Final check
        return (parenthesesConst == 0 && bracketConst == 0 && braceConst == 0);
    }
}
