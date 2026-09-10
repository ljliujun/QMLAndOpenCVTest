#include "ForecastModel.h"

ForecastModel::ForecastModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int ForecastModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_items.size();
}

QVariant ForecastModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.size())
        return {};

    const ForecastItem& item = m_items.at(index.row());
    switch (role)
    {
    case TimeRole:        return item.timeText;
    case DescriptionRole: return item.description;
    case IconRole:        return item.icon;
    case TempRole:        return item.temp;
    case FeelsLikeRole:   return item.feelsLike;
    case HumidityRole:    return item.humidity;
    case WindSpeedRole:   return item.windSpeed;
    default:              return {};
    }
}

QHash<int, QByteArray> ForecastModel::roleNames() const
{
    return {
        { TimeRole,        "time" },
        { DescriptionRole, "description" },
        { IconRole,        "icon" },
        { TempRole,        "temp" },
        { FeelsLikeRole,   "feelsLike" },
        { HumidityRole,    "humidity" },
        { WindSpeedRole,   "windSpeed" }
    };
}

void ForecastModel::setItems(const QList<ForecastItem>& items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
}

void ForecastModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}