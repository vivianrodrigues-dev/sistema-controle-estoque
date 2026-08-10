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
    int opcao;

    do {
        printf("\n====================================\n");
        printf("   SISTEMA DE CONTROLE DE ESTOQUE   \n");
        printf("====================================\n");
        printf("1. Cadastrar produto\n");
        printf("17. Sair\n");
        printf("====================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(); 
                break;
            case 17:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 17);

    return 0;
}

// vai percorrer o vetor estoque pra achar o produto e retornar seu indice 
// se não achar (-1)
int buscarIndicePorCodigo(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            return i; 
        }
    }
    return -1; 
}

// Retorna 1 se a categoria for valida e 0 se for invalida
int validarCategoria(const char *cat) {
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        // strcmp retorna 0 se as duas palavras forem EXATAMENTE iguais
        if (strcmp(cat, CATEGORIAS_VALIDAS[i]) == 0) {
            return 1; // Encontrou uma correspondencia valida
        }
    }
    return 0; // Nao encontrou na lista de validas
}
void cadastrarProduto(){

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    if (total_produtos >= MAX_PRODUTOS) {
        printf("Erro: Limite maximo de 200 produtos atingido!\n");
        return;

}
// variavel temp pra ler dados do novo produto
Produto p; 

getchar(); // limpa o Enter que ficou no teclado após escolher a opção no main

printf("\nDigite o codigo do produto: ");
    scanf("%d", &p.codigo);

getchar(); // pra limpar o enter do código para não atrapalhar o fgets do nome

// validação código único, não pode ter repetido
if (buscarIndicePorCodigo(p.codigo) != -1) {
        printf("\nErro: O codigo %d ja esta cadastrado!\n", p.codigo);
        return;
}

do {
        printf("\nDigite o nome do produto: ");
        fgets(p.nome, 100, stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';

        if (strlen(p.nome) == 0) {
            printf("Erro: O nome do produto e obrigatorio!\n");
        }
    } while (strlen(p.nome) == 0);

do {
        printf("Digite a categoria: ");
        fgets(p.categoria, 50, stdin);
        p.categoria[strcspn(p.categoria, "\n")] = '\0';

        if (!validarCategoria(p.categoria)) {
            printf("\nErro: Categoria invalida! As categorias aceitas sao:\n");
            for (int i = 0; i < MAX_CATEGORIAS; i++) {
                printf(" - %s\n", CATEGORIAS_VALIDAS[i]);
            }
            printf("\n");
        }
    } while (!validarCategoria(p.categoria));

// Quantidade inicial nao pode ser negativa (Item 5 PDF)  / utilizando do while pra repetir ate a pessoa digitar o certo
    do {
        printf("Digite a quantidade inicial: ");
        scanf("%d", &p.qtd_disponivel);  // da pasta produtos, adiciona a qntd disponivel

        if (p.qtd_disponivel < 0) {              // se a qntd disponivel do produto for negativa da erro
            printf("Erro: A quantidade nao pode ser negativa!\n");
        }
    } while (p.qtd_disponivel < 0);

    // Quantidade minima nao pode ser negativa (Item 5 PDF)
    do {
        printf("Digite a quantidade minima recomendada: ");
        scanf("%d", &p.qtd_minima);

        if (p.qtd_minima < 0) {
            printf("Erro: A quantidade minima nao pode ser negativa!\n");
        }
    } while (p.qtd_minima < 0);

    // Valor unitario deve ser maior que zero (Item 5 PDF)
    do {
        printf("Digite o valor unitario (R$): ");
        scanf("%f", &p.valor_unitario);

        if (p.valor_unitario <= 0) {
            printf("Erro: O valor deve ser maior que zero!\n");
        }
    } while (p.valor_unitario <= 0);

    // Situacao inicial padrao: 1 (Ativo)
    p.situacao = 1;

    // Guarda o produto no vetor na posicao 'total_produtos'
    estoque[total_produtos] = p;
    total_produtos++; // Incrementa o contador de produtos cadastrados

    printf("\n>>> SUCESSO: Produto cadastrado com exito! <<<\n");
}


// Função auxiliar sua para não repetir printf grande em várias funções
void exibirLinhaProduto(Produto p){
    char sitStr[25];
    if (p.situacao == 1)strcpy(sitStr, "Ativo");
    else if (p.situacao == 2) strcpy(sitStr, "Indisponivel");
    else strcpy(sitStr, "Descontinuado");

    printf("Cod: %d | Nome: %s | Cat: %s | Qtd: %d | Val Unit: R$ %.2f | Sit: %s\n", 
           p.codigo, p.nome, p.categoria, p.qtd_disponivel, p.valor_unitario, sitStr);
}
void exibirValorIndividualEstoque(){
    if (total_produtos == 0){ // Verifica se tem produtos cadastrados
        printf("\nNenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- VALOR INDIVIDUAL DE CADA PRODUTO EM ESTOQUE ---\n");
    for (int i = 0; i < total_produtos; i++){ // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        float valor_total = estoque[i].qtd_disponivel * estoque[i].valor_unitario; // Cria uma variável local e calcula o patrimônio daquele item multiplicando a quantidade em estoque pelo preço de custo unitário.
        exibirLinhaProduto(estoque[i]);
    }
}
void calcularValorTotalEstoque(){
    float soma_total = 0.0;
    for (int i = 0; i < total_produtos; i++){ // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        soma_total += estoque[i].qtd_disponivel * estoque[i].valor_unitario; // Multiplica a quantidade pelo preço do produto atual e soma ao valor total acumulado
    }
    printf("\nVALOR TOTAL DE TODOS OS PRODUTOS EM ESTOQUE: R$ %.2f\n", soma_total);
}
void consultarProdutosSemEstoque(){
    int encontrados = 0;
    printf("\n--- PRODUTOS SEM ESTOQUE ---\n");
    for (int i = 0; i < total_produtos; i++){ // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        if (estoque[i].qtd_disponivel == 0){ // Verifica se a quantidade em estoque é igual a zero
            exibirLinhaProduto(estoque[i]);
            encontrados++; // Soma 1 ao contador de produtos encontrados sem estoque
        }
    }
    if (encontrados == 0){ // Verifica se o contador de produtos encontrados sem estoque é igual a zero, ou seja, não encontrou nenhum produto sem estoque
        printf("\nNenhum produto encontrado sem estoque.\n");
    }
}
void consultarProdutosAbaixoDoMinimo(){
    int encontrados = 0;
    printf("\n--- PRODUTOS ABAIXO DA QUANTIDADE MÍNIMA ---\n");
    for (int i = 0; i < total_produtos; i++){ // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        if (estoque[i].qtd_disponivel < estoque[i].qtd_minima){ // Varre o estoque e compara se a quantidade atual está menor do que a quantidade mínima configurada no cadastro
            exibirLinhaProduto(estoque[i]);
            printf("Quantidade mínima recomendada: %d\n", estoque[i].qtd_minima); // Se o produto estiver em nível crítico, informa qual era o limite mínimo aceitável
            encontrados++; // Soma 1 ao contador de produtos encontrados abaixo da quantidade mínima
        }
    }
    if (encontrados == 0){ // Verifica se o contador de produtos encontrados abaixo da quantidade mínima é igual a zero, ou seja, não encontrou nenhum produto abaixo do limite mínimo
        printf("\nNenhum produto encontrado abaixo da quantidade mínima.\n");
    }
}