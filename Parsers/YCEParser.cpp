#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

using std::tuple;
using std::make_tuple;
using std::get;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

class YCEParser
{
  protected:
    vector<tuple<string, string>> tokens;

    tuple<string, string> currentToken;

    int currentTokenPosition;

    bool GoToNextToken()
    {
        if (currentTokenPosition >= (signed int)tokens.size())
        {
            return false;
        }
        currentToken = tokens[++currentTokenPosition];
        return true;
    }

    bool ValueParser()
    {
        if (!GoToNextToken())
        {
            return false;
        }
        string tokenType = get<0>(currentToken);
        if (tokenType == "s_value")
        {
            return TerminatorParser();
        }
        else if (tokenType == "i_value")
        {
            return TerminatorParser();
        }
        return false;
    }

    bool TerminatorParser()
    {
        if (!GoToNextToken())
        {
            return false;
        }
        string tokenType = get<0>(currentToken);
        if (tokenType == "terminator")
        {
            return true;
        }
        return false;
    }

    bool VariableParser()
    {
        if (!GoToNextToken())
        {
            return false;
        }
        string tokenType = get<0>(currentToken);
        if (tokenType == "variable")
        {
            if (!GoToNextToken())
            {
                return false;
            }
            tokenType = get<0>(currentToken);
            if (tokenType == "equal")
            {
                return ValueParser();
            }
        }
        return false;
    }

  public:
    YCEParser(vector<tuple<string, string>> tokens)
    {
        this->tokens = tokens;
    }

    bool Parse()
    {
        currentTokenPosition = -1;
        return VariableParser();
    }
};

int main(int argc, char *argv[])
{
    vector<tuple<string, string>> tokens = {
        make_tuple<string, string>("variable", "var"),
        make_tuple<string, string>("equal", "="),
        make_tuple<string, string>("s_value", "Hello"),
        make_tuple<string, string>("terminator", ";"),
    };

    YCEParser parser(tokens);
    cout << (parser.Parse() ? "True" : "False") << endl;
}