#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
using namespace std;

/*  Daniel de Godoy Carolino -> Projeto: A festa da democracia. */

	struct Candidato {
		string nome;
		int numero;
		int votos;
		Candidato* proximo;
		Candidato(std::string nome, int numero) : nome(nome), numero(numero), proximo(nullptr) {}
	};
	
	struct Eleitor{
		string nome;
		int documento;
		Eleitor* next;
		
	};

	struct Fila{
        Eleitor *inicio, *fim;
        int total;
	};
	
	void inserirCandidato(std::string nome, int numero);
	void removerCandidato(int numero);
	void atualizarCandidato(int numero, std::string novoNome);
	void listarCandidatos();
	void salvarCandidatosEmArquivo(std::string nomeArquivo);
	
  	    void inserirEleitor(string nome, int documento);
    void eleitoresCadastrados();
	void listarEleitores();

int main() {
	setlocale(LC_ALL,"Portuguese");
	
	int op,ac,ae;
	int numero,idade,documento;
	string candidato,eleitor;

	
	do{
		cout<<"\n xxx A FESTA DA DEMOCRACIA FATEC 2023 xxx"<<endl;
		cout<<" 1- AREA DO CANDIDATO "<<endl;
		cout<<" 2- AREA DE ELEITORES "<<endl;
		cout<<" 3- REGISTRO DE VOTOS "<<endl;
		cout<<" 4- APURACAO DOS VOTOS! "<<endl;
		cout<<" 5- ENCERRAR"<<endl;
		cin>>op;	
		
	switch(op){

		case 1:{	/* ####### INICIO ÁREA DOS CANDIDATOS ###################################################################### */
					do{
						cout<<"\n $$$ AREA DO CANDIDATO $$$ "<<endl;
						cout<<" 1- INSERIR CANDIDATO "<<endl;
						cout<<" 2- REMOVER CANDIDATO "<<endl;
						cout<<" 3- LISTAR CANDIDATOS "<<endl;
						cout<<" 4- GRAVAR "<<endl;
						cout<<" 5- Voltar ao menu principal"<<endl;
						cin>>ac;
						
					switch(ac){
						case 1:
							{	
								cout<<"\n Nome do Candidato: ";
								cin>>candidato;
								cout<<" Numero do candidato ";
								cin>>numero;
							    inserirCandidato(candidato,numero);
								break;
							}
						
						case 2:
							{	
								cout<<"\n Candidatos ja Cadastrados: ";
								listarCandidatos();
								cout<<"\n Numero do Candidato a remover: ";
								cin>>numero;
								removerCandidato(numero);
								cout<<"\n Candidatos restantes: ";
								listarCandidatos();
							    break;
							}
						case 3:
							{
								listarCandidatos();
								break;
							}
						case 4:
							{
								salvarCandidatosEmArquivo("CANDIDATOS.txt");
								break;
							}
						default:
							{
								if(ac>5)
								cout<<"\n OPCAO INVALIDA! verifique as opcoes."<<endl;
								cout<<"\n";
							}
				}
				}while(ac!=5);
				break;
		    	}
			

		case 2:{	/* ####### INICIO AREA DOS ELEITORES ###################################################################### */
					
					void listarEleitores() ;
						break;
		    	}
			
/* ####### INICIO AREA DOS VOTOS ###################################################################### */
		case 3:
			{
				break;
			}

/* ####### APURACAO DOS VOTOS! ###################################################################### */
		case 4:
			{
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
        	cout<<"\n----------------------------------------------------------------"<<endl;
            while (atual != nullptr) {
                std::cout << " Nome: " << atual->nome << " Numero: " << atual->numero << std::endl;
                atual = atual->proximo;
            }
            cout<<"----------------------------------------------------------------"<<endl;
        }
    }
	
    void salvarCandidatosEmArquivo(std::string nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);

        if (arquivo.is_open()) {
            Candidato* atual = primeiro;

            while (atual != nullptr) {
                arquivo << atual->nome << " " << atual->numero << std::endl;
                atual = atual->proximo;
            }

            arquivo.close();
            std::cout << "\n Candidatos salvos no arquivo " << nomeArquivo << "." << std::endl;
        } else {
            std::cout << "\n Nao foi possivel abrir o arquivo " << nomeArquivo << " para salvar os candidatos." << std::endl;
        }
    }
    
/* ####### FUNCOES DO CANDIDATO ###################################################################### */
	struct Eleitor* eleitor;
	
    void inserirEleitor(string nome, int documento) 
	    {
	    Eleitor* novoEleitor = new Eleitor();
	    novoEleitor->nome = nome;
	    novoEleitor->documento = documento;
	    novoEleitor->next = eleitor;
	    eleitor = novoEleitor;
	    }
	
	void eleitoresCadastrados()
	{
		inserirEleitor("Daniel",1111111111);
		inserirEleitor("Vanessa",2222222222);
		inserirEleitor("Francisco",3333333333);
		inserirEleitor("Antonico",4444444444);
		inserirEleitor("Anna",5555555555);
		inserirEleitor("Emilia",6666666666);	
	}
	
	void printFila(Fila *fila)
    	{
		Eleitor *aux;
		aux = fila->inicio;
		int total = fila->total;
		cout<<" Eleitores Cadastrados ";
		while(total>0)
		{
			cout << aux->nome<<aux->documento;
			aux = aux->next;
			cout << " ";
			total--;
		}
		
    	}
    	
      void listarEleitores() 
  {
        Eleitor* presente = eleitor;

        if (presente == nullptr) {
            std::cout << "\n Nao ha candidatos registrados." << std::endl;
        } else {
        	cout<<"\n----------------------------------------------------------------"<<endl;
            while (presente != nullptr) {
                std::cout << " Nome: " << presente->nome << " Documento: " << presente->documento << std::endl;
                presente = presente->next;
            }
            cout<<"----------------------------------------------------------------"<<endl;
        }
    }
