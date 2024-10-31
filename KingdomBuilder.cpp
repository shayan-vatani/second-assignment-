using namespace std;
#include <iostream>
#include <vector>

class KingdomBuilder {
private:
    string kingdomName;
    int population;
    int resources;
    vector<string> conqueredKingdoms;
    int level;
    int armyStrength;
    void calculateLevel() {
        level = population / 500;
    }
    void AddResources() {
        resources = (population / 500) * 50;
    }
    void armyStrenghtIncrement() {
        armyStrength = armyStrength + level * level + (population / 100);
    }
public:
    KingdomBuilder() : level(0), population(0), resources(0), armyStrength(0) {}
    KingdomBuilder( int population , int resources,int armyStrength):level(0),
        population(population),resources(resources),armyStrength(armyStrength),conqueredKingdoms() {
       
        calculateLevel();
        AddResources();
        armyStrenghtIncrement();
    }
    void display(ostream&o){
        o <<"name : " << kingdomName << " , population : " << population << " , Level : " << level << " , resources : " 
            << resources << " , army strength : " << armyStrength;
        for (const auto & item : conqueredKingdoms) {
            o << item << " ";
        }
        o << endl;

    }
    void changeName(const string &name) {
        if (!conqueredKingdoms.empty())
        {
            cout << "you can't change the name because it has not conquered yet ";
        }
        else {
            kingdomName = name;
        }
    }
    int AddPopulation(int pop) {
        population += pop;
        return population;
    }
    void Fight(KingdomBuilder& opnnt) {
        srand(time(0));
        int randomNum = rand()%2;
        int AdjustedArmyStrength = armyStrength+level*randomNum;
        int oponent_AdjustedArmyStrength = opnnt.armyStrength + opnnt.level * randomNum;
        if (AdjustedArmyStrength > oponent_AdjustedArmyStrength) {
            conqueredKingdoms.push_back(opnnt.kingdomName);
            level += opnnt.level;
            opnnt.afterWar();
            cout << kingdomName << " won against " << opnnt.kingdomName << endl;
        }
        else {
            opnnt.conqueredKingdoms.push_back(kingdomName);
            opnnt.level += level;
            afterWar();
            cout << opnnt.kingdomName << " won against " << kingdomName << endl;
        }

    }
    void AddPopulation(int &newPop) {
        population += newPop;
        calculateLevel();
        AddResources();
        armyStrenghtIncrement();
    }
    void afterWar() {
        population = population / 50;
        resources = resources / 50;
        armyStrength = 0;
        conqueredKingdoms.clear();
    }
    void read(istream& i) {
        cout << "enter your name (it should be unique name ) : ";
        cin >> kingdomName;
        cout << "\nplease enter the population : ";i >> population;
        cout << "\nplease enter the armyStrength : ";i >> armyStrength;
        cout << "\nplease enter the resources : ";i >> resources;
        cout << endl;
        calculateLevel();
        AddResources();
        armyStrenghtIncrement();
    }
};
istream& operator>>(istream& i, KingdomBuilder& k) {
    k.read(i);
    return i;
}
ostream& operator<<(ostream& o, KingdomBuilder& n) {
    n.display(o);
    return o;
}
int main()
{
    string stop;
    while (stop != "no") {

    srand(time(0)); 
    cout << "**** welcome to the Kingdom Builder game ***** \n";
    cout << "First opponent: \n";
    int population = 0, resources = 0, armyStrength = 0;
    KingdomBuilder s1(population, resources, armyStrength);
    cin >> s1;

    cout << "Second opponent: \n";
    int population_2 = 0, resources_2 = 0, armyStrength_2 = 0;
    KingdomBuilder s2(population_2, resources_2, armyStrength_2);
    cin >> s2;
    cout << s1 << "\n" << s2;
    cout << "First opponent info: \n" << s1;
    cout << "Second opponent info: \n" << s2;

    cout << "\nSimulating a fight between the two opponents...\n";
    s1.Fight(s2);
  
    cout << "\nUpdated state of the first opponent: \n" << s1;
    cout << "Updated state of the second opponent: \n" << s2;
    string new_name;
    cout << "choose a name to change the kingdom name \n";
    cin >> new_name;
    int choose_the_kingdom;

    while (true) {

    cout << "Choose which kingdom to rename (1 for first kingdom, 2 for second kingdom): ";
    cin >> choose_the_kingdom;
    if (choose_the_kingdom ==1)
    {
        s1.changeName(new_name);
        break;
    }
    else if (choose_the_kingdom==2) {
        
        s2.changeName(new_name);
        break;
    }
    else {
        cout << "try to choose 1 for first kingdom  or 2 for second kingdom";
    }
 }
    cout << "\nFinal state of the kingdoms:\n";
    cout << s1 << endl;
    cout << s2 << endl;
    cout << "game is over \n";
    cout << "would you like to play again \n";
    cout << "yes or no !!!\n";
    cin >> stop;
    }
}