#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include "Object.h"
#include "Gun.h"
#include "Character.h"
#include "Hero.h"
#include "Pistol.h"
#include "Bazooka.h"
#include "Rifle.h"
#include "Monster.h"
#include "MedicHero.h"
#include "DemolitionHero.h"
#include "GhostMonster.h"
#include "TankMonster.h"
#include "Item.h"
#include "Ammo.h"
#include "Potion.h"
#include "Game.h"
using namespace std;

// Object class

    Object::Object(char t) : type(t) {}

    char Object::getType() const {
        return type;
    }

    ostream& operator<<(ostream& os, const Object& o){
        char c = o.getType();
        switch(c){
            case 'G' :
                os<<"Ghost monster";
                break;
             case 'T' :
                os<<"Tank monster";
                break;
             case 'M' :
                os<<"Medic hero";
                break;
             case 'D' :
                os<<"Demolition hero";
                break;
            case 'P' :
                os<<"Potion";
                break;
            case 'A' :
                os<<"Ammo";
                break;
            default :
                os<<"error";
        }
        return os;
    }


    Gun::Gun( string n, int b, int d, int r) : name(n), bullets(b), damage(d), range(r) {}

        string Gun::getName() {
            return name;
        }

        int Gun::getBullets()  {
            return bullets;
        }

        void Gun::setBullets(int x)
        {
            bullets = x;
        }

        int Gun::getDamage()  {
            return damage;
        }

        int Gun::getRange()  {
            return range;
        }

        void Gun::useSpecial(Hero& h1 , Object* map[15][15]) {}

// Character class

    Character::Character(char t, int x, int y, int hp) : Object(t), positionX(x), positionY(y), healthPoints(hp) {}

    int Character::getPositionX()  {
        return positionX;
    }

    int Character::getPositionY()  {
        return positionY;
    }

    int Character::getHealthPoints()  {
        return healthPoints;
    }

    void Character::setPosition(int x, int y) {
        positionX = x;
        positionY = y;
    }

    void Character::setHealthPoints(int hp) {
        healthPoints = hp;
    }


// Hero class
    Hero::Hero(char t, int x, int y, int hp) : Character(t, x, y, hp) {

    }

     Gun* Hero::getWeapon()  {
        return weapon;
    }
    void Hero::setWeapon(Gun* g){
        weapon = g;
    }


    Hero& Hero::operator+(Potion &p)
    {
        this->setHealthPoints(p.getHealingAmount()+this->getHealthPoints());
        return *this;
    }

    Hero& Hero::operator-(Monster &m)
    {
        this->setHealthPoints(this->getHealthPoints() - 10);
        m.setHealthPoints(m.getHealthPoints() - 20);

        return *this;
    }


    Hero::~Hero(){
        delete weapon;
    }


    ostream& operator<<(ostream& os, Hero& hero)
    {
        os<<"Hero type: "<< hero.type << "\n"
          << "Hero position: x = " << hero.positionX << " y = " << hero.positionY << "\n"
          << "Hero Health: " << hero.healthPoints << "\n"
          << "Hero's guns: " << hero.getWeapon()->getName() << " Bullets: " << hero.getWeapon()->getBullets()<<endl;

        return os;
    }

