#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

// DEIXA A STRING DA OPERACAO TODA EM MÍNUSCULO PARA EVITAR ERRO DE DIGITAÇÃO
string min(string &str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
    return str;
}
// VALIDA A OPERAÇÃO E RETORNA SEU CASO OU SE A OPERAÇÃO FOR INVÁLIDA ACABA O PROGRAMA
int op(string &operacao)
{
    const int qtdOps = 14;
    int caso = 0;
    string operacoes[qtdOps] = {"pushi", "push", "pop", "input", "print", "add", "sub", "mul", "div",
                                "swap", "drop", "dup", "hlt", "erro"};
    while (caso < qtdOps)
    {
        if (operacoes[caso] == operacao)
        {
            return caso;
        }
        caso++;
    }
    return 13;
}

void pushi(stack<float> &pilha)
{
    float valor;
    cin >> valor;
    pilha.push(valor);
}

void push(stack<float> &pilha, float memoria[], string &operacao)
{
    int endereco;
    float valor;
    cin >> hex >> endereco;
    if (endereco > 256)
    {
        cout << "ERRO: VERIFIQUE O ENDERECO DE MEMORIA ESPECIFICADO";
        operacao = "erro";
    }
    else
    {
        valor = memoria[endereco - 1];
        pilha.push(valor);
    }
}

void pop(stack<float> &pilha, float memoria[], string &operacao, vector<int> &modif)
{
    int endereco;
    cin >> hex >> endereco;
    if (endereco > 256)
    {
        cout << "ERRO: VERIFIQUE O ENDERECO DE MEMORIA ESPECIFICADO";
        operacao = "erro";
    }
    else
    {
        memoria[endereco - 1] = pilha.top();
        modif.push_back(endereco - 1);
        pilha.pop();
    }
}

void input(stack<float> &pilha)
{
    float aux;
    cin >> aux;
    pilha.push(aux);
}

void print(stack<float> &pilha, string &operacao)
{
    float valor;
    if (pilha.empty())
    {
        cout << "Stack Underflow\n";
        operacao = "erro";
    }
    else
    {
        cout << pilha.top() << endl;
        pilha.pop();
    }
}

void add(stack<float> &pilha)
{
    float res, a, b;
    a = pilha.top();
    pilha.pop();
    b = pilha.top();
    pilha.pop();
    res = b + a;
    pilha.push(res);
    cout << b << " + " << a << " = " << res << endl;
}

void sub(stack<float> &pilha)
{
    float res, a, b;
    a = pilha.top();
    pilha.pop();
    b = pilha.top();
    pilha.pop();
    res = b - a;
    pilha.push(res);
    cout << b << " - " << a << " = " << res << endl;
}

void mul(stack<float> &pilha)
{
    float res, a, b;
    a = pilha.top();
    pilha.pop();
    b = pilha.top();
    pilha.pop();
    res = b * a;
    pilha.push(res);
    cout << b << " X " << a << " = " << res << endl;
}

void div(stack<float> &pilha, string &operacao)
{
    float res, a, b;
    a = pilha.top();
    if (a == 0)
    {
        cout << "Impossivel Dividir por zero\n";
        operacao = "erro";
    }
    else
    {
        pilha.pop();
        b = pilha.top();
        pilha.pop();
        res = b / a;
        pilha.push(res);
        cout << b << " / " << a << " = " << res << endl;
    }
}

void swap(stack<float> &pilha)
{
    float a, b;
    a = pilha.top();
    pilha.pop();
    b = pilha.top();
    pilha.pop();
    pilha.push(a);
    pilha.push(b);
}

void drop(stack<float> &pilha, string &operacao)
{
    if (pilha.empty())
    {
        cout << "Stack Underflow\n";
        operacao = "erro";
    }
    else
    {
        pilha.pop();
    }
}

void dup(stack<float> &pilha)
{
    pilha.push(pilha.top());
}

void end(stack<float> &pilha, float memoria[], string operacao, vector<int> memoriaModif)
{
    if (operacao == "erro")
        cout << "PROGRAMA TERMINADO COM ERRO!\n";
    else
    {
        cout << "PROGRAMA TERMINADO COM EXITO!\n";
        if (pilha.empty())
        {
            cout << "PILHA ESTA VAZIA!\n";
        }
        else
        {
            cout << "VALORES NA PILHA:\n";
            while (!pilha.empty())
            {
                cout << pilha.top() << endl;
                pilha.pop();
            }
        }
        if (memoriaModif.empty())
        {
            cout << "NENHUM ENDERECO DE MEMORIA FOI MODIFICADO\n";
        }
        else
        {
            int i = 0;
            cout << "ENDERECOS DE MEMORIA MODIFICADOS:\n";
            while (i < memoriaModif.size())
            {
                stringstream aux;
                aux << hex << memoriaModif[i] + 1;
                string res = aux.str();
                int j = 0;
                while (res[j] != '\0')
                {
                    res[j] = toupper(res[j]);
                    j++;
                }
                cout << "Endereco " << res << " = " << memoria[(memoriaModif[i])] << endl;
                i++;
            }
            
        }
    }
}

int main()
{
    float memoria[256];
    vector<int> memoriaModif;
    stack<float> pilha;
    string operacao;
    do
    {
        cin >> operacao;
        operacao = min(operacao);
        switch (op(operacao))
        {
        case 0:
            pushi(pilha);
            break;
        case 1:
            push(pilha, memoria, operacao);
            break;
        case 2:
            pop(pilha, memoria, operacao, memoriaModif);
            break;
        case 3:
            input(pilha);
            break;
        case 4:
            print(pilha, operacao);
            break;
        case 5:
            add(pilha);
            break;
        case 6:
            sub(pilha);
            break;
        case 7:
            mul(pilha);
            break;
        case 8:
            div(pilha, operacao);
            break;
        case 9:
            swap(pilha);
            break;
        case 10:
            drop(pilha, operacao);
            break;
        case 11:
            dup(pilha);
            break;
        case 12:
            operacao = "hlt";
            break;
        case 13:
            operacao = "erro";
            break;
        }
    } while (operacao != "hlt" && operacao != "erro");
    end(pilha, memoria, operacao, memoriaModif);
}