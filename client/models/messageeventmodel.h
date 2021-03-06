/**************************************************************************
 *                                                                        *
 * Copyright (C) 2015 Felix Rohrbach <kde@fxrh.de>                        *
 *                                                                        *
 * This program is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU General Public License            *
 * as published by the Free Software Foundation; either version 3         *
 * of the License, or (at your option) any later version.                 *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                        *
 **************************************************************************/

#ifndef LOGMESSAGEMODEL_H
#define LOGMESSAGEMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QModelIndex>

namespace QMatrixClient
{
    class Room;
    class Connection;
}

class Message;
class QuaternionRoom;

class MessageEventModel: public QAbstractListModel
{
        Q_OBJECT
    public:
        enum EventRoles {
            EventTypeRole = Qt::UserRole + 1,
            TimeRole,
            DateRole,
            AuthorRole,
            ContentRole,
            ContentTypeRole,
            HighlightRole
        };

        MessageEventModel(QObject* parent = nullptr);
        virtual ~MessageEventModel();

        void setConnection(QMatrixClient::Connection* connection);
        void changeRoom(QMatrixClient::Room* room);

        //override QModelIndex index(int row, int column, const QModelIndex& parent=QModelIndex()) const;
        //override QModelIndex parent(const QModelIndex& index) const;
        int rowCount(const QModelIndex& parent) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    public slots:
        void newMessage(Message* messageEvent);

    private:
        QMatrixClient::Connection* m_connection;
        QuaternionRoom* m_currentRoom;
        QList<Message*> m_currentMessages;
};

#endif // LOGMESSAGEMODEL_H
