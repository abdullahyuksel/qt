#ifndef CODEC_H
#define CODEC_H

#include <QWidget>

namespace Ui {
class Codec;
}

class Codec : public QWidget
{
    Q_OBJECT

public:
    explicit Codec(QWidget *parent = nullptr);
    ~Codec();

private:
    Ui::Codec *ui;
};

#endif // CODEC_H
