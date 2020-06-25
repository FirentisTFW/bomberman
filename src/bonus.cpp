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

    if(randomNumber < 21) type = 's';                             // 20% chance for speed bonus
    else if(randomNumber < 31 && randomNumber > 20) type = 'h';   // 10% chance for shield
    else if(randomNumber < 41 && randomNumber > 35) type = 'l';   // 5% chance for additional live

    std::cout << randomNumber << " " << type << std::endl;

    return type;
}
