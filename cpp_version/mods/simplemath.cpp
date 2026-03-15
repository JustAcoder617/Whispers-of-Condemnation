#include <vector>
#include <string>
#include <random>

// Alteramos o retorno para vector e adicionamos o parâmetro 'quantidade'
std::vector<std::string> frases_aleatorias(std::vector<std::string> lista, int quantidade) {
    if (lista.empty() || quantidade <= 0) return {}; 

    static std::random_device rd;
    static std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, lista.size() - 1);

    std::vector<std::string> resultado;
    
    // Sorteia o número de vezes solicitado
    for (int i = 0; i < quantidade; ++i) {
        resultado.push_back(lista[dist(engine)]);
    }

    return resultado;
}