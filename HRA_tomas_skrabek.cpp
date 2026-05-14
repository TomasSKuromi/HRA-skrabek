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

        cout << "\n*** LEVEL UP! (" << level << ") ***\n";

        cout << "HP: " << maxHp << " -> ";
        maxHp += 5;
        cout << maxHp << "\n";

        cout << "ATK: " << attack << " -> ";
        attack += 3;
        cout << attack << "\n";

        cout << "MANA: " << maxMana << " -> ";
        maxMana += 2;
        cout << maxMana << "\n";

        hp = maxHp;
        mana = maxMana;
    }
}

// ---------- VESNICE ----------
void village() {

    int choice;

    while (true) {

        cout << "\n=== VESNICE ===\n";
        cout << "Gold: " << gold << "\n";

        cout << "1 Heal (5 gold)\n";
        cout << "2 +HP (10 gold)\n";
        cout << "3 +ATK (10 gold)\n";
        cout << "4 +MANA (10 gold)\n";
        cout << "0 Exit\n";

        cin >> choice;

        if (choice == 1) {

            if (gold >= 5) {

                hp = maxHp;
                mana = maxMana;

                gold -= 5;

                cout << "Healed!\n";
            }
            else {
                cout << "Not enough gold!\n";
            }
        }

        else if (choice == 2) {

            if (gold >= 10) {

                maxHp += 5;
                gold -= 10;

                cout << "HP upgraded!\n";
            }
            else {
                cout << "Not enough gold!\n";
            }
        }

        else if (choice == 3) {

            if (gold >= 10) {

                attack += 2;
                gold -= 10;

                cout << "Attack upgraded!\n";
            }
            else {
                cout << "Not enough gold!\n";
            }
        }

        else if (choice == 4) {

            if (gold >= 10) {

                maxMana += 5;
                gold -= 10;

                cout << "Mana upgraded!\n";
            }
            else {
                cout << "Not enough gold!\n";
            }
        }

        else if (choice == 0) {
            break;
        }
    }
}

