#ifndef TETRIS__H
#define TETRIS__H

#include "Header.h"
#include "Tetromino.h"

const int FRAMES_PER_GIRDCELL[31] = {0, 48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
const int LINES_BEFORE_LEVEL_INCREASES[31] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 200, 200, 200, 1000000000};

enum GameStatus
{
    GAME_PLAY,
    GAME_PAUSE,
    GAME_OVER
};

class Tetris
{
private:
    static const int MAP_HEIGHT = 22;
    static const int MAP_WIDTH = 12;
    static const int NEXT_HEIGHT = 12;
    static const int NEXT_WIDTH = 8;
    static const int HOLD_WIDTH = 8;
    static const int HOLD_HEIGHT = 6;
    static const int NUM_NEXT_TETROMINO = 3;
    static const int DELAY_CLEAR_LINE = 26;
    Block blockI = Block(0, 0, BLOCK_TYPE_I);
    Block blockJ = Block(0, 0, BLOCK_TYPE_J);
    Block blockL = Block(0, 0, BLOCK_TYPE_L);
    Block blockO = Block(0, 0, BLOCK_TYPE_O);
    Block blockS = Block(0, 0, BLOCK_TYPE_S);
    Block blockT = Block(0, 0, BLOCK_TYPE_T);
    Block blockZ = Block(0, 0, BLOCK_TYPE_Z);
    Block blockEmpty = Block(0, 0, BLOCK_TYPE_EMPTY);
    Block blockWall = Block(0, 0, BLOCK_TYPE_WALL);

    Tetromino tetrominoI;
    Tetromino tetrominoJ;
    Tetromino tetrominoL;
    Tetromino tetrominoO;
    Tetromino tetrominoS;
    Tetromino tetrominoT;
    Tetromino tetrominoZ;
    Tetromino tetromino[7];

    vector<vector<Block> > map, nex, hold;
    int score;
    int lines;
    int delayFrame, numLinesInLevel;
    SDL_Point holdPos, mapPos, nexPos, scorePos, linePos;
    string playerName;
    Tetromino currentTetromino;
    Tetromino nextTetromino[NUM_NEXT_TETROMINO], holdTetromino;
    queue<int> queueTetromino;
    bool holdEmpty, swapHold;
    Texture scoreTexture;
    int level;
    Uint8 blockAlpha;
    bool clearedLine[MAP_HEIGHT];
    int delayRender;
    enum RenderStatus
    {
        RENDER_NORMAL,
        RENDER_CLEAR_LINE,
        RENDER_PUTDOWN_TETROMINO,
        RENDER_DROP_TETROMINO
    } renderStatus;
    GameStatus gameStatus;
    bool lastRotate;
    bool TSpin;
    bool wallKick;
    int linesClear;
    vector<vector<pair<int, int> > > JLSTZWallKick = vector<vector<pair<int, int> > >({vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, -2), make_pair(-1, -2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(1, -1), make_pair(0, 2), make_pair(1, 2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(1, -1), make_pair(0, 2), make_pair(1, 2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, -2), make_pair(-1, -2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(1, 1), make_pair(0, -2), make_pair(1, -2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(-1, -1), make_pair(0, 2), make_pair(-1, 2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(-1, -1), make_pair(0, 2), make_pair(-1, 2)}),
                                                                                       vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(1, 1), make_pair(0, -2), make_pair(1, -2)})});

    vector<vector<pair<int, int> > > IWallKick = vector<vector<pair<int, int> > >({vector<pair<int, int> >({make_pair(0, 0), make_pair(-2, 0), make_pair(1, 0), make_pair(-2, -1), make_pair(1, 2)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(2, 0), make_pair(-1, 0), make_pair(2, 1), make_pair(-1, -2)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(2, 0), make_pair(-1, 2), make_pair(2, -1)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(-2, 0), make_pair(1, -2), make_pair(-2, 1)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(2, 0), make_pair(-1, 0), make_pair(2, 1), make_pair(-1, -2)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(-2, 0), make_pair(1, 0), make_pair(-2, -1), make_pair(1, 2)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(1, 0), make_pair(-2, 0), make_pair(1, -2), make_pair(-2, 1)}),
                                                                                   vector<pair<int, int> >({make_pair(0, 0), make_pair(-1, 0), make_pair(2, 0), make_pair(-1, 2), make_pair(2, -1)})});

public:
    Tetris();
    Tetris(Tetris &&) = default;
    Tetris(const Tetris &) = default;
    Tetris &operator=(Tetris &&) = default;
    Tetris &operator=(const Tetris &) = default;
    void initBoard(vector<vector<Block> > &board, int height, int width, SDL_Point posUpLeft);
    void initGame(int x, int y, int level = 1);
    void loadTexture(SDL_Renderer *renderer);
    void loadBlock(SDL_Renderer *renderer);
    void loadTetromino();
    SDL_Point getHoldPos();
    SDL_Point getMAapPos();
    SDL_Point getNextPos();
    Tetromino getShadowTetromino(Tetromino tetromino);
    int genTetromino();
    Tetromino rotate(Tetromino tetromino, int direct);
    void setHoldTetromino();
    void handleEvent(SDL_Event event);
    void checkTSpin(Tetromino tetromino);
    GameStatus getGameStatus();
    void setGameStatus(GameStatus status);
    bool checkCorrectTetromino(Tetromino tetromino) const;
    void moveDownTetromino();
    void putDownTetromino(Tetromino tetromino);
    void updateMap();
    void checkClearLines();
    void clearLines();
    void setNextTetromino();
    void updateScore();
    int getScore();
    int getClearLines();
    void textCenterRender(string text, int fontSize, SDL_Color color, SDL_Renderer *renderer, int left, int width, int height);
    void renderBoard(SDL_Renderer *renderer, vector<vector<Block> > &board, int height, int width);
    void renderScoreTable(SDL_Renderer *renderer);
    void renderMap(SDL_Renderer *renderer);
    void renderDropTetromino(SDL_Renderer *renderer);
    void renderPutdownTetromino(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer);
    void freeBlock();
    ~Tetris();
};

#endif // !TETRIS__H
