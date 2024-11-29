#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"

/**
 * @def USERNAME_MAX_LENGTH
 * @brief A quantidade máxima de caracteres que o nome de usuário pode ter.
 */
#ifndef USERNAME_MAX_LENGTH
#define USERNAME_MAX_LENGTH 20 
#endif

/**
 * @def PASSWORD_MAX_LENGTH
 * @brief A quantidade máxima de caracteres que a senha pode ter.
 */
#ifndef PASSWORD_MAX_LENGTH
#define PASSWORD_MAX_LENGTH 20
#endif

/**
 * @def PASSWORD_MAX_ATTEMPTS
 * @brief A quantidade máxima de vezes em que o usuário pode falhar ao tentar realizar um login no sistema.
 */
#ifndef PASSWORD_MAX_ATTEMPTS
#define PASSWORD_MAX_ATTEMPTS 3
#endif

extern User* s_AuthenticatedUser;

/**
 * @brief Tenta autenticar o usuário com as credenciais fornecidas.
 *
 * Solicita ao usuário as informações necessárias para realizar um login no sistema de gerenciamento
 * de produtos, sendo um nome de usuário e uma senha.
 * 
 * @param username O nome de usuário fornecido para autenticação.
 * @param password A senha fornecida para autenticação.
 * 
 * @return Retorna 1 se a autenticação for bem-sucedida; caso contrário, retorna um código de erro.
 */
int AUTH_AuthenticateUser(char* username, char* password);

/**
 * @brief Exibe o painel de login e tenta autenticar o usuário.
 *
 * Mostra a interface de login, onde o usuário pode inserir suas credenciais. Após a entrada, chama a 
 * função de autenticação para verificar o acesso.
 */
void AUTH_ShowPanel();

#endif