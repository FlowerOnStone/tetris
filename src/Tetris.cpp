#include "Tetris.h"

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

Tetris::Tetris()
{
}

void Tetris::loadTexture(SDL_Renderer *renderer)
{
    scoreTexture.loadFromFile("Texture/ScoreTable.png", renderer);
    loadBlock(renderer);
    loadTetromino();
}

void Tetris::initBoard(vector<vector<Block> > &board, int height, int width, SDL_Point posUpLeft)
{
    board.resize(height);
    for (int i = 0; i < height; i++)
    {
        board[i].resize(width);
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                board[i][j] = blockWall;
            }
            else
            {
                board[i][j] = blockEmpty;
            }
            board[i][j].setScreenPos(posUpLeft.x + j * BLOCK_SIZE, posUpLeft.y + i * BLOCK_SIZE);
        }
    }
}

int Tetris::genTetromino()
{
    if (queueTetromino.empty())
    {
        vector<int> v;
        for (int i = 0; i < 7; i++)
        {
            v.push_back(i);
        }
        shuffle(v.begin(), v.end(), rd);
        for (auto x : v)
        {
            queueTetromino.push(x);
        }
    }
    int resuft = queueTetromino.front();
    queueTetromino.pop();
    return resuft;
}

void Tetris::initGame(int x, int y, int level)
{
    lastRotate = false;
    gameStatus = GAME_PLAY;
    this->level = level;
    renderStatus = RENDER_NORMAL;
    holdTetromino = Tetromino();
    memset(clearedLine, false, sizeof(clearedLine));
    holdPos.x = x;
    holdPos.y = y;
    initBoard(hold, HOLD_HEIGHT, HOLD_WIDTH, holdPos);
    mapPos.x = holdPos.x + BLOCK_SIZE * HOLD_WIDTH;
    mapPos.y = holdPos.y;
    initBoard(map, MAP_HEIGHT, MAP_WIDTH, mapPos);
    nexPos.x = mapPos.x + BLOCK_SIZE * MAP_WIDTH;
    nexPos.y = mapPos.y;
    initBoard(nex, NEXT_HEIGHT, NEXT_WIDTH, nexPos);
    currentTetromino = tetromino[genTetromino()];
    currentTetromino.setMapPos(1, MAP_WIDTH / 2 - 1 - (currentTetromino.getTetrominoType() == BLOCK_TYPE_O ? 0 : 1));
    currentTetromino.setScreenPos(mapPos.x + currentTetromino.getMapPos().y * BLOCK_SIZE, mapPos.y + currentTetromino.getMapPos().x * BLOCK_SIZE);
    if (currentTetromino.getTetrominoType() == BLOCK_TYPE_I)
    {
        currentTetromino.moveUp();
    }
    for (int i = 0; i < 3; i++)
    {
        nextTetromino[i] = tetromino[genTetromino()];
        nextTetromino[i].setScreenPos(nexPos.x + BLOCK_SIZE + (nextTetromino[i].getTetrominoType() == BLOCK_TYPE_O ? 2 : 1) * BLOCK_SIZE, nexPos.y + (2 + (2 - i) * 3) * BLOCK_SIZE);
    }
    delayFrame = FRAMES_PER_GIRDCELL[level];
    holdEmpty = true;
    swapHold = false;
    score = lines = 0;
}

