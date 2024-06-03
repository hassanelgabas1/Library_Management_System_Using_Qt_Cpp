#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUserType(QString type)
{
    userType = type;
    if (userType == "user") {
        ui->addBookButton->setEnabled(false);
        ui->removeBookButton->setEnabled(false);
    }
}

QJsonArray MainWindow::loadBooks()
{
    QFile file("bookdatabase.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QJsonArray();

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc.array();
}

void MainWindow::saveBooks(const QJsonArray &books)
{
    QFile file("bookdatabase.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QJsonDocument doc(books);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::updateBookList(const QJsonArray &books)
{
    ui->bookList->clear();
    for (const QJsonValue &val : books) {
        QJsonObject book = val.toObject();
        ui->bookList->addItem(book["title"].toString());
    }
}

void MainWindow::on_addBookButton_clicked()
{
    QJsonArray books = loadBooks();
    QJsonObject book;

    book["title"] = QInputDialog::getText(this, "Add Book", "Title:");
    book["author"] = QInputDialog::getText(this, "Add Book", "Author:");
    book["category"] = QInputDialog::getText(this, "Add Book", "Category:");
    book["barcode"] = QInputDialog::getText(this, "Add Book", "Barcode:");

    books.append(book);
    saveBooks(books);
    updateBookList(books);
}

void MainWindow::on_searchBookButton_clicked()
{
    QString title = QInputDialog::getText(this, "Search Book", "Title:");
    QJsonArray books = loadBooks();
    for (const QJsonValue &val : books) {
        QJsonObject book = val.toObject();
        if (book["title"].toString().compare(title, Qt::CaseInsensitive) == 0) {
            QMessageBox::information(this, "Book Found",
                                     "Title: " + book["title"].toString() +
                                         "\nAuthor: " + book["author"].toString() +
                                         "\nCategory: " + book["category"].toString() +
                                         "\nBarcode: " + book["barcode"].toString());
            return;
        }
    }
    QMessageBox::information(this, "Book Not Found", "No book with title " + title);
}

void MainWindow::on_filterCategoryButton_clicked()
{
    QString category = QInputDialog::getText(this, "Filter by Category", "Category:");
    QJsonArray books = loadBooks();
    QJsonArray filteredBooks;
    for (const QJsonValue &val : books) {
        QJsonObject book = val.toObject();
        if (book["category"].toString().compare(category, Qt::CaseInsensitive) == 0) {
            filteredBooks.append(book);
        }
    }
    updateBookList(filteredBooks);
}

void MainWindow::on_removeBookButton_clicked()
{
    QString title = QInputDialog::getText(this, "Remove Book", "Title:");
    QJsonArray books = loadBooks();
    QJsonArray updatedBooks;
    bool found = false;

    for (const QJsonValue &val : books) {
        QJsonObject book = val.toObject();
        if (book["title"].toString().compare(title, Qt::CaseInsensitive) == 0) {
            found = true;
        } else {
            updatedBooks.append(book);
        }
    }

    if (found) {
        saveBooks(updatedBooks);
        updateBookList(updatedBooks);
        QMessageBox::information(this, "Book Removed", "Book with title " + title + " has been removed.");
    } else {
        QMessageBox::information(this, "Book Not Found", "No book with title " + title);
    }
}
