/*
Laboratório 05 - Estruturas e Arquivos
L05_03 - Filtragem Linear

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87387
Consultado em 23/10/2026. Formatação normalizada para comentário em C.
Exemplos em imagens transcritos conforme exibidos no Moodle.
Arquivos de exemplo disponibilizados na seção do laboratório:
    https://moodle.ufabc.edu.br/mod/resource/view.php?id=87388

Filtragem Linear

O objetivo é simular as funcionalidades encontradas em softwares de
edição de imagem, como o GIMP e o Adobe Photoshop.

1. Introdução à Filtragem Linear

Softwares de edição de imagens, como o GIMP e o Adobe Photoshop, são
ferramentas comuns no dia a dia de designers e usuários de redes sociais.
Eles oferecem diversos filtros para aprimorar imagens, ajustar contraste,
eliminar ruídos ou, simplesmente, deixá-las mais bonitas. Um dos algoritmos
fundamentais por trás desses filtros é a convolução.

2. Conceitos Fundamentais de Imagem Digital

Uma imagem digital em níveis de cinza (tons do preto ao branco) é composta
por pixels (picture elements) ou, genericamente, spels (space elements).
Pode ser vista como uma matriz I de m linhas e n colunas, onde cada pixel
tem uma posição (i,j) e um valor de brilho (intensidade) I(i,j).
Neste trabalho, as intensidades estarão no intervalo fechado [0, 255].

O domínio de uma imagem corresponde ao conjunto de todas as coordenadas
válidas: (0,0), (0,1), ..., (m-1,n-1). A ordenação dos pixels segue a
leitura de cima para baixo e da esquerda para a direita.

Figura 1: visualização dos brilhos de uma pequena região de uma imagem
em cinza. Adaptado da documentação de convolução da Apple:
    https://developer.apple.com/library/ios/documentation/Performance/Conceptual/vImage/ConvolutionOperations/ConvolutionOperations.html
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%281%29.png

3. A Operação de Convolução

Suponha uma imagem de entrada I, de domínio Di, armazenada em uma matriz
de m linhas e n colunas. Um pixel na posição (i,j) tem valor I(i,j).
A convolução consiste em aplicar, para cada pixel (i,j), uma função
matemática Lambda sobre sua vizinhança e armazenar o resultado em uma
nova imagem J de mesmo domínio e dimensão de I. O efeito final depende
do tipo de função aplicada.

Para especificar essa função, define-se um filtro: uma matriz K de
domínio Dk, cujos valores são chamados pesos ou coeficientes.
Para um filtro 3 x 3:
    k1 k2 k3
    k4 k5 k6
    k7 k8 k9

A função aplicada ao pixel (i,j) corresponde a:
    J(i,j) = Lambda(I,i,j,K)
           = k1 * I(i-1,j-1) + k2 * I(i-1,j) + k3 * I(i-1,j+1)
           + k4 * I(i,j-1)   + k5 * I(i,j)   + k6 * I(i,j+1)
           + k7 * I(i+1,j-1) + k8 * I(i+1,j) + k9 * I(i+1,j+1)

O peso central k5 é multiplicado por I(i,j). Os demais pesos são
multiplicados pelos brilhos dos pixels vizinhos de (i,j).
Ilustração do filtro:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%284%29.png

Figura 2: exemplo de convolução entre filtro e imagem para o pixel (4,3).
    J(4,3) = 4*0 + 9*0 + 8*1 + 6*(-2) + 11*(-1) + 4*2
             + 1*(-1) + 4*0 + 19*1 = 11
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%285%29.png

Figura 3: outro exemplo visual de convolução entre uma imagem e um filtro.
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%287%29.png

3.1. Tratamento de Bordas (Vizinhanças Parciais)

Quando o filtro não se encaixa completamente na imagem, considere apenas
os pixels cujos pesos correspondem a coordenadas válidas dentro da imagem.
O peso central do filtro DEVERÁ SEMPRE multiplicar uma coordenada (i,j)
válida da entrada I. O resultado é atribuído à mesma coordenada (i,j)
na saída J.

Figura 4: convolução na borda da imagem, com alguns pesos fora do domínio.
    J(0,0) = 1*(-1) + 12*2 + 8*0 + 5*1 = 28
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%288%29.png

Figura 5: visualização de diferentes convoluções aplicadas a uma imagem.
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%289%29.png

4. Objetivo

Implemente a operação de convolução em imagens usando C.
Utilize registros (structs) para representar a imagem e o filtro.
    - Brilhos dos pixels e pesos dos filtros são inteiros.
    - Implemente uma função que realize a convolução entre a imagem
      de entrada e o filtro, gerando uma nova imagem.
    - Truncamento: resultados menores que 0 tornam-se 0; maiores que
      255 tornam-se 255. Nenhum pixel resultante pode sair de [0, 255].
    - Os filtros possuem uma coordenada central bem definida.
    - Dimensões máximas da imagem: 600 x 600 pixels.

5. Especificações de Implementação

Os arquivos de entrada serão fornecidos como parâmetros de linha de
comando. O primeiro (imagem) estará em argv[1]; o segundo (filtro),
em argv[2]. Ambos devem ser lidos em modo texto.

5.1. Formato de Entrada

5.1.1. Arquivo de Imagem (argv[1])

Formato PGM (Portable Graymap). As três primeiras linhas são o cabeçalho:
    - Primeira: string "P2", indicando o formato; deve ser desconsiderada.
    - Segunda: dois inteiros n (largura/colunas) e m (altura/linhas),
      respectivamente.
    - Terceira: valor máximo de cinza, sempre 255.
As m linhas seguintes contêm os brilhos, com n valores em cada linha.

Exemplo de imagem de entrada (transcrito da figura):
    P2
    10 4
    255
    120 0 0 0 0 0 0 0 0 0
    120 0 0 0 0 0 255 255 0 0
    120 0 0 0 0 0 255 255 0 0
    120 0 0 0 0 0 0 0 0 0
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%2810%29.png

5.1.2. Arquivo de Filtro (argv[2])

Arquivo texto simples:
    - Primeira linha: q (colunas) e p (linhas), respectivamente.
    - As p linhas seguintes contêm os pesos, com q valores por linha.

Exemplo de filtro:
    3 3
    -1 0 1
    -2 0 2
    -1 0 1

5.2. Formato de Saída

Imprima na saída padrão (tela) a imagem resultante no formato PGM:
    - As três primeiras linhas devem conter os mesmos dados de cabeçalho
      da imagem original.
    - As seguintes contêm os brilhos resultantes, separados por
      EXATAMENTE um caractere em branco entre cada valor.
    - Cada linha termina com uma quebra de linha.
    - Observação importante: após o brilho do ÚLTIMO pixel de cada linha,
      também deve haver um espaço antes da quebra de linha.

Exemplo de saída apresentado na figura do enunciado:
    P2
    10 4
    255
    120 0 0 0 0 0 0 0 0 0
    120 0 0 0 0 0 255 255 0 0
    120 0 0 0 0 0 255 255 0 0
    120 0 0 0 0 0 0 0 0 0
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%2811%29.png

6. Dicas
    - Não modifique os arquivos de entrada: abra-os somente para leitura.
    - Utilize argc e argv na assinatura:
          int main(int argc, char *argv[])
    - Utilize um editor de texto para analisar os brilhos dos pixels
      das imagens de entrada, saída e dos filtros.
    - Imagens dos testes (ex.: imagemXX.pgm) podem ser visualizadas
      por editores ou visualizadores compatíveis com PGM.
    - Para executar e guardar o resultado em resultado.pgm:
          ./seu_programa imagem.pgm filtro.txt > resultado.pgm

7. Exemplos de Execução

Exemplo 1 - argv[1] (imagem):
    P2
    5 5
    255
    0 0 0 0
    10 10 10 5 5
    10 0 10 5 0
    10 10 10 5 5
    20 20 20 40 40
argv[2] (filtro):
    3 1
    -1 0 1
Saída:
    P2
    5 5
    255
    0 0 0 0
    10 0 0 0 0
    0 0 5 0 0
    10 0 0 0 0
    20 0 20 20 0
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%2813%29.png

Exemplo 2 - argv[1] (imagem):
    P2
    10 4
    255
    10 10 10 10 0 0 0 0 0 0
    10 10 10 10 0 0 0 255 255 0
    25 25 25 25 0 0 0 255 255 0
    25 25 25 25 0 0 0 0 0 0
argv[2] (filtro):
    3 3
    -1 -2 -1
    0 0 0
    1 2 1
Saída:
    P2
    10 4
    255
    30 40 40 30 10 0 255 255 255 255 255
    45 60 60 45 15 0 255 255 255 255 255
    45 60 60 45 15 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195435/mod_vpl/intro/image%20%2812%29.png

Nota de transcrição: os exemplos acima preservam as figuras do Moodle.
No Exemplo 1, a primeira linha de pixels da entrada e da saída tem
apenas quatro valores, apesar da largura declarada de cinco.
No Exemplo 2, as duas primeiras linhas de pixels da saída têm onze
valores, apesar da largura declarada de dez. Os espaços finais exigidos
pela especificação estão descritos na seção 5.2, mas não são representados
como espaços ao final das linhas deste comentário.

8. Observações

Para comparar a saída com um arquivo de referência, pode-se usar kdiff3,
disponível para Linux, macOS e Windows:
    https://kdiff3.sourceforge.net/
*/
