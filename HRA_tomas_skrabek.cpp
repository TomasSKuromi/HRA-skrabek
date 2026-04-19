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

// ---------- SCHOPNOST ----------

// ---------- BOJ ----------

// ---------- BOSS ----------

// ---------- MAIN ----------
int main() {


}

