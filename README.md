# SCM - Matrix

## Visão Geral

Aplicação de processamento de imagens para extração de características. O algoritmo presente recebe uma imagem e retorna a Matriz de Coocorrência Estrutura (Structural Co-occurrence Matrix, SCM).

Foi utilizado o dataset Epistroma, que contém 547 imagens no formato pgm.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **Makefile:** Contém as instruções para compilar e construir o projeto.
- **lib:** Pasta contendo os cabeçalhos necessários para compilar o projeto.
- **main.c:** Utilizado para testar o projeto e executar as funcionalidades implementadas.
- **funcs.c:** Contém as principais funções responsáveis pela lógica do projeto.
- **utils.c:** Implementa as funções matemáticas necessárias para o funcionamento dos algoritmos.
- **pgm.c:** Contém funções para lidar com imagens em escala de cinza.

## Algoritmos Principais

1. **imageFilter:** Filtra uma imagem com base em um tamanho de kernel.
2. **quantizer:** Quantiza uma imagem de acordo com o nível de quantização escolhido.
3. **SCM:** Cria a SCM a partir das imagens quantizadas.
4. **algTest**: Executa todos os outros algoritmos. 

## Como Utilizar

Para utilizar o projeto, siga estas etapas:

1. Compile o projeto utilizando o Makefile.
2. Execute o arquivo gerado para testar as funcionalidades implementadas.
3. Siga as instruções apresentadas no console para interagir com o projeto.

## Eficiência dos Algoritmos

O dataset inteiro é processado em poucos minutos. Para o nível 8 com dimensões do filtro 3x3, o tempo total é de 32 segundos. Para o nível 256 com tamanho de filtro 7x7, o tempo total é de 2 minutos.