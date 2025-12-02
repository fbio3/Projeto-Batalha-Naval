# 🚢 Batalha Naval - Projeto PIF 2025.2

**Disciplina:** PIF - Projetos de Sistemas de Informação  
**Professor:** João Victor Tinoco

## 👨‍💻 Autores
* **[ Fabio Henrique Dantas Layme Lopes de Albuquerque ]**
* **[ Felipe Borba De Carvalho ]**
* **[ Francisco Rodrigues de Oliveira Junior ]**

---

## 📝 Sobre o Projeto
Implementação completa do clássico jogo **Batalha Naval** utilizando a linguagem **C**. O projeto foi desenvolvido com foco em **Structs, Ponteiros**, **Alocação Dinâmica de Memória** e **fluxos básicos de controle**, sem o uso de bibliotecas gráficas externas.

O objetivo principal é demonstrar o domínio sobre alocação dinâmica (`malloc`, `realloc`, `free`), manipulação de ponteiros, structs e modularização de código.

---

## ⚙️ Funcionalidades Implementadas

### 1. Sistema de Configuração
* O jogo permite definir o **tamanho do tabuleiro** (de 6x6 a 26x26).
* Escolha entre modo de posicionamento **Manual** ou **Automático**.
* As configurações podem ser alteradas através de um menu dedicado antes do início da partida.

### 2. Posicionamento de Frotas
* **Automático:** Algoritmo inteligente que distribui os navios aleatoriamente, garantindo que não haja sobreposição ou saída dos limites do mapa.
* **Manual:** Interface interativa onde o jogador escolhe coordenada e orientação. O sistema possui validação matemática em tempo real para impedir navios fora do tabuleiro.

### 3. Validação Robusta (Anti-Crash)
* O sistema de entrada (`io.c`) é blindado contra entradas inválidas.
* Impede erros comuns como digitar letras em campos numéricos ou coordenadas inexistentes (ex: "Z99" em mapa 10x10).
* Uso de `fgets` para evitar estouro de buffer (*buffer overflow*).

---

## 🛠️ Destaques Técnicos (Requisitos do Projeto)

* **Alocação Dinâmica de Tabuleiro:** O tabuleiro é alocado como um vetor linearizado (`malloc`), acessado via aritmética de ponteiros para otimização de memória.
* **Frota Dinâmica:** A lista de navios utiliza `realloc` para crescer conforme necessário durante a inicialização.
* **Structs:** Uso de estruturas para encapsular dados de `Jogador`, `Navio`, `Tabuleiro` e `Configurações`.
* **Modularização:** Separação clara de responsabilidades:
  * `game.c`: Lógica de jogo e turnos.
  * `board.c`: Gerenciamento de memória do tabuleiro.
  * `fleet.c`: Gerenciamento da frota.
  * `io.c`: Tratamento de entrada e saída.

---

## 🚀 Como Compilar e Rodar

### Opção 1: Via GCC (Windows/Linux/Mac) "Testado no visual code"
Esta é a forma manual e garantida de funcionar em qualquer terminal.
Na pasta raiz do projeto, execute:

```
    gcc src/main.c src/board.c src/fleet.c src/game.c src/io.c -o batalha_naval
```

Em seguida execute:

## Para Windows (no terminal)
```
    .\batalha_naval.exe
```

## Para Linux/Mac (no terminal)
```
    ./batalha_naval
```

### Opção 2: Via Makefile (Se disponível) "Testado no Kali linux"
Se você estiver em ambiente Linux ou com MinGW configurado.
Na pasta raiz do projeto, execute:

```
    make
    
    make run
```
