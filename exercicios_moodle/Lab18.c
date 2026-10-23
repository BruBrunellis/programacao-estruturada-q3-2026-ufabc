/*
Laboratório 05 - Estruturas e Arquivos
L05_01 - RSA

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87377
Consultado em 23/10/2026. Formatação normalizada para comentário em C.

Implementação do RSA

O objetivo deste exercício é implementar as funcionalidades de encriptação
e decriptação do algoritmo RSA, utilizando a exponenciação modular.
As operações devem ser realizadas caractere por caractere de uma string
de entrada, utilizando números que se encaixam no tipo unsigned long long
do C. O programa deverá ser capaz de ler chaves pública e privada em
hexadecimal. Para encriptação, ele lê uma palavra (string) e gera uma
sequência hexadecimal dos caracteres cifrados. Para decriptação, ele lê
uma sequência hexadecimal de caracteres cifrados e gera a palavra original.

Algoritmo RSA

O sistema de criptografia de chave pública RSA se baseia na espetacular
diferença entre a facilidade de encontrar números primos grandes e a
dificuldade de fatorar o produto de dois números primos grandes.
Cada participante gera um par de chaves: uma chave pública, que pode ser
compartilhada abertamente, e uma chave secreta (ou privada), que deve ser
mantida em sigilo. Um participante cria suas chaves pública e secreta
com o seguinte procedimento:

    1. Selecione aleatoriamente dois números primos p e q, tais que p != q.
    2. Calcule n = pq.
    3. Selecione um inteiro ímpar pequeno e tal que e seja primo com
       phi(n), que é igual a (p - 1)(q - 1).
    4. Calcule d como o inverso multiplicativo de e, módulo phi(n).
    5. Divulgue o par P = (e, n) como a chave pública RSA do participante.
    6. Mantenha o par S = (d, n) em segredo como a chave secreta RSA
       do participante.

Aplicação Prática do RSA

Uma das aplicações práticas mais comuns e importantes do RSA é a
comunicação segura e as assinaturas digitais. O enunciado apresenta como
exemplo o acesso a um site seguro (HTTPS): o navegador usa a chave pública
do site para encriptar uma chave de sessão (uma chave simétrica usada
para a comunicação principal, que é mais rápida). O servidor usa sua
chave privada para decriptar essa chave de sessão e, a partir daí,
a comunicação é segura e privada.

Tamanhos de Chave RSA Padrão de Segurança:
Para fins de segurança real, as chaves utilizadas na prática são
significativamente maiores do que as que podem ser manipuladas por um
unsigned long long. O enunciado cita chaves de 2048, 3072 ou 4096 bits.
Neste exercício simplificado, utilizamos unsigned long long e números
de no máximo 64 bits.

As operações de encriptação e decriptação são realizadas da seguinte forma:
    - Encriptação: converta um caractere M_char em um número M
      ('a' -> 0, 'b' -> 1, ..., 'z' -> 25). Com a chave pública (e, n):
          C = M^e mod n
    - Decriptação: com a chave privada (d, n), calcule:
          M = C^d mod n
      Converta M de volta para M_char (0 -> 'a', ..., 25 -> 'z').

Exponenciação Modular (MODULAR-EXPONENTIATION)

A exponenciação modular é uma maneira eficiente de calcular
base^expoente mod modulo. Este algoritmo é fundamental para o RSA,
pois permite realizar operações com potências e módulos de forma
controlada, mantendo os números dentro dos limites do tipo de dados
e evitando cálculos desnecessariamente grandes.

Pseudocódigo fornecido (versão da direita para a esquerda):

    MODULAR-EXPONENTIATION(base, expoente, modulo)
    1  resultado = 1
    2  base_atual = base % modulo // Garante base menor que o módulo
    3  exp = expoente

    4  while (exp > 0) {
    5      if (exp é ímpar) { // Bit menos significativo igual a 1
               resultado = MULTIPLY-MOD(resultado, base_atual, modulo);
    6      }
           base_atual = MULTIPLY-MOD(base_atual, base_atual, modulo);
    7      exp = exp / 2 // Desloca bits para a direita (divisão inteira)
    8  }
    9  return resultado

Exemplo de Execução da Exponenciação Modular

    base = 7, expoente = 560, modulo = 561.
    Representação binária de 560: 1000110000.
    Inicialização: resultado = 1, base_atual = 7 % 561 = 7, exp = 560.

Tabela transcrita do Moodle (valores e operações preservados):
    Iteração | exp | exp binário | Ímpar? | resultado
    Início   | 560 | 1000110000  | Não    | 1
    1        | 560 | 1000110000  | Não    | 1
    2        | 280 | 100011000   | Não    | 1
    3        | 140 | 10001100    | Não    | 1
    4        |  70 | 1000110     | Não    | 1
    5        |  35 | 100011      | Sim    | (1 * 286) % 561 = 286
    6        |  17 | 10001       | Sim    | (286 * 154) % 561 = 343
    7        |   8 | 1000        | Não    | 343
    8        |   4 | 100         | Não    | 343
    9        |   2 | 10          | Não    | 343
    10       |   1 | 1           | Sim    | (343 * 379) % 561 = 103
    Fim      |   0

    Iteração | base_atual (operação)
    Início   | 7
    1        | (7 * 7) % 561 = 49
    2        | (49 * 49) % 561 = 145
    3        | (145 * 145) % 561 = 163
    4        | (163 * 163) % 561 = 286
    5        | (286 * 286) % 561 = 154
    6        | (154 * 154) % 561 = 103
    7        | (103 * 103) % 561 = 484
    8        | (484 * 484) % 561 = 196
    9        | (196 * 196) % 561 = 379
    10       | (379 * 379) % 561 = 445

Resultado final informado no enunciado: resultado = 103.

Dicas de Implementação

    1. multiply_mod(unsigned long long a, unsigned long long b,
                    unsigned long long m)
       Calcula (a * b) % m de forma segura, evitando overflow.
       Utiliza um método de "multiplicação russa" baseado em operações
       de adição e divisão por 2 para garantir que os resultados
       intermediários não excedam unsigned long long.
       Recebe três unsigned long long (a, b, m) e retorna
       um unsigned long long.

    2. modular_exponentiation(unsigned long long base,
                              unsigned long long exponent,
                              unsigned long long modulus)
       Implementa exponenciação modular por elevação ao quadrado repetida.
       Recebe base, exponent e modulus como unsigned long long e retorna
       base^exponent % modulus também como unsigned long long.
       Utiliza multiply_mod em todas as multiplicações, garantindo
       segurança contra overflow.

    3. encrypt_string(const char* plaintext_word, unsigned long long e_key,
                      unsigned long long n_modulus, size_t* out_len)
       Propósito: encripta uma string de texto claro caractere por caractere.
       Parâmetros:
           plaintext_word: string de caracteres 'a'-'z' a encriptar.
           e_key: expoente da chave pública (e).
           n_modulus: módulo da chave pública (n).
           out_len: ponteiro para size_t onde será armazenado o número
                    de elementos no array de saída.
       Retorno: ponteiro para um array de unsigned long long contendo
       os valores cifrados, alocado dinamicamente com malloc.
       A função chamadora deve liberá-lo com free.
       Retorna NULL em caso de erro de alocação ou palavra de entrada vazia.

    4. decrypt_string(const unsigned long long* ciphertext_array,
                      size_t ciphertext_len, unsigned long long d_key,
                      unsigned long long n_modulus)
       Propósito: decripta um array de valores cifrados, convertendo-os
       de volta para uma string de texto claro.
       Parâmetros:
           ciphertext_array: ponteiro para o array de unsigned long long
                             contendo os valores cifrados.
           ciphertext_len: número de elementos no ciphertext_array.
           d_key: expoente da chave privada (d).
           n_modulus: módulo da chave privada (n).
       Retorno: ponteiro char* para a palavra decriptada, alocada
       dinamicamente com malloc. A função chamadora deve liberá-la
       com free. Retorna NULL em caso de erro de alocação.

    5. print_result(const void* data, size_t len, char type_flag)
       Propósito: imprime os resultados formatados na saída padrão.
       Parâmetros:
           data: ponteiro genérico const void* para os dados;
                 unsigned long long* para encriptados ou char*
                 para decriptados.
           len: número de elementos (arrays cifrados) ou caracteres
                (strings decriptadas) a imprimir.
           type_flag: 'E' para valores encriptados, impressos em
                      hexadecimal separados por espaço; 'D' para
                      dados decriptados, impressos como string.

    6. main()
       - Lê a operação ('E' ou 'D') e as chaves em hexadecimal.
       - Lê a entrada apropriada: string de texto claro para encriptar
         ou sequência de hexadecimais para decriptar.
       - Chama encrypt_string ou decrypt_string para processar a entrada.
       - Chama print_result para exibir o resultado.
       - Libera com free() a memória alocada por encrypt_string
         e decrypt_string após o uso.
       - Retorna 0 para sucesso e 1 para falha.

Dicas Adicionais
    - Utilize unsigned long long para todas as variáveis numéricas
      que representam chaves e valores.
    - Mapeamento caractere-número:
          M = ch - 'a'; // 'a'-'z' para 0-25
          ch = M + 'a'; // 0-25 para 'a'-'z'
    - Entrada hexadecimal: %llx com scanf para unsigned long long.
    - Saída hexadecimal: %llX com printf para hexadecimal maiúsculo.
    - Para converter string hexadecimal para unsigned long long:
          valor = strtoull(cipher_text, &endptr, 16);
      strtoull converte na base 16; endptr aponta para o caractere
      logo após o número convertido.

Exemplos de Entrada e Saída do Programa

Par de chaves utilizado nos exemplos (em hexadecimal):
    Chave Pública: e = 10001, n = 2273D04C69E5
    Chave Privada: d = 20B50064A08D, n = 2273D04C69E5

Exemplo 1 - Entrada:
    E
    10001 2273D04C69E5
    universidade
Saída (uma única linha):
    12C420DEDD81 1AF04D038002 1B9C3A31BFA8 6B590C04A07 219F86304AFC B13B30F5A20 15FABF73CE1E 1B9C3A31BFA8 510D1AB48A0 0 510D1AB48A0 219F86304AFC

Exemplo 2 - Entrada (a sequência cifrada ocupa uma única linha):
    D
    20B50064A08D 2273D04C69E5
    12C420DEDD81 1AF04D038002 1B9C3A31BFA8 6B590C04A07 219F86304AFC B13B30F5A20 15FABF73CE1E 1B9C3A31BFA8 510D1AB48A0 0 510D1AB48A0 219F86304AFC
Saída:
    universidade
*/
