#include "Controller.h"

Controller::Controller()
{
    renderer = NULL;
    window = NULL;
}

Controller::Controller(SDL_Renderer *renderer, SDL_Window *window, int screenWidth, int screenHeight)
{
    this->renderer = renderer;
    this->window = window;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Controller::setRenderer(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

void Controller::setWindow(SDL_Window *window)
{
    this->window = window;
}

void Controller::loadTexture()
{
    startGameTexture.loadFromFile("Texture/StartGame.png", renderer);
    backgroundTexture.loadFromFile("Texture/GameBackground.png", renderer);
    buttonBackgroundTexture.loadFromFile("Texture/ButtonBackground.png", renderer);
    helpBackgroundTexture.loadFromFile("Texture/HelpBackground.png", renderer);
    pauseTexture.loadFromRenderedText("PAUSE", "Consolas.ttf", 32, createColor(255, 0, 0, 0), renderer);
    quitGameTexture.loadFromRenderedText("QUIT GAME", "Consolas.ttf", 32, createColor(255, 0, 0, 0), renderer);
    controlTexture.loadFromRenderedText("CONTROL", "Consolas.ttf", 48, createColor(255, 255, 255, 0), renderer);
    playButton.setCenterPos(screenWidth / 2 + 25, screenHeight * 2 / 3);
    playButton.loadDefaultTextureFromFile("Texture/Button/play_white.png", renderer);
    playButton.loadHoverTextureFromFile("Texture/Button/play_blue.png", renderer);
    helpButton.setCenterPos(screenWidth * 3 / 4, screenHeight * 2 / 3);
    helpButton.loadDefaultTextureFromFile("Texture/Button/help_white.png", renderer);
    helpButton.loadHoverTextureFromFile("Texture/Button/help_blue.png", renderer);
    quitButton.loadDefaultTextureFromFile("Texture/Button/quit_white.png", renderer);
    quitButton.loadHoverTextureFromFile("Texture/Button/quit_blue.png", renderer);
    level = 0;
    for (int i = 0; i < 5; i++)
    {
        levelButton[i].setCenterPos(screenWidth / 4 + 25, screenHeight * 2 / 3);
        levelButton[i].loadDefaultTextureFromFile("Texture/Button/lv" + to_string(i + 1) + "_white.png", renderer);
        levelButton[i].loadHoverTextureFromFile("Texture/Button/lv" + to_string(i + 1) + "_blue.png", renderer);
    }
    soundMode = 0;
    soundButton[0].loadDefaultTextureFromFile("Texture/Button/sound_ON_white.png", renderer);
    soundButton[0].loadHoverTextureFromFile("Texture/Button/sound_ON_blue.png", renderer);
    soundButton[1].loadDefaultTextureFromFile("Texture/Button/sound_OFF_white.png", renderer);
    soundButton[1].loadHoverTextureFromFile("Texture/Button/sound_OFF_blue.png", renderer);
    pauseButton.loadDefaultTextureFromFile("Texture/Button/pause_white.png", renderer);
    pauseButton.loadHoverTextureFromFile("Texture/Button/pause_blue.png", renderer);
    resumeButton.loadDefaultTextureFromFile("Texture/Button/resume_white.png", renderer);
    resumeButton.loadHoverTextureFromFile("Texture/Button/resume_blue.png", renderer);
    okButton.loadDefaultTextureFromFile("Texture/Button/ok_white.png", renderer);
    okButton.loadHoverTextureFromFile("Texture/Button/ok_blue.png", renderer);
    cancelButton.loadDefaultTextureFromFile("Texture/Button/cancel_white.png", renderer);
    cancelButton.loadHoverTextureFromFile("Texture/Button/cancel_blue.png", renderer);
    replayButton.setCenterPos(screenWidth / 2 - 100, screenHeight * 2 / 3);
    replayButton.loadDefaultTextureFromFile("Texture/Button/replay_white.png", renderer);
    replayButton.loadHoverTextureFromFile("Texture/Button/replay_blue.png", renderer);
    homeButton.setCenterPos(screenWidth / 2 + 100, screenHeight * 2 / 3);
    homeButton.loadDefaultTextureFromFile("Texture/Button/home_white.png", renderer);
    homeButton.loadHoverTextureFromFile("Texture/Button/home_blue.png", renderer);
}

void Controller::load()
{
    music = Mix_LoadMUS("tetris-gameboy-03.mp3");
    loadTexture();
    tetris.loadTexture(renderer);
}

void Controller::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Point tmp;
    SDL_Rect rect;
    switch (gameMode)
    {
    case MAIN_MENU_MODE:
        startGameTexture.render(NULL, renderer);
        playButton.render(renderer);
        helpButton.render(renderer);
        quitButton.setCenterPos(screenWidth * 3 / 4, screenHeight * 2 / 3 + 100);
        quitButton.render(renderer);
        soundButton[soundMode].setCenterPos(screenWidth / 4 + 25, screenHeight * 2 / 3 + 100);
        soundButton[soundMode].render(renderer);
        levelButton[level].render(renderer);
        break;
    case HELP_MODE:
        backgroundTexture.render(NULL, renderer);
        rect.w = helpBackgroundTexture.getWidth();
        rect.h = helpBackgroundTexture.getHeight();
        rect.x = screenWidth / 2 - rect.w / 2;
        rect.y = screenHeight / 2 - rect.h / 2;
        helpBackgroundTexture.render(&rect, renderer);
        rect.w = controlTexture.getWidth();
        rect.h = controlTexture.getHeight();
        rect.x = screenWidth / 2 - rect.w / 2;
        rect.y = screenHeight / 2 - rect.h / 2 - 200;
        controlTexture.render(&rect, renderer);
        okButton.setCenterPos(screenWidth - 150, screenHeight - 50);
        okButton.render(renderer);
        break;
    case PLAY_MODE:
        backgroundTexture.render(NULL, renderer);
        tetris.render(renderer);
        tmp = tetris.getNextPos();
        pauseButton.setCenterPos(tmp.x + 4 * BLOCK_SIZE, tmp.y + 13 * BLOCK_SIZE);
        pauseButton.render(renderer);
        soundButton[soundMode].setCenterPos(tmp.x + 4 * BLOCK_SIZE, tmp.y + 16 * BLOCK_SIZE);
        soundButton[soundMode].render(renderer);
        break;
    case PAUSE_MODE:
        backgroundTexture.render(NULL, renderer);
        tetris.render(renderer);
        rect.w = buttonBackgroundTexture.getWidth();
        rect.h = buttonBackgroundTexture.getHeight();
        rect.x = tetris.getMAapPos().x + BLOCK_SIZE * 6 - rect.w / 2;
        rect.y = tetris.getMAapPos().y + BLOCK_SIZE * 2;
        buttonBackgroundTexture.render(&rect, renderer);
        rect.w = pauseTexture.getWidth();
        rect.h = pauseTexture.getHeight();
        rect.x = tetris.getMAapPos().x + BLOCK_SIZE * 6 - rect.w / 2;
        rect.y = tetris.getMAapPos().y + BLOCK_SIZE * 3;
        pauseTexture.render(&rect, renderer);
        resumeButton.setCenterPos(tetris.getMAapPos().x + BLOCK_SIZE * 6, tetris.getMAapPos().y + BLOCK_SIZE * 6);
        resumeButton.render(renderer);
        soundButton[soundMode].setCenterPos(tetris.getMAapPos().x + BLOCK_SIZE * 6, tetris.getMAapPos().y + BLOCK_SIZE * 8);
        soundButton[soundMode].render(renderer);
        quitButton.setCenterPos(tetris.getMAapPos().x + BLOCK_SIZE * 6, tetris.getMAapPos().y + BLOCK_SIZE * 10);
        quitButton.render(renderer);
        break;
    case QUIT_GAME_MODE:
        backgroundTexture.render(NULL, renderer);
        tetris.render(renderer);
        rect.w = buttonBackgroundTexture.getWidth();
        rect.h = buttonBackgroundTexture.getHeight();
        rect.x = tetris.getMAapPos().x + BLOCK_SIZE * 6 - rect.w / 2;
        rect.y = tetris.getMAapPos().y + BLOCK_SIZE * 2;
        buttonBackgroundTexture.render(&rect, renderer);
        rect.w = quitGameTexture.getWidth();
        rect.h = quitGameTexture.getHeight();
        rect.x = tetris.getMAapPos().x + BLOCK_SIZE * 6 - rect.w / 2;
        rect.y = tetris.getMAapPos().y + BLOCK_SIZE * 3;
        quitGameTexture.render(&rect, renderer);
        okButton.setCenterPos(tetris.getMAapPos().x + BLOCK_SIZE * 6, tetris.getMAapPos().y + BLOCK_SIZE * 6);
        okButton.render(renderer);
        cancelButton.setCenterPos(tetris.getMAapPos().x + BLOCK_SIZE * 6, tetris.getMAapPos().y + BLOCK_SIZE * 9);
        cancelButton.render(renderer);
        break;
    case GAME_OVER_MODE:
        backgroundTexture.render(NULL, renderer);
        tetris.textCenterRender("GAME OVER", 72, createColor(255, 0, 0, 0), renderer, 0, screenWidth, 100);
        tetris.textCenterRender("Score: " + to_string(tetris.getScore()), 36, createColor(255, 255, 0, 0), renderer, 0, screenWidth, 200);
        tetris.textCenterRender("Lines: " + to_string(tetris.getClearLines()), 36, createColor(255, 255, 0, 0), renderer, 0, screenWidth, 300);
        replayButton.render(renderer);
        homeButton.render(renderer);
        break;
    default:
        break;
    }
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}

void Controller::setGameMode(int mode)
{
    prevGameMode = gameMode;
    gameMode = mode;
}

void Controller::updateSound()
{
    if (soundMode == 0)
    {
        Mix_PauseMusic();
        soundMode = 1;
    }
    else
    {
        Mix_ResumeMusic();
        soundMode = 0;
    }
}

void Controller::handleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        gameMode = QUIT_MODE;
        return;
    }
    int gameStatus;
    switch (gameMode)
    {
    case MAIN_MENU_MODE:
        if (playButton.handleEvent(event))
        {
            setGameMode(PLAY_MODE);
            tetris.initGame(200, 10, level + 1);
        }
        if (helpButton.handleEvent(event))
        {
            setGameMode(HELP_MODE);
        }
        if (quitButton.handleEvent(event))
        {
            setGameMode(QUIT_MODE);
        }
        if (levelButton[level].handleEvent(event))
        {
            level = (level + 1) % 5;
        }
        if (soundButton[soundMode].handleEvent(event))
        {
            updateSound();
            break;
        }
        break;
    case HELP_MODE:
        if (okButton.handleEvent(event))
        {
            setGameMode(MAIN_MENU_MODE);
        }
        break;
    case PLAY_MODE:
        tetris.handleEvent(event);
        if (tetris.getGameStatus() == GAME_PAUSE)
        {
            setGameMode(PAUSE_MODE);
        }
        if (tetris.getGameStatus() == GAME_OVER)
        {
            setGameMode(GAME_OVER_MODE);
        }
        if (pauseButton.handleEvent(event))
        {
            setGameMode(PAUSE_MODE);
        }
        if (soundButton[soundMode].handleEvent(event))
        {
            updateSound();
        }
        break;
    case PAUSE_MODE:
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            setGameMode(PLAY_MODE);
            tetris.setGameStatus(GAME_PLAY);
        }
        if (resumeButton.handleEvent(event))
        {
            setGameMode(PLAY_MODE);
            tetris.setGameStatus(GAME_PLAY);
        }
        if (soundButton[soundMode].handleEvent(event))
        {
            updateSound();
        }
        if (helpButton.handleEvent(event))
        {
            setGameMode(HELP_MODE);
        }
        if (quitButton.handleEvent(event))
        {
            setGameMode(QUIT_GAME_MODE);
        }
        break;
    case GAME_OVER_MODE:
        if (replayButton.handleEvent(event))
        {
            setGameMode(PLAY_MODE);
            tetris.initGame(200, 10, level + 1);
        }
        if (homeButton.handleEvent(event))
        {
            setGameMode(MAIN_MENU_MODE);
        }
        break;
    case QUIT_GAME_MODE:
        if (okButton.handleEvent(event))
        {
            setGameMode(MAIN_MENU_MODE);
        }
        if (cancelButton.handleEvent(event))
        {
            setGameMode(PAUSE_MODE);
        }
        break;
    default:
        break;
    }
}

void Controller::run()
{
    gameMode = MAIN_MENU_MODE;
    prevGameMode = MAIN_MENU_MODE;
    Mix_PlayMusic(music, -1);
    while (gameMode != QUIT_MODE)
    {
        handleEvent();
        render();
        SDL_Delay(14);
    }
    Mix_HaltMusic();
}

void Controller::free()
{
    Mix_FreeMusic(music);
    tetris.freeBlock();
    startGameTexture.free();
    backgroundTexture.free();
    pauseTexture.free();
    quitGameTexture.free();
    buttonBackgroundTexture.free();
    helpBackgroundTexture.free();
    controlTexture.free();
    playButton.free();
    helpButton.free();
    for (int i = 0; i < 2; i++)
    {
        soundButton[i].free();
    }
    for (int i = 0; i < 5; i++)
    {
        levelButton[i].free();
    }
    pauseButton.free();
    resumeButton.free();
    okButton.free();
    cancelButton.free();
    replayButton.free();
}

Controller::~Controller()
{
}
