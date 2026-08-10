#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limites do sistema exigidos (PDF)
#define MAX_PRODUTOS 200
#define MAX_CATEGORIAS 12

// Lista fixa de categorias permitidas no sistema (PDF Item 4)
const char CATEGORIAS_VALIDAS[MAX_CATEGORIAS][50] = {
    "Maquiagem",
    "Cabelo",
    "Skincare",
    "Perfumaria",
    "Corpo e Banho",
    "Unhas",
    "Bijuterias",
    "Bolsas",
    "Necessaires",
    "Óculos",
    "Roupas",
    "Calçados",
};

// ESTRUTURA DO PRODUTO (PDF Item 3)

typedef struct {
    int codigo;             // Código de identificação único de 1 a 200 (0 indica posição vazia/disponível)
    char nome[100];         // Nome do produto
    char categoria[50];     // Categoria do produto
    int qtd_disponivel;     // Quantidade disponível em estoque
    int qtd_minima;         // Quantidade mínima recomendada
    float valor_unitario;   // Valor unitário do produto
    int situacao;           // Situação: 1 = Ativo, 2 = Indisponível, 3 = Descontinuado
} Produto;

//Produto estoque[MAX_PRODUTOS]; // Vetor com capacidade para até 200 produtos
//int total_produtos = 0;        // Contador de produtos atualmente cadastrados

FILE* inicializarArquivo(const char *cherieBelle);
// PROTÓTIPOS DAS FUNÇÕES
int buscarIndicePorCodigo(int codigo);
int validarCategoria(const char *cat);
int produtoEstaAtivo(FILE *fPtr, int codigo);
void exibirMenuPrincipal();

//  Funções (protótipos): Vívian 
void cadastrarProduto(FILE *fPtr);
void consultarProdutoPorCodigo(FILE *fPtr);
void consultarProdutoPorNome(FILE *fPtr);
void consultarProdutosPorSituacao(FILE *fPtr);
void listarTodosProdutos(FILE *fPtr);
void alterarProduto(FILE *fPtr);
void excluirOuDescontinuarProduto(FILE *fPtr);
void ordenarProdutosPorNome(FILE *fPtr);
void ordenarProdutosPorQuantidade(FILE *fPtr);
void salvarDados(FILE *fPtr);
void carregarDados(FILE *fPtr);
void encerrarSistema(FILE *fPtr);
//  Funções (protótipos): Rebeca 
void registrarEntrada(FILE *fPtr);
void registrarSaida(FILE *fPtr);
void consultarProdutosPorCategoria(FILE *fPtr);
void consultarProdutosAbaixoDoMinimo(FILE *fPtr);
void consultarProdutosSemEstoque(FILE *fPtr);
void relatorioPorCategoria(FILE *fPtr);
void ordenarProdutosPorValorUnitario(FILE *fPtr);
void exibirValorIndividualEstoque(FILE *fPtr);
void calcularValorTotalEstoque(FILE *fPtr);
void buscarProdutoMaiorValorUnitario(FILE *fPtr);
void buscarProdutoMaiorValorArmazenado(FILE *fPtr);

