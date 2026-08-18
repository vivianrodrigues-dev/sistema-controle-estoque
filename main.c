#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necessário para a função tolower()

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
    "Oculos",
    "Roupas",
    "Calcados",
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
int validarCategoria(const char *cat);
int stringEstaEmBranco(const char *str); // PROFESSOR FALOU NO MEET
void selecionarCategoria(char *destino);
int produtoEstaAtivo(FILE *fPtr, int codigo);
void limparBuffer(void);
void paraMinusculo(char *str); // dxar padrão desde o cadastro
int contemSubpalavra(const char *texto, const char *busca); 
void exibirLinhaProduto(Produto p);
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
void relatorioGeralEstoque(FILE *fPtr);
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
        printf("16. Ordenar Produtos por Valor Unitario\n");
        printf("17. Relatorio de Totais por Categoria\n");
        printf("18. Relatorio Geral\n");
        printf("19. Registrar Entrada de Produtos no Estoque\n");
        printf("20. Registrar Saida de Produtos do Estoque\n");
        printf("21. Calcular Valor Total do Estoque Geral\n");
        printf("\n22. Sair do Sistema\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = 0; // Força cair no 'default' (Opção inválida)
        } else {
            limparBuffer(); // Consome o '\n' deixado pelo scanf
}

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
                ordenarProdutosPorValorUnitario(cfPtr);
                break;
            case 17:
                relatorioPorCategoria(cfPtr);
                break;
            case 18:
                relatorioGeralEstoque(cfPtr);
                break;
            case 19:
                registrarEntrada(cfPtr);
                break;
            case 20:
                registrarSaida(cfPtr);
                break;
            case 21:
                calcularValorTotalEstoque(cfPtr);
                break;
            case 22:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 22);

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

// Converte uma string inteira para minusculas
void paraMinusculo(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}
// Retorna 1 se a string for vazia ou contiver apenas espaços em branco
int stringEstaEmBranco(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

// Exibe o menu de categorias e atribui a escolha por código 
// Exibe o menu de categorias e atribui a escolha por código 
void selecionarCategoria(char *destino) {
    int catOpcao = 0;

    // 1. Imprime a lista de categorias apenas UMA VEZ no início
    printf("\n--- SELEÇAO DE CATEGORIA ---\n");
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        printf(" %2d. %s\n", i + 1, CATEGORIAS_VALIDAS[i]);
    }
    printf("----------------------------\n");

    do {
        printf("Escolha o codigo da categoria (1 a %d): ", MAX_CATEGORIAS);
        fflush(stdout);
        
        // Validação se a pessoa digitou letras/símbolos
        if (scanf("%d", &catOpcao) != 1) {
            limparBuffer();
            printf("\n>>> Erro: Digite apenas numeros inteiros! <<<\n\n");
            fflush(stdout);
            catOpcao = 0; // Força continuar no laço
            continue;
        }
        limparBuffer();

        // Validação se o número está fora do intervalo (1 a 12)
        if (catOpcao < 1 || catOpcao > MAX_CATEGORIAS) {
            printf("\n>>> Erro: Opcao invalida! Escolha um codigo entre 1 e %d. <<<\n\n", MAX_CATEGORIAS);
            fflush(stdout);
        }

    } while (catOpcao < 1 || catOpcao > MAX_CATEGORIAS);

    // Copia o nome da categoria para o produto
    strcpy(destino, CATEGORIAS_VALIDAS[catOpcao - 1]);
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

// Função auxiliar: converte textos para minúsculo para busca parcial e case-insensitive
int contemSubpalavra(const char *texto, const char *busca) {
    char tempTexto[100]; // Vetor local temporário para armazenar a cópia do texto em minúsculas
    char tempBusca[100]; // Vetor local temporário para armazenar a cópia do termo buscado em minúsculas
    int i = 0;

    // onverte caractere por caractere de 'texto' para minúsculo até encontrar o fim da string ('\0')
    while (texto[i] != '\0' && i < 99) {
        tempTexto[i] = (char)tolower((unsigned char)texto[i]);
        i++;
        // (unsigned char): Garante a conversão correta de caracteres acentuados/especiais sem dar erro de sinal
        // tolower(): Função que recebe um caractere maiúsculo e o transforma em minúsculo 
        // (char): Converte o retorno numérico do tolower de volta para o tipo caractere
    }
    tempTexto[i] = '\0'; // Adiciona o caractere nulo terminador no final para fechar a string em C

    // Converte o termo buscado para minúsculas
    i = 0;
    while (busca[i] != '\0' && i < 99) {
        tempBusca[i] = (char)tolower((unsigned char)busca[i]);
        i++;
    }
    tempBusca[i] = '\0';
    // strstr(tempTexto, tempBusca): Função da biblioteca <string.h> que procura a subpalavra 'tempBusca' dentro de 'tempTexto'.
    // - Se encontrar: Retorna o ponteiro com a posição da memória onde a subpalavra começa.
    // - Se NÃO encontrar: Retorna NULL (ponteiro nulo).
    // (strstr(...) != NULL): resulta em 1 se encontrou, ou 0 se não encontrou.
    // Retorna 1 se encontrar a subpalavra no texto (strstr) ou 0 se não encontrar
    return (strstr(tempTexto, tempBusca) != NULL);
}

void cadastrarProduto(FILE *fPtr){

    printf("\n--- CADASTRO DE PRODUTO ---\n");
    int codigo;
    Produto p;
    int codigoValido = 0;
    
do{
    printf("\nDigite o codigo do produto (1 a %d): ", MAX_PRODUTOS);
    scanf("%d", &codigo);
    limparBuffer();
    
    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        printf("Erro: O codigo fora do limite permitido (1 a %d)!", MAX_PRODUTOS);
    }else {

    // Posiciona o ponteiro do arquivo na posicao exata do codigo
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET); //o próprio número do código do produto é a posição dele no arquivo
    // variavel temp pra ler dados do novo produto
    fread(&p, sizeof(Produto), 1, fPtr);

    // Se a posicao ja possui um codigo registrado, aborta (Verificacao de Duplicidade)
    if (p.codigo != 0) {
    printf("\nErro: O codigo %d ja esta cadastrado pra outro produto!\n", codigo);
} else {
    // Se passou nos dois testes, o código é válido e a posição está livre!
    codigoValido = 1;
        }
    }
} while (!codigoValido);

p.codigo = codigo;

