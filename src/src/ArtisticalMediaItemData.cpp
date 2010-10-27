#include <Nepomuk/ResourceManager>
#include <Nepomuk/Variant>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Tag>
#include <Nepomuk/Resource>
#include <Nepomuk/Tag>

#include <taglib/fileref.h>
#include <taglib/tag.h>




//#include <Nepomuk/Resour1ceManager>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <Nepomuk/Tag>


#include "ArtisticalMediaItemData.hpp"
#include "Ontologies.hpp"

ArtisticalMediaItemData::ArtisticalMediaItemData(QString file)
{
  // NOTE: This code is not realy usefull, because we don not need create an AlbumMediaItemData,
  //       only the ""gets"" functions are usefull
  Nepomuk::Resource rFile(file);
  Nepomuk::Variant variant;
  TagLib::FileRef id3File(file.toStdString().c_str());

  if ( (variant = rFile.property(NID3_OFFICIALARTISTWEBPAGE)).isString()) 
    mArtistWebsite = variant.toString();
  else
    mArtistWebsite = KUrl();
  // TODO: Search how read the tag WOAR from ID3
  // TODO: Search from where read the original media and implement it
  // We verificate with ID3 tag
//   if ( !id3File.isNull() && id3File.tag()->album().toCString() != mAlbum.toStdString().c_str() )
//   {
//     // ID3 tag is more importan than data stored in Nepomuk.
//     // We use ID3 tag and update the data stored in nepomuk
//     mAlbum = id3File.tag()->album().toCString();
//     rFile.setProperty(NID3_ALBUMTITLE, Nepomuk::Variant(mAlbum) );
//     rFile.setProperty(NID3_ORIGINALALBUMTITLE, Nepomuk::Variant(mAlbum) );
//   }

//   if ( (variant = rFile.property(NID3_TRACKNUMBER)).isInt())
//     mTrackNumber = variant.toInt();
//   else
//     mTrackNumber = 0;
//   // We verificate with ID3 tag
//   if ( !id3File.isNull() && id3File.tag()->track() != mTrackNumber )
//   {
//     // ID3 tag is more importan than data stored in Nepomuk.
//     // We use ID3 tag and update the data stored in nepomuk
//     mTrackNumber = id3File.tag()->track();
//     rFile.setProperty(NID3_TRACKNUMBER, Nepomuk::Variant(mAlbum) );
//   }
}

KUrl ArtisticalMediaItemData::artistWebsite()
{
  return mArtistWebsite;
}

QString ArtisticalMediaItemData::originalMedia()
{
  return  mOriginalMedia;
}
