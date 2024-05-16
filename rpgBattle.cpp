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

		virtual int attack() {
			int damage = rand() % (3 * atk_) + 1;
			if (rand() % 100 + 1 <= crit_) {
				damage *= 2;
			}
			return damage;
		}

    	void takeDamage(int damage) {
			damage -= def_;
			if (damage < 0) {
				damage = 0;
			}

    	    currentHp_ -= damage;
    	    if (currentHp_ < 0) {
    	        currentHp_ = 0;
    	    }
    	}

    	void heal(int amount) {
    	    currentHp_ += amount;
    	    if (currentHp_ > maxHp_) {
    	        currentHp_ = maxHp_;
    	    }
    	}

		void increaseMaxHp(int amount) { maxHp_ += amount; }
    	void increaseAtk(int amount) { atk_ += amount; }
    	void increaseDef(int amount) { def_ += amount; }
    	void increaseDodge(int amount) { dodge_ += amount; }
    	void increaseCrit(int amount) { crit_ += amount; }

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

		// Métodos para acessar os atributos.
		int getMaxMp() const { return maxMp_; }
		int getCurrentMp() const { return currentMp_; }
		int getMagic() const { return magic_; }
		int getLevel() const { return level_; }

		void spendMp(int amount) {
			currentMp_ -= amount;

    	    if (currentMp_ < 0) {
    	        currentMp_ = 0;
    	    }
		}

		void recoverMp(int amount) {
    	    currentMp_ += amount;
    	    if (currentMp_ > maxMp_) {
    	        currentMp_ = maxMp_;
    	    }
    	}

		int secondWind() {
			int heal = rand() % (10 + level_);
			return heal;
		}

		int healingMagic() {
			int heal = rand() % (7 * (magic_ + level_)) + 1;
			if (rand() % 100 + 1 <= this->getCrit()) {
				heal *= 2;
			}
			return heal;
		}

		int destructiveMagic() {
			int damage = rand() % (7 * (magic_ + level_)) + 1;
			if (rand() % 100 + 1 <= this->getCrit()) {
				damage *= 2;
			}
			return damage;
		}

		void increaseMaxMp(int amount) { maxMp_ += amount; }
    	void increaseMagic(int amount) { magic_ += amount; }

	private:
		int maxMp_;
		int currentMp_;
		int magic_;
		int level_;
};


// Prototipagem das funções.
int selectCharacter(const vector<Hero>& characters);
bool confirmCharacter(string name, int hp, int mp, int atk, int magic, int def, int dodge, int crit, int lvl);
bool combatEncounter(Hero chosenCharacter, Monster chosenMonster);
Monster chooseRandomMonster(const vector<Monster>& monsters, Hero chosenCharacter);


main() {
	system("chcp 65001");
	srand(time(NULL));
	
	// Lista de personagens.
	vector<Hero> characters = {
        Hero("Herói do Reino", 420, 420, 200, 200, 15, 15, 5, 10, 15, 15),
        Hero("Aventureiro", 120, 120, 20, 20, 7, 5, 2, 10, 5, 4),
        Hero("Plebeu", 40, 40, 10, 10, 3, 2, 0, 5, 3, 1)
    };
	Hero chosenCharacter = characters[0];

	// Lista de monstros.
	vector<Monster> monsters = {
		Monster("Goblin", 27, 27, 3, 0, 7, 1),
		Monster("Orc", 65, 65, 9, 1, 1, 3),
		Monster("Dragão Vermelho", 650, 650, 20, 10, 5, 5)
	};
	Monster chosenMonster = monsters[0];

	// Programa começa selecionando o personagem.
	chosenCharacter = characters[selectCharacter(characters)];

	bool victory;

	// Continua enquanto o jogador não derrotar o Dragão Vermelho!
	do {
		victory = false;
		// Jogador luta contra um monstro aleatório.
		chosenMonster = chooseRandomMonster(monsters, chosenCharacter);
		victory = combatEncounter(chosenCharacter, chosenMonster);

		// Se triunfante, o personagem sobe de nível e evolui um de seus atributos.
		system("cls");
		if (victory) {
			cout << "\n" << "Parabéns! Você derrotou " << chosenMonster.getName();
			cout << "\n" << "Você subiu de nível!" << "\n";
			system("pause");
		}
		else {
			cout << "\n" << "Gameover!" << "\n";
			system("pause");
		}

		// Se o Dragão Vermelho for derrotado o personagem vence o jogo.
	} while (true);	
}


int selectCharacter(const vector<Hero>& characters) {
	int action;

	do {
		system("cls");
		cout << "\n\t\t" << "Bem-vindo ao RPG Battle!" << "\n";
		cout << "\n" << "Escolha o seu personagem para começar a jornada!";

		for (int i = 0; i < characters.size(); i++) {
			cout << "\n" << "[" << i + 1 << "] - " << characters[i].getName();
		}
		cout << "\n";
		cin >> action;

		if (action >= 1 && action <= characters.size()) {
			int selectedCharacter = action - 1;
			bool confirmed = false;

			confirmed = confirmCharacter(
                characters[selectedCharacter].getName(),
                characters[selectedCharacter].getMaxHp(),
                characters[selectedCharacter].getMaxMp(),
                characters[selectedCharacter].getAtk(),
                characters[selectedCharacter].getMagic(),
                characters[selectedCharacter].getDef(),
                characters[selectedCharacter].getDodge(),
                characters[selectedCharacter].getCrit(),
                characters[selectedCharacter].getLevel()
            );

			if (confirmed) {
				return selectedCharacter;
			}
		} 
		else {
			cout << "\n" << "Opção inválida!";
			cout << "\n" << "Escolha novamente..." << "\n";
			system("pause");
		}
	} while (true);
}

