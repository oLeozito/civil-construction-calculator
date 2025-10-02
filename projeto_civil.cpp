#include <iostream>
#include <vector>

using namespace std;

struct Material{
    string nome;
    float altura;
    float comprimento;
    float area;
    // ADICIONAR PREÇO DA UNIDADE
};

struct Muro{
    float altura;
    float comprimento;
    float area;
};


int main()
{ 
    int escolha;

    // Lista simples com matériais possiveis.
    vector<Material> materiais;

    // Adicionando os materiais padrão (medidas em metros para facilitar o cálculo)

    // Tijolo Comum (24x14x11.5) -> Altura x Comprimento: 14.5cm x 24cm
    materiais.push_back({"Tijolo Comum (24x14x11.5)", 0.145, 0.24, (0.145 * 0.24)});

    // Bloco Cerâmico (29x19x14) -> Altura x Comprimento: 19cm x 29cm
    materiais.push_back({"Bloco Cerâmico (29x19x14)", 0.19, 0.29, (0.19 * 0.29)});

    // Bloco de Concreto (39x19x14) -> Altura x Comprimento: 19cm x 39cm
    materiais.push_back({"Bloco de Concreto (39x19x14)", 0.19, 0.39, (0.19 * 0.39)});

    Muro muro;

    cout << "Quais as dimensões do muro a ser construido?" << endl;
    cout << "Altura: "; 
    cin >> muro.altura;
    cout << "Comprimento: ";
    cin >> muro.comprimento;
    muro.area = (muro.altura)*(muro.comprimento);

    cout << "Qual material deseja utilizar pra a construcao deste muro?" << endl;
    for(int i = 0; i<materiais.size(); i++){
        cout << (i+1) << " - " << materiais[i].nome << endl;
    }
    cin >> escolha;

    // Se o material estiver na lista de materiais, continua.
    if (escolha >= 1 && escolha <= materiais.size()){
        Material material_escolhido = materiais[escolha-1];

        float qtd_material = muro.area/material_escolhido.area;
        cout << "Quantidade estimada de material: " << qtd_material << endl;
    }else{
        cout << "Por favor digite um valor válido!" << endl;
    }
    return 0;
}