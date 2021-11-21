#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <locale>

using namespace std;

string conteudoDoCabecalho(ifstream& arquivo)
{   
    // Retorna string do cabebalho no programa. Caso o arquivo .txt nao exista, entramos no else abaixo.
    string linhas = "";                  // Sa�da
    
    if (arquivo) 
    {
	while (arquivo.good())
	{
	    string lerLinha;
	    getline (arquivo , lerLinha);
	    lerLinha += "\n";
	    
	    linhas += lerLinha;
	}
	    return linhas;
    }
    else {
	    return "ERROR! O cabe�alho n�o existe";
    }
}

string lerLinha(string &arquivonome, int n) //
{
    ifstream arquivo(arquivonome); //
    string saida;

    // Pular linhas
    for (int i = 0; i < n; i++)
    {
        getline(arquivo, saida);
    }
    // Saida atual
    getline(arquivo, saida);
    arquivo.close();
    return saida;
}

class ecpBank
{
    public:
        void cabecalho();
        // Menus 
        void mainMenu();
        void telaLogin();
        void telaRegistro();
        void telaInfo();
        void telaMenu();
        void consultarDinheiro();
        void sacarDinheiro();
        void depositarDinheiro();
        void transferirDinheiro();

        // funccoes para criar, autenticar, sacar, depositar e transferir
        bool criarUsuario(const string nomeusuario, const string senha);
        bool autenticarUsuario(const string tentarUser);
        bool autenticarSenha(const string tentarUser, const string tentarPass);
        bool sacar(const string nomeusuario, float saldo);
        bool depositar(const string nomeusuario, float saldo);
        bool transferir(const string nomeusuario1, const string nomeusuario2, float saldo);

    private:
        bool autenticada;
        string login_usuario;
        string senha_usuario;
};

void ecpBank::cabecalho()
{
    ifstream leituraCabecalho("cabecalho.txt");
    string saida = conteudoDoCabecalho(leituraCabecalho);
    cout << saida << endl;
    leituraCabecalho.close();    
}

void ecpBank::mainMenu()
{   

    int opcao;

    do
    {   
        system("cls"); // limpar o console do programa e novamente chama o cabecalho
        cabecalho();
        cout << "   Por favor, escolha uma opcao!" << endl;
        cout << "   1 : LOGIN" << endl;
        cout << "   2 : REGISTRO" << endl;
        cout << "   3 : INFORMACOES" << endl;
        cout << "   4 : SAIR" << endl;
        cout << "\n\n";
        cout << "   opcao : "; cin >> opcao;

        switch(opcao)
        {
            case 1:
                cout << "   LOGANDO...\n";
                Sleep(500);
                telaLogin();
                break;

            case 2:
                cout << "   REGISTRANDO! AGUARDE UM MOMENTO...\n";
                Sleep(500);
                telaRegistro();
                break;

            case 3:
                cout << "   MAIORES INFORMACOES\n";
                Sleep(500);
                telaInfo();
                break;
            
            case 4:
                cout << "   SAINDO...\n";
                Sleep(500);
                opcao = 4;
                exit(0);

            default:
                cout << "   OPCAO INVALIDA!\n";
                cout << "   Por favor, selecione uma opcao de 1 a 4.\n";
                Sleep(500);
                mainMenu();
                break;
        }
    } while (opcao != 4);
}

void ecpBank::telaLogin()
{       

    system("cls"); // limpar o console do programa e novamente chama o cabecalho
    cabecalho();
    cout << "   Por favor, entre com seu nome de usuario. " << endl << "  Usuario : "; cin >> login_usuario;
    if (autenticarUsuario(login_usuario))
    {
        cout << "   Por favor, entre com sua senha. " << endl << "  senha : "; cin >> senha_usuario;
        if (autenticarSenha(login_usuario, senha_usuario))
        {   
            autenticada = true;
            cout << "   Login realizado com sucesso!" << endl;
            Sleep(500);
            telaMenu();
        }
        else
        {
            cout << "   SENHA ERRADA! Por favor, tente uma nova senha!" << endl;
            Sleep(500);
            telaLogin();
        }
    }
    else
    {
        cout << "   USUARIO NAO EXISTE! Por favor, tente um outro usuario!" << endl;
        cout << "\n\n";
        system("PAUSE");
        Sleep(500);
        mainMenu();
    }
}

