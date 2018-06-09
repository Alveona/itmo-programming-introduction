#include "message.h"
void Message::receiveData(QByteArray dataArray)
{
    memcpy(header, dataArray, sizeof(*header));
    int stringsReceived = 0;
    //for()
    char* end = dataArray.data() + dataArray.size();
    for(char* curchar = dataArray.data() + sizeof(*header); curchar < end;)
    {
        strings[stringsReceived] = QString::fromUtf8(curchar);
        stringsReceived++;
        curchar += strlen(curchar) + 1;
    }
    parseData();
}
void Message::parseData()
{
    if(header->magic != header->intended_magic)
        return;
    if(header->type == header->cont.type_introduction)
    {
        introductionMessage(strings[0]);
    }
    if(header->type == header->cont.type_message)
    {
        textMessage(strings[0], strings[1]);
    }
}
void Message::constructHeader_text(QString name, QString text)
{
    constructHeader(0xC8A1, 1, name, text);
}
void Message::constructHeader_introduction(QString name)
{
    constructHeader(0xC8A1, 2, name, QString(""));
}
void Message::constructHeader(uint16_t magic, uint16_t type, QString name, QString text)
{
    header->magic = magic;
    header->type = type;
    strings[0] = name;
    strings[1] = text;
}

ExchangeMsgHeader *Message::getHeader() const
{
    return header;
}

QString *Message::getStrings() const
{
    return strings;
}

void Message::introductionMessage(QString name)
{
    this->name = name;
    this->message = QString("");
}
void Message::textMessage(QString name, QString message)
{
    this->name = name;
    this->message = message;
}
QString Message::getMessage() const
{
    return message;
}

void Message::setMessage(const QString &value)
{
    message = value;
}

QString Message::getName() const
{
    return name;
}

void Message::setName(const QString &value)
{
    name = value;
}

Message::Message()
{
    header = new ExchangeMsgHeader();
    strings = new QString[2];
}
