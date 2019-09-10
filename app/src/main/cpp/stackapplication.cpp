#include <math.h>
#include "stackapplication.h"

string reverseString(const char* src)
{

    assert(src != NULL);
    string str;
    LinkedStack<char> s;
    while (*src != '\0')
        s.push(*src++);

    while (!s.isEmpty())
        str += s.pop();
    return str;
}

void match(Pair& p, const char* str)
{
    std::cout << str << std::endl;

    LinkedStack<Symbol> s;
    char* wrongInfo = new char[strlen(str) + 1];
    int location = 1;
    while (*str != '\0')
    {
        if (*str == p.left)
        {
            Symbol sym(*str, location - 1);
            s.push(sym);


        }
        else if (*str == p.right)
        {
            if (!s.isEmpty())
            {
                if (p.left == s.getTop()->getData().s)
                {
                    Symbol pairLeft = s.pop();
                    wrongInfo[pairLeft.key] = ' ';
                    wrongInfo[location - 1] = ' ';

                }
                else
                {
                    wrongInfo[location - 1] = '?';
                }
            }
            else
            {
                wrongInfo[location - 1] = '?';
            }
        }
        else
        {
            wrongInfo[location - 1] = ' ';
        }
        str++;
        location++;
    }
    while (!s.isEmpty())
    {
        Symbol sym = s.pop();
        wrongInfo[sym.key] = '?';
    }
    wrongInfo[location - 1] = '\0';
    std::cout << wrongInfo << std::endl;
}

int isOperator(char operators[],int n,char ch)
{
    int index = 0;
    while (index<n)
    {
        if (ch == operators[index])
            return index;
        index++;
    }
    return -1;//is not operator
}

string* infixToPostfix(const char* infix)
{
    LinkedStack<string> s;
    //string* postfix = new string[strlen(infix) + 2];
    char operators[] = { '#','+','-','*','/','(',')' };
    int priorities[] = { 0,1,1,3,4,6,6 };

    string* items = splitToString(infix, operators, 7);
    //计算items的长度
    int itemsOfLength = 0;
    while (items[itemsOfLength]!="end")
    {
        //cout << items[itemsOfLength];
        itemsOfLength++;
    }
    string* postfix = new string[itemsOfLength+1];

    string start(" ");
    start[0] = '#';
    s.push(start);

    int iOfItems = 0;
    int iOfPostfix = 0;
    while (items[iOfItems]!="end")
    {
        if (isOperator(operators,7,(items[iOfItems])[0]) == -1)
        {
            postfix[iOfPostfix] = items[iOfItems];
            iOfPostfix++;
            iOfItems++;
            continue;
        }

        int currentPriority = priorities[isOperator(operators, 7,items[iOfItems][0])];//当前字符的优先级
        int topPriority = priorities[isOperator(operators,7, (s.getTop()->getData())[0])];//栈顶运算符的优先级
        if (currentPriority)//是运算符
        {
            if ((s.getTop()->getData())[0] == '(')//rule 5
            {
                s.push(items[iOfItems]);

            }
            else if (items[iOfItems][0] == ')')
            {
                while ((s.getTop()->getData())[0] != '(')
                {
                    postfix[iOfPostfix] = s.pop();
                    iOfPostfix++;
                }
                s.pop();//左圆括号出栈
                //iOfItems++;
            }
            else if (currentPriority > topPriority)
            {
                s.push(items[iOfItems]);
                //iOfItems++;
            }
            else if (currentPriority <= topPriority)
            {
                while (priorities[isOperator(operators,7, (s.getTop()->getData())[0])] >= currentPriority
                       && (s.getTop()->getData())[0] != '('
                       && (s.getTop()->getData())[0] != '#')//rule 6
                {
                    postfix[iOfPostfix] = s.pop();
                    iOfPostfix++;//凡是对postfix赋值的地方都需要此行代码
                }
                s.push(items[iOfItems]);//rule6 重难点代码
            }
        }
        else//是操作数
        {
            postfix[iOfPostfix] = items[iOfItems];
            iOfPostfix++;
            //iOfItems++;
        }
        iOfItems++;
    }
    //出栈到只剩'#'
    while ((s.getTop()->getData())[0]!='#')
    {
        postfix[iOfPostfix] = s.pop();
        iOfPostfix++;
    }

    postfix[iOfPostfix] = "end";

    delete []items;
    return postfix;
}
string* splitToString(const char* str, char splitChars[],int n)
{
    string* results = new string[strlen(str)+3];
    LinkedStack<char> s;
    int length = 0;
    while (*str!='\0')
    {
        if (isOperator(splitChars, n, *str) == -1)
        {
            s.push(*str);
        }
        else
        {
            if (s.isEmpty())
            {
                string temp = " ";
                temp[0] = *str;
                results[length] = temp;

                str++;
                length++;
                continue;
            }
            int i = 0;
            int stackLength = s.getLength();
            char* item = new char[stackLength + 1];
            LinkedStack<char> temp;
            for (; i < stackLength; i++)
            {
                temp.push(s.pop());
            }
            i = 0;
            for (; i < stackLength; i++)
            {
                item[i] = temp.pop();
            }
            item[i] = '\0';
            results[length] = string(item);
            length++;
            delete []item;

            results[length] = string(" ");
            (results[length])[0] = *str;
            length++;
        }
        str++;
    }
    //清空栈
    if (!s.isEmpty())
    {
        char* item = new char[s.getLength() + 1];
        int i = 0;
        int stackLength = s.getLength();
        for (; i < stackLength; i++)
        {
            item[i] = s.pop();
        }
        item[i] = '\0';
        results[length] = reverseString(item);
        length++;
        delete[]item;
    }


    results[length] = "end";
    return results;
}

double countPostfix(string* postfix)
{
    assert(postfix != NULL);

    //double result = 0;
    char operators[] = { '#','+','-','*','/','(',')' };
    LinkedStack<double> s;

    int i = 0;
    while (postfix[i] != "end")
    {
        if (isOperator(operators, 7, postfix[i][0])==-1)//将字符串形式的操作数转为double型数据
        {
            double number= atof(postfix[i].c_str());//先利用c_str()轉成C string，再用atoi()與atof()。
            if (number != 0.0 || number != HUGE_VAL)//转换成功
            {
                s.push(number);
            }
            else
            {
                cout<<"转换错误!"<<endl;
                return HUGE_VAL;
            }
        }
        else
        {
            switch (postfix[i][0])
            {
                case '+':
                {
                    s.push(s.pop() + s.pop());
                    break;
                }
                case '-':
                {
                    double right = s.pop();
                    double left = s.pop();
                    s.push(left - right);
                    break;
                }
                case '*':
                {
                    s.push(s.pop() * s.pop());
                    break;
                }
                case '/':
                {
                    double right = s.pop();//关键代码
                    double left = s.pop();
                    s.push(left / right);
                    break;
                }
                default:
                    break;
            }
        }
        i++;
    }
    return s.pop();
}
