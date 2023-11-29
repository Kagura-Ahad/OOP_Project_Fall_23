
#include "player.hpp"
#include "drawing.hpp"
#include "game.hpp"

int main(int argc, char *argv[]){
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    game.initVampire(Drawing::gRenderer);
    game.run();
    game.close();

    return 0;
}

char* concatStrings(char* str1, char* str2)
{
    int str1Length{0}, str2Length{0};

    while(str1[str1Length]!='\0'){
        str1Length++;
    }

    while(str2[str2Length]!='\0'){
        str2Length++;
    }

    char* result = new char[str1Length+str2Length+1];

    for(int i=0; i<str1Length; i++){
        result[i] = str1[i];
    }

    for(int i=0; i<str2Length; i++){
        result[str1Length+i] = str2[i];
    }

    result[str1Length+str2Length] = '\0';

    return result;
}