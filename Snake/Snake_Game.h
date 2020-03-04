#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Snake_Game
{
	private:
		int snake_x, snake_y, score, best_score;
		int tail_x[100], tail_y[100], tail_length;
		int width, height;
		int fruit_x, fruit_y;
		bool game_over;
		enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN } dir;

		void setGame();
		void drawMap();
		void move();
		void getKey();
		void setFruit();
		void mainMinu();
		void instructions();
		void setWindow();
		bool playAgain();
		void saveBestScore();
		void getBestScore();

	public:
		Snake_Game();
		void play();	
};

