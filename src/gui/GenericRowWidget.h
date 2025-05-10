 /**
 * @file GenericRowWidget.h
 * @author Filip Ficka, xfickaf00
 * @brief header file for GenericRow object
 * @version 1.1
 * @date 2025-05-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GENERICROWWIDGET_H
#define GENERICROWWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

/**
 * @brief inheretance from Qwidget
 * 
 */
class GenericRowWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief enum for row type, set by different buttons in ui
     * 
     */
    enum RowType { Input, Output, Variable };
    
    /// all comments for function in .cpp

    explicit GenericRowWidget(RowType type, QWidget *parent = nullptr);
    void setGenericTexts(const QString &keyText, const QString &valueText);
    void disableKeyEdit();
    QString key() const;
    QString value() const;
    void setDeleteButtonEnabled(bool enabled);

signals:
    void requestDelete(GenericRowWidget *self);

private:
    /// pointers to child objects and place for rowType

    QLineEdit *keyEdit;
    QLineEdit *valueEdit;
    RowType rowType;
    QPushButton *deleteButton;
    QString disableStyle = "QPushButton:disabled { background-color: #444444; color: #888888; }";
};

#endif // GENERICROWWIDGET_H