// FUNÇÃO MAIN
int main(void) {
    FILE *cfPtr = inicializarArquivo("produtos.dat");
    int opcao;

    do {
        printf("\n====================================\n");
        printf("   SISTEMA DE CONTROLE DE ESTOQUE   \n");
        printf("====================================\n");
        printf(" 1. Cadastrar Produto\n");
        printf(" 2. Listar Todos os Produtos\n");
        printf(" 3. Alterar Dados de um Produto\n");
        printf(" 4. Excluir ou Descontinuar Produto\n");
        printf(" 5. Consultar Produto por Codigo\n");
        printf(" 6. Consultar Produto por Nome\n");
        printf(" 7. Consultar Produtos por Situacao\n");
        printf(" 8. Consultar Produtos por Categoria\n");
        printf(" 9. Consultar Produtos Abaixo do Minimo\n");
        printf("10. Consultar Produtos Sem Estoque\n");
        printf("11. Buscar Produto com Maior Valor Unitario\n");
        printf("12. Buscar Produto com Maior Valor Total Armazenado\n");
        printf("13. Exibir Valor Individual Armazenado por Produto\n");
        printf("14. Ordenar Produtos por Nome\n");
        printf("15. Ordenar Produtos por Quantidade\n");
        printf("16. Relatorio de Totais por Categoria\n");
        printf("17. Ordenar Produtos por Valor Unitario\n");
        printf("18. Calcular Valor Total do Estoque Geral\n");
        printf("\n 19. Sair do Sistema\n");
        printf("====================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(cfPtr); 
                break;
            case 2:
                listarTodosProdutos(cfPtr);
                break;
            case 3:
                alterarProduto(cfPtr);
                break;
            case 4:
                excluirOuDescontinuarProduto(cfPtr);
                break;
            case 5:
                consultarProdutoPorCodigo(cfPtr);
                break;
            case 6:
                consultarProdutoPorNome(cfPtr);
                break;
            case 7:
                consultarProdutosPorSituacao(cfPtr);
                break;
            case 8:
                consultarProdutosPorCategoria(cfPtr);
                break;
            case 9:
                consultarProdutosAbaixoDoMinimo(cfPtr);
                break;
            case 10:
                consultarProdutosSemEstoque(cfPtr);
                break;
            case 11:
                buscarProdutoMaiorValorUnitario(cfPtr);
                break;
            case 12:
                buscarProdutoMaiorValorArmazenado(cfPtr);
                break;
            case 13:
                exibirValorIndividualEstoque(cfPtr);
                break;
            case 14:
                ordenarProdutosPorNome(cfPtr);
                break;
            case 15:
                ordenarProdutosPorQuantidade(cfPtr);
                break;
            case 16:
                relatorioPorCategoria(cfPtr);
                break;
            case 17:
                ordenarProdutosPorValorUnitario(cfPtr);
                break;
            case 18:
                calcularValorTotalEstoque(cfPtr);
                break;
            case 19:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 18);

    fclose(cfPtr);
    return 0;
}
// Inicializa o arquivo de acesso aleatorio 
FILE* inicializarArquivo(const char *cherieBelle) {
    // Tenta abrir para leitura e escrita binaria
    FILE *fPtr = fopen(cherieBelle, "rb+");

    // Se o arquivo nao existe, cria e inicializa 200 posicoes em branco
    if (fPtr == NULL) {
        fPtr = fopen(cherieBelle, "wb+");
        if (fPtr == NULL) {
            puts("Erro critico: Nao foi possivel criar o arquivo de dados!");
            exit(1);
        }

        // Registro em branco padrao
        Produto produtoVazio = {0, "", "", 0, 0, 0.0f, 0};
        
        // Grava 200 registros vazios no arquivo (Fig. 11.10)
        for (int i = 1; i <= MAX_PRODUTOS; i++) {
            fwrite(&produtoVazio, sizeof(Produto), 1, fPtr);
        }

        //inicializado cm 200 posicoes em branco
        printf(">>> Arquivo '%s' criado e inicializado com sucesso! <<<\n", cherieBelle);
    } else {
        printf(">>> Arquivo '%s' carregado com sucesso! <<<\n", cherieBelle);
    }

    return fPtr;
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Retorna 1 se a categoria for valida e 0 se for invalida
int validarCategoria(const char *cat) {
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        // strcmp retorna 0 se as duas palavras forem EXATAMENTE iguais
        if (strcmp(cat, CATEGORIAS_VALIDAS[i]) == 0) {
            return 1; 
        }
    }
    return 0; // Nao encontrou na lista de validas
}

void exibirLinhaProduto(Produto p){
    char sitStr[25];
    if (p.situacao == 1)strcpy(sitStr, "Ativo");
    else if (p.situacao == 2) strcpy(sitStr, "Indisponivel");
    else strcpy(sitStr, "Descontinuado");

    printf("Cod: %d | Nome: %s | Cat: %s | Qtd: %d | Val Unit: R$ %.2f | Sit: %s\n", 
           p.codigo, p.nome, p.categoria, p.qtd_disponivel, p.valor_unitario, sitStr);
}

// Verifica se existe um produto cadastrado naquele código
// Retorna 1 se o produto existe, ou 0 se a posição estiver vazia/inválida
int produtoExisteNoArquivo(FILE *fPtr, int codigo) {
    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        return 0; // Código fora do limite (1 a 200)
    }

    // Posiciona e lê o registro diretamente no disco
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
    Produto p;
    fread(&p, sizeof(Produto), 1, fPtr);

    // Se o código for diferente de 0, a posição está ocupada
    return (p.codigo != 0);
}

// Verifica se o produto correspondente ao código está com situacao == 1 (Ativo)
// Retorna 1 se estiver Ativo, ou 0 caso contrário
int produtoEstaAtivo(FILE *fPtr, int codigo) {
    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        return 0;
    }

    // Posiciona e lê o registro no arquivo
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
    Produto p;
    fread(&p, sizeof(Produto), 1, fPtr);

    // Retorna verdadeiro somente se o slot estiver ocupado e a situação for 1 (Ativo)
    return (p.codigo != 0 && p.situacao == 1);
}

void cadastrarProduto(FILE *fPtr){

    printf("\n--- CADASTRO DE PRODUTO ---\n");
    int codigo;
    printf("\nDigite o codigo do produto (1 a %d): ", MAX_PRODUTOS);
    scanf("%d", &codigo);
    limparBuffer();

    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        printf("Erro: O codigo fora do limite permitido (1 a %d)!", MAX_PRODUTOS);
        return;
    //if (total_produtos >= MAX_PRODUTOS) {
        //printf("Erro: Limite maximo de 200 produtos atingido!\n");
        //return;

}

