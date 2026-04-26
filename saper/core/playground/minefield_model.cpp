#include "minefield_model.h"

#include <QString>

#include <algorithm>

namespace core
{

namespace
{

bool AreEqual(qreal lhs, qreal rhs)
{
    return std::abs(lhs - rhs) <= 0.0001;
}

} // namespace

MinefieldModel::MinefieldModel(MinefieldInteractorSPtr minefiledInteractorSPtr,
                               MinefieldStorageSPtr minefieldStorageSPtr,
                               app::managers::GameInteractorSPtr gameInteractorSPtr,
                               app::managers::SettingsInteractorSPtr settingsInteractorSPtr,
                               QObject* parent) :
    QAbstractItemModel(parent),
    m_minefiledInteractorSPtr{ std::move(minefiledInteractorSPtr) },
    m_minefieldStorageSPtr{ std::move(minefieldStorageSPtr) },
    m_gameInteractorSPtr{ std::move(gameInteractorSPtr) },
    m_settingsInteractorSPtr{ std::move(settingsInteractorSPtr) } {}

QModelIndex MinefieldModel::index(int row, int column, const QModelIndex& parent) const
{
    return createIndex(row, column);
}

QModelIndex MinefieldModel::parent(const QModelIndex& index) const
{
    return {};
}

int MinefieldModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return m_minefieldStorageSPtr->Size();
}

int MinefieldModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant MinefieldModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
    {
        return {};
    }

    const auto idx = static_cast<std::size_t>(index.row());
    const int x = idx % m_minefiledInteractorSPtr->Width();
    const int y = idx / m_minefiledInteractorSPtr->Width();
    const auto& field = m_minefieldStorageSPtr->At(idx);

    switch(role)
    {
        case static_cast<int>(Role::X):
            return x;
        case static_cast<int>(Role::Y):
            return y;
        case static_cast<int>(Role::IsOpen):
            return field.IsOpen();
        case static_cast<int>(Role::IsFlagged):
            return field.IsFlagged();
        case static_cast<int>(Role::Value):
            return field.IsVoid() ? QString("") : QString::number(field.Value());
        case static_cast<int>(Role::TextureIndex):
            return field.TextureIndex();
        default:
            return {};
    }
}

QHash<int, QByteArray> MinefieldModel::roleNames() const
{
    return {
        { static_cast<int>(Role::X), "xPos" },
        { static_cast<int>(Role::Y), "yPos" },
        { static_cast<int>(Role::IsOpen), "isOpen" },
        { static_cast<int>(Role::IsFlagged), "isFlagged" },
        { static_cast<int>(Role::Value), "value" },
        { static_cast<int>(Role::TextureIndex), "textureIndex" }
    };
}

void MinefieldModel::setCameraX(qreal value)
{
    if (AreEqual(m_cameraX, value))
    {
        return;
    }

    m_cameraX = value;
    emit cameraXChanged();
}

void MinefieldModel::setCameraY(qreal value)
{
    if (AreEqual(m_cameraY, value))
    {
        return;
    }

    m_cameraY = value;
    emit cameraYChanged();
}

void MinefieldModel::setViewportWidth(qreal value)
{
    qDebug() << "setViewportWidth" << value;
    if (value < 0.0 || AreEqual(m_viewportWidth, value))
    {
        return;
    }

    m_viewportWidth = value;
    emit fieldGeometryChanged();
}

void MinefieldModel::setViewportHeight(qreal value)
{
    qDebug() << "setViewportHeight" << value;
    if (value < 0.0 || AreEqual(m_viewportHeight, value))
    {
        return;
    }

    m_viewportHeight = value;
    emit fieldGeometryChanged();
}

void MinefieldModel::setEdgeWidth(qreal value)
{
    if (value < 0.0 || AreEqual(m_edgeWidth, value))
    {
        return;
    }

    m_edgeWidth = value;
    emit fieldGeometryChanged();
}

void MinefieldModel::setEdgeHeight(qreal value)
{
    if (value < 0.0 || AreEqual(m_edgeHeight, value))
    {
        return;
    }

    m_edgeHeight = value;
    emit fieldGeometryChanged();
}

qreal MinefieldModel::cameraX() const
{
    return m_cameraX;
}