do {
        printf("\nNome do produto: ");
        fgets(p.nome, 100, stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';

        if (stringEstaEmBranco(p.nome)) {
            printf("Erro: O nome do produto e obrigatorio!\n");
        }
    } while (stringEstaEmBranco(p.nome));

// Converte o nome do produto para minúsculo como padrão
    paraMinusculo(p.nome);
// Seleção da Categoria por Código
    selecionarCategoria(p.categoria);


// Quantidade inicial nao pode ser negativa (Item 5 PDF)  / utilizando do while pra repetir ate a pessoa digitar o certo
    do {
        printf("Quantidade disponivel em estoque: ");
        if (scanf("%d", &p.qtd_disponivel) != 1) {  // da pasta produtos, adiciona a qntd disponivel
            limparBuffer();
            printf("Erro: Digite um numero inteiro valido!\n");
            p.qtd_disponivel = -1;
            continue;
        }
        limparBuffer(); 

        if (p.qtd_disponivel < 0) {              // se a qntd disponivel do produto for negativa da erro
            printf("Erro: A quantidade nao pode ser negativa!\n");
        }
    } while (p.qtd_disponivel < 0);

    if (p.qtd_disponivel == 0) {
        p.situacao = 2; // Temporariamente Indisponível
        printf("-> Nota: Produto cadastrado com quantidade 0. Situacao definida automaticamente como 'Temporariamente Indisponivel'.\n");
    } else {
        p.situacao = 1; // Ativo
    }
    // Quantidade minima nao pode ser negativa (Item 5 PDF)
    do {
        printf("Digite a quantidade minima recomendada: ");
        if (scanf("%d", &p.qtd_minima) != 1) {
            limparBuffer();
            printf("Erro: Digite um numero inteiro valido!\n");
            p.qtd_minima = -1;
            continue;
        }
        limparBuffer();

        if (p.qtd_minima < 0) {
            printf("Erro: A quantidade minima nao pode ser negativa!\n");
        }
    } while (p.qtd_minima < 0);

    // Valor unitario deve ser maior que zero (Item 5 PDF)
    do {
        printf("Digite o valor unitario (R$): ");
        if (scanf("%f", &p.valor_unitario) != 1) {
            limparBuffer();
            printf("Erro: Digite um valor numerico valido!\n");
            p.valor_unitario = 0.0f;
            continue;
        }
        limparBuffer();

        if (p.valor_unitario <= 0) {
            printf("Erro: O valor deve ser maior que zero!\n");
        }
    } while (p.valor_unitario <= 0);

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
    printf("\n================================================================================================================\n");
    printf("                              VALOR INDIVIDUAL DOS PRODUTOS EM ESTOQUE\n");
    printf("================================================================================================================\n");

    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){
        if (p.codigo != 0){
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
    }
    printf("\n=======================================================\n");
    printf("\nVALOR TOTAL DE TODOS OS PRODUTOS EM ESTOQUE: R$ %.2f\n", soma_total);
    printf("\n=======================================================\n");
}
void consultarProdutosSemEstoque(FILE *fPtr){
    printf("\n================================================================================================================\n");
    printf("                                              PRODUTOS SEM ESTOQUE\n");
    printf("================================================================================================================\n");
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
    printf("\n====================================================================================================\n");
    printf("                              PRODUTOS ABAIXO DA QUANTIDADE MINIMA\n");
    printf("====================================================================================================\n");
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        if (p.codigo != 0 && p.qtd_disponivel < p.qtd_minima){ // Varre o estoque e compara se a quantidade atual está menor do que a quantidade mínima configurada no cadastro
            exibirLinhaProduto(p);
            printf("Quantidade minima recomendada: %d\n", p.qtd_minima); // Se o produto estiver em nível crítico, informa qual era o limite mínimo aceitável
            encontrados++; // Soma 1 ao contador de produtos encontrados abaixo da quantidade mínima
        }
    }
    if (encontrados == 0){ // Verifica se o contador de produtos encontrados abaixo da quantidade mínima é igual a zero, ou seja, não encontrou nenhum produto abaixo do limite mínimo
        printf("\nNenhum produto encontrado abaixo da quantidade minima.\n");
    }
    
}

 // Utiliza a chave primária (código) para calcular a posição exata
 // no arquivo binário usando fseek(), permitindo busca em tempo O(1).

void consultarProdutoPorCodigo(FILE *fPtr) {
    printf("\n--- CONSULTA DE PRODUTO POR CODIGO ---\n");
    int codigo;

    printf("Digite o codigo do produto (1 a %d): ", MAX_PRODUTOS);
    if (scanf("%d", &codigo) != 1) {
        limparBuffer(); // Chama a função de limpar o buffer do teclado para remover caracteres inválidos
        printf("\nErro: Entrada invalida!\n");
        return;
    }
    limparBuffer(); // Limpa o caractere '\n' 

    // Validação dos limites do arquivo (exigido no PDF Item 3 e 13)
    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        printf("\nErro: Codigo fora do limite permitido (1 a %d)!\n", MAX_PRODUTOS);
        return;
    }

    // fseek(fPtr, offset, origem): Movimenta o ponteiro de leitura/escrita do arquivo para uma posição específica.
    // - fPtr: ponteiro do arquivo aberto "produtos.dat".
    // - (long)(codigo - 1) * sizeof(Produto): O deslocamento em bytes. Como o código 1 fica no byte 0 (primeira posição),
    //   subtraímos 1 do código e multiplicamos pelo tamanho da struct Produto em bytes.
    // - SEEK_SET: Constante que indica que a contagem dos bytes deve começar do INÍCIO do arquivo.
    
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
    Produto p; // Declara variável do tipo 'Produto' na RAM para armazenar temporariamente o registro lido do disco

    // fread(destino, tamanho, quantidade, ponteiro_arquivo): Lê dados binários do arquivo.
    // - &p: Endereço de memória da variável 'p' onde os dados lidos do disco serão gravados.
    // - sizeof(Produto): O tamanho em bytes da estrutura de dados Produto.
    // - 1: Especifica que queremos ler exatamente 1 bloco/registro por vez.
    // - fPtr: O arquivo de onde os bytes serão lidos.

    fread(&p, sizeof(Produto), 1, fPtr);

    // Se codigo == 0, a posição está vazia no arquivo
    if (p.codigo == 0) {
        printf("\nNenhum produto cadastrado com o codigo %d.\n", codigo);
    } else {
        printf("\n================ PRODUTO ENCONTRADO ================\n");
        exibirLinhaProduto(p);
        printf(" -> Qtd Minima Recomendada: %d unidades\n", p.qtd_minima);
        printf(" -> Valor Total Armazenado: R$ %.2f\n", p.qtd_disponivel * p.valor_unitario);
        printf("===================================================\n");
    }
}

