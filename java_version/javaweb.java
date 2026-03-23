import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class javaweb {

    // Retorna a String pronta para uso
    public static String descriptografar(String urlCifrada, int chave) {
        StringBuilder resultado = new StringBuilder();
        for (int i = 0; i < urlCifrada.length(); i++) {
            char c = urlCifrada.charAt(i);
            resultado.append((char) (c ^ chave));
        }
        return resultado.toString();
    }

    public static void dispararWebhook(String url, String jsonDados) {
        HttpClient client = HttpClient.newHttpClient();

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(url))
                    .header("Content-Type", "application/json")
                    .POST(HttpRequest.BodyPublishers.ofString(jsonDados))
                    .build();

            // Usando sendAsync para não travar o jogo
            client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                    .thenApply(HttpResponse::statusCode)
                    .thenAccept(status -> {
                        System.out.println("Webhook enviado! Status: " + status);
                    });
            // Removi o .join() para ser 100% assíncrono (o jogo segue enquanto envia)

        } catch (Exception e) {
            System.err.println("Erro ao disparar webhook: " + e.getMessage());
        }
    }

}