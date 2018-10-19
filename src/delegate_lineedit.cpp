#include "delegate_lineedit.h"

LineEditDelegate::LineEditDelegate(QObject *parent, QStringList list)
    :QStyledItemDelegate(parent)
{
    setList(list);
    compleater = new QCompleter();
    compleater->setCaseSensitivity(Qt::CaseInsensitive);
    compleater->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    compleater->setFilterMode(Qt::MatchContains);
    compleater->setModel(new QStringListModel(this->list));
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    auto *editor = new QLineEdit(parent);
    compleater->setModel(new QStringListModel(CategoriesSingleton::getInstance()->getList()));
    editor->setCompleter(compleater);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *lineEdit = dynamic_cast<QLineEdit*>(editor);
    QString currentText = index.data(Qt::EditRole).toString();
    lineEdit->setText(currentText);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (auto *lineEdit = dynamic_cast<QLineEdit*>(editor)) {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

void LineEditDelegate::setList(QStringList list)
{
    this->list = list;
}

QCompleter *LineEditDelegate::getCompleater()
{
    return compleater;
}
