/*
    Copyright (c) 2011, <copyright holder> <email>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "PlaylistModel.h"

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
        return QVariant();
  if (role == Qt::DisplayRole)
    if (m_items.size() > index.row() )
      return m_items[index.row()]->url();
  return QVariant();
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
  return m_items.size();
}

PlaylistModel::PlaylistModel(QObject *parent) :
  QAbstractListModel(parent)
{
  
}

PlaylistModel::PlaylistModel(const PlaylistModel& other)
{

}

PlaylistModel::~PlaylistModel()
{

}

PlaylistModel& PlaylistModel::operator=(const PlaylistModel& other)
{
    return *this;
}

bool PlaylistModel::operator==(const PlaylistModel& other) const
{
///TODO: return ...;
return false;
}

void PlaylistModel::addItem(const KUrl& url)
{
  m_items.append(new MediaItem(url));
}


