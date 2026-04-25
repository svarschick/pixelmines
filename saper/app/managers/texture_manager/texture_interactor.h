#pragma once

#include "resource_manager/i_update_interactor.h"

#include <QString>
#include <QObject>

#include <memory>

namespace app::managers
{

class TextureInteractor : public QObject, IUpdateInteractor
{
    Q_OBJECT
public:

    Q_PROPERTY(QString bg01 MEMBER m_bg01 NOTIFY bg01Changed)
    Q_PROPERTY(QString buttonLeft  MEMBER m_buttonLeft NOTIFY buttonLeftChanged)
    Q_PROPERTY(QString buttonPlash MEMBER m_buttonPlash NOTIFY buttonPlashChanged)
    Q_PROPERTY(QString buttonRight MEMBER m_buttonRight NOTIFY buttonRightChanged)
    Q_PROPERTY(QString leftButton MEMBER m_leftButton NOTIFY leftButtonChanged)
    Q_PROPERTY(QString leftSliderBorder MEMBER m_leftSliderBorder NOTIFY leftSliderBorderChanged)
    Q_PROPERTY(QString logo MEMBER m_logo NOTIFY logoChanged)
    Q_PROPERTY(QString rightButton MEMBER m_rightButton NOTIFY rightButtonChanged)
    Q_PROPERTY(QString rightSliderBorder MEMBER m_rightSliderBorder NOTIFY rightSliderBorderChanged)
    Q_PROPERTY(QString selectedCheckbox MEMBER m_selectedCheckbox NOTIFY selectedCheckboxChanged)
    Q_PROPERTY(QString selectedCorner MEMBER m_selectedCorner NOTIFY selectedCornerChanged)
    Q_PROPERTY(QString selectedProfile MEMBER m_selectedProfile NOTIFY selectedProfileChanged)
    Q_PROPERTY(QString slider MEMBER m_slider NOTIFY sliderChanged)
    Q_PROPERTY(QString sliderPlash MEMBER m_sliderPlash NOTIFY sliderPlashChanged)
    Q_PROPERTY(QString unselectedButtonLeftBorder MEMBER m_unselectedButtonLeftBorder NOTIFY unselectedButtonLeftBorderChanged)
    Q_PROPERTY(QString unselectedButtonPlash MEMBER m_unselectedButtonPlash NOTIFY unselectedButtonPlashChanged)
    Q_PROPERTY(QString unselectedButtonRightBorder MEMBER m_unselectedButtonRightBorder NOTIFY unselectedButtonRightBorderChanged)
    Q_PROPERTY(QString unselectedCheckbox MEMBER m_unselectedCheckbox NOTIFY unselectedCheckboxChanged)
    Q_PROPERTY(QString unselectedCorner MEMBER m_unselectedCorner NOTIFY unselectedCornerChanged)
    Q_PROPERTY(QString unselectedProfile MEMBER m_unselectedProfile NOTIFY unselectedProfileChanged)

public:
    TextureInteractor(QObject* obj = nullptr);

    void OnUpdateInteractor() override;

signals:
    void bg01Changed();
    void buttonLeftChanged();
    void buttonPlashChanged();
    void buttonRightChanged();
    void leftButtonChanged();
    void leftSliderBorderChanged();
    void logoChanged();
    void rightButtonChanged();
    void rightSliderBorderChanged();
    void selectedCheckboxChanged();
    void selectedCornerChanged();
    void selectedProfileChanged();
    void sliderChanged();
    void sliderPlashChanged();
    void unselectedButtonLeftBorderChanged();
    void unselectedButtonPlashChanged();
    void unselectedButtonRightBorderChanged();
    void unselectedCheckboxChanged();
    void unselectedCornerChanged();
    void unselectedProfileChanged();

public:
    QString m_bg01;
    QString m_buttonLeft;
    QString m_buttonPlash;
    QString m_buttonRight;
    QString m_leftButton;
    QString m_leftSliderBorder;
    QString m_logo;
    QString m_rightButton;
    QString m_rightSliderBorder;
    QString m_selectedCheckbox;
    QString m_selectedCorner;
    QString m_selectedProfile;
    QString m_slider;
    QString m_sliderPlash;
    QString m_unselectedButtonLeftBorder;
    QString m_unselectedButtonPlash;
    QString m_unselectedButtonRightBorder;
    QString m_unselectedCheckbox;
    QString m_unselectedCorner;
    QString m_unselectedProfile;
};

using TextureInteractorSPtr = std::shared_ptr<TextureInteractor>;

} // namespace app::managers
