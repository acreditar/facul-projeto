#include "menu.h"

#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "auth.h"
#include "database.h"
#include "settings.h"
#include "user.h"
#include "utils.h"

void back_to_menu() {
    printf("\n \n");
    printf("Pressione qualquer tecla para voltar ao menu anterior...");
    getchar();  // Para consumir o caractere da nova linha anterior
}

void MENU_Show() {
    int choice;

    int exitIndex = s_AuthenticatedUser->admin ? 10 : 7;

    do {
        printf("███╗   ███╗███████╗███╗   ██╗██╗   ██╗ \n");
        printf("████╗ ████║██╔════╝████╗  ██║██║   ██║ \n");
        printf("██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║ \n");
        printf("██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║ \n");
        printf("██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝ \n");
        printf("╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝  \n");

        printf("2. Venda de produto \n");
        printf("3. Demonstrativo de Estoque \n");

        if (s_AuthenticatedUser && s_AuthenticatedUser->admin == true) {
            printf("1. Adicione um produto\n");
            printf("5. Remova um produto\n");
            printf("6. Gerenciamento de estoque(- para remover)\n");
            printf("4. Demonstrativo de Vendas \n");
            printf("7. Adicione um usuário\n");
            printf("8. Remova um usuário\n");
            printf("9. Listar usuários\n");
        }

        printf("%d. Sair do programa\n", exitIndex);

        printf("Escolha uma opção e pressione enter: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada invalida. Por favor, insira um número.\n");

            while (getchar() != '\n');

            system("cls");
        }

        system("cls");

        switch (choice) {
            case 1:
                add_prod();
                break;
            case 2:
                venda_prod();
                break;
            case 3:
                demonstra_estoque();
                getch();
                break;
            case 4:
                demonstra_venda();
                getch();
                break;
            case 5:
                del_prod();
                break;
            case 6:
                ger_estoque();
                break;
            case 7:
                MENU_AddUser();
                break;
            case 8:
                MENU_RemoveUser();
                getch();
                break;
            case 9:
                MENU_ListUsers();
                getch();
                break;
            default:
                if (choice != exitIndex) {
                    printf("Tente novamente, a opção escolhida é invalida.\n");
                }
                break;
        }

        if (choice == exitIndex) {
            printf("Saindo do programa...");
            Sleep(SHUTDOWN_COOLDOWN_IN_MILLISECONDS);
            exit(EXIT_SUCCESS);
        }

        printf("\n");
        system("cls");
    } while (choice != exitIndex);
}

void MENU_AddUser() {
    if (!s_AuthenticatedUser || !s_AuthenticatedUser->admin) {
        return;
    }

    char username[USER_MAX_USERNAME_LENGTH];

    printf("Digite o nome do novo usuário:");
    scanf("%s", username);

    char password[USER_MAX_PASSWORD_LENGTH];

    printf("Digite a senha do novo usuário:");
    scanf("%s", password);

    if (DATABASE_WriteUser(username, password, false) == EXIT_SUCCESS) {
        printf("Novo usuário registrado com sucesso!");
    } else {
        printf("Erro ao criar novo usuário.");
    }
}

void MENU_RemoveUser() {
    if (!s_AuthenticatedUser || !s_AuthenticatedUser->admin) {
        return;
    }

    int id = 0;

    printf("Digite o id do usuário para remover:");
    scanf("%d", &id);

    if (DATABASE_RemoveUser(id) == EXIT_SUCCESS) {
        printf("Usuário removido com sucesso!");
    } else {
        printf("Erro ao remover o usuário especificado.");
    }
}

void MENU_ListUsers() {
    if (!s_AuthenticatedUser || !s_AuthenticatedUser->admin) {
        return;
    }

    printf("=============================================================\n");

    FILE* file = fopen(DATABASE_FILE_PATH, "rb");

    if (file == NULL) {
        printf("Erro ao abrir a database de usuários.\n");
        return;
    }

    User user;

    printf("Usuários registrados:\n");
    printf("%-15s %-15s %-15s %-15s\n", "Id", "Nome", "Senha", "Administrador");
    printf("-------------------------------------------------------------\n");

    while (fread(&user, sizeof(User), 1, file) == 1) {
        printf("%-15d %-15s %-15s %-15d\n", user.id, user.name, user.password, user.admin);
    }

    fclose(file);
}

