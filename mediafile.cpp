#include "mediafile.h"

MediaFile::MediaFile(QString filePath)
{
    this->_filePath = filePath;
    this->_artist = "Josh Woodward";
    this->_title = "California Lullabye";
    this->_duration = 184;
    this->_playing = false;
}
