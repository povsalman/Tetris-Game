/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
using namespace sf;

void fallingPiece(float& timer, float& delay, int& colorNum, int& level){

    if (timer>delay ){
    
	for (int i=0;i<4;i++){
            point_1[i][1]+=1;                   //How much units downward
       
       }
    
    if(level == 1){					// For level 1
        if (!anamoly()){
        	for( int i=0; i<4; i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
             
              colorNum = 1+rand()%7;
              int n=rand()%4;
              
        	delay = 0.3;         
     		
                for (int i=0;i<4;i++){

                    point_1[i][0] = BLOCKS4[n][i] % 2 ;
                    point_1[i][1] = BLOCKS4[n][i] / 2 ;
                    
                }
	
        }
        delay = 0.3;
	}
    

    if(level == 2){					// For level 2
        if (!anamoly()){
        	for( int i=0; i<4; i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
             
              colorNum = 1+rand()%7;
              int n=rand()%8;
              delay = 0.13;         
     		
                for (int i=0;i<4;i++){

                    point_1[i][0] = BLOCKS[n][i] % 2 ;
                    point_1[i][1] = BLOCKS[n][i] / 2 ;
                    
                }
	
        }

        delay = 0.13;
	}
        
        timer=0;

    }
    
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

//For movement
void movement(int& delta_x)
{

	for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][0]+=delta_x;                   //How much units left or right
            shadow[i][0]+=delta_x;
       
       
       
       }
	
	delta_x = 0;					//To avoid jumping to left and right boundaries
	
	if(!anamoly())
	{
	 for (int i=0;i<4;i++){
            point_1[i][0]=point_2[i][0];
            point_1[i][1]=point_2[i][1];}		//For left and right boundary checks
	}
	
}

//For Rotation

void rotation(bool& rotate){

	int xcentre = 0;
	int ycentre = 0;
	
	if(rotate == true){
	
		for(int j=0;j<4 ; j++){
		
			xcentre = point_1[j][0] - point_1[1][0];		//finding centre x wrt the common block 2
			ycentre = point_1[j][1] - point_1[1][1];		//finding centre y wrt the common block 2
		
			point_1[j][0] = point_1[j][0] - xcentre - ycentre;	 //rotation formula and using the centres
			point_1[j][1] = point_1[j][1] - ycentre + xcentre;
		
		}
				
		rotate = false;

	}
	if(!anamoly())
	{
	 for (int i=0;i<4;i++){
            point_1[i][0]=point_2[i][0];
            point_1[i][1]=point_2[i][1];}		//For left and right boundary checks
	}
}

//For checking Line

void checkLine(int& score){ 

for (int i = M-1; i > 0; i--) { 			//For-loop for checking each row from M-1 = 19 till M = 1
	bool clearline = 1;
	
	
	for (int j = 0; j < N; j++) { 		//For-loop for checking each column of that row

		if (gameGrid[i][j] == 0) { 		//if any coordinate is empty, then update clearline = 0 and iterate for new row
			clearline = 0;
			break; 
			} 
	} 

	
	if (clearline == 1) { 						//if clearline isnt updated to 0, then line is complete
		
		 
		for (int k = i; k > 0; k--) {				// k here is same as i in the parent loop i.e. rows
			for (int j = 0; j < N; j++){ 			// For-loop for checking each column of that row
				gameGrid[k][j] = gameGrid[k-1][j]; 	//At this point [k][j] , place blocks that are directly above it
				
			}
				
		}
	
	score += 10;
	
	}
	
		
}


}
//For New game

void checkLine(){ 

for (int i = M-1; i > 0; i--) { 			//For-loop for checking each row from M-1 = 19 till M = 1
	bool clearline = 1;
	
	for (int j = 0; j < N; j++) { 		//For-loop for checking each column of that row

		if (gameGrid[i][j] == 0) { 		
			for (int k = i; k > 0; k--) {				
				for (int j = 0; j < N; j++){ 			
				gameGrid[k][j] = gameGrid[k-1][j]; 	
				
				}
				
			}
		} 
	} 
	
		
}

}

// Saves Highscore
void high(int& score, string& name){
fstream myFile;
myFile.open("highscore.txt", std::ios::out);  //writing into file
if(myFile.is_open()){

	

	myFile << name << "\n" ;
	myFile << score << "\n" ;
	myFile.close();

}



}







///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
