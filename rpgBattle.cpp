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
			int crit
			) : 
			name_(name), 
			maxHp_(maxHp), 
			currentHp_(currentHp), 
			atk_(atk), 
			def_(def), 
			crit_(crit) 
		{}

	    // Métodos para acessar os atributos.
	    string getName() const { return name_; }
	    int getMaxHp() const { return maxHp_; }
	    int getCurrentHp() const { return currentHp_; }
	    int getAtk() const { return atk_; }
	    int getDef() const { return def_; }
	    int getCrit() const { return crit_; }

	private:
	    // Atributos
	    string name_;
	    int maxHp_;
	    int currentHp_;
	    int atk_;
	    int def_;
	    int crit_;
};

// Prototipagem das funções.
void createLayout();
Monster chooseRandomMonster(const vector<Monster>& monsters);

main() {
	system("chcp 65001");
	srand(time(NULL));
	
	vector<Monster> monsters = {
		Monster("Hero", 40, 40, 5, 0, 5),
		Monster("Goblin", 27, 27, 3, 0, 1),
		Monster("Orc", 65, 65, 9, 1, 2),
	};
	// int action, actionResult;

	Monster randomMonster = chooseRandomMonster(monsters);
    cout << "\n" << "O monstro escolhido foi: " << randomMonster.getName() << "\n";
	// do {
	// 	system("cls");
		
	// 	gerarLayout();
	// 	cin >> action;
		
	// 	switch (action) {
	// 		case 1:
	// 			actionResult = heroiAtacar();
	// 			cout << "Você ataca causando: " << actionResult << " de dano!";
	// 			bossHp -= actionResult;
	// 			cout << "\n\n";
	// 			system("pause");
				
	// 			actionResult = monstroAtacar(bossAtk);
	// 			cout << "O monstro te ataca causando: " << actionResult << " de dano!";
	// 			heroHp -= actionResult;
	// 			cout << "\n\n";
	// 			system("pause");
	// 			break;
	// 	}
	// } while (heroHp > 0 || bossHp > 0);
}

//void gerarLayout() {
//	cout << "\n" << "Sua HP: " << heroHp << " / " << heroMaxHp;
//	cout << "\n\n\t" << "-----Dragão: " << bossHp << "/ 650-----" << "\n\n";
//	
//	cout << "                             / \\  //\\" << "\n";
//    cout << "                |\\___/|      /   \\//  \\\\" << "\n";
//    cout << "                /0  0  \\__  /    //  | \\ \\" << "\n";
//    cout << "               /     /  \\/_/    //   |  \\  \\" << "\n";
//    cout << "               @_^_@'/   \\/_   //    |   \\   \\" << "\n";
//    cout << "               //_^_/     \\/_ //     |    \\    \\" << "\n";
//    cout << "            ( //) |        \\///      |     \\     \\" << "\n";
//    cout << "          ( / /) _|_ /   )  //       |      \\     _\\" << "\n";
//    cout << "        ( // /) '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-. " << "\n";
//    cout << "      (( / / )) ,-{        _      `-.|.-~-.           .~         `. " << "\n";
//    cout << "     (( // / ))  '/\\      /                 ~-. _ .-~      .-~^-.  \\" << "\n";
//    cout << "     (( /// ))      `.   {            }                   /      \\  \\" << "\n";
//    cout << "      (( / ))     .----~-.\        \\-'                 .~         \\  `. \\^-." << "\n";
//    cout << "                 ///.----..>        \\             _ -~             `.  ^-`  ^-_ " << "\n";
//    cout << "                   ///-._ _ _ _ _ _ _}^ - - - - ~                     ~-- ,.-~ " << "\n";
//    cout << "                                                                      /.-~ " << "\n";
//	
//	cout << "\n" << "Chegou o seu turno, o que você faz?";
//	cout << "\n" << "[1] - atacar";
//	cout << "\n" << "[2] - curar-se";
//	cout << "\n" << "[3] - magia selvagem";
//}
//
//int heroiAtacar() {
//	int damage;
//	
//	damage = rand() % (10 * heroAtk) + 1;
//	
//	return damage;
//}
//
//int monstroAtacar(int monsterAtk) {
//	int damage;
//	
//	damage = rand() % (3 * monsterAtk) + 1;
//	
//	return damage;
//}


// & monsters, indica que o vetor `monsters`é passado por referencia a função.
// Recebendo o seu endereço da memória.
Monster chooseRandomMonster(const vector<Monster>& monsters) {
	// Gera um índice aleatório diferente de 0.
    int index = rand() % monsters.size() + 1; 
    return monsters[index];
}