// Varre todo o arquivo sequencialmente (fread) buscando produtos cujos
//nomes contenham o termo digitado pelo usuário (total ou parcialmente).

void consultarProdutoPorNome(FILE *fPtr) {
    printf("\n--- CONSULTA DE PRODUTO POR NOME ---\n");
    char termoBusca[100];

    // fgets(destino, tamanho_maximo, fluxo_entrada): Lê uma linha inteira de texto com segurança.
    // - termoBusca: Onde a string digitada será gravada.
    // - sizeof(termoBusca): Limite de leitura (100 bytes) para evitar o estouro de memória (buffer overflow).
    // - stdin: Abreviação de "Standard Input", representa a entrada padrão do teclado.

    printf("Digite o nome ou parte do nome do produto: ");
    fgets(termoBusca, sizeof(termoBusca), stdin);

    // strcspn(termoBusca, "\n"): Procura o índice do caractere de quebra de linha '\n' deixado pelo Enter ao usar fgets.
    // termoBusca[...] = '\0': Substitui a quebra de linha pelo caractere nulo '\0', que finaliza a string corretamente.
    termoBusca[strcspn(termoBusca, "\n")] = '\0'; // Remove o \n capturado pelo fgets

    // Validação do campo de busca (Item 13)
    // strlen(termoBusca): Retorna a quantidade de caracteres da string.
    // Se for igual a 0, significa que o usuário apenas apertou Enter sem digitar nenhuma letra.
    if (stringEstaEmBranco(termoBusca)) {
        printf("\nErro: O termo de busca nao pode ser vazio!\n");
        return;
    }

    // Reposiciona o ponteiro para o início do arquivo antes de iniciar a varredura
    // rewind(fPtr): Reposiciona o ponteiro de leitura do arquivo no início do arquivo (byte 0).
    // É o equivalente a chamar fseek(fPtr, 0, SEEK_SET).
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    printf("\n--- RESULTADOS PARA \"%s\" ---\n", termoBusca);

    // Varre todos os registros do arquivo sequencialmente
    // fread(...) == 1: O laço while continua executando enquanto a função fread conseguir ler com sucesso
    // exatamente 1 registro do tipo Produto do arquivo binário. Quando chegar ao fim do arquivo (EOF), fread retorna 0 e o laço para
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        // Ignora posições vazias (p.codigo == 0) e verifica se bate com a busca
        // 1ª Validação (p.codigo != 0): Garante que a posição não seja um registro em branco/vazio do arquivo.
        // 2ª Validação (contemSubpalavra(p.nome, termoBusca)): Chama a função auxiliar para testar se o termo digitado está no nome
        if (p.codigo != 0 && contemSubpalavra(p.nome, termoBusca)) {
            exibirLinhaProduto(p);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto encontrado contendo \"%s\" no nome.\n", termoBusca);
    } else {
        printf("Total de registros encontrados: %d\n", encontrados);
    }
}


// Solicita ao usuário qual situação filtrar (1 = Ativo, 2 = Indisponível,
// 3 = Descontinuado) e percorre o arquivo listando apenas os correspondentes.
 
void consultarProdutosPorSituacao(FILE *fPtr) {
    printf("\n--- CONSULTA DE PRODUTOS POR SITUACAO ---\n");
    printf(" Escolha a situacao desejada:\n");
    printf(" 1. Ativo\n");
    printf(" 2. Temporariamente Indisponivel\n");
    printf(" 3. Descontinuado\n");
    printf("Opcao: ");

    int situacaoDesejada;
    if (scanf("%d", &situacaoDesejada) != 1) {
        limparBuffer(); // Limpa entradas incorretas
        printf("\nErro: Opcao invalida!\n");
        return;
    }
    limparBuffer();

    // Validação da opção informada pelo usuário (Item 13)
    if (situacaoDesejada < 1 || situacaoDesejada > 3) {
        printf("\nErro: Situacao invalida! Escolha apenas entre 1, 2 ou 3.\n");
        return;
    }

    // Reposiciona o ponteiro para o início do arquivo (byte 0)
    rewind(fPtr);
    Produto p;
    int encontrados = 0;

    // Vetor de ponteiros para string que mapeia a posição numérica no texto do cabeçalho
    // Posição 1 = "ATIVO", Posição 2 = "INDISPONÍVEL", Posição 3 = "DESCONTINUADO"
    const char *rotulosSituacao[] = {"", "ATIVO", "TEMPORARIAMENTE INDISPONIVEL", "DESCONTINUADO"};
    printf("\n====================================================================================================\n");
    printf("                              PRODUTOS NA SITUACAO: %s\n", rotulosSituacao[situacaoDesejada]);
    printf("====================================================================================================\n");

    // Percorre todos os registros do arquivon do início ao fim lendo 1 bloco por vez
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        // Filtra posições ativas e que correspondam à situação escolhida
        // p.codigo != 0: Garante que é um registro ocupado no arquivo.
        // Compara a situação do produto atual com a solicitada pelo usuário.
        if (p.codigo != 0 && p.situacao == situacaoDesejada) {
            exibirLinhaProduto(p);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto encontrado com a situacao \"%s\".\n", rotulosSituacao[situacaoDesejada]);
    } else {
        printf("Total de produtos encontrados nesta situacao: %d\n", encontrados);
    }
}

void ordenarProdutosPorNome(FILE *fPtr) {
    printf("\n--- PRODUTOS ORDENADOS POR NOME (A - Z) ---\n");

    // Vetor temporário na memória RAM para armazenar apenas os produtos válidos
    Produto lista[MAX_PRODUTOS];
    int total = 0; 

    rewind(fPtr);
    Produto p;

    //Lê registro por registro (bloco por bloco) do arquivo binário
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        // Ignora posições vazias (p.codigo == 0 indica slot livre)
        if (p.codigo != 0) {
            lista[total] = p; // Copia a estrutura completa para a memória RAM
            total++;          // Incrementa a quantidade de itens na lista
        }
    }
    // Se o arquivo só tiver posições em branco, avisa o usuário e encerra a função
    if (total == 0) {
        printf("Nenhum produto cadastrado para ordenar.\n");
        return;
    }

    // 3. BUBBLE SORT (Ordenação por Nome)
    //laço externo: controla quantas passadas vão ser feitas no vetor
    for (int i = 0; i < total - 1; i++) {
        //laço interno: compara elementos vizinhos (j e j+1)
        for (int j = 0; j < total - i - 1; j++) {
            
            // strcmp(str1, str2) compara duas strings caractere por caractere (tabela ASCII).
            // Retorna um valor > 0 se a primeira string for "maior" (vier depois alfabeticamente).
            // Exemplo: strcmp("Maquiagem", "Bolsas") traz um valor maior que 0.
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                // TROCA (SWAP): Troca a estrutura inteira de posição na memória RAM
                Produto temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < total; i++) {
        exibirLinhaProduto(lista[i]);
    }
    printf("\nTotal de produtos exibidos: %d\n", total);
}

