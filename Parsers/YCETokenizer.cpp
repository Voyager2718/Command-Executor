#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <regex>

using std::tuple;
using std::make_tuple;
using std::get;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::regex_match;

class YCETokenizer
{
  protected:
    enum STATE
    {
        NORMAL,
        KEY,
        VARIABLE,
        I_VALUE,
        S_VALUE,
        COMMENT
    };
    STATE state;

    int tokenizedPosition; // Intepreted code position.
    int maybeTokenizedPosition;

    string sourceCode;

    vector<tuple<string, string>> tokens;

    vector<tuple<string, string>> candidateTokens;

    bool IsAcceptableKeyword(string test)
    {
        regex keywordPattern("([A-Za-z_][A-Za-z0-9_]{0,254})");
        if (!regex_match(test, keywordPattern))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool IsInteger(string test)
    {
        regex integerPattern("([0-9]{1,10})");
        if (!regex_match(test, integerPattern))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool IsEndOfFile()
    {
        if (tokenizedPosition >= sourceCode.size())
        {
            return true;
        }
        return false;
    }

    bool IsEndOfFile(int plus)
    {
        if (tokenizedPosition + plus >= sourceCode.size())
        {
            return true;
        }
        return false;
    }

    void SpaceTokenizer()
    {
        while (1)
        {
            if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == " ")
            {
                maybeTokenizedPosition++;
            }
            else
            {
                break;
            }
        }
    }

    void EnterTokenizer()
    {
        while (1)
        {
            if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 2) == "\r\n")
            {
                tokenizedPosition += 2;
            }
            else if ((sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "\n"))
            {
                tokenizedPosition += 1;
            }
            else
            {
                break;
            }
        }
    }

    bool HashSignTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "#")
        {
            tokenizedPosition += 1;
            return true;
        }
        return false;
    }

    void CommentTokenizer()
    {
        while (1)
        {
            if (IsEndOfFile())
            {
                break;
            }
            else if (IsEndOfFile(1))
            {
                break;
            }

            if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "\n")
            {
                tokenizedPosition += 1;
                break;
            }
            if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 2) == "\r\n")
            {
                tokenizedPosition += 2;
                break;
            }

            tokenizedPosition += 1;
        }
    }

    bool KeyTokenizer()
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            if (endChar == ":" || endChar == " ")
            {
                break;
            }
            i++;
        }
        if (i == 0)
        {
            return false; // No key specified.
        }
        string key = string(sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, i));
        maybeTokenizedPosition += i;
        if (IsAcceptableKeyword(key))
        {
            candidateTokens.push_back(make_tuple("key", key));
            return true;
        }
        return false;
    }

    bool ColonTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == ":")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("colon", ":"));
            return true;
        }
        return false;
    }

    bool TerminatorTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == ";")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("terminator", ";"));
            return true;
        }
        return false;
    }

    bool IValueTokenizer()
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            if (endChar == ";" || endChar == " ")
            {
                break;
            }
            i++;
        }
        if (i == 0)
        {
            return false; // No i_value specified.
        }
        string i_value = string(sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, i));
        if (IsInteger(i_value))
        {
            maybeTokenizedPosition += i;
            candidateTokens.push_back(make_tuple("i_value", i_value));
            return true;
        }
        return false;
    }

    bool SValueTokenzier()
    {
        int i = 0;
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) != "\"")
        {
            return false;
        }
        i += 1;

        if (IsEndOfFile(maybeTokenizedPosition + i))
        {
            return false;
        }

        string s_value = "";

        while (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1) != "\"")
        {
            s_value += sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            i += 1;
            if (IsEndOfFile(maybeTokenizedPosition + i))
            {
                return false;
            }
        }
        i += 1;
        maybeTokenizedPosition += i;
        candidateTokens.push_back(make_tuple("s_value", s_value));
        return true;
    }

    bool ConstantTokenizer()
    {
        if (!KeyTokenizer())
        {
            candidateTokens.clear();
            maybeTokenizedPosition = 0;
            return false;
        }

        SpaceTokenizer();
        EnterTokenizer();

        if (!ColonTokenizer())
        {
            candidateTokens.clear();
            maybeTokenizedPosition = 0;
            return false;
        }

        SpaceTokenizer();
        EnterTokenizer();

        if (IValueTokenizer())
        {
            tokenizedPosition += maybeTokenizedPosition;
            maybeTokenizedPosition = 0;
            tokens.insert(tokens.end(), candidateTokens.begin(), candidateTokens.end());
            candidateTokens.clear();

            SpaceTokenizer();
            EnterTokenizer();

            if (TerminatorTokenizer())
            {
                tokenizedPosition += maybeTokenizedPosition;
                maybeTokenizedPosition = 0;
                tokens.insert(tokens.end(), candidateTokens.begin(), candidateTokens.end());
                candidateTokens.clear();

                return true;
            }
            return false;
        }
        if (SValueTokenzier())
        {
            tokenizedPosition += maybeTokenizedPosition;
            maybeTokenizedPosition = 0;
            tokens.insert(tokens.end(), candidateTokens.begin(), candidateTokens.end());
            candidateTokens.clear();

            SpaceTokenizer();
            EnterTokenizer();

            if (TerminatorTokenizer())
            {
                tokenizedPosition += maybeTokenizedPosition;
                maybeTokenizedPosition = 0;
                tokens.insert(tokens.end(), candidateTokens.begin(), candidateTokens.end());
                candidateTokens.clear();

                return true;
            }
            return false;
        }
        return false;
    }

  public:
    YCETokenizer(string sourceCode)
    {
        this->sourceCode = sourceCode;
    }

    YCETokenizer() {}

    bool Parse()
    {
        state = NORMAL;
        tokenizedPosition = 0;
        maybeTokenizedPosition = 0;

        while (!IsEndOfFile())
        {
            switch (state)
            {
            case NORMAL:
                SpaceTokenizer();
                EnterTokenizer();
                if (ConstantTokenizer())
                {
                    break;
                }
                else if (HashSignTokenizer())
                {
                    state = COMMENT;
                    break;
                }
                else
                {
                    return false;
                }
                break;
            case COMMENT:
                CommentTokenizer();
                state = NORMAL;
                break;
            case KEY:
                break;
            case VARIABLE:
                break;
            case I_VALUE:
                break;
            case S_VALUE:
                break;
            }
        }
        return true;
    }

    vector<tuple<string, string>> GetTokens()
    {
        return tokens;
    }
};

int main(int argc, char *argv[])
{
    YCETokenizer tokenizer("version:12345;\n# Comments\nversion2:67890;");

    tokenizer.Parse();

    vector<tuple<string, string>> tokens = tokenizer.GetTokens();

    for (auto t : tokens)
    {
        cout << get<0>(t) + " -> " + get<1>(t) << endl;
    }
}