void add_prod() {
    char prod_name[MAX_PROD_NAME_LENGTH];
    char unidade[3];
    float preco;
    int quantidade;

    printf(" █████╗ ██████╗ ██╗ ██████╗██╗ ██████╗ ███╗   ██╗ █████╗ ██████╗     ██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ \n");
    printf("██╔══██╗██╔══██╗██║██╔════╝██║██╔═══██╗████╗  ██║██╔══██╗██╔══██╗    ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
    printf("███████║██║  ██║██║██║     ██║██║   ██║██╔██╗ ██║███████║██████╔╝    ██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
    printf("██╔══██║██║  ██║██║██║     ██║██║   ██║██║╚██╗██║██╔══██║██╔══██╗    ██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
    printf("██║  ██║██████╔╝██║╚██████╗██║╚██████╔╝██║ ╚████║██║  ██║██║  ██║    ██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
    printf("╚═╝  ╚═╝╚═════╝ ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ \n");
    int continuar = 1;
    while (continuar) {
        printf("Digite o nome do produto: ");
        scanf("%s", prod_name);

        // Verifica se o produto já existe
        FILE* file = fopen("database.txt", "r");
        if (file != NULL) {
            char line[100];
            int prod_id;
            char existing_name[MAX_PROD_NAME_LENGTH];
            float existing_price;
            int existing_quantity;
            char existing_unidade[3];

            while (fgets(line, sizeof(line), file)) {
                sscanf(line, "%d,%[^,],%f,%d,%s", &prod_id, existing_name, &existing_price, &existing_quantity, existing_unidade);
                if (strcmp(existing_name, prod_name) == 0) {
                    printf("Esse produto já existe.\n");
                    Sleep(2000);
                    back_to_menu();  // Retorna ao menu anterior
                    return;
                }
            }
            fclose(file);
        } else {
            createDatabaseFile();
        }

        printf("Digite o preço do produto: ");
        scanf("%f", &preco);
        printf("Digite a quantidade do produto: ");
        scanf("%d", &quantidade);
        printf("Escolha a unidade de medida ('un' para unidade ou 'kg' para quilograma): ");
        scanf("%s", unidade);

        file = fopen("database.txt", "r");
        int id = 0;
        if (file != NULL) {
            char line[100];
            int current_id;
            while (fgets(line, sizeof(line), file)) {
                sscanf(line, "%d,", &current_id);
                if (current_id > id) {
                    id = current_id;
                }
            }
            fclose(file);
        }
        id++;

        file = fopen("database.txt", "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        fprintf(file, "%d,%s,%.2f,%d,%s\n", id, prod_name, preco, quantidade, unidade);
        fclose(file);

        printf("Produto adicionado com sucesso com ID %d!\n", id);
        printf("Deseja adicionar outro produto? (1-Sim, 0-Nao): ");
        scanf("%d", &continuar);
    }
    back_to_menu();  // Retorna ao menu após adicionar o produto
}

typedef struct {
    int id;
    char nome[MAX_PROD_NAME_LENGTH];
    float preco;
    int quantidade;
} ItemVendido;

void venda_prod() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("▄▄███▄▄·               ██████╗ █████╗ ██╗██╗  ██╗ █████╗               ▄▄███▄▄· \n");
    printf("██╔════╝              ██╔════╝██╔══██╗██║╚██╗██╔╝██╔══██╗              ██╔════╝ \n");
    printf("███████╗    █████╗    ██║     ███████║██║ ╚███╔╝ ███████║    █████╗    ███████╗ \n");
    printf("╚════██║    ╚════╝    ██║     ██╔══██║██║ ██╔██╗ ██╔══██║    ╚════╝    ╚════██║ \n");
    printf("███████║              ╚██████╗██║  ██║██║██╔╝ ██╗██║  ██║              ███████║ \n");
    printf("╚═▀▀▀══╝               ╚═════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝  ╚═╝              ╚═▀▀▀══╝ \n");

    int continuar = 1;
    ItemVendido recibo[100];  // Armazena até 100 itens vendidos na transação
    int numItensVendidos = 0;
    float totalVenda = 0.0;

    while (continuar) {
        printf("Digite o ID do produto para realizar a venda ou digite 'back' para cancelar: ");
        char input[10];
        scanf("%s", input);

        if (strcmp(input, "back") == 0) {
            printf("Venda cancelada. Retornando ao menu...\n");
            Sleep(1);
            return;
        }

        int id = atoi(input);
        int quantidade;

        printf("Digite a quantidade do produto a ser vendido: ");
        scanf("%s", input);

        if (strcmp(input, "back") == 0) {
            printf("Venda cancelada. Retornando ao menu...\n");
            Sleep(1);
            return;
        }

        quantidade = atoi(input);

        FILE* file = fopen("database.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro ao criar arquivo temporário.\n");
            fclose(file);
            return;
        }

        char line[100];
        int found = 0;

        while (fgets(line, sizeof(line), file)) {
            int prod_id;
            char prod_name[MAX_PROD_NAME_LENGTH];
            float preco;
            int estoque_qtd;
            char unidade[3];

            sscanf(line, "%d,%[^,],%f,%d,%s", &prod_id, prod_name, &preco, &estoque_qtd, unidade);

            if (prod_id == id) {
                found = 1;
                if (quantidade <= estoque_qtd) {
                    int updatedquantidade = estoque_qtd - quantidade;
                    fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, updatedquantidade, unidade);

                    // Adiciona o item ao recibo
                    recibo[numItensVendidos].id = prod_id;
                    strcpy(recibo[numItensVendidos].nome, prod_name);
                    recibo[numItensVendidos].preco = preco;
                    recibo[numItensVendidos].quantidade = quantidade;
                    totalVenda += preco * quantidade;
                    numItensVendidos++;

                    printf("Deseja adicionar outro produto? (1-Sim, 0-Nao): ");
                    scanf("%d", &continuar);

                    FILE* balanceFile = fopen("balance.txt", "a");
                    if (balanceFile == NULL) {
                        printf("Erro ao abrir o arquivo 'balance'.\n");
                        fclose(file);
                        fclose(tempFile);
                        return;
                    }

                    float valor_total = preco * quantidade;
                    fprintf(balanceFile, "ID: %d,Produto: %s,Valor: %.2f\n", prod_id, prod_name, valor_total);
                    fclose(balanceFile);
                } else {
                    printf("Quantidade insuficiente no estoque.\n");
                    fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, estoque_qtd, unidade);
                    Sleep(2);
                }
            } else {
                fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, estoque_qtd, unidade);
            }
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove("database.txt");
            rename("temp.txt", "database.txt");
        } else {
            printf("Produto não encontrado.\n");
            Sleep(1);
            remove("temp.txt");
        }
    }

    // Imprimir o recibo com formatação corrigida
    printf("\nRecibo de Venda:\n");
    printf("Produto          Quantidade    Preço (R$)    Total (R$)\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < numItensVendidos; i++) {
        float valor_total_item = recibo[i].preco * recibo[i].quantidade;
        printf("%-15s %-14d %-14.2f %-14.2f\n", recibo[i].nome, recibo[i].quantidade, recibo[i].preco, valor_total_item);
    }

    printf("--------------------------------------------------------\n");
    printf("Total da venda: R$ %.2f\n", totalVenda);
    printf("\nData da venda: %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("Produto(s) vendido(s) com sucesso!\n");
    getch();
}

void demonstra_estoque() {
    printf("███████╗███████╗████████╗ ██████╗  ██████╗ ██╗   ██╗███████╗\n");
    printf("██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔═══██╗██║   ██║██╔════╝\n");
    printf("█████╗  ███████╗   ██║   ██║   ██║██║   ██║██║   ██║█████╗\n");
    printf("██╔══╝  ╚════██║   ██║   ██║   ██║██║▄▄ ██║██║   ██║██╔══╝\n");
    printf("███████╗███████║   ██║   ╚██████╔╝╚██████╔╝╚██████╔╝███████╗\n");
    printf("╚══════╝╚══════╝   ╚═╝    ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝\n");
    printf("ID\tNome do Produto\t\tPreco\t\tQuantidade\tUnidade\n");
    printf("=========================================================================\n");

    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        int prod_id;
        char prod_name[MAX_PROD_NAME_LENGTH];
        float preco;
        int quantidade;
        char unidade[3];

        sscanf(line, "%d,%[^,],%f,%d,%s", &prod_id, prod_name, &preco, &quantidade, unidade);

        // Ajusta a largura da coluna Nome do Produto para garantir alinhamento
        printf("%-8d%-20s\t%-8.2f\t%-10d\t%s\n", prod_id, prod_name, preco, quantidade, unidade);
    }
    back_to_menu();  // Retorna ao menu após adicionar o produto
    fclose(file);
}

