#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>

using std::map;
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

    vector<map<string, string>> tokens;

    vector<map<string, string>> candidateTokens;

    map<string, string> MakeMap(string key, string value)
    {
        map<string, string> temp;
        temp["keyword"] = key;
        temp["value"] = value;
        return temp;
    }

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
                maybeTokenizedPosition += 2;
            }
            else if ((sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "\n"))
            {
                maybeTokenizedPosition += 1;
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
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + 1, 1);
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
        if (IsAcceptableKeyword(key))
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(MakeMap("key", key));
            return true;
        }
        return false;
    }

    bool ColonTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == ":")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(MakeMap("colon", ":"));
            return true;
        }
        return false;
    }

    bool TerminatorTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == ";")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(MakeMap("terminator", ";"));
            return true;
        }
        return false;
    }

    bool IValueTokenizer()
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + 1, 1);
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
            candidateTokens.push_back(MakeMap("i_value", i_value));
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
        candidateTokens.push_back(MakeMap("s_value", s_value));
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

    vector<map<string, string>> GetTokens()
    {
        return tokens;
    }
};

int main(int argc, char *argv[])
{
    YCETokenizer tokenizer("version:12345;\n# Comments ");

    vector<map<string, string>> tokens = tokenizer.GetTokens();

    for (auto t : tokens)
    {
        cout<<t[""]
    }
}