#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>
#include <QTimer>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* timer;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetButton_clicked();

    void on_startGameButton_clicked();

    void on_turnCardButton_clicked();

    void on_playerNumConfirmButton_clicked();

    void game_state();

    void on_TimerTimeout();

    void on_pauseButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;

    //___________________DATA STRUCTURES___________________
    // Struct Card contains the button pointer and icon for the card face
    struct Card {
        QPushButton* button;     // The card's button (click to turn)
        QPixmap card_face;       // The card face's pixmap
        bool is_back;            // The card is turned or not
    };

    // Struct Player contains the Cards collected, points, and name
    struct Player {
        std::string player_name_;                     // Name
        std::vector<QPixmap> collected_cards_;        // All the cards collected
        long int pairs_num;                           // Number of pairs collected
        int clicks;                                   // Number of clicks left in 1 turn
        QPushButton* player_name_display_;            // Display the name of player on the game screen
        QLineEdit* player_score_display_;             // Pointer to the score's display
        std::vector<QLabel*> collected_pairs_display; // Vector of pointers to the player's collected cards display
    };

    //___________________VARIABLES___________________
    // Space between elements, both horizontally and vertically
    const int MARGIN = 2;

    // Constants for push buttons
    const int NARROW_BUTTON_WIDTH = 40;
    const int DEFAULT_BUTTON_HEIGTH = 40;

    // Location of the gameboard view and scene
    const int VIEW_X = 20;
    const int VIEW_Y = 345;

    // Setup the player score board: name, score and pairs collected
    const int PLAYER_LABEL_START_X = 460;
    const int PLAYER_LABEL_START_Y = 68;
    const int PLAYER_LABEL_WIDTH = 100;
    const int PLAYER_LABEL_HEIGHT = 28;
    const int PLAYER_LABEL_MARGIN = 20;
    const int PLAYER_LABEL_GAP = 4;
    const int PLAYER_SCORE_WIDTH = 50;

    // Timer
    const int TIMER_INTERVAL = 1000;

    // Game instruction
    const QString game_instruction_text =
            "This is a memory card game, where players take turns and turn pairs of card around.\n "
            "If a pair of the same cards is found, the player in that turn can keep that pair and gain a point.\n "
            "Start by input the number of players and their names, then click 'Confirm player number' button.\n"
            "Next, input the number of cards you want to play the game with, then click 'Start game' button.\n"
            "During the game, each player can turn 2 cards: just click the card on the game board to turn them around.\n"
            "If the turned cards form a pair, the player in that turn get to keep the cards and they gain 1 point.\n"
            "The player who found a pair in a turn can also keep playing in that turn.\n"
            "If the turned cards don't form a pair, the turn is ended. Just click the 'End turn' button.\n"
            "Keep playing until all cards are found!\n"
            "When the game ends, there can be multiple winners or just one winner. The game will announce this.\n"
            "After the game end, you can click the 'Reset' button to reset the game, or 'Close' button to close the game.\n"
            "At any given point in the game, you can click the 'Pause' button to pause the game's timer.\n"
            "You can also click the 'Reset' button to reset the game at any point.\n"
            "At this stage, the game can be played with maximum 29 pairs (or 58 cards).\n"
            "More card can be added using a 40x40 PNG image, put into the 'Images' folder.\n"
            "Then input the new image name into the CARD_FACES vector in the file mainwindow.cpp,\n"
            "Just type in as 'Images/<file name>' and your image will be added into the game.\n"
            "That's it! Have fun playing!";

    // The card faces
    const std::vector<QString> CARD_FACES = {
        "Images/card_1.png",
        "Images/card_2.png",
        "Images/card_3.png",
        "Images/card_4.png",
        "Images/card_5.png",
        "Images/card_6.png",
        "Images/card_7.png",
        "Images/card_8.png",
        "Images/card_9.png",
        "Images/card_10.png",
        "Images/card_11.png",
        "Images/card_12.png",
        "Images/card_13.png",
        "Images/card_15.png",
        "Images/card_16.png",
        "Images/card_17.png",
        "Images/card_18.png",
        "Images/card_19.png",
        "Images/card_20.png",
        "Images/card_21.png",
        "Images/card_22.png",
        "Images/card_23.png",
        "Images/card_24.png",
        "Images/card_25.png",
        "Images/card_26.png",
        "Images/card_27.png",
        "Images/card_28.png",
        "Images/card_29.png",
        "Images/card_30.png"
    };

    // The icons vector
    std::vector<QPixmap> face_pixmap;

    // Vector of all the cards
    std::vector<Card> cards_;

    // Vector of all players
    std::vector<Player> players_;

    // The 2 cards which are turned in the current turn
    std::vector<Card> turned_card_in_turn_;

    // Turn counter
    unsigned long turn_;
    Player* in_turn_ = 0;

    // Whether a card can be clicked or not
    bool can_click_ = true;

    //___________________FUNCTIONS___________________
    // Update timer display
    void update_timer_display(int minutes, int seconds);

    // Create a pixmap vector from all the images
    std::vector<QPixmap> create_pixmap(std::vector<QString> card_faces_vec, unsigned int card_num);

    // Create the card board
    void init_cards(unsigned int card_num);

    // Handle card clicks
    void handle_click();
    void handle_card_click(std::vector<Card> card_vec);

    // Check if the cards form pairs or not
    bool is_a_pair();

    // Display the card collected by the players
    void display_collected_cards();

    // Check if a card existed in a vector of cards
    bool card_existed(std::vector<Card> card_vec, Card card);

    // Check if the game is over
    bool check_game_over();

    // Find the winner (player with most pairs)
    // Or if it's a tie, print out all the tied players with their score
    void check_winner();

    // Reset the game
    void game_reset();

};
#endif // MAINWINDOW_HH
