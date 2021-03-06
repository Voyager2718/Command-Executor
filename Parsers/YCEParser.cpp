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

    int maybeTokenPosition;

    void CommitParsePosition()
    {
        currentTokenPosition += maybeTokenPosition;
        maybeTokenPosition = 0;
    }

    bool GoToNextToken()
    {
        if (currentTokenPosition + maybeTokenPosition >= (signed int)tokens.size() - 1)
        {
            return false;
        }
        maybeTokenPosition += 1;
        currentToken = tokens[maybeTokenPosition + currentTokenPosition];
        return true;
    }

    bool IsEndOfTokens()
    {
        if (currentTokenPosition >= (signed int)tokens.size() - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
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
        int tmp = maybeTokenPosition;
        if (!GoToNextToken())
        {
            maybeTokenPosition = tmp;
            return false;
        }
        string tokenType = get<0>(currentToken);
        if (tokenType == "variable")
        {
            if (!GoToNextToken())
            {
                maybeTokenPosition = tmp;
                return false;
            }
            tokenType = get<0>(currentToken);
            if (tokenType == "equal")
            {
                return ValueParser();
            }
        }
        maybeTokenPosition = tmp;
        return false;
    }

    bool ConstantParser()
    {
        int tmp = maybeTokenPosition;
        if (!GoToNextToken())
        {
            maybeTokenPosition = tmp;
            return false;
        }
        string tokenType = get<0>(currentToken);
        if (tokenType == "constant")
        {
            if (!GoToNextToken())
            {
                maybeTokenPosition = tmp;
                return false;
            }
            tokenType = get<0>(currentToken);
            if (tokenType == "colon")
            {
                return ValueParser();
            }
        }
        maybeTokenPosition = tmp;
        return false;
    }

    bool ProgramParser()
    {
        int tmp = maybeTokenPosition;
        if (!GoToNextToken())
        {
            maybeTokenPosition = tmp;
            return false;
        }

        string tokenType = get<0>(currentToken);
        if (tokenType == "program")
        {
            if (!GoToNextToken())
            {
                maybeTokenPosition = tmp;
                return false;
            }
            tokenType = get<0>(currentToken);
            if (tokenType == "left_parenthese")
            {
                if (!GoToNextToken())
                {
                    maybeTokenPosition = tmp;
                    return false;
                }
                tokenType = get<0>(currentToken);
                if (tokenType == "s_value")
                {
                    if (!GoToNextToken())
                    {
                        maybeTokenPosition = tmp;
                        return false;
                    }
                    tokenType = get<0>(currentToken);
                    if (tokenType == "right_parenthese")
                    {
                        return TerminatorParser();
                    }
                }
            }
        }
        maybeTokenPosition = tmp;
        return false;
    }

    bool RunningModeParser()
    {
        int tmp = maybeTokenPosition;
        if (!GoToNextToken())
        {
            maybeTokenPosition = tmp;
            return false;
        }

        string tokenType = get<0>(currentToken);
        if (tokenType == "running_mode")
        {
            if (!GoToNextToken())
            {
                maybeTokenPosition = tmp;
                return false;
            }

            tokenType = get<0>(currentToken);
            if (tokenType == "left_brace")
            {

                while (ProgramParser())
                {
                    ProgramParser();
                };

                if (!GoToNextToken())
                {
                    maybeTokenPosition = tmp;
                    return false;
                }
                tokenType = get<0>(currentToken);
                if (tokenType == "right_brace")
                {
                    return TerminatorParser();
                }
            }
        }
        maybeTokenPosition = tmp;
        return false;
    }

    bool ExpressionParser()
    {
        if (VariableParser())
        {
            CommitParsePosition();
            return ExpressionParser();
        }
        else if (ConstantParser())
        {
            CommitParsePosition();
            return ExpressionParser();
        }
        else if (RunningModeParser())
        {
            CommitParsePosition();
            return ExpressionParser();
        }
        else if (IsEndOfTokens())
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
        currentTokenPosition = -1;
        maybeTokenPosition = 0;
        return ExpressionParser();
    }
};

int main(int argc, char *argv[])
{
    vector<tuple<string, string>> tokens = {
        make_tuple<string, string>("variable", "var"),
        make_tuple<string, string>("equal", "="),
        make_tuple<string, string>("s_value", "Hello"),
        make_tuple<string, string>("terminator", ";"),
        make_tuple<string, string>("constant", "var"),
        make_tuple<string, string>("colon", "="),
        make_tuple<string, string>("s_value", "Hello"),
        make_tuple<string, string>("terminator", ";"),
        make_tuple<string, string>("variable", "var"),
        make_tuple<string, string>("equal", "="),
        make_tuple<string, string>("s_value", "Hello"),
        make_tuple<string, string>("terminator", ";"),
        make_tuple<string, string>("running_mode", "serial"),
        make_tuple<string, string>("left_brace", "{"),
        make_tuple<string, string>("program", "program"),
        make_tuple<string, string>("left_parenthese", "("),
        make_tuple<string, string>("s_value", "Test"),
        make_tuple<string, string>("right_parenthese", ")"),
        make_tuple<string, string>("terminator", ";"),
        make_tuple<string, string>("program", "program"),
        make_tuple<string, string>("left_parenthese", "("),
        make_tuple<string, string>("s_value", "Test"),
        make_tuple<string, string>("right_parenthese", ")"),
        make_tuple<string, string>("terminator", ";"),
        make_tuple<string, string>("right_brace", "}"),
        make_tuple<string, string>("terminator", ";"),
    };

    YCEParser parser(tokens);
    cout << (parser.Parse() ? "True" : "False") << endl;
}
