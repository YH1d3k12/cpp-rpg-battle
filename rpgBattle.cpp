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
	    // Construtor da classe.
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
			int damage = rand() % (5 * atk_) + atk_;
			if (rand() % 100 + 1 <= crit_) {
				damage *= 2;
			}
			return damage;
		}

    	void takeDamage(int damage) {
			damage -= def_ * 3;
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
		// Construtor da classe.
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
			int heal = rand() % (10 + level_) + level_;
			return heal;
		}

		int healingMagic() {
			int heal = rand() % (15 * (magic_ + level_)) + magic_ + level_;
			if (rand() % 100 + 1 <= this->getCrit()) {
				heal *= 2;
			}
			return heal;
		}

		int destructiveMagic() {
			int damage = rand() % (12 * (magic_ + level_)) + magic_ + level_;
			if (rand() % 100 + 1 <= this->getCrit()) {
				damage *= 2;
			}
			return damage;
		}

		void increaseMaxMp(int amount) { maxMp_ += amount; }
    	void increaseMagic(int amount) { magic_ += amount; }
		void increaseLevel(int amount) { level_ += amount; }

	private:
		// Atributos.
		int maxMp_;
		int currentMp_;
		int magic_;
		int level_;
};


// Prototipagem das funções.
int selectCharacter(const vector<Hero>& characters);
void showCharacter(string name, int hp, int mp, int atk, int magic, int def, int dodge, int crit, int lvl);
bool combatEncounter(Hero chosenCharacter, Monster chosenMonster);
Hero levelUp(Hero chosenCharacter);
Monster chooseRandomMonster(const vector<Monster>& monsters, Hero chosenCharacter);


main() {
	system("chcp 65001");
	srand(time(NULL));
	
	// Lista de personagens.
	vector<Hero> characters = {
		// Fácil.
        Hero("Herói do Reino", 420, 420, 200, 200, 25, 25, 10, 10, 15, 15),
		// Médio.
        Hero("Guerreiro", 145, 145, 20, 20, 10, 3, 4, 15, 5, 3),
		Hero("Mago", 82, 82, 60, 60, 5, 15, 1, 10, 5, 3),
		Hero("Ladino", 92, 92, 12, 12, 12, 1, 0, 30, 20, 3),
		// Difícil.
        Hero("Plebeu", 65, 65, 15, 15, 5, 3, 1, 5, 3, 1)
    };
	Hero chosenCharacter = characters[0];

	/*
		Lista de monstros.
		25% de chance de aparecer goblin.
		10% de chance de aparecer ogro.
		20% de chance de aparecer esqueleto.
		15% de chance de aparecer orc.
		10% de chance de aparecer troll.
		15% de chance de aparecer lobo.
		5% de chance de aparecer dragão vermelho.
	*/ 

	vector<Monster> monsters = {
		Monster("Goblin", 27, 27, 3, 0, 7, 3),
		Monster("Lobo", 40, 40, 5, 0, 15, 3),
		Monster("Ogro", 240, 240, 15, 2, 0, 3),
		Monster("Esqueleto", 21, 21, 9, 1, 2, 5),
		Monster("Goblin", 27, 27, 3, 0, 7, 3),
		Monster("Orc", 65, 65, 8, 3, 5, 5),
		Monster("Goblin", 27, 27, 3, 0, 7, 3),
		Monster("Esqueleto", 21, 21, 9, 1, 2, 5),
		Monster("Troll", 165, 165, 9, 5, 0, 3),
		Monster("Lobo", 40, 40, 5, 0, 15, 3),
		Monster("Orc", 65, 65, 8, 3, 5, 5),
		Monster("Goblin", 27, 27, 3, 0, 7, 3),
		Monster("Esqueleto", 21, 21, 9, 1, 2, 5),
		Monster("Ogro", 240, 240, 15, 2, 0, 3),
		Monster("Lobo", 40, 40, 5, 0, 15, 3),
		Monster("Esqueleto", 21, 21, 9, 1, 2, 5),
		Monster("Troll", 165, 165, 9, 5, 0, 3),
		Monster("Orc", 65, 65, 8, 3, 5, 5),
		Monster("Goblin", 27, 27, 3, 0, 7, 3),
		Monster("Dragão Vermelho", 650, 650, 20, 10, 5, 5)
	};
	Monster chosenMonster = monsters[0];

	// Programa começa selecionando o personagem.
	chosenCharacter = characters[selectCharacter(characters)];

	// Continua enquanto o jogador não derrotar o Dragão Vermelho!
	bool victory;
	do {
		victory = false;
		// Jogador luta contra um monstro aleatório.
		chosenMonster = chooseRandomMonster(monsters, chosenCharacter);
		victory = combatEncounter(chosenCharacter, chosenMonster);

		system("cls");
		// Se o Dragão Vermelho for derrotado o jogador vence o jogo.
		if (victory && chosenMonster.getName() == "Dragão Vermelho") {
			cout << "\n" << "Parabéns! Você derrotou o Dragão Vermelho!";
			cout << "\n" << "Você venceu o jogo!";
			cout << "\n\n" << "Seus atributos finais";
			showCharacter(
				chosenCharacter.getName(),
				chosenCharacter.getMaxHp(),
				chosenCharacter.getMaxMp(),
				chosenCharacter.getAtk(),
				chosenCharacter.getMagic(),
				chosenCharacter.getDef(),
				chosenCharacter.getDodge(),
				chosenCharacter.getCrit(),
				chosenCharacter.getLevel()
			);
			cout << "\n";
			system("pause");
			break;
		}
		else if (victory) {
			cout << "\n" << "Parabéns! Você derrotou " << chosenMonster.getName();
			cout << "\n" << "Você subiu de nível!" << "\n";
			system("pause");
			chosenCharacter = levelUp(chosenCharacter);
		}
		else {
			cout << "\n" << "Você foi derrotado por " << chosenMonster.getName() << "!";
			cout << "\n" << "Gameover!" << "\n";
			system("pause");
			break;
		}
	} while (true);	
}