void Tetris::loadBlock(SDL_Renderer *renderer)
{
    blockI.loadFullBlock("Texture/I_BLOCK.png", renderer);
    blockI.loadBorderBlock("Texture/I_BORDER.png", renderer);
    blockJ.loadFullBlock("Texture/J_BLOCK.png", renderer);
    blockJ.loadBorderBlock("Texture/J_BORDER.png", renderer);
    blockL.loadFullBlock("Texture/L_BLOCK.png", renderer);
    blockL.loadBorderBlock("Texture/L_BORDER.png", renderer);
    blockO.loadFullBlock("Texture/O_BLOCK.png", renderer);
    blockO.loadBorderBlock("Texture/O_BORDER.png", renderer);
    blockS.loadFullBlock("Texture/S_BLOCK.png", renderer);
    blockS.loadBorderBlock("Texture/S_BORDER.png", renderer);
    blockT.loadFullBlock("Texture/T_BLOCK.png", renderer);
    blockT.loadBorderBlock("Texture/T_BORDER.png", renderer);
    blockZ.loadFullBlock("Texture/Z_BLOCK.png", renderer);
    blockZ.loadBorderBlock("Texture/Z_BORDER.png", renderer);
    blockWall.loadFullBlock("Texture/WALL.png", renderer);
    blockWall.loadBorderBlock("Texture/WALL.png", renderer);
    blockEmpty.loadFullBlock("Texture/EMPTY.png", renderer);
    blockEmpty.loadBorderBlock("Texture/EMPTY.png", renderer);
}

void Tetris::loadTetromino()
{
    tetromino[0] = tetrominoI = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({false, false, false, false}), vector<bool>({true, true, true, true}), vector<bool>({false, false, false, false}), vector<bool>({false, false, false, false})}), blockI, blockEmpty);
    tetromino[1] = tetrominoJ = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({true, true, true}), vector<bool>({false, false, true}), vector<bool>({false, false, false})}), blockJ, blockEmpty);
    tetromino[2] = tetrominoL = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({false, false, true}), vector<bool>({true, true, true}), vector<bool>({false, false, false})}), blockL, blockEmpty);
    tetromino[3] = tetrominoO = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({true, true}), vector<bool>({true, true})}), blockO, blockEmpty);
    tetromino[4] = tetrominoS = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({false, true, true}), vector<bool>({true, true, false}), vector<bool>({false, false, false})}), blockS, blockEmpty);
    tetromino[5] = tetrominoT = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({false, true, false}), vector<bool>({true, true, true}), vector<bool>({false, false, false})}), blockT, blockEmpty);
    tetromino[6] = tetrominoZ = Tetromino(0, 0, vector<vector<bool> >({vector<bool>({true, true, false}), vector<bool>({false, true, true}), vector<bool>({false, false, false})}), blockZ, blockEmpty);
}

SDL_Point Tetris::getHoldPos()
{
    return holdPos;
}

SDL_Point Tetris::getMAapPos()
{
    return mapPos;
}

SDL_Point Tetris::getNextPos()
{
    return nexPos;
}

void Tetris::renderBoard(SDL_Renderer *renderer, vector<vector<Block> > &board, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j].render(renderer, "SOLID");
        }
    }
}

Tetromino Tetris::getShadowTetromino(Tetromino tetromino)
{
    while (checkCorrectTetromino(tetromino))
    {
        tetromino.moveDown();
    }
    tetromino.moveUp();
    return tetromino;
}

void Tetris::textCenterRender(string text, int fontSize, SDL_Color color, SDL_Renderer *renderer, int left, int width, int height)
{
    Texture tmp;
    tmp.loadFromRenderedText(text, "Consolas.ttf", fontSize, color, renderer);
    SDL_Rect rect;
    rect.x = left + width / 2 - tmp.getWidth() / 2;
    rect.w = tmp.getWidth();
    rect.y = height;
    rect.h = tmp.getHeight();
    tmp.render(&rect, renderer);
    tmp.free();
}