void ecpBank::telaRegistro()
{   
    system("cls"); // limpar o console do programa e novamente chama o cabecalho
    cabecalho();
    string usuario, senhaa;
    cout << "   Por favor, tente um usuario que ainda nao foi utilizado. " << endl << " Usuario : "; cin >> usuario;
    cout << "   Por favor, escolha uma senha. " << endl << " senha : "; cin >> senhaa;

    if(criarUsuario(usuario, senhaa)) // se a condicao 'if' for verdadeira, ele cria o usuario
    {
        cout << "   SUCESSO! Usuario: " << usuario << " criado.\n";
        Sleep(500);
        mainMenu();
    }
    else
    {
        cout << "   Este usuario ja existe. Por favor, tente um outro usuario.\n";
        Sleep(500);
        telaRegistro();
    }
}

void ecpBank::telaInfo()
{   

    system("cls");
    cabecalho();
    cout << "   Feito por Cassio Lima, Davy Pedro e Esdras de Aquino" << endl;
    cout << "   Versao 2.0 do Projeto da disciplina de Orientacao a Objetos." << endl;

    cout << "\n\n\n";

    system("PAUSE");
    mainMenu();
}

void ecpBank::telaMenu()
{
    system("cls");
    cabecalho();

    int opcao;
    while(1)
    {
        cout << "   Por favor, escolha uma opCAcacacacao." << endl;
        cout << "   1 [*] SALDO ATUAL." << endl;
        cout << "   2 [*] DEPOSITAR DINHEIRO." << endl;
        cout << "   3 [*] SACAR DINHEIRO." << endl;
        cout << "   4 [*] TRANSFERIR DINHEIRO." << endl;
        cout << "   5 [*] SAIR." << endl;
        cout << "\n\n";
        cout << "   opcao : "; cin >> opcao;

        switch(opcao)
        {
            case 1:
                cout << "   SALDO ATUAL...\n";
                Sleep(500);
                // caso em que o usuario poder consultar o saldo
                consultarDinheiro();
                break;

            case 2:
                cout << "   DEPOSITAR DINHEIRO...\n";
                Sleep(500);
                // caso em que o usuario podera depositar valor em sua conta
                depositarDinheiro();
                break;
            
            case 3:
                cout << "   SACAR DINHEIRO...\n";
                Sleep(500);
                // caso em que o usuario podera sacar dinheiro da sua conta
                sacarDinheiro();
                break;
            
            case 4:
                cout << "   TRANSFERIR DINHEIRO...\n";
                Sleep(500);
                // caso em que o usuario podera transferir seu dinheiro para outra conta
                transferirDinheiro();
                break;
            
            case 5:
                cout << "   SAIR...\n"; // Volta para o menu principal
                Sleep(500);
                mainMenu();
                break;

            default:
                cout << "   OPCAO INVALIDA.\n";
                cout << "   Por favor, selecione uma opcao de 1 a 5.\n";
                Sleep(500);
                telaMenu();
                break;   
        }
    }
}

void ecpBank::consultarDinheiro()
{
    system("cls");
    cabecalho();

    if (autenticada)
    {   
        string arquivoNome = "data\\" + login_usuario + ".dat";
        string montante = lerLinha(arquivoNome, 2); //leitura da string saldo dentro do arquivo .dat
        float Montante = stof(montante); //conversao para float ja que se trata de uma informacao do tipo numerico

        stringstream stream;
        stream << fixed << setprecision(2) << Montante; //pegar apenas 2 casas decimais depois do ponto
        montante = stream.str();

        cout << "   ecpBank - Valor disponivel : $" << montante;
        cout << "\n\n";

        system("PAUSE");
        telaMenu();
    }
}

