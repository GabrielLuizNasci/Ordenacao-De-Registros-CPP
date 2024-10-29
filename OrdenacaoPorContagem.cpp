#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

struct venda{
    string nomeProduto;
    int quantVendida;
    double precoUnitario;
    string dataVenda;
};

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distAno(1995, 2024);


string gerarDataAleat(){
	int dia = rand() % 28 + 1;
	int mes = rand() % 12 + 1;
	int ano = distAno(gen);
	
	return (dia < 10 ? "0" : "") + to_string(dia) + "/" +
           (mes < 10 ? "0" : "") + to_string(mes) + "/" + to_string(ano);
}

vector<venda> gerarVendasAleat(int numRegist){
	vector<venda> vendas;
	default_random_engine gerador;
	uniform_int_distribution<int> distQuant(1, 100);
	uniform_real_distribution<double> distPreco(1.0, 100.0);
	vector<string> nomesProdutos = {
		"Macarrão", "Feijão", "Arroz", "Maça", "Laranja", "Limão", "Carburador",
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

int buscaQuantMax(const vector<venda>& vendas){
	int quantMax = 0;
	for(const auto& v : vendas) {
		if(v.quantVendida > quantMax){
			quantMax = v.quantVendida;
		}
	}
	return quantMax;
}

void ordenarPorContagem(vector<venda>& vendas){
	int maxQuant = buscaQuantMax(vendas);
	vector<int> c(maxQuant + 1, 0);
	
	for(const auto& v : vendas){
		c[v.quantVendida]++;
	}
	
	for(int i = 1; i < c.size(); i++){
		c[i] += c[i - 1];
	}
	
	vector<venda> b(vendas.size());
	
	for(int i = vendas.size() - 1; i >= 0; i--){
		b[c[vendas[i].quantVendida] - 1] = vendas[i];
        c[vendas[i].quantVendida]--;
	}
	
	vendas = b;
}

int main() {
    int numRegist = 1000000;

    vector<venda> vendas = gerarVendasAleat(numRegist);
    ordenarPorContagem(vendas);

    return 0;
}
