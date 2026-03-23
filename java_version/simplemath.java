public class simplemath{
    public static Object char_aleatorio(char lista[], int qquantidade){
    int sorteio = (int)(Math.random() * qquantidade) + 1;
    return lista[sorteio];
    }
}