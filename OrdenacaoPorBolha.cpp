#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

struct venda {
    string nomeProduto;
    int quantVendida;
    double precoUnitario;
    string dataVenda;
};

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distAno(1995, 2024);

string gerarDataAleat() {
    int dia = rand() % 28 + 1;
    int mes = rand() % 12 + 1;
    int ano = distAno(gen);
    return (dia < 10 ? "0" : "") + to_string(dia) + "/" +
           (mes < 10 ? "0" : "") + to_string(mes) + "/" + to_string(ano);
}

vector<venda> gerarVendasAleat(int numRegist) {
    vector<venda> vendas;
    default_random_engine gerador;
    uniform_int_distribution<int> distQuant(1, 100);
    uniform_real_distribution<double> distPreco(1.0, 100.0);
    vector<string> nomesProdutos = {
        "Macarr�o", "Feij�o", "Arroz", "Ma��", "Laranja", "Lim�o", "Carburador",
        "Calopsita", "Geladeira", "Barco"
    };

    for (int i = 0; i < numRegist; ++i) {
        venda venda;
        venda.nomeProduto = nomesProdutos[rand() % nomesProdutos.size()];
        venda.quantVendida = distQuant(gerador);
        venda.precoUnitario = distPreco(gerador);
        venda.dataVenda = gerarDataAleat();
        vendas.push_back(venda);
    }
    return vendas;
}

void ordenarPorBolha(vector<venda>& vendas) {
    int n = vendas.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vendas[j].precoUnitario > vendas[j + 1].precoUnitario) {
                venda temp = vendas[j];
                vendas[j] = vendas[j + 1];
                vendas[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numRegist = 1000;

    vector<venda> vendas = gerarVendasAleat(numRegist);
    ordenarPorBolha(vendas);

    return 0;
}