void ordenarProdutosPorQuantidade(FILE *fPtr) {
    printf("\n--- PRODUTOS ORDENADOS POR QUANTIDADE (CRESCENTE) ---\n");

    Produto lista[MAX_PRODUTOS];
    int total = 0;
    rewind(fPtr);
    Produto p;
    
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1) {
        if (p.codigo != 0) {
            lista[total] = p;
            total++;
        }
    }
    if (total == 0) {
        printf("Nenhum produto cadastrado para ordenar.\n");
        return;
    }
    // BUBBLE SORT (Ordenação por Quantidade)
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            
            // Comparação numérica simples: se a quantidade do elemento atual (j)
            // for MAIOR que a do próximo elemento (j+1), eles estão fora de ordem crescente.
            if (lista[j].qtd_disponivel > lista[j + 1].qtd_disponivel) {
                // TROCA COMPLETA: Movemos a struct inteira para que o código,
                // preço e nome continuem sincronizados com essa quantidade!
                Produto temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < total; i++) {
        exibirLinhaProduto(lista[i]);
    }
    printf("\nTotal de produtos exibidos: %d\n", total);
}


void registrarEntrada(FILE *fPtr){ // Função para registrar a entrada de produtos no estoque
    printf("\n====================================================================================================\n");
    printf("                                  REGISTRAR ENTRADA DE PRODUTOS\n");
    printf("====================================================================================================\n");
    int codigo, qtd_recebida;
    printf("Digite o codigo do produto (1 a %d): ", MAX_PRODUTOS);
    if (scanf("%d", &codigo) != 1){ // Lê o código digitado e verifica se o usuário digitou um número válido
        limparBuffer();
        printf("Erro: Entrada invalida!\n");
        return;
    }
    limparBuffer();
    if (codigo < 1 || codigo > MAX_PRODUTOS){ // Valida o limite do código
        printf("Erro: Codigo fora do limite permitido (1 a %d)!\n", MAX_PRODUTOS);
        return;
    }
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET); // Move o leitor do arquivo direto para onde o produto está salvo
    Produto p; // Cria uma variável para guardar temporariamente os dados do produto
    fread(&p, sizeof(Produto), 1, fPtr); // Lê as informações do produto diretamente do arquivo
    if (p.codigo == 0){ // Verifica se o produto existe
        printf("Erro: Produto inexistente!\n");
        return;
    }
    if (p.situacao != 1){ // Verifica se o produto está ativo
        printf("Erro: O produto '%s' nao esta ativo (Situação: %d). Movimentacao bloqueada!\n", p.nome, p.situacao);
        return;
    }
    printf("Digite a quantidade recebida: "); // Pede a quantidade recebida ao usuário
    if (scanf("%d", &qtd_recebida) != 1){ // Lê a quantidade digitada e confirma se é um número válido
        limparBuffer();
        printf("Erro: Quantidade invalida!\n");
        return;
    }
    limparBuffer();
    if (qtd_recebida <= 0){ // Garante que a quantidade informada seja maior que zero
        printf("Erro: A quantidade informada deve ser maior que zero!\n");
        return;
    }
    int qtd_anterior = p.qtd_disponivel; // Salva a quantidade atual para exibir no comprovante final
    p.qtd_disponivel += qtd_recebida; // Adiciona a nova quantidade ao estoque

    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET); // Volta o leitor do arquivo para a posição do produto
    fwrite(&p, sizeof(Produto), 1, fPtr); // Salva os dados atualizados do produto no arquivo
    fflush(fPtr); // Força a gravação imediata no disco para evitar perda de dados

    printf("\n>>> ENTRADA REGISTRADA COM SUCESSO! <<<\n"); // Exibe o resumo da operação
    printf("Produto: %s\n", p.nome);
    printf("Quantidade anterior: %d\n", qtd_anterior);
    printf("Quantidade recebida: %d\n", qtd_recebida);
    printf("Nova quantidade disponivel: %d\n", p.qtd_disponivel);
}


