#include "SuntingYardToken.hpp"





std::ostream& operator<<(std::ostream& os, const SuntingYardToken& token)
{
    os << token.str;
    return os;
}


// Debug output
template<class T, class U>
void debugReport(const SuntingYardToken& token, const T& queue, const U& stack, const std::string& comment = "")
{
    std::ostringstream ossQueue;
    for(const auto& t : queue)
    {
        ossQueue << " " << t;
    }

    std::ostringstream ossStack;
    for(const auto& t : stack)
    {
        ossStack << " " << t;
    }

    printf(reportFmt
           , token.str.c_str()
           , ossQueue.str().c_str()
           , ossStack.str().c_str()
           , comment.c_str()
    );
}


std::deque<SuntingYardToken> exprToTokens(const std::string& expr)
{
    std::deque<SuntingYardToken> tokens;

    for(const auto* p = expr.c_str(); *p; ++p)
    {
        if(isblank(*p))
        {
            // do nothing
        } 
        else if(isdigit(*p))
        {
            const auto* b = p;
            while(isdigit(*p))
            {
                ++p;
            }
            const auto s = std::string(b, p);
            tokens.push_back(SuntingYardToken { SuntingYardToken::Type::Number, s });
            --p;
        } 
        else
        {
            SuntingYardToken::Type t = SuntingYardToken::Type::Unknown;
            int pr = -1;            // precedence
            bool ra = false;        // rightAssociative
            switch(*p)
            {
                default:                                    break;
                case '(':   t = SuntingYardToken::Type::LeftParen;     break;
                case ')':   t = SuntingYardToken::Type::RightParen;    break;
                case '^':   t = SuntingYardToken::Type::Operator;      pr = 4; ra = true;  break;
                case '*':   t = SuntingYardToken::Type::Operator;      pr = 3; break;
                case '/':   t = SuntingYardToken::Type::Operator;      pr = 3; break;
                case '+':   t = SuntingYardToken::Type::Operator;      pr = 2; break;
                case '-':   t = SuntingYardToken::Type::Operator;      pr = 2; break;
            }
            const auto s = std::string(1, *p);
            tokens.push_back(SuntingYardToken { t, s, pr, ra });
        }
    }

    return tokens;
}


std::deque<SuntingYardToken> shuntingYard(const std::deque<SuntingYardToken>& tokens)
{
    std::deque<SuntingYardToken> queue;
    std::vector<SuntingYardToken> stack;

    // While there are tokens to be read:
    for(auto token : tokens)
    {
        // Read a token
        switch(token.type)
        {
            case SuntingYardToken::Type::Number:
                // If the token is a number, then add it to the output queue
                queue.push_back(token);
                break;

            case SuntingYardToken::Type::Operator:
                {
                    // If the token is operator, o1, then:
                    const auto o1 = token;

                    // while there is an operator token,
                    while(!stack.empty())
                    {
                        // o2, at the top of stack, and
                        const auto o2 = stack.back();

                        // either o1 is left-associative and its precedence is
                        // *less than or equal* to that of o2,
                        // or o1 if right associative, and has precedence
                        // *less than* that of o2,
                        if(
                            (! o1.rightAssociative && o1.precedence <= o2.precedence)
                        ||  (  o1.rightAssociative && o1.precedence <  o2.precedence)
                        )
                        {
                            // then pop o2 off the stack,
                            stack.pop_back();
                            // onto the output queue;
                            queue.push_back(o2);

                            continue;
                        }

                        // @@ otherwise, exit.
                        break;
                    }

                    // push o1 onto the stack.
                    stack.push_back(o1);
                }
                break;

            case SuntingYardToken::Type::LeftParen:
                // If token is left parenthesis, then push it onto the stack
                stack.push_back(token);
                break;

            case SuntingYardToken::Type::RightParen:
                // If token is right parenthesis:
                {
                    bool match = false;

                    // Until the token at the top of the stack
                    // is a left parenthesis,
                    while(! stack.empty() && stack.back().type != SuntingYardToken::Type::LeftParen)
                    {
                        // pop operators off the stack
                        // onto the output queue.
                        queue.push_back(stack.back());
                        stack.pop_back();
                        match = true;
                    }

                    // Pop the left parenthesis from the stack,
                    // but not onto the output queue.
                    stack.pop_back();

                    if(!match && stack.empty())
                    {
                        // If the stack runs out without finding a left parenthesis,
                        // then there are mismatched parentheses.
                        printf("RightParen error (%s)\n", token.str.c_str());
                        return {};
                    }
                }
                break;

            default:
                printf("error (%s)\n", token.str.c_str());
                return {};
        }

        //debugReport(token, queue, stack);
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while(! stack.empty())
    {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if(stack.back().type == SuntingYardToken::Type::LeftParen)
        {
            printf("Mismatched parentheses error\n");
            return {};
        }

        // Pop the operator onto the output queue.
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    //debugReport(SuntingYardToken { SuntingYardToken::Type::Unknown, "End" }, queue, stack);

    //Exit.
    return queue;
}

double SuntingYardToken::shuntingYardF(std::string expre)
{
    std::string zero_init = "0";

    std::string full_expre = zero_init + expre;
    
    std::vector<double> stack;

    std::vector<std::string> expressions ={full_expre};

    for( std::string& expr : expressions)
    {
        printf("expr = %s\n", expr.c_str());
        
        // if (expr[1] == '-' && expr[2] == '-' )
        // {
        //     expr.erase(expr.begin()+2) ;
        //     expr[1] = '+';
        // }
        
        //printf(reportFmt, "Token", "Queue", "Stack", "");

        const auto tokens = exprToTokens(expr);
        auto queue = shuntingYard(tokens);

        // printf("\nCalculation\n");
        //printf(reportFmt, "Token", "Queue", "Stack", "");

        while(! queue.empty())
        {
            std::string op;

            const auto token = queue.front();
            queue.pop_front();
            switch(token.type)
            {
                case SuntingYardToken::Type::Number:
                    stack.push_back(std::stoi(token.str));
                    op = "Push " + token.str;
                    break;

                case SuntingYardToken::Type::Operator:
                    {
                        const auto rhs = stack.back();
                        stack.pop_back();
                        const auto lhs = stack.back();
                        stack.pop_back();

                        switch(token.str[0])
                        {
                        default:
                            printf("Operator error [%s]\n", token.str.c_str());
                            exit(0);
                            break;
                        case '^':
                            stack.push_back(static_cast<int>(pow(lhs, rhs)));
                            break;
                        case '*':
                            stack.push_back(lhs * rhs);
                            break;
                        case '/':
                            stack.push_back(lhs / rhs);
                            break;
                        case '+':
                            stack.push_back(lhs + rhs);
                            break;
                        case '-':
                            stack.push_back(lhs - rhs);
                            break;
                        }
                        op = "Push " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
                    }
                    break;

                default:
                    printf("Token error\n");
                    exit(0);
            }
            //debugReport(token, queue, stack, op);
        }
        //std::cout << "  result = "<< stack.back() << "\n";
    }
    return stack.back();
}
