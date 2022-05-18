#ifndef CONTROLLER__H
#define CONTROLLER__H
#include "Header.h"
#include "Tetris.h"
#include "Button.h"

enum GameMode
{
    MAIN_MENU_MODE,
    HELP_MODE,
    PLAY_MODE,
    QUIT_MODE,
    QUIT_GAME_MODE,
    PAUSE_MODE,
    GAME_OVER_MODE
};

class Controller
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Mix_Music *music;
    Tetris tetris;
    Texture startGameTexture;
    Texture backgroundTexture;
    Texture pauseTexture;
    Texture quitGameTexture;
    Texture buttonBackgroundTexture;
    Texture helpBackgroundTexture;
    Texture controlTexture;
    Button playButton;
    Button helpButton;
    Button quitButton;
    Button pauseButton;
    Button resumeButton;
    Button nextButton;
    Button backButton;
    Button okButton;
    Button cancelButton;
    Button replayButton;
    Button homeButton;
    Button soundButton[2];
    int soundMode;
    Button levelButton[5];
    int level;
    int screenWidth, screenHeight;
    int gameMode, prevGameMode;

public:
    Controller();
    Controller(SDL_Renderer *renderer, SDL_Window *window, int screenWidth, int screenHeight);
    void loadTexture();
    void load();
    void setRenderer(SDL_Renderer *renderer);
    void setWindow(SDL_Window *window);
    void setGameMode(int mode);
    void updateSound();
    void handleEventMenu(SDL_Event event);
    void handleEventHelp(SDL_Event event);
    void handleEventPlay(SDL_Event event);
    void handleEventQuit(SDL_Event event);
    void handleEventPause(SDL_Event event);
    void handleEventGameOver(SDL_Event event);
    void handleEvent();
    void renderMenu();
    void renderHelp();
    void renderPlay();
    void renderQuit();
    void renderPause();
    void renderGameOver();
    void render();
    void run();
    void free();
    ~Controller();
};

#endif // !CONTROLLER__H