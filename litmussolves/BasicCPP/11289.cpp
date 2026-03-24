#include <iostream>
#include <string>
using namespace std;

class Player {
   friend class PlayerChanger;
private:
   string name;
   int health;
   int level;

public:
   Player(string pname, int phealth, int plevel):
      name(pname), health(phealth), level(plevel)
   { }

   friend void print_player_information(const Player& p); 
};

class PlayerChanger {
public:
   void set_player_name(Player &p, string changed_name) {
      p.name = changed_name;
   }
};

void print_player_information(const Player& p) {
   cout << p.name << " " << p.health << " " << p.level << endl;
}

int main()
{
 string name;
 int hp, xp;
 cin >> name >> hp >> xp;

 Player hero( name,hp,xp );
 print_player_information(hero);

 PlayerChanger pc;
 string another_name;
 cin >> another_name;

 pc.set_player_name(hero, another_name);
 print_player_information(hero);
}
