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
        printf("\n19. Sair do Sistema\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(cfPtr); 
                break;
            case 2:
                listarTodosProdutos(cfPtr);
                break;
            //case 3:
               // alterarProduto(cfPtr);
               // break;
            //case 4:
               // excluirOuDescontinuarProduto(cfPtr);
               // break;
            case 5:
                consultarProdutoPorCodigo(cfPtr);
                break;
            case 6:
                consultarProdutoPorNome(cfPtr);
                break;
            case 7:
                consultarProdutosPorSituacao(cfPtr);
                break;
           // case 8:
                //consultarProdutosPorCategoria(cfPtr);
               // break;
            case 9:
                consultarProdutosAbaixoDoMinimo(cfPtr);
                break;
            case 10:
                consultarProdutosSemEstoque(cfPtr);
                break;
            //case 11:
               // buscarProdutoMaiorValorUnitario(cfPtr);
               // break;
           //case 12:
               // buscarProdutoMaiorValorArmazenado(cfPtr);
                //break;
            case 13:
                exibirValorIndividualEstoque(cfPtr);
                break;
            //case 14:
                //ordenarProdutosPorNome(cfPtr);
               // break;
            //case 15:
                //ordenarProdutosPorQuantidade(cfPtr);
               // break;
            //case 16:
               // relatorioPorCategoria(cfPtr);
               // break;
            //case 17:
                //ordenarProdutosPorValorUnitario(cfPtr);
                break;
            case 18:
                calcularValorTotalEstoque(cfPtr);
                break;
            case 19:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao inválida! Tente novamente.\n");
        }

    } while (opcao != 19);

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
}
    printf("\n=======================================================\n");
    printf("\nVALOR TOTAL DE TODOS OS PRODUTOS EM ESTOQUE: R$ %.2f\n", soma_total);
    printf("\n=======================================================\n");
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

 // Utiliza a chave primária (código) para calcular a posição exata
 // no arquivo binário usando fseek(), permitindo busca em tempo O(1).

void consultarProdutoPorCodigo(FILE *fPtr) {
    printf("\n--- CONSULTA DE PRODUTO POR CÓDIGO ---\n");
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
    if (strlen(termoBusca) == 0) {
    if (strlen(termoBusca) == 0) {
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
}

// Solicita ao usuário qual situação filtrar (1 = Ativo, 2 = Indisponível,
// 3 = Descontinuado) e percorre o arquivo listando apenas os correspondentes.
 
void consultarProdutosPorSituacao(FILE *fPtr) {
    printf("\n--- CONSULTA DE PRODUTOS POR SITUAÇÃO ---\n");
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

    // Reposiciona o ponteiro para o início do arquivo
    rewind(fPtr);

    Produto p;
    int encontrados = 0;

    // Vetor de ponteiros para string que mapeia a posição numérica no texto do cabeçalho
    // Posição 1 = "ATIVO", Posição 2 = "INDISPONÍVEL", Posição 3 = "DESCONTINUADO"
    const char *rotulosSituacao[] = {"", "ATIVO", "INDISPONÍVEL", "DESCONTINUADO"};
    printf("\n--- PRODUTOS NA SITUAÇÃO: %s ---\n", rotulosSituacao[situacaoDesejada]);

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