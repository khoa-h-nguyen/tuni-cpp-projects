#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <iostream>
#include <QHBoxLayout>
#include <QPoint>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QIcon>
#include <algorithm>
#include <QBitmap>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      timer(new QTimer(this)),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Timer
    connect(timer, &QTimer::timeout, this, &MainWindow::on_TimerTimeout);
    // Cannot edit number of cards right away
    ui->lineEditCardNum->setEnabled(false);
    ui->startGameButton->setEnabled(false);
    // Center align all the stuffs
    ui->lineEditPlayerNames->setAlignment(Qt::AlignHCenter);
    ui->lineEditCardNum->setAlignment(Qt::AlignHCenter);
    // Set the game stutus bar to read only
    ui->lineEditStatusBar->setReadOnly(true);
    ui->lineEditStatusBar->setText("Welcome players! Enter number of players and their names!");
    ui->lineEditStatusBar->setAlignment(Qt::AlignHCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<QPixmap> MainWindow::create_pixmap(std::vector<QString> card_faces_vec, unsigned int card_num) {
    std::vector<QPixmap> pixmap_vec;
    for (unsigned int i = 0; i < card_num/2; ++i) {
        QPixmap pixmap(card_faces_vec[i]);
        pixmap_vec.push_back(pixmap);        // Each pixmap will get assign to 2 cards,
        pixmap_vec.push_back(pixmap);        // so push back twice here
    }
    return pixmap_vec;
}

//_______________________UTILITY FUNCTIONS_______________________
// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor, unsigned int product)
{
    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

bool MainWindow::card_existed(std::vector<Card> card_vec, Card card) {
    for (unsigned long i = 0; i < card_vec.size(); ++i) {
        if (card_vec[i].button == card.button) {
            return true;
        }
    }
    return false;
}

bool MainWindow::check_game_over()
{
    // The game is over when total cards the players
    // have collected is equal to the number of cards in the game
    unsigned long total_cards_collected = 0;
    for (Player player : players_) {
        total_cards_collected += player.pairs_num*2;
    }
    if (total_cards_collected == cards_.size()) {
        return true;
    }
    return false;
}

void MainWindow::check_winner()
{
    // Put all the winners into a vector: if later, this vector only
    // has 1 player, then the game ends with 1 winner. If more than
    // 1, it means the game has multiple players tie
    std::vector<Player> winners = {};
    // Find the player with the most collected pairs
    Player player_most_pairs = players_[0];
    for (Player player : players_) {
        if (player.pairs_num > player_most_pairs.pairs_num) {
            player_most_pairs = player;
        }
    }
    // Add the player with most pairs into the winners vector
    winners.push_back(player_most_pairs);
    // Check if there is any other player with the same score
    // Then exclude the winner's self
    for (Player player : players_) {
        if ((player.pairs_num == player_most_pairs.pairs_num) && (player.player_name_ != player_most_pairs.player_name_)) {
            winners.push_back(player);
        }
    }
    // Print out the winner(s) by checking the size
    if (winners.size() == 1) {
        QString message = "Game over! Player " + QString::fromStdString(winners[0].player_name_) + " won with ";
        message += QString::number(winners[0].pairs_num) + " pair(s)!";
        ui->lineEditStatusBar->setText(message);
    } else {
        QString message = "Game over! Player ";
        for (unsigned long i = 0; i < winners.size(); ++i) {
            if (winners[i].player_name_ != winners.end()->player_name_) {
                message += QString::fromStdString(winners[i].player_name_) + ", ";
            } else {
                message += QString::fromStdString(winners[i].player_name_);
            }
        }
        message += "tie with ";
        message += QString::number(winners[0].pairs_num) + " pair(s)!";
        ui->lineEditStatusBar->setText(message);
    }
}

void MainWindow::game_reset()
{
    // Clear all the game elements
    face_pixmap.clear();
    for (Card card : cards_) {
        card.button->close();
    }
    cards_.clear();
    // Delete all the created player's elements
    for (Player player : players_) {
        player.player_score_display_->close();
        player.player_name_display_->close();
        for (QLabel* card : player.collected_pairs_display) {
            card->close();
        }
    }
    players_.clear();
    turn_ = 0;
    in_turn_ = 0;

    // Enable player names and number input
    ui->playerNumConfirmButton->setEnabled(true);
    ui->lineEditPlayerNames->setEnabled(true);
    ui->lineEditPlayerNames->setText("");
    ui->spinBoxPlayerNum->setEnabled(true);
    ui->lineEditCardNum->setText("");

    // Reset the timer
    timer->stop();
    update_timer_display(0, 0);

    // Cannot edit number of cards right away
    ui->lineEditCardNum->setEnabled(false);
    ui->startGameButton->setEnabled(false);
    // Set the game stutus bar to read only
    ui->lineEditStatusBar->setReadOnly(true);
    ui->lineEditStatusBar->setText("Welcome players! Enter number of players and their names!");
    ui->lineEditStatusBar->setAlignment(Qt::AlignHCenter);
}

// Split lines into tokens of texts
std::vector<std::string> split(const std::string& s, const char& delimiter, bool ignore_empty = true){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

//_______________________GAME DISPLAY FUNCTIONS_______________________
// This function is used to create the game board
void MainWindow::init_cards(unsigned int card_num)
{
    // Calculate the board size
    unsigned int width = 0;
    unsigned int height = 0;
    ask_product_and_calculate_factors(height, width, card_num);

    // Create the face icons
    face_pixmap = create_pixmap(CARD_FACES, card_num);

    // Setting number buttons in a horizontal line and connecting all of them
    // to the same slot (specific coordinates required)
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x)
        {
            QPushButton* pushButton = new QPushButton(this);
            pushButton->setGeometry(11 * MARGIN + x * (NARROW_BUTTON_WIDTH + MARGIN),
                                    MARGIN + VIEW_Y + y * (DEFAULT_BUTTON_HEIGTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);

            // Select a random icon from the face icons vector and set that
            // icon to the created button. Then add the created card into the
            // all cards vector
            unsigned long random = rand() % face_pixmap.size();
            QPixmap selected_face = face_pixmap[random];
            Card new_card = {pushButton, selected_face, true};
            cards_.push_back(new_card);
            // Remove the pixmap just randomly selected from the pixmaps vectors
            for (std::vector<QPixmap>::iterator it = face_pixmap.begin(); it < face_pixmap.end(); ++it) {
                if (it->toImage() == selected_face.toImage()) {
                    face_pixmap.erase(it);
                }
            }
            // Display the card as card back
            QPixmap pixmap("Images/card_back.png");
            QIcon ButtonIcon(pixmap);
            pushButton->setIcon(ButtonIcon);
            pushButton->setIconSize(pixmap.rect().size());
            pushButton->show();
            // Connect the button to handle card turning
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handle_click);
        }
    }
    // Set the status bar
    ui->lineEditStatusBar->setText("Game started! Select your card!");
}

void MainWindow::update_timer_display(int minutes, int seconds) {
    ui->lcdTimerMin->display(minutes);
    ui->lcdTimerSec->display(seconds);
}

// Display the cards each player have
void MainWindow::display_collected_cards() {
    std::vector<QPixmap> cards = in_turn_->collected_cards_;
    for (unsigned long i = 0; i < cards.size(); ++i) {
        QRect player_label_geometry = in_turn_->player_score_display_->geometry();
        int card_start_x = player_label_geometry.x();
        int card_start_y = player_label_geometry.y() + 3*PLAYER_LABEL_GAP;
        QLabel* new_card = new QLabel(this);
        new_card->setPixmap(cards[i]);
        // Divide the cards into 2 rows
        if ((i+1) % 2 == 0) {
            new_card->setGeometry(card_start_x + 3*MARGIN + NARROW_BUTTON_WIDTH,
                                         card_start_y + 10*MARGIN + (i-1)*(MARGIN + NARROW_BUTTON_WIDTH/2),
                                         NARROW_BUTTON_WIDTH, NARROW_BUTTON_WIDTH);
        } else {
            new_card->setGeometry(card_start_x,
                                         card_start_y + 10*MARGIN + (i)*(MARGIN + NARROW_BUTTON_WIDTH/2),
                                         NARROW_BUTTON_WIDTH, NARROW_BUTTON_WIDTH);
        }
        in_turn_->collected_pairs_display.push_back(new_card);
        new_card->show();
    }
}
//_______________________GAME BUTTON_______________________
void MainWindow::handle_click()
{
    if (can_click_) {
        handle_card_click(cards_);
    }
    return;
}

void MainWindow::handle_card_click(std::vector<Card> cards_)
{
    // Will execute only if the player can click the card
    if (can_click_) {
        // Storing global cursor position
        QPoint global_click_position = QCursor::pos();

        // Counting local cursor position, i.e. decreasing
        // Main Window's location from the global one
        int local_x = global_click_position.x() - geometry().x();
        int local_y = global_click_position.y() - geometry().y();
        QPoint local_click_position = QPoint(local_x, local_y);

        // Searching for the button clicked
        for(unsigned int i = 0; i < cards_.size(); ++i) {
            if(cards_[i].button->geometry().contains(local_click_position))
            {
                // Check if this button already clicked: the player missclick
                // one button twice. If the player click 2 different cards, turn them
                // over and add them into the turned cards vector to check
                if (!card_existed(turned_card_in_turn_, cards_[i])) {
                    // If it's not in, turn the card: now the card cannot be turned by clicking anymore
                    cards_[i].is_back = false;
                    QIcon card_face_icon(cards_[i].card_face);
                    cards_[i].button->setIcon(card_face_icon);
                    cards_[i].button->setIconSize(cards_[i].card_face.rect().size());
                    // Add the turned card into the current turned cards vector
                    turned_card_in_turn_.push_back(cards_[i]);
                    in_turn_->clicks -= 1;
                    ui->lineEditStatusBar->setText("Card turned! Select another card!");
                    if (in_turn_->clicks < 1) {
                        game_state();
                    }
                    return;
                } else {
                    // Inform the player that they missclick
                    ui->lineEditStatusBar->setText("Cards can't be the same! Please select another card!");
                }
                return;
            }
        }
    }
}

void MainWindow::on_resetButton_clicked()
{
    game_reset();
}

void MainWindow::on_startGameButton_clicked()
{
    unsigned int card_num = ui->lineEditCardNum->text().toInt();
    if (card_num % 2 != 0) {
        ui->lineEditCardNum->setText("Number of cards must be even!");
        ui->lineEditCardNum->setAlignment(Qt::AlignHCenter);
    } else {
        init_cards(card_num);
        // Notify that the gameboard has been successfully setup
        ui->lineEditCardNum->setText("Set cards successfully!");
        ui->lineEditCardNum->setAlignment(Qt::AlignHCenter);
        // Disable the setup card stuffs
        ui->lineEditCardNum->setEnabled(false);
        ui->startGameButton->setEnabled(false);
    }
    // First player to play is the first player in the player vector
    in_turn_ = &players_[0];
    // Set player name
    ui->inTurn->setText(QString::fromStdString(in_turn_->player_name_));
    // Start the game timer
    timer->start(TIMER_INTERVAL);
}

void MainWindow::on_turnCardButton_clicked()
{
    // Only end turn when the player in turn cannot click anymore
    if (!can_click_) {
        for(unsigned int i = 0; i < cards_.size(); ++i)
        {
            // Only turn the active cards
            if (cards_[i].button->isEnabled()) {
                QPixmap card_back("Images/card_back.png");
                QIcon card_back_icon(card_back);

                cards_[i].button->setIcon(card_back_icon);
                cards_[i].button->setIconSize(card_back.rect().size());
            }
        }
        // If no pairs are found, no score and continue
        // to the next player's turn
        turn_ = (turn_ + 1) % players_.size();
        if (turn_ <= (players_.size()))
        {
            in_turn_ = &players_[turn_];
        }
        else if (turn_ > (players_.size())) {
            turn_ = 0;
        }
        // Set player name of that turn
        ui->inTurn->setText(QString::fromStdString(in_turn_->player_name_));
        // Reset the number of clicks of the player in next turn
        in_turn_->clicks = 2;
        can_click_ = true;
        // Notify on the status bar that one card is turned
        ui->lineEditStatusBar->setText("Select a card!");
    } else {
        // If the player can still playing, but click this button, notify them
        // that they cannot end their turn yet
        ui->lineEditStatusBar->setText("You are still in turn! Keep selecting cards!");
    }
}

void MainWindow::on_playerNumConfirmButton_clicked()
{
    std::string player_names_str = ui->lineEditPlayerNames->text().toStdString();
    unsigned long player_num = ui->spinBoxPlayerNum->value();
    std::vector<std::string> player_names = split(player_names_str, ',');
    // Check if the correct number of player names have been entered
    if (player_num != player_names.size() or player_num == 0) {
        ui->lineEditPlayerNames->setText("Wrong number of players!");
        ui->lineEditPlayerNames->setAlignment(Qt::AlignHCenter);
    } else {
        int i = 0;
        for (std::string name : player_names) {
            // Create new players
            // Create player name, score and pairs display
            QLineEdit* player_score_display = new QLineEdit(this);
            QPushButton* playerLabel = new QPushButton(this);
            playerLabel->setText(QString::fromStdString(name));
            playerLabel->setGeometry(PLAYER_LABEL_START_X + i*(PLAYER_LABEL_WIDTH + PLAYER_LABEL_GAP), PLAYER_LABEL_START_Y,
                                     PLAYER_LABEL_WIDTH, PLAYER_LABEL_HEIGHT);
            playerLabel->show();

            // Add the newly created player into the players vector
            Player new_player = {name, {}, 0, 2, playerLabel, player_score_display, {}};
            players_.push_back(new_player);

            // Set the score under the name
            player_score_display->setText("0 pairs");
            player_score_display->setGeometry(PLAYER_LABEL_START_X + i*(PLAYER_LABEL_WIDTH + PLAYER_LABEL_GAP),
                                              PLAYER_LABEL_START_Y + PLAYER_LABEL_HEIGHT + PLAYER_LABEL_GAP,
                                              PLAYER_LABEL_WIDTH, PLAYER_LABEL_HEIGHT);
            player_score_display->setAlignment(Qt::AlignHCenter);
            player_score_display->show();
            ++i;
        }
        // Disable the setup player stuffs
        ui->lineEditPlayerNames->setText("Set players successfully!");
        ui->lineEditPlayerNames->setAlignment(Qt::AlignHCenter);
        ui->playerNumConfirmButton->setEnabled(false);
        ui->lineEditPlayerNames->setEnabled(false);
        ui->spinBoxPlayerNum->setEnabled(false);
        // Enable the card setup
        ui->lineEditCardNum->setEnabled(true);
        ui->startGameButton->setEnabled(true);
        // Update the status bar
        ui->lineEditStatusBar->setText("Enter the number of cards you want to play with!");
    }
}

void MainWindow::on_pauseButton_clicked()
{
    // If game is playing: pause the timer and notify on the status bar
    if (ui->pauseButton->text() == "Pause") {
        timer->stop();
        ui->pauseButton->setText("Resume");
        ui->lineEditStatusBar->setText("Game on pause!");
    } else {
        // If game is pausing: resume the timer and notify
        timer->start(TIMER_INTERVAL);
        ui->pauseButton->setText("Pause");
        if (can_click_ == true) {
            ui->lineEditStatusBar->setText("Game resume! Select a card!");
        } else {
            ui->lineEditStatusBar->setText("Game resume! Next player's turn!");
        }

    }

}

void MainWindow::on_helpButton_clicked()
{
    QMessageBox::information(this,"Game Instruction", game_instruction_text);

}

// _______________________GAME ENGINE_______________________
void MainWindow::on_TimerTimeout() {
    int current_minutes = ui->lcdTimerMin->intValue();
    int current_seconds = ui->lcdTimerSec->intValue();

    if (current_seconds == 59) {
        update_timer_display(current_minutes+1, 0);
    } else {
        update_timer_display(current_minutes, current_seconds+1);
    }
}

bool MainWindow::is_a_pair()
{
    // Start the check only if the vector has 2 cards in different positions
    if (turned_card_in_turn_[0].button->geometry() != turned_card_in_turn_[1].button->geometry()) {
        // Check if the cards have the same face (they are a pair)
        QImage image_card_1 = turned_card_in_turn_[0].card_face.toImage();
        QImage image_card_2 = turned_card_in_turn_[1].card_face.toImage();
        if (image_card_1 == image_card_2) {
            // If the cards form a pair, add that pair to the the player currently in turn
            in_turn_->collected_cards_.push_back(turned_card_in_turn_[0].card_face);
            // Then remove them from the board (not clickable)
            for (Card card : turned_card_in_turn_) {
                card.button->setEnabled(false);
            }
            // Clear the vector after the check
            turned_card_in_turn_.clear();
            // Inform the player that they found a pair
            ui->lineEditStatusBar->setText("Pair found! Pick a new card!");
            return true;
        }
        ui->lineEditStatusBar->setText("Pair not found! Next player's turn.");
        turned_card_in_turn_.clear();
        return false;
    }  else {
        // If the player click the same card twice, refund 1 click
        // and remove the last added card
        in_turn_->clicks = 2;
        turned_card_in_turn_.pop_back();
        return false;
    }
    return false;
}

void MainWindow::game_state()
{
    // If a player found a pair: can keep the pair and can keep playing
    if (is_a_pair()) {
        // Update number of pairs of that player
        in_turn_->pairs_num += 1;
        std::string pairs_num_string = std::to_string(in_turn_->pairs_num);
        QString num_of_pair = QString::fromStdString(pairs_num_string + " pairs");
        in_turn_->player_score_display_->setText(num_of_pair);
        display_collected_cards();
        // The player can continue clicking the cards
        in_turn_->clicks = 2;
    } else {
        // If it's not a pair, flush the card checking vector
        // Move onto the next turn
        turned_card_in_turn_.clear();
        can_click_ = false;
    }
    // Check if the game has over or not
    if (check_game_over()) {
        timer->stop();
        check_winner();
    }
}


