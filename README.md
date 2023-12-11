# 🚛Projeto_de_Grafos 🦟

## 📃 Sobre

Este projeto foi desenvolvido na disciplina GBC042 - Teoria dos Grafos. O trabalho foi realizado pelos estudantes Marcus Vinícius Almeida Florêncio, Cauã Pereira Neres e Maria Fernanda Gouveia.

No repositório **Projeto_de_Grafos**, é possível encontrar o código completo do programa no arquivo **main (7).c**, bem como o arquivo **Slides Projeto de Grafos.pdf**. Nele, encontram-se os slides com a explicação completa e detalhada sobre o trabalho.

## 📖 Contexto
Uberlândia está na lista das cidades mineiras que mais possuem casos de dengue. Atualmente, foram constatados mais de 127 mil casos e 70 mortes de dengue no município.

Algumas atitudes têm sido tomadas pela Prefeitura Municipal de Uberlândia, como a utilização de carros de fumacê, que objetivam eliminar os mosquitos. Apesar disso, a doença retorna anualmente. 

O caminhão do fumacê é um veículo que aplica inseticidas para combater o mosquito Aedes aegypti. O uso do fumacê é uma medida aplicada para controlar a dengue, mas é importante que o caminhão seja utilizado de forma eficiente para que o combate seja eficaz. 

Um dos principais problemas do fumacê é a sua eficiência limitada. Como o fumacê é aplicado na forma de fumaça, ele pode não atingir todos os mosquitos adultos, especialmente aqueles que estão abrigados em locais fechados ou que estão em movimento.


## 🎯 Objetivo
Otimizar o combate à dengue na cidade de Uberlândia, encontrando o caminho mais curto para que o caminhão do fumacê percorra todas as ruas contaminadas da cidade.

## 🧠 Modelagem
- As ruas são modeladas como arestas do grafo;
- Os vértices podem ou não serem focos de dengue;
- O peso de cada aresta representa o comprimento das ruas.

## 💻 Visão Geral do Programa
Os inputs são:
- quantidade de vértices
- as ruas juntamente com suas distâncias
- vértices contaminados
- local de início do carro do fumacê

O output gera:
- Menor caminho
- Distância total

Para encontrar o menor caminho foi o utilizado o algoritmo Dijkstra com fila de prioridade.