void demonstra_venda() {
    // Obter a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Exibir a arte ASCII
    printf("▄▄███▄▄·    ██╗   ██╗███████╗███╗   ██╗██████╗  █████╗ ███████╗    ▄▄███▄▄·\n");
    printf("██╔════╝    ██║   ██║██╔════╝████╗  ██║██╔══██╗██╔══██╗██╔════╝    ██╔════╝\n");
    printf("███████╗    ██║   ██║█████╗  ██╔██╗ ██║██║  ██║███████║███████╗    ███████╗\n");
    printf("╚════██║    ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║██║  ██║██╔══██║╚════██║    ╚════██║\n");
    printf("███████║     ╚████╔╝ ███████╗██║ ╚████║██████╔╝██║  ██║███████║    ███████║\n");
    printf("╚═▀▀▀══╝      ╚═══╝  ╚══════╝╚═╝  ╚═══╝╚═════╝ ╚═╝  ╚═╝╚══════╝    ╚═▀▀▀══╝\n");

    // Abrir e ler o arquivo balance
    FILE* balanceFile = fopen("balance.txt", "r");
    if (balanceFile == NULL) {
        printf("Erro ao abrir o arquivo 'balance'.\n");
        return;
    }

    float total_vendas = 0.0;
    char line[100];

    printf("\nLista de itens vendidos:\n");
    printf("Produto\t\tValor (R$)\n");
    printf("----------------------------\n");

    while (fgets(line, sizeof(line), balanceFile)) {
        // Procurar pelo nome do produto
        char* produto_ptr = strstr(line, "Produto: ");
        char* valor_ptr = strstr(line, "Valor: ");

        if (produto_ptr != NULL && valor_ptr != NULL) {
            // Extrair o nome do produto
            produto_ptr += 9;  // Tamanho de "Produto: " é 9 caracteres
            char produto[50];
            sscanf(produto_ptr, "%[^,]", produto);  // Lê até a vírgula

            // Extrair e converter o valor
            valor_ptr += 7;  // Tamanho de "Valor: " é 7 caracteres
            float valor = atof(valor_ptr);

            // Exibir o produto e o valor
            printf("%-15s %.2f\n", produto, valor);

            // Somar ao total de vendas
            total_vendas += valor;
        }
    }

    fclose(balanceFile);

    printf("----------------------------\n");
    printf("Total de vendas realizadas em R$: %.2f\n", total_vendas);
    printf("\nData da venda: %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    back_to_menu();  // Função para retornar ao menu, se existir
}

void del_prod() {
    printf("██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗     ██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗\n");
    printf("██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗    ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗\n");
    printf("██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██████╔╝    ██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
    printf("██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗    ██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║\n");
    printf("██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██║  ██║    ██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝\n");
    printf("╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝\n");

    int id;
    int continuar = 1;
    while (continuar) {
        printf("Informe o ID do produto que deseja remover: ");
        scanf("%d", &id);

        // Abre o arquivo data base para ler e escreve
        FILE* file = fopen("database.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Criando um arquivo temporário para os produtos removidos
        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro ao criar um arquivo temporário.\n");
            fclose(file);
            return;
        }

        char line[150];
        int found = 0;

        // Lê o arquivo original e faz uma cópia para o arquivo temporário, exceto para os itens removidos
        while (fgets(line, sizeof(line), file)) {
            int prod_id;
            char prod_name[MAX_PROD_NAME_LENGTH];
            float preco;
            int quantidade;
            char unidade[3];

            // Lê o produto com a unidade incluída
            sscanf(line, "%d,%[^,],%f,%d,%s", &prod_id, prod_name, &preco, &quantidade, unidade);

            // Escreve no arquivo temporário se o produto não for o que será removido
            if (prod_id != id) {
                fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, quantidade, unidade);
            } else {
                found = 1;
            }
        }

        fclose(file);
        fclose(tempFile);

        // Substitui o arquivo original pelo temporário
        if (found) {
            remove("database.txt");
            rename("temp.txt", "database.txt");
            printf("Deseja remover outro produto? (1-Sim, 0-Nao): ");
            scanf("%d", &continuar);
            printf("Produto removido com sucesso!\n");
            Sleep(1);
        } else {
            remove("temp.txt");
            printf("Produto não encontrado.\n");
            Sleep(1);
        }
    }
}
void ger_estoque() {
    printf(" ██████╗ ███████╗██████╗        ███████╗███████╗████████╗ ██████╗  ██████╗ ██╗   ██╗███████╗\n");
    printf("██╔════╝ ██╔════╝██╔══██╗       ██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔═══██╗██║   ██║██╔════╝\n");
    printf("██║  ███╗█████╗  ██████╔╝       █████╗  ███████╗   ██║   ██║   ██║██║   ██║██║   ██║█████╗\n");
    printf("██║   ██║██╔══╝  ██╔══██╗       ██╔══╝  ╚════██║   ██║   ██║   ██║██║▄▄ ██║██║   ██║██╔══╝\n");
    printf("╚██████╔╝███████╗██║  ██║██╗    ███████╗███████║   ██║   ╚██████╔╝╚██████╔╝╚██████╔╝███████╗\n");
    printf(" ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝    ╚══════╝╚══════╝   ╚═╝    ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝\n\n");

    int id;
    int quantidade;
    int continuar = 1;

    while (continuar) {
        printf("Digite o ID do produto que deseja atualizar: ");
        scanf("%d", &id);
        printf("Digite a quantidade do produto a ser atualizada: ");
        scanf("%d", &quantidade);

        FILE* file = fopen("database.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro ao criar arquivo temporário.\n");
            fclose(file);
            return;
        }

        char line[100];
        int found = 0;

        while (fgets(line, sizeof(line), file)) {
            int prod_id;
            char prod_name[MAX_PROD_NAME_LENGTH];
            float preco;
            int estoque_qtd;
            char unidade[3];

            sscanf(line, "%d,%[^,],%f,%d,%s", &prod_id, prod_name, &preco, &estoque_qtd, unidade);

            if (prod_id == id) {
                found = 1;
                int updatedquantidade = estoque_qtd + quantidade;

                if (updatedquantidade < 0) {
                    printf("Atualização falhou! A quantidade resultaria em um estoque negativo.\n");
                    fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, estoque_qtd, unidade);
                    printf("Deseja adicionar outro produto? (1-Sim, 0-Nao): ");
                    scanf("%d", &continuar);

                    // back_to_menu(); // Retorna ao menu após adicionar o produto
                    // getch();
                } else {
                    fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, updatedquantidade, unidade);
                    printf("Produto atualizado com sucesso!\n");
                    printf("Deseja adicionar outro produto? (1-Sim, 0-Nao): ");
                    scanf("%d", &continuar);
                    // back_to_menu(); // Retorna ao menu
                    // getch ();
                }

            } else {
                fprintf(tempFile, "%d,%s,%.2f,%d,%s\n", prod_id, prod_name, preco, estoque_qtd, unidade);
            }
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove("database.txt");
            rename("temp.txt", "database.txt");
        } else {
            printf("Produto não encontrado.\n");
            remove("temp.txt");
        }
    }
}