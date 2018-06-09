#ifndef MESSAGE_H
#define MESSAGE_H

#include<QString>
#include<string.h>
#pragma pack(push, 1)
struct ExchangeMsgHeader {
    uint16_t magic;
    constexpr static uint16_t intended_magic = 0xC8A1;
    uint16_t type;
    union Content {
        constexpr static uint16_t type_message = 1;

        struct Message {
            uint16_t flags;
                constexpr static uint16_t MeFlag = 1;
        } message;
        constexpr static uint16_t type_introduction = 2;

        struct Introduction {
            uint16_t flags;
        } introduction;
    } cont;
};
#pragma pack(pop)

class Message
{
    QString message;
    QString name;
    QString *strings;
    ExchangeMsgHeader *header;
    void introductionMessage(QString name);
    void textMessage(QString name, QString message);
    void constructHeader(uint16_t magic, uint16_t type, QString name, QString text);
public:
    void constructHeader_text(QString name, QString text);
    void constructHeader_introduction(QString name);
    void receiveData(QByteArray dataArray);
    void parseData();
    Message();

    QString getMessage() const;
    void setMessage(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    ExchangeMsgHeader *getHeader() const;
    QString *getStrings() const;
};

#endif // MESSAGE_H