void registrarSaida(FILE *fPtr){// Função para registrar a saída de produtos do estoque
    printf("\n====================================================================================================\n");
    printf("                                  REGISTRAR SAIDA DE PRODUTOS\n");
    printf("====================================================================================================\n");
    int codigo, qtd_retirada;
    printf("Digite o codigo do produto (1 a %d): ", MAX_PRODUTOS);
    if (scanf("%d", &codigo) != 1){ // Lê o código digitado e verifica se o usuário digitou um número válido
        limparBuffer();
        printf("Erro: Entrada invalida!\n");
        return;
    }
    limparBuffer();
    if (codigo < 1 || codigo > MAX_PRODUTOS){ // Valida o limite do código
        printf("Erro: Codigo fora do limite permitido (1 a %d)!\n", MAX_PRODUTOS);
        return;
    }
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET); // Move o leitor do arquivo direto para onde o produto está salvo
    Produto p; // Cria uma variável para guardar temporariamente os dados do produto
    fread(&p, sizeof(Produto), 1, fPtr); // Lê as informações do produto diretamente do arquivo
    if (p.codigo == 0){ // Verifica se o produto existe
        printf("Erro: Produto inexistente!\n");
        return;
    }
    if (p.situacao != 1){ // Verifica se o produto está ativo
        printf("Erro: O produto '%s' nao esta ativo (Situação: %d). Movimentacao bloqueada!\n", p.nome, p.situacao);
        return;
    }
    printf("Digite a quantidade a ser retirada: "); // Pede a quantidade a ser retirada ao usuário
    if (scanf("%d", &qtd_retirada) != 1){ // Lê a quantidade digitada e confirma se é um número válido
        limparBuffer();
        printf("Erro: Quantidade invalida!\n");
        return;
    }
    limparBuffer();
    if (qtd_retirada <= 0){ // Garante que a quantidade informada seja maior que zero
        printf("Erro: A quantidade informada deve ser maior que zero!\n");
        return;
    }
    if (p.qtd_disponivel < qtd_retirada){ // Verifica se há quantidade suficiente em estoque para a retirada
        printf("Erro: Quantidade insuficiente! Estoque atual: %d unidades.\n", p.qtd_disponivel);
        return;
    }
    int qtd_anterior = p.qtd_disponivel; // Salva a quantidade atual para exibir no comprovante final
    p.qtd_disponivel -= qtd_retirada; // Subtrai a quantidade retirada do estoque
    if (p.qtd_disponivel == 0){ // Verifica se o estoque zerou
        p.situacao = 2; // Altera o status para "Temporariamente Indisponível"
        printf("-> Nota: O estoque zerou. Situação alterada para 'Temporariamente Indisponível'.\n");
    }

    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);  // Volta o leitor do arquivo para a posição do produto
    fwrite(&p, sizeof(Produto), 1, fPtr); // Salva os dados atualizados do produto no arquivo
    fflush(fPtr); // Força a gravação imediata no disco para evitar perda de dados

    printf("\n>>> SAIDA REGISTRADA COM SUCESSO! <<<\n");  // Exibe o resumo da operação
    printf("Produto: %s\n", p.nome);
    printf("Quantidade anterior: %d\n", qtd_anterior);
    printf("Quantidade retirada: %d\n", qtd_retirada);
    printf("Quantidade restante: %d\n", p.qtd_disponivel);
}


void ordenarProdutosPorValorUnitario(FILE *fPtr){ // Função para ordenar e listar produtos pelo preço unitário
    printf("\n====================================================================================================\n");
    printf("                              PRODUTOS ORDENADOS POR VALOR UNITARIO\n");
    printf("====================================================================================================\n");

    int ordem; // Variável para guardar a escolha do tipo de ordenação (crescente ou decrescente)
    printf("Escolha a ordem de exibicao:\n");
    printf("1. Crescente (Menor para o Maior)\n");
    printf("2. Decrescente (Maior para o Menor)\n");
    printf("Opcao: "); // Pede ao usuário para escolher a ordem de exibição
    
    if (scanf("%d", &ordem) != 1 || (ordem != 1 && ordem != 2)){ // Lê a opção e valida se é válida (1 ou 2)
        limparBuffer(); // Limpa o teclado caso a entrada seja inválida
        printf("Erro: Opcao invalida!\n");
        return; // Cancela a operação e sai da função
    }
    limparBuffer(); // Limpa a memória temporária do teclado após a digitação

    Produto lista[MAX_PRODUTOS]; // Cria uma lista temporária para guardar os produtos na memória
    int total = 0; // Contador para saber quantos produtos válidos foram carregados
    rewind(fPtr); // Volta o leitor do arquivo para o início para ler todos os produtos
    Produto p; // Cria uma variável temporária para guardar os dados do produto lido
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo produto por produto até o final
        if (p.codigo != 0){ // Ignora produtos excluídos ou posições vazias
            lista[total] = p; // Copia o produto encontrado para a lista na memória
            total++; // Incrementa o total de produtos carregados
        }
    }
    if (total == 0){ // Verifica se nenhum produto válido foi encontrado no arquivo
        printf("Nenhum produto cadastrado para ordenar.\n");
        return; // Cancela a exibição e sai da função
    }
    // BUBBLE SORT (Ordenação por Valor Unitário)
    for (int i = 0; i < total - 1; i++){ // Percorre a lista para realizar as rodadas de comparação
        for (int j = 0; j < total - i - 1; j++){ // Compara os produtos vizinhos par a par
            int precisaTrocar = 0; // Indicador de controle para saber se as posições devem ser trocadas
            if (ordem == 1 && lista[j].valor_unitario > lista[j + 1].valor_unitario){ // Caso crescente: se o anterior for mais caro
                precisaTrocar = 1; // Marca que os dois produtos devem trocar de lugar
            } 
            else if (ordem == 2 && lista[j].valor_unitario < lista[j + 1].valor_unitario){ // Caso decrescente: se o anterior for mais barato
                precisaTrocar = 1; // Marca que os dois produtos devem trocar de lugar
            }
            if (precisaTrocar){ // Executa a troca de posição se necessário
                Produto temp = lista[j]; // Guarda temporariamente o primeiro produto
                lista[j] = lista[j + 1]; // Move o segundo produto para a posição do primeiro
                lista[j + 1] = temp; // Coloca o primeiro produto na posição do segundo
            }
        }
    }
    printf("\n--- RESULTADO DA ORDENACAO ---\n");
    for (int i = 0; i < total; i++){ // Percorre a lista já organizada com todos os produtos
        exibirLinhaProduto(lista[i]); // Imprime as informações do produto na tela
    }
    printf("\nTotal de produtos exibidos: %d\n", total); // Exibe a quantidade total de produtos mostrados
}


void consultarProdutosPorCategoria(FILE *fPtr){ // Função para buscar e listar produtos de uma categoria específica
    char categoriaDesejada[50]; // Variável para armazenar o nome da categoria escolhida
    selecionarCategoria(categoriaDesejada); // Exibe as opções e guarda a categoria escolhida pelo usuário
    printf("\n====================================================================================================\n");
    printf("                              PRODUTOS DA CATEGORIA: %s\n", categoriaDesejada); // Imprime o título da consulta na tela
    printf("====================================================================================================\n");
    rewind(fPtr); // Volta o leitor do arquivo para o início para começar a busca do zero
    Produto p; // Cria uma variável temporária para guardar os dados de cada produto lido
    int encontrados = 0; // Contador para saber quantos produtos da categoria foram localizados
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo produto por produto até o final
        if (p.codigo != 0 && strcmp(p.categoria, categoriaDesejada) == 0){ // Verifica se o produto existe e pertence à categoria buscada
            exibirLinhaProduto(p); // Exibe os dados do produto na tela
            encontrados++; // Soma +1 no contador de produtos encontrados
        }
    }
    if (encontrados == 0){ // Verifica se nenhum produto foi encontrado após percorrer todo o arquivo
        printf("\nNenhum produto cadastrado na categoria '%s'.\n", categoriaDesejada);
    } 
    else{ // Caso tenha encontrado pelo menos um produto
        printf("\nTotal de produtos encontrados: %d\n", encontrados); // Exibe a quantidade total de produtos localizados
    }
}