int selectCharacter(const vector<Hero>& characters) {
	int action, confirmAction, selectedCharacter;
	bool confirmed = false;

	do {
		system("cls");
		cout << "\n\t\t" << "Bem-vindo ao RPG Battle!" << "\n";
		cout << "\n" << "Escolha o seu personagem para começar a jornada!";

		// Dinâmicamente lista os personagens disponiveis.
		for (int i = 0; i < characters.size(); i++) {
			cout << "\n" << "[" << i + 1 << "] - " << characters[i].getName();
		}
		cout << "\n";
		cin >> action;

		// Se a ação estiver no alcance, vai para a etapa de confirmação.
		if (action >= 1 && action <= characters.size()) {
			selectedCharacter = action - 1;
			
			// Demonstra os status do personagem para confirma sua escolha.
			do {
				system("cls");
				cout << "\n\t\t" << "Você escolheu o " << characters[selectedCharacter].getName() << "!";
				showCharacter(
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

				cout << "\n\n" << "Deseja realmente escolher este personagem?";
				cout << "\n" << "[1] - Sim";
				cout << "\n" << "[2] - Não" << "\n";
				cin >> confirmAction;

				// A pergunta continua até o usuário fornecer uma ação válida.
				if (confirmAction == 1) {
					confirmed = true;
				} 
				else if (confirmAction == 2) {
					confirmed = false;
				}
				else {
					cout << "\n" << "Opção inválida!" << "\n";
					system("pause");
				}
			} while (confirmAction != 1 && confirmAction != 2);
		} 
		else {
			cout << "\n" << "Opção inválida!";
			cout << "\n" << "Escolha novamente..." << "\n";
			system("pause");
		}
	} while (!confirmed);

	return selectedCharacter;
}

void showCharacter(string name, int hp, int mp, int atk, int magic, int def, int dodge, int crit, int lvl) {
		cout << "\n\n\n" << "Atributos";
		cout << "\n" << "Vida: " << hp;
		cout << "\n" << "Mana: " << mp;
		cout << "\n" << "Ataque: " << atk;
		cout << "\n" << "Magia: " << magic;
		cout << "\n" << "Defesa: " << def;
		cout << "\n" << "Esquiva: " << dodge << "%";
		cout << "\n" << "Crítico: " << crit << "%";
		cout << "\n" << "Nível: " << lvl;
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
		do {
			system("cls");
			cout << "\n\t\t" << "Batalha contra " << chosenMonster.getName() << "!";

			cout << "\n\n" << "Lvl " << chosenCharacter.getLevel() << " " << chosenCharacter.getName();
			cout << "\n" << "HP: " << chosenCharacter.getCurrentHp() << "/" << chosenCharacter.getMaxHp();
			cout << "\n" << "MP: " << chosenCharacter.getCurrentMp() << "/" << chosenCharacter.getMaxMp();

			cout << "\n\n\n\t\t" << chosenMonster.getName();
			cout << "\n" << "Vida: " << chosenMonster.getCurrentHp() << "/" << chosenMonster.getMaxHp();

			validAction = false;
			cout << "\n\n\n" << "--------------------------------";
			cout << "\n" << "Sua vez de agir!";
			cout << "\n" << "[1] - Atacar";
			cout << "\n" << "[2] - Cura (7mp)";
			cout << "\n" << "[3] - Magia Destrutiva (12mp)";
			cout << "\n" << "[4] - Folego (Recupera um pouco de HP e MP)" << "\n";
			cin >> action;

			system("cls");
			switch (action) {
			case 1:
				result = chosenCharacter.attack();
				if (rand() % 100 + 1 <= chosenMonster.getDodge()) {
					cout << "\n" << chosenMonster.getName() << " esquivou do seu ataque!" << "\n";
				}
				else {
					cout << "\n" << "Você ataca o " << chosenMonster.getName() << " causando " << result << " de dano!";
					chosenMonster.takeDamage(result);
				}
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
				if (rand() % 100 + 1 <= chosenMonster.getDodge()) {
					cout << "\n" << chosenMonster.getName() << " esquivou do seu ataque!" << "\n";
				}
				else {
					cout << "\n" << "Você usa magia de destruição contra o " << chosenMonster.getName() << " causando " << result << " de dano!";
					chosenMonster.takeDamage(result);
				}
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
			
			if (rand() % 100 + 1 <= chosenCharacter.getDodge()) {
				cout << "\n" << "Você esquivou do ataque do " << chosenMonster.getName() << "!" << "\n";
			} 
			else {
				chosenCharacter.takeDamage(result);
				cout << "\n" << "O " << chosenMonster.getName() << " te ataca, causando " << result << " pontos de dano!" << "\n";
			}
			system("pause");
		} 

	} while (chosenCharacter.getCurrentHp() > 0 && chosenMonster.getCurrentHp() > 0);

	if (chosenCharacter.getCurrentHp() <= 0) {
		return false;
	}
	return true;
}

Hero levelUp(Hero chosenCharacter) {
	int action, result;
	bool validAction = false;

	do {
		system("cls");
		// Demonstra os status do personagem.
		cout << "\n\t\t" << "Lvl " << chosenCharacter.getLevel() << " " << chosenCharacter.getName();
		cout << "\n\n" << "Seus atributos atuais";
		showCharacter(
			chosenCharacter.getName(),
			chosenCharacter.getMaxHp(),
			chosenCharacter.getMaxMp(),
			chosenCharacter.getAtk(),
			chosenCharacter.getMagic(),
			chosenCharacter.getDef(),
			chosenCharacter.getDodge(),
			chosenCharacter.getCrit(),
			chosenCharacter.getLevel()
		);

		cout << "\n\n" << "Qual atributo deseja aumentar?";
		cout << "\n" << "[1] - Aumentar HP";
		cout << "\n" << "[2] - Aumentar MP";
		cout << "\n" << "[3] - Aumentar Ataque";
		cout << "\n" << "[4] - Aumentar Magia";
		cout << "\n" << "[5] - Aumentar Defesa";
		cout << "\n" << "[6] - Aumentar Esquiva";
		cout << "\n" << "[7] - Aumentar Critico" << "\n";
		cin >> action;

		switch (action) {
			case 1:
				result = (chosenCharacter.getMaxHp() / 5) + 21;
				chosenCharacter.increaseMaxHp(result);
				chosenCharacter.heal(result);
				cout << "\n" << "Sua vida máxima aumentou em " << result << "\n";
				validAction = true;
				break;
			case 2:
				result = (chosenCharacter.getMaxMp() / 3) + 7;
				chosenCharacter.increaseMaxMp(result);
				chosenCharacter.recoverMp(result);
				cout << "\n" << "Sua mana máxima aumentou em " << result << "\n";
				validAction = true;
				break;
			case 3:
				result = (chosenCharacter.getAtk() / 9) + 3;
				chosenCharacter.increaseAtk(result);
				cout << "\n" << "Seu ataque aumentou em " << result << "\n";
				validAction = true;
				break;
			case 4:
				result = (chosenCharacter.getMagic() / 9) + 3;
				chosenCharacter.increaseMagic(result);
				cout << "\n" << "Sua magia aumentou em " << result << "\n";
				validAction = true;
				break;
			case 5:
				result = (chosenCharacter.getDef() / 9) + 2;
				chosenCharacter.increaseDef(result);
				cout << "\n" << "Sua defesa aumentou em " << result << "\n";
				validAction = true;
				break;
			case 6:
				result = (chosenCharacter.getDodge() / 9) + 2;
				chosenCharacter.increaseDodge(result);
				cout << "\n" << "Sua esquiva aumentou em " << result << "\n";
				validAction = true;
				break;
			case 7:
				result = (chosenCharacter.getCrit() / 9) + 2;
				chosenCharacter.increaseCrit(result);
				cout << "\n" << "Sua chance de acerto crítico aumentou em " << result << "\n";
				validAction = true;
				break;
			default:
				cout << "\n" << "Opção inválida!";
				cout << "\n" << "Escolha novamente..." << "\n";
				system("pause");
				break;
		}
	} while (!validAction);
	system("pause");
	chosenCharacter.increaseLevel(1);
	return chosenCharacter;
}