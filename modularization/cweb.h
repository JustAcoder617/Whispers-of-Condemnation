#ifndef CWEB_H
#define CWEB_H
//Antes de tudo: Obrigado por usar o CWEB, espero que ele seja útil para o seu projeto! Este arquivo é destinado a fornecer funcionalidades relacionadas a webhooks e comunicação com servidores, usando a biblioteca libcurl para facilitar as requisições HTTP. Ele inclui uma função para descriptografar dados (caso você queira armazenar URLs ou outras informações sensíveis de forma criptografada) e uma função para disparar um webhook, enviando um JSON formatado com os dados desejados. Lembre-se de ajustar os caminhos dos arquivos, as chaves de criptografia e o formato do JSON conforme necessário para o seu projeto específico. Se tiver alguma dúvida ou precisar de ajuda para integrar este código ao seu projeto, sinta-se à vontade para perguntar no nosso canal de duvidas do discord: https://discord.gg/x4D2FZpqNn
#include <curl/curl.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

static inline char* descriptografar(char *dados, int tamanho, int chave) { // aqui, a função descriptografar recebe os dados criptografados, o tamanho dos dados e a chave de criptografia. Ela percorre cada caractere dos dados, verificando se é um caractere de nova linha ou retorno de carro para substituir por null terminator, e aplica uma operação XOR com a chave para descriptografar os dados. O resultado é retornado como uma string descriptografada pronta para uso ou uma string criptografada, dependo se o arquivo/dado ja esteja em formato criptografado ou não. Lembre-se de usar a mesma chave para criptografar e descriptografar os dados, e de ajustar a função conforme necessário para o seu formato específico de criptografia, se for diferente do exemplo simples de XOR.
    for(int i = 0; i < tamanho; i++) {
        if(dados[i] == '\n' || dados[i] == '\r') {
            dados[i] = '\0';
            break; 
        }
        dados[i] = (char)(dados[i] ^ chave);//Atenção: a chave de criptografia deve ser a mesma usada tanto para criptografar quanto para descriptografar os dados. Certifique-se de escolher uma chave segura e mantê-la protegida, especialmente se estiver lidando com informações sensíveis. O exemplo acima usa uma operação XOR simples para criptografia/descriptografia, mas dependendo do nível de segurança necessário, você pode querer implementar um método de criptografia mais robusto.
    }
    return dados;
}

// Note os 3 argumentos aqui: feedback, login e pontos
//o formato aqui está sendo usado com texto, user_login e pontos, mas você pode ajustar conforme necessário no seu projeto!
static inline int disparar_webhook(char *texto, char *user_login, int pontos) {
    // Tenta abrir o arquivo de config
    //aqui, se você tiver um caminho diferente para o arquivo de configuração, ajuste o caminho abaixo, se não tiver nada para usar o sistema de crptografia ou quiser usar esta função apenas para urls normais sem criptografia, ajuste a função removendo a parte de descriptografia e lendo o arquivo, e use a URL diretamente na argumentação, onde está a variável url, ou seja, substitua a parte de leitura do arquivo e descriptografia por algo como: char *url = "sua_url_aqui", ou ajuste conforme necessário para o seu projeto específico.
    CURL *curl;
    
    FILE *f = fopen("hard_assets/config.txt", "rb");
    if (!f) {
        puts("Erro: Arquivo de config não encontrado.");
        return;
    }

    if (!CURLE_OK)
    {
        puts("Erro: Falha ao se conectar com a internet ou fazer o processo de envio de algum dado, verifique sua conexão e tente novamente.");
        fclose(f);
        return 1;
    }
    

    char url_encriptada[512];
    size_t n = fread(url_encriptada, 1, sizeof(url_encriptada) - 1, f);
    fclose(f);

    if (n > 0) {
        url_encriptada[n] = '\0';
        // Descriptografa a URL
        char *url = descriptografar(url_encriptada, (int)n, 42);
     //desta parte em diante, o curl vai entrar em ação para enviar/disparar a URL desejada.
        curl = curl_easy_init();
        if(curl) {
            char json[2048];
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            char horario[64];
            strftime(horario, sizeof(horario), "%d/%m/%Y %H:%M:%S", tm_info);

            // Monta o JSON com os 3 dados
            //atenção! como aqui falamos de webhooks, esse json envia dados para o nosso canal do discord com a url. AQUI VOCÊ VAI TER QUE MUDAR PARA O SEU PRÓPRIO FORMATO DE JSON, SE O SEU WEBHOOK NÃO FOR DO DISCORD, OU SE VOCÊ QUISER USAR ESSA FUNÇÃO PARA OUTROS FINS, COMO ENVIAR DADOS PARA UM SERVIDOR, VOCÊ VAI TER QUE AJUSTAR O FORMATO DO JSON E OS DADOS QUE QUER ENVIAR, AQUI EU USEI UM EXEMPLO BÁSICO PARA ENVIAR OS 3 DADOS (TEXTO, LOGIN E PONTOS) PARA UM CANAL DO DISCORD, MAS VOCÊ PODE AJUSTAR PARA O QUE QUISER!
            snprintf(json, sizeof(json),
                     "{\"content\": \"🎮 **New Feedback!!**\\n**User:** `%s`\\n**Message:** %s\\n🕒 %s \\n**Rating:** %i/10\"}",
                     user_login, texto, horario, pontos);

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_perform(curl);

            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }
    }
}

#endif