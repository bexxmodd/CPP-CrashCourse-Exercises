#include <iostream>
#include <stack>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

bool valid(std::string& s)
{
    std::stack<char> stack{};
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '[' || s[i] == '{' || s[i] == '(')
            stack.push(s[i]);
        else
        {
            if (stack.size() == 0) return false;
            else if (s[i] == ']' && stack.top() == '[') stack.pop();
            else if (s[i] == '}' && stack.top() == '{') stack.pop();
            else if (s[i] == ')' && stack.top() == '(') stack.pop();
            else return false;
        }
    }
    return stack.size() == 0;
}

TEST_CASE("Valid Parentheses", "[valid]")
{
    std::string s1 = "";
    REQUIRE(valid(s1));

    std::string s = "{}[]()";
    REQUIRE(valid(s));
}
