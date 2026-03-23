import java.util.Scanner;

public class things {
    private static Scanner leitor = new Scanner(System.in);

    public static void print(Object printar) {
        System.err.println(printar);
    }

    public static Object scanf(String tipo) {
        if (tipo.equals("i")) {
            int coisa = leitor.nextInt();
            leitor.nextLine(); 
            return coisa;
        }
        if (tipo.equals("d")) {
            double coisa = leitor.nextDouble();
            leitor.nextLine(); 
            return coisa;
        }
        if (tipo.equals("s")) {
            return leitor.next();
        }
        return null;
    }

    public static String fgets() {
        return leitor.nextLine();
    }
}