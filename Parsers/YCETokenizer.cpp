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
using std::regex;
using std::regex_match;

class YCETokenizer
{
  protected:
    enum STATE
    {
        NORMAL,
        RUNNING_MODE,
        PROGRAM
    };
    STATE state;

    int tokenizedPosition;      // Intepreted code position.
    int maybeTokenizedPosition; // Maybe interpreted code position. Will be removed if tokenization failed.

    string sourceCode;

    vector<tuple<string, string>> tokens;

    vector<tuple<string, string>> candidateTokens;

    bool tokenizeSuccessful = false;

    void Reset()
    {
        sourceCode = "";
        state = NORMAL;
        tokenizedPosition = 0;
        maybeTokenizedPosition = 0;
        tokens.clear();
        candidateTokens.clear();
        tokenizeSuccessful = false;
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
            string next = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1);
            if (next == " " || next == "\t")
            {
                tokenizedPosition += 1;
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

    void BlankTokenizer(){
        while (1)
        {
            string next = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1);
          
            if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 2) == "\r\n")
            {
                tokenizedPosition += 2;
            }
            else if ((sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "\n"))
            {
                tokenizedPosition += 1;
            }
            if (next == " " || next == "\t")
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

    /* Put comment tokenization into preprocessor. So this method is obsolete. Keep this is because it might be useful later.
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
    */

    bool KeyTokenizer(string tokenType = "constant")
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            if (endChar == ":" || endChar == " " || endChar == "=" || endChar == "\t")
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
            candidateTokens.push_back(make_tuple(tokenType, key));
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