void ecpBank::sacarDinheiro()
{
    system("cls");
    cabecalho();

    if (autenticada)
    {   
        string usuarioEntrada;
        float montante;
        cout << "   Por favor, informe quanto voce deseja sacar: $"; cin >> usuarioEntrada;
        cout << "\n\n";

        if (usuarioEntrada.find_first_not_of("1234567890.") != string::npos ) 
        //Caso usuario digite valor numerico para 'entrada de usuario', o valor e tido com invalido.
        //Este if avalia se o valor numerico digitado e do tipo string.
        //Caso o usuario digite um valor numerico (int/float), o if ira avaliar e ira usar a funcao 'npos'
        //para obrigar que os numeros sejam do tipo string.
        {
            cout << "   Entrada invalida: " << usuarioEntrada << endl;
            cout << "\n\n";
            system("PAUSE");
            sacarDinheiro();
        }

        montante = stof(usuarioEntrada);
        if (montante <= 0)
        {
            cout << "   Por favor, digite apenas valores positivos.\n";
        }

        if (sacar(login_usuario, montante))
        {
            cout << "   Saque feito com sucesso! $" << montante << " da conta.\n";
            Sleep(500);
            telaMenu();
        }
        else
        {
            cout << "   Sem dinheiro suficiente para sacar da conta. Verifique seu saldo e tente novamente!\n";
            system("PAUSE");
            telaMenu();
        }
    }
}

void ecpBank::depositarDinheiro()
{
    system("cls");
    cabecalho();
    if (autenticada)
    {   
        string usuarioEntrada;
        float montante;
        cout << "   Por favor, informe o valor do seu depsito: $"; cin >> usuarioEntrada;
        cout << "\n\n";

        if (usuarioEntrada.find_first_not_of("1234567890.") != string::npos ) 
        ////Caso usuario digite valor numerico para 'entrada de usuario', o valor e tido com invalido.
        //Este if avalia se o valor numerico digitado e do tipo string.
        //Caso o usuario digite um valor numerico (int/float), o if ira avaliar e ira usar a funcao 'npos'
        //para obrigar que os numeros sejam do tipo string.
        {
            cout << "   Entrada invalida!: " << usuarioEntrada << endl;
            cout << "\n\n";
            system("PAUSE");
            depositarDinheiro();
        }

        montante = stof(usuarioEntrada);
        if (montante <= 0)
        {
            cout << "   Por favor, digite apenas valores positivos.\n";
        }

        if (depositar(login_usuario, montante))
        {
            cout << "   Deposito feito com sucesso! $" << montante << " para a conta.\n";
            Sleep(500);
            telaMenu();
        }
    }
}

void ecpBank::transferirDinheiro()
{
    system("cls");
    cabecalho();
    if (autenticada)
    {   
        string enviarValor; //enviar valor para a conta
        string destinatarioValor;
        float montante;
        cout << "   Por favor, informe quanto voce deseja trasnferir: $"; cin >> enviarValor;
        cout << "\n";

        cout << "   Por favor, informe o destinatario da transferencia: "; cin >> destinatarioValor;
        cout << "\n";

        if (enviarValor.find_first_not_of("1234567890.") != string::npos )
        {
            cout << "   Entrada invalida: " << enviarValor << endl;
            cout << "\n\n";
            system("PAUSE");
            transferirDinheiro();
        }

        montante = stof(enviarValor);
        if (montante <= 0)
        {
            cout << "   Por favor, digite apenas valores positivos.\n";
        }

        if (transferir(login_usuario, destinatarioValor, montante))
        {   
            cout << "   Transferencia realizada com sucesso! $" << montante << " da conta para " << destinatarioValor << ".\n";
            Sleep(500);
            telaMenu();
        }
        else
        {
            cout << "   Por favor, consulte seu saldo ou contate o recebedor.\n";
            system("PAUSE");
            telaMenu();
        }
    }
}

