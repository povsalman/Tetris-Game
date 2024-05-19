/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;
int main(){
    srand(time(0));
    Texture obj1, obj2, obj3, obj4 , obj5, obj6, obj7, obj8, obj9, obj10, obj11, obj12;
    
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/scrollc.png");
    obj5.loadFromFile("img/gameover.png");
    obj6.loadFromFile("img/pscrollc.png");
    obj7.loadFromFile("img/start.png");
    obj8.loadFromFile("img/exit.png");
    obj9.loadFromFile("img/highscore.png");
    obj10.loadFromFile("img/newgame.png");
    obj11.loadFromFile("img/level1.png");
    obj12.loadFromFile("img/level1.png");
   
   
   
    Sprite sprite(obj1), background(obj2), frame(obj3), scroll(obj4) , gameover(obj5), pscroll(obj6), start(obj7), exit(obj8), highscore(obj9), newgame(obj10), level1(obj11), level2(obj12);
    
	int score = 0;
	bool paused = false;
	int menu = 0;
	bool gover = false;
	int level = 1;
	int xbutton = 0;
	int ybutton = 0;  
	string name = "empty";
	bool space = false;
	bool restart = true;
    
	int delta_x=0, colorNum=1;
	float timer=0, delay=0.3;
	bool rotate=0;
    
    	sf::Font open_sans;
	open_sans.loadFromFile("font/opensans-light.ttf");

    
    
    Clock clock;
    
    cout << "Enter Your Name:  " << endl;
	cin >> name;
    cout << "Welcome To Tetris  " << name << "!" << endl;	
	
	
    while(restart == true){	
	restart = false;
    if(name != "empty" ){
    
    RenderWindow window(VideoMode(320, 480), title);
    checkLine();							//clear the grid initially
    
   //Music
    sf::Music music;
        if (!music.openFromFile("music/TetrisTheme.ogg"))
            return -1; // error
     
        music.play();
        music.setLoop(true);
    
 
    
    while (window.isOpen()){
    
    	xbutton = 0;
	ybutton = 0; 
	space = true;
   
    
 
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        

        //---Event Listening Part---// 
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            
            if (e.type == Event::Closed){                   //If cross/close is clicked/pressed                          
       	high(score,name);
       	window.close();				//Opened window disposes
              }
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
           	 else if (e.key.code == Keyboard::H) {   
          		 paused = !paused;
          		 menu += 1;
          		 }
          	 else if (e.key.code == Keyboard::Num1 || e.key.code == Keyboard::Numpad1)    
          		 level = 1;
          	else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2)    
          		 level = 2; 
        
        }


 	if (Keyboard::isKeyPressed(Keyboard::Down))	     //Just another way to detect key presses without event listener
          delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
	 
	if (Keyboard::isKeyPressed(Keyboard::Space)){	     //Just another way to detect key presses without event listener
          delay=0.0000000000000007; 
	}



       if (e.type == sf::Event::MouseButtonPressed)
	{
    		if (e.mouseButton.button == sf::Mouse::Left)
   	 	{
    		xbutton = e.mouseButton.x;						//to get x y coordinates of cursor
    		ybutton = e.mouseButton.y;
    
    		}	
	}

	 
	if (xbutton > 101 && xbutton < 207 && ybutton > 225 && ybutton < 250){              //for exit button      
                high(score,name);
                window.close();
         	       
        }        
 
 	if (xbutton > 101 && xbutton < 207 && ybutton > 185 && ybutton < 209) {                //for Start button  
                paused = true;
                menu+=1;
	   
	}

	
	if (xbutton > 224 && xbutton < 264 && ybutton > 208 && ybutton < 228) {                   //for level 1 button
              level = 1;  
	   
	}
	
	
	if (xbutton > 224 && xbutton < 264 && ybutton > 274 && ybutton < 315) {                  //for level 2 button
              level = 2;  
	   
	}
	
	if (xbutton > 101 && xbutton < 207 && ybutton > 265 && ybutton < 290) {    		//for highscore button
	     
	      fstream myFile;              
              myFile.open("highscore.txt", ios::in);  //read
              if(myFile.is_open()){
              string line;
              cout<< "LAST RECORD: \n" ;
              while (getline(myFile, line)){
              	
              cout << line << endl;
           
              }
              myFile.close();
              }  
	   
	}
	
	if (xbutton > 101 && xbutton < 207 && ybutton > 305 && ybutton < 330) {                  
              window.close();
              restart = true;
               
	   
	}


       }

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
       
        
        if (paused == true){
        
        
	for(int j=0; j< N; j++){				//For Gameover Detection
		if (gameGrid[0][j] != 0){
			menu = 2;
			paused = false;
			gover = true;
		}
	}

        fallingPiece(timer, delay, colorNum, level);          //Example: fallingPiece() function is called here
        movement(delta_x);					// movement checks left and right movement
        rotation(rotate);					// rotation checks the rotation
        checkLine(score);					// for checking line and score
        }
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////




//for displaying score on screen

std::ostringstream ss; 		//string buffer to convert numbers to string
ss << "Score \n"  << score;		// put float into string buffer


sf::Text my_text;
my_text.setFont(open_sans);
my_text.setPosition(230,250);
my_text.setCharacterSize(18);
my_text.setString(ss.str()); 		//ss.str() converts the string buffer into a regular string 


// For Displaying scroll
sf::Texture texture;
if(!texture.loadFromFile("img/scrollc.png")){
	return 0;
}

scroll.setTexture(texture);
scroll.setPosition(sf::Vector2f(20,80));

// For Displaying Pause
sf::Texture texture2;
if(!texture2.loadFromFile("img/pscrollc.png")){
	return 0;
}

pscroll.setTexture(texture2);
pscroll.setPosition(sf::Vector2f(20,80));



// For Displaying Gameover scroll
sf::Texture texture3;
if(!texture3.loadFromFile("img/gameover.png")){
	return 0;
}

gameover.setTexture(texture3);
gameover.setPosition(sf::Vector2f(50,40));



// For Displaying Start
sf::Texture texture4;
if(!texture4.loadFromFile("img/start.png")){
	return 0;
}

start.setTexture(texture4);
start.setPosition(sf::Vector2f(95,180));



// For Displaying Exit
sf::Texture texture5;
if(!texture5.loadFromFile("img/exit.png")){
	return 0;
}

exit.setTexture(texture5);
exit.setPosition(sf::Vector2f(95,220));


// For Displaying Highscores
sf::Texture texture6;
if(!texture6.loadFromFile("img/highscore.png")){
	return 0;
}

highscore.setTexture(texture6);
highscore.setPosition(sf::Vector2f(95,260));



// For Displaying New game
sf::Texture texture7;
if(!texture7.loadFromFile("img/newgame.png")){
	return 0;
}

newgame.setTexture(texture7);
newgame.setPosition(sf::Vector2f(95,300));


// For Displaying Level 1
sf::Texture texture8;
if(!texture8.loadFromFile("img/level1.png")){
	return 0;
}

level1.setTexture(texture8);
level1.setPosition(sf::Vector2f(210,190));


// For Displaying Level 2
sf::Texture texture9;
if(!texture9.loadFromFile("img/level2.png")){
	return 0;
}

level2.setTexture(texture9);
level2.setPosition(sf::Vector2f(210,260));




        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
     
        //---The Final on Which Everything is Drawn Over is Loaded---//
       
        
       
        window.draw(frame);
        window.draw(my_text);				//this will display the score
        if(menu%2 == 0 && gover == true) {		// when game over is true
        
        window.draw(scroll);
        window.draw(gameover);
        window.draw(newgame);
        window.draw(highscore);
        window.draw(exit);
        window.draw(level1);
        window.draw(level2);
        
        
        }
        
        else if(menu%2 == 0 && gover == false) {		// for pause and start menu
        
        window.draw(pscroll);
        window.draw(start);
        window.draw(newgame);
        window.draw(highscore);
        window.draw(exit);
        window.draw(level1);
        window.draw(level2);
 

        }
        
        
        
        
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    
    
    }
    }
    }
    return 0;
}
