#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath> 
#include <limits> // Para numeric_limits
#include <locale>
#include <sstream> // Necessário para a função de formatação
#include <Windows.h> // Adicionado para suporte a caracteres especiais no Windows
#include "../json.hpp"

using namespace std;
using json = nlohmann::json;

// Estruturas de dados
struct Material {
    string nome;
    float altura;
    float comprimento;
    float area;
};

struct Piso {
    string nome;
    float largura;
    float comprimento;
    float area;
};

struct Muro {
    float altura;
    float comprimento;
    float area;
};

struct User {
    string username;
    string password;
};

// Persistencia de Dados
vector<User> carregar_usuarios() {
    vector<User> usuarios;
    ifstream i("data/users.json");
    if (i.is_open()) {
        json j_usuarios;
        i >> j_usuarios;
        for (const auto& j_user : j_usuarios) {
            usuarios.push_back({j_user["username"], j_user["password"]});
        }
    }
    return usuarios;
}

void salvar_usuarios(const vector<User>& usuarios) {
    json j_usuarios;
    for (const auto& user : usuarios) {
        j_usuarios.push_back({
            {"username", user.username},
            {"password", user.password}
        });
    }

    ofstream o("data/users.json");
    if (o.is_open()) {
        o << setw(4) << j_usuarios << endl;
        cout << "\nDados de usuários salvos com sucesso!" << endl;
    } else {
        cerr << "Erro ao salvar o arquivo de usuários." << endl;
    }
}

// Cadastro e Login de Empresa
void cadastrar_usuario(vector<User>& usuarios) {
    string username, password;
    cout << "\n--- Cadastro de Empresa ---\n";
    cout << "Digite um login para a empresa: ";
    cin >> username;
    
    // Verifica se o usuario ja existe
    for (const auto& user : usuarios) {
        if (user.username == username) {
            cout << "Nome de usuário já existe. Tente outro." << endl;
            return;
        }
    }

    cout << "Digite uma senha: ";
    cin >> password;
    
    usuarios.push_back({username, password});
    cout << "Empresa cadastrada com sucesso!" << endl;
}

bool fazer_login(const vector<User>& usuarios, string& usuario_logado) {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Nome de usuário: ";
    cin >> username;
    cout << "Senha: ";
    cin >> password;

    for (const auto& user : usuarios) {
        if (user.username == username && user.password == password) {
            cout << "\nBem-vindo(a), " << username << "!" << endl;
            usuario_logado = username;
            return true;
        }
    }
    cout << "Login falhou. Usuário ou senha incorretos." << endl;
    return false;
}

