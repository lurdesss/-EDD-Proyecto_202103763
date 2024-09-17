#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include <QMainWindow>
namespace Ui {
class ProfileUser;
}

class ProfileUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileUser(QWidget *parent = nullptr);
    ~ProfileUser();

private slots:
    void on_actionLog_out_triggered();

    void on_actionSearch_triggered();

    void on_actionPosts_triggered();

    void on_actionFriend_Requests_triggered();

    void on_actionReports_triggered();

    void on_actionProfile_triggered();

    void on_actionInformation_triggered();

private:
    Ui::ProfileUser *ui;
};

#endif // PROFILEUSER_H
