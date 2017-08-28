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

    int currentTokenPosition = 0;

    bool GoToNextToken()
    {
        if (currentTokenPosition >= tokens.size())
        {
            return false; // No more token.
        }
        currentTokenPosition += 1;
        currentToken = tokens[currentTokenPosition];
        return true;
    }

    bool ValueParser()
    {
        string tokenType = get<0>(currentToken);
        if (tokenType == "s_value")
        {
            if (GoToNextToken())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (tokenType == "i_value")
        {
            if (GoToNextToken())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool TerminatorParser()
    {
        string tokenType = get<0>(currentToken);
        if (tokenType == "terminator")
        {
            if (GoToNextToken())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool VariableParser()
    {
        string tokenType = get<0>(currentToken);
        if (tokenType == "variable")
        {
            if (GoToNextToken())
            {
                string tokenType2 = get<0>(currentToken);
                if (tokenType2 == "equal")
                {
                    if (GoToNextToken())
                    {
                        if (ValueParser())
                        {
                            if (GoToNextToken())
                            {
                                return TerminatorParser();
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    /*
    bool RunnmingModeParser()
    {
        string tokenType = get<0>(currentToken);
        if (tokenType == "running_mode")
        {
            if (GoToNextToken())
            {
                string tokenType2 = get<0>(currentToken);
                if (tokenType2 == "{")
                {
                    if (GoToNextToken())
                    {
                        ProgramParser
                    }
                }
            }
        }
        return false;
    }
    */

    bool ProgramParser()
    {
        string tokenType = get<0>(currentToken);
    }

    bool ExpressionParser()
    {
        if (VariableParser())
        {
            return ExpressionParser();
        }
        else if (!GoToNextToken())
        {
            return true;
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
    cout << (parser.Parse() ? "True" : "False");
}