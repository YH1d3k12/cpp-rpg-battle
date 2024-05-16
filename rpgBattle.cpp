/*
	Batalhas RPG.
	
	1° - O programa vai gerar um monstro aleátorio para o jogador enfrentar.
	2° - Um monstro derrotado aumenta o nível do jogador, podendo evoluir seus status.
	3° - O jogador vence o jogo se derrotar o dragão.
	4° - As chances do dragão vir aumentam conforme o nível.
*/

// Bibliotecas.
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

class Monster {
	public:
	    // Construtor para inicializar os atributos.
	    Monster(
			string name,
			int maxHp, 
			int currentHp, 
			int atk, 
			int def,
			int dodge, 
			int crit
		) : 
			name_(name),
			maxHp_(maxHp), 
			currentHp_(currentHp), 
			atk_(atk), 
			def_(def),
			dodge_(dodge), 
			crit_(crit) 
		{}

	    // Métodos para acessar os atributos.
	    string getName() const { return name_; }
	    int getMaxHp() const { return maxHp_; }
	    int getCurrentHp() const { return currentHp_; }
	    int getAtk() const { return atk_; }
	    int getDef() const { return def_; }
		int getDodge() const { return dodge_; }
	    int getCrit() const { return crit_; }

		// Ataque básico.
		virtual int attack() {
			int damage = rand() % (3 * atk_) + 1;
			if (rand() % 100 + 1 <= crit_) {
				damage *= 2;
			}
			return damage;
		}

	private:
	    // Atributos.
	    string name_;
	    int maxHp_;
	    int currentHp_;
	    int atk_;
	    int def_;
		int dodge_;
	    int crit_;
};

class Hero : public Monster {
	public:
		Hero(
			string name,
			int maxHp, 
			int currentHp,
			int maxMp,
			int currentMp, 
			int atk,
			int magic, 
			int def,
			int dodge, 
			int crit,
			int level
		) : 
			Monster(name, maxHp, currentHp, atk, def, dodge, crit),
			maxMp_(maxMp),
			currentMp_(currentMp),
			magic_(magic),
			level_(level)
		{}

		int getMaxMp() const { return maxMp_; }
		int getCurrentMp() const { return currentMp_; }
		int getMagic() const { return magic_; }
		int getLevel() const { return level_; }

	private:
		int maxMp_;
		int currentMp_;
		int magic_;
		int level_;
};

// Prototipagem das funções.
int chooseCharacter(string nome, int vida, int ataque, int defesa, int esquiva, int critico, int nivel);
Monster chooseRandomMonster(const vector<Monster>& monsters);

main() {
	system("chcp 65001");
	srand(time(NULL));

	int action, subAction;
	bool validAction;
	
	vector<Monster> monsters = {
		Monster("Goblin", 27, 27, 3, 0, 7, 1),
		Monster("Orc", 65, 65, 9, 1, 1, 3)
	};

	do {
		system("cls");
		cout << "\n\t\t" << "Bem-vindo ao RPG Battle!" << "\n";
		cout << "\n" << "Escolha o seu personagem para começar a jornada!";
		cout << "\n" << "[1] - O Herói do Reino";
		cout << "\n" << "[2] - O Aventureiro";
		cout << "\n" << "[3] - O Plebeu";
		cin >> action;

		switch (action) {
		case 1:
			subAction = chooseCharacter("Herói do Reino", 420, 200, 15, 15, 5, 10, 15, 15);
			validAction = true;
			break;
		case 2:
			subAction = chooseCharacter("Aventureiro", 120, 20, 7, 5, 2, 10, 5, 4);
			validAction = true;
			break;
		case 3:
			subAction = chooseCharacter("Plebeu", 40, 10, 3, 2, 0, 5, 3, 1);
			validAction = true;
			break;
		default:
			validAction = false;
			cout << "\n" << "Opção inválida!";
			cout << "\n" << "Escolha novamente..." << "\n";
			system("pause");
			break;
		}
	} while (!validAction || subAction != 1);

	// Monster randomMonster = chooseRandomMonster(monsters);
}

// Função para escolher o personagem.
int chooseCharacter(string name, int hp, int mp, int atk, int magic, int def, int dodge, int crit, int lvl) {
	int action;
	bool validAction;

	do {
		system("cls");
		cout << "\n" << "Você escolheu o " << name << "!";
		cout << "\n" << "Atributos";
		cout << "\n" << "Vida: " << hp;
		cout << "\n" << "Mana: " << mp;
		cout << "\n" << "Ataque: " << atk;
		cout << "\n" << "Magia: " << magic;
		cout << "\n" << "Defesa: " << def;
		cout << "\n" << "Esquiva: " << dodge << "%";
		cout << "\n" << "Crítico: " << crit << "%";
		cout << "\n" << "Nível: " << lvl;

		cout << "\n\n" << "Deseja realmente escolher este personagem?";
		cout << "\n" << "[1] - Sim";
		cout << "\n" << "[2] - Não";
		cin >> action;

		if (action == 1) {
			validAction = true;
			
		} 
		else if (action == 2) {
			validAction = true;
		}
		else
		{
			validAction = false;
			cout << "\n" << "Opção inválida!";
			cout << "\n" << "Escolha novamente..." << "\n";
			system("pause");
		}
	} while (!validAction);

	return action;
}


// & monsters, indica que o vetor `monsters` é passado por referencia a função.
// Recebendo o seu endereço da memória.
Monster chooseRandomMonster(const vector<Monster>& monsters) {
	// Gera um índice aleatório diferente de 0.
    int index = rand() % monsters.size() + 1;

	// Se o índice for maior que o tamanho do vetor, decrementa, retornando o último monstro.
	if (index > monsters.size()) {
		index--;
	}

    return monsters[index];
}