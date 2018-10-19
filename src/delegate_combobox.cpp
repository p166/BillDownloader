#include "delegate_combobox.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent, const QStringList &list)
    :QStyledItemDelegate(parent)
{
    setList(list);
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    auto *editor = new QComboBox(parent);
    editor->addItems(list);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *comboBox = dynamic_cast<QComboBox*>(editor);
    QString currentText = index.data(Qt::EditRole).toString();
    int cbIndex = comboBox->findText(currentText);
    if (cbIndex >= 0)
        comboBox->setCurrentIndex(cbIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (auto *comboBox = dynamic_cast<QComboBox*>(editor)) {
        model->setData(index, list.at(comboBox->currentIndex()), Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::setList(const QStringList list)
{
    this->list = list;
    this->list.removeDuplicates();
    this->list.sort();
}
