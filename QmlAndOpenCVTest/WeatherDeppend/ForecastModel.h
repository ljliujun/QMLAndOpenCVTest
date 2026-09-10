#pragma once

#include <QAbstractListModel>

//单日/单时段预报条目

struct ForecastItem
{
    QString timeText;       // "2026-09-09 12:00:00" 或简化后 "12:00"
    QString description;    // "多云"
    QString icon;           // "03n"
    double  temp = 0.0;
    double  feelsLike = 0.0;
    int     humidity = 0;
    double  windSpeed = 0.0;
};

class ForecastModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TimeRole = Qt::UserRole + 1,
        DescriptionRole,
        IconRole,
        TempRole,
        FeelsLikeRole,
        HumidityRole,
        WindSpeedRole
    };

    explicit ForecastModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // 清空并填充
    void setItems(const QList<ForecastItem>& items);
    void clear();

private:
    QList<ForecastItem> m_items;
};

Q_DECLARE_METATYPE(ForecastItem)           // 注册指针类型
Q_DECLARE_METATYPE(QList<ForecastItem>)   // 注册指针列表类型