// ---------- SCHOPNOST ----------
void ability(vector<int>& enemyHp, int enemies) {

    if (playerClass == "Paladin") {

        if (mana >= 2) {

            mana -= 2;

            hp = min(maxHp, hp + 6);

            cout << "Holy Heal!\n";
        }
        else {
            cout << "Not enough mana!\n";
        }
    }

    else if (playerClass == "Mag") {

        if (mana >= 3) {

            mana -= 3;

            cout << "Fireball!\n";

            for (int i = 0; i < enemies; i++) {

                if (enemyHp[i] > 0) {

                    enemyHp[i] -= attack + 3;
                }
            }
        }
        else {
            cout << "Not enough mana!\n";
        }
    }

    else if (playerClass == "Lovec") {

        if (mana >= 3) {

            mana -= 3;

            cout << "Triple Shot!\n";

            for (int i = 0; i < enemies; i++) {

                if (enemyHp[i] > 0) {

                    enemyHp[i] -= attack * 3;
                    break;
                }
            }
        }
        else {
            cout << "Not enough mana!\n";
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

    // MINI BOSS ATTACKS FIRST
    if (miniBoss) {

        cout << "MiniBoss attacks first!\n";

        hp -= 5;

        cout << "You lost 5 HP!\n";

        if (hp <= 0) {

            cout << "\nPROHRA!\n";
            exit(0);
        }
    }

    while (true) {

        cout << "\nHP: " << hp << "/" << maxHp;
        cout << " | Mana: " << mana << "/" << maxMana << "\n";

        for (int i = 0; i < enemies; i++) {

            if (enemyHp[i] > 0) {

                cout << "Enemy " << i + 1
                     << " HP: " << enemyHp[i] << "\n";
            }
        }

        int choice;

        cout << "\n1 Attack\n";
        cout << "2 Skill\n";

        cin >> choice;

        // ATTACK
        if (choice == 1) {

            for (int i = 0; i < enemies; i++) {

                if (enemyHp[i] > 0) {

                    enemyHp[i] -= attack;

                    cout << "Hit!\n";

                    break;
                }
            }
        }

        // SKILL
        else if (choice == 2) {

            ability(enemyHp, enemies);
        }

        // DEAD CHECK
        bool dead = true;

        for (int hpE : enemyHp) {

            if (hpE > 0)
                dead = false;
        }

        // WIN
        if (dead) {

            cout << "\nVictory!\n";

            exp += miniBoss ? 10 : 5;

            // GOLD
            if (miniBoss) {

                int reward = 10 + rand() % 15;

                gold += reward;

                cout << "Gold earned: " << reward << "\n";
            }

            else if (rand() % 2) {

                int reward = 5 + rand() % 10;

                gold += reward;

                cout << "Gold earned: " << reward << "\n";
            }

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

            cout << "\nPROHRA!\n";
            exit(0);
        }
    }
}

// ---------- BOSS ----------
void bossFight() {

    int bossHp = 80;

    bool active = false;

    int damage = 0;

    int calmTurns = 0;

    cout << "\n=== BOSS: BLOOMSHADE ===\n";
    cout << "A strange flower watches you...\n";

    while (true) {

        cout << "\nHP: " << hp << "/" << maxHp;
        cout << "\nBoss HP: " << bossHp;
        cout << "\nBoss DMG: " << damage << "\n";

        int choice;

        cout << "\n1 Attack";
        cout << "\n2 Skill";
        cout << "\n3 Wait";
        cout << "\n";

        cin >> choice;

        bool attacked = false;

        // ATTACK
        if (choice == 1) {

            bossHp -= attack;

            attacked = true;

            cout << "You attacked Bloomshade!\n";
        }

        // SKILL
        else if (choice == 2) {

            if (mana >= 3) {

                mana -= 3;

                bossHp -= attack + 5;

                attacked = true;

                cout << "Skill used!\n";
            }
            else {

                cout << "Not enough mana!\n";
            }
        }

        // WAIT
        else if (choice == 3) {

            cout << "You wait...\n";
        }

        // ACTIVATION
        if (attacked) {

            calmTurns = 0;

            // FIRST ACTIVATION
            if (!active) {

                active = true;

                damage = 5;

                cout << "\nBloomshade awakens!\n";
            }

            // DAMAGE GROWTH
            else {

                damage += 5;

                cout << "Flowers duplicate...\n";
            }
        }

        // PLAYER DOES NOT ATTACK
        else {

            calmTurns++;

            // RESET
            if (calmTurns >= 2) {

                active = false;

                damage = 0;

                cout << "\nBloomshade calms down...\n";
            }
        }

        // WIN
        if (bossHp <= 0) {

            cout << "\n====================";
            cout << "\nYOU WON THE GAME!";
            cout << "\n====================\n";

            exit(0);
        }

        // BOSS ATTACK
        if (active) {

            hp -= damage;

            cout << "Bloomshade attacks for "
                 << damage << " damage!\n";

            if (hp <= 0) {

                cout << "\nPROHRA!\n";
                exit(0);
            }
        }

        // PASSIVE
        else {

            cout << "Bloomshade watches you...\n";
        }
    }
}

// ---------- CLASS SELECT ----------
void chooseClass() {

    while (true) {

        cout << "\nChoose class:\n";
        cout << "1 Paladin\n";
        cout << "2 Mag\n";
        cout << "3 Lovec\n";

        int c;
        cin >> c;

        if (c == 1) {

            cout << "\n=== PALADIN ===\n";
            cout << "HP: 30\n";
            cout << "Mana: 10\n";
            cout << "Attack: 5\n";
            cout << "Skill: Heal\n";
        }

        else if (c == 2) {

            cout << "\n=== MAG ===\n";
            cout << "HP: 20\n";
            cout << "Mana: 20\n";
            cout << "Attack: 6\n";
            cout << "Skill: Fireball\n";
        }

        else if (c == 3) {

            cout << "\n=== LOVEC ===\n";
            cout << "HP: 25\n";
            cout << "Mana: 12\n";
            cout << "Attack: 7\n";
            cout << "Skill: Triple Shot\n";
        }

        else {
            continue;
        }

        cout << "\nConfirm class?\n";
        cout << "1 YES\n";
        cout << "2 NO\n";

        int confirm;
        cin >> confirm;

        if (confirm != 1)
            continue;

        // SET CLASS
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

        break;
    }
}

// ---------- MAIN ----------
int main() {

    srand(time(0));

    chooseClass();

    village();

    // 1 MONSTER
    fight(1);

    // 2 MONSTERS
    fight(2);

    // MINI BOSS
    fight(1, true);

    village();

    fight(2);
    fight(2);

    // MINI BOSS
    fight(1, true);

    village();

    fight(2);
    fight(2);

    // 3 MONSTERS
    fight(3);

    village();

    // EXTRA FIGHTS = 16 MONSTERS TOTAL
    fight(2);
    fight(2);

    village();

    // FINAL BOSS
    bossFight();

    return 0;
}
