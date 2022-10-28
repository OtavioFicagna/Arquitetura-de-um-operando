#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

memory mem;
int error_count = 0; 
std::stack<float> stack;

struct memory
{
    float values[256];
    std::vector<int> adress;
};

std::string exec_operation(std::string &operation)
{
    lowercase(operation);
    switch (identify_operation(operation))
        {
        case 0:
            //pushi(pilha);
            break;
        case 1:
            //push(pilha, memoria, operacao);
            break;
        case 2:
            //pop(pilha, memoria, operacao, memoriaModif);
            break;
        case 3:
            //input(pilha);
            break;
        case 4:
            //print(pilha, operacao);
            break;
        case 5:
            //add(pilha);
            break;
        case 6:
            //sub(pilha);
            break;
        case 7:
            //mul(pilha);
            break;
        case 8:
            //div(pilha, operacao);
            break;
        case 9:
            //swap(pilha);
            break;
        case 10:
            //drop(pilha, operacao);
            break;
        case 11:
            //dup(pilha);
            break;
        case 12:
            //operacao = "hlt";
            break;
        case 13:
            //operacao = "erro";
            break;
        }
}

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
    std::string operations[qtdOps] = {"pushi", "push", "pop", "input", "print", "add", "sub", "mul", "div","swap", "drop", "dup", "hlt", "erro"};
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

int main()
{
    std::string operation; 
    do
    {
        std::cin >> operation;
        exec_operation(operation);
    } while (operation != "hlt" && error_count < 1);
    
}