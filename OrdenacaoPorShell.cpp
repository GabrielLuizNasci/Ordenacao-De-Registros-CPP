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

void ordenarPorShell(vector<venda>& vendas){
    int i, j;
	int add = 1;
	int tamArray = vendas.size();

    while(add <= tamArray / 3){
        add = add * 3 + 1;
    }

    while(add > 0){
        for(i = add; i < tamArray; i++) {
            venda registTemp = vendas[i];
            j = i;
            while(j >= add && vendas[j - add].precoUnitario > registTemp.precoUnitario){
                vendas[j] = vendas[j - add];
                j -= add;
            }
            vendas[j] = registTemp;
        }
        add = (add - 1) / 3;
    }
}

int main() {
    int numRegist = 1000;

    vector<venda> vendas = gerarVendasAleat(numRegist);
    ordenarPorShell(vendas);

    return 0;
}
