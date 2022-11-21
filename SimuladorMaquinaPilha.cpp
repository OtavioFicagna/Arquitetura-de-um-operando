#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

struct memory //ESTRUTURA PARA GUARDAR OS ENDEREÇOS DE MEMÓRIA MODIFICADOS E A MEMÓRIA EM SI
{
    float values[256];
    std::vector<int> adress;
};

struct vm //ESTRUTRA PARA CRIAÇÃO DO "PC" QUE EXECUTA AS OPERAÇÕES
{
    memory mem;
    bool error;
    std::stack<float> stack;
};

std::string lowercase(std::string &str) //PASSA A STRING DIGITADA PARA MINÚSCULO
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
    return str;
}

int identify_operation(std::string operacao) //IDENTIFICA A OPERÇÃO DIGITADA OU RETORNA ERRO
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

void pushi(vm &pc) //INSERE NA PILHA O VALOR ESPECIFICADO
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

void push(vm &pc) //INSERE NA PILHA UM VALOR QUE ESTÁ NA MEMORIA
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
        bool aux = false;
        for(int i : pc.mem.adress)
        {
            if(i == adress - 1) //VERIFICA SE O ENDEREÇO DE MEMÓRIA DIGITADO CONTÉM VALOR
            {
                value = pc.mem.values[adress - 1];
                pc.stack.push(value);
                aux = true;
            }
        }
        if(aux == false)
        {
            std::cout << "Endereço de memoria vazio\n";
            pc.error = true; 
        }
        
    }
}

void pop(vm &pc) //RETIRA O VALOR DA PILHA E INSERE NA MEMÓRIA
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
        if (pc.stack.empty())
        {
            std::cout << "Stack Underflow\n";
            pc.error = true;
        }
        else
        {
            pc.mem.values[adress - 1] = pc.stack.top(); //ADICIONA O VALOR NA MEMÓRIA NO INDICE CORRETO
            if (pc.mem.adress.empty())
                pc.mem.adress.push_back(adress - 1);
            for (int i = 0; i < pc.mem.adress.size(); i++)
            {
                if (pc.mem.adress[i] != (adress - 1)) //VERIFICA SE O ENDEREÇO JÁ EXISTE NO VETOR
                    pc.mem.adress.push_back(adress - 1);
            }
            pc.stack.pop();
        }
    }
}

void input(vm &pc) //RECEBE UM VALOR E INSERE NA PILHA
{
    if (pc.stack.size() <= 16)
    {
        float value;
        std::string input;
        std::cout << "Digite um valor: ";
        std::getline(std::cin >> std::ws, input);
        value = std::stof(input);
        pc.stack.push(value);
    }
    else
    {
        std::cout << "Stack Overflow\n";
        pc.error = true;
    }
}

void print(vm &pc) //PRINTA O VALOR DO TOPO DA PILHA
{
    if (pc.stack.empty())
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
    {
        std::cout << pc.stack.top() << std::endl;
        pc.stack.pop();
    }
}
void add(vm &pc) //EFETUA A ADIÇÃO
{
    if (pc.stack.size() < 2)
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
    {
        float a = pc.stack.top();
        pc.stack.pop();
        float b = pc.stack.top();
        pc.stack.pop();
        pc.stack.push(b + a);
    }
}
void sub(vm &pc) //EFETUA A SUBTRAÇÃO
{
    if (pc.stack.size() < 2)
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
    {
        float a = pc.stack.top();
        pc.stack.pop();
        float b = pc.stack.top();
        pc.stack.pop();
        pc.stack.push(b - a);
    }
}
void mul(vm &pc) //EFETUA A MULTIPLICAÇÃO
{
    if (pc.stack.size() < 2)
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
    {
        float a = pc.stack.top();
        pc.stack.pop();
        float b = pc.stack.top();
        pc.stack.pop();
        pc.stack.push(b * a);
    }
}
void div(vm &pc) //EFETUA A DIVISÃO
{
    if (pc.stack.size() < 2)
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else if (pc.stack.top() == 0)
    {
        std::cout << "Zero division error\n";
        pc.error = true;
    }
    else
    {
        float a = pc.stack.top();
        pc.stack.pop();
        float b = pc.stack.top();
        pc.stack.pop();
        pc.stack.push(b * a);
    }
}
void swap(vm &pc) //INVERTE A POSIÇÃO DE DOIS VALORES DA PILHA
{
    if (pc.stack.size() < 2)
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
    {
        float v1, v2;
        v1 = pc.stack.top();
        pc.stack.pop();
        v2 = pc.stack.top();
        pc.stack.pop();
        pc.stack.push(v1);
        pc.stack.push(v2);
    }
}
void drop(vm &pc) //RETIRA O VALOR DO TOPO DA PILHA
{
    if (pc.stack.empty())
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
        pc.stack.pop();
}
void dup(vm &pc) //DUPLICA O VALOR DO TOPO DA PILHA
{
    if (pc.stack.empty())
    {
        std::cout << "Stack Underflow\n";
        pc.error = true;
    }
    else
        pc.stack.push(pc.stack.top());
}
std::string exec_operation(std::string &operation, vm &pc) //BUSCA E CHAMA A FUNÇÃO QUE EXECUTARA A OPERAÇÃO 
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
        print(pc);
        break;
    case 5:
        add(pc);
        break;
    case 6:
        sub(pc);
        break;
    case 7:
        mul(pc);
        break;
    case 8:
        div(pc);
        break;
    case 9:
        swap(pc);
        break;
    case 10:
        drop(pc);
        break;
    case 11:
        dup(pc);
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
void end(vm &pc)
{
    if (pc.error)
        std::cout << "PROGRAMA TERMINADO COM ERRO!\n";
    else
    {
        std::cout << "PROGRAMA TERMINADO COM EXITO!\n";
        if (pc.stack.empty())
        {
            std::cout << "PILHA ESTA VAZIA!\n";
        }
        else
        {
            std::cout << "VALORES NA PILHA:\n";
            while (!pc.stack.empty())
            {
                std::cout << pc.stack.top() << std::endl;
                pc.stack.pop();
            }
        }
        if (pc.mem.adress.empty())
        {
            std::cout << "NENHUM ENDERECO DE MEMORIA FOI MODIFICADO\n";
        }
        else
        {
            int i = 0;
            std::cout << "ENDERECOS DE MEMORIA MODIFICADOS:\n";
            while (i < pc.mem.adress.size())
            {
                std::stringstream aux;
                aux << std::hex << pc.mem.adress[i] + 1;
                std::string res = aux.str();
                int j = 0;
                while (res[j] != '\0')
                {
                    res[j] = toupper(res[j]);
                    j++;
                }
                std::cout << "Endereco " << res << " = " << pc.mem.values[(pc.mem.adress[i])] << std::endl;
                i++;
            }
        }
    }
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
    end(pc);
}