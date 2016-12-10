#include "ModelItem.h"

#include <QSharedPointer>
#include <QPixmapCache>

namespace QtcUtilities {
namespace Internal {
namespace Ci {

ModelItem::ModelItem (ModelItem *parent)
  : parent_ (parent), decoration_ (Decoration::None)
{
}

ModelItem::~ModelItem ()
{
}

ModelItem * ModelItem::parent () const
{
  return parent_;
}

ModelItem * ModelItem::child (int row) const
{
  if (children_.size () > row) {
    return children_[row].data ();
  }
  return nullptr;
}

int ModelItem::row () const
{
  if (parent_) {
    const auto &siblings = parent_->children_;
    for (auto i = 0, end = siblings.size (); i < end; ++i) {
      if (siblings[i] == this) {
        return i;
      }
    }
  }
  return -1;
}

int ModelItem::rowCount () const
{
  return children_.size ();
}

int ModelItem::columnCount () const
{
  return data_.size ();
}

void ModelItem::setData (int column, const QVariant &data)
{
  for (auto i = column - data_.size (); i >= 0; --i) {
    data_ << QVariant ();
  }
  data_[column] = data;
}

ModelItem::Decoration ModelItem::decoration () const
{
  return decoration_;
}

void ModelItem::setDecoration (Decoration decoration)
{
  decoration_ = decoration;
}

void ModelItem::addChild (QSharedPointer<ModelItem> child)
{
  children_ << child;
}

QVariant ModelItem::data (int column, int role) const
{
  if (role == Qt::DisplayRole && column < data_.size ()) {
    return data_[column];
  }
  else if (role == Qt::DecorationRole && column == 0) {
    static QMap<Decoration, QString> names {
      {Decoration::None, ""}, {Decoration::Success, ":success"},
      {Decoration::Failure, ":failure"}, {Decoration::Working, ":working"}
    };
    auto name = names.value (decoration_);
    if (!name.isEmpty ()) {
      QPixmap pixmap;
      if (QPixmapCache::find (name, &pixmap)) {
        return pixmap;
      }
      if (pixmap.load (name)) {
        QPixmapCache::insert (name, pixmap);
      }
      return pixmap;
    }
  }
  return {};
}

QList<QSharedPointer<ModelItem> > ModelItem::children () const
{
  return children_;
}

} // namespace Ci
} // namespace Internal
} // namespace QtcUtilities
