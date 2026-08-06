#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limites do sistema exigidos (PDF)
#define MAX_PRODUTOS 200
#define MAX_CATEGORIAS 6

// Lista fixa de categorias permitidas no sistema (PDF Item 4)
const char CATEGORIAS_VALIDAS[MAX_CATEGORIAS][50] = {
    "Material de escritorio",
    "Material de limpeza",
    "Equipamentos",
    "Componentes eletronicos",
    "Ferramentas",
    "Acessorios"
};

// ESTRUTURA DO PRODUTO (PDF Item 3)

typedef struct {
    int codigo;             // Código de identificação único
    char nome[100];         // Nome do produto
    char categoria[50];     // Categoria do produto
    int qtd_disponivel;     // Quantidade disponível em estoque
    int qtd_minima;         // Quantidade mínima recomendada
    float valor_unitario;   // Valor unitário do produto
    int situacao;           // Situação: 1 = Ativo, 2 = Indisponível, 3 = Descontinuado
} Produto;

// VARIÁVEIS GLOBAIS COMPARTILHADAS

Produto estoque[MAX_PRODUTOS]; // Vetor com capacidade para até 200 produtos
int total_produtos = 0;        // Contador de produtos atualmente cadastrados

// PROTÓTIPOS DAS FUNÇÕES
int buscarIndicePorCodigo(int codigo);
int validarCategoria(const char *cat);
int produtoEstaAtivo(int indice);
void exibirMenuPrincipal();

//  Funções (protótipos): Vívian 
void cadastrarProduto();
void consultarProdutoPorCodigo();
void consultarProdutoPorNome();
void consultarProdutosPorSituacao();
void listarTodosProdutos();
void alterarProduto();
void excluirOuDescontinuarProduto();
void ordenarProdutosPorNome();
void ordenarProdutosPorQuantidade();
void salvarDados();
void carregarDados();
void encerrarSistema();
//  Funções (protótipos): Rebeca 
void registrarEntrada();
void registrarSaida();
void consultarProdutosPorCategoria();
void consultarProdutosAbaixoDoMinimo();
void consultarProdutosSemEstoque();
void relatorioPorCategoria();
void ordenarProdutosPorValorUnitario();
void exibirValorIndividualEstoque();
void calcularValorTotalEstoque();
void buscarProdutoMaiorValorUnitario();
void buscarProdutoMaiorValorArmazenado();

// FUNÇÃO MAIN
int main() {
    
}