// Posiciona o ponteiro do arquivo na posicao exata do codigo
fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
// variavel temp pra ler dados do novo produto
Produto p; 
fread(&p, sizeof(Produto), 1, fPtr);

// Se a posicao ja possui um codigo registrado, aborta (Verificacao de Duplicidade)
if (p.codigo != 0) {
    printf("\nErro: O codigo %d ja esta cadastrado pra outro produto!\n", codigo);
    return;
    }
 
p.codigo = codigo;
// validação código único, não pode ter repetido
if (buscarIndicePorCodigo(p.codigo) != -1) {
        printf("\nErro: O codigo %d ja esta cadastrado!\n", p.codigo);
        return;
}

do {
        printf("\nNome do produto: ");
        fgets(p.nome, 100, stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';

        if (strlen(p.nome) == 0) {
            printf("Erro: O nome do produto e obrigatorio!\n");
        }
    } while (strlen(p.nome) == 0);

do {
        printf("Categoria do produto: ");
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
        printf("Quantidade disponivel em estoque: ");
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

    limparBuffer(); // Limpa o buffer residual para as proximas operacoes

    // Situacao inicial padrao: 1 (Ativo)
    p.situacao = 1;

    fseek(fPtr, (p.codigo - 1) * sizeof(Produto), SEEK_SET);
    fwrite(&p, sizeof(Produto), 1, fPtr);
    fflush(fPtr);

    printf("\n>>> SUCESSO: Produto cadastrado com exito! <<<\n");
}

void listarTodosProdutos(FILE *fPtr) {
    printf("\n--- LISTA GERAL DE PRODUTOS ---\n");
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        if (p.codigo != 0) {
            exibirLinhaProduto(p);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto cadastrado no arquivo.\n");
    }
}

// Função auxiliar sua para não repetir printf grande em várias funções

void exibirValorIndividualEstoque(FILE *fPtr){
    printf("\n--- VALOR INDIVIDUAL DE CADA PRODUTO EM ESTOQUE ---\n");
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        if (p.codigo != 0) {
            float total = p.qtd_disponivel * p.valor_unitario;
            exibirLinhaProduto(p);
            printf("   -> Valor Total em Estoque: R$ %.2f\n", total);
            encontrados++;
    }
}
}
void calcularValorTotalEstoque(FILE *fPtr){
    rewind(fPtr);
    Produto p;
    float soma_total = 0.0f;
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        if (p.codigo != 0) {
        soma_total += (p.qtd_disponivel * p.valor_unitario); // Multiplica a quantidade pelo preço do produto atual e soma ao valor total acumulado
    }
    printf("\n=======================================================\n");
    printf("\nVALOR TOTAL DE TODOS OS PRODUTOS EM ESTOQUE: R$ %.2f\n", soma_total);
}   printf("\n=======================================================\n");
}
void consultarProdutosSemEstoque(FILE *fPtr){
    printf("\n--- PRODUTOS SEM ESTOQUE ---\n");
    rewind(fPtr);
    Produto p;
    int encontrados = 0;
    
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) { // Percorre o vetor de produtos, ou seja, todos os produtos cadastrados
        if (p.codigo != 0 && p.qtd_disponivel == 0){ // Verifica se a quantidade em estoque é igual a zero
            exibirLinhaProduto(p);
            encontrados++; // Soma 1 ao contador de produtos encontrados sem estoque
        }
    }
    if (encontrados == 0){ // Verifica se o contador de produtos encontrados sem estoque é igual a zero, ou seja, não encontrou nenhum produto sem estoque
        printf("\nNenhum produto encontrado sem estoque.\n");
    }

}
void consultarProdutosAbaixoDoMinimo(FILE *fPtr){
    printf("\n--- PRODUTOS ABAIXO DA QUANTIDADE MÍNIMA ---\n");
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        if (p.codigo != 0 && p.qtd_disponivel < p.qtd_minima){ // Varre o estoque e compara se a quantidade atual está menor do que a quantidade mínima configurada no cadastro
            exibirLinhaProduto(p);
            printf("Quantidade mínima recomendada: %d\n", p.qtd_minima); // Se o produto estiver em nível crítico, informa qual era o limite mínimo aceitável
            encontrados++; // Soma 1 ao contador de produtos encontrados abaixo da quantidade mínima
        }
    }
    if (encontrados == 0){ // Verifica se o contador de produtos encontrados abaixo da quantidade mínima é igual a zero, ou seja, não encontrou nenhum produto abaixo do limite mínimo
        printf("\nNenhum produto encontrado abaixo da quantidade mínima.\n");
    }
}