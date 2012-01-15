#ifndef CUSTOMASSIGNDIALOG_H
#define CUSTOMASSIGNDIALOG_H

#include "engine.h"

#include <QHBoxLayout>
#include <QSpinBox>
#include <QDialog>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QMap>
#include <QButtonGroup>
#include <QLabel>
#include <QtGui/QTableWidget>

#ifndef SERVER_H
static QLayout *HLay(QWidget *left, QWidget *right){
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(left);
    layout->addWidget(right);

    return layout;
}
#endif

class LabelButton : public QLabel {
    Q_OBJECT
public:
    LabelButton()
        :QLabel(){}

    void mouseDoubleClickEvent(QMouseEvent *)
    {
        emit double_clicked();
    }

    void mousePressEvent(QMouseEvent *)
    {
        emit clicked();
    }
signals:
    void double_clicked();
    void clicked();
};

class CustomAssignDialog: public QDialog{
    Q_OBJECT

public:
    CustomAssignDialog(QWidget *parent);

protected:
  //  virtual void accept();
    virtual void reject();

private:
    QListWidget *list,*equip_list,*hand_list;
    QComboBox *role_combobox, *num_combobox;
    LabelButton *general_label, *general_label2;
    QCheckBox *max_hp_prompt,*hp_prompt;
    QSpinBox *max_hp_spin,*hp_spin;
    QCheckBox *self_select_general, *self_select_general2;

    QMap<QString, QString> role_mapping, general_mapping, general2_mapping;
    QMap<int, QString> player_mapping;
    QMap<int, QListWidgetItem *> item_map;

    QMap<QString, QList<int> > player_equips, player_handcards, player_judges;
    QMap<QString, int> player_maxhp, player_hp;
    QList<int> set_pile;

    QString general_name, general_name2;
    bool choose_general2;
    bool free_choose_general, free_choose_general2;

private slots:
    void updateRole(int index);
    void updateNumber(int num);
    void updatePlayerInfo(QString name);
    void updatePlayerHpInfo(QString name);

    void freeChoose(bool toggled);
    void freeChoose2(bool toggled);

    void setPlayerHpEnabled(bool toggled);
    void setPlayerMaxHpEnabled(bool toggled);
    void getPlayerHp(int hp);
    void getPlayerMaxHp(int maxhp);

    void doGeneralAssign();
    void doGeneralAssign2();
    void doEquipCardAssign();
    void doHandCardAssign();

    void on_list_itemSelectionChanged(QListWidgetItem *current);

public slots:
    void getChosenGeneral(QString general_name);
    void getEquipCard(int card_id);
    void getHandCard(int card_id);
};


class GeneralAssignDialog: public QDialog{
    Q_OBJECT

public:
    explicit GeneralAssignDialog(QWidget *parent);

private:
    QButtonGroup *group;
    QWidget *createTab(const QList<const General *> &generals);

private slots:
    void chooseGeneral();

signals:
    void general_chosen(const QString &name);
};

class CardAssignDialog : public QDialog {
    Q_OBJECT
public:

    CardAssignDialog(QWidget *parent = 0, QString card_type = QString(), QString class_name = QString());
private:
    void addCard(const Card *card);

    QListWidget *card_list;

private slots:
    void askCard();

signals:
    void card_chosen(int card_id);
};


#endif // CUSTOMASSIGNDIALOG_H
