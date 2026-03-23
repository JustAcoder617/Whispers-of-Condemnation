public class simplemath{
    public static Object char_aleatorio(char lista[], int qquantidade){
    int sorteio = (int)(Math.random() * lista.length) + 1;
    return lista[sorteio];
    }
}