void buscarProdutoMaiorValorUnitario(FILE *fPtr){ // Função para encontrar e exibir o produto mais caro do estoque
    printf("\n====================================================================================================\n");
    printf("                                  PRODUTO(S) COM MAIOR VALOR UNITARIO\n");
    printf("====================================================================================================\n");

    rewind(fPtr); // Volta o leitor do arquivo para o início para começar a busca
    Produto p; // Cria uma variável temporária para guardar os dados do produto lido
    float maiorValor = 0.0f; // Guarda o maior preço encontrado até o momento
    int encontrou = 0; // Indica se pelo menos um produto válido foi localizado
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo produto por produto até o final
        if (p.codigo != 0){ // Ignora produtos excluídos ou posições vazias
            if (!encontrou || p.valor_unitario > maiorValor){ // Se for o primeiro produto ou se for mais caro que o anterior
                maiorValor = p.valor_unitario; // Atualiza o maior preço registrado
                encontrou = 1; // Marca que encontrou ao menos um produto no arquivo
            }
        }
    }
    if (!encontrou){ // Verifica se não havia nenhum produto cadastrado
        printf("Nenhum produto cadastrado no arquivo.\n");
        return; // Cancela a exibição e sai da função (percebi agr que n precisava dessa explicação kkkkkk)
    }
    rewind(fPtr); // Rebobina o leitor para o início para reler os dados
    printf("Maior valor unitario registrado: R$ %.2f\n\n", maiorValor);
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Percorre o arquivo novamente para listar os produtos
        if (p.codigo != 0 && p.valor_unitario == maiorValor){ // Filtra apenas os produtos que possuem o maior valor
            exibirLinhaProduto(p); // Imprime as informações do produto na tela
        }
    }
    printf("======================================================\n");
}


