#ifndef GENBUILDCONFIGWIDGET_H
#define GENBUILDCONFIGWIDGET_H

#include <QWidget>


namespace Ui {
class GenBuildConfigWidget;
}

class GenBuildConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GenBuildConfigWidget(QWidget *parent = nullptr);
    ~GenBuildConfigWidget();

private:
    Ui::GenBuildConfigWidget *ui;
private slots:
    void on_BuildSysComboBox_currentIndexChanged(int index);
    void on_cmakePathBtn_clicked();
    void on_cmakelistFileBtn_clicked();
    void on_cmakeCComplierBtn_clicked();
    void on_cmakeCXXComplierBtn_clicked();
    void on_cmakeUseBuildBtn_clicked();
    void on_cmakeBuildDirBtn_clicked();
    void on_cmakeInstallBtn_clicked();
};

#endif // GENBUILDCONFIGWIDGET_H
