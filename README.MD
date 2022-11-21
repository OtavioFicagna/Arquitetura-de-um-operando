<h1 align="center"> SIMULADOR DE ARQUITETURA ZERO OPERANDOS</h1>

### Simples simulador de uma arquitetura de zero operandos (PILHA) escrita em C++.
## INFORMAÇÕES IMPORTANTES
- [Características](#características)
- [Utilização](#utilização)
- [Operações](#operações)
- [Autores](#autores)

## Características:
* Dados float de 32 bits
* Arquitetura de Harvard, mas simular apenas a memória de dados.
* Endereços de memória de 8 bits (00..FF) com palavras de 32 bits.
* Pilha com espaço para 16 valores.
* Toda a pilha e a memória do computador está inicialmente zerada.
* O simulador não é 'case sensitive'.

## Utilização:
1. Compile e execute o arquivo Simulador_ZeroOperandos.cpp
2. Insira as operações desejadas corretamente *Lembre que o programa não é case sensitive
3. Caso não haja nenhum erro você pode digitar hlt para terminar o programa
* Obs: Caso utilize um redirecionamento de arquivo como entrada, coloque o valor digitado ao lado da função input, exemplo: input 10.

### Exemplo de utilização:
```
PUSHI 3.1415   # Insere o valor do PI na pilha
INPUT          # Lê um valor para R e insere na pilha
DUP            # Duplica R na pilha
MUL            # Calcula R*R
MUL            # Multiplica por PI
DUP            # Duplica valor no topo
PRINT          # Exibe resultado
POP 80         # Armazena o valor no endereço 80 (variável A)
HLT            # Encerra execução
```

## Operações:
- [pushi](#pushi-valor)
- [push](#push-endereço)
- [pop](#pop-endereço)
- [input](#input)
- [print](#print)
- [add](#add)
- [sub](#sub)
- [mul](#mul)
- [div](#div)
- [swap](#swap)
- [drop](#drop)
- [dup](#dup)
- [hlt](#hlt)

### pushi valor:
**Descrição:**
- Insere na pilha o valor imediato especificado como operando da instrução. Exemplo: PUSHI 3.1415.

### push endereço:
**Descrição:**
- Insere na pilha uma cópia do valor contido no endereço (hexadecimal) especificado da memória. Exemplo: PUSH 8A.

### pop endereço:
**Descrição:**
- Retira um valor da pilha e copia-o para endereço (hexadecimal) especificado da memória.  Exemplo: POP 8A.

### input:
**Descrição:**
- Lê um número float do dispositivo de entrada padrão e insere-o na pilha.

### print:
**Descrição:**
- Lê um número float do dispositivo de entrada padrão e insere-o na pilha.
### add:
**Descrição:**
- Retira dois valores da pilha (A e B, na ordem de retirada), calcula B+A  e empilha o resultado.

### sub:
**Descrição:**
- Retira dois valores da pilha (A e B, na ordem de retirada), calcula B-A  e empilha o resultado.

### mul:
**Descrição:**
- Retira dois valores da pilha (A e B, na ordem de retirada), calcula B*A  e empilha o resultado.

### div:
**Descrição:**
- Retira dois valores da pilha (A e B, na ordem de retirada), calcula B/A  e empilha o resultado.

### swap:
**Descrição:**
- Inverte a ordem dos dois valores no topo da pilha.

### drop:
**Descrição:**
- Descarta o valor no topo da pilha.

### dup:
**Descrição:**
- Insere na pilha uma cópia do atual valor no topo, ou seja, duplica na pilha o valor do topo.

### hlt:
**Descrição:**
- Encerra a execução do programa e sai do simulador.

## Autores:
- Otávio Augusto Ficagna
- Gabriel Rodrigues de Lara Junqueira
- Rafael Antônio Zanoni