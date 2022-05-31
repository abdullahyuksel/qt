#include "codec.h"
#include "ui_codec.h"

Codec::Codec(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Codec)
{
    ui->setupUi(this);
}

Codec::~Codec()
{
    delete ui;
}
