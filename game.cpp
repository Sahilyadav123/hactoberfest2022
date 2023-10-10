# arcade game using c++
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Character {
public:
    std::string name;
    int health;
    int attack;

    Character(const std::string& name, int health, int attack)
        : name(name), health(health), attack(attack) {}

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    int generateAttack() const {
        // Generate a random attack within a range (e.g., between attack/2 and attack)
        return rand() % (attack / 2) + (attack / 2);
    }
};

void fight(Character& player, Character& enemy) {
    std::cout << "You encounter a " << enemy.name << " with " << enemy.health << " health." << std::endl;

    while (player.isAlive() && enemy.isAlive()) {
        // Player's turn
        int playerDamage = player.generateAttack();
        enemy.takeDamage(playerDamage);
        std::cout << "You attack the " << enemy.name << " for " << playerDamage << " damage. "
                  << enemy.name << " has " << enemy.health << " health left." << std::endl;

        // Check if the enemy is defeated
        if (!enemy.isAlive()) {
            std::cout << "You defeated the " << enemy.name << "!" << std::endl;
            break;
        }

        // Enemy's turn
        int enemyDamage = enemy.generateAttack();
        player.takeDamage(enemyDamage);
        std::cout << "The " << enemy.name << " attacks you for " << enemyDamage << " damage. "
                  << "You have " << player.health << " health left." << std::endl;

        // Check if the player is defeated
        if (!player.isAlive()) {
            std::cout << "You were defeated by the " << enemy.name << "." << std::endl;
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Character player("Player", 100, 20);
    Character enemy("Dragon", 150, 25);

    std::cout << "Welcome to the Combat Game!" << std::endl;
    std::cout << "You are " << player.name << " with " << player.health << " health and " << player.attack << " attack." << std::endl;

    char action;
    do {
        std::cout << "Do you want to fight? (y/n): ";
        std::cin >> action;

        if (action == 'y' || action == 'Y') {
            fight(player, enemy);
            if (player.isAlive()) {
                std::cout << "You are victorious!" << std::endl;
            }
            else {
                std::cout << "Game Over!" << std::endl;
            }
        }
    } while (action != 'n' && action != 'N');

    return 0;
}
