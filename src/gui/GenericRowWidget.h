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
    
    /**
     * @brief Construct a new Generic Row Widget:: Generic Row Widget object
     * 
     * @param type setting type from enum decleared in header file
     * @param parent widget to bound generic row
     */
    explicit GenericRowWidget(RowType type, QWidget *parent = nullptr);

    /**
     * @brief function for setting text into genericRow
     * 
     * @param keyText name of row
     * @param valueText value that it contains
     */
    void setGenericTexts(const QString &keyText, const QString &valueText);

    /**
     * @brief function for diseabling name rewrite
     * 
     */
    void disableKeyEdit();

    /**
     * @brief function to get name of row
     * 
     * @return QString 
     */
    QString getKey() const;

    /**
     * @brief function to get value of row
     * 
     * @return QString 
     */
    QString getValue() const;

    /**
     * @brief function to set value of row
     * 
     * @param value new value
     */
    void setValue(QString value);

    /**
     * @brief function to eneable/disable delete button of row
     * 
     * @param enabled 
     */
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
