#include <iostream>
#include <locale.h>
#include <fstream>
const int tam = 5; 
using namespace std;

/*  Daniel de Godoy Carolino -> Projeto: A festa da democracia. */

	struct Candidato {
		string nome;
		int numero;
		int votos;
		Candidato* proximo;
		Candidato(std::string nome, int numero) : nome(nome), numero(numero), proximo(nullptr) {}
	};
	
	struct Eleitor {
	    std::string nome;
	    std::string documento;
	};
	
	struct Fila {
	    Eleitor secao[tam];
	    int inicio;
	    int fim;
	};
	
	void inserirCandidato(std::string nome, int numero);
	void removerCandidato(int numero);
	void atualizarCandidato(int numero, std::string novoNome);
	void listarCandidatos();
	void salvarCandidatosEmArquivo(std::string nomeArquivo);
	
	void iniciarFila(Fila& fila);
	Eleitor inicio(const Fila& fila);
	void inserirFila(Fila& fila, const std::string& nome, const std::string& documento);
	void registrandoEleitor();
	void verificaElementoNaFila(const std::string& documento);
	void mostrarResultados();
	void salvarResultadoEmArquivo(std::string nomeArquivo);
		void exibirEleitor();

int main() {
	setlocale(LC_ALL,"Portuguese");
	
	int op,ac,ae;
	int numero,numeroCandidato;
	string candidato;
	string nome,documento;
	registrandoEleitor();

	
	do{
		cout<<"\n xxx A FESTA DA DEMOCRACIA FATEC 2023 xxx"<<endl;
		cout<<" 1- AREA DO CANDIDATO "<<endl;
		cout<<" 2- AREA DE ELEITORES "<<endl;
		cout<<" 3- REGISTRO DE VOTOS "<<endl;
		cout<<" 4- APURACAO DOS VOTOS! "<<endl;
		cout<<" 5- ENCERRAR"<<endl;
		cin>>op;	
		
	switch(op){

		case 1:{	/* ####### INICIO AREA DOS CANDIDATOS ###################################################################### */
					do{
						cout<<"\n $$$ AREA DO CANDIDATO $$$ "<<endl;
						cout<<" 1- INSERIR CANDIDATO "<<endl;
						cout<<" 2- REMOVER CANDIDATO "<<endl;
						cout<<" 3- LISTAR CANDIDATOS "<<endl;
						cout<<" 4- Voltar ao menu principal"<<endl;
						cin>>ac;
						
					switch(ac){
						case 1:{	
								cout<<"\n Nome do Candidato: ";
								cin>>candidato;
								cout<<" Numero do candidato ";
								cin>>numero;
							    inserirCandidato(candidato,numero);
							    salvarCandidatosEmArquivo("CANDIDATOS.txt");
								break;
							}
						
						case 2:{	
								cout<<"\n Candidatos ja Cadastrados: ";
								listarCandidatos();
								cout<<"\n Numero do Candidato a remover: ";
								cin>>numero;
								removerCandidato(numero);
								cout<<"\n Candidatos restantes: ";
								listarCandidatos();
								salvarCandidatosEmArquivo("CANDIDATOS.txt");
							    break;
							}
						case 3:{
								listarCandidatos();
								break;
							}
						default:{
								if(ac>4)
								cout<<"\n OPCAO INVALIDA! verifique as opcoes."<<endl;
								cout<<"\n";
							}
				}
				}while(ac!=4);
				break;
		    	}
			
		case 2:{	/* ####### INICIO AREA DOS ELEITORES ###################################################################### */
					exibirEleitor();
					break;		
		    	}
			
		case 3:{	/* ####### INICIO AREA DOS VOTOS ###################################################################### */
					cout<<"	Documento do eleitor ";
					cin>>documento;
					verificaElementoNaFila(documento);
					break;
			}


		case 4:{	/* ####### APURACAO DOS VOTOS! ###################################################################### */
				mostrarResultados();
				salvarResultadoEmArquivo("GANHADOR.txt");
				break;
			}
			
		default:
			{
				if(op>5)
				cout<<"\n OPCAO INVALIDA! verifique as opcoes."<<endl;
				cout<<"\n";
			}
	}
	}while(op!=5);
	
			cout<<"\n OBRIGADO ATE A PROXIMA ELEICAO!";
	
		return 0;
	}
	
	