bool ecpBank::sacar(const string nomeusuario, float saldo)
{   
    float saldoInicial;
    string arquivoNome = "data\\" + nomeusuario + ".dat";
    saldoInicial = stof(lerLinha(arquivoNome, 2)); // converte string para float

    if (saldo > saldoInicial) // saldo = o que voce deseja sacar. saldoInicial e o que voce tem na conta. 
                              //Condicao em que o saldo e insuficiente
    {   
        return false;
    }
    else
    {   
        string buffer;
        ifstream arquivoAtual(arquivoNome);
        string arquivoAux1 = "data\\buffer.dat";
        ofstream arquivoAux2(arquivoAux1);

        for (int i = 0; i < 2; i++) // Copia nome de usuario e senha
        {
            getline(arquivoAtual, buffer);
            arquivoAux2 << buffer + '\n';
        }

        getline(arquivoAtual, buffer); // Colocar aquivoAtual no aux
        float novoSaldo = saldoInicial - saldo;
        string mostrarSaldo = to_string(novoSaldo);
        arquivoAux2 << mostrarSaldo + '\n';

        arquivoAtual.close();
        arquivoAux2.close();
        remove(arquivoNome.c_str());
        rename("data\\buffer.dat", arquivoNome.c_str());
        
        return true;
    }
}

bool ecpBank::depositar(const string nomeusuario, float saldo)
{
    float saldoInicial;
    string arquivoNome = "data\\" + nomeusuario + ".dat";
    saldoInicial = stof(lerLinha(arquivoNome, 2)); // converte de string para float

    string buffer;
    ifstream arquivoAtual(arquivoNome); // ifstream - funccao responsavel para ler dados de um arquivo (arquivo nome)
    string arquivoAux1 = "data\\buffer.dat";
    ofstream arquivoAux2(arquivoAux1); //ofstream - funccao responsavel por escrever em um arquivo. 
                                     //Neste caso, o arquivo de referencia ao .dat

    for (int i = 0; i < 2; i++) // Copia nome de usuario e senha
    {
        getline(arquivoAtual, buffer);
        arquivoAux2 << buffer + '\n';
    }

    getline(arquivoAtual, buffer); // Coloca saldo dentro de aux
    float novoSaldo = saldoInicial + saldo;
    string mostrarSaldo = to_string(novoSaldo);
    arquivoAux2 << mostrarSaldo + '\n';

    arquivoAtual.close();
    arquivoAux2.close();
    remove(arquivoNome.c_str());
    rename("data\\buffer.dat", arquivoNome.c_str());
    
    return true;
}

bool ecpBank::transferir(const string do_usuario, const string para_usuario, float saldo)
{
    // Funcao responsavel por verificar se o usuario existe
    string arquivoNome = "data\\" + para_usuario + ".dat";
    ifstream isFile;
    isFile.open(arquivoNome);
    if(isFile) // para_usuario Exists
    {   
        isFile.close();
        if (sacar(do_usuario, saldo)) // Se o saque for um sucesso 
        {
            depositar(para_usuario, saldo);
            return true;
        }
    }
    return false;
}

bool ecpBank::criarUsuario(const string nomeusuario, const string senha)
{   
    string arquivoNome = nomeusuario + ".dat";
    string diretorio = "data\\" + arquivoNome;
    
    if (!ifstream(diretorio)) // Se o arquivo nao existir, cria
    {   
        ofstream arquivo(diretorio, ios::out);
        arquivo << nomeusuario << endl; // usuario
        arquivo << senha << endl; // senhaa
        arquivo << 0 << endl; // saldo
        
        arquivo.close();
        return true; // Sucesso.
    }
    else
    {   
        return false; // username already exists. Thus do not create.
    }
}

bool ecpBank::autenticarUsuario(const string tentarUser)
{
    string arquivoNome = tentarUser + ".dat";
    string diretorio = "data\\" + arquivoNome;
    
    if (ifstream(diretorio)) // Caso exista usuario
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ecpBank::autenticarSenha(const string tentarUser, const string tentarPass)
{
    string arquivoNome = tentarUser + ".dat";
    string diretorio = "data\\" + arquivoNome;
    string senha = lerLinha(diretorio, 1);

    if (senha == tentarPass)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

int main ()
{   

    ecpBank app;
    app.mainMenu();
    return 0;
}

