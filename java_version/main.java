public class main {
    public static void main(String[] args) {
        things.print("Olá! bem vindo ao Whispers-Of-Condenation (versão Java)!");
        things.print("Digite seu nome de desenvolvedor/usuário: ");
        Object player1=things.scanf("s");
        things.print("JOgador 2, digite seu nome: ");
        Object player2=things.scanf("s");
        things.print("Redirecioonando...");
        jogo(player1,player2);
    }
    public static void jogo(Object player1, Object player2) {
        int jg1vivo=1;
        int jg2vivo=1;
        int primeira=1;
        while (jg1vivo==1 && jg2vivo==1) { 
            if(primeira==1){
                things.print("Jogador 1, escolha: 1.Condenar 2.passar");
                Object choice=things.scanf("i");
                if ((int)choice==1){
                    int sorteio = (int)(Math.random() * 4) + 1;
                    if(sorteio==1){
                        char escolhas[]={'s','n','n','n'};
                        String decisao=(String)simplemath.char_aleatorio(escolhas, sorteio);
                        if(decisao.equals("s")){
                            jg2vivo=0;
                        }
                    }
                }
            }
        
        }
    }
}