// Battle1.cpp : It's the game where you have to fight with your enemy.
//
// 
//Á³áë³îòåêè
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int heroHealth = 1000;  /* Ãëîáàëüí³ çì³íí³*/
int enemyHealth = 2000;
int heroEnergy = 100;
int enemyEnergy = 200;
int choice;
bool queue;
bool block = false; /**/

HANDLE hConsole;

enum Colors
{
    Blue=3,
    Green=2,
    Red=4,
    Orange=6,
    BrightBlue=11
}; // Ùîá ðîçêðàøóâàòè ñòðîêè

void Game();    //Ôóíêö³ÿ, ó ÿê³é â³äáóâàºòüñÿ ñàìà ãðà
void HeroAttack();  //Àòàêà ãðàâöÿ
void EnemyAttack(); //Àòàêà âîðîãà
void EnemyAction(); //Ä³¿ âîðîãà
void HeroRegen();   //Ðåãåíåðàö³ÿ æèòòÿ ãðàâöÿ
void Block();   //Áëîê ãðàâöÿ
void TakeHeroEnergy();  //Âîðîã çàáèðàº åíåðã³þ ãðàâöÿ
void Description(); //Îïèñ ãðè
void EnemyTidalWave();  //Ðóéí³âíà õâèëÿ âîðîãà
void HeroTidalWave();   //Ðóéí³âíà õâèëÿ ãðàâöÿ

