 my_tetris  
 
Use :  

  SDL2_mixer-2.6.3  
  
  SDL2_image-2.6.2  
  
  SDL2_ttf-2.20.2  
  
  SDL2_2.6.2  
  
Compile and run:  

  Requirements:  
  
    CodeBlock  
    
    MinGW-w64  
    
  Clone this repo to your computer.  
  
  Create a SDL2 project.  
  
  Add files .h .cpp .dll to project.  
  
  Click compile and run.  
  
How to play:  

  game will random generate 1 in 7 tetromino per time.   
  
  A row of board with full block will disappear and you get score.  
  
  If board is fulled with blocks in height, you lose.  
  
  Your mission is to arrange blocks right away and get more and more score.  
  
Control:  

  You can see in game :))  
  
More infomation about code:  

    Create a board game with height(20), width(10) and an array[height][width] to show the type of each part of the board.  

    Each tetromino is formed by 4 squares ( 7 types of tetromino) and is performed in the game by a position array[4].  

    Whenever a tetromino moves, we change the position of each square of it.  

    If the tetromino can't move more, we set the type of board, create a new tetromino and update the game ( score, speed, level,...).  

    Render the game by drawing the tetromino that is moving now and drawing the board ( type of board <=> 1 in 7 tetrominos).    
    
    
    
    
  
  
