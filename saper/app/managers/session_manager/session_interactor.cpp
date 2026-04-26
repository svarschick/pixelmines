#include "session_interactor.h"

namespace app::managers
{

SessionInteractor::SessionInteractor(core::MinefieldInteractorSPtr minefieldInteractorSPtr,
                                     QObject* parent)
    : QObject(parent), m_minefieldInteractorSPtr{ std::move(minefieldInteractorSPtr) } {}

void SessionInteractor::setWidth(qint16 value)
{
    m_minefieldInteractorSPtr->SetWidth(value);
}

void SessionInteractor::setHeight(qint16 value)
{
    m_minefieldInteractorSPtr->SetHeight(value);
}

void SessionInteractor::setMines(qint64 value)
{
    m_minefieldInteractorSPtr->SetMines(value);
}

qint16 SessionInteractor::width() const
{
    return m_minefieldInteractorSPtr->Width();
}

qint16 SessionInteractor::height() const
{
    return m_minefieldInteractorSPtr->Height();
}

qint64 SessionInteractor::mines() const
{
    return m_minefieldInteractorSPtr->Mines();
}

} // namespace app::managers
