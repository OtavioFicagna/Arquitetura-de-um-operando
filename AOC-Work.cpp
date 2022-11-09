#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

struct memory
{
    float values[256];
    std::vector<int> adress;
};

struct vm
{
    memory mem;
    bool error;
    std::stack<float> stack;
};

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

void pushi(vm &pc)
{
    if (pc.stack.size() <= 16)
    {
        float value;
        std::cin >> value;
        pc.stack.push(value);
    }
    else
    {
        std::cout << "Stack Overflow\n";
        pc.error = true;
    }
}

void push(vm &pc)
{
    int adress;
    float value;
    std::cin >> std::hex >> adress;
    if (adress > 256)
    {
        std::cout << "Index Out Of Range\n";
        pc.error = true;
    }
    else
    {
        value = pc.mem.values[adress - 1];
        pc.stack.push(value);
    }
}

void pop(vm &pc)
{
    int adress;
    std::cin >> std::hex >> adress;
    if (adress > 256)
    {
        std::cout << "Index Out Of Range\n";
        pc.error = true;
    }
    else
    {
        if(pc.stack.empty())
        {
            std::cout << "Stack Underflow\n";
            pc.error = true;
        }
        else
        {
            pc.mem.values[adress - 1] = pc.stack.top();
            pc.mem.adress.push_back(adress - 1);
            pc.stack.pop();
        }
        
    }
}

void input(vm &pc)
{
    if (pc.stack.size() <= 16)
    {
        float value;
        std::cin >> value;
        pc.stack.push(value);
    }
    else
    {
        std::cout << "Stack Overflow\n";
        pc.error = true;
    }
}

std::string exec_operation(std::string &operation, vm &pc)
{
    lowercase(operation);
    switch (identify_operation(operation))
    {
    case 0:
        pushi(pc);
        break;
    case 1:
        push(pc);
        break;
    case 2:
        pop(pc);
        break;
    case 3:
        input(pc);
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
        pc.error = true;
        break;
    }
    return operation;
}

int main()
{
    std::string operation;
    vm pc;
    pc.error = false;
    do
    {
        std::cin >> operation;
        exec_operation(operation, pc);
    } while (operation != "hlt" && !(pc.error));
}