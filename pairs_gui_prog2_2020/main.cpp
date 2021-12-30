/*
 * pairs_gui
 *
 * Desc: This program created a pair memory game. Most
 * of the information about the game is found in the file
 * 'instructions.txt' or when clicking the 'Help' button
 * inside the game's GUI.
 *
 * Program author
 * Name: Khoa Nguyen
 * Student number: 050359141
 * UserID: vgkhng
 * E-Mail: khoa.h.nguyen@tuni.fi
 */
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
