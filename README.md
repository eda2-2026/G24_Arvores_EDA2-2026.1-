# Estrutura de Dados 2 - algoritmos de busca

Repositório destinado ao trabalho de algoritmos de busca da disciplina de estrutura de dados 2

## Alunos
| Matrícula   | Aluno                              |
|-------------|------------------------------------|
|  202045348  | Ingrid Alves Rocha   |
| 202016168   | Eric Camargo da Silva              |

## Sobre 

Este projeto demonstra a aplicação prática do **Algoritmo Greedy (Guloso)** para resolver o problema clássico do troco, utilizando como base o sistema monetário brasileiro. O objetivo é calcular a menor quantidade possível de cédulas para um determinado valor em reais.

O algoritmo funciona tomando a melhor decisão local a cada passo: ele sempre seleciona a maior cédula disponível que seja menor ou igual ao valor restante, repetindo o processo até que o valor seja zerado.

### Principais Características:
* **Eficiência:** Execução otimizada com complexidade de tempo $O(n)$, onde $n$ é o número de tipos de cédulas.
* **Confiabilidade:** Uso de representação em centavos (inteiros) para evitar erros de precisão de ponto flutuante comuns em Python.
* **Interface Gráfica:** Implementação amigável utilizando a biblioteca `Tkinter`.
* **Testes Unitários:** Validação de casos extremos e prova de otimalidade com `pytest`.


---

## Screenshots

## Instalação
### Pré-requisitos
- Python 3.10 ou superior
- `tkinter` (já incluso no Python padrão)
- `pytest` (apenas para rodar os testes)

### Passo a passo

```bash
# 1. Clone o repositório
git clone https://github.com/SEU_USUARIO/caixa-eletronico-greedy.git
cd caixa-eletronico-greedy

# 2. (Opcional) Crie um ambiente virtual
python -m venv venv
source venv/bin/activate      # Linux/macOS
venv\Scripts\activate         # Windows

# 3. Instale dependências
pip install -r requirements.txt

# 4. Execute a interface gráfica
python interface.py

# 5. Execute os testes
python -m pytest test_greedy.py -v
```

---

## Uso

Após realizar a instalação conforme o passo a passo anterior, siga as instruções abaixo para utilizar o simulador de Caixa Eletrônico:

1.  **Inicie a aplicação:**
    ```bash
    python interface.py
    ```
2.  **Interação com a Interface:**
    * No campo de entrada, digite o **valor desejado** (ex: `388`).
    * Clique no botão **Calcular** (ou pressione Enter).
3.  **Resultado:**
    * O sistema exibirá a listagem detalhada de quantas notas de cada valor serão necessárias.
    * Exemplo para R$ 388: 1 de R$200, 1 de R$100, 1 de R$50, 1 de R$20, 1 de R$10, 1 de R$5, 1 de R$2 e 1 de R$1.
4.  **Execução de Testes:**
    Para verificar a integridade do algoritmo de busca por troco, execute:
    ```bash
    python -m pytest test_greedy.py -v
    ```

---

## Videos de Apresentação

<table border="1" style="width: 100%; text-align: center;">
    <thead>
        <tr>
            <th>Descrição</th>
            <th>Link</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td></td>
            <td><a href="">Assistir no YouTube</a></td>
        </tr>
        <tr>
            <td> </td>
            <td><a href="">Assistir no YouTube</a></td>
        </tr>
    </tbody>
</table>
