#ifndef MENU_H
#define MENU_H
#define MAX_PROD_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100
/**
 * @brief Exibe o menu principal do sistema de gerenciamento.
 *
 * Mostra as opções disponíveis ao usuário, como adicionar um produto, vender um produto, exibir o estoque
 * de produtos, deletar um produto do e visualizar o saldo acumulado no sistema de gerenciamento.
 */
void MENU_Show();

/**
 * @brief Adiciona um novo produto ao estoque.
 *
 * Solicita ao usuário as informações necessárias para adicionar um novo produto ao estoque, sendo seu nome,
 * quantidade e preço, e o armazena no estoque.
 */
void MENU_AddProduct();

/**
 * @brief Realiza a venda de um produto do estoque.
 *
 * Solicita ao usuário as informações necessárias para vender um produto do estoque, sendo seu nome e
 * quantidade. A quantidade do produto é decrementada conforme a venda é realizada.
 */
void MENU_SellProduct();

/**
 * @brief Exibe a lista de produtos no estoque.
 *
 * Mostra todos os produtos atualmente disponíveis no estoque, incluindo informações como o nome, quantidade
 * e preço de cada item.
 */
void MENU_ShowStock();

/**
 * @brief Remove um produto do estoque.
 *
 * Solicita ao usuário as informações necessárias para remover um produto do estoque, sendo seu identificador
 * numérico.
 */
void MENU_DeleteProduct();

/**
 * @brief Exibe o saldo acumulado no sistema de gerenciamento.
 *
 * Mostra o valor total obtido com as vendas realizadas.
 */
void MENU_ShowBalance();

void MENU_AddUser();

void MENU_RemoveUser();

void MENU_ListUsers();

#endif
