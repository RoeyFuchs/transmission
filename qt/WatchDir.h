/*
 * This file Copyright (C) 2009-2015 Mnemosyne LLC
 *
 * It may be used under the GNU GPL versions 2 or 3
 * or any future license endorsed by Mnemosyne LLC.
 *
 * $Id$
 */

#ifndef QTR_WATCH_DIR_H
#define QTR_WATCH_DIR_H

#include <QObject>
#include <QSet>
#include <QString>

class QFileSystemWatcher;

class TorrentModel;

class WatchDir: public QObject
{
    Q_OBJECT

  public:
    WatchDir (const TorrentModel&);
    ~WatchDir ();

  public:
    void setPath (const QString& path, bool isEnabled);

  private:
    enum { OK, DUPLICATE, ERROR };
    int metainfoTest (const QString& filename) const;

  signals:
    void torrentFileAdded (QString filename);

  private slots:
    void watcherActivated (const QString& path);
    void onTimeout ();

  private slots:
    void rescanAllWatchedDirectories ();

  private:
    const TorrentModel& myModel;
    QSet<QString> myWatchDirFiles;
    QFileSystemWatcher * myWatcher;
};

#endif // QTR_WATCH_DIR_H