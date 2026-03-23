import java.nio.file.Files;
import java.nio.file.Path;

public class main {
    public static void main(String[] args) {
        things.print("Olá! Bem-vindo ao Whispers-Of-Condemnation!");

        things.print("Digite o nome do Jogador 1: ");
        Object p1 = things.scanf("s");

        things.print("Jogador 2, digite seu nome: ");
        Object p2 = things.scanf("s");

        things.print("Redirecionando...");
        jogo(p1, p2);
    }

    public static void jogo(Object player1, Object player2) {
        int jg1vivo = 1;
        int jg2vivo = 1;
        int vez = 1;

        while (jg1vivo == 1 && jg2vivo == 1) {
            String nomeAtual = (vez == 1) ? player1.toString() : player2.toString();
            things.print("\n--- Vez de " + nomeAtual + " ---");
            things.print("1. Condenar | 2. Passar");

            int escolha = (int) things.scanf("i");

            if (escolha == 1) {
                int dificuldade = (int) (Math.random() * 3) + 1;
                boolean matou = false;

                if (dificuldade == 1) {
                    matou = Math.random() < 0.25;
                } else if (dificuldade == 2) {
                    matou = Math.random() < 0.50;
                } else {
                    matou = Math.random() < 0.75;
                }

                if (matou) {
                    things.print("O MARTELO CAIU! Fim de jogo para o oponente.");
                    if (vez == 1) jg2vivo = 0; else jg1vivo = 0;
                } else {
                    things.print("O martelo falhou... A sorte mudou.");
                }
            }
            vez = (vez == 1) ? 2 : 1;
        }

        things.print("\nFim da sessão de julgamento.");
        things.print("...");

        // Passamos o player1 para a avaliação para registrar quem deu o feedback
        avaliation(player1);
    }

    public static void avaliation(Object player) {
        String conteudo = "";
        String urlReal = "";

        try {
            // Lendo a URL criptografada do arquivo config.txt no seu Zorin
            Path caminho = Path.of("config.txt");
            conteudo = Files.readString(caminho);
            urlReal = javaweb.descriptografar(conteudo, 42);
        } catch (Exception e) {
            System.out.println("Erro ao abrir as configurações: " + e.getMessage());
            return;
        }

        things.print("Gostaria de deixar sua opinião sobre o nosso jogo? (1.sim 2.não)");
        int choice = (int) things.scanf("i");

        if (choice == 1) {
            things.print("Digite sua opinião: ");
            Object opiniao = things.scanf("s");

            // Criando o JSON estruturado para enviar via Webhook
            String jsonDados = "{" +
                    "\"jogador\":\"" + player.toString() + "\"," +
                    "\"feedback\":\"" + opiniao.toString() + "\"," +
                    "\"os\":\"Zorin OS\"," +
                    "\"hardware\":\"Acer Aspire 5\"" +
                    "}";

            // Dispara o webhook de forma assíncrona (não trava o jogo)
            javaweb.dispararWebhook(urlReal, jsonDados);

            things.print("Opiniao enviada com sucesso para o servidor!");
        }
    }
}