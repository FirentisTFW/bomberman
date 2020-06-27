#include "bonus.h"

Bonus::Bonus(int _posX, int _posY, char _type) {
  
    type = _type;
    posX = _posX;
    posY = _posY;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::White);
}

Bonus::~Bonus() {}

char Bonus::shouldBonusBeCreated() {                    
    char type = '0';                                              // '0' means no bonus will be created

    int randomNumber = rand() % 100 + 1;                          // 1 - 100

    if(randomNumber < 21) type = 'r';                             // 20% chance for increased range
    else if(randomNumber < 31 && randomNumber > 20) type = 'h';   // 10% chance for shield
    else if(randomNumber < 41 && randomNumber > 35) type = 'l';   // 5% chance for additional live
    else if(randomNumber < 71 && randomNumber > 51) type = 'b';   // 20% chance for additional bomb
    else if(randomNumber < 85 && randomNumber > 70) type = 'l';   // 15% chance for increased speed

    std::cout << randomNumber << " " << type << std::endl;

    return type;
}
