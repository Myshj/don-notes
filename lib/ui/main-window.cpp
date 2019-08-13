#include "main-window.h"
#include "ui_main-window.h"

#include "my-storage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace don::notes;
using namespace std;

const QString SYMBOLS_USED_TEMPLATE("%1/%2");

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
    storage::initFrom(QStringLiteral("save.data"));
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
    table->setRowCount(indexToFill + 1);

    const auto result = storage::add(text);
    if(result == storage::AdditionResult::OK){
        const auto recordVariant = storage::last();
        const auto maybeRecord = get<storage::Record>(recordVariant);

        display(maybeRecord, *table, indexToFill);
    }


    ui->noteLine->clear();

    storage::saveTo(QStringLiteral("save.data"));
}
