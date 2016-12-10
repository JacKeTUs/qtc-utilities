#pragma once

#include "ModelItem.h"

#include <QUrl>
#include <QNetworkAccessManager>

class QJsonObject;

namespace QtcUtilities {
namespace Internal {
namespace Ci {
namespace Drone {

struct Settings
{
  QUrl url;
  QByteArray user;
  QByteArray pass;

  bool isValid () const;
};

class Node : public QObject, public ModelItem
{
  Q_OBJECT

  public:
    Node (ModelItem &parent, const Settings &settings);

    Settings settings () const;
    void setSettings (const Settings &settings);

  signals:
    void updated (ModelItem *item);
    void added (ModelItem *item);
    void reset ();

  public slots:
    void contextMenu (ModelItem *item);

  protected:
    void timerEvent (QTimerEvent *e) override;

  private slots:
    void replyFinished (QNetworkReply *reply);

  private:
    void login ();
    void getReposotories ();
    void parseRepositories (const QByteArray &reply);
    void getBuilds (ModelItem &repository);
    void parseBuilds (const QByteArray &reply, ModelItem &repository);
    void parseBuild (const QJsonObject &object, ModelItem &build);
    void updateRepository (ModelItem &repository, const ModelItem &build);
    void getJobs (ModelItem &build);
    void parseJobs (const QByteArray &reply, ModelItem &build);
    void parseJob (const QJsonObject &object, ModelItem &job);
    void getLogs (ModelItem &job);

    Settings settings_;

    QList<QNetworkReply *> pendingReplies_;
    QNetworkAccessManager *manager_;
};

} // namespace Drone
} // namespace Ci
} // namespace Internal
} // namespace QtcUtilities
