class Entity {
public:
    Entity(const string& name) : name(name) {}
    virtual ~Entity() {}
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }
    void SayName() const {
        cout << "My name is " << name << endl;
    }
protected:
    string name;
};
class Warrior : virtual public Entity {
public:
    Warrior(const string& name, int stamina)
        : Entity(name), stamina(stamina), isAggressiveStance(true) {
    }
    int getStamina() const { return stamina; }
    void setStamina(int newStamina) {
        if (newStamina >= 0) stamina = newStamina;
    }
    void UseSword() {
        if (isAggressiveStance) {
            stamina -= 10; 
            cout << format("{} AGGRESSIVE STANCE! ", name) << endl;
        }
        else {
            stamina -= 5; 
            cout << format("{} DEFENSIVE STANCE! ", name) << endl;
        }
        isAggressiveStance = !isAggressiveStance;
    }
protected:
    int stamina;
    bool isAggressiveStance;
};
class Mage : virtual public Entity {
public:
    Mage(const string& name, int mana)
        : Entity(name), mana(mana), isOffensiveMode(true) {
    }
    int getMana() const { return mana; }
    void setMana(int newMana) {
        if (newMana >= 0) mana = newMana;
    }
    void CastSpell() {
        if (isOffensiveMode) {
            mana -= 12; 
            cout << format("{} OFFENSIVE SPELLCASTING! ", name) << endl;
        }
        else {
            mana -= 6;  
            cout << format("{} SUPPORT SPELLCASTING! ", name) << endl;
        }
        isOffensiveMode = !isOffensiveMode;
    }
protected:
    int mana;
    bool isOffensiveMode;
};
class Spellblade : public Warrior, public Mage {
public:
    Spellblade(const string& name, int stamina, int mana)
        : Entity(name), Warrior(name, stamina), Mage(name, mana) {
    }
    void ShowStats() const {
        cout << format(" {} Stamina: {} Mana: {} ",
            getName(), getStamina(), getMana()) << endl;
    }
};
int main() {
    Spellblade hero1("Elvin", 20, 30);
    Spellblade hero2("Valik", 15, 40);
    cout << " BATTLE " << endl << endl;
    hero1.SayName();
    hero2.SayName();
    cout << endl;
    hero1.ShowStats();
    hero2.ShowStats();
    int round = 1;
    while (hero1.getStamina() > 0 && hero1.getMana() > 0 &&
        hero2.getStamina() > 0 && hero2.getMana() > 0)
    {
        cout << format("Round {} ", round) << endl;
        if (round % 2 != 0) {
            hero1.CastSpell();
            hero2.UseSword();
        }
        else {
            hero1.UseSword();
            hero2.CastSpell();
        }
        cout << endl;
        round++;
    }
    cout << "FINAL" << endl;
    hero1.ShowStats();
    hero2.ShowStats();
    return 0;
}
