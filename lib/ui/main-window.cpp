#include "main-window.h"
#include "ui_main-window.h"

#include "my-storage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

using namespace don::notes;
using namespace std;

const QString SYMBOLS_USED_TEMPLATE("%1/%2");
const QString INIT_ERROR("Initialization error");
const QString ADDITION_ERROR("Addition error");
const QString SAVE_ERROR("Initialization error");

void display(
    const storage::Record& record,
    QTableWidget& table,
    const int row
){
    const auto whenItem = new QTableWidgetItem(record.when.toString());
    const auto textItem = new QTableWidgetItem(record.text);

    table.setItem(row, 0, whenItem);
    table.setItem(row, 1, textItem);
}

void display(QTableWidget& table){
    const auto count = storage::count();
    table.setRowCount(count);
    for (int i = 0; i < count; ++i) {
        const auto recordVariant = storage::byId(i);
        const auto maybeRecord = get<storage::Record>(recordVariant);

        display(maybeRecord, table, i);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    auto initResult = storage::initFrom(QStringLiteral("save.data"));
    switch (initResult) {
    case storage::InitResult::ERROR_WHILE_OPENING_FILE:
        QMessageBox::warning(this, INIT_ERROR, QStringLiteral("Unable to open 'save.data' file. No notes loaded."));
        break;
    case storage::InitResult::ERROR_WHILE_READING_DATA:
        QMessageBox::warning(this, INIT_ERROR, QStringLiteral("Unable to read data from 'save.data' file. No notes loaded."));
        break;
    case storage::InitResult::READ_CORRUPT_DATA:
        QMessageBox::warning(this, INIT_ERROR, QStringLiteral("'save.data' file is corrupted. No notes loaded."));
        break;
    case storage::InitResult::OK:
        break;
    }
    ui->setupUi(this);
    connect(
        ui->noteLine, &QLineEdit::textChanged,
        this, &MainWindow::onNoteLineChanged
    );
    onNoteLineChanged(ui->noteLine->text());

    connect(
        ui->noteLine, &QLineEdit::editingFinished,
        this, &MainWindow::onNoteEntered
    );

    display(*ui->notesTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNoteLineChanged(const QString &text)
{
    const auto noteLine = ui->noteLine;
    const auto labelText = SYMBOLS_USED_TEMPLATE
        .arg(text.size())
        .arg(noteLine->maxLength());

    ui->symbolsUsedLabel->setText(labelText);
}

void MainWindow::onNoteEntered()
{
    const auto text = ui->noteLine->text();
    if(text.isEmpty()){
        return;
    }

    auto table = ui->notesTable;

    const auto indexToFill = table->rowCount();

    const auto additionResult = storage::add(text);
    switch (additionResult) {
    case storage::AdditionResult::OK:{
        const auto recordVariant = storage::last();
        const auto maybeRecord = get_if<storage::Record>(&recordVariant);

        if(maybeRecord == nullptr){
            QMessageBox::warning(this, ADDITION_ERROR, QStringLiteral("Added note is not present in the DB."));
            return;
        }

        table->setRowCount(indexToFill + 1);
        display(*maybeRecord, *table, indexToFill);
        break;
    }
    case storage::AdditionResult::ERROR_WHILE_ADDING_TEXT_FIELD:{
        QMessageBox::warning(this, ADDITION_ERROR, QStringLiteral("Unable to save note text."));
        return;
    }
    case storage::AdditionResult::ERROR_WHILE_ADDING_WHEN_FIELD:{
        QMessageBox::warning(this, ADDITION_ERROR, QStringLiteral("Unable to save note date."));
        return;
    }
    }

    auto saveResult = storage::saveTo(QStringLiteral("save.data"));
    switch (saveResult) {
    case storage::SaveResult::ERROR_WHILE_OPENING_FILE:
        QMessageBox::warning(this, SAVE_ERROR, QStringLiteral("Unable to open 'save.data' file. No notes saved."));
        table->setRowCount(indexToFill);
        break;
    case storage::SaveResult::ERROR_WHILE_WRITING_DATA:
        QMessageBox::warning(this, SAVE_ERROR, QStringLiteral("Unable to write data to 'save.data' file. No notes saved."));
        table->setRowCount(indexToFill);
        break;
    case storage::SaveResult::OK:
        ui->noteLine->clear();
        break;
    }
}