// Gun subclasses

    Pistol::Pistol() : Gun("Pistol", 16, 30, 2) {}

    void Pistol::useSpecial(Hero& hero , Object* map[15][15])
    {
        int x = hero.getPositionX();
        int y = hero.getPositionY();

        bool flag = false;

        hero.getWeapon()->setBullets(hero.getWeapon()->getBullets() -4);
        if(y != 14){
            for(int i = 1; i <= hero.getWeapon()->getRange(); i++)
                    {
                        if(map[y + i][x]->getType() == 'T' || map[y + i][x]->getType() == 'G')
                        {
                            Monster *m=static_cast<Monster*>(map[y + i][x]);
                            m->setHealthPoints(m->getHealthPoints() - hero.getWeapon()->getDamage());

                            cout<<"A monster was hit!"<<endl;
                            flag = true;
                        }
                    }
                    if(!flag)
                    {
                        cout<<"nothing was hit!"<<endl;
                    }
        }
        else
        {
            cout<<"nothing was hit!"<<endl;
        }

        flag = false;
        if(x != 14)
        {
            for(int i = 1; i <= hero.getWeapon()->getRange(); i++)
                    {
                        if(map[y][x+i]->getType() == 'T' || map[y][x+i]->getType() == 'G')
                        {
                            Monster *m=static_cast<Monster*>(map[y][x+i]);
                            m->setHealthPoints(m->getHealthPoints() - hero.getWeapon()->getDamage());

                            cout<<"A monster was hit!"<<endl;
                            flag = true;
                        }
                    }
            if(!flag)
                    {
                        cout<<"nothing was hit!"<<endl;
                    }
        }
        else
        {
            cout<<"nothing was hit!"<<endl;
        }


        flag = false;


        if(x !=0)
        {
             for(int i = 1; i <= hero.getWeapon()->getRange(); i++)
                    {
                        if(map[y][x-i]->getType() == 'T' || map[y][x-i]->getType() == 'G')
                        {
                            Monster *m=static_cast<Monster*>(map[y][x-i]);
                            m->setHealthPoints(m->getHealthPoints() - hero.getWeapon()->getDamage());

                            cout<<"A monster was hit!"<<endl;
                            flag = true;
                        }
                    }
                if(!flag)
                    {
                        cout<<"nothing was hit!"<<endl;
                    }
        }
        else
        {
            cout<<"nothing was hit!"<<endl;
        }

        flag = false;

        if(y!=0)
        {
         for(int i = 1; i <= hero.getWeapon()->getRange(); i++)
                {
                    if(map[y-i][x]->getType() == 'T' || map[y-i][x]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(map[y-i][x]);
                        m->setHealthPoints(m->getHealthPoints() - hero.getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                    }
                }
                if(!flag)
                    {
                        cout<<"nothing was hit!"<<endl;
                    }
        }
        else
        {
            cout<<"nothing was hit!"<<endl;
        }
    }



    Bazooka::Bazooka() : Gun("Bazooka", 4, 150, 8) {}


    void Bazooka::useSpecial(Hero& h1 , Object* map[15][15])
    {
        int x = h1.getPositionX();
        int y = h1.getPositionY();

        const int rows = 15;

        //X DIAGONAL
        if(x==y)
        {
            for(int i =0;i<rows;i++)
            {
                if(map[i][i]->getType() == 'T' || map[i][i]->getType() == 'G')
                {
                    Monster *m=static_cast<Monster*>(*&map[i][i]);
                    m->setHealthPoints(0);

                    cout<<"A monster was hit!"<<endl;
                }
            }
        }
        else{
            cout<<"not on x diagonal"<<endl;
        }

        //Y DIAGONAL

        if(x+y == rows-1)
        {
             for(int i =0;i<rows;i++)
            {
                if(map[rows-1-i][i]->getType() == 'T' || map[rows-1-i][i]->getType() == 'G')
                {
                    Monster *m=static_cast<Monster*>(*&map[rows-1-i][i]);
                    m->setHealthPoints(0);

                    cout<<"A monster was hit!"<<endl;
                }
            }
        }
        else{
            cout<<"not on y diagonal"<<endl;
        }
    }

    Rifle::Rifle() : Gun("Rifle", 30, 20, 4) {}


    void Rifle::useSpecial(Hero& h1 , Object* map[15][15])
    {
        h1.getWeapon()->setBullets(h1.getWeapon()->getBullets() -1);
        int x = h1.getPositionX();
        int y = h1.getPositionY();

        int limit = this->getRange();

        for(int j = 0;j<3;j++){

        //UP
        if(y != 0)
        {
            if(j==0){
                for(int i =1;i<limit+1;i++){
                    if(map[x][y+i]->getType() == 'T' || map[x][y+i]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(*&map[x][y+i]);
                        m->setHealthPoints(m->getHealthPoints() - h1.getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                    }
                }
            }
        }
        else{
            cout<<"nothing was hit!"<<endl;
        }


        //RIGHT
        if(x!= 14)
        {
            if(j==1)
            {
                for(int i =1;i<limit+1;i++){
                    if(map[x+i][y]->getType() == 'T' || map[x+i][y]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(*&map[x+i][y]);
                        m->setHealthPoints(m->getHealthPoints() - h1.getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                    }
                }
            }
        }
        else{
        cout<<"nothing was hit!"<<endl;
        }

            if(j==2)
            {
                if(x != 0){
                //LEFT
             for(int i =1;i<limit+1;i++){
                    if(map[x-i][y]->getType() == 'T' || map[x-i][y]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(*&map[x-i][y]);
                        m->setHealthPoints(m->getHealthPoints() - h1.getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                    }
                }
                }
                else{
                    cout<<"nothing was hit!"<<endl;
                }
            }
        }
    }


// Monster class

    Monster::Monster(char t, int x, int y, int hp) : Character(t, x, y, hp) {}


// Hero subclasses
MedicHero::MedicHero(char t, int x, int y, int hp,int ha) : Hero(t, x, y, hp), healingAmount(ha) {}

    int MedicHero::getHealingAmount()  {
        return healingAmount;
    }

    //use special medic hero
     void MedicHero::useSpecial(){
        if(healthPoints != 0){
            healthPoints = healthPoints + healingAmount;
            healingAmount = 0;
        }
     }

    MedicHero& MedicHero::operator+ (Ammo& a)
    {
        this->weapon->setBullets(this->weapon->getBullets() + a.getBullets());
        return *this;
    }

DemolitionHero::DemolitionHero(char t, int x, int y, int hp) : Hero(t, x, y, hp) {}

DemolitionHero& DemolitionHero::operator+ (Ammo& a)
{
    this->weapon->setBullets(this->weapon->getBullets() + a.getBullets());
    this->weapon2->setBullets(this->weapon2->getBullets() + a.getBullets());
    return *this;

}

void DemolitionHero::setWeapon2(Gun* g)
{
    weapon2 = g;
}

Gun* DemolitionHero::getWeapon2()
{
    return weapon2;
}

//use special demo hero
void DemolitionHero::useSpecial(){
        Gun* temp = this->weapon2;
        weapon2 = this->weapon;
        weapon = temp;
    }

// Monster subclasses
GhostMonster::GhostMonster(char t, int x, int y, int hp) : Monster(t, x, y, hp), isVisible(true) {}

    void GhostMonster::setIsVisible(bool t)
    {
        isVisible = t;
    }

    bool GhostMonster::isVisibleOnMap() const {
        return isVisible;
    }


TankMonster::TankMonster(char t, int x, int y, int hp, int s) : Monster(t, x, y, hp), shield(s) {}

    int TankMonster::getShield() const {
        return shield;
    }


// Item class
Item::Item(char t) : Object(t) {}


// Item subclasses
Ammo::Ammo(int b) : Item('A'), bullets(b) {}

    int Ammo::getBullets() const {
        return bullets;
    }


Potion::Potion(int ha) : Item('P'), healingAmount(ha) {}

    int Potion::getHealingAmount() const {
        return healingAmount;
    }


// Game class
Game::Game() {
        hero = NULL;
        // Initialize grid with empty objects
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j] = new Object('.');
            }
        }
    }

    Game::~Game() {
        // Deallocate memory for grid objects
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
        }
        // Deallocate memory for hero object
        delete hero;
    }

    void Game::generateMap() {
        srand(time(0));

        // Generate health potions
        for (int i = 0; i < 5; i++) {
            int healingAmount = rand() % 41 + 10;  // Random number between 10 and 50
            grid[rand() % rows][rand() % cols] = new Potion(healingAmount);
        }

        // Generate ammo
        for (int i = 0; i < 10; i++) {
            int bullets = rand() % 16 + 5;  // Random number between 5 and 20
            grid[rand() % rows][rand() % cols] = new Ammo(bullets);
        }

        // Generate monsters

         int monsterCount = 5;
         int monsterHPRange = 10;
         int monsterHPMin = 10;

            for (int j = 0; j < monsterCount; j++) {
                int hp = (rand() % monsterHPRange + 6) * monsterHPMin;  // Random multiple of 10 between 60 and 150
                grid[rand() % rows][rand() % cols] = new TankMonster('T', 0, 0, 2*hp,hp);
            }

            for (int j = 0; j < monsterCount; j++) {
                int hp = (rand() % monsterHPRange + 6) * monsterHPMin;  // Random multiple of 10 between 60 and 150
                grid[rand() % rows][rand() % cols] = new GhostMonster('G', 0, 0, hp);
            }

    }

    void Game::showMap()  {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(grid[i][j]->getType() == 'G')
                {
                    GhostMonster *m = static_cast<GhostMonster*>(grid[i][j]);
                    if(m->isVisibleOnMap())
                    {
                        cout << grid[i][j]->getType() << " ";
                    }
                    else
                    {
                        cout << '.' << " ";
                    }
                }
                else
                {
                    cout << grid[i][j]->getType() << " ";
                }
            }
            cout << endl;
        }
    }


    void Game::startGame() {
        int heroType;
        int gunType;

        cout << "Please enter 1 to choose Demolition or 2 to choose Medic: ";
        cin >> heroType;

        cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
        cin >> gunType;

        if (heroType == 1) {
            if (gunType == 1) {
                Pistol* p = new Pistol();
                cout<<"Choose your second weapon"<<endl;
                cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
                int gun2;
                cin >> gun2;
                hero = new DemolitionHero('D', 0, 0, 100);
                hero->setWeapon(p);
                if(gun2 == 1)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Pistol* p2 = new Pistol();
                    dm->setWeapon2(p2);
                }
                else if(gun2 == 2)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Bazooka* b2 = new Bazooka();
                    dm->setWeapon2(b2);
                }
                else if(gun2 == 3)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Rifle* r2 = new Rifle();
                    dm->setWeapon2(r2);
                }

            } else if (gunType == 2) {
                Bazooka* b = new Bazooka();
                cout<<"Choose your second weapon"<<endl;
                cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
                int gun2;
                cin >> gun2;
                hero = new DemolitionHero('D', 0, 0, 100);
                hero->setWeapon(b);
                if(gun2 == 1)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Pistol* p2 = new Pistol();
                    dm->setWeapon2(p2);
                }
                else if(gun2 == 2)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Bazooka* b2 = new Bazooka();
                    dm->setWeapon2(b2);
                }
                else if(gun2 == 3)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Rifle* r2 = new Rifle();
                    dm->setWeapon2(r2);
                }
            } else if (gunType == 3) {
                Rifle* r = new Rifle();
                cout<<"Choose your second weapon"<<endl;
                cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
                int gun2;
                cin >> gun2;
                hero = new DemolitionHero('D', 0, 0, 100);
                hero->setWeapon(r);
                if(gun2 == 1)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Pistol* p2 = new Pistol();
                    dm->setWeapon2(p2);
                }
                else if(gun2 == 2)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Bazooka* b2 = new Bazooka();
                    dm->setWeapon2(b2);
                }
                else if(gun2 == 3)
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    Rifle* r2 = new Rifle();
                    dm->setWeapon2(r2);
                }
            }
        } else if (heroType == 2) {
            if (gunType == 1) {
                Pistol* p = new Pistol();
                hero = new MedicHero('M', 0, 0, 100,50);
            hero->setWeapon(p);
            } else if (gunType == 2) {
                Bazooka* b = new Bazooka();
                hero = new MedicHero('M', 0, 0, 100,50);
                hero->setWeapon(b);
            } else if (gunType == 3) {

                Rifle* r = new Rifle();
                hero = new MedicHero('M', 0, 0, 100,50);
                hero->setWeapon(r);
            }
        }

        generateMap();
        grid[hero->getPositionY()][hero->getPositionX()] = hero;

        system("cls");

        round = 0;

        valid = true;

        cout<<"Round: "<<round<<endl;

        cout<<"A: Ammo, P: Potion, T: Tank Monster, G: Ghost Monster"<<endl;

        cout<<endl;

        cout<<*hero<<endl;

        showMap();

        cout<<endl;

        cout<<"1 to move, 2 to shoot, 3 to use the gun's special ability, 4 to use the hero's special ability"<<endl;

        playRound();
    }

    void Game::useGunSpecial() {
        Gun *g;
        int x = hero->getPositionX();
        int y = hero->getPositionY();
        if(hero->getWeapon()->getName()=="Pistol"){
            g = static_cast<Pistol *>(hero->getWeapon());
            if(g->getBullets()>=4){
                g->useSpecial(*hero,grid);
            }
            else
            {
                cout<<"Not enough bullets!"<<endl;
                round--;
            }
        }
        else if(hero->getWeapon()->getName()=="Bazooka"){
            g = static_cast<Bazooka *>(hero->getWeapon());
            if(x==y || x+y==rows-1){
                g->useSpecial(*hero,grid);
            }
            else
            {
                cout<<"not on diagonal"<<endl;
                round--;
            }
        }
        else if(hero->getWeapon()->getName()=="Rifle"){
            g = static_cast<Rifle *>(hero->getWeapon());
            if(g->getBullets()>=3){
                g->useSpecial(*hero,grid);
            }
            else
            {
                cout<<"Not enough bullets!"<<endl;
                round--;
            }
        }
    }



    void Game::FireGun(char direction)
    {
        if(hero->getWeapon()->getBullets() == 0)
        {
            cout<<"The gun is empty!"<<endl;
            round--;
        }
        else
        {
            hero->getWeapon()->setBullets(hero->getWeapon()->getBullets() -1);

            if(direction == 's')
            {
                for(int i = 1; i <= hero->getWeapon()->getRange(); i++)
                {
                    if(hero->getPositionY() + i > 14)
                    {
                        cout<<"nothing was hit!"<<endl;
                        return;
                    }
                    if(grid[hero->getPositionY() + i][hero->getPositionX()]->getType() == 'T' || grid[hero->getPositionY() + i][hero->getPositionX()]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(grid[hero->getPositionY() + i][hero->getPositionX()]);
                        m->setHealthPoints(m->getHealthPoints() - hero->getWeapon()->getDamage());

                        cout<<m->getHealthPoints()<<endl;

                        cout<<"A monster was hit!"<<endl;
                        return;
                    }
                }
                cout<<"nothing was hit!"<<endl;
            }

            if(direction == 'w')
            {
                for(int i = 1; i <= hero->getWeapon()->getRange(); i++)
                {
                    if(hero->getPositionY() - i < 0)
                    {
                        cout<<"nothing was hit!"<<endl;
                        return;
                    }
                    if(grid[hero->getPositionY() + i][hero->getPositionX()]->getType() == 'T' || grid[hero->getPositionY() + i][hero->getPositionX()]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(grid[hero->getPositionY() + i][hero->getPositionX()]);
                        m->setHealthPoints(m->getHealthPoints() - hero->getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                        return;
                    }
                }
                cout<<"nothing was hit!"<<endl;
            }

            if(direction == 'a')
            {
                for(int i = 1; i <= hero->getWeapon()->getRange(); i++)
                {
                    if(hero->getPositionX() - i < 0)
                    {
                        cout<<"nothing was hit!"<<endl;
                        return;
                    }
                    if(grid[hero->getPositionY()][hero->getPositionX() + i]->getType() == 'T' || grid[hero->getPositionY()][hero->getPositionX() + i]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(grid[hero->getPositionY()][hero->getPositionX() + i]);
                        m->setHealthPoints(m->getHealthPoints() - hero->getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                        return;
                    }
                }
                cout<<"nothing was hit!"<<endl;

            }

            if(direction == 'd')
            {
                for(int i = 1; i <= hero->getWeapon()->getRange(); i++)
                {
                    if(hero->getPositionX() + i > 14)
                    {
                        cout<<"nothing was hit!"<<endl;
                        return;
                    }
                    if(grid[hero->getPositionY()][hero->getPositionX() + i]->getType() == 'T' || grid[hero->getPositionY()][hero->getPositionX() + i]->getType() == 'G')
                    {
                        Monster *m=static_cast<Monster*>(grid[hero->getPositionY()][hero->getPositionX() + i]);
                        m->setHealthPoints(m->getHealthPoints() - hero->getWeapon()->getDamage());

                        cout<<"A monster was hit!"<<endl;
                        return;
                    }
                }
                cout<<"nothing was hit!"<<endl;
            }
        }

    }

    void Game::playRound()
    {
        while(true)
        {
            int input;
            cin>>input;

            if(input == 1)
            {
                cout<<"W to move up, A to move left, S to move down, D to move right"<<endl;
                char direction;
                cin>>direction;
                move(*hero, direction);
            }
            if(input == 2)
            {
                cout<<"W to shoot up, A to shoot left, S to shoot down, D to shoot right"<<endl;
                char direction;
                cin>>direction;
                FireGun(direction);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            if(input == 3)
            {
                cout<<"Used gun's special!"<<endl;
                useGunSpecial();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            if(input == 4)
            {
                cout<<"Used hero's special!"<<endl;
                if(hero->getType() == 'M')
                {
                    MedicHero* m = static_cast<MedicHero*>(hero);
                    m->useSpecial();
                }
                else
                {
                    DemolitionHero* dm = static_cast<DemolitionHero*>(hero);
                    dm->useSpecial();
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));

            }

            round++;
            updateMap();
            checkGameOver();

        }
    }

    int Game::checkGameOver(){
        if(hero->getHealthPoints() <= 0)
        {
            cout<<"the hero is dead, You lost"<<endl;
            exit(0);
        }
        else
        {
            bool flag = true;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    if(grid[i][j]->getType() == 'T' || grid[i][j]->getType() == 'T')
                    {
                        flag = false;
                    }
                }
            }

            if(flag)
            {
                cout<<"You killed all the zombies, You Win!"<<endl;
                exit(0);
            }
            else
            {
                return 0;
            }
        }
    }

    void Game::updateMap()
    {
        for(int i = 0; i<15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                if(grid[i][j]->getType() == 'T' || grid[i][j]->getType() == 'G')
                {
                    Monster *m=static_cast<Monster*>(grid[i][j]);
                    if(m->getHealthPoints() <= 0)
                        {
                            grid[i][j] = new Object('.');
                        }
                }
            }
        }

        if(round % 3 == 0)
        {
            for(int i = 0; i<15; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    if(grid[i][j]->getType() == 'G')
                    {
                        GhostMonster *m = static_cast<GhostMonster*>(grid[i][j]);
                        cout<<m->isVisibleOnMap()<<endl;
                        m->setIsVisible(!m->isVisibleOnMap());
                    }
                }
            }
        }

        if(round % 20 == 0)
        {

            bool flag = true;
            while(flag)
            {
                int newX = rand() % 15;
                int newY = rand() % 15;
                if(grid[newX][newY]->getType() == '.')
                {
                    int monsterHPRange = 10;
                    int monsterHPMin = 60;
                    int hp = (rand() % monsterHPRange + 1) * monsterHPMin;  // Random multiple of 10 between 60 and 150
                    grid[newX][newY] = new TankMonster('T', 0, 0, 2*hp,hp);
                    flag = false;
                }
            }


            flag = true;
            while(flag)
            {
                int newX = rand() % 15;
                int newY = rand() % 15;
                if(grid[newX][newY]->getType() == '.')
                {
                    int monsterHPRange = 10;
                    int monsterHPMin = 60;
                    int hp = (rand() % monsterHPRange + 1) * monsterHPMin;  // Random multiple of 10 between 60 and 150
                    grid[newX][newY] = new GhostMonster('G', 0, 0, hp);
                    flag = false;
                }
            }
        }

        system("cls");
        cout<<"Round: "<<round<<endl;
        cout<<"A: Ammo, P: Potion, T: Tank Monster, G: Ghost Monster"<<endl;
        cout<<endl;
        cout<<*hero<<endl;
        showMap();
        cout<<endl;


        if(!valid)
        {
            cout<<"Invalid move!"<<endl;
            cout<<endl;
            valid = true;
        }

        cout<<"1 to move, 2 to shoot, 3 to use the gun's special ability, 4 to use the hero's special ability"<<endl;
    }



    void Game::move(Hero& h1 , char direction)
    {
        Object * o = new Object('.');

        int x = h1.getPositionX();
        int y = h1.getPositionY();

        switch (direction)
        {
            case 'w' :
                if(y>0)
                {
                    if(grid[y-1][x]->getType()!='G' && grid[y-1][x]->getType()!='T'&& y>0) {

                        h1.setPosition(x, y-1);

                        if (grid[y-1][x]->getType()=='A'){
                            Ammo *A = static_cast<Ammo *>(grid[y-1][x]);

                            cout<<A->getBullets()<<endl;
                            if(grid[y][x]->getType() == 'D')
                            {
                                DemolitionHero* dm = static_cast<DemolitionHero*>(&h1);
                                *dm + *A;
                            }
                            if(grid[y][x]->getType() == 'M')
                            {
                                MedicHero* m = static_cast<MedicHero*>(&h1);
                                *m + *A;
                            }

                        }
                        else if (grid[y-1][x]->getType()=='P'){
                            Potion *P = static_cast<Potion *>(grid[y-1][x]);
                            h1 + *P;
                        }
                        grid[y][x] = o;
                        grid [y-1][x] = &h1;
                    }

                    else if(grid[y-1][x]->getType()=='G' || grid[y-1][x]->getType()=='T') {
                        Monster *m = static_cast<Monster *>(grid[y - 1][x]);
                        h1 - *m;
                    }
                }
                else
                {
                    valid = false;
                    round--;
                }

            break;

            case 's' :
                if(y<14)
                {
                    if(grid[y+1][x]->getType()!='G' && grid[y+1][x]->getType()!='T'&& y<14) {

                        h1.setPosition(x, y+1);

                        if (grid[y+1][x]->getType()=='A'){
                            Ammo *A = static_cast<Ammo *>(grid[y+1][x]);
                            cout<<A->getBullets()<<endl;

                            if(grid[y][x]->getType() == 'D')
                            {
                                DemolitionHero* dm = static_cast<DemolitionHero*>(&h1);
                                *dm + *A;
                            }
                            if(grid[y][x]->getType() == 'M')
                            {
                                MedicHero* m = static_cast<MedicHero*>(&h1);
                                *m + *A;
                            }

                        }
                        else if (grid[y+1][x]->getType()=='P'){
                            Potion *P = static_cast<Potion *>(grid[y+1][x]);
                            h1 + *P;
                        }
                        grid [y+1][x] = &h1;
                        grid[y][x] = o;
                    }

                    else if(grid[y+1][x]->getType()=='G' || grid[y+1][x]->getType()=='T') {
                        Monster *m = static_cast<Monster *>(grid[y + 1][x]);
                        h1 - *m;
                    }
                }
                else
                {
                    valid = false;
                    round--;
                }

            break;

            case 'a' :
                if(x>0)
                {
                    if(grid[y][x-1]->getType()!='G' && grid[y][x-1]->getType()!='T'&& x>0) {

                        h1.setPosition(x-1,y);

                        if (grid[y][x-1]->getType()=='A'){

                            Ammo *A = static_cast<Ammo *>(grid[y][x-1]);
                            cout<<A->getBullets()<<endl;

                            if(grid[y][x]->getType() == 'D')
                            {
                                DemolitionHero* dm = static_cast<DemolitionHero*>(&h1);
                                *dm + *A;
                            }
                            if(grid[y][x]->getType() == 'M')
                            {
                                MedicHero* m = static_cast<MedicHero*>(&h1);
                                *m + *A;
                            }
                        }
                        else if (grid[y][x-1]->getType()=='P'){
                            Potion *P = static_cast<Potion *>(grid[y][x-1]);
                            h1 + *P;
                        }
                        grid [y][x-1] = &h1;
                        grid[y][x] = o;
                    }

                    else if(grid[y][x-1]->getType()=='G' || grid[y][x-1]->getType()=='T') {
                        Monster *m = static_cast<Monster *>(grid[y][x-1]);
                        h1 - *m;
                    }
                }
                else
                {
                    valid = false;
                    round--;
                }

                break;

            case 'd' :
                if(x < 14)
                {
                    if(grid[y][x+1]->getType()!='G' && grid[y][x+1]->getType()!='T'&& x<14) {

                        h1.setPosition(x+1,y);

                        if (grid[y][x+1]->getType()=='A'){

                            Ammo *A = static_cast<Ammo *>(grid[y][x+1]);

                            if(grid[y][x]->getType() == 'D')
                            {
                                DemolitionHero* dm = static_cast<DemolitionHero*>(&h1);
                                *dm + *A;
                            }
                            if(grid[y][x]->getType() == 'M')
                            {
                                MedicHero* m = static_cast<MedicHero*>(&h1);
                                *m + *A;
                            }
                        }
                        else if (grid[y][x+1]->getType()=='P'){
                            Potion *P = static_cast<Potion *>(grid[y][x+1]);
                            h1 + *P;
                        }
                        grid[y][x] = o;
                        grid [y][x+1] = &h1;
                    }

                    else if(grid[y][x+1]->getType()=='G' || grid[y][x+1]->getType()=='T') {
                        Monster *m = static_cast<Monster *>(grid[y][x+1]);
                        h1 - *m;
                    }
                }
                else
                {
                    valid = false;
                    round--;
                }

                break;

            default: cout<<"Please enter a valid character"<<endl;
        }
    }



int main() {
    Game game;
    game.startGame();

    return 0;
}

