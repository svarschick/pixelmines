#pragma once

#include "managers/game_manager/game_interactor.h"
#include "managers/settings_manager/settings_interactor.h"
#include "game/minefield_storage.h"
#include "game/minefield_interactor.h"

#include <QAbstractItemModel>
#include <QHash>
#include <QVariant>

#include <memory>
#include <utility>
#include <optional>

namespace core
{

class MinefieldModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_PROPERTY(qreal cameraX READ cameraX WRITE setCameraX NOTIFY cameraXChanged)
    Q_PROPERTY(qreal cameraY READ cameraY WRITE setCameraY NOTIFY cameraYChanged)
    Q_PROPERTY(qreal cellSize READ cellSize NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal viewportWidth READ viewportWidth WRITE setViewportWidth NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal viewportHeight READ viewportHeight WRITE setViewportHeight NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal edgeWidth READ edgeWidth WRITE setEdgeWidth NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal edgeHeight READ edgeHeight WRITE setEdgeHeight NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal boardWidth READ boardWidth NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal boardHeight READ boardHeight NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal minefieldHeight READ minefieldHeight NOTIFY fieldGeometryChanged)
    Q_PROPERTY(qreal minefieldWidth READ minefieldWidth NOTIFY fieldGeometryChanged)

    enum class Role
    {
        X = Qt::UserRole + 1,
        Y,
        IsOpen,
        IsFlagged,
        Value,
        TextureIndex,
    };
    Q_ENUM(Role)

public:
    static constexpr const qreal CellSize = 5.0;

public:
    explicit MinefieldModel(MinefieldInteractorSPtr minefiledInteractorSPtr,
                            MinefieldStorageSPtr minefieldStorageSPtr,
                            app::managers::GameInteractorSPtr gameInteractorSPtr,
                            app::managers::SettingsInteractorSPtr settingsInteractorSPtr,
                            QObject* parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
    QModelIndex parent([[maybe_unused]] const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = {}) const override;
    int columnCount([[maybe_unused]] const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setCameraX(qreal value);
    void setCameraY(qreal value);
    void setViewportWidth(qreal value);
    void setViewportHeight(qreal value);
    void setEdgeWidth(qreal value);
    void setEdgeHeight(qreal value);

    qreal cameraX() const;
    qreal cameraY() const;
    qreal cellSize() const;
    qreal viewportWidth() const;
    qreal viewportHeight() const;
    qreal edgeWidth() const;
    qreal edgeHeight() const;
    qreal boardWidth() const;
    qreal boardHeight() const;
    qreal minefieldHeight() const;
    qreal minefieldWidth() const;

    void RefreshModel();

    Q_INVOKABLE void leftClickAt(qreal mouseX, qreal mouseY);
    Q_INVOKABLE void rightClickAt(qreal mouseX, qreal mouseY);
    Q_INVOKABLE void moveCameraBy(qreal dx, qreal dy);
    Q_INVOKABLE void clampCamera();

signals:
    void cameraXChanged();
    void cameraYChanged();
    void fieldGeometryChanged();

private:
    void ApplyCameraClamp();
    void SetCameraPosition(qreal x, qreal y);
    std::optional<Pos> CellFromMousePosition(qreal mouseX, qreal mouseY);

private:
    MinefieldInteractorSPtr m_minefiledInteractorSPtr;
    MinefieldStorageSPtr m_minefieldStorageSPtr;
    app::managers::GameInteractorSPtr m_gameInteractorSPtr;
    app::managers::SettingsInteractorSPtr m_settingsInteractorSPtr;

    qreal m_cameraX {0.0};
    qreal m_cameraY {0.0};
    qreal m_viewportWidth {100.0};
    qreal m_viewportHeight {100.0};
    qreal m_edgeWidth {100.0};
    qreal m_edgeHeight {100.0};
    qreal m_boardWidth {0.0};
    qreal m_boardHeight {0.0};
};

using MinefieldModelSPtr = std::shared_ptr<MinefieldModel>;

} // namespace core