bool confirmCharacter(string name, int hp, int mp, int atk, int magic, int def, int dodge, int crit, int lvl) {
	int action;

	do {
		system("cls");
		cout << "\n\t\t" << "Você escolheu o " << name << "!";
		cout << "\n\n\n" << "Atributos";
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
		cout << "\n" << "[2] - Não" << "\n";
		cin >> action;

		if (action == 1) {
			return true;
		} 
		else if (action == 2) {
			return false;
		}
		else
		{
			cout << "\n" << "Opção inválida!" << "\n";
			system("pause");
		}
	} while (action != 1 || action != 2);

	return false;
}

// & monsters, indica que o vetor `monsters` é passado por referencia a função.
// Recebendo o seu endereço da memória.
Monster chooseRandomMonster(const vector<Monster>& monsters, Hero chosenCharacter) {
	// Chance do dragão aparecer aumenta conforme o nível do jogador.
	if (rand() % 100 + 1 <= chosenCharacter.getLevel()) {
		return monsters[monsters.size() - 1];
	}
	
	// Se a verificação anterior não for sucedida retorne outro monstro aleatório.
    int index = rand() % monsters.size();
    return monsters[index];
}

bool combatEncounter(Hero chosenCharacter, Monster chosenMonster) {
	int action, result;
	bool validAction;

	do {
		system("cls");
		cout << "\n\t\t" << "Batalha contra " << chosenMonster.getName() << "!";

		cout << "\n\n" << "Lvl " << chosenCharacter.getLevel() << " " << chosenCharacter.getName();
		cout << "\n" << "HP: " << chosenCharacter.getCurrentHp() << "/" << chosenCharacter.getMaxHp();
		cout << "\n" << "MP: " << chosenCharacter.getCurrentMp() << "/" << chosenCharacter.getMaxMp();

		cout << "\n\n\n\t\t" << chosenMonster.getName();
		cout << "\n" << "Vida: " << chosenMonster.getCurrentHp() << "/" << chosenMonster.getMaxHp();
		do {
			validAction = false;
			cout << "\n" << "Escolha a ação desejada:";
			cout << "\n" << "[1] - Atacar";
			cout << "\n" << "[2] - Cura (7mp)";
			cout << "\n" << "[3] - Magia Destrutiva (12mp)";
			cout << "\n" << "[4] - Folego (Recupera um pouco de HP e MP)" << "\n";
			cin >> action;

			system("cls");
			switch (action) {
			case 1:
				result = chosenCharacter.attack();
				cout << "\n" << "Você ataca o " << chosenMonster.getName() << " causando " << result << " de dano!";
				chosenMonster.takeDamage(result);
				validAction = true;
				break;
			case 2:
				if (chosenCharacter.getCurrentMp() < 7) {
					cout << "\n" << "Mana insuficiente!" << "\n" << "Escolha outra ação!";
					break;
				}
				result = chosenCharacter.healingMagic();
				chosenCharacter.spendMp(7);
				cout << "\n" << "Você se cura, restaurando " << result << " pontos de vida!";
				chosenCharacter.heal(result);
				validAction = true;
				break;
			case 3:
				if (chosenCharacter.getCurrentMp() < 12) {
					cout << "\n" << "Mana insuficiente!" << "\n" << "Escolha outra ação!";
					break;
				}
				result = chosenCharacter.destructiveMagic();
				chosenCharacter.spendMp(12);
				cout << "\n" << "Você usa magia de destruição contra o " << chosenMonster.getName() << " causando " << result << " de dano!";
				chosenMonster.takeDamage(result);
				validAction = true;
				break;
			default:
				cout << "\n" << "Você recupera seu folego";

				result = chosenCharacter.secondWind();
				chosenCharacter.heal(result);
				cout << "\n" << "Resturado " << result << " pontos de vida!";

				result /= 2;
				chosenCharacter.recoverMp(result);
				cout << "\n" << "Restaurado " << result << " pontos de mana!";
				validAction = true;
				break;
			}
		} while (!validAction);
		cout << "\n";
		system("pause");
		system("cls");

		if (chosenMonster.getCurrentHp() > 0) {
			result = chosenMonster.attack();
			chosenCharacter.takeDamage(result);
			cout << "\n" << "O " << chosenMonster.getName() << " te ataca, causando " << result << " pontos de dano!" << "\n";
			system("pause");
		} 
	} while (chosenCharacter.getCurrentHp() > 0 && chosenMonster.getCurrentHp() > 0);

	if (chosenCharacter.getCurrentHp() <= 0) {
		return false;
	}
	return true;
}