# HortiFruti Rodrigues

HortiFruti Rodrigues é uma aplicação de linha de comando que permite aos usuários gerenciar o inventário de café, vender café, acompanhar o saldo de vendas e realizar diversas outras operações. Este README fornece uma visão geral da aplicação e instruções para configurá-la e executá-la em sua máquina local.

## Features

- **Adicione um produto**: Adiciona um novo produto ao estoque, com valor e quantidade.
- **Venda de produto**: Vende uma produto do estoque, especificando pelo ID e quantidade e atualiza e acompanha o saldo de vendas.
- **Demonstrativo de Estoque**: Exibe o inventário atual, incluindo ID do café, nome, preço e quantidade.
- **Demonstrativo de Vendas**: Exibe o saldo total acumulado das vendas.
- **Remova um produto**: Remova um produto do inventário especificando seu ID. Atualiza o inventário de acordo.

## Pre Requerimentos

Para rodar o HortiFruti Rodrigues em sua maquina, você vai precisar instalar os seguites programas:
 
- C compiler (e.g., GCC)
- Standard C libraries

## Getting Started

1. Clone the repository to your local machine:

   ```bash
   git clone git@github.com:guilhermefariamartins/HortiFruti_Rodrigues.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Hortifruti
   ```

3. Compile the code using the C compiler:

   ```bash
   gcc -I .\include .\src\auth.c .\src\database.c .\src\main.c .\src\menu.c .\src\splash.c -O2 -g -Wall -o bin\horti.exe
   ```

4. Run the application:

   ```bash
   ./horti.exe
   ```



## Modo de uso

Quando rodar o executavel ele ira iniciar no menu de login, para logar é usar esses dados abaixos: 
- Username: admin
- Password: admin

Depois de ter conectado como administrador, você sera redirecionado para o menu principal onde tera acesso ao gerenciamento de usuarios e de estoque.