int main()
{
    char choose;
    Description();
    cout << "To start press any key\n";
    _getch();

    system("cls");

    srand(static_cast<unsigned int>(time(0)));
    queue = rand() % 2;
    
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true)
    {
        while (heroHealth > 0 && enemyHealth > 0)
            Game();

        if (heroHealth > enemyHealth)
        {
            SetConsoleTextAttribute(hConsole, Orange);
            cout << "You won!\n";
        }
        else
        {
            SetConsoleTextAttribute(hConsole, Orange);
            cout << "Your enemy won :(\n";
        }
        cout << "\nDo you want to play again? If yes press \'y\', if no press \'n\'";
        cin >> choose;
        if (choose == 'y')
        {
            system("cls");
            heroHealth = 1000;
            enemyHealth = 2000;
            heroEnergy = 100;
            enemyEnergy = 200;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, BrightBlue);
            cout << "Thanks for playing!";
            break;
        }
    }

    _getch();
}
// Îïèñ Ôóíêö³¿ Game()
void Game()
{
    
    SetConsoleTextAttribute(hConsole, BrightBlue);
    cout << "Your hp: ";
    SetConsoleTextAttribute(hConsole, Red);
    cout << heroHealth << endl;
    SetConsoleTextAttribute(hConsole, BrightBlue);
    cout << "Enemy hp: ";
    SetConsoleTextAttribute(hConsole, Red);
    cout << enemyHealth << endl;
    SetConsoleTextAttribute(hConsole, BrightBlue);
    cout << "Your energy: ";
    SetConsoleTextAttribute(hConsole, Red);
    cout << heroEnergy << endl;
    SetConsoleTextAttribute(hConsole, BrightBlue);
    cout << "Enemy energy: ";
    SetConsoleTextAttribute(hConsole, Red);
    cout << enemyEnergy << endl << endl;

    if (queue)
    {
        SetConsoleTextAttribute(hConsole, Orange);
        cout << "Choose action:\n";
        SetConsoleTextAttribute(hConsole, Green);
        cout << "1. Attack\n";
        cout << "2. Regen (30 energy points)\n";
        cout << "3. Block\n";
        cout << "4. \"Tidal wave\"\n";
        
        choice = _getch();
        system("cls");

        switch (choice)
        {
        case 49:
            HeroAttack();
            Sleep(1000);
            break;
        case 50:
            HeroRegen();
            Sleep(1000);
            break;
        case 51:
            Block();
            Sleep(1000);
            break;
        case 52:
            HeroTidalWave();
            Sleep(1000);
            break;
        }
        
        if (heroEnergy > 100)
            heroEnergy = 100;
        
    }
    else
    {
        EnemyAction();
        enemyEnergy += 10;
        if (enemyEnergy > 200)
            enemyEnergy = 200;
        queue = true;
    }
    
}
// Îïèñ Ôóíêö³¿ HeroAttack()
void HeroAttack()
{
    srand(static_cast<unsigned int>(time(0)));
    int damage = rand() % 100;
    int promah = rand() % 6;
    if (damage < 50)
        damage += 50;
    if (!promah)
    {
        SetConsoleTextAttribute(hConsole, Green);
        cout << "\n\t\tYour missing!\n";
        queue = false;
        return;
    }
    enemyHealth -= damage;
    
    cout << "\nYou hit with damage: "<<damage<<"\n";
    heroEnergy += 10;
    queue = false;
}
// Îïèñ Ôóíêö³¿ EnemyAction()
void EnemyAction()
{
    int randt;
    //srand(static_cast<unsigned int>(time(0)));
    randt = rand();
    if (randt % 20 == 0 && enemyEnergy > 60)
        EnemyTidalWave();
    else if (randt % 6 == 0)
        TakeHeroEnergy();
    else
        EnemyAttack();
    
}
// Îïèñ Ôóíêö³¿ EnemyAttack()
void EnemyAttack()
{
    
    int damage = rand() % 100;
    int promah = rand() % 6;
    if (damage < 50)
        damage += 50;
    if (block)
    {
        damage /= 4;
        block = false;
    }
    if (!promah)
    {
        SetConsoleTextAttribute(hConsole, Blue);
        
        cout << "\t\tEnemy's missing!\n\n";
        return;
    }
    heroHealth -= damage;
    
    cout << "\nEnemy hit with damage: " << damage << "\n";

    if (enemyHealth < 2000)
    {
        enemyHealth += damage / 2;
        if (enemyHealth > 2000)
            enemyHealth = 2000;
    }
}
// Îïèñ Ôóíêö³¿ HeroRegen()
void HeroRegen()
{
    if (heroEnergy < 30)
    {
        SetConsoleTextAttribute(hConsole, Green);
        
        cout << "\n\t\tYou cannot use regeneration because you don't have enough energy\n";
        queue = true;
        return;
    }
    
    heroHealth += 200;
    heroEnergy -= 30;
    if (heroHealth > 1000)
        heroHealth = 1000;
    queue = false;
}
// Îïèñ Ôóíê³¿ Block()
void Block()
{
    
    block = true;
    queue = false;
    SetConsoleTextAttribute(hConsole, Blue);
    cout << "\n\t\tYou blocked\n";
    heroEnergy += 10;
}
// Îïèñ Ôóíêö³¿ TakeHeroEnergy()
void TakeHeroEnergy()
{
    heroEnergy -=20;
    enemyEnergy += 20;
    if (enemyEnergy > 200)
        enemyEnergy = 200;
    if (heroEnergy < 0)
        heroEnergy = 0;
    
    cout << "Enemy took 20 points of your energy\n\n";
    block = false;
}
// Îïèñ Ôóíêö³¿ Description()
void Description()
{
    cout << "This game calls \"Battle of legends\".\n";
    cout << "You have to fight with your enemy.\n";
    cout << "With \"Attack\" action you heat the enemy with random damage.\n";
    cout << "With \"Regen\" action you regeneration your hp. It cost 30 energy points.\n";
    cout << "With \"Block\" action you block yourself. Enemy's damage devides by 4.\n";
    cout << "With \"Tidal wave\" action you devide enemy's health by 2.\n\n\n";
}
// Îïèñ Ôóíêö³¿ EnemyTidalWave()
void EnemyTidalWave()
{

    block = false;
    heroHealth /= 2;
    enemyEnergy -= 60;
    SetConsoleTextAttribute(hConsole, Red);
    cout << "\n\t\tEnemy used \"Tidal wave\"\n";
}
// Îïèñ Ôóíêö³¿ HeroTidalWave()
void HeroTidalWave()
{
    if (heroEnergy < 60)
    {
        cout << "\n\t\tYou cannot use \"Tidal wave\"\n";
        queue = true;
        return;
    }
    enemyHealth /= 2;
    heroEnergy -= 60;
    queue = false;
}