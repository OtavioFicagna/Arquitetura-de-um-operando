#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

struct memory
{
    float values[256];
    std::vector<int> adress;
};

memory mem;
int error_count = 0;
std::stack<float> stack;

std::string lowercase(std::string &str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
    return str;
}

int identify_operation(std::string operacao)
{
    const int qtdOps = 14;
    int count = 0;
    std::string operations[qtdOps] = {"pushi", "push", "pop", "input", "print", "add", "sub", "mul", "div", "swap", "drop", "dup", "hlt", "erro"};
    while (count < qtdOps)
    {
        if (operations[count] == operacao)
        {
            return count;
        }
        count++;
    }
    return 13;
}

void pushi()
{
    if (stack.size() <= 16)
    {
        float value;
        std::cin >> value;
        stack.push(value);
    }
    else
    {
        std::cout << "Stack Overflow\n";
        error_count++;
    }
}

void push()
{
    int adress;
    float value;
    std::cin >> std::hex >> adress;
    if (adress > 256)
    {
        std::cout << "Index Out Of Range\n";
        error_count++;
    }
    else
    {
        value = mem.values[adress - 1];
        stack.push(value);
    }
}

void pop()
{
    int adress;
    std::cin >> std::hex >> adress;
    if (adress > 256)
    {
        std::cout << "Index Out Of Range\n";
        error_count++;
    }
    else
    {
        if(stack.empty())
        {
            std::cout << "Stack Underflow\n";
            error_count++;
        }
        else
        {
            mem.values[adress - 1] = stack.top();
            mem.adress.push_back(adress - 1);
            stack.pop();
        }
        
    }
}

void input()
{
    if (stack.size() <= 16)
    {
        float value;
        std::cin >> value;
        stack.push(value);
    }
    else
    {
        std::cout << "Stack Overflow\n";
        error_count++;
    }
}

std::string exec_operation(std::string &operation)
{
    lowercase(operation);
    switch (identify_operation(operation))
    {
    case 0:
        pushi();
        break;
    case 1:
        push();
        break;
    case 2:
        pop();
        break;
    case 3:
        input();
        break;
    case 4:
        // print(pilha, operacao);
        break;
    case 5:
        // add(pilha);
        break;
    case 6:
        // sub(pilha);
        break;
    case 7:
        // mul(pilha);
        break;
    case 8:
        // div(pilha, operacao);
        break;
    case 9:
        // swap(pilha);
        break;
    case 10:
        // drop(pilha, operacao);
        break;
    case 11:
        // dup(pilha);
        break;
    case 12:
        operation = "hlt";
        break;
    case 13:
        operation = "error";
        error_count++;
        break;
    }
    return operation;
}

int main()
{
    std::string operation;
    do
    {
        std::cin >> operation;
        exec_operation(operation);
    } while (operation != "hlt" && error_count < 1);
}