#include "Bats.hpp"

Bats::Bats(int itemType, SDL_Renderer* renderer) : Collectibles(itemType) {
    // Constructor
    // Initialize other attributes such as icon, position, action, etc.
    
}

Bats::~Bats() {
    // Destructor
    
}

void Bats::addToScore() {
    // add to the score based on how many bats collected
    // Call the base class's addToScore function if needed
    Collectibles::addToScore(); // base class's addToScore function

    
    // if (checkCollision(playerRect)) {
    //     score += 15;
   
}

