#include "stdafx.h"
#include "HangManProject.h"
#include <cstdlib> // used to generate random number
#include <iostream>
#include <string>

HangManProject::HangManProject(QWidget* parent)
    : QWidget(parent)
{
    // default call this by "Qt"
    ui.setupUi(this);

    // 1. choose random word from our random dictionary
    // seed so random not expected with same sequence
    srand(time(0)); // seed with current time
    randomNum = rand() % NUM_RAND_WORDS;

    this->setWindowTitle("kill yara");

    defaultFont = QFont("Arial", 18);

    characterLayout = new QGridLayout();
    hangManLayout = new QGridLayout();
    stateLayout = new QGridLayout();
    wordLayout = new QGridLayout();

    layout = new QGridLayout();

    /*
        ---------------------
        |||||word layout|||||
        ---------------------
        ----------  ---------
        charachter||hang man
        layout    ||layout
                  ||
                  ||---------
                  ||status
        ---------------------
    */
    /*
            0   1   2   3   4   5   6   7   8   9   10  11  12
        0
        1
        2
        3   ===================================================
        4                           ||
        5                           ||
        6                           ||
        7                           ||
        8                           ||
        9                           ||
        10                          ||=========================
        12                          ||

    */
    layout->addLayout(wordLayout, 0, 0, 4, 12);
    layout->addLayout(characterLayout, 4, 0, 6, 6);
    layout->addLayout(hangManLayout, 4, 6, 6, 6);
    layout->addLayout(stateLayout, 10, 6, 1, 6);

    // Set background color for character layout
    drawAlphabetCharacters();
    drawChooseWord();
    drawHangMan();
    drawStates();

    this->setLayout(layout);
}


// ============== Main Function Hold All Game Logic ===============
void HangManProject::keyPressEvent(QKeyEvent* e) {
    // get key pressed & make sure it's lower
    char key = e->key();
    key = tolower(key);

    // if the key press alphapet & not pressed before & still there's lives & still not win=> play
    if (isalpha(key) && !isKeypressed[key - 'a'] && currentLives && this->guessWord != randomWords[randomNum]) {
        this->isKeypressed[key - 'a'] = true; // so don't take action if it pressed again

        // update character style // TODO: make it in define function for readability
        charactersLabels[key - 'a']->setStyleSheet("background-color: #DDD;color: #AAA;border-radius: 5px");

        // If the sub-string is not found it returns string::npos like (end pos)
        // check if random choosen word have key in uppercase or lowercase => draw word again & check if win
        if (randomWords[randomNum].find(key) != std::string::npos || randomWords[randomNum].find(toupper(key)) != std::string::npos) {
            drawChooseWord();
            drawStates();
        }
        // if player press alpha key not in word decrease lives & call everyfunction update depend on lives
        else {
            currentLives--;
            drawStates();
            drawHangMan();
        }

    }
    // pass it to parent as "Qt" said to us
    QWidget::keyPressEvent(e);
}



void HangManProject::drawChooseWord() {
    // if firt time defined create it 
    if (!this->gussedWordLabel)
        this->gussedWordLabel = new QLabel();

    guessWord = "";
    for (auto c : randomWords[randomNum]) {
        // if it's not guesses/pressed yet
        if (c != ' ' && !isKeypressed[tolower(c) - 'a']) {
            guessWord += "_";
        }
        // character is space seperate between words or pressed
        else {
            guessWord += c;
        }
    }

    this->gussedWordLabel->setText(QString::fromStdString(guessWord));
    this->gussedWordLabel->setFont(defaultFont);
    this->gussedWordLabel->setAlignment(Qt::AlignCenter);
    this->gussedWordLabel->setStyleSheet("letter-spacing: 5px;color:#FFF;");
    this->wordLayout->addWidget(gussedWordLabel);
}


void HangManProject::drawStates() {
    // if firt time defined create it 
    if (!statesLabel)
        statesLabel = new QLabel();
    //
    std::string states;

    if (this->guessWord == randomWords[randomNum])
        states = "You Won !!",
        this->statesLabel->setAlignment(Qt::AlignCenter);
    else if (currentLives > 0)
        states = "Lives Count: " + std::to_string(currentLives),
        this->statesLabel->setAlignment(Qt::AlignCenter);
    else
        states = "YOU LOST\nAnswer was \"" + randomWords[randomNum] + "\"",
        this->statesLabel->setAlignment(Qt::AlignLeft);
    //
    this->statesLabel->setText(QString::fromStdString(states));
    this->statesLabel->setFont(defaultFont);
    this->statesLabel->setStyleSheet("color:#ff;font-size:15px;background-color:#044;");

    this->stateLayout->addWidget(statesLabel);

}

void HangManProject::drawHangMan() {
    // if firt time defined create it 
    if (!hangManLabel)
        this->hangManLabel = new QLabel();

    int imgIndex = MX_LIVES - currentLives + 1;
    std::string imgPath = "./lives/" + std::to_string(imgIndex) + ".png";
      
    // must take path as const char
    // so need to convert string => const char
    this->hangManLabel->setPixmap(QPixmap(imgPath.c_str()).scaledToWidth(250));
    this->hangManLabel->setAlignment(Qt::AlignCenter);


    this->hangManLayout->addWidget(hangManLabel);
}

void HangManProject::drawAlphabetCharacters() {
    // loop on all character and draw them
    for (char c = 'A'; c <= 'Z'; c++) {
        this->charactersLabels[c - 'A'] = new QLabel(QString(c));
        this->charactersLabels[c - 'A']->setAlignment(Qt::AlignCenter);
        this->charactersLabels[c - 'A']->setFont(defaultFont);
        this->charactersLabels[c - 'A']->setStyleSheet("background-color: #DDD;color: #000;border-radius: 5px");
        // choose row column of character in grid 6x6
        this->characterLayout->addWidget(charactersLabels[c - 'A'], (c - 'A') / 6, (c - 'A') % 6);
    }
}

// remove every object created dynamically
HangManProject::~HangManProject()
{
    for (char c = 'A'; c <= 'Z'; c++) {
        this->characterLayout->removeWidget(charactersLabels[c - 'A']);
        delete charactersLabels[c - 'A'];
    }

    delete characterLayout;
    delete hangManLayout;
    delete hangManLabel;
    delete stateLayout;
    delete wordLayout;
    delete layout;

    delete gussedWordLabel;
    delete statesLabel;
}