void Tetris::renderScoreTable(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.h = scoreTexture.getHeight();
    rect.w = scoreTexture.getWidth();
    rect.x = holdPos.x + BLOCK_SIZE * 4 - rect.w / 2;
    rect.y = holdPos.y + BLOCK_SIZE * 9;
    scoreTexture.render(&rect, renderer);
    textCenterRender(to_string(score), 32, createColor(255, 255, 0, 0), renderer, holdPos.x, BLOCK_SIZE * 8, holdPos.y + BLOCK_SIZE * 9 + 65);
    textCenterRender(to_string(lines), 32, createColor(255, 255, 0, 0), renderer, holdPos.x, BLOCK_SIZE * 8, holdPos.y + BLOCK_SIZE * 9 + 65 + 102);
    textCenterRender(to_string(level), 32, createColor(255, 255, 0, 0), renderer, holdPos.x, BLOCK_SIZE * 8, holdPos.y + BLOCK_SIZE * 9 + 65 + 102 * 2);
}

void Tetris::renderMap(SDL_Renderer *renderer)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (clearedLine[i] && j > 0 && j < MAP_WIDTH - 1)
            {
                blockEmpty.setScreenPos(map[i][j].getArea().x, map[i][j].getArea().y);
                blockEmpty.render(renderer, "SOLID");
                map[i][j].setAlpha(blockAlpha);
                map[i][j].render(renderer, "SOLID");
                map[i][j].setAlpha(255);
            }
            else
            {
                map[i][j].render(renderer, "SOLID");
            }
        }
    }
    if (delayRender > 0 && renderStatus == RENDER_CLEAR_LINE)
    {
        blockAlpha = max(blockAlpha - 10, 0);
        delayRender--;
        if (delayRender == 0)
        {
            renderStatus = RENDER_NORMAL;
            clearLines();
        }
    }
}

void Tetris::renderDropTetromino(SDL_Renderer *renderer)
{
    Tetromino shadowTetromino = getShadowTetromino(currentTetromino);
    if (currentTetromino.getScreenPos().y == shadowTetromino.getScreenPos().y)
    {
        delayRender = 7;
        renderStatus = RENDER_PUTDOWN_TETROMINO;
    }
    else
    {
        if (delayRender > shadowTetromino.getScreenPos().y)
        {
            delayRender = 7;
            renderStatus = RENDER_PUTDOWN_TETROMINO;
        }
        else
        {
            int step = 255 / 12;
            Tetromino tmp = currentTetromino;
            tmp.setScreenPos(tmp.getScreenPos().x, delayRender);
            blockAlpha = 255 - step * min((shadowTetromino.getScreenPos().y - delayRender) / (BLOCK_SIZE / 4), 12);
            for (int i = 0; i < 12 && tmp.getScreenPos().y <= shadowTetromino.getScreenPos().y; i++)
            {
                if (tmp.getScreenPos().y >= currentTetromino.getScreenPos().y)
                {
                    tmp.setAlpha(blockAlpha);
                    tmp.render(renderer, "SOLID");
                    tmp.setAlpha(255);
                }
                tmp.setScreenPos(tmp.getScreenPos().x, tmp.getScreenPos().y + (BLOCK_SIZE / 2));
                blockAlpha += step;
            }
            delayRender += BLOCK_SIZE / 2;
        }
    }
}

void Tetris::renderPutdownTetromino(SDL_Renderer *renderer)
{
    blockAlpha = 255 - 32 * delayRender;
    currentTetromino = getShadowTetromino(currentTetromino);
    currentTetromino.setAlpha(blockAlpha);
    currentTetromino.render(renderer, "SOLID");
    currentTetromino.setAlpha(255);
    if (delayRender == 0)
    {
        putDownTetromino(currentTetromino);
        checkClearLines();
        updateScore();
        renderStatus = (linesClear == 0 ? RENDER_NORMAL : RENDER_CLEAR_LINE);
        setNextTetromino();
    }
    else
    {
        delayRender--;
    }
}