void buscarProdutoMaiorValorArmazenado(FILE *fPtr){ // Função para encontrar o produto com maior valor total acumulado no estoque
    
    printf("\n====================================================================================================\n");
    printf("                              PRODUTO(S) COM MAIOR VALOR TOTAL ARMAZENADO\n");
    printf("====================================================================================================\n");
    rewind(fPtr); // Volta o leitor do arquivo para o início para começar a busca
    Produto p; // Cria uma variável temporária para guardar os dados do produto lido
    float maiorValorTotal = 0.0f; // Guarda o maior valor em dinheiro total acumulado
    int encontrou = 0; // Indica se pelo menos um produto válido foi localizado
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo produto por produto até o final
        if (p.codigo != 0){ // Ignora produtos excluídos ou posições vazias
            float valorTotalAtual = p.qtd_disponivel * p.valor_unitario; // Calcula o valor total do produto (quantidade x preço)
            if (!encontrou || valorTotalAtual > maiorValorTotal){ // Se for o primeiro ou se tiver valor acumulado maior que o anterior
                maiorValorTotal = valorTotalAtual; // Atualiza o maior valor total registrado
                encontrou = 1; // Marca que encontrou ao menos um produto no arquivo
            }
        }
    }
    if (!encontrou){ // Verifica se não havia nenhum produto cadastrado
        printf("Nenhum produto cadastrado no arquivo.\n");
        return;
    }
    rewind(fPtr); // Rebobina o leitor para o início para reler os dados
    printf("Maior capital financeiro armazenado em um único produto: R$ %.2f\n\n", maiorValorTotal);
    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Percorre o arquivo novamente para listar os produtos
        if (p.codigo != 0){ // Ignora posições vazias na segunda varredura
            float valorTotalAtual = p.qtd_disponivel * p.valor_unitario; // Recalcula o valor total acumulado deste produto
            if (valorTotalAtual == maiorValorTotal){ // Filtra apenas os produtos que empataram com o maior valor total
                exibirLinhaProduto(p); // Imprime as informações do produto na tela
            }
        }
    }
    printf("======================================================\n");
}
void alterarProduto(FILE *fPtr) {
    printf("\n--- ALTERAÇÃO DE PRODUTO ---\n");
    int codigo;
    printf("Digite o codigo do produto que deseja alterar (1 a %d): ", MAX_PRODUTOS);
    
    if (scanf("%d", &codigo) != 1) {
        limparBuffer();
        printf("\n>>> Erro: Digite um numero inteiro valido! <<<\n");
        return;
    }
    limparBuffer();

    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        printf("\n>>> Erro: Codigo fora dos limites (1 a %d)! <<<\n", MAX_PRODUTOS);
        return;
    }

    // Posiciona e le o registro direto no arquivo
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
    Produto p;
    // Le 1 estrutura 'Produto' da posição atual do arquivo e guarda na variável 'p'
    fread(&p, sizeof(Produto), 1, fPtr);

    if (p.codigo == 0) {
        printf("\n>>> Erro: Nenhum produto cadastrado no codigo %d! <<<\n", codigo);
        return;
    }

    printf("\n--- DADOS ATUAIS DO PRODUTO ---\n");
    exibirLinhaProduto(p);
    printf("-------------------------------\n");

    Produto pNovo = p; // Copia os dados atuais para alteracao gradual
    char opcao;

    // 1. Alterar Nome
    printf("\nDeseja alterar o NOME? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();
    if (tolower((unsigned char)opcao) == 's') {
        do {
            printf("Digite o novo nome: ");
            fgets(pNovo.nome, sizeof(pNovo.nome), stdin);
            pNovo.nome[strcspn(pNovo.nome, "\n")] = '\0';

            if (stringEstaEmBranco(pNovo.nome)) {
                printf("Erro: O nome do produto nao pode ficar em branco!\n");
            }
        } while (stringEstaEmBranco(pNovo.nome));
        paraMinusculo(pNovo.nome);
    }

    // 2. Alterar Categoria
    printf("Deseja alterar a CATEGORIA? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();
    if (tolower((unsigned char)opcao) == 's') {
        selecionarCategoria(pNovo.categoria);
    }

    // 3. Alterar Quantidade Minima
    printf("Deseja alterar a QUANTIDADE MÍNIMA? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();
    if (tolower((unsigned char)opcao) == 's') {
        do {
            printf("Digite a nova quantidade minima: ");
            if (scanf("%d", &pNovo.qtd_minima) != 1 || pNovo.qtd_minima < 0) {
                limparBuffer();
                printf("Erro: A quantidade minima nao pode ser negativa!\n");
                pNovo.qtd_minima = -1;
            } else {
                limparBuffer();
            }
        } while (pNovo.qtd_minima < 0);
    }

    // 4. Alterar Valor Unitario
    printf("Deseja alterar o VALOR UNITARIO? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();
    if (tolower((unsigned char)opcao) == 's') {
        do {
            printf("Digite o novo valor unitario (R$): ");
            if (scanf("%f", &pNovo.valor_unitario) != 1 || pNovo.valor_unitario <= 0) {
                limparBuffer();
                printf("Erro: O valor unitario deve ser maior que zero!\n");
                pNovo.valor_unitario = 0.0f;
            } else {
                limparBuffer();
            }
        } while (pNovo.valor_unitario <= 0);
    }

    // 5. Alterar Situacao
    printf("Deseja alterar a SITUACAO? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();
    if (tolower((unsigned char)opcao) == 's') {
        int novaSit = 0;
        do {
            printf("\nEscolha a nova situacao:\n");
            printf(" 1. Ativo\n");
            printf(" 2. Temporariamente Indisponivel\n");
            printf(" 3. Descontinuado\n");
            printf("Opcao: ");
            if (scanf("%d", &novaSit) != 1 || novaSit < 1 || novaSit > 3) {
                limparBuffer();
                printf("Erro: Opcao de situacao invalida!\n");
                novaSit = 0;
            } else {
                limparBuffer();
            }
        } while (novaSit < 1 || novaSit > 3);
        pNovo.situacao = novaSit;
    }

    // Confirmacao Final antes de salvar no arquivo
    printf("\n====================================\n");
    printf("     RESUMO DAS ALTERACOES          \n");
    printf("====================================\n");
    exibirLinhaProduto(pNovo);
    printf("====================================\n");
    printf("Deseja CONFIRMAR e salvar estas alteracoes? (S/N): ");
    scanf(" %c", &opcao);
    limparBuffer();

    if (tolower((unsigned char)opcao) == 's') {
        // Reposiciona o ponteiro do arquivo de volta na posição correta antes de escrever
        fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
        // Sobrescreve o registro antigo no arquivo binário com os dados atualizados
        fwrite(&pNovo, sizeof(Produto), 1, fPtr);
        // Descarrega o buffer da RAM para o disco imediatamente
        fflush(fPtr); // Garante que foi salvo fisicamente
        printf("\n>>> SUCESSO: Produto alterado com exito! <<<\n");
    } else {
        printf("\n>>> Operacao cancelada. Nenhuma alteracao foi salva. <<<\n");
    }
}
void excluirOuDescontinuarProduto(FILE *fPtr) {
    printf("\n--- EXCLUIR OU DESCONTINUAR PRODUTO ---\n");
    int codigo;
    printf("Digite o codigo do produto (1 a %d): ", MAX_PRODUTOS);

    if (scanf("%d", &codigo) != 1) {
        limparBuffer();
        printf("\n>>> Erro: Digite um numero inteiro valido! <<<\n");
        return;
    }
    limparBuffer();

    if (codigo < 1 || codigo > MAX_PRODUTOS) {
        printf("\n>>> Erro: Codigo fora dos limites (1 a %d)! <<<\n", MAX_PRODUTOS);
        return;
    }

    // Posiciona e le no arquivo
    fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
    Produto p;
    fread(&p, sizeof(Produto), 1, fPtr);

    if (p.codigo == 0) {
        printf("\n>>> Erro: Nenhum produto cadastrado no codigo %d! <<<\n", codigo);
        return;
    }

    printf("\n--- PRODUTO SELECIONADO ---\n");
    exibirLinhaProduto(p);
    printf("---------------------------\n");

    // REGRA DE IMPEDIMENTO (PDF Item 9)
    if (p.qtd_disponivel > 0) {
        printf("\n[BLOQUEIO]: O produto ainda possui %d unidade(s) em estoque!\n", p.qtd_disponivel);
        printf("A exclusao definitiva NAO e permitida enquanto houver estoque.\n\n");
        printf("Deseja marcar este produto como 'DESCONTINUADO'? (S/N): ");
        char op;
        scanf(" %c", &op);
        limparBuffer();

        if (tolower((unsigned char)op) == 's') {
            p.situacao = 3; // Descontinuado
            fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, fPtr);
            fflush(fPtr);
            printf("\n>>> SUCESSO: Situacao do produto alterada para 'Descontinuado'! <<<\n");
        } else {
            printf("\n>>> Operacao cancelada. Nenhuma alteracao realizada. <<<\n");
        }
        return;
    }

    // Se o estoque estiver ZERADO, a exclusao e liberada
    printf("\nEstoque zerado! Escolha uma das opcoes abaixo:\n");
    printf(" 1. Excluir DEFINITIVAMENTE o produto (liberar o codigo)\n");
    printf(" 2. Apenas marcar como DESCONTINUADO\n");
    printf(" 3. Cancelar operacao\n");
    printf("Opcao: ");
    
    int opcao = 0;
    if (scanf("%d", &opcao) != 1) {
        limparBuffer();
        opcao = 3;
    } else {
        limparBuffer();
    }

    char confirma;
    if (opcao == 1) {
        printf("\nTem certeza que deseja EXCLUIR DEFINITIVAMENTE o produto '%s'? (S/N): ", p.nome);
        scanf(" %c", &confirma);
        limparBuffer();

        if (tolower((unsigned char)confirma) == 's') {
            // Cria um registro zerado para sobrescrever o slot
            Produto produtoVazio = {0, "", "", 0, 0, 0.0f, 0};
            fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
            fwrite(&produtoVazio, sizeof(Produto), 1, fPtr);
            fflush(fPtr);
            printf("\n>>> SUCESSO: Produto excluido e codigo %d liberado para novos cadastros! <<<\n", codigo);
        } else {
            printf("\n>>> Exclusao cancelada. <<<\n");
        }
    } else if (opcao == 2) {
        printf("\nTem certeza que deseja marcar o produto como DESCONTINUADO? (S/N): ");
        scanf(" %c", &confirma);
        limparBuffer();

        if (tolower((unsigned char)confirma) == 's') {
            p.situacao = 3; // Descontinuado
            fseek(fPtr, (codigo - 1) * sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, fPtr);
            fflush(fPtr);
            printf("\n>>> SUCESSO: Produto marcado como 'Descontinuado'! <<<\n");
        } else {
            printf("\n>>> Operacao cancelada. <<<\n");
        }
    } else {
        printf("\n>>> Operacao cancelada. <<<\n");
    }
}
// Forca a sincronizacao de qualquer dado pendente em memoria buffer para o disco
void salvarDados(FILE *fPtr) {
    if (fPtr != NULL) {
        if (fflush(fPtr) == 0) {
            printf("\n>>> SUCESSO: Todos os dados foram salvos fisicamente no arquivo binario! <<<\n");
        } else {
            printf("\n>>> Erro ao sincronizar dados com o arquivo de disco! <<<\n");
        }
    }
}

// Rewind e verificacao de integridade do arquivo binario aberto
void carregarDados(FILE *fPtr) {
    if (fPtr != NULL) {
        rewind(fPtr); // Volta ao inicio do arquivo
        printf("\n>>> SUCESSO: Ponteiro resetado e dados prontos para leitura do arquivo! <<<\n");
    } else {
        printf("\n>>> Erro: Arquivo de dados invalido ou nao carregado! <<<\n");
    }
}
void encerrarSistema(FILE *fPtr) {
    printf("\n====================================\n");
    printf("   FINALIZANDO SISTEMA DE ESTOQUE   \n");
    printf("====================================\n");

    // 1. função já criada para descarregar o buffer
    salvarDados(fPtr);

    // 2. Fecha o ponteiro do arquivo binário
    if (fPtr != NULL) {
        fclose(fPtr);
        printf(" -> Arquivo 'produtos.dat' fechado com seguranca.\n");
    }
    printf(" -> Obrigado por utilizar o Cherie Belle Stock!\n");
    printf(" -> Sistema encerrado com sucesso. Ate logo!\n");
    printf("====================================\n\n");
}


void relatorioPorCategoria(FILE *fPtr){
    int produtosCadastrados[MAX_CATEGORIAS] = {0}; // Vetor para contar produtos por categoria
    int totalUnidades[MAX_CATEGORIAS] = {0}; // Vetor para somar as unidades em estoque por categoria
    float valorTotalArmazenado[MAX_CATEGORIAS] = {0.0f}; // Vetor para somar valor total por categoria

    rewind(fPtr); // Volta o ponteiro de leitura para o início do arquivo binário
    Produto p; // Variável temporária para armazenar os dados de cada produto durante a leitura

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo um registro de produto por vez até chegar ao fim
        if (p.codigo != 0){ // Verifica se a posição do arquivo contém um produto válido (ignora posições vazias)
            for (int i = 0; i < MAX_CATEGORIAS; i++){ // Percorre a lista de categorias válidas para identificar a categoria do produto
                if (strcmp(p.categoria, CATEGORIAS_VALIDAS[i]) == 0){ // Compara a categoria do produto com a categoria oficial do sistema
                    produtosCadastrados[i]++; // Soma +1 na contagem de tipos de produtos cadastrados nessa categoria
                    totalUnidades[i] += p.qtd_disponivel; // Soma a quantidade em estoque do produto ao total da categoria
                    valorTotalArmazenado[i] += (p.qtd_disponivel * p.valor_unitario); // Calcula o valor total do produto e acumula no total da categoria
                    break; // Interrompe a busca nas categorias já que encontrou a correspondente
                }
            }
        }
    }

    printf("\n================================================================================\n");
    printf("                      RELATORIO DE PRODUTOS POR CATEGORIA                       \n");
    printf("================================================================================\n");
    printf("%-20s | %-12s | %-14s | %-20s\n", "CATEGORIA", "QTD PRODUTOS", "TOTAL UNIDADES", "VALOR ARMAZENADO"); // Imprime os nomes das colunas da tabela alinhando o texto à esquerda com larguras fixas
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < MAX_CATEGORIAS; i++){ // Percorre todas as categorias para imprimir os dados calculados de cada uma
        printf("%-20s | %-12d | %-14d | R$ %.2f\n", CATEGORIAS_VALIDAS[i], produtosCadastrados[i], totalUnidades[i], valorTotalArmazenado[i]);
    }   // |-> Exibe os dados acumulados da categoria formatando texto, inteiros e valor em reais (R$)
    printf("================================================================================\n");
}


void relatorioGeralEstoque(FILE *fPtr){
    printf("\n==================================================================================================================\n");
    printf("                                            RELATORIO GERAL DO ESTOQUE                                            \n");
    printf("==================================================================================================================\n");

    rewind(fPtr); // Volta o ponteiro de leitura para o início do arquivo binário
    Produto p; // Variável temporária para armazenar os dados de cada produto lido do arquivo
    int total = 0; // Contador para acumular a quantidade total de produtos válidos exibidos

    printf("%-5s | %-20s | %-15s | %-8s | %-8s | %-12s | %-28s\n", "COD", "NOME", "CATEGORIA", "QTD", "QTD MIN", "VALOR UNIT", "SITUACAO");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(Produto), 1, fPtr) == 1){ // Varre o arquivo lendo um registro de produto por vez até atingir o fim do arquivo
        if (p.codigo != 0){ // Ignora posições vazias ou excluídas no arquivo
            char sitStr[30]; // Vetor para guardar o texto explicativo do status da situação do produto
            if (p.situacao == 1){ // Se a situação for 1, o produto está ativo no sistema
                strcpy(sitStr, "Ativo"); // Copia o texto "Ativo" para a variável sitStr
            } else if (p.situacao == 2){ // Se a situação for 2, o estoque do produto está zerado temporariamente
                strcpy(sitStr, "Temporariamente Indisponivel"); // Copia o texto "Temporariamente Indisponível" para sitStr
            } else{ // Caso contrário (situação 3), o produto não é mais comercializado
                strcpy(sitStr, "Descontinuado"); // Copia o texto "Descontinuado" para sitStr
            }

            printf("%-5d | %-20s | %-15s | %-8d | %-8d | R$ %-9.2f | %-28s\n", p.codigo, p.nome, p.categoria, p.qtd_disponivel, p.qtd_minima, p.valor_unitario, sitStr);
            total++; // Incrementa o contador de produtos cadastrados
        }
    }

    if (total == 0){ // Verifica se a contagem terminou zerada (nenhum produto no arquivo)
        printf("Nenhum produto cadastrado no arquivo.\n");
    }

    printf("==================================================================================================================\n");
    printf("Total de produtos cadastrados: %d\n", total); // Imprime a contagem final de produtos exibidos
}