/* ####### FUNCOES DO CANDIDATO ###################################################################### */
	struct Candidato* primeiro;

    void inserirCandidato(std::string nome, int numero) {
        Candidato* novoCandidato = new Candidato(nome, numero);
        novoCandidato->proximo = primeiro;
        primeiro = novoCandidato;
    }

    void removerCandidato(int numero) {
        Candidato* atual = primeiro;
        Candidato* anterior = nullptr;

        while (atual != nullptr) {
            if (atual->numero == numero) {
                if (anterior == nullptr) {
                    primeiro = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                delete atual;
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }

  void listarCandidatos() 
  {
        Candidato* atual = primeiro;

        if (atual == nullptr) {
            std::cout << "\n Nao ha candidatos registrados." << std::endl;
        } else {
        	cout<<"--CANDIDATOS------------------"<<endl;
            while (atual != nullptr) {
                std::cout << " Nome: " << atual->nome << " Numero: " << atual->numero << std::endl;
                atual = atual->proximo;
            }
            cout<<"------------------------------"<<endl;
        }
    }
	
    void salvarCandidatosEmArquivo(std::string nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);

        if (arquivo.is_open()) {
            Candidato* atual = primeiro;
			arquivo <<" Candidatos cadastardos: " << std::endl;
            while (atual != nullptr) {
                arquivo <<" Nome: "<< atual->nome << " , Numero: " << atual->numero << std::endl;
                atual = atual->proximo;
            }

            arquivo.close();
            std::cout << "\n Candidatos salvos no arquivo " << nomeArquivo << "." << std::endl;
        } else {
            std::cout << "\n Erro ao criar o arquivo!" << nomeArquivo << "." << std::endl;
        }
    }
    
/* ####### FUNCOES DO ELEITOR ###################################################################### */

	void iniciarFila(Fila& fila){
		fila.inicio = -1;
	    fila.fim = -1;
	}
	
	bool estaVazia(const Fila& fila){
	    return (fila.inicio == -1 && fila.fim == -1);
	}
	
	bool estaCheia(const Fila& fila){
	    return (fila.fim == tam - 1);
	}
	
	void inserirFila(Fila& fila, const std::string& nome, const std::string& documento) {
	    if (estaCheia(fila)) {
	        std::cout << "Erro: a fila está cheia!" << std::endl;
	        return;
	    }
	    Eleitor novoEleitor;
	    novoEleitor.nome = nome;
	    novoEleitor.documento = documento;
	    if (estaVazia(fila)) {
	        fila.inicio = 0;
	    }
	    fila.fim++;
	    fila.secao[fila.fim] = novoEleitor;
	}
	
	void desinserirFila(Fila& fila) {
	    if (estaVazia(fila)) {
	        std::cout << "Erro: a fila está vazia!" << std::endl;
	        return;
	    }
	    if (fila.inicio == fila.fim) {
	        fila.inicio = -1;
	        fila.fim = -1;
	    } else {
	        fila.inicio++;
	    }
	}
		Eleitor inicio(const Fila& fila) {
	    if (estaVazia(fila)) {
	        std::cout << "Erro: a fila está vazia!" << std::endl;
	        return Eleitor();
	    }
	    return fila.secao[fila.inicio];
	}
	
	void criarArquivoFila(const Fila& fila, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao criar o arquivo!" << std::endl;
        return;
    }
    for (int i = fila.inicio; i <= fila.fim; i++) {
        arquivo << "Nome: " << fila.secao[i].nome << ", Documento: " << fila.secao[i].documento << std::endl;
    }
    arquivo.close();
    std::cout << "\n Eleitores salvos no arquivo " << nomeArquivo << "." << std::endl;
	}
	
	Fila filaEleitor;
	void registrandoEleitor(){
	    iniciarFila(filaEleitor);
	    cout<<" Eleitores cadastrados: "<<endl;
	    inserirFila(filaEleitor, "Joao", "123456");
	    inserirFila(filaEleitor, "Maria", "789012");
	    inserirFila(filaEleitor, "Pedro", "345678");
	    inserirFila(filaEleitor, "Paulo", "987654");
	    inserirFila(filaEleitor, "Ana", "321045");
	    criarArquivoFila(filaEleitor,"ELEITORES.txt");
	}
	
	void exibirEleitor(){
		for (int i = filaEleitor.inicio; i <= filaEleitor.fim; i++) {
        std::cout << "Nome: " << filaEleitor.secao[i].nome << ", Documento: " << filaEleitor.secao[i].documento << std::endl;
	    }
	}

/* ####### FUNCOES VOTACAO, APURAÇÃO E RESULTADO ###################################################################### */
	void votar(int numeroCandidato) {
    Candidato* candidatoAtual = primeiro;
    while (candidatoAtual != nullptr) {
        if (candidatoAtual->numero == numeroCandidato) {
            candidatoAtual->votos++;
            cout << "Voto registrado com sucesso!\n";
            return;
        }
        candidatoAtual = candidatoAtual->proximo;
    }
    cout << "Candidato não encontrado. Voto não registrado.\n";
	};
	
	void verificaElementoNaFila(const std::string& documento) {
	    for (int i = filaEleitor.inicio; i <= filaEleitor.fim; i++) {
	        if (filaEleitor.secao[i].documento == documento) {
	        	cout<<"\n Voce esta apto a votar"<<endl;
				listarCandidatos();
				int voto;
				cout<<"\n Qual o numero do seu candidato? ";
				cin>>voto;
				votar(voto);
				break;
	        }else{
	        	 cout<<"\n Voce nao esta apto a votar"; 
	        	 break;
			}
	    }
    }
    
    void mostrarResultados() {
     if (primeiro == nullptr) {
        std::cout << "A lista de candidatos está vazia." << std::endl;
        return;
    }

    const Candidato* candidatoMaisVotado = primeiro;
    int maiorNumeroVotos = candidatoMaisVotado->votos;

    const Candidato* candidatoAtual = primeiro->proximo;
    while (candidatoAtual != nullptr) {
        if (candidatoAtual->votos > maiorNumeroVotos) {
            candidatoMaisVotado = candidatoAtual;
            maiorNumeroVotos = candidatoAtual->votos;
        }
        candidatoAtual = candidatoAtual->proximo;
    }

    std::cout << "\n Candidato com mais votos: " << candidatoMaisVotado->nome << std::endl;
    std::cout << " Número de votos: " << candidatoMaisVotado->votos << std::endl;
}
	   
	void salvarResultadoEmArquivo(std::string nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);
		
        if (arquivo.is_open()) {
           Candidato* atual = primeiro;
			
			arquivo <<"Resultado das eleicoes: "<<std::endl;
	    while (primeiro != nullptr) {
	        arquivo <<"Nome: "<< primeiro->nome << " , Numero: " << primeiro->numero << " Votos: "<< primeiro->votos << std::endl;
	        primeiro = primeiro->proximo;
	    }
	    	
            arquivo.close();
            std::cout << "\n Candidatos salvos no arquivo " << nomeArquivo << "." << std::endl;
        } else {
            std::cout << "\n Erro ao criar o arquivo!" << nomeArquivo << "." << std::endl;
        }
    }
	
    	
  
