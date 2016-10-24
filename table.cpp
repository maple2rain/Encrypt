#include "table.h"

PlayTable::PlayTable(QWidget *parent) :
    QTableWidget(parent){

}

void PlayTable::AddItem(PlayFair &playfair)
{
    this->setRowCount(PlayFair::rows - 1);//设置行数
    this->setColumnCount(PlayFair::cols - 1);//设置列数
    //this->setGeometry(QRect(0, 180, 0, 0));

    /* 填充表格 */
    for(int i = 0; i < PlayFair::rows - 1; ++i){
        /* 设置行高和列高 */
        this->setRowHeight(i, 30);
        this->setColumnWidth(i, 30);

        for(int j = 0; j < PlayFair::cols - 1; ++j){
            QTableWidgetItem *item = new QTableWidgetItem;
            QString txt = QString("%1").arg(playfair.getKey(i + 1, j + 1));
            item->setText(txt);
            this->setItem(i, j, item);
        }
    }
    //this->setItem(PlayFair::rows - 1, PlayFair::cols - 1, new QTableWidgetItem(""));//设置最后一行最后一列为空
    this->setItem(playfair.getKeyValue('z') / 5, playfair.getKeyValue('z') % 5, new QTableWidgetItem("y/z"));//设置z和y显示在同一位置，但其他地方会出现有z和y同时出现却没有在一起的情况
    //重新设置表格大小
    //this->resize((PlayFair::rows) * 30, (PlayFair::cols) * 30);
}
