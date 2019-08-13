#include "my-storage.h"
#include <QFile>
#include <QDataStream>

namespace don{
namespace notes {
namespace storage {

static QVector<QDateTime> _whenColumn;
static QVector<QString> _textColumn;
static qint32 _count = 0;

const int version = QDataStream::Qt_5_13;

void reset(){
    _whenColumn.clear();
    _textColumn.clear();
    _count = 0;
}

AdditionResult add(const QString &text)
{
    const auto now = QDateTime::currentDateTime();
    _whenColumn.append(now);
    _textColumn.append(text);

    const auto whenSize = _whenColumn.size();
    const auto textSize = _textColumn.size();

    const auto expectedSize = _count + 1;

    if(whenSize != expectedSize){
        return AdditionResult::ERROR_WHILE_ADDING_WHEN_FIELD;
    }

    if(textSize != expectedSize){
        return AdditionResult::ERROR_WHILE_ADDING_TEXT_FIELD;
    }

    _count = expectedSize;

    return AdditionResult::OK;
}

std::variant<Record, GetByIdError> byId(const qint32 id)
{
    if(id < 0 || id >= _count){
        return GetByIdError::NO_SUCH_ID;
    }

    return Record{
        _whenColumn[id],
        _textColumn[id]
    };
}

qint32 count()
{
    return _count;
}

InitResult initFrom(const QString& fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        return InitResult::ERROR_WHILE_OPENING_FILE;
    }

    QDataStream in(&file);
    in.setVersion(version);

    QVector<QDateTime> whenColumn;
    QVector<QString> textColumn;

    in.startTransaction();
    in >> whenColumn;
    in >> textColumn;

    if(!in.commitTransaction()){
        return InitResult::ERROR_WHILE_READING_DATA;
    }

    const auto whenSize = whenColumn.size();
    const auto textSize = textColumn.size();

    if(whenSize != textSize){
        return InitResult::READ_CORRUPT_DATA;
    }

    _whenColumn = whenColumn;
    _textColumn = textColumn;

    _count = whenSize;

    return InitResult::OK;
}

SaveResult saveTo(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        return SaveResult::ERROR_WHILE_OPENING_FILE;
    }

    QDataStream out(&file);
    out.setVersion(version);

    out << _whenColumn;
    out << _textColumn;

    if(out.status() != QDataStream::Ok){
        return SaveResult::ERROR_WHILE_WRITING_DATA;
    }

    return SaveResult::OK;
}

std::variant<Record, GetLastError> last()
{
    if(_count == 0){
        return GetLastError::EMPTY;
    }

    return std::get<Record>(byId(_count - 1));
}

}
}
}
