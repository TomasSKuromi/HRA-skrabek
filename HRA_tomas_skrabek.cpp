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
        for (int hpE : enemyHp)
            if (hpE > 0) dead = false;

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

// ---------- BOSS ----------
void bossFight() {

    vector<int> enemyHp(1);
    enemyHp[0] = 80;

    int damage = 5;
    bool active = false;
    int calm = 0;

    cout << "\n=== BOSS: BLOOMSHADE ===\n";

    while (true) {

        cout << "\nHP: " << hp << "/" << maxHp;
        cout << "\nBoss HP: " << enemyHp[0] << "\n";

        int choice;
        cout << "1 Attack\n2 Skill\n";
        cin >> choice;

        bool attacked = false;

        if (choice == 1) {
            enemyHp[0] -= attack;
            attacked = true;
        }
        else if (choice == 2 && mana >= 3) {
            mana -= 3;
            enemyHp[0] -= attack;
            attacked = true;
        }

        // aktivace bosse
        if (attacked) {
            active = true;
            calm = 0;
            damage = min(damage + 2, 20);
        }
        else {
            calm++;
        }

        if (calm >= 2) {
            active = false;
            damage = 5;
        }

        // win check
        if (enemyHp[0] <= 0) {
            cout << "\nVYHRA HRY!\n";
            exit(0);
        }

        // boss attack
        hp -= damage;

        cout << "Boss hit: " << damage << "\n";

        if (hp <= 0) {
            cout << "\nPROHRA!\n";
            exit(0);
        }
    }
}
// ---------- MAIN ----------
int main() {

    srand(time(0));

    while (true) {

        cout << "Class:\n1 Paladin\n2 Mag\n3 Lovec\n";

        int c;
        cin >> c;

        if (c == 1) {
            playerClass = "Paladin";
            maxHp = hp = 30;
            maxMana = mana = 10;
            attack = 5;
        }
        else if (c == 2) {
            playerClass = "Mag";
            maxHp = hp = 20;
            maxMana = mana = 20;
            attack = 6;
        }
        else if (c == 3) {
            playerClass = "Lovec";
            maxHp = hp = 25;
            maxMana = mana = 12;
            attack = 7;
        }
        else continue;

        break;
    }

    village();

    fight(1);
    fight(2);
    fight(1, true);

    village();

    fight(2);
    fight(2);
    fight(1, true);

    village();

    fight(2);
    fight(3);

    village();

    bossFight();

    return 0;
}
