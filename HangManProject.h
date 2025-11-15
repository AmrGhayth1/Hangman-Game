#pragma once

#include <QtWidgets/QWidget>
#include "ui_HangManProject.h"

class HangManProject : public QWidget
{
    Q_OBJECT


public:
    // initalize game variables & layouts 
    HangManProject(QWidget* parent = nullptr);
    //
    ~HangManProject();
    // ================================ UI Privates ================================
private:

    Ui::HangManProjectClass ui;

    // default font I designed for over GUI application
    QFont defaultFont;
    // layouts of game 
    QGridLayout* characterLayout, * hangManLayout, * wordLayout, * stateLayout, * layout;
    // widgets of game
    QLabel* charactersLabels[26];
    QLabel* gussedWordLabel;
    QLabel* statesLabel;
    QLabel* hangManLabel;

    // ================================ Function Privates ================================
private:
    // draw & update drawn characters depend on isKeypressed
    void drawAlphabetCharacters();

    //  draw & update guessed word depend on isKeypressed & randomWords choosen
    void drawChooseWord();

    // draw & update bottom right stats depend on currentLives
    void drawStates();

    // draw & update hangMan depend on currentLives
    void drawHangMan();

    /*
        this function called by "QT" whenerever user press key on Application
        responsible on updating user state | UI state depend on key pressed & Game logic
        Assumption: no changing of state until user press key
    */
    void keyPressEvent(QKeyEvent* e);


    // ================================ UI Privates ================================
private:

    const int MX_LIVES = 6;
    const int NUM_RAND_WORDS = 5;
    // hold random index of word that player should guess
    int randomNum;
    // Random words|Dictonary that application choose randomly
    const std::string randomWords[6] = {
        "amr zengy",
        "yara zebala",
    };
    // hold if the user key pressed before or not
    bool isKeypressed[26] = { 0 };

    int currentLives = MX_LIVES;
    // guessed word that user make till make
    // can be used later for win state
    std::string guessWord = "";

};