    bool EqualSignTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "=")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("equal", "="));
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
            if (endChar == ";" || endChar == " " || endChar == "\t")
            {
                break;
            }
            i++;
        }
        if (i == 0)
        {
            return false; // No i_const specified.
        }
        string i_const = string(sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, i));
        if (IsInteger(i_const))
        {
            maybeTokenizedPosition += i;
            candidateTokens.push_back(make_tuple("i_value", i_const));
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

    bool VariableTokenizer()
    {
        if (!KeyTokenizer("variable"))
        {
            candidateTokens.clear();
            maybeTokenizedPosition = 0;
            return false;
        }

        SpaceTokenizer();
        EnterTokenizer();

        if (!EqualSignTokenizer())
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

    bool LeftBraceSignTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "{")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("left_brace", "{"));
            return true;
        }
        return false;
    }

    bool RightBraceSignTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "}")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("right_brace", "}"));
            return true;
        }
        return false;
    }

    bool RunningModeKeyTokenizer()
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            if (endChar == "{" || endChar == " " || endChar == "\t")
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
            candidateTokens.push_back(make_tuple("running_mode", key));
            return true;
        }
        return false;
    }

    bool LeftParentheseTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == "(")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("left_parenthese", "("));
            return true;
        }
        return false;
    }

    bool RightParentheseTokenizer()
    {
        if (sourceCode.substr(maybeTokenizedPosition + tokenizedPosition, 1) == ")")
        {
            maybeTokenizedPosition += 1;
            candidateTokens.push_back(make_tuple("right_parenthese", ")"));
            return true;
        }
        return false;
    }

    bool ProgramTokenizer()
    {
        int i = 0;
        while (maybeTokenizedPosition + tokenizedPosition + i < sourceCode.size())
        {
            string endChar = sourceCode.substr(maybeTokenizedPosition + tokenizedPosition + i, 1);
            if (endChar == "(" || endChar == " " || endChar == "\t")
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
            candidateTokens.push_back(make_tuple("program", key));
            return true;
        }
        return false;
    }

    void Preprocess()
    {
        string preprocessedSourceCode = "";

        bool inCommentArea = false;

        for (int i = 0; i < sourceCode.size(); i++)
        {
            string next = sourceCode.substr(i, 1);
            if (next == "#" && !inCommentArea)
            {
                inCommentArea = true;
                continue;
            }
            if (inCommentArea && next == "\n")
            {
                inCommentArea = false;
                continue;
            }
            if (inCommentArea && next == "\r")
            {
                if (IsEndOfFile(1))
                {
                    continue;
                }
                if (sourceCode.substr(i + 1, 1) == "\n")
                {
                    inCommentArea = false;
                    continue;
                }
                continue;
            }
            if (!inCommentArea)
            {
                preprocessedSourceCode += next;
            }
        }
        sourceCode = preprocessedSourceCode;
    }

  public:
    YCETokenizer(string sourceCode)
    {
        this->sourceCode = sourceCode;
    }

    YCETokenizer() {}

    void SetSourceCode(string sourceCode)
    {
        this->sourceCode = sourceCode;
    }

    bool GetTokenizationResult()
    {
        return tokenizeSuccessful;
    }

    bool Tokenize()
    {
        Preprocess();

        state = NORMAL;
        tokenizedPosition = 0;
        maybeTokenizedPosition = 0;

        int inProgramNumber = 0;

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
                if (VariableTokenizer())
                {
                    break;
                }
                else if (RunningModeKeyTokenizer())
                {
                    SpaceTokenizer();
                    EnterTokenizer();
                    if (LeftBraceSignTokenizer())
                    {
                        state = RUNNING_MODE;
                    }
                    else
                    {
                        tokenizeSuccessful = false;
                        Reset();
                        return false;
                    }
                }
                else
                {
                    tokenizeSuccessful = false;
                    Reset();
                    return false;
                }
                break;
            case RUNNING_MODE:
                SpaceTokenizer();
                EnterTokenizer();
                if (RightBraceSignTokenizer())
                {
                    SpaceTokenizer();
                    EnterTokenizer();
                    if (TerminatorTokenizer())
                    {
                        state = NORMAL;

                        tokenizedPosition += maybeTokenizedPosition;
                        maybeTokenizedPosition = 0;
                        tokens.insert(tokens.end(), candidateTokens.begin(), candidateTokens.end());
                        candidateTokens.clear();

                        break;
                    }
                    Reset();
                    return false;
                }
                else if (ProgramTokenizer())
                {
                    state = PROGRAM;
                    break;
                }
                else
                {
                    Reset();
                    return false;
                }
                break;
            case PROGRAM:
                SpaceTokenizer();
                EnterTokenizer();

                if (LeftParentheseTokenizer())
                {
                    SpaceTokenizer();
                    EnterTokenizer();
                    if (SValueTokenzier())
                    {
                        SpaceTokenizer();
                        EnterTokenizer();
                        if (RightParentheseTokenizer())
                        {
                            SpaceTokenizer();
                            EnterTokenizer();
                            if (TerminatorTokenizer())
                            {
                                if (inProgramNumber == 0)
                                {
                                    state = RUNNING_MODE;
                                }

                                break;
                            }
                            else if (LeftBraceSignTokenizer())
                            {
                                inProgramNumber += 1;
                                SpaceTokenizer();
                                EnterTokenizer();
                                if (ProgramTokenizer())
                                {
                                    break;
                                }
                                else
                                {
                                    Reset();
                                    return false;
                                }
                            }
                        }
                    }
                }
                else if (RightBraceSignTokenizer())
                {
                    SpaceTokenizer();
                    EnterTokenizer();
                    if (TerminatorTokenizer())
                    {
                        SpaceTokenizer();
                        EnterTokenizer();
                        if (inProgramNumber > 1)
                        {
                            inProgramNumber -= 1;
                        }
                        else
                        {
                            state = RUNNING_MODE;
                        }
                        break;
                    }
                }
                Reset();
                return false;
                break;
            }
        }
        tokenizeSuccessful = true;
        return true;
    }

    vector<tuple<string, string>> GetTokens()
    {
        return tokens;
    }
};

int main(int argc, char *argv[])
{
    YCETokenizer tokenizer("version:\t12345;\nversion2:\t \"Test\";version3:67890;#Comments\nserial\t { program(\"Test\"); program(\"Test2\"){program(\"In Test2\"){program(\"In In Test2\");}; }; };BadTest: \"BadValue\";var=123;#Comments\n");

    if (tokenizer.Tokenize())
    {
        vector<tuple<string, string>> tokens = tokenizer.GetTokens();

        for (auto t : tokens)
        {
            cout << get<0>(t) + " -> " + get<1>(t) << endl;
        }
    }
    else
    {
        cout << "Lexical error." << endl;
    }
}
