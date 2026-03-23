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
        int vez = 1; // 1 para Jogador 1, 2 para Jogador 2

        while (jg1vivo == 1 && jg2vivo == 1) {
            String nomeAtual = (vez == 1) ? player1.toString() : player2.toString();
            things.print("\n--- Vez de " + nomeAtual + " ---");
            things.print("1. Condenar | 2. Passar");

            int escolha = (int) things.scanf("i");

            if (escolha == 1) {
                // Sorteia a dificuldade do martelo (1 a 3)
                int dificuldade = (int) (Math.random() * 3) + 1;
                boolean matou = false;

                // Exemplo simplificado de lógica de chance
                if (dificuldade == 1) {
                    // 25% de chance (seu array {'s','n','n','n'})
                    matou = Math.random() < 0.25;
                } else if (dificuldade == 2) {
                    // 50% de chance
                    matou = Math.random() < 0.50;
                } else {
                    // 75% de chance
                    matou = Math.random() < 0.75;
                }

                if (matou) {
                    things.print("O MARTELO CAIU! Fim de jogo para o oponente.");
                    if (vez == 1) jg2vivo = 0; else jg1vivo = 0;
                } else {
                    things.print("O martelo falhou... A sorte mudou.");
                }
            }

            // Alterna a vez: se era 1 vira 2, se era 2 vira 1
            vez = (vez == 1) ? 2 : 1;
        }

        things.print("Fim da sessão de julgamento.");
        things.print("...");
        avaliation();
    }
    public static void avaliation(){
        String conteudo="a";
        String real="z";
        try {
            Path caminho = Path.of("config.txt");
            conteudo = Files.readString(caminho);
            real=javaweb.descriptografar(conteudo, 42);
        } catch (Exception e) {
            System.out.println("Erro ao abrir o arquivo: " + e.getMessage());
            return;
        }

    }
}