#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;
// ---------- HRAC ----------
string playerClass;

int hp, maxHp;
int mana, maxMana;
int attack;

int gold = 10;
int level = 1;
int exp = 0;

// ---------- LEVEL SYSTEM ----------
void levelUp() {
    while (exp >= level * 10) {
        exp -= level * 10;
        level++;

        maxHp += 5;
        attack += 3;
        maxMana += 2;

        hp = maxHp;

        cout << "\n*** LEVEL UP! (" << level << ") ***\n";
    }
}

// ---------- VESNICE ----------
void village() {
    int choice;

    while (true) {
        cout << "\n=== VESNICE ===\n";
        cout << "Zlato: " << gold << "\n";
        cout << "1 Heal (5)\n2 +HP (10)\n3 +ATK (10)\n4 +MANA (10)\n0 Odejit\n";

        cin >> choice;

        if (choice == 1 && gold >= 5) {
            hp = maxHp;
            gold -= 5;
        }
        else if (choice == 2 && gold >= 10) {
            maxHp += 5;
            gold -= 10;
        }
        else if (choice == 3 && gold >= 10) {
            attack += 2;
            gold -= 10;
        }
        else if (choice == 4 && gold >= 10) {
            maxMana += 5;
            gold -= 10;
        }
        else if (choice == 0) break;
    }
}

void ability(vector<int>& enemyHp, int enemies) {

    if (playerClass == "Paladin") {
        if (mana >= 2) {
            mana -= 2;
            hp = min(maxHp, hp + 6);
            cout << "Heal!\n";
        }
    }

    else if (playerClass == "Mag") {
        if (mana >= 3) {
            mana -= 3;
            cout << "Fireball!\n";
            for (int i = 0; i < enemies; i++)
                if (enemyHp[i] > 0)
                    enemyHp[i] -= attack + 3;
        }
    }

    else if (playerClass == "Lovec") {
        if (mana >= 3) {
            mana -= 3;
            cout << "triple shot!\n";

            for (int i = 0; i < enemies; i++) {
                if (enemyHp[i] > 0) {
                    enemyHp[i] -= attack * 3;
                    break;
                }
            }
        }
    }
}

// ---------- BOJ ----------
void fight(int enemies, bool miniBoss = false) {

    vector<int> enemyHp(enemies);

    for (int i = 0; i < enemies; i++) {
        enemyHp[i] = miniBoss ? 30 : (10 + rand() % 10);
    }

    cout << "\n--- SOUBOJ ---\n";

    while (true) {

        cout << "\nHP: " << hp << "/" << maxHp
             << " | Mana: " << mana << "/" << maxMana << "\n";

        int choice;
        cout << "1 Attack\n2 Skill\n";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < enemies; i++) {
                if (enemyHp[i] > 0) {
                    enemyHp[i] -= attack;
                    cout << "Hit!\n";
                    break;
                }
            }
        }
        else if (choice == 2) {
            ability(enemyHp, enemies);
        }

        // DEAD CHECK
        bool dead = true;
        for (int hpsmrt : enemyHp)
            if (hpsmrt > 0) dead = false;

        if (dead) {
            cout << "Vyhra!\n";

            exp += miniBoss ? 10 : 5;

            if (miniBoss)
                gold += 10 + rand() % 15;
            else if (rand() % 2)
                gold += 5 + rand() % 10;

            levelUp();
            return;
        }

        // ENEMY ATTACK
        for (int i = 0; i < enemies; i++) {
            if (enemyHp[i] > 0) {
                hp -= miniBoss ? 5 : 3;
            }
        }

        if (hp <= 0) {
            cout << "PROHRA!\n";
            exit(0);
        }
    }
}

// ---------- BOJ ----------

// ---------- BOSS ----------

// ---------- MAIN ----------
int main() {


}

