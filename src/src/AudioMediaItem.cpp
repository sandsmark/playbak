#include "Ontologies.hpp"

#include <Nepomuk/ResourceManager>
#include <Nepomuk/Variant>
#include <Nepomuk/Types/Class>
#include <Nepomuk/Tag>
#include <Nepomuk/Resource>
#include <Nepomuk/Tag>

#include <taglib/fileref.h>
#include <taglib/tag.h>




// #include <Nepomuk/Resour1ceManager>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <Nepomuk/Tag>

#include "AudioMediaItem.hpp"

AudioMediaItem::AudioMediaItem(KUrl url) :
  MediaItem(url)
{
  // TODO: Read from nepomuk the subtype (we need create own ontology)
  mSubtype = AudioMediaItem::Subtype::NORMAL;
}

void AudioMediaItem::setSubtype(Subtype::AudioMediaItemSubtype subtype)
{
  mSubtype = subtype;
  // TODO: Save in nepomuk this data (we need create own ontology)
}

AudioMediaItem::Subtype::AudioMediaItemSubtype AudioMediaItem::subtype()
{
  return mSubtype;
}
