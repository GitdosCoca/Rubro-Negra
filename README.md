# Rubro-Negra

# Estruturas de Dados I: Árvores Rubro-Negras (Red-Black Trees)

[cite_start]Este repositório contém o estudo teórico e a implementação prática de **Árvores Rubro-Negras**, uma estrutura de dados balanceada essencial para garantir eficiência em operações de busca, inserção e remoção[cite: 5, 6].

## 📖 Visão Geral

[cite_start]Uma árvore rubro-negra é uma árvore binária de busca (ABB) que utiliza um bit extra de informação por nó (cor: Vermelho ou Preto) para assegurar que a árvore permaneça aproximadamente balanceada[cite: 5].



### Propriedades Fundamentais (P1-P5)
[cite_start]Para ser considerada válida, a árvore deve satisfazer cinco regras estritas[cite: 7, 8]:
* [cite_start]**P1**: Todo nó é vermelho ou preto[cite: 9].
* [cite_start]**P2**: A raiz é sempre preta[cite: 10].
* [cite_start]**P3**: Toda folha (nó sentinela NIL) é preta[cite: 11].
* [cite_start]**P4**: Se um nó é vermelho, ambos os seus filhos são pretos (não há dois vermelhos consecutivos)[cite: 12].
* [cite_start]**P5**: Para qualquer nó, todos os caminhos até as folhas descendentes contêm o mesmo número de nós pretos (altura negra)[cite: 13].

---

## 📊 Análise de Complexidade

| Operação | ABB  | AVL      | Rubro-Negra |
| -------- | ---- | -------- | ----------- |
| Busca    | O(n) | O(log n) | O(log n)    |
| Inserção | O(n) | O(log n) | O(log n)    |
| Remoção  | O(n) | O(log n) | O(log n)    |


---

## 📝 Resolução das Atividades

### 1. Validação de Árvores
* **(a) Raiz vermelha com dois filhos pretos**: Inválida. [cite_start]Viola a propriedade **P2** (raiz deve ser preta)[cite: 281, 282].
* **(b) Raiz preta; filho esquerdo vermelho com filho esquerdo também vermelho**: Inválida. [cite_start]Viola a **P4** (vermelhos consecutivos) e afeta a **P3**[cite: 283, 284].
* **(c) Raiz preta; subárvores com alturas negras 3 e 2**: Inválida. [cite_start]Viola a **P5** (altura negra inconsistente)[cite: 285, 286].
* [cite_start]**(d) Raiz preta; nós internos pretos; caminhos de mesmo comprimento**: Válida[cite: 287, 289].

### 2. Simulação de Inserção (10, 20, 30, 15, 25)
[cite_start]Abaixo, o comportamento lógico durante a construção da árvore[cite: 290]:
1.  [cite_start]**Inserir 10**: Torna-se raiz preta[cite: 294].
2.  [cite_start]**Inserir 20**: Inserido à direita como vermelho[cite: 298].
3.  [cite_start]**Inserir 30**: Gera violação de vermelhos consecutivos; ocorre **rotação à esquerda** e recoloração[cite: 303].
4.  [cite_start]**Inserir 15**: Inserido à direita de 10 como vermelho[cite: 309].
5.  [cite_start]**Inserir 25**: Inserido à esquerda de 30 como vermelho para manter altura negra[cite: 316].

### 3. Perguntas Técnicas sobre Fixup
* [cite_start]**Violação Inicial**: A propriedade **P4** (vermelhos seguidos) é a mais comum após a inserção de um nó vermelho[cite: 356, 358].
* [cite_start]**Caso 1 (Tio Vermelho)**: O avô é pintado de vermelho para preservar a altura negra nos caminhos das subárvores[cite: 360, 362].
* [cite_start]**Caso 2 para Caso 3**: O Caso 2 (configuração em triângulo) realiza uma rotação para alinhar os nós, transformando o problema no Caso 3 (linha reta), facilitando a correção final com uma única rotação e recoloração[cite: 364, 366].

---


👥 Autores

    Eduardo Augusto Bozute 

    Luis Miguel Gomes Nascimento 

Este material foi desenvolvido como parte da disciplina de Estruturas de Dados I, sob orientação do Prof. Dr. Wallace Casaca (UNESP - IBILCE).
