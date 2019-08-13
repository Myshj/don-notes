#ifndef STORAGE_H
#define STORAGE_H

#include <variant>
#include <QDateTime>

namespace don {
namespace notes {
namespace storage {

enum class InitResult : quint8{
    OK,
    ERROR_WHILE_OPENING_FILE,
    ERROR_WHILE_READING_DATA,
    READ_CORRUPT_DATA
};

enum class SaveResult : quint8{
    OK,
    ERROR_WHILE_OPENING_FILE,
    ERROR_WHILE_WRITING_DATA
};

enum class AdditionResult : quint8{
    OK,
    ERROR_WHILE_ADDING_WHEN_FIELD,
    ERROR_WHILE_ADDING_TEXT_FIELD
};

enum class GetByIdError : quint8{
    NO_SUCH_ID
};

enum class GetLastError : quint8{
    EMPTY
};

struct Record
{
    const QDateTime when;
    const QString text;
};

AdditionResult add(const QString&);
std::variant<Record, GetByIdError> byId(const qint32 id);
std::variant<Record, GetLastError> last();
qint32 count();
InitResult initFrom(const QString& fileName);
SaveResult saveTo(const QString& fileName);


}
}
}

#endif // STORAGE_H
