#pragma once

#include <QMetaType>
#include <QVariant>

namespace QtcUtilities {
  namespace Internal {
    namespace Ci {

      class ModelItem {
        public:
          enum class Decoration {
            None, Success, Failure, Running, Skipped, Pending
          };
          using Data = QVariantList;
          explicit ModelItem (ModelItem *parent);
          virtual ~ModelItem ();

          ModelItem *parent () const;
          ModelItem *child (int row) const;
          void prependChild (QSharedPointer<ModelItem> child);
          void addChild (QSharedPointer<ModelItem> child);
          void removeAt (int row);
          int row () const;
          bool isEmpty () const;
          int rowCount () const;
          int columnCount () const;
          void clear ();

          Decoration decoration () const;
          void setDecoration (Decoration decoration);
          void setData (int column, const QVariant &data);
          QVariant data (int column, int role = Qt::DisplayRole) const;

          QList<QSharedPointer<ModelItem> > children () const;

          int levelInTree (ModelItem *item, int current = 0) const;

        protected:
          ModelItem *parent_;
          Data data_;
          Decoration decoration_;
          QList<QSharedPointer<ModelItem> > children_;
      };

    } // namespace Ci
  } // namespace Internal
} // namespace QtcUtilities

Q_DECLARE_METATYPE (QtcUtilities::Internal::Ci::ModelItem *)