void Tetris::render(SDL_Renderer *renderer)
{
    renderBoard(renderer, hold, HOLD_HEIGHT, HOLD_WIDTH);
    renderMap(renderer);
    renderBoard(renderer, nex, NEXT_HEIGHT, NEXT_WIDTH);
    renderScoreTable(renderer);
    if (renderStatus == RENDER_NORMAL || renderStatus == RENDER_CLEAR_LINE)
    {
        getShadowTetromino(currentTetromino).render(renderer, "BORDER");
        currentTetromino.render(renderer, "SOLID");
    }
    else if (renderStatus == RENDER_DROP_TETROMINO)
    {
        renderDropTetromino(renderer);
    }
    else
    {
        renderPutdownTetromino(renderer);
    }
    holdTetromino.render(renderer, "SOLID");
    for (int i = 0; i < 3; i++)
    {
        nextTetromino[i].render(renderer, "SOLID");
    }
}

bool Tetris::checkCorrectTetromino(Tetromino tetromino) const
{
    SDL_Point tetrominoPos = tetromino.getMapPos();
    int tetrominoSize = tetromino.getTetrominoSize();
    for (int i = 0; i < tetrominoSize; i++)
    {
        for (int j = 0; j < tetrominoSize; j++)
        {
            if (tetromino.getBlockType(i, j) != BLOCK_TYPE_EMPTY)
            {
                if (i + tetrominoPos.x <= 0 || i + tetrominoPos.x >= MAP_HEIGHT || j + tetrominoPos.y <= 0 || j + tetrominoPos.y >= MAP_WIDTH)
                {
                    return false;
                }
                if (map[i + tetrominoPos.x][j + tetrominoPos.y].getBlockType() != BLOCK_TYPE_EMPTY)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Tetris::putDownTetromino(Tetromino tetromino)
{
    swapHold = false;
    SDL_Point tetrominoPos = tetromino.getMapPos();
    int tetrominoSize = tetromino.getTetrominoSize();
    for (int i = 0; i < tetrominoSize; i++)
    {
        for (int j = 0; j < tetrominoSize; j++)
        {
            if (tetromino.getBlockType(i, j) != BLOCK_TYPE_EMPTY)
            {
                map[i + tetrominoPos.x][j + tetrominoPos.y] = tetromino.getBlock(i, j);
            }
        }
    }
}

void Tetris::updateMap()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map[i][j].setScreenPos(mapPos.x + j * BLOCK_SIZE, mapPos.y + i * BLOCK_SIZE);
        }
    }
}

void Tetris::checkClearLines()
{
    for (int i = 1; i < MAP_HEIGHT - 1; i++)
    {
        bool fullLine = true;
        for (int j = 1; j < MAP_WIDTH - 1; j++)
        {
            if (map[i][j].getBlockType() == BLOCK_TYPE_EMPTY)
            {
                fullLine = false;
                break;
            }
        }
        if (fullLine == true)
        {
            renderStatus = RENDER_CLEAR_LINE;
            delayRender = DELAY_CLEAR_LINE;
            blockAlpha = 255;
            clearedLine[i] = true;
        }
    }
    linesClear = count(clearedLine, clearedLine + MAP_HEIGHT, true);
}

void Tetris::clearLines()
{
    for (int i = 1; i <= MAP_HEIGHT - 1; i++)
    {
        if (clearedLine[i])
        {
            lines++;
            numLinesInLevel++;
            for (int j = i; j > 1; j--)
            {
                for (int k = 1; k < MAP_WIDTH - 1; k++)
                {
                    map[j][k] = map[j - 1][k];
                }
            }
            for (int j = 1; j < MAP_WIDTH - 1; j++)
            {
                map[1][j] = blockEmpty;
            }
            clearedLine[i] = false;
        }
    }
    if (numLinesInLevel >= LINES_BEFORE_LEVEL_INCREASES[level])
    {
        numLinesInLevel -= LINES_BEFORE_LEVEL_INCREASES[level];
        level++;
    }
    updateMap();
}

void Tetris::setNextTetromino()
{
    currentTetromino = nextTetromino[0];
    currentTetromino.setMapPos(1, MAP_WIDTH / 2 - 1 - (currentTetromino.getTetrominoType() == BLOCK_TYPE_O ? 0 : 1));
    currentTetromino.setScreenPos(mapPos.x + currentTetromino.getMapPos().y * BLOCK_SIZE, mapPos.y + currentTetromino.getMapPos().x * BLOCK_SIZE);
    if (currentTetromino.getTetrominoType() == BLOCK_TYPE_I)
    {
        currentTetromino.moveUp();
    }
    nextTetromino[0] = nextTetromino[1];
    nextTetromino[1] = nextTetromino[2];
    nextTetromino[2] = tetromino[genTetromino()];
    for (int i = 0; i < 3; i++)
    {
        nextTetromino[i].setScreenPos(nexPos.x + BLOCK_SIZE + (nextTetromino[i].getTetrominoType() == BLOCK_TYPE_O ? 2 : 1) * BLOCK_SIZE, nexPos.y + (2 + (2 - i) * 3) * BLOCK_SIZE);
    }
    lastRotate = false;
    if (!checkCorrectTetromino(currentTetromino))
    {
        gameStatus = GAME_OVER;
    }
}

void Tetris::moveDownTetromino()
{
    delayFrame--;
    if (delayFrame <= 0)
    {
        Tetromino tempTetromino = currentTetromino;
        tempTetromino.moveDown();
        if (checkCorrectTetromino(tempTetromino))
        {
            currentTetromino = tempTetromino;
        }
        else
        {
            delayRender = 7;
            renderStatus = RENDER_PUTDOWN_TETROMINO;
        }
        delayFrame = FRAMES_PER_GIRDCELL[level];
    }
}

GameStatus Tetris::getGameStatus()
{
    return gameStatus;
}

void Tetris::setGameStatus(GameStatus status)
{
    gameStatus = status;
}

Tetromino Tetris::rotate(Tetromino tetromino, int direct)
{
    if (tetromino.getTetrominoType() == BLOCK_TYPE_O)
    {
        return tetromino;
    }
    int currentDirect = tetromino.getRotateDirect();
    int rotateTestIndex;
    switch (currentDirect)
    {
    case 0:
        rotateTestIndex = (direct == 1 ? 0 : 7);
        break;
    case 1:
        rotateTestIndex = (direct == 1 ? 2 : 1);
        break;
    case 2:
        rotateTestIndex = (direct == 1 ? 4 : 3);
        break;
    case 3:
        rotateTestIndex = (direct == 1 ? 6 : 5);
        break;
    }
    vector<pair<int, int> > testRotate = (tetromino.getTetrominoType() == BLOCK_TYPE_I ? IWallKick[rotateTestIndex] : JLSTZWallKick[rotateTestIndex]);
    Tetromino rotateTetromino = tetromino;
    if (direct == 1)
    {
        rotateTetromino.clockwiseRotate();
    }
    else
    {
        tetromino.anticlockwiseRotate();
    }
    wallKick = false;
    for (pair<int, int> test : testRotate)
    {
        Tetromino tmp = rotateTetromino;
        tmp.move(test.first, test.second);
        if (checkCorrectTetromino(tmp))
        {
            lastRotate = true;
            if (test != make_pair(0, 0))
            {
                wallKick = true;
            }
            return tmp;
        }
    }
    return tetromino;
}

void Tetris::checkTSpin(Tetromino tetromino)
{
    TSpin = false;
    if (lastRotate == false || tetromino.getTetrominoType() != BLOCK_TYPE_T)
    {
        return;
    }
    int cnt = 0;
    int x = tetromino.getMapPos().x, y = tetromino.getMapPos().y;
    static const int testX[4] = {0, 0, 2, 2};
    static const int testY[4] = {0, 2, 0, 2};
    for (int i = 0; i < 4; i++)
    {
        if (map[x + testX[i]][y + testY[i]].getBlockType() != BLOCK_TYPE_EMPTY)
        {
            cnt++;
        }
    }
    if (cnt >= 3)
    {
        TSpin = true;
    }
}

void Tetris::updateScore()
{
    checkTSpin(currentTetromino);
    if (TSpin)
    {
        switch (linesClear)
        {
        case 0:
            score += (wallKick == 0 ? 100 : 400) * level;
            break;
        case 1:
            score += (wallKick == 0 ? 200 : 800) * level;
            break;
        case 2:
            score += (wallKick == 0 ? 400 : 1200) * level;
            break;
        case 3:
            score += 1600 * level;
            break;
        }
    }
    else
    {
        switch (linesClear)
        {
        case 1:
            score += 100 * level;
            break;
        case 2:
            score += 300 * level;
            break;
        case 3:
            score += 500 * level;
            break;
        case 4:
            score += 800 * level;
            break;
        }
    }
}

int Tetris::getScore()
{
    return score;
}

int Tetris::getClearLines()
{
    return lines;
}

void Tetris::setHoldTetromino()
{
    if (swapHold == false)
    {
        if (holdEmpty)
        {
            holdEmpty = false;
            holdTetromino = currentTetromino;
            setNextTetromino();
        }
        else
        {
            swap(holdTetromino, currentTetromino);
        }
        currentTetromino.setMapPos(1, MAP_WIDTH / 2 - 1 - (currentTetromino.getTetrominoType() == BLOCK_TYPE_O ? 0 : 1));
        currentTetromino.setScreenPos(mapPos.x + currentTetromino.getMapPos().y * BLOCK_SIZE, mapPos.y + currentTetromino.getMapPos().x * BLOCK_SIZE);
        while (holdTetromino.getRotateDirect() != 0)
        {
            holdTetromino.clockwiseRotate();
        }
        holdTetromino.setScreenPos(holdPos.x + BLOCK_SIZE * (holdTetromino.getTetrominoType() == BLOCK_TYPE_O ? 3 : 2), holdPos.y + BLOCK_SIZE * 2);
        swapHold = true;
        delayFrame = FRAMES_PER_GIRDCELL[level];
    }
}

void Tetris::handleEvent(SDL_Event event)
{
    if (renderStatus != RENDER_NORMAL)
    {
        return;
    }
    moveDownTetromino();
    Tetromino tempTetromino = currentTetromino;
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            currentTetromino = rotate(currentTetromino, 1);
            break;
        case SDLK_z:
            currentTetromino = rotate(currentTetromino, -1);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            tempTetromino.moveDown();
            delayFrame = FRAMES_PER_GIRDCELL[level];
            score += 1;
            lastRotate = false;
            if (checkCorrectTetromino(tempTetromino))
            {
                currentTetromino = tempTetromino;
            }
            else
            {
                renderStatus = RENDER_PUTDOWN_TETROMINO;
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            tempTetromino.moveLeft();
            if (checkCorrectTetromino(tempTetromino))
            {
                currentTetromino = tempTetromino;
            }
            lastRotate = false;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            tempTetromino.moveRight();
            if (checkCorrectTetromino(tempTetromino))
            {
                currentTetromino = tempTetromino;
            }
            lastRotate = false;
            break;
        case SDLK_SPACE:
            tempTetromino = getShadowTetromino(tempTetromino);
            renderStatus = RENDER_DROP_TETROMINO;
            delayRender = currentTetromino.getScreenPos().y - (BLOCK_SIZE / 2) * 11;
            score += (tempTetromino.getMapPos().x - currentTetromino.getMapPos().x) * 2;
            break;
        case SDLK_c:
            setHoldTetromino();
            break;
        case SDLK_ESCAPE:
            gameStatus = GAME_PAUSE;
            break;
        }
    }
}

void Tetris::freeBlock()
{
    blockI.free();
    blockJ.free();
    blockL.free();
    blockO.free();
    blockS.free();
    blockT.free();
    blockZ.free();
    blockWall.free();
    blockEmpty.free();
}

Tetris::~Tetris()
{
}