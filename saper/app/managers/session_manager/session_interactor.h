#pragma once

#include "game/minefield_interactor.h"

#include <QObject>
#include <QtTypes>

#include <memory>

namespace app::managers
{

class SessionInteractor : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(qint16 width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qint16 height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qint64 mines READ mines WRITE setMines NOTIFY minesChanged)

    SessionInteractor(core::MinefieldInteractorSPtr minefieldInteractorSPtr, QObject* parent = nullptr);

    void setWidth(qint16 value);
    void setHeight(qint16 value);
    void setMines(qint64 value);

    qint16 width() const;
    qint16 height() const;
    qint64 mines() const;

signals:
    void widthChanged();
    void heightChanged();
    void minesChanged();

private:
    core::MinefieldInteractorSPtr m_minefieldInteractorSPtr;
};

using SessionInteractorSPtr = std::shared_ptr<SessionInteractor>;

} // namespace app::managers
