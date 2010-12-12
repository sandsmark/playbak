/*
 *  The PlaybaK Multimedia Player's library.
 *  Copyright (C) 2010 PlaybaK Development Team (see AUTHORS file)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef PLAYBAK_ONTOLOGIES_H
#define PLAYBAK_ONTOLOGIES_H

#include <QString>

// Album
static const QString NID3_ALBUMTITLE      = "http://www.semanticdesktop.org/ontologies/nid3#albumTitle";
static const QString NID3_ORIGINALALBUMTITLE = "http://www.semanticdesktop.org/ontologies/nid3#originalAlbumTitle";
static const QString XESAM_ALBUM          = "http://freedesktop.org/standards/xesam/1.0/core#album";
// Artist
static const QString NID3_ORIGINALARTIST  = "http://www.semanticdesktop.org/ontologies/nid3#originalArtist";
static const QString NIE_LEADERARTIST     = "http://www.semanticdesktop.org/ontologies/nid3#leadArtist";
static const QString NEXIF_ARTIST         = "http://www.semanticdesktop.org/ontologies/2007/05/10/nexif#artist";
static const QString XESAM_ARTIST         = "http://freedesktop.org/standards/xesam/1.0/core#artist";
// Artist webpage
static const QString NID3_OFFICIALARTISTWEBPAGE = "http://www.semanticdesktop.org/ontologies/nid3#officialArtistWebpage";
// Bitrate
static const QString XESAM_BITRATE        = "http://freedesktop.org/standards/xesam/1.0/core#audioBitrate";
// BPM NOTE: ¿Lo usamos?
static const QString XESAM_BPM            = "http://freedesktop.org/standards/xesam/1.0/core#audioBPM";
// Codec
static const QString XESAM_AUDIOCODEC     = "http://freedesktop.org/standards/xesam/1.0/core#audioCodec";
// Comment
static const QString XESAM_COMMENT        = "http://freedesktop.org/standards/xesam/1.0/core#comment";
// Composer
static const QString XESAM_COMPOSER       = "http://freedesktop.org/standards/xesam/1.0/core#composer";
// Copyright URL
// Created
static const QString NAO_CREATED          = "http://www.semanticdesktop.org/ontologies/2007/08/15/nao#created";
static const QString NFO_FILECREATED      = "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#fileCreated";
static const QString NIE_CONTENTCREATED   = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#contentCreated";
// Disc number
static const QString XESAM_DISCNUMBER     = "http://freedesktop.org/standards/xesam/1.0/core#discNumber";
// File size
static const QString XESAM_SIZE           = "http://freedesktop.org/standards/xesam/1.0/core#size";
// First played
static const QString XESAM_FIRSTUSED      = "http://freedesktop.org/standards/xesam/1.0/core#firstUsed";
// Genre
static const QString XESAM_GENRE          = "http://freedesktop.org/standards/xesam/1.0/core#genre";
static const QString NID3_CONTENTTYPE     = "http://www.semanticdesktop.org/ontologies/nid3/#contentType";
// Involvd persons
static const QString NID3_INVOLVEDPERSONS = "http://www.semanticdesktop.org/ontologies/nid3/#involvedPerson";
// Keywords
static const QString NIE_KEYWORD          = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#keyword";
// Language
static const QString NID3_LANGUAGE        = "http://www.semanticdesktop.org/ontologies/2007/05/10/nid3/#language";
static const QString NIE_LANGUAGE         = "http://www.semanticdesktop.org/ontologies/nie/#language";
// Last played
static const QString XESAM_LASTUSED       = "http://freedesktop.org/standards/xesam/1.0/core#lastUsed";
// Last updated
static const QString NFO_LASTUPDATED      = "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#fileLastModified";
static const QString NIE_LASTUPDATE       = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#contentLastModified";
// Length
static const QString XESAM_MEDIADURATION  = "http://freedesktop.org/standards/xesam/1.0/core#mediaDuration";
static const QString NID3_LENGHT          = "http://www.semanticdesktop.org/ontologies/nid3/#length";
// License
static const QString NIE_LICENSE          = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#license";
// License type
static const QString NIE_LICENSETYPE      = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#licenseType";
// Mime type
static const QString NIE_MIMETYPE         = "http://www.semanticdesktop.org/ontologies/2007/01/19/nie#mimeType";
// Play count
static const QString XESAM_USERCOUNT      = "http://freedesktop.org/standards/xesam/1.0/core#useCount";
// Rating
static const QString XESAM_RATING         = "http://freedesktop.org/standards/xesam/1.0/core#userRating";
static const QString XESAM_AUTORATING     = "http://freedesktop.org/standards/xesam/1.0/core#autoRating";
// Sample rate
static const QString XESAM_AUDIOSAMPLERATE= "http://freedesktop.org/standards/xesam/1.0/core#audioSampleRate";
// Score
static const QString NAO_SCORE            = "http://www.semanticdesktop.org/ontologies/nao#score";
// Title
static const QString NID3_TITLE           = "http://www.semanticdesktop.org/ontologies/2007/05/10/nid3#title";
static const QString NIE_TITLE            = "http://www.semanticdesktop.org/ontologies/nie#title";
static const QString XESAM_TITLE          = "http://freedesktop.org/standards/xesam/1.0/core#title";
// Tag
static const QString NAO_TAG              = "http://semanticdesktop.org/ontologies/2007/08/15/nao#Tag";
// Track number
static const QString NID3_TRACKNUMBER     = "http://www.semanticdesktop.org/ontologies/nid3#trackNumber";
static const QString XESAM_TRACKNUMBER    = "http://freedesktop.org/standards/xesam/1.0/core#trackNumber";
// Url
static const QString XESAM_URL            = "http://freedesktop.org/standards/xesam/1.0/core#url";
// Year
static const QString NID3_ORIGINALRELASEYEAR  = "http://www.semanticdesktop.org/ontologies/nid3#originalReleaseYear";
static const QString NID3_RECORDINGYEAR   = "http://www.semanticdesktop.org/ontologies/nid3#recordingYear";
static const QString XESAM_CONTENTCREATED = "http://freedesktop.org/standards/xesam/1.0/core#contentCreated";

#endif