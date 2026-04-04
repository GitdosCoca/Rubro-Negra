# Rubro-Negra

# Estruturas de Dados I: Árvores Rubro-Negras (Red-Black Trees)

Este repositório contém o estudo teórico e a implementação prática de **Árvores Rubro-Negras**, uma estrutura de dados balanceada essencial para garantir eficiência em operações de busca, inserção e remoção.

## 📖 Visão Geral

Uma árvore rubro-negra é uma árvore binária de busca (ABB) que utiliza um bit extra de informação por nó (cor: Vermelho ou Preto) para assegurar que a árvore permaneça aproximadamente balanceada.



### Propriedades Fundamentais (P1-P5)
Para ser considerada válida, a árvore deve satisfazer cinco regras estritas:
* **P1**: Todo nó é vermelho ou preto.
* **P2**: A raiz é sempre preta.
* **P3**: Toda folha (nó sentinela NIL) é preta.
* **P4**: Se um nó é vermelho, ambos os seus filhos são pretos (não há dois vermelhos consecutivos).
* **P5**: Para qualquer nó, todos os caminhos até as folhas descendentes contêm o mesmo número de nós pretos (altura negra).

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
* **(a) Raiz vermelha com dois filhos pretos**: Inválida. Viola a propriedade **P2** (raiz deve ser preta).
* **(b) Raiz preta; filho esquerdo vermelho com filho esquerdo também vermelho**: Inválida. Viola a **P4** (vermelhos consecutivos) e afeta a **P3**.
* **(c) Raiz preta; subárvores com alturas negras 3 e 2**: Inválida. Viola a **P5** (altura negra inconsistente).
* **(d) Raiz preta; nós internos pretos; caminhos de mesmo comprimento**: Válida.

### 2. Simulação de Inserção (10, 20, 30, 15, 25)
Abaixo, o comportamento lógico durante a construção da árvore:
1.  **Inserir 10**: Torna-se raiz preta.
2.  **Inserir 20**: Inserido à direita como vermelho.
3.  **Inserir 30**: Gera violação de vermelhos consecutivos; ocorre **rotação à esquerda** e recoloração.
4.  **Inserir 15**: Inserido à direita de 10 como vermelho.
5.  **Inserir 25**: Inserido à esquerda de 30 como vermelho para manter altura negra.

### 3. Perguntas Técnicas sobre Fixup
* **Violação Inicial**: A propriedade **P4** (vermelhos seguidos) é a mais comum após a inserção de um nó vermelho.
* **Caso 1 (Tio Vermelho)**: O avô é pintado de vermelho para preservar a altura negra nos caminhos das subárvores.
* **Caso 2 para Caso 3**: O Caso 2 (configuração em triângulo) realiza uma rotação para alinhar os nós, transformando o problema no Caso 3 (linha reta), facilitando a correção final com uma única rotação e recoloração.

---


👥 Autores

    Eduardo Augusto Bozute 

    Luis Miguel Gomes Nascimento 

Este material foi desenvolvido como parte da disciplina de Estruturas de Dados I, sob orientação do Prof. Dr. Wallace Casaca (UNESP - IBILCE).