qreal MinefieldModel::cameraY() const
{
    return m_cameraY;
}

qreal MinefieldModel::cellSize() const
{
    return CellSize * m_settingsInteractorSPtr->guiMultiply();
}

qreal MinefieldModel::viewportWidth() const
{
    return m_viewportWidth;
}

qreal MinefieldModel::viewportHeight() const
{
    return m_viewportHeight;
}

qreal MinefieldModel::edgeWidth() const
{
    return m_edgeWidth;
}

qreal MinefieldModel::edgeHeight() const
{
    return m_edgeHeight;
}

qreal MinefieldModel::boardWidth() const
{
    return minefieldWidth() + m_edgeWidth;
}

qreal MinefieldModel::boardHeight() const
{
    return minefieldHeight() + m_edgeHeight;
}

qreal MinefieldModel::minefieldWidth() const
{
    return m_minefiledInteractorSPtr->Width() * cellSize();
}

qreal MinefieldModel::minefieldHeight() const
{
    return m_minefiledInteractorSPtr->Height() * cellSize();
}

void MinefieldModel::RefreshModel()
{
    emit dataChanged(index(0, 0), index(rowCount() - 1, 0));
}

void MinefieldModel::leftClickAt(qreal mouseX, qreal mouseY)
{
    auto clickIndex = CellFromMousePosition(mouseX, mouseY);
    if (clickIndex.has_value())
    {
        m_gameInteractorSPtr->LeftClick(*clickIndex);
    }
}

void MinefieldModel::rightClickAt(qreal mouseX, qreal mouseY)
{
    auto clickIndex = CellFromMousePosition(mouseX, mouseY);
    if (clickIndex.has_value())
    {
        m_gameInteractorSPtr->RightClick(*clickIndex);
    }
}

void MinefieldModel::moveCameraBy(qreal dx, qreal dy)
{
    SetCameraPosition(m_cameraX + dx, m_cameraY + dy);
}

void MinefieldModel::clampCamera()
{
    const qreal previousX = m_cameraX;
    const qreal previousY = m_cameraY;

    ApplyCameraClamp();

    if (!AreEqual(previousX, m_cameraX))
    {
        emit cameraXChanged();
    }

    if (!AreEqual(previousY, m_cameraY))
    {
        emit cameraYChanged();
    }
}

void MinefieldModel::ApplyCameraClamp()
{
    if (m_viewportWidth < boardWidth())
    {
        m_cameraX = std::clamp(m_cameraX, 0.0, boardWidth() - m_viewportWidth);
    }
    else
    {
        m_cameraX = (boardWidth() - m_viewportWidth) / 2.0;
    }

    if (m_viewportHeight < boardHeight())
    {
        m_cameraY = std::clamp(m_cameraY, 0.0, boardHeight() - m_viewportHeight);
    }
    else
    {
        m_cameraY = (boardHeight() - m_viewportHeight) / 2.0;
    }
}

void MinefieldModel::SetCameraPosition(qreal x, qreal y)
{
    const qreal previousX = m_cameraX;
    const qreal previousY = m_cameraY;

    m_cameraX = x;
    m_cameraY = y;
    ApplyCameraClamp();

    if (!AreEqual(previousX, m_cameraX))
    {
        emit cameraXChanged();
    }

    if (!AreEqual(previousY, m_cameraY))
    {
        emit cameraYChanged();
    }
}

std::optional<Pos> MinefieldModel::CellFromMousePosition(qreal mouseX, qreal mouseY)
{
    const qreal boardX = mouseX + m_cameraX;
    const qreal boardY = mouseY + m_cameraY;
    const qreal playgroundX = m_edgeWidth / 2.0;
    const qreal playgroundY = m_edgeHeight / 2.0;
    const qreal localX = boardX - playgroundX;
    const qreal localY = boardY - playgroundY;

    if (localX < 0.0 || localY < 0.0 || localX >= minefieldWidth() || localY >= minefieldHeight())
    {
        return std::nullopt;
    }

    const auto x = static_cast<int>(std::floor(localX / cellSize()));
    const auto y = static_cast<int>(std::floor(localY / cellSize()));

    return x + y * m_minefiledInteractorSPtr->Width();
}

} // namespace core
