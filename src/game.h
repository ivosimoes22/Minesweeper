//Macros for sprites array

const int TILE_0 = 0;
const int TILE_1 = 1;
const int TILE_2 = 2;
const int TILE_3 = 3;
const int TILE_4 = 4;
const int TILE_5 = 5;
const int TILE_6 = 6;
const int TILE_7 = 7;
const int TILE_8 = 8;
const int TILE_FLAG = 9;
const int TILE_MINE = 10;
const int TILE_UNREVEALED = 11;

/* Tamanho dos quadrados vai ser 40x40 pixeis
logo o tamanho da janela vai variar de acordo com
a dimensão que o jogador escolher */

const int square_dim = 40;

class Graphics
{
    public:
        //Constructor
        Graphics(int n_squares);
        void initGrid();
        void drawGrid(sf::RenderWindow& window);
        void newGameButton(sf::RenderWindow& window);
        void loadSprites();
        void loadfont();
        void setNewGameText();
        void setLoseWinText();
        void drawLoseText(sf::RenderWindow& window);
        void drawWinText(sf::RenderWindow& window);
        void winText(sf::RenderWindow& window);
        void drawNewGameText(sf::RenderWindow& window);
        void drawInitTiles(sf::RenderWindow& window);
        void drawUnrevealedSprites(sf::RenderWindow& window, int x, int y);
        void drawNumber(sf::RenderWindow& window, int x, int y, int tile);
        void drawMines(sf::RenderWindow& window, int x, int y);
        void drawFlags(sf::RenderWindow& window, int x, int y);
        int newGameMouse(sf::RenderWindow& window);
    
        //Destructor
        ~Graphics();

    private:
        int n_squares;
        sf::Vertex *lines;
        sf::Texture pic_arr[12];
        sf::Sprite sprite_arr[12];
        sf::Font font;
        sf::Text new_game_str, new_game_str1, lose_game_str, win_game_str;
    
};

class Cell
{
    public:
        // Constructor
        Cell(bool mine, bool revealed)
        {
            this->is_mine = mine;
            this->revealed = revealed;
        }

        //Helper functions
        bool isMine() {
            return is_mine; }

        bool isRevealed() {
            return revealed; }

        bool isFlagged() {
            return is_flagged; }

        void setMine() {
            this->is_mine = true; }
        
        void deMine() {
            this->is_mine = false; }

        void setFlag() {
            this->is_flagged = true; }
        
        void deFlag() {
            this->is_flagged = false; }

        void reveal() {
            this->revealed = true; }

        void unreveal() {
            this->revealed = false; }

    private:
        bool is_mine;
        bool is_flagged;
        bool revealed;
};

class Game
{
    public:
        //Constructor
        Game(int n_squares);

        void setDimension(int dim);
        void randomMines();
        void printMines();
        void getMousecoor(sf::RenderWindow& window);
        void checkTile(sf::RenderWindow& window, Graphics* graphics);
        void insertFlag(sf::RenderWindow& window, Graphics* graphics);
        int checkAround(sf::RenderWindow& window, Graphics* graphics, int x, int y);
        int checkLose();
        int checkWin();
        void endGame(sf::RenderWindow& window, Graphics* graphics);
        void revealAllMines(sf::RenderWindow& window, Graphics* graphics);
        void newGame();

        void gameEnd() {
            game_end = true;
        }

        bool checkGameStart() {
            return game_end;
        }

        void resetGame() {
            game_end = false;
        }

    private:
        int dimension;
        int total_mines = 50;
        bool game_end = false;

        //Coordenadas do rato normalizadas aos quadrados
        sf::Vector2i nMouse;
        
        //Matriz de celulas
        std::vector< std::vector<Cell> > board;

};