// Função genérica para validar a entrada de float
void get_valid_float_input(float& value, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good()) {
            break;
        } else {
            cout << "Entrada inválida. Por favor, digite um número." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Função genérica para validar a entrada de int
void get_valid_int_input(int& value, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good()) {
            break;
        } else {
            cout << "Entrada inválida. Por favor, digite um número." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Função para formatar um float com vírgula em vez de ponto
string formatar_com_virgula(float valor, int precisao) {
    stringstream ss;
    ss << fixed << setprecision(precisao) << valor;
    string s = ss.str();
    size_t pos = s.find('.');
    if (pos != string::npos) {
        s[pos] = ',';
    }
    return s;
}

void calcular_muro(const vector<Material>& materiais) {
    Muro muro;
    int escolha_material;

    cout << "\n--- Cálculo de Materiais para Muro ---\n";
    cout << "Quais as dimensões do muro a ser construído?" << endl;
    
    get_valid_float_input(muro.altura, "Altura (m): ");
    get_valid_float_input(muro.comprimento, "Comprimento (m): ");
    muro.area = (muro.altura) * (muro.comprimento);

    cout << "\nÁrea total do muro: " << formatar_com_virgula(muro.area, 2) << " metros quadrados\n\n";

    cout << "Qual material deseja utilizar para a construção deste muro?" << endl;
    for(size_t i = 0; i < materiais.size(); i++) {
        cout << (i+1) << " - " << materiais[i].nome << endl;
    }
    get_valid_int_input(escolha_material, "Opção: ");

    if (escolha_material >= 1 && escolha_material <= materiais.size()) {
        Material material_escolhido = materiais[escolha_material - 1];
        
        float qtd_material = muro.area / material_escolhido.area;
        float qtd_final = qtd_material * 1.05; // 5% de desperdício

        int qtd_material_arredondada = static_cast<int>(round(qtd_material));
        int qtd_final_arredondada = static_cast<int>(ceil(qtd_final));

        cout << "\nQuantidade de material (sem desperdício): " << qtd_material_arredondada << " unidades\n";
        cout << "Quantidade final (com 5% de desperdício): " << qtd_final_arredondada << " unidades\n";
    } else {
        cout << "Por favor, digite um valor válido!" << endl;
    }
}

void calcular_piso(const vector<Piso>& pisos) {
    Muro area_piso;
    int escolha_piso;

    cout << "\n--- Cálculo de Materiais para Piso ---\n";
    cout << "Quais as dimensões do cômodo a ser revestido?" << endl;
    
    get_valid_float_input(area_piso.altura, "Largura (m): ");
    get_valid_float_input(area_piso.comprimento, "Comprimento (m): ");
    area_piso.area = area_piso.altura * area_piso.comprimento;

    cout << "\nÁrea total do piso: " << formatar_com_virgula(area_piso.area, 2) << " metros quadrados\n\n";

    cout << "Selecione o tipo de porcelanato:" << endl;
    for(size_t i = 0; i < pisos.size(); i++) {
        cout << (i+1) << " - " << pisos[i].nome << endl;
    }
    get_valid_int_input(escolha_piso, "Opção: ");

    if (escolha_piso >= 1 && escolha_piso <= pisos.size()) {
        Piso piso_escolhido = pisos[escolha_piso - 1];

        float qtd_piso = area_piso.area / piso_escolhido.area;
        float qtd_final = qtd_piso * 1.05; // Adicionando 5% de desperdício

        int qtd_piso_arredondada = static_cast<int>(round(qtd_piso));
        int qtd_final_arredondada = static_cast<int>(ceil(qtd_final));

        cout << "\nQuantidade de peças (sem desperdício): " << qtd_piso_arredondada << " unidades\n";
        cout << "Quantidade final de peças (com 5% de desperdício): " << qtd_final_arredondada << " unidades\n";
    } else {
        cout << "Por favor, digite um valor válido!" << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // Habilita a exibição de caracteres UTF-8 no console do Windows

    // Inicialização dos materiais de muro
    vector<Material> materiais;
    materiais.push_back({"Tijolo Comum (24x14x11.5)cm", 0.145, 0.24, (0.145 * 0.24)});
    materiais.push_back({"Bloco Cerâmico (29x19x14)cm", 0.19, 0.29, (0.19 * 0.29)});
    materiais.push_back({"Bloco Estrutural (39x19x14)cm", 0.19, 0.39, (0.19 * 0.39)});

    // Inicialização dos materiais de piso
    vector<Piso> pisos;
    pisos.push_back({"Porcelanato (50x50)cm", 0.50, 0.50, (0.50 * 0.50)});
    pisos.push_back({"Porcelanato (1x1)m", 1.0, 1.0, (1.0 * 1.0)});
    pisos.push_back({"Porcelanato (1,20x1,20)m", 1.20, 1.20, (1.20 * 1.20)});

    vector<User> usuarios = carregar_usuarios();
    int escolha_menu;
    string usuario_logado = "";

    while (usuario_logado.empty()) {
        get_valid_int_input(escolha_menu, "\n--- Menu Inicial ---\n1 - Fazer Login\n2 - Cadastrar\n0 - Sair\nEscolha uma opção: ");

        if (escolha_menu == 1) {
            if (fazer_login(usuarios, usuario_logado)) {
                break;
            }
        } else if (escolha_menu == 2) {
            cadastrar_usuario(usuarios);
        } else if (escolha_menu == 0) {
            salvar_usuarios(usuarios);
            return 0;
        } else {
            cout << "Opção inválida. Tente novamente." << endl;
        }
    }

    int opcao_consulta;
    while (true) {
        get_valid_int_input(opcao_consulta, "\n-------- Menu de Opções --------\n1 - Calcular material para muro\n2 - Calcular material para piso\n0 - Sair\nEscolha uma opção: ");

        if (opcao_consulta == 1) {
            calcular_muro(materiais);
        } else if (opcao_consulta == 2) {
            calcular_piso(pisos);
        } else if (opcao_consulta == 0) {
            salvar_usuarios(usuarios);
            cout << "Programa encerrado. Até mais!" << endl;
            break;
        } else {
            cout << "Opção inválida. Tente novamente." << endl;
        }
    }